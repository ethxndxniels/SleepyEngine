#pragma once
#include "Drawable.h"
#include "../Bindable/Bindables/ConstantBuffers.h"
#include "../SceneManager/RenderTechnique.h"

class DirectionalLight : public Drawable
{
public:
	DirectionalLight( GraphicsDeviceInterface& gfx, RenderTechnique renderTechnique );
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void UpdateCBuffers( GraphicsDeviceInterface& gdi, DirectX::XMMATRIX lightViewMatrix, DirectX::XMMATRIX lightProjectionMatrix, DirectX::XMFLOAT3 camPos );
	void Draw( GraphicsDeviceInterface& gdi ) const noexcept;
private:
	struct LightBufferType
	{
		DirectX::XMFLOAT3 lightDirection = { 0.0f, -1.0f, 0.0f };
		float padding;
		float specularIntensity = 1.0f;
		float att = 0.5f;
		float specularPower = 128.0f;
		float padding2;
		DirectX::XMMATRIX cameraMatrix;
		DirectX::XMMATRIX projInvMatrix;
	} lbuf;
	std::shared_ptr<Bind::PixelConstantBuffer<LightBufferType>> pcs;
	struct CamPosBuffer
	{
		DirectX::XMFLOAT3 camPos;
		float padding3;
		DirectX::XMMATRIX lightViewMatrix;
		DirectX::XMMATRIX lightProjMatrix;
	} cambuf;
	std::shared_ptr<Bind::PixelConstantBuffer<CamPosBuffer>> pcs2;
	struct DirectionalLightDirection
	{
		DirectX::XMFLOAT3 lightDirection = { 0.0f, -1.0f, 0.0f };
		float padding4;
	} dlcbuf;
	std::shared_ptr<Bind::PixelConstantBuffer<DirectionalLightDirection>> pcs3;
};