#include "Sampler.h"
#include "../BindableCodex.h"

namespace Bind
{
	Sampler::Sampler( Graphics& gdi, Type type, bool reflect, UINT slot )
		:
		type( type ),
		reflect( reflect ),
		slot( slot ) 
	{
		D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC{ CD3D11_DEFAULT{} };
		samplerDesc.Filter = [type]() {
			switch ( type )
			{
			case Type::Anisotropic: return D3D11_FILTER_ANISOTROPIC;
			case Type::Point: return D3D11_FILTER_MIN_MAG_MIP_POINT;
			default:
			case Type::Bilinear: return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			}
		}( );
		samplerDesc.AddressU = reflect ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = reflect ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
		GetDevice( gdi )->CreateSamplerState( &samplerDesc, &pSampler );
	}
	void Sampler::Bind( Graphics& gdi ) noexcept
	{
		GetContext( gdi )->PSSetSamplers( slot, 1, &pSampler );
	}
	std::shared_ptr<Sampler> Sampler::Resolve( Graphics& gdi, Type type, bool reflect, UINT slot )
	{
		return Codex::Resolve<Sampler>( gdi, type, reflect, slot );
	}
	std::string Sampler::GenerateUID( Type type, bool reflect, UINT slot )
	{

		using namespace std::string_literals;
		return typeid( Sampler ).name() + "#"s + std::to_string( (int)type ) + ( reflect ? "R"s : "W"s ) + "@"s + std::to_string( slot );
	}
	std::string Sampler::GetUID() const noexcept
	{
		return GenerateUID( type, reflect, slot );
	}
}
