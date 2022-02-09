#pragma once
#include "../Bindable.h"

namespace Bind
{
	class Sampler : public Bindable
	{
	public:
		enum class Type
		{
			Anisotropic,
			Bilinear,
			Point,
		};
	public:
		Sampler( GraphicsDeviceInterface& gdi, Type type, bool reflect );
		void Bind( GraphicsDeviceInterface& gdi ) noexcept override;
		static std::shared_ptr<Sampler> Resolve( GraphicsDeviceInterface& gdi, Type type = Type::Anisotropic, bool reflect = false );
		static std::string GenerateUID( Type type, bool reflect );
		std::string GetUID() const noexcept override;
	protected:
		ID3D11SamplerState* pSampler;
		Type type;
		bool reflect;
	};
}
