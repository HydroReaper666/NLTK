#include "textbutton.h"

TextButton::TextButton(void) : Button() { }

TextButton::TextButton(Point_t location, Size_t size, u32 bgColor, u32 activatorKeys, u32 textColor, std::string text)
    : Button(location, size, bgColor, activatorKeys), myText(text) {
    
    SetTextColor(textColor);
    SetTextSize(FontScale, FontScale);
    SetTextPos(Location.X + 2, Location.Y + 2);
    Visible = true;
};

TextButton::TextButton(u32 x, u32 y, u32 width, u32 height, u32 bgColor, u32 activatorKeys, u32 textColor, std::string text)
    : TextButton(Point_t{ x, y }, Size_t{ width, height }, bgColor, activatorKeys, textColor, text) { }

TextButton::TextButton(u32 x, u32 y, u32 bgColor, u32 activatorKeys, u32 textColor, std::string text)
    : TextButton(Point_t{ x, y }, Size_t{ 0, 0 }, bgColor, activatorKeys, textColor, text) {

    SetSize(Size_t{ static_cast<u32>(myText.GetWidth()), static_cast<u32>(myText.GetHeight()) });
}

void TextButton::Draw(void) {
    Button::Draw();
    myText.Draw();
}

void TextButton::SetVisibility(bool visibility) {
    Visible = visibility;
}

void TextButton::SetTextSize(float scaleX, float scaleY) {
    myText.SetSize(scaleX, scaleY);
}

void TextButton::SetTextColor(u32 color) {
    myText.SetColor(color);
}

void TextButton::SetTextPos(float posX, float posY) {
    myText.SetPos(posX, posY);
}

void TextButton::CentreText(void) {
    myText.CenterInBounds(Location.X+2, Location.Y+2, Size.Width-4, Size.Height-4);
}