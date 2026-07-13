#pragma once

#include <raylib.h>

#include <algorithm>
#include <string>
#include <unordered_map>

#include "../const/AudioIds.hpp"

struct MusicPitchTween
{
    bool active = false;

    float from = 1.0f;
    float to = 1.0f;

    float timer = 0.0f;
    float duration = 1.0f;
};

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
            AudioIds::MainSoundTrack,
            std::string(ASSETS_PATH) + "/audio/main_soundtrack.ogg"
        );
        LoadMusicTrack(
            AudioIds::StoreSoundTrack,
            std::string(ASSETS_PATH) + "/audio/store_soundtrack.ogg"
        );

        LoadSfx(AudioIds::Whiff, std::string(ASSETS_PATH) + "/audio/whiff.wav");
        LoadSfx(AudioIds::FirstStrike, std::string(ASSETS_PATH) + "/audio/first_strike.wav");
        LoadSfx(AudioIds::LastStrike, std::string(ASSETS_PATH) + "/audio/last_strike.wav");
        LoadSfx(AudioIds::Homerun, std::string(ASSETS_PATH) + "/audio/homerun.wav");
        LoadSfx(AudioIds::Yard, std::string(ASSETS_PATH) + "/audio/yard.wav");
        LoadSfx(AudioIds::Mult, std::string(ASSETS_PATH) + "/audio/mult.wav");
        LoadSfx(AudioIds::SkillCheckBuildup, std::string(ASSETS_PATH) + "/audio/skill_check_buildup.wav");
        LoadSfx(AudioIds::WallHit, std::string(ASSETS_PATH) + "/audio/wall_hit.wav");
        LoadSfx(AudioIds::Payout, std::string(ASSETS_PATH) + "/audio/payout.wav");
        LoadSfx(AudioIds::Bell, std::string(ASSETS_PATH) + "/audio/bell.wav");
        
        LoadSfx(AudioIds::SkillCheck, std::string(ASSETS_PATH) + "/audio/skill_check.wav");
        LoadSfx(AudioIds::SkillCheckMiss, std::string(ASSETS_PATH) + "/audio/skill_check_miss.wav");
        LoadSfx(AudioIds::SkillCheckGood, std::string(ASSETS_PATH) + "/audio/skill_check_good.wav");
        LoadSfx(AudioIds::SkillCheckGreat, std::string(ASSETS_PATH) + "/audio/skill_check_great.wav");
        LoadSfx(AudioIds::FirstStrikePerfect, std::string(ASSETS_PATH) + "/audio/first_strike_perfect.wav");

        LoadSfx(AudioIds::Reroll, std::string(ASSETS_PATH) + "/audio/reroll.wav");
        LoadSfx(AudioIds::ItemBuy, std::string(ASSETS_PATH) + "/audio/item_buy.wav");
        
        LoadSfx(AudioIds::MainMenuBatStrike, std::string(ASSETS_PATH) + "/audio/main_menu_bat_strike.wav");
        LoadSfx(AudioIds::GlassBreak, std::string(ASSETS_PATH) + "/audio/glass_break.wav");

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

    static Music& GetMusic(const std::string& id)
    {
        auto it = musicTracks.find(id);

        if(it == musicTracks.end())
        {
            throw std::runtime_error("Music not loaded: " + id);
        }

        return it->second;
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

        musicPitches[id] = 1.0f;
        musicPitchTweens[id] = MusicPitchTween{};

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

    static void ResumeMusic(const std::string& id)
    {
        Music& music = GetMusic(id);

        ResumeMusicStream(music);

        currentMusicId = id;
    }

    static void PauseMusic(const std::string& id)
    {
        Music& music = GetMusic(id);

        PauseMusicStream(music);

        if(currentMusicId == id)
        {
            currentMusicId.clear();
        }
    }

    static void StopMusic(const std::string& id)
    {
        Music& music = GetMusic(id);

        StopMusicStream(music);

        if (currentMusicId == id) {
            currentMusicId.clear();
        }
    }

    static void PlayMusic(
        const std::string& id,
        float volume = 1.0f
    )
    {
        Music& music = GetMusic(id);

        musicVolume = volume;

        SetMusicVolume(music, musicVolume);

        if(IsMusicStreamPlaying(music))
        {
            return;
        }

        PlayMusicStream(music);
        currentMusicId = id;
    }

    static void PlaySoundtrack()
    {
        PlayMusic(AudioIds::MainSoundTrack, 0.6f);
    }

    static void Update()
    {
        float dt =
            GetFrameTime();

        for(auto& [id, music] : musicTracks)
        {
            if(IsMusicValid(music))
            {
                UpdateMusicStream(music);
            }
        }

        for(auto& [id, tween] : musicPitchTweens)
        {
            if(!tween.active)
            {
                continue;
            }

            tween.timer += dt;

            float t =
                tween.timer / tween.duration;

            if(t > 1.0f)
            {
                t = 1.0f;
            }

            float eased =
                t * t * (3.0f - 2.0f * t);

            float pitch =
                tween.from + (tween.to - tween.from) * eased;

            SetMusicPitchValue(
                id,
                pitch
            );

            if(t >= 1.0f)
            {
                tween.active = false;
            }
        }
    }

    static void SetMusicVolumeValue(float volume)
    {
        musicVolume =
            std::clamp(volume, 0.0f, 1.0f);

        if(currentMusicId.empty())
        {
            return;
        }

        Music& music =
            GetMusic(currentMusicId);

        SetMusicVolume(
            music,
            musicVolume
        );
    }

    static void StopCurrentMusic()
    {
        if(currentMusicId.empty())
        {
            return;
        }

        StopMusic(currentMusicId);
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

    static void SetMusicPitchValue(
        const std::string& id,
        float pitch
    )
    {
        Music& music =
            GetMusic(id);

        musicPitches[id] = pitch;

        SetMusicPitch(
            music,
            pitch
        );
    }

    static void StartMusicPitchTransition(
        const std::string& id,
        float targetPitch,
        float duration
    )
    {
        Music& music =
            GetMusic(id);

        (void)music;

        float currentPitch = 1.0f;

        auto pitchIt =
            musicPitches.find(id);

        if(pitchIt != musicPitches.end())
        {
            currentPitch = pitchIt->second;
        }

        MusicPitchTween tween{};
        tween.active = true;
        tween.from = currentPitch;
        tween.to = targetPitch;
        tween.timer = 0.0f;
        tween.duration = std::max(0.01f, duration);

        musicPitchTweens[id] = tween;
    }

    static void RestartMusic(
        const std::string& id,
        float volume = 1.0f,
        float pitch = 1.0f
    )
    {
        Music& music =
            GetMusic(id);

        StopMusicStream(music);

        SetMusicVolume(
            music,
            volume
        );

        SetMusicPitch(
            music,
            pitch
        );

        musicPitches[id] = pitch;

        PlayMusicStream(music);

        currentMusicId = id;
    }
private:
    inline static std::unordered_map<std::string, Sound> sounds;
    inline static std::unordered_map<std::string, Music> musicTracks;
    inline static std::unordered_map<std::string, float> musicPitches;
    inline static std::unordered_map<std::string, MusicPitchTween> musicPitchTweens;

    inline static std::string currentMusicId;

    inline static float musicVolume = 3.f;

    inline static bool initialized = false;
    inline static bool ownsAudioDevice = false;
};