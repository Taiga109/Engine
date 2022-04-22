#include "fbxsdk.h"


#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FBXLoader
{
public:
	// シングルトンインスタンスの取得
	static FBXLoader* GetInstance();

	// 初期化
	void Initialize(ID3D12Device* device);
	// 後始末
	void Finalize();

private:
	// D3D12デバイス
	ID3D12Device* device = nullptr;
	// FBXマネージャ
	FbxManager* fbxManager = nullptr;
	// FBXインポータ
	FbxImporter* fbxImporter = nullptr;

};

