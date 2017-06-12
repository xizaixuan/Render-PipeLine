#include "RenderFace.h"

RenderFace::RenderFace()
	: v0(0.0f, 0.0f, 0.0f)
	, v1(0.0f, 0.0f, 0.0f)
	, v2(0.0f, 0.0f, 0.0f)
{
}

RenderFace::RenderFace(const RenderFace& face)
{
	v0 = face.v0;
	v1 = face.v1;
	v2 = face.v2;
}

RenderFace::~RenderFace()
{

}