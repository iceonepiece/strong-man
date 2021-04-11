#pragma once

void MoveSystem(MoveComponent& moveComp, BoxComponent& boxComp, float deltaTime)
{
	b2Body* body = boxComp.Body;
	if (body)
	{
		b2Vec2 velocity = body->GetLinearVelocity();
		float desiredVelocity = 0;

		switch (moveComp.m_MoveState)
		{
			case MS_LEFT:  desiredVelocity = -16; break;
			case MS_IDLE:  desiredVelocity =  0; break;
			case MS_RIGHT: desiredVelocity =  16; break;
		}

		float velocityChange = desiredVelocity - velocity.x;
		float force = body->GetMass() * velocityChange / deltaTime;

		body->SetLinearVelocity(b2Vec2(desiredVelocity, velocity.y));

		if (moveComp.m_Jump)
		{
			body->ApplyLinearImpulse(
				b2Vec2(0, -150),
				body->GetWorldCenter(),
				true
			);
		}
	}
}
