#include "FBXLoader.h"
#include <cassert>

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
