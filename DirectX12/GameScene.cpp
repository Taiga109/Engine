#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "Collision.h"
#include "FBXLoader.h"


using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spritegameover);
	safe_delete(spriteui);
	safe_delete(spritetitle);
	safe_delete(objbeltconber);
	safe_delete(objbox);
	safe_delete(objpress);
	safe_delete(objbefordonut);
	safe_delete(objdonut);
	safe_delete(objbecookiee);
	safe_delete(objcookieeafter);


}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input,Audio* audio)
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
	spritetitle = Sprite::Create(1, { 0.0f,0.0f });

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(2, L"Resources/gameover.png")) {
		assert(0);
		return;
	}
	// 前景スプライト生成
	spritegameover = Sprite::Create(2, { 0.0f,0.0f });

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(3, L"Resources/ui.png")) {
		assert(0);
		return;
	}
	// 前景スプライト生成
	spriteui = Sprite::Create(3, { 760.0f,400.0f });
	spriteui->SetSize({ 520,320 });
	// 3Dオブジェクト生成

	objbeltconber = Object3d::Create();
	objbox = Object3d::Create();
	objpress = Object3d::Create();

	FBXLoader::GetInstance()->LoadModelFromFile("cube");
	objdonut = Object3d::Create();
	objbefordonut = Object3d::Create();

	objbecookiee = Object3d::Create();
	objcookieeafter = Object3d::Create();



	modeldonut = modeldonut->CreateFromObj("donut");
	modelbefordonut = modelbefordonut->CreateFromObj("befordonut");


	modelbeltconber = modelbeltconber->CreateFromObj("beltconber");
	modelbox = modelbox->CreateFromObj("box");
	modelpress = modelpress->CreateFromObj("press");

	modelcookiee = modelcookiee->CreateFromObj("cookiee");
	modelcookieeafter = modelcookieeafter->CreateFromObj("cookieeafter");


	objbeltconber->SetModel(modelbeltconber);
	objbox->SetModel(modelbox);
	objpress->SetModel(modelpress);

	objdonut->SetModel(modeldonut);
	objbefordonut->SetModel(modelbefordonut);

	objbecookiee->SetModel(modelcookiee);
	objcookieeafter->SetModel(modelcookieeafter);

	sphere.center = XMVectorSet(1.5, 2, 145, 1);
	sphere.radius = 30.0f;

	sphere2.center = XMVectorSet(1.5, 2, 145, 1);
	sphere2.radius = 10.0f;

	ray.start = XMVectorSet(0, 3, 0, 1);
	ray.dir = XMVectorSet(0, -1, 0, 0);

	objdonut->SetPosition({ 10, 5, 0 });
	objbefordonut->SetPosition({ -10, 5, 0 });

	Object3d::SetTarget({ 0, 1, 0 });
	Object3d::SetEye({ 25, 40.0f, -50.0f });

	donutpos.x = 0.06;
	donutpos.y = 2.0;
	donutpos.z = 120;

	cookieepos.x = 0.06;
	cookieepos.y = 2.0;
	cookieepos.z = 120;

}
void GameScene::Update()
{
	if (scene == 0)
	{
		if (input->PushKey(DIK_SPACE))
		{
			scene = 1;
		}
	}
	else if (scene == 1)
	{
		objbefordonut->Update();
		objdonut->Update();

		objbecookiee->Update();
		objcookieeafter->Update();

		objbeltconber->Update();
		objbox->Update();
		objpress->Update();

		XMFLOAT3 position = objpress->GetPosition();
		position.x = ray.start.m128_f32[0];
		position.y = ray.start.m128_f32[1];
		position.z = ray.start.m128_f32[2];

		objpress->SetPosition(position);

		if (type == 1)
		{
			objbefordonut->SetPosition(donutpos);
			objdonut->SetPosition(donutpos);
			donutpos.x = sphere.center.m128_f32[0];
			donutpos.y = sphere.center.m128_f32[1];
			donutpos.z = sphere.center.m128_f32[2];
			{
				XMVECTOR spheremoveZ = XMVectorSet(0, 0, spherespeedZ, 0);
				XMVECTOR spheremoveX = XMVectorSet(spherespeedx, 0, 0, 0);
				if (donutpos.x > -0.03 && donutpos.z > -50)
				{
					sphere.center -= spheremoveZ;
					sphere.center -= spheremoveX;
				}
				else if (donutpos.z <= -45)
				{
					Resetpos();
				}

			}
		}

		else if (type == 2)
		{
			objbecookiee->SetPosition(cookieepos);
			objcookieeafter->SetPosition(cookieepos);
			cookieepos.x = sphere2.center.m128_f32[0];
			cookieepos.y = sphere2.center.m128_f32[1];
			cookieepos.z = sphere2.center.m128_f32[2];
			{
				XMVECTOR spheremoveZ = XMVectorSet(0, 0, spherespeedZ, 0);
				XMVECTOR spheremoveX = XMVectorSet(spherespeedx, 0, 0, 0);
				if (cookieepos.x > -0.03 && cookieepos.z > -50)
				{
					sphere2.center -= spheremoveZ;
					sphere2.center -= spheremoveX;
				}
				else if (cookieepos.z <= -45)
				{
					Resetpos();
					if (gameover)
					{
						scene = 2;
						change = true;
						
						Resetpos();
					}
				}
				if (input->PushKey(DIK_1))
				{
					sphere2.center -= spheremoveZ;
					sphere2.center -= spheremoveX;
				}
				else if (input->PushKey(DIK_2))
				{
					sphere2.center += spheremoveZ;
					sphere2.center += spheremoveX;
				}
			}
		}

		//レイと球の当たり判定
		XMVECTOR inter;
		float distance;







		//stringstreamで変数の値を埋め込んで整形する
		std::ostringstream spherestr;
		spherestr << "Sphere:("
			<< std::fixed << std::setprecision(2)
			<< sphere.center.m128_f32[0] << ","//x
			<< sphere.center.m128_f32[1] << ","//y
			<< sphere.center.m128_f32[2] << ")";//z


		//レイ操作
		{
			XMVECTOR moveY = XMVectorSet(0, 1.0f, 0, 0);

			if (input->TriggerKey(DIK_SPACE) && press == false)
			{
				press = true;
			}
			if (press)
			{
				bool hit = Collision::CheckRay2Sphere(ray, sphere, &distance, &inter);
				bool gameoverhit = Collision::CheckRay2Sphere(ray, sphere2, &distance, &inter);
				if (hit)
				{
					count += 1;
					if (count >= 10)
					{
						score += 1;
						count = 0;
						speedlevel += 1;
						change = true;
					}
					if (speedlevel == 3)
					{
						spherespeedZ += 0.3;
						speedlevel = 0;
					}
					
				}
				else if (gameoverhit)
				{
					gameover = true;
					change = true;
					
				}
				ray.start -= moveY;

			}

			if (ray.start.m128_f32[1] <= -15)
			{
				press = false;
				reset = true;

			}
			else if (ray.start.m128_f32[1] >= 1)
			{
				ray.start.m128_f32[1] = 1;
				reset = false;

			}
			if (reset)
			{
				ray.start += moveY;
			}

			//std::ostringstream raystr;
			//raystr << "lay.start("
			//	<< std::fixed << std::setprecision(2)
			//	<< ray.start.m128_f32[0] << ","//x
			//	<< ray.start.m128_f32[1] << ","//y
			//	<< ray.start.m128_f32[2] << ")";//z

			//debugText.Print(raystr.str(), 50, 80, 1.0f);

			std::ostringstream scorestr;
			scorestr << "score("
				<< std::fixed << std::setprecision(2)
				<< score << ")"//x
				;

			debugText.Print(scorestr.str(), 50, 300, 1.0f);
		}

	}

	else if (scene == 2)
	{
		count++;
		if (input->PushKey(DIK_SPACE)&&count>=80)
		{
			count = 0;
			scene = 0;
			gameReset();
		}
	}


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
	objbeltconber->Draw();
	objbox->Draw();
	objpress->Draw();
	if (change == false)
	{
		objbefordonut->Draw();
	}
	else if (change)
	{
		objdonut->Draw();
	}

	if (change == false)
	{
		objbecookiee->Draw();
	}
	else if (change)
	{
		objcookieeafter->Draw();
	}


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
	if (scene == 0)
	{
		spritetitle->Draw();
	}
	else if (scene == 1)
	{
		spriteui->Draw();
	}
	else if (scene == 2)
	{
		spritegameover->Draw();
	}
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
	donutpos.x = 1.5;
	donutpos.y = 2.0;
	donutpos.z = 145;
	cookieepos.x = 1.5;
	cookieepos.y = 2.0;
	cookieepos.z = 145;
	sphere.center = XMVectorSet(1.5, 2, 145, 1);;
	sphere2.center = XMVectorSet(1.5, 2, 145, 1);;
	change = false;
	type = rand() % 2 + 1;
}

void GameScene::gameReset()
{
	Resetpos();
	speedlevel = 0;
	count = 0;
	score = 0;
	type = 1;

	spherespeedZ = 0.3f;
	spherespeedx = 0.0001f;
	gameover = false;
	reset = false;
	press = false;
	change = false;
}
