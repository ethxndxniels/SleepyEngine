#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>

namespace Bind
{
	class TransformCbuf : public Bindable
	{
	protected:
		struct Transforms
		{
			DirectX::XMMATRIX m_ModelMatrix;
			DirectX::XMMATRIX m_ModelViewMatrix;
			DirectX::XMMATRIX m_ModelViewProjMatrix;
		};
	public:
		TransformCbuf( GraphicsDeviceInterface& gdi, const Drawable& parent, UINT slot = 0u );
		void Bind( GraphicsDeviceInterface& gdi ) noexcept override;
	protected:
		void UpdateBindImpl( GraphicsDeviceInterface& gdi, const Transforms& tf ) noexcept;
		Transforms GetTransforms( GraphicsDeviceInterface& gdi ) noexcept;
	private:
		static std::unique_ptr<VertexConstantBuffer<Transforms>> m_pVcbuf;
		const Drawable& m_DrawableParent;
	};
}
