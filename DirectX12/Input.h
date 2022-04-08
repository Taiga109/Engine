#pragma once

#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <DirectXMath.h>
#include "WinApp.h"

using namespace DirectX;

enum MouseButton {
	Left,		//!< 左
	Right,		//!< 右
	Center,		//!< 真ん中
};

class Input
{
private:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //メンバ関数
	//初期化
	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	//更新
	void Update();
	// キーの押下をチェック
	bool PushKey(BYTE keyNumber);
	// キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);

	//キーボードデバイス生成
	bool CreateKeyDevice(HINSTANCE hInstance, HWND hwnd);
	//マウスデバイス生成
	bool CreateMouceDevice(HINSTANCE hInstance, HWND hwnd);

	// マウスの押下をチェック
	bool PushMouse(MouseButton buttonType);
	// マウスのトリガーをチェック
	bool TriggerMouse(MouseButton buttonType);
	//マウスの移動量取得
	XMFLOAT2 GetMouseVelocity();
	//マウスの位置取得
	XMFLOAT2 GetMousePosition();

private: //メンバ変数
	HWND hwnd;
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	ComPtr<IDirectInputDevice8> devmouse;
	BYTE keyState[256] = {};
	BYTE prevKeyState[256] = {};

private:
	static DIMOUSESTATE currentMouseState;
	static DIMOUSESTATE prevMouseState;
	static XMFLOAT2 mousePos;
};