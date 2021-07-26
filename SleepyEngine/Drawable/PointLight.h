#pragma once
#include "./Drawable.h"
#include "../Bindable/Bindables/StructuredBuffers.h"
#include "../SceneManager/RenderTechnique.h"
#include "../Drawable/SolidSphere.h"

class PointLight : public Drawable
{
public:
	PointLight( GraphicsDeviceInterface& gdi, float radius );
	void Draw( GraphicsDeviceInterface& gdi );
	void Update( GraphicsDeviceInterface& gdi, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix, DirectX::XMFLOAT3 camPos );
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void Translate( DirectX::XMFLOAT3 vec );
	bool CameraIsInside( DirectX::XMFLOAT3 camPos );
private:
	struct PointLightData
	{
		alignas( 16 ) DirectX::XMFLOAT3 pos = { 10.0f, 9.0f, 2.5f };
		alignas( 16 ) DirectX::XMFLOAT3 ambient = { 0.2f, 0.2f, 0.2f };
		alignas( 16 ) DirectX::XMFLOAT3 diffuseColor = { 1.0f, 1.0f, 1.0f };
		float diffuseIntensity = 1.0f;
		float attConst = 1.0f;
		float attLin = 0.045f;
		float attQuad = 0.0075f;
		DirectX::XMFLOAT3 camPos;
		float radius = 5.0f;
		DirectX::XMMATRIX cameraMatrix;
		DirectX::XMMATRIX projInvMatrix;
	};
public:
	PointLightData m_StructuredBufferData;
private:
	SolidSphere* m_SolidSphere;
private:
	ID3D11PixelShader* pPixelShader;
	ID3D11RasterizerState* rasterizerInside;
	ID3D11RasterizerState* rasterizerOutside;
	ID3D11DepthStencilState* pDSStateInfrontBackFaceOfLight;
	ID3D11DepthStencilState* pDSStateLightingBehindFrontFaceOfLight;
	ID3D11DepthStencilState* pDSStateInsideLighting;
};
