#pragma once
#include "../Drawable/Drawable.h"
#include "../Utilities/NumericDataTypes.h"

class SolidCone : public Drawable
{
public:
	SolidCone( Graphics& gdi, f32 scale );
	void SetPos( DirectX::XMFLOAT3 pos ) noexcept;
	void Rotate( f32 dx, f32 dy ) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	DirectX::XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
	f32 m_fPitch;
	f32 m_fYaw;
};