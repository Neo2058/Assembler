#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "Asm_Tools_Interface.h"
#include "Menu_Item.h"

//--------------------------------------------------------------------------------------------------------------
class AFile_Discriptor
{
public:
	AFile_Discriptor(unsigned int attributes, unsigned int file_size_low, unsigned int file_size_hight, wchar_t *file_name);

	unsigned int Attributes;
	unsigned long long File_Size;
	std::wstring File_Name;
};
//--------------------------------------------------------------------------------------------------------------
class APanel
{
public:
	APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO *screen_buffer, unsigned short screen_width);

	void Draw();
	void Get_Directory_Files(const std::wstring& curr_dir);
	void Move_Highlight(bool move_up);
	void On_Enter();


private:
	void Draw_Panels();
	void Draw_Files();
	void Draw_One_File(AFile_Discriptor* file_discriptor, int x_offset, int y_offset, unsigned short background_attribute);
	void Draw_Highlight();

	unsigned short X_Pos, Y_Pos;
	unsigned short Width, Height;
	unsigned short Screen_Width;
	CHAR_INFO *Screen_Buffer;

	int Curr_File_Index;
	int  Highlight_X_Offset, Highlight_Y_Offset;
	std::wstring Current_Directory;

	std::vector<AFile_Discriptor *> Files;
};
//--------------------------------------------------------------------------------------------------------------