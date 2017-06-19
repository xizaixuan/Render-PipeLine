#include "RenderFace.h"

RenderFace::RenderFace()
	: v0(0.0f, 0.0f, 0.0f)
	, v1(0.0f, 0.0f, 0.0f)
	, v2(0.0f, 0.0f, 0.0f)
	, uv0(0.0f, 0.0f)
	, uv1(0.0f, 0.0f)
	, uv2(0.0f, 0.0f)
{
}

RenderFace::RenderFace(const RenderFace& face)
{
	v0 = face.v0;
	v1 = face.v1;
	v2 = face.v2;

	uv0 = face.uv0;
	uv1 = face.uv1;
	uv2 = face.uv2;
}

RenderFace::~RenderFace()
{

}