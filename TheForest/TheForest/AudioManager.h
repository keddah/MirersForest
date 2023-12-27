/**************************************************************************************************************
* Audio Manager - Header
*
* The header file for the Audio manager class. Responsible for providing the file paths for each audio file that it can play.
* Also declares an enum of the different sounds
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once

#include <iostream>
#include <SDL_mixer.h>
#include <sstream>
#include <vector>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    enum class Esounds
    {
        Jump,
        Flowerup,
        SeedShoot,
        SeedExplosion,
        PetalShoot,
        SunShoot,
        SunBeam,
        NoAmmo,
        SlimeDeath,
        PlayerHit,
        ProjImpact,
        BeamStrike
    };
    
    // Overlap = can play over other sounds
    void PlaySound(Esounds sound, bool overlap = true) const;

    // Loops the song with the while loop
    void PlayMusic() const { while(!Mix_Playing(musicChannel)) Mix_PlayChannel(musicChannel, sounds[soundsLength - 1], -1); }

private:
    Mix_Music* soundPlayer;
    std::vector<Mix_Chunk*> sounds;

    static constexpr int soundsLength = 13;
    
    // The order of the array affects the selection of the sound
    const std::string soundPaths[soundsLength]
    {
        "Audio/jump.wav",
        "Audio/flowerup.wav",
        "Audio/seedShoot.wav",
        "Audio/seedExplosion.wav",
        "Audio/petalShoot.wav",
        "Audio/sunShoot.wav",
        "Audio/sunBeam.wav",
        "Audio/noAmmo.wav",
        "Audio/slimeDeath.wav",
        "Audio/playerHit.wav",
        "Audio/projImpact.wav",
        "Audio/beamStrike.wav",
        "Audio/R3DB0N3.wav"
    };

    const short sfxChannel = 1;
    const short musicChannel = 2;
};
