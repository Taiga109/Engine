#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "Collision.h"


using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteui);
	safe_delete(objbox);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);


	this->dxCommon = dxCommon;
	this->input = input;


	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/title.png")) {
		assert(0);
		return;
	}
	// 前景スプライト生成


	// テクスチャ読み込み
	if (!Sprite::LoadTexture(2, L"Resources/gameover.png")) {
		assert(0);
		return;
	}
	// 前景スプライト生成


	// テクスチャ読み込み
	if (!Sprite::LoadTexture(3, L"Resources/ui.png")) {
		assert(0);
		return;
	}
	// 前景スプライト生成
	spriteui = Sprite::Create(3, { 760.0f,400.0f });
	spriteui->SetSize({ 520,320 });
	// 3Dオブジェクト生成


	objbox = Object3d::Create();

	modelbox = modelbox->CreateFromObj("box");
	objbox->SetModel(modelbox);
	float s = 1.0;
	objbox->SetScale({ s,s,s });

	Object3d::SetTarget({ 0, 1, 0 });
	Object3d::SetEye({ 0, 0, -800 });

	x = 0;
	y = 10;
	ax = 0.0f;
	ay = 0.0f;


	vx = 0.0f;
	vy = 0.0f;
}
void GameScene::Update()
{

	objbox->Update();
	if (input->PushKey(DIK_1))
	{
		part = 0;
	}

	else if (input->PushKey(DIK_2))
	{
		part = 1;
	}

	else if (input->PushKey(DIK_3))
	{
		part = 2;
	}

	objbox->SetPosition({ x,y,0 });
	//等速直線運動
	if (part == 0)
	{

		if (input->PushKey(DIK_SPACE) && flag == false)
		{
			flag = true;
			if (vx == 0)
			{
				vx = 1.0f;
			}
		}
		if (flag == true)
		{
			x = x + vx;
		}
		std::ostringstream modestr;
		modestr << "mode(1)";


		debugText.Print(modestr.str(), 50, 300, 1.0f);
	}
	//等加速度運動
	else if (part == 1)
	{

		if (input->PushKey(DIK_SPACE) && flag == false)
		{
			flag = true;
			if (ax == 0)
			{
				ax = 1.0f;
			}
		}
		if (flag == true)
		{
			vx = vx + ax;
			x = vx;
		}

		std::ostringstream modestr;
		modestr << "mode("
			<< "2"
			<< ")";
		debugText.Print(modestr.str(), 50, 300, 1.0f);
	}

	else if (part == 2)
	{
		if (input->PushKey(DIK_SPACE) && flag == false)
		{
			flag = true;
		}
		if (flag == true)
		{

			vy = vy + 9.8;
			y = y + -vy;
			
			if (y <= -500)
			{
				y = -500;
			}
		}
		std::ostringstream modestr;
		modestr << "mode("
			<< "3"
			<< ")";
		debugText.Print(modestr.str(), 50, 300, 1.0f);
	}


	if (t >= 60)
	{
		flag = false;
		Resetpos();
		count = 0;
	}
	if (flag == true)
	{
		t++;
	}
	if (input->TriggerKey(DIK_UP) && flag == false)
	{
		ax += 5.0;
		vx += 5.0;
	}
	if (input->TriggerKey(DIK_DOWN) && flag == false && ax > 0)
	{
		ax -= 5.0;
		vx -= 5.0;
	}
	std::ostringstream ui;
	ui << "push up add ax vx";
	debugText.Print(ui.str(), 50, 400, 1.0f);
	std::ostringstream ui2;
	ui2 << "push down subtract ax vx";
	debugText.Print(ui2.str(), 50, 450, 1.0f);
	std::ostringstream a;
	a << "ax,vx("
		<< ax <<","
		<< vx
		<< ")";
	debugText.Print(a.str(), 50, 350, 1.0f);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画

	objbox->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::Resetpos()
{
	x = 0;
	y = 10;
	ax = 0.0f;
	ay = 0.0f;

	t = 0;
	vx = 0.0f;
	vy = 0.0f;
}