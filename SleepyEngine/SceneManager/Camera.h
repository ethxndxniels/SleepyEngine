#pragma once
#include <DirectXMath.h>
#include "../Utilities/NumericDataTypes.h"

enum class MatrixType
{
	Orthographic,
	Perspective
};

struct ViewSpace
{
	f32 width;
	f32 height;
	f32 nearZ;
	f32 farZ;
};

class Camera
{
public:
	Camera( const wchar_t* name, MatrixType matrixType, ViewSpace viewSpace, DirectX::XMFLOAT3 homePos = { 0.0f,0.0f,0.0f }, f32 homePitch = 0.0f, f32 homeYaw = 0.0f ) noexcept;
	~Camera();
public:
	DirectX::XMFLOAT3 GetPosition() noexcept;
	DirectX::XMMATRIX GetViewMatrix() noexcept;
	DirectX::XMMATRIX GetProjectionMatrix() noexcept;
	void Reset() noexcept;
	void Rotate( const f32 dx, const f32 dy ) noexcept;
	void Translate( DirectX::XMFLOAT3 translation ) noexcept;
private:
	DirectX::XMMATRIX GeneratePerpectiveProjectionMatrix( f32 width, f32 height, f32 nearZ, f32 farZ );
	DirectX::XMMATRIX GenerateOrthographicProjectionMatrix( f32 width, f32 height, f32 nearZ, f32 farZ );
public:
	f32 m_fPitch;
	f32 m_fYaw;
private:
	const wchar_t* m_sName;
	MatrixType m_MatrixType;
	ViewSpace m_ViewSpace;

	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_HomePos;
	f32 m_fHomePitch;
	f32 m_fHomeYaw;

	static constexpr f32 m_fTravelSpeed = 12.0f;
	static constexpr f32 m_fRotationSpeed = 0.004f;
	// TODO:
	// - Make Graphics API Independent
};