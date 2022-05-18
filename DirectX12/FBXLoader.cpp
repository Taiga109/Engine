#include "FBXLoader.h"
#include <cassert>
#include "FbxModel.h"
#include <string>

FBXLoader* FBXLoader::GetInstance()
{
	static FBXLoader instance;
	return &instance;
}

void FBXLoader::Initialize(ID3D12Device* device)
{
	//�ď������`�F�b�N
	assert(fbxManager == nullptr);

	//�������烁���o�ϐ��ɑ��
	this->device = device;

	//FBX�}�l�[�W���̐���
	fbxManager = FbxManager::Create();

	//FBX�}�l�[�W���̓��o�͐ݒ�
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	//FBX�C���|�[�^�̐���
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FBXLoader::Finalize()
{
	//�e��FBX�C���X�^���X�̔j��
	fbxImporter->Destroy();
	fbxManager->Destroy();
}

void FBXLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode)
{
	string name = fbxNode->GetName();

	for (int i = 0; i < fbxNode->GetChildCount(); i++) {
		ParseNodeRecursive(model, fbxNode->GetChild(i));
	}
}

void FBXLoader::LoadModelFromFile(const string& modelName)
{
	//���f���Ɠ������O�̃t�H���_����ǂݍ���
	const string directoryPath = baseDirectory +
		modelName + "/";
	//�g���q.fbx��t��
	const string fileName = modelName + ".fbx";
	//�A�����ăt���p�X�𓾂�
	const string fullpath = directoryPath + fileName;

	//�t�@�C�������w�肵��FBX�t�@�C����ǂݍ���
	if (!fbxImporter->Initialize(fullpath.c_str(),-1,fbxManager->GetIOSettings()))
	{
		assert(0);
	}
	//�V�[������
	FbxScene* fbxScene =
		FbxScene::Create(fbxManager, "fbxScene");
	//�t�@�C�����烍�[�h����FBX�̏����V�[���ɃC���|�[�g
	fbxImporter->Import(fbxScene);
}


