#include "GraphicsDeviceInterface.h"

GraphicsDeviceInterface::GraphicsDeviceInterface()
{}

void GraphicsDeviceInterface::InitializeGraphics( HWND& hWnd, GraphicsAPI api, u32 width, u32 height )
{
	if ( api == GraphicsAPI::DirectX )
		m_D3D11Interface.Initialize( hWnd, width, height );
}

void GraphicsDeviceInterface::DrawIndexed( UINT count ) noexcept
{
	m_D3D11Interface.GetContext()->DrawIndexed( count, 0u, 0u );
}

bool GraphicsDeviceInterface::IsInitialized() noexcept
{
	if ( m_GraphicsApi == GraphicsAPI::Uninitialized )
		return false;
	return true;
}

ID3D11Device* GraphicsDeviceInterface::GetDevice()
{
	return m_D3D11Interface.GetDevice();
}

ID3D11DeviceContext* GraphicsDeviceInterface::GetContext()
{
	return m_D3D11Interface.GetContext();
}
