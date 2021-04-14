#pragma once

struct BoxComponent
{
	b2Body* Body;

	BoxComponent(b2Body* body): Body(body) {}
};

enum MoveState { MS_IDLE, MS_LEFT, MS_RIGHT };

struct MoveComponent
{
	MoveState m_MoveState;
	bool m_Jump;
	int m_NumGrounds;

	MoveComponent(): m_MoveState(MS_IDLE), m_Jump(false), m_NumGrounds(0) {}
};

struct InputComponent
{
	std::vector<InputListener> m_Listeners;

	InputComponent(std::vector<InputListener> listeners): m_Listeners(listeners) {}
};
