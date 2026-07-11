#pragma once

#include <raylib.h>

#include <algorithm>
#include <string>
#include <unordered_map>

#include "../const/AudioIds.hpp"

class AudioHelper
{
public:
    static void InitializeAudioHelper()
    {
        if(initialized)
        {
            return;
        }

        Init();

        LoadMusicTrack(
            AudioIds::SoundTrack_01,
            std::string(ASSETS_PATH) + "/audio/soundtrack_01.ogg"
        );

        
        LoadSfx(AudioIds::MenuMove, "assets/audio/menu_move.wav");
        LoadSfx(AudioIds::MenuSelect, "assets/audio/menu_select.wav");
        LoadSfx(AudioIds::Whiff, std::string(ASSETS_PATH) + "/audio/whiff.wav");
        LoadSfx(AudioIds::FirstStrike, std::string(ASSETS_PATH) + "/audio/first_strike.wav");
        LoadSfx(AudioIds::LastStrike, std::string(ASSETS_PATH) + "/audio/last_strike.wav");
        LoadSfx(AudioIds::Homerun, std::string(ASSETS_PATH) + "/audio/homerun.wav");
        LoadSfx(AudioIds::SkillCheck, std::string(ASSETS_PATH) + "/audio/skill_check.wav");
        LoadSfx(AudioIds::SkillCheckBuildUp, std::string(ASSETS_PATH) + "/audio/skill_check_build_up.wav");
        LoadSfx(AudioIds::Yard, std::string(ASSETS_PATH) + "/audio/yard.wav");
        LoadSfx(AudioIds::Mult, std::string(ASSETS_PATH) + "/audio/mult.wav");
        LoadSfx(AudioIds::WallHit, std::string(ASSETS_PATH) + "/audio/wall_hit.wav");

        initialized = true;
    }

    static void Init()
    {
        if(IsAudioDeviceReady())
        {
            return;
        }

        InitAudioDevice();
        ownsAudioDevice = true;
    }

    static bool LoadSfx(
        const std::string& id,
        const std::string& path
    )
    {
        if(!IsAudioDeviceReady())
        {
            Init();
        }

        if(sounds.find(id) != sounds.end())
        {
            return true;
        }

        Sound sound =
            LoadSound(path.c_str());

        if(!IsSoundValid(sound))
        {
            TraceLog(
                LOG_WARNING,
                "AUDIO: Failed to load sound '%s' from path '%s'",
                id.c_str(),
                path.c_str()
            );

            return false;
        }

        sounds.emplace(id, sound);

        return true;
    }

    static bool LoadMusicTrack(
        const std::string& id,
        const std::string& path
    )
    {
        if(!IsAudioDeviceReady())
        {
            Init();
        }

        if(musicTracks.find(id) != musicTracks.end())
        {
            return true;
        }

        Music music =
            LoadMusicStream(path.c_str());

        if(!IsMusicValid(music))
        {
            TraceLog(
                LOG_WARNING,
                "AUDIO: Failed to load music '%s' from path '%s'",
                id.c_str(),
                path.c_str()
            );

            return false;
        }

        music.looping = true;

        musicTracks.emplace(id, music);

        return true;
    }

    static void PlaySfx(
        const std::string& id,
        float volume = 1.0f,
        float pitch = 1.0f
    )
    {
        auto it =
            sounds.find(id);

        if(it == sounds.end())
        {
            TraceLog(
                LOG_WARNING,
                "AUDIO: Tried to play missing SFX '%s'",
                id.c_str()
            );

            return;
        }

        // volume =
        //     std::clamp(volume, 0.0f, 1.0f);

        SetSoundVolume(it->second, volume);
        SetSoundPitch(it->second, pitch);

        PlaySound(it->second);
    }

    static void PlayMusic(
        const std::string& id,
        float volume = 1.0f
    )
    {
        auto it =
            musicTracks.find(id);

        if(it == musicTracks.end())
        {
            TraceLog(
                LOG_WARNING,
                "AUDIO: Tried to play missing music '%s'",
                id.c_str()
            );

            return;
        }

        // if(volume >= 0.0f)
        // {
        //     musicVolume =
        //         std::clamp(volume, 0.0f, 3.0f);
        // }

        musicVolume = volume;

        Music& music =
            it->second;

        if(currentMusicId == id)
        {
            SetMusicVolume(music, musicVolume);

            if(!IsMusicStreamPlaying(music))
            {
                PlayMusicStream(music);
            }

            return;
        }

        StopCurrentMusic();

        currentMusicId = id;

        SetMusicVolume(music, musicVolume);
        PlayMusicStream(music);
    }

    static void PlaySoundtrack()
    {
        PlayMusic(AudioIds::SoundTrack_01, musicVolume);
    }

    static void Update()
    {
        if(currentMusicId.empty())
        {
            return;
        }

        auto it =
            musicTracks.find(currentMusicId);

        if(it == musicTracks.end())
        {
            return;
        }

        UpdateMusicStream(it->second);
    }

    static void SetMusicVolumeValue(float volume)
    {
        musicVolume =
            std::clamp(volume, 0.0f, 1.0f);

        if(currentMusicId.empty())
        {
            return;
        }

        auto it =
            musicTracks.find(currentMusicId);

        if(it == musicTracks.end())
        {
            return;
        }

        SetMusicVolume(it->second, musicVolume);
    }

    static void StopCurrentMusic()
    {
        if(currentMusicId.empty())
        {
            return;
        }

        auto it =
            musicTracks.find(currentMusicId);

        if(it != musicTracks.end())
        {
            StopMusicStream(it->second);
        }

        currentMusicId.clear();
    }

    static void Shutdown()
    {
        StopCurrentMusic();

        for(auto& [id, sound] : sounds)
        {
            if(IsSoundValid(sound))
            {
                UnloadSound(sound);
            }
        }

        for(auto& [id, music] : musicTracks)
        {
            if(IsMusicValid(music))
            {
                UnloadMusicStream(music);
            }
        }

        sounds.clear();
        musicTracks.clear();

        initialized = false;

        if(ownsAudioDevice && IsAudioDeviceReady())
        {
            CloseAudioDevice();
        }

        ownsAudioDevice = false;
    }

private:
    inline static std::unordered_map<std::string, Sound> sounds;
    inline static std::unordered_map<std::string, Music> musicTracks;

    inline static std::string currentMusicId;

    inline static float musicVolume = 3.f;

    inline static bool initialized = false;
    inline static bool ownsAudioDevice = false;
};