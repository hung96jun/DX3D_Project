#include "Framework.h"
#include "ModelExporter.h"

ModelExporter::ModelExporter(const string Name, const string File)
{
    CONSTRUCTOR_DEBUG();
 
    Importer = new Assimp::Importer();

    Importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
    Importer->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS);

    Scene = Importer->ReadFile(File,
        aiProcessPreset_TargetRealtime_MaxQuality |         //메쉬의 접선공간 계산
        aiProcess_CalcTangentSpace |                        //메쉬의 모든 정점에서 부드러운 법선 생성
        aiProcess_GenSmoothNormals |                        //모든 메쉬에서 동일한(중복) 정점 데이터 세트를 식별하고 합체 - 인덱스
        aiProcess_JoinIdenticalVertices |                   //메쉬의 수를 줄이기위한 후처리 단계(메시 수를 줄이기 위한 최적화)
        aiProcess_OptimizeMeshes |                          //정점 캐시의 지역성을 높이기위해 삼각형 재정리.정렬
        aiProcess_ImproveCacheLocality |                    // 단일 정점에 동시에 영향을 미치는 본의 수를 제한
        aiProcess_LimitBoneWeights |                        //큰메쉬를 작은메쉬로 분할
        aiProcess_SplitLargeMeshes |                        //모든 메쉬의 면을 삼각화
        aiProcess_Triangulate |                             //비 UV매핑을 적절한 텍스쳐 좌표 체널로 변경
        aiProcess_GenUVCoords |                             //p:primitvetopology= 연결성 정보, P Type정렬
        aiProcess_SortByPType |                             //선or점 정렬된것들 정리(지우거나 채우거나)
        aiProcess_FindDegenerates |                         //유효하지않은 데이터 찾기
        aiProcess_FindInvalidData |                         //중복메시 찾아 첫번째 메시로 참조
        aiProcess_FindInstances |                           //구조체 검사
        aiProcess_ValidateDataStructure |                   //무손실로 또는 일부 임계 값에 따라 본 제거 
        aiProcess_Debone |                                  //왼손좌표계로 바꿔라);
        aiProcess_ConvertToLeftHanded);

    assert(Scene != nullptr);
}

ModelExporter::~ModelExporter()
{
    DESTRUCTOR_DEBUG();

    delete Importer;
}

void ModelExporter::ExportMaterial()
{
    ReadMaterial();
    WriteMaterial();
}

void ModelExporter::ExportMesh()
{
    ReadNode(Scene->mRootNode, -1, -1);
    ReadMesh(Scene->mRootNode);
    WriteMesh();
}

void ModelExporter::ExportClip(const string ClipName)
{
    int animCount = static_cast<int>(Scene->mNumAnimations);
    for (int i = 0; i < animCount; i++)
    {
        Clip* clip = ReadClip(Scene->mAnimations[i]);
        WriterClip(clip, ClipName, i);
    }
}

void ModelExporter::ReadMaterial()
{
    for (UINT i = 0; i < Scene->mNumMaterials; i++)
    {
        aiMaterial* srcMaterial = Scene->mMaterials[i];
        Material* material = new Material();

        material->SetName(srcMaterial->GetName().C_Str());
        
        aiColor3D color;
        MaterialBuffer::BufferData& data = material->GetData();

        srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        data.Diffuse = Float4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
        data.Specular = Float4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
        data.Ambient = Float4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
        data.Emissive = Float4(color.r, color.g, color.b, 1.0f);

        srcMaterial->Get(AI_MATKEY_SHININESS, data.Shininess);

        aiString file;
        srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
        material->SetDiffuseMap(ToString(CreateTexture(file.C_Str())));
        file.Clear();

        srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
        material->SetSpecularMap(ToString(CreateTexture(file.C_Str())));
        file.Clear();
        
        srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
        material->SetNormalMap(ToString(CreateTexture(file.C_Str())));
        file.Clear();

        Materials.push_back(material);
    }
}

void ModelExporter::WriteMaterial()
{
    string savePath = "../Datas/Models/Materials/" + Name + "/";
    string file = Name + ".mds";

    CreateFolders(savePath);

    BinaryWrite* writer = new BinaryWrite(savePath + file);
    writer->WriteUInt(static_cast<UINT>(Materials.size()));
}

