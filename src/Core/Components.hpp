#pragma once

struct BoxComponent
{
	float Width;
	float Height;
	b2Body* Body;

	BoxComponent(float width, float height, b2Body* body)
		:Width(width)
		,Height(height)
		,Body(body)
	{}
};
