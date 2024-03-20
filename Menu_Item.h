#pragma once
#include "Panel.h"

//--------------------------------------------------------------------------------------------------------------
class AMenu_Item
{
public:
	AMenu_Item(unsigned short x_pos, unsigned short y_pos, unsigned short len, const wchar_t *key, const wchar_t *name);

	void Draw(CHAR_INFO *screen_buffer, unsigned short screen_width);

	unsigned short X_Pos;
	unsigned short Y_Pos;
	unsigned short Len;
	const wchar_t *Key;
	const wchar_t *Name;


};
//--------------------------------------------------------------------------------------------------------------