const string ModelExporter::CreateTexture(string File)
{
    if (File.length() == 0)
        return "";

    string fileName = GetFileNameWithoutExtension(File) + ".png";
    string path = "../Datas/Textures/Model/" + Name + "/" + fileName;
    CreateFolders(path);

    const aiTexture* texture = Scene->GetEmbeddedTexture(File.c_str());

    if (texture == nullptr)
        return "";

    if (texture->mHeight < 1)
    {
        BinaryWrite writer(path);
        writer.WriteByte(texture->pcData, texture->mWidth);
    }
    else
    {
        Image image;
        image.width = texture->mWidth;
        image.height = texture->mHeight;
        image.pixels = (uint8_t*)(texture->pcData);
        image.rowPitch = image.width * 4;
        image.slicePitch = image.width * image.height * 4;

        SaveToWICFile(image, WIC_FLAGS_NONE,
            GetWICCodec(WIC_CODEC_PNG), ToString(path).c_str());
    }

    return path;
}

void ModelExporter::ReadMesh(aiNode* Node)
{
    for (UINT i = 0; i < Node->mNumMeshes; i++)
    {
        MeshData* mesh = new MeshData();
        mesh->Name = Node->mName.C_Str();

        UINT index = Node->mMeshes[i];
        aiMesh* srcMesh = Scene->mMeshes[index];
        mesh->MaterialIndex = srcMesh->mMaterialIndex;

        vector<VertexWeights> vertexWeights(srcMesh->mNumVertices);
        ReadBone(srcMesh, vertexWeights);

        mesh->Vertices.resize(srcMesh->mNumVertices);
        for (UINT v = 0; v < srcMesh->mNumVertices; v++)
        {
            ModelVertex vertex;
            memcpy(&vertex.Position, &srcMesh->mVertices[v], sizeof(Float3));

            if (srcMesh->HasTextureCoords(0))
                memcpy(&vertex.Uv, &srcMesh->mTextureCoords[0][v], sizeof(Float2));

            if (srcMesh->HasNormals())
                memcpy(&vertex.Normal, &srcMesh->mNormals[v], sizeof(Float3));

            if (srcMesh->HasTangentsAndBitangents())
                memcpy(&vertex.Tangent, &srcMesh->mTangents[v], sizeof(Float3));

            if (vertexWeights.empty() == false)
            {
                vertexWeights[i].Normalize();

                vertex.Indices.x = static_cast<float>(vertexWeights[v].Indices[0]);
                vertex.Indices.y = static_cast<float>(vertexWeights[v].Indices[1]);
                vertex.Indices.z = static_cast<float>(vertexWeights[v].Indices[2]);
                vertex.Indices.w = static_cast<float>(vertexWeights[v].Indices[3]);

                vertex.Weights.x = vertexWeights[v].Weights[0];
                vertex.Weights.y = vertexWeights[v].Weights[1];
                vertex.Weights.z = vertexWeights[v].Weights[2];
                vertex.Weights.w = vertexWeights[v].Weights[3];
            }

            mesh->Vertices[v] = vertex;
        }

        mesh->Indices.resize(srcMesh->mNumFaces * 3);
        for (UINT f = 0; f < srcMesh->mNumFaces; f++)
        {
            aiFace& face = srcMesh->mFaces[f];

            for (UINT j = 0; j < face.mNumIndices; j++)
            {
                mesh->Indices[f * 3 + j] = face.mIndices[j];
            }
        }

        Meshes.push_back(mesh);
    }

    for (UINT i = 0; i < Node->mNumChildren; i++)
        ReadMesh(Node->mChildren[i]);
}

void ModelExporter::ReadNode(aiNode* Node, const int Index, const int Parent)
{
    NodeData* data = new NodeData();
    data->Index = Index;
    data->Parent = Parent;
    data->Name = Node->mName.C_Str();

    Matrix mat(Node->mTransformation[0]);
    data->Transform = XMMatrixTranspose(mat);
    Nodes.push_back(data);

    int childrenNum = static_cast<int>(Node->mNumChildren);
    for (int i = 0; i < childrenNum; i++)
        ReadNode(Node->mChildren[i], static_cast<int>(Nodes.size()), Index);
}

