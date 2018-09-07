#include "RenderContext.h"

RenderContext::RenderContext()
	: CameraPosition(0.0f, 0.0f, 0.0f)
{
	ViewMatrix.Identity();
	ProjMatrix.Identity();
}