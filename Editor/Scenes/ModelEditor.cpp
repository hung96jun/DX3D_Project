#include "stdafx.h"
#include "ModelEditor.h"
//#include "Model/ModelExporter.h"

ModelEditor::ModelEditor()
{
}

ModelEditor::~ModelEditor()
{
}

void ModelEditor::GUIRender()
{
	if (ImGui::Begin("ModelEditor"))
	{
		if (ImGui::Button("LoadModel"))
		{
			DIALOG->OpenDialog("LoadModel", "LoadModel", ".fbx", "../Datas/Assets/Models");
		}

		if (DIALOG->Display("LoadModel"))
		{
			if (DIALOG->IsOk())
			{

			}
		}

		ImGui::End();
	}
}

void ModelEditor::ResizeScreen()
{
}
