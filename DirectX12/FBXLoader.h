#include "fbxsdk.h"


#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FBXLoader
{
private:
	using string = std::string;
public:
	// �V���O���g���C���X�^���X�̎擾
	static FBXLoader* GetInstance();

	// ������
	void Initialize(ID3D12Device* device);
	// ��n��
	void Finalize();
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode);

	void LoadModelFromFile(const string& modelName);
private:
	// D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	// FBX�}�l�[�W��
	FbxManager* fbxManager = nullptr;
	// FBX�C���|�[�^
	FbxImporter* fbxImporter = nullptr;
	
	

public:
	static const string baseDirectory;

	const std::string FBXLoader::baseDirectory =
		"Resources/";

};

