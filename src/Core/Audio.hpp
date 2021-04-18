#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>

class Audio
{
public:
  bool Initialize()
  {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
      SDL_Log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
      return false;
    }

    m_Chunks.emplace("notification", Mix_LoadWAV( "src/Assets/notification.wav"));

    Mix_Music* levelMusic = Mix_LoadMUS("src/Assets/sea.wav");
    if (levelMusic)
    {
      m_Musics.emplace("level", levelMusic);
    }

    return true;
  }

  void Shutdown()
  {
    for (auto chunk : m_Chunks)
    {
      Mix_FreeChunk(chunk.second);
    }
    m_Chunks.clear();

    for (auto music : m_Musics)
    {
      Mix_FreeMusic(music.second);
    }
    m_Musics.clear();

    Mix_Quit();
  }

  void PlaySound(std::string name)
  {
    auto iter = m_Chunks.find(name);
    if (iter != m_Chunks.end())
    {
      Mix_PlayChannel(-1, iter->second, 0);
    }
  }

  void PlayMusic(std::string name)
  {
    auto iter = m_Musics.find(name);
    if (iter != m_Musics.end())
    {
      std::cout << "PlayMusic: " << name << std::endl;

      if (Mix_PlayMusic(iter->second, -1) == -1)
      {
        std::cout << "PlayMusic Failed" << std::endl;
      }
    }
  }

private:
  std::unordered_map<std::string, Mix_Chunk*> m_Chunks;
  std::unordered_map<std::string, Mix_Music*> m_Musics;
};
