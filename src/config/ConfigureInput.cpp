#include "ConfigureInput.hpp"
#include <input/InputBindings.hpp>
#include "../const/InputActionIds.hpp"

void ConfigureInput(World& world)
{
    auto& bindings =
        world.GetResource<InputBindings>();

    /** UI */
    bindings.BindKeyboard(InputActionIds::UiUp, KEY_UP);
    bindings.BindKeyboard(InputActionIds::UiUp, KEY_W);

    bindings.BindKeyboard(InputActionIds::UiDown, KEY_DOWN);
    bindings.BindKeyboard(InputActionIds::UiDown, KEY_S);

    bindings.BindKeyboard(InputActionIds::UiLeft, KEY_LEFT);
    bindings.BindKeyboard(InputActionIds::UiLeft, KEY_A);

    bindings.BindKeyboard(InputActionIds::UiRight, KEY_RIGHT);
    bindings.BindKeyboard(InputActionIds::UiRight, KEY_D);

    bindings.BindKeyboard(InputActionIds::UiAccept, KEY_ENTER);
    bindings.BindKeyboard(InputActionIds::UiAccept, KEY_SPACE);

    bindings.BindKeyboard(InputActionIds::UiCancel, KEY_ESCAPE);

    bindings.BindGamepadButton(InputActionIds::UiUp, GAMEPAD_BUTTON_LEFT_FACE_UP);
    bindings.BindGamepadButton(InputActionIds::UiDown, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    bindings.BindGamepadButton(InputActionIds::UiLeft, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    bindings.BindGamepadButton(InputActionIds::UiRight, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    bindings.BindGamepadButton(InputActionIds::UiAccept, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    bindings.BindGamepadButton(InputActionIds::UiCancel, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);

    /** Game */
    bindings.BindKeyboard(InputActionIds::Throw,  KEY_SPACE);
    bindings.BindGamepadButton(InputActionIds::Throw, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    bindings.BindTouchAnywhere(InputActionIds::Throw);
}
