#pragma once

#include <DirectXMath.h>

struct Sphere
{
	DirectX::XMVECTOR center = { 0,0,0,1 };

	float radius = 1.0f;
};

struct Plane
{
	DirectX::XMVECTOR nomal = { 0,1,0,0 };

	float distance = 0.0f;
};

class Triangle
{
public:
	//頂点座標３つ
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;
	//法線ベクトル
	DirectX::XMVECTOR normal;

	void ComputeNormal();
};

struct Ray
{
	DirectX::XMVECTOR start = { 0,0,0,1 };
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};
