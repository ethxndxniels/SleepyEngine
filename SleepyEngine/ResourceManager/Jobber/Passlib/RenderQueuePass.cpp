#include "RenderQueuePass.h"


void RenderQueuePass::Accept( Job job ) noexcept
{
	jobs.push_back( job );
}

void RenderQueuePass::Execute( GraphicsDeviceInterface& gfx ) const noexcept
{
	BindAll( gfx );

	for( const auto& j : jobs )
	{
		j.Execute( gfx );
	}
}

void RenderQueuePass::Reset() noexcept
{
	jobs.clear();
}