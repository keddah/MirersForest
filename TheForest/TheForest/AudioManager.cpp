#include "AudioManager.h"

AudioManager::AudioManager()
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        print("couldnt start audio")
        return;
    }
}

AudioManager::~AudioManager()
{
    for (const auto& sfx : sounds) Mix_FreeChunk(sfx);

    Mix_FreeMusic(soundPlayer);
}
