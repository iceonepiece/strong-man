#pragma once

const int PLAYER_MOVE_SPEED = 10;
const int PLAYER_JUMP_FORCE = 36;

void MoveSystem(MoveComponent& moveComp, BoxComponent& boxComp, float deltaTime)
{
	b2Body* body = boxComp.Body;
	if (body)
	{
		b2Vec2 velocity = body->GetLinearVelocity();
		float desiredVelocity = 0;

		switch (moveComp.m_MoveState)
		{
			case MS_LEFT:  desiredVelocity = -PLAYER_MOVE_SPEED; break;
			case MS_IDLE:  desiredVelocity =  0; break;
			case MS_RIGHT: desiredVelocity =  PLAYER_MOVE_SPEED; break;
		}

		float velocityChange = desiredVelocity - velocity.x;
		float force = body->GetMass() * velocityChange / deltaTime;

		body->SetLinearVelocity(b2Vec2(desiredVelocity, velocity.y));

		if (moveComp.m_Jump)
		{
			body->ApplyLinearImpulse(
				b2Vec2(0, -PLAYER_JUMP_FORCE),
				body->GetWorldCenter(),
				true
			);
		}
	}
}
