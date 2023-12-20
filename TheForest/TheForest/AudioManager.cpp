#include "AudioManager.h"

#define print(x){std::cout << (x) << std::endl;}

AudioManager::AudioManager()
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        print("couldnt start audio")
        return;
    }

    for(int i = 0; i < soundsLength; i++)
    {
        std::stringstream file;
        file << soundPaths[i];
        Mix_Chunk* newSound = Mix_LoadWAV(file.str().c_str());
        sounds.push_back(newSound);
    }

    Mix_Volume(musicChannel, 30);
}

AudioManager::~AudioManager()
{
    for (const auto& sfx : sounds) Mix_FreeChunk(sfx);

    Mix_FreeMusic(soundPlayer);
}

void AudioManager::PlaySound(Esounds sound, bool overlap) const
{
    if(Mix_Playing(-1) && !overlap) return;

    short index;
    
    switch (sound)
    {
        case Esounds::Jump:
            index = 0;
            break;
        
        case Esounds::Flowerup:
            index = 1;
            break;

        case Esounds::SeedShoot:
            index = 2;
            break;

        case Esounds::SeedExplosion:
            index = 3;
            break;

        case Esounds::PetalShoot:
            index = 4;
            break;

        case Esounds::SunShoot:
            index = 5;
            break;

        case Esounds::SunBeam:
            index = 6;
            break;

        case Esounds::NoAmmo:
            index = 7;
            break;

        case Esounds::SlimeDeath:
            index = 8;
            break;

        case Esounds::PlayerHit:
            index = 9;
            break;

        case Esounds::ProjImpact:
            index = 10;
            break;

        case Esounds::BeamStrike:
            index = 11;
            break;
    }

    Mix_PlayChannel(sfxChannel, sounds[index], 0);
}
