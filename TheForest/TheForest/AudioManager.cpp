/**************************************************************************************************************
* Audio Manager - Code
*
* The code file for the Audio manager class. Initiates the audio mixer, creates each sound from the array of audio file paths
* and adds them to an array of sounds. 
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "AudioManager.h"

#define print(x){std::cout << (x) << std::endl;}

AudioManager::AudioManager()
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        print("couldnt start audio")
        return;
    }

    for (const auto& soundPath : soundPaths)
    {
        std::stringstream file;
        file << soundPath;
        Mix_Chunk* newSound = Mix_LoadWAV(file.str().c_str());
        sounds.push_back(newSound);
    }

    Mix_Volume(musicChannel, 30);
}

void AudioManager::PlaySound(Esounds sound, bool overlap) const
{
    // Stop the other sounds first if not allowed to overlap
    if(Mix_Playing(sfxChannel) && !overlap) Mix_Pause(sfxChannel);

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
