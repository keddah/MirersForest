#pragma once

#include <SDL_mixer.h>
#include <sstream>
#include <vector>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

private:
    Mix_Music* soundPlayer;
    std::vector<Mix_Chunk*> sounds;
};
