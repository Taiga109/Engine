#include "fbxsdk.h"
#include "FbxModel.h"
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
	//���f���i�[���[�g�p�X
	static const string baseDirectory;

	// ������
	void Initialize(ID3D12Device* device);
	// ��n��
	void Finalize();

	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent=nullptr);
	//���b�V���ǂݎ��
	void ParseMesh(FbxModel* model, FbxNode* fbxnode);
	//���_���W�ǂݎ��
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxmesh);
	//�ʏ��ǂݎ��
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxmesh);
	//�}�e���A���ǂݎ��
	void ParseMaterial(FbxModel* model, FbxNode* fbxnode);
	//�e�N�X�`���ǂݎ��
	void LoadTexture(FbxModel* model, const std::string& fullpath);

	//�f�B���N�g�����܂񂾃t�@�C���p�X����t�@�C�����𒊏o����
	std::string ExtractFileName(const std::string& path);
	void LoadModelFromFile(const string& modelName);
private:
	// D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	// FBX�}�l�[�W��
	FbxManager* fbxManager = nullptr;
	// FBX�C���|�[�^
	FbxImporter* fbxImporter = nullptr;
	
	

public:

	

	
	//�e�N�X�`�����Ȃ��ꍇ�̕W���e�N�X�`���t�@�C����
	static const string defaultTextureFileName;

};

