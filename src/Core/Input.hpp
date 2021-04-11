#pragma once

#include <string>
#include <SDL2/SDL.h>

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

struct InputListener
{
	SDL_Scancode m_KeyCode;
	ButtonState m_ButtonState;
	std::string m_Command;
};

class KeyboardState
{
public:
	friend class Input;

	bool GetKeyValue(SDL_Scancode keyCode) const
	{
		return mCurrState[keyCode] == 1;
	}

	ButtonState GetKeyState(SDL_Scancode keyCode) const
	{
		if (mPrevState[keyCode] == 0)
		{
			if (mCurrState[keyCode] == 0)
			{
				return ENone;
			}
			else
			{
				return EPressed;
			}
		}
		else // Prev state must be 1
		{
			if (mCurrState[keyCode] == 0)
			{
				return EReleased;
			}
			else
			{
				return EHeld;
			}
		}
	}

private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

class Input
{
public:
	Input()
	{
		m_KeyboardState.mCurrState = SDL_GetKeyboardState(NULL);
		memset(m_KeyboardState.mPrevState, 0, SDL_NUM_SCANCODES);
	}

	void PrepareForUpdate()
	{
		memcpy(m_KeyboardState.mPrevState, m_KeyboardState.mCurrState, SDL_NUM_SCANCODES);
	}

	void Update() {}
	void ProcessEvent(union SDL_Event& event) {}

	const KeyboardState& GetKeyboardState() const { return m_KeyboardState; }

private:
	KeyboardState m_KeyboardState;
};
