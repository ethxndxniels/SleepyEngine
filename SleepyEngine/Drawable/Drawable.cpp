#include "Drawable.h"
#include "../Bindable/BindableCommon.h"
#include <cassert>

using namespace Bind;

//void Drawable::Draw( GraphicsDeviceInterface& gdi ) const noexcept
//{
//	// bindables
//	for ( auto& b : binds )
//	{
//		b->Bind( gdi );
//	}
//
//	// draw
//	gdi.DrawIndexed( pIndexBuffer->GetCount() );
//}

void Drawable::Submit( FrameCommander& frame ) const noexcept
{
	for ( const auto& tech : techniques )
	{
		tech.Submit( frame, *this );
	}
}

void Drawable::AddTechnique( Technique tech_in ) noexcept
{
	tech_in.InitializeParentReferences( *this );
	techniques.push_back( std::move( tech_in ) );
}

void Drawable::Bind( GraphicsDeviceInterface& gfx ) const noexcept
{
	pTopology->Bind( gfx );
	pIndices->Bind( gfx );
	pVertices->Bind( gfx );
}

void Drawable::Accept( TechniqueProbe& probe )
{
	for ( auto& t : techniques )
	{
		t.Accept( probe );
	}
}

UINT Drawable::GetIndexCount() const noexcept
{
	return pIndices->GetCount();
}

Drawable::~Drawable()
{}

//void Drawable::DrawDepth( GraphicsDeviceInterface& gdi ) const noexcept
//{
//	// bindables
//	for ( auto& b : binds )
//	{
//		b->Bind( gdi );
//	}
//
//	gdi.GetContext()->PSSetShader( nullptr, nullptr, 0u );
//
//	// draw
//	gdi.DrawIndexed( pIndexBuffer->GetCount() );
//}

//void Drawable::AddBind( std::shared_ptr<Bind::Bindable> bind ) noexcept
//{
//	if ( typeid( *bind ) == typeid( IndexBuffer ) )
//	{
//		assert( "Binding multiple index buffers not allowed" && pIndexBuffer == nullptr );
//		pIndexBuffer = &static_cast<IndexBuffer&>( *bind );
//	}
//	binds.push_back( std::move( bind ) );
//}
