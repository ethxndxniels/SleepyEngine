#pragma once
#include "../GraphicsDeviceInterface/GraphicsDeviceInterface.h"
#include "Camera.h"
#include "../Utilities/SleepyMath.h"
#include "../ResourceManager/Mesh.h"
#include "../Drawable/DirectionalLight.h"
#include "../Drawable/PointLight.h"
#include "./RenderTechnique.h"


class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager();
public:
	void Initialize( GraphicsDeviceInterface& gdi, GraphicsAPI api );
	bool IsInitialzed() noexcept;
	void SetRenderTechnique( RenderTechnique renderTechnique ) noexcept;
public:
	void Draw();
	void Present();
	void RotateCamera( const f32 dx, const f32 dy );
	void TranslateCamera( DirectX::XMFLOAT3 camDelta );
public:
	void TranslatePointLight( DirectX::XMFLOAT3 translation );
	void RotatePointLight( const f32 dx, const f32 dy );
	void TranslateDirectionalLight( DirectX::XMFLOAT3 translation );
	void RotateDirectionalLight( const f32 dx, const f32 dy );
private:
	void ForwardRender();
	void DeferredRender();
private:
	GraphicsAPI m_GraphicsAPI = GraphicsAPI::Uninitialized;
	GraphicsDeviceInterface* m_pGDI = nullptr;
	Camera m_Camera = { L"Character Camera", MatrixType::Perspective, ViewSpace( 1.0f, 9.0f / 16.0f, 0.5f, 400.0f ), DirectX::XMFLOAT3{ -13.5f, 5.0f, 3.5f }, 0.0f, PI / 2.0f };
	RenderTechnique m_RenderTechnique = RenderTechnique::Uninitialized;
private:
	// stucture buffers for lights - list of lights
	DirectionalLight* m_pForwardDirectionalLight;
	DirectionalLight* m_pDeferredDirectionalLight;
	PointLight* m_pForwardPointLight;
	PointLight* m_pDeferredPointLight;
	std::vector<Model*> m_vecOfModels;
	// TODO: 
	// - Consolidate into one Directional and one Point Light
	//		- Or seperate into ForwardDirectionalLight and DeferredDirectionalLight classes?
	// - Resource Manager?
	// - Stop load two whole games worth of resources to be able to have both deferred and forward?
};