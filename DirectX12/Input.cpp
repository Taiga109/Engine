#include "Input.h"
#include <cassert>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

DIMOUSESTATE Input::currentMouseState;
DIMOUSESTATE Input::prevMouseState;
XMFLOAT2 Input::mousePos;

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd) {
	HRESULT result = S_FALSE;

	//初期化（一度だけ行う処理）
	result = DirectInput8Create
	(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr
	);
	if (FAILED(result)) 	{
		assert(0);
		return result;
	}

	this->hwnd = hwnd;

	CreateKeyDevice(hInstance, hwnd);
	CreateMouceDevice(hInstance, hwnd);

	return true;
}

void Input::Update() {
	HRESULT result;

	//キーボード情報の取得開始
	result = devkeyboard->Acquire();
	// 前回のキー入力を保存
	memcpy(prevKeyState, keyState, sizeof(keyState));
	//全キーの入力状態を取得する
	result = devkeyboard->GetDeviceState(sizeof(keyState), keyState);

	//マウス情報の取得開始
	result = devmouse->Acquire();
	prevMouseState = currentMouseState;
	// マウスの状態を取得
	result = devmouse->GetDeviceState(sizeof(currentMouseState), &currentMouseState);
	POINT p;
	// マウス座標(スクリーン座標)を取得する
	GetCursorPos(&p);
	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(hwnd, &p);
	// 変換した座標を保存
	mousePos.x = (float)p.x;
	mousePos.y = (float)p.y;
}

XMFLOAT2 Input::GetMouseVelocity() {
	return XMFLOAT2((float)currentMouseState.lX, (float)currentMouseState.lY);
}

XMFLOAT2 Input::GetMousePosition() {
	return XMFLOAT2(mousePos);
}

bool Input::PushKey(BYTE keyNumber) {
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 0でなければ押している
	if (keyState[keyNumber]) 	{
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerKey(BYTE keyNumber) {
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回が0で、今回が0でなければトリガー
	if (!prevKeyState[keyNumber] && keyState[keyNumber]) 	{
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::PushMouse(MouseButton buttonType) {
	// 異常な引数を検出
	assert(0 <= buttonType <= 4);

	// 0でなければ押している
	if (currentMouseState.rgbButtons[buttonType]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerMouse(MouseButton buttonType) {
	// 異常な引数を検出
	assert(0 <= buttonType <= 4);

	// 前回が0で、今回が0でなければトリガー
	if (!currentMouseState.rgbButtons[buttonType] && prevMouseState.rgbButtons[buttonType]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::CreateKeyDevice(HINSTANCE hInstance, HWND hwnd) {
	HRESULT result = S_FALSE;

	//キーボードデバイスの生成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel
	(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	return true;
}

bool Input::CreateMouceDevice(HINSTANCE hInstance, HWND hwnd) {
	HRESULT result = S_FALSE;

	//キーボードデバイスの生成
	result = dinput->CreateDevice(GUID_SysMouse, &devmouse, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//入力データ形式のセット
	result = devmouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//排他制御レベルのセット
	result = devmouse->SetCooperativeLevel
	(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	return true;
}