#include <vector>
#include "Font.hpp"
#include <iostream>

Font::Font()
{
	std::cout << "Font constructor" << std::endl;
}

Font::~Font()
{
	std::cout << "Font destructor" << std::endl;
}

bool Font::Load(const std::string& fileName)
{
	std::vector<int> fontSizes = { 16, 18, 24, 36, 48, 64, 72 };

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);

		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		m_FontData.emplace(size, font);
	}

	return true;
}

void Font::Unload()
{
	std::cout << "Font::Unload(): " << m_FontData.size() << std::endl;
	for (auto& font : m_FontData)
	{
		TTF_CloseFont(font.second);
	}
}

void Font::RenderText(
	SDL_Renderer* renderer,
	const std::string& text,
	const b2Vec2& position,
	const b2Vec3& color,
	unsigned int size
)
{
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x);
	sdlColor.g = static_cast<Uint8>(color.y);
	sdlColor.b = static_cast<Uint8>(color.z);
	sdlColor.a = 255;

	auto iter = m_FontData.find(size);
	if (iter != m_FontData.end())
	{
		TTF_Font* font = iter->second;

		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
		if (textSurface != nullptr)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_Rect renderQuad = {
				static_cast<int>(position.x),
				static_cast<int>(position.y),
				textSurface->w,
				textSurface->h
			};
	    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	    SDL_FreeSurface(textSurface);
		}

	}
	else
	{
		SDL_Log("Font size %d is unsupported", size);
	}
}
