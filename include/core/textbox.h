#pragma once

#include "control.h"
#include "keyboard.h"
#include "CTRFont.hpp"

class TextBox : public Control {
public:
    TextBox(void);
    TextBox(Point_t location, Size_t size, std::string text, std::string hint, u32 maxLength, KeyboardInType inType, u32 bgColor, u32 textColor);
    TextBox(u32 x, u32 y, u32 width, u32 height, std::string text, std::string hint, u32 maxLength, KeyboardInType inType, u32 bgColor, u32 textColor);

    void Draw();
    bool CheckActivate(u32 x, u32 y);
    std::string Activate();

    void SetVisibility(bool visibility);
    void SetTextSize(float scaleX, float scaleY);
    void SetTextColor(u32 color);
    void SetTextPos(float posX, float posY);

    Text myText;
    std::string Hint;
    u32 MaxLength = 0;
    KeyboardInType InputType = KeyboardInType::None;

    float FontScale = 0.5f;
};