void ModelExporter::ReadBone(aiMesh* Mesh, vector<VertexWeights>& VertexWeights)
{
    int boneNum = Mesh->mNumBones;
    for (int i = 0; i < boneNum; i++)
    {
        UINT boneIndex = 0;
        string name = Mesh->mBones[i]->mName.C_Str();

        if (BoneMap.count(name) == 0)
        {
            boneIndex = BoneCount++;
            BoneMap[name] = boneIndex;

            BoneData* data = new BoneData();
            data->Name = name;
            data->Index = boneIndex;

            Matrix matrix(Mesh->mBones[i]->mOffsetMatrix[0]);
            data->Offset = XMMatrixTranspose(matrix);

            Bones.push_back(data);
        }
        else
        {
            boneIndex = BoneMap[name];
        }

        for (UINT j = 0; j < Mesh->mBones[i]->mNumWeights; j++)
        {
            UINT index = Mesh->mBones[i]->mWeights[i].mVertexId;
            VertexWeights[index].Add(boneIndex, Mesh->mBones[i]->mWeights[j].mWeight);
        }
    }
}

void ModelExporter::WriteMesh()
{
    string path = "../Datasa/Models/Meshes/" + Name + ".mesh";
    CreateFolders(path);

    BinaryWrite* writer = new BinaryWrite(path);
    writer->WriteUInt(static_cast<UINT>(Meshes.size()));
    for (MeshData* mesh : Meshes)
    {
        writer->WriteString(mesh->Name);
        writer->WriteUInt(mesh->MaterialIndex);

        writer->WriteUInt(static_cast<UINT>(mesh->Vertices.size()));
        writer->WriteByte(mesh->Vertices.data(), sizeof(ModelVertex) * 
            static_cast<UINT>(mesh->Vertices.size()));

        writer->WriteUInt(static_cast<UINT>(mesh->Indices.size()));
        writer->WriteByte(mesh->Indices.data(), sizeof(UINT) * 
            static_cast<UINT>(mesh->Indices.size()));

        delete mesh;
    }
    Meshes.clear();

    writer->WriteUInt(static_cast<UINT>(Nodes.size()));
    for (NodeData* node : Nodes)
    {
        writer->WriteInt(node->Index);
        writer->WriteString(node->Name);
        writer->WriteInt(node->Parent);
        writer->WriteMatrix(node->Transform);

        delete node;
    }
    Nodes.clear();

    writer->WriteUInt(static_cast<UINT>(Bones.size()));
    for (BoneData* bone : Bones)
    {
        writer->WriteInt(bone->Index);
        writer->WriteString(bone->Name);
        writer->WriteMatrix(bone->Offset);

        delete bone;
    }
    Bones.clear();

    delete writer;
}

