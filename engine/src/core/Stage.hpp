#pragma once

enum class Stage
{
    Startup,

    PreUpdate,
    Update,
    PostUpdate,

    BeginScene,
    RenderScene,
    ScenePostProcess,

    BeginUi,
    RenderUi,

    Composite,
    Present,

    Shutdown
};