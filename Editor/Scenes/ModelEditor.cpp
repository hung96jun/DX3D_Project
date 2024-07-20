#include "stdafx.h"
#include "ModelEditor.h"
#include "Framework/Model/ModelExporter.h"

ModelEditor::ModelEditor()
{
	CONSTRUCTOR_DEBUG();

	Exporter = new ModelExporter();
	//Exporter->ReadFile(L"Tank/Tank.fbx");
}

ModelEditor::~ModelEditor()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Exporter);
}

void ModelEditor::GUIRender()
{
	if (ImGui::Begin("ModelEditor"))
	{
		ModelLoader();

		ImGui::End();
	}
}

void ModelEditor::ResizeScreen()
{
}

void ModelEditor::ModelLoader()
{
	if (ImGui::TreeNode("Model Loader"))
	{
		ImGui::Text(string("File : " + FileName).c_str());
		ImGui::Text("Loading Success");

		if (ImGui::Button("LoadModel"))
		{
			DIALOG->OpenDialog("LoadModel", "LoadModel", ".fbx", "../Datas/Assets/Models");
		}

		if (DIALOG->Display("LoadModel"))
		{
			if (DIALOG->IsOk())
			{
				ImGui::Text("Loading...");
				string file = DIALOG->GetFilePathName();
				size_t index = file.find("Models\\");
				index += string("Models\\").size();
				file = file.substr(index);

				while ((index = file.find("\\")) != string::npos)
				{
					file[index] = '/';
				}

				index = GetFileExtension(file).size();
				FilePath = file.substr(0, file.size() - (index + 1));
				FileName = GetFileName(FilePath);

				Exporter->ReadFile(ToString(file));
			}

			DIALOG->Close();
		}

		if (Exporter->IsVailed() == false)
		{
			if (ImGui::Button(string(FileName + "_Export").c_str()))
			{
				ImGui::Text("Loading...");
				Exporter->ExportMesh(ToString(FilePath));
				Exporter->ExportMaterial(ToString(FilePath));
			}

			if (ImGui::Button(string(FileName + "_Export Mesh").c_str()))
			{
				ImGui::Text("Loading...");
				Exporter->ExportMesh(ToString(FilePath));
			}

			if (ImGui::Button(string(FileName + "_Export Material").c_str()))
			{
				ImGui::Text("Loading...");
				Exporter->ExportMaterial(ToString(FilePath));
			}
		}

		ImGui::TreePop();
	}
}