Clip* ModelExporter::ReadClip(aiAnimation* Animation)
{
    Clip* clip = new Clip();
    clip->Name = Animation->mName.C_Str();
    clip->TickPerSec = static_cast<float>(Animation->mTicksPerSecond);
    clip->FrameCount = static_cast<UINT>(Animation->mDuration) + 1;

    vector<ClipNode> clipNodes;
    clipNodes.reserve(Animation->mNumMeshChannels);
    int channelNum = Animation->mNumChannels;
    for (int i = 0; i < channelNum; i++)
    {
        aiNodeAnim* srcNode = Animation->mChannels[i];
        
        ClipNode node;
        node.Name = srcNode->mNodeName;

        UINT keyCount = max(srcNode->mNumPositionKeys, srcNode->mNumRotationKeys);
        keyCount = max(keyCount, srcNode->mNumScalingKeys);

        node.Transform.reserve(clip->FrameCount);

        KeyTransform transform;
        for (UINT j = 0; j < keyCount; j++)
        {
            bool isFound = false;
            float t = static_cast<float>(node.Transform.size());

            if (j < srcNode->mNumPositionKeys &&
                Math::NearlyEqual(static_cast<float>(srcNode->mRotationKeys[j].mTime), t))
            {
                aiVectorKey key = srcNode->mPositionKeys[j];
                memcpy_s(&transform.Position, sizeof(Float3),
                    &key.mValue, sizeof(aiVector3D));

                isFound = true;
            }

            if (j < srcNode->mNumRotationKeys &&
                Math::NearlyEqual(static_cast<float>(srcNode->mRotationKeys[j].mTime), t))
            {
                aiQuatKey key = srcNode->mRotationKeys[j];
                transform.Rotation.x = static_cast<float>(key.mValue.x);
                transform.Rotation.y = static_cast<float>(key.mValue.y);
                transform.Rotation.z = static_cast<float>(key.mValue.z);
                transform.Rotation.w = static_cast<float>(key.mValue.w);

                isFound = true;
            }

            if (j < srcNode->mNumScalingKeys &&
                Math::NearlyEqual(static_cast<float>(srcNode->mRotationKeys[j].mTime), t))
            {
                aiVectorKey key = srcNode->mScalingKeys[j];
                memcpy_s(&transform.Scale, sizeof(Float3),
                    &key.mValue, sizeof(aiVector3D));

                isFound = true;
            }

            if (isFound == true)
                node.Transform.push_back(transform);
        }

        if (node.Transform.size() < clip->FrameCount)
        {
            UINT count = clip->FrameCount - static_cast<UINT>(node.Transform.size());
            KeyTransform keyTransform = node.Transform.back();

            for (UINT i = 0; i < count; i++)
                node.Transform.push_back(keyTransform);
        }

        clipNodes.push_back(node);
    }

    ReadKeyFrame(clip, Scene->mRootNode, clipNodes);

    return clip;
}

void ModelExporter::ReadKeyFrame(Clip* AnimClip, aiNode* Node, vector<ClipNode>& ClipNodes)
{
    KeyFrame* frame = new KeyFrame();
    frame->BoneName = Node->mName.C_Str();
    frame->Transform.reserve(AnimClip->FrameCount);
    for (UINT i = 0; i < AnimClip->FrameCount; i++)
    {
        ClipNode* node = nullptr;
        for (ClipNode& temp : ClipNodes)
        {
            if (temp.Name == Node->mName)
            {
                node = &temp;
                break;
            }
        }

        KeyTransform transform;
        if (node == nullptr)
        {
            Matrix matrix(Node->mTransformation[0]);
            matrix = XMMatrixTranspose(matrix);

            XMVECTOR s, r, t;
            XMMatrixDecompose(&s, &r, &t, matrix);
            XMStoreFloat3(&transform.Scale, s);
            XMStoreFloat4(&transform.Rotation, r);
            XMStoreFloat3(&transform.Position, t);
        }
        else
        {
            transform = node->Transform[i];
        }

        frame->Transform.push_back(transform);
    }

    AnimClip->KeyFrame.push_back(frame);

    int childrenNum = static_cast<int>(Node->mNumChildren);
    for (int i = 0; i < childrenNum; i++)
        ReadKeyFrame(AnimClip, Node->mChildren[i], ClipNodes);
}

void ModelExporter::WriterClip(Clip* AnimClip, const string ClipName, const UINT Index)
{
    string file = "../Datas/Models/Clips/" + Name + "/" +
        ClipName + to_string(Index) + ".clip";

    CreateFolders(file);

    BinaryWrite* writer = new BinaryWrite(file);
    writer->WriteString(AnimClip->Name);
    writer->WriteUInt(AnimClip->FrameCount);
    writer->WriteFloat(AnimClip->TickPerSec);
    writer->WriteUInt(static_cast<UINT>(AnimClip->KeyFrame.size()));

    for (KeyFrame* frame : AnimClip->KeyFrame)
    {
        writer->WriteString(frame->BoneName);
        writer->WriteUInt(static_cast<UINT>(frame->Transform.size()));
        writer->WriteByte(frame->Transform.data(), sizeof(KeyTransform) * static_cast<UINT>(frame->Transform.size()));

        delete frame;
    }

    delete AnimClip;
    delete writer;
}
