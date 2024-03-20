#include "Panel.h"




//APanel
//--------------------------------------------------------------------------------------------------------------
APanel::APanel(unsigned short x_pos, unsigned short y_pos, unsigned short width, unsigned short height, CHAR_INFO *screen_buffer, unsigned short screen_width)
	: X_Pos(x_pos), Y_Pos(y_pos), Width(width), Height(height), Screen_Buffer(screen_buffer), Screen_Width(screen_width)
{
}
//--------------------------------------------------------------------------------------------------------------
void APanel::Draw()
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