#include "SolidSphere.h"
#include "../Bindable/BindableCommon.h"
#include "../Bindable/Bindables/Blender.h"
#include "../Renderer/Model/Vertex.h"
#include "../Geometry/Sphere.h"
#include "../Bindable/Bindables/ConstantBuffers.h"
#include "../Bindable/Bindables/DynamicConstant.h"
#include "../Bindable/Bindables/ConstantBuffersEx.h"
#include "../Renderer/Jobber/TechniqueProbe.h"
#include "../Renderer/Channels.h"

SolidSphere::SolidSphere( Graphics& gdi, float radius )
{
	using namespace Bind;
	namespace dx = DirectX;

	auto model = Sphere::Make();
	model.Transform( dx::XMMatrixScaling( radius, radius, radius ) );
	const auto geometryTag = "$sphere." + std::to_string( radius );

	pVertices = VertexBuffer::Resolve( gdi, geometryTag, model.m_VBVertices );
	pIndices = IndexBuffer::Resolve( gdi, geometryTag, model.m_vecOfIndices );
	pTopology = Topology::Resolve( gdi, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	{
		Technique solid{ Chan::main };
		Step only( "lambertian" );

		auto pvs = VertexShader::Resolve( gdi, "./Shaders/Bin/Solid_VS.cso" );
		only.AddBindable( InputLayout::Resolve( gdi,model.m_VBVertices.GetLayout(),*pvs ) );
		only.AddBindable( std::move( pvs ) );

		only.AddBindable( PixelShader::Resolve( gdi, "./Shaders/Bin/Solid_PS.cso" ) );

		struct PSColorConstant
		{
			dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
			float padding;
		} colorConst;
		only.AddBindable( PixelConstantBuffer<PSColorConstant>::Resolve( gdi, colorConst, 8u ) );

		only.AddBindable( std::make_shared<TransformCbuf>( gdi ) );

		only.AddBindable( Rasterizer::Resolve( gdi, false ) );

		solid.AddStep( std::move( only ) );
		AddTechnique( std::move( solid ) );
	}
}

void SolidSphere::SetPos( DirectX::XMFLOAT3 pos ) noexcept
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixTranslation( pos.x, pos.y, pos.z );
}