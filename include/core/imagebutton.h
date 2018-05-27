#pragma once

#include "button.h"

class ImageButton : public Button {
public:
	ImageButton(void);
	ImageButton(Point_t location, Size_t size, u32 bgColor, u32 activatorKeys, u32 imageId);
	ImageButton(u32 x, u32 y, u32 width, u32 height, u32 bgColor, u32 activatorKeys, u32 imageId);

	void Draw(void);
	void SetImageId(u32 id);
	u32 GetImageId(void);

	float Scale = 1;
	u32 ActiveColor;

protected:
	u32 m_imageId = 0;
};