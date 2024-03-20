#pragma once
#include <stdio.h>
#include "Panel.h"


//--------------------------------------------------------------------------------------------------------------
class AsCommander
{
public:
	~AsCommander();

	bool Init();
	bool Draw();

private:
	void Add_Next_Menu_Item(int &index, int &x_pos, int x_step, const wchar_t *key, const wchar_t *name);
	void Build_Menu();

	HANDLE Std_Handle = 0, Screen_Buffer_Handle = 0;
	CHAR_INFO *Screen_Buffer = 0;
	CONSOLE_SCREEN_BUFFER_INFO Screen_Buffer_Info{};


	APanel *Left_Panel = 0;
	APanel *Right_Panel = 0;

	AMenu_Item *Menu_Items[10]{};
};
//--------------------------------------------------------------------------------------------------------------