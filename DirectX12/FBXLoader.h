#include "fbxsdk.h"


#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FBXLoader
{
private:
	using string = std::string;
public:
	// シングルトンインスタンスの取得
	static FBXLoader* GetInstance();

	// 初期化
	void Initialize(ID3D12Device* device);
	// 後始末
	void Finalize();
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode);

	void LoadModelFromFile(const string& modelName);
private:
	// D3D12デバイス
	ID3D12Device* device = nullptr;
	// FBXマネージャ
	FbxManager* fbxManager = nullptr;
	// FBXインポータ
	FbxImporter* fbxImporter = nullptr;
	
	

public:
	static const string baseDirectory;

	const std::string FBXLoader::baseDirectory =
		"Resources/";

};

