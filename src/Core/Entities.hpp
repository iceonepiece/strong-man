#pragma once

class PlayerEntity
{
public:
	PlayerEntity(Entity entity)
	{
		Fixture bodyFixture { 1.0f, 2.0f, 0.0f, 0.0f, false };
		Fixture footFixture { 1.0f, 3.0f, 0.0f, 0.0f, true };
		std::vector<Fixture> fixtures { bodyFixture, footFixture };
		entity.AddComponent<BoxComponent>(entity.GetScene()->GetPhysics().CreateDynamicBody(1.0f, 10.0f, fixtures));
		entity.AddComponent<MoveComponent>();

		InputListener moveLeft;
		moveLeft.m_KeyCode = SDL_SCANCODE_LEFT;
		moveLeft.m_ButtonState = EHeld;
		moveLeft.m_Command = "MOVE_LEFT";

		InputListener moveRight;
		moveRight.m_KeyCode = SDL_SCANCODE_RIGHT;
		moveRight.m_ButtonState = EHeld;
		moveRight.m_Command = "MOVE_RIGHT";

		InputListener moveJump;
		moveJump.m_KeyCode = SDL_SCANCODE_SPACE;
		moveJump.m_ButtonState = EPressed;
		moveJump.m_Command = "MOVE_JUMP";

		std::vector<InputListener> listeners { moveLeft, moveRight, moveJump };
		entity.AddComponent<InputComponent>(listeners);
	}
};

class TileEntity
{
public:
	TileEntity(Entity entity)
	{
		Fixture tileFixture_1 { 20.0f, 2.0f, 0.0f, 0.0f, false };
		std::vector<Fixture> tileFixtures { tileFixture_1 };
		entity.AddComponent<BoxComponent>(entity.GetScene()->GetPhysics().CreateStaticBody(10.0f, 20.0f, tileFixtures));
	}
};
