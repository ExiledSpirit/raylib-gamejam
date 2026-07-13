#pragma once

enum class MusicTrack
{
    None,
    Menu,
    Gameplay,
    Shop
};

struct MusicStateResource
{
    MusicTrack current = MusicTrack::None;
};
