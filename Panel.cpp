#include "Panel.h"

//AFile_Discriptor
//--------------------------------------------------------------------------------------------------------------
AFile_Discriptor::AFile_Discriptor(unsigned int attributes, unsigned int file_size_low, unsigned int file_size_hight, wchar_t * file_name)
	: Attributes(attributes), File_Name(file_name)
{
	File_Size = (unsigned long long)file_size_low | ((unsigned long long)file_size_hight << 32);
}
//--------------------------------------------------------------------------------------------------------------




//APanel
//--------------------------------------------------------------------------------------------------------------
APanel::APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO *screen_buffer, unsigned short screen_width)
	: X_Pos(x_pos), Y_Pos(y_pos), Width(width), Height(height), Screen_Buffer(screen_buffer), Screen_Width(screen_width)
{
}
//--------------------------------------------------------------------------------------------------------------
void APanel::Draw()
{
	Draw_Panels();
	Draw_Files();
}
//--------------------------------------------------------------------------------------------------------------
void APanel::Get_Directory_Files()
{
	HANDLE search_handle;
	WIN32_FIND_DATAW find_data{};

	search_handle = FindFirstFile(L"*.*", &find_data);

	while (FindNextFileW(search_handle, &find_data))
	{
		AFile_Discriptor *file_descriptor = new AFile_Discriptor(find_data.dwFileAttributes, find_data.nFileSizeLow, find_data.nFileSizeHigh, find_data.cFileName);
		Files.push_back(file_descriptor);
	}
}
//--------------------------------------------------------------------------------------------------------------
void APanel::Draw_Panels()
{
	ASymbol symbol(L' ', 0x1b, L' ', L' ');
	SArea_Pos area_pos(X_Pos + 1,Y_Pos + 1, Screen_Width, Width - 2, Height - 2);
	Clear_Area(Screen_Buffer, area_pos, symbol);

	{
		ASymbol symbol(L'═', 0x1b, L'╔', L'╗');
		SPos pos(X_Pos, Y_Pos, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, pos, symbol);
	}


	//Down line
	{
		ASymbol symbol(L'═', 0x1b, L'╚', L'╝');
		SPos pos(X_Pos, Y_Pos + Height - 1, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, pos, symbol);
	}

	//Vertical Line
	//Left line
	{
		ASymbol symbol(L'║', 0x1b, L'║', L'║');
		SPos pos(X_Pos, Y_Pos + 1, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, pos, symbol);
	}

	//Right line
	{
		ASymbol symbol(L'║', 0x1b, L'║', L'║');
		SPos pos(X_Pos + Width - 1, Y_Pos + 1, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, pos, symbol);
	}

	//Midle horizontal line
	{
		ASymbol symbol(L'─', 0x1b, L'╟', L'╢');
		SPos pos(X_Pos, Y_Pos + Height - 3, Screen_Width, Width - 2);
		Draw_Line_Horizontal(Screen_Buffer, pos, symbol);
	}

	//Middle vertical line
	{
		ASymbol symbol(L'║', 0x1b, L'╦', L'╨');
		SPos pos(X_Pos + Width / 2, Y_Pos, Screen_Width, Height - 4);
		Draw_Line_Vertical(Screen_Buffer, pos, symbol);                                                                                                                                                                                                                                                   
	}

	//Show_Colors(Screen_Buffer, pos, symbol);
}
//--------------------------------------------------------------------------------------------------------------
void APanel::Draw_Files()
{
	unsigned short attributes;
	int x_offset = 0;
	int y_offset = 0;

	for (auto *file : Files)
	{
		if (file->Attributes & FILE_ATTRIBUTE_DIRECTORY)
			attributes = 0x1f;
		else
			attributes = 0x1b;

		SText_Pos pos(X_Pos + x_offset + 1, Y_Pos + y_offset + 2, Screen_Width, attributes);
		Draw_Text(Screen_Buffer, pos, file->File_Name.c_str() );
		++y_offset;

		if (y_offset >= Height - 5)
		{
			if (x_offset == 0)
			{
				x_offset += Width / 2;
				y_offset = 0;
			}
			else
				break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------