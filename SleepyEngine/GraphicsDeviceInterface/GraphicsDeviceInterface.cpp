#include "GraphicsDeviceInterface.h"
#include "../Bindable/Bindables/DepthStencil.h"

GraphicsDeviceInterface::GraphicsDeviceInterface()
{}

void GraphicsDeviceInterface::InitializeGraphics( HWND& hWnd, GraphicsAPI api, u32 width, u32 height )
{
	m_iWidth = width;
	m_iHeight = height;
	m_GraphicsAPI = api;

	if ( api == GraphicsAPI::DirectX )
		m_D3D11Interface.Initialize( hWnd, width, height );
}

void GraphicsDeviceInterface::BindSwapBuffer() noexcept
{
	GetContext()->OMSetRenderTargets( 1u, GetTarget(), nullptr );

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = (float)m_iWidth;
	vp.Height = (float)m_iHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	m_D3D11Interface.GetContext()->RSSetViewports( 1u, &vp );
}

void GraphicsDeviceInterface::BindSwapBuffer( const DepthStencil& ds ) noexcept
{
	GetContext()->OMSetRenderTargets( 1u, GetTarget(), ds.pDepthStencilView );

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = (float)m_iWidth;
	vp.Height = (float)m_iHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	m_D3D11Interface.GetContext()->RSSetViewports( 1u, &vp );
}

void GraphicsDeviceInterface::DrawIndexed( UINT count ) noexcept
{
	m_D3D11Interface.GetContext()->DrawIndexed( count, 0u, 0u );
}

void GraphicsDeviceInterface::SetViewMatrix( DirectX::XMMATRIX viewMatrix ) noexcept
{
	m_ViewMatrix = viewMatrix;
}

void GraphicsDeviceInterface::SetProjMatrix( DirectX::XMMATRIX projMatrix ) noexcept
{
	m_ProjMatrix = projMatrix;
}

DirectX::XMMATRIX GraphicsDeviceInterface::GetViewMatrix() noexcept
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX GraphicsDeviceInterface::GetProjMatrix() noexcept
{
	return m_ProjMatrix;
}

bool GraphicsDeviceInterface::IsInitialized() noexcept
{
	return  m_GraphicsAPI != GraphicsAPI::Uninitialized;
}

IDXGISwapChain* GraphicsDeviceInterface::GetSwap() noexcept
{
	return m_D3D11Interface.GetSwap();
}

ID3D11Device* GraphicsDeviceInterface::GetDevice() noexcept
{
	return m_D3D11Interface.GetDevice();
}

ID3D11DeviceContext* GraphicsDeviceInterface::GetContext() noexcept
{
	return m_D3D11Interface.GetContext();
}

ID3D11RenderTargetView** GraphicsDeviceInterface::GetTarget() noexcept
{
	return m_D3D11Interface.GetTarget();
}

ID3D11DepthStencilView** GraphicsDeviceInterface::GetDSV() noexcept
{
	return m_D3D11Interface.GetDSV();
}

ID3D11RenderTargetView** GraphicsDeviceInterface::GetGBuffers() noexcept
{
	return m_D3D11Interface.GetGBuffers();
}

ID3D11ShaderResourceView** GraphicsDeviceInterface::GetShaderResources() noexcept
{
	return m_D3D11Interface.GetShaderResources();
}

ID3D11ShaderResourceView** GraphicsDeviceInterface::GetDepthResource() noexcept
{
	return  m_D3D11Interface.GetDepthResource();
}

ID3D11ShaderResourceView** GraphicsDeviceInterface::GetShadowResource() noexcept
{
	return m_D3D11Interface.GetShadowResource();
}

ID3D11BlendState* GraphicsDeviceInterface::GetBlendState()
{
	return m_D3D11Interface.GetBlendState();
}

ID3D11DepthStencilView** GraphicsDeviceInterface::GetDSV_ReadOnly() noexcept
{
	return m_D3D11Interface.GetDSV_ReadOnly();
}

ID3D11DepthStencilState* GraphicsDeviceInterface::GetLightDSS() noexcept
{
	return m_D3D11Interface.GetLightDSS();
}

ID3D11DepthStencilState* GraphicsDeviceInterface::GetBufferDSS() noexcept
{
	return m_D3D11Interface.GetGBufferDSS();
}

ID3D11DepthStencilState* GraphicsDeviceInterface::GetBufferDSS2() noexcept
{
	return m_D3D11Interface.GetGBufferDSS2();
}

ID3D11DepthStencilView** GraphicsDeviceInterface::GetShadowDSV() noexcept
{
	return m_D3D11Interface.GetShadowDSV();
}

ID3D11DepthStencilView** GraphicsDeviceInterface::GetShadowDSV2() noexcept
{
	return m_D3D11Interface.GetShadowDSV2();
}

ID3D11ShaderResourceView** GraphicsDeviceInterface::GetShadowResource2() noexcept
{
	return m_D3D11Interface.GetShadowResource2();
}

UINT GraphicsDeviceInterface::GetWidth() const noexcept
{
	return m_iWidth;
}

UINT GraphicsDeviceInterface::GetHeight() const noexcept
{
	return m_iHeight;
}