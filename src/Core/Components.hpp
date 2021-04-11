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

enum MoveState { MS_IDLE, MS_LEFT, MS_RIGHT };

struct MoveComponent
{
	MoveState m_MoveState;
	bool m_Jump;

	MoveComponent(): m_MoveState(MS_IDLE), m_Jump(false) {}
};

struct InputComponent
{
	std::vector<InputListener> m_Listeners;

	InputComponent(std::vector<InputListener> listeners): m_Listeners(listeners) {}
};
