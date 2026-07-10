#include "CalculateViewport.hpp"
#include <cmath>
#include <algorithm>

void CalculateViewport(DisplayResource& display) {
    float scaleX = display.windowResolution.x / display.internalResolution.x;
    float scaleY = display.windowResolution.y / display.internalResolution.y;

    display.scale = floor(std::min(scaleX, scaleY));

    float width = display.internalResolution.x * display.scale;
    float height = display.internalResolution.y * display.scale;

    display.viewportOffset = {
        (display.windowResolution.x - width) / 2.0f,
        (display.windowResolution.y - height) / 2.0f
    };
}