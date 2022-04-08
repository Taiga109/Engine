#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "CollisionPrimitive.h"
#include <stdlib.h>
#include <time.h>
#include "Audio.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input,Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Resetpos();

	void gameReset();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugText debugText;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spritetitle = nullptr;
	Sprite* spritegameover = nullptr;
	Sprite* spriteui = nullptr;

	Model* modelbox = nullptr;
	Model* modelbeltconber = nullptr;

	Model* modelbefordonut = nullptr;
	Model* modeldonut = nullptr;

	Model* modelcookiee = nullptr;
	Model* modelcookieeafter = nullptr;

	Model* modelpress = nullptr;

	Object3d* objbeltconber = nullptr;
	Object3d* objbox = nullptr;
	Object3d* objpress = nullptr;
	Object3d* objbefordonut = nullptr;
	Object3d* objdonut = nullptr;

	Object3d* objbecookiee = nullptr;
	Object3d* objcookieeafter = nullptr;

	XMFLOAT3 donutpos;
	XMFLOAT3 cookieepos;

	float spherespeedZ = 0.3f;
	float spherespeedx = 0.0001f;
	Sphere sphere;
	Sphere sphere2;
	bool reset = false;
	bool press = false;
	bool change = false;
	bool gameover = false;
	int speedlevel = 0;
	int count = 0;
	int score = 0;
	int type = 1;
	int scene = 0;
	Ray ray;
};

