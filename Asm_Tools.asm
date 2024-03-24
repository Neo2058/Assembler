.code
;--------------------------------------------------------------------------------------------------------------
Make_Sum proc

; int Make_Sum(int one_value, int another_value)
; RCX первый параметр будет передан через этот регистр 8 byte!!!
; RDX второй параметр будет передаваться через этот регистр 8 byte?
; R8 третий параметр будет передаваться через этот регистр
; R9 четвертый параметр будет передаваться через этот регистр
; Остальные параметры передаются через стек
; Возврат находится в регистре RAX

	mov eax, ecx
	add eax, edx

	ret

Make_Sum endp
;--------------------------------------------------------------------------------------------------------------
Get_Pos_Addres proc
;RCX - screen_buffer
;RDX - pos
;Возврат: RDI

	mov rax, rdx
	shr rax, 16			;shr - Shift Right команда выполняет логический сдвиг вправо. AX = pos.Y_Pos
	movzx rax, ax		; RAX = AX = pos.Y_Pos

	mov rbx, rdx
	shr rbx, 32			; BX = pos.Screen_Width
	movzx rbx, bx		; RBX = BX = pos.Screen_Width

	imul rax, rbx		; RAX = RAX * RBX = pos.Y_Pos * pos.Screen_Width

	;pos.X + RAX
	movzx rbx, dx		;RBX = DX = pos.X_Pos
	add rax, rbx		;RAX = pos.Y_Pos * pos.Screen_Width + pos.X_Pos

	shl rax, 2			;RAX = RAX * 4 = addres_offset
	
	mov rdi, rcx		;RDI = screen_buffer
	add rdi, rax		;RDI = screen_buffer + addres_offset

	ret

Get_Pos_Addres endp
;--------------------------------------------------------------------------------------------------------------
Draw_Start_Symbol proc
;RDI - current address window buffer
;R8 - symbol

	; Выводим стартовый символ
	push rax
	push rbx

	mov eax, r8d
	mov rbx, r8
	shr rbx, 32	;RBX = EBX = { symbol.Start_Symbol, symbol. End_Symbol }
	mov ax, bx	;EAX = { symbol.Attributes, symbol. Start_Symbol }

	stosd

	pop rbx
	pop rax

	ret

Draw_Start_Symbol endp
;--------------------------------------------------------------------------------------------------------------
Draw_End_Symbol proc
;EAX - symbol.End_Symbol
	
	mov rbx, r8
	shr rbx, 48	;RBX = BX = symbol.End_Symbol
	mov ax, bx	;EAX = symbol.End_Symbol

	stosd

	ret

Draw_End_Symbol endp
;--------------------------------------------------------------------------------------------------------------
Draw_Line_Horizontal proc
;extern "C" void Draw_Line_Horizontal(CHAR_ INFO screen_buffer, SPos pos, ASymbol symbol)
;RCX - screen_buffer
;RDX - pos
;R8 - symbol
;R9 - не используется для передачи параметров
; Возврат: RAX
	
;_put_symbol:
;	mov [ rcx ], r9d
;	add rcx, 4
;	
;	dec r8
;	jnz _put_symbol ;jmp - это команда безусловного перехода, а есть команды условного перехода. 
					;При безусловном переходе процессор в любом случае выполнит переход, а при условном только в том случае,если соблюдено пределённое условие
					; Можно использовать и этот цикл, однако здесь используются 4 команды, а в цикле ниже всего 1
	push rax
	push rbx
	push rcx
	push rdi

	; addres_offset = (pos.Y_Pos * pos.Screen_Width + pos.X_Pos) * 4
	; pos.Y * pos.Screen_Width
	call Get_Pos_Addres

	; Выводим стартовый символ
	call Draw_Start_Symbol

	;Вывод символов symbol.Main_Symbol
	mov eax, r8d
	mov rcx, rdx
	shr rcx, 48		;RCX = CX = pos.Len
					;mov rcx, r8		; Воспользуемся префиксом повторения

	rep stosd		; Напишем префикс повторения для самого эффективного способа вывода на экран повторяющихся символов

	; Выводим конечный символ
	call Draw_End_Symbol

					;Store String Dword - запишет содержимое регистра eax по указателю который находится в регистре rdi и автоматически увеличит адрес на 4 байта,
					; что позволит последовательно вызывая такую команду записывать последовательность символов в память
					
					; После использования префикса повторения уже не нужен цикл и метка
					;_put_symbol:  
					;dec r8
					;jnz _put_symbol

	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

Draw_Line_Horizontal endp
;--------------------------------------------------------------------------------------------------------------
Draw_Line_Vertical proc
;extern "C" void	Draw_Line_Vertical(CHAR_INFO *screen_buffer, SPos pos, ASymbol symbol)
;RCX - screen_buffer
;RDX - pos
;R8 - symbol
;R9 - не используется для передачи параметров
; Возврат: RAX

	push rax
	push rcx
	push rdi
	push r11

	call Get_Pos_Addres

	call Get_Screen_Width_Size
	sub r11, 4

	; Выводим стартовый символ
	call Draw_Start_Symbol
	
	add rdi, r11

	;Preparing cycle counter

	mov rcx, rdx
	shr rcx, 48		;RCX = CX = pos.Len

	mov eax, r8d	;EAX = symbol

_1:
	stosd	;Displaying a symbol
	add rdi, r11

	loop _1

	; Выводим конечный символ
	call Draw_End_Symbol

	pop r11
	pop rdi
	pop rcx
	pop rax

	ret

Draw_Line_Vertical endp
;--------------------------------------------------------------------------------------------------------------
Show_Colors proc
;extern "C" void Show_Colors(CHAR_INFO *screen_buffer, SPos pos, CHAR_INFO symbol)
;extern "C" void Draw_Line_Horizontal(CHAR_ INFO screen_buffer, SPos pos, CHAR_INFO symbol)
;RCX - screen_buffer
;RDX - pos
;R8 - symbol
;R9 - не используется для передачи параметров
; Возврат: RAX

	push rax
	push rbx
	push rcx
	push rdi
	push r10
	push r11

	call Get_Pos_Addres

	mov r10, rdi
	
	call Get_Screen_Width_Size

	mov rax, r8

	and rax, 0ffffh
	mov rbx, 16
	xor rcx, rcx
_0:
	mov cl, 16


_1:
	stosd
	add rax, 010000h

	loop _1

	add r10, r11
	mov rdi, r10

	dec rbx
	jnz _0

	pop r11
	pop r10
	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

Show_Colors endp
;--------------------------------------------------------------------------------------------------------------
Get_Screen_Width_Size proc
; Calculates the screen Width in bytes
;RDX - area_pos or pos
;Return: R11 = pos.Screen_Width * 4

	mov r11, rdx
	shr r11, 32
	movzx r11, r11w
	shl r11, 2

	ret

Get_Screen_Width_Size endp
;--------------------------------------------------------------------------------------------------------------
Clear_Area proc
;extern "C" void Clear_Area(CHAR_INFO *screen_buffer, SArea_Pos area_pos, ASymbol symbol);
;RCX - screen_buffer
;RDX - area_pos
;R8 - symbol
;Возврат: non

	push rax
	push rbx
	push rcx
	push rdi
	push r10
	push r11

	call Get_Pos_Addres

	mov r10, rdi

	call Get_Screen_Width_Size
	
	mov rax, r8

	mov rbx, rdx
	shr rbx, 48 ; BH = area_pos.Height, BL = area_pos.Width
	
	xor rcx, rcx

_0:
	mov cl, bl
	rep stosd

	add r10, r11
	mov rdi, r10

	dec bh
	jnz _0
	
	pop r11
	pop r10
	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

Clear_Area endp
;--------------------------------------------------------------------------------------------------------------
Draw_Text proc
;extern "C" int Draw_Text(CHAR_INFO *screen_buffer, SText_Pos pos, const wchar_t *str);
;Parametrs
;RCX - screen_buffer
;RDX - pos
;R8 - str
;Return: RAX - lenght stroke

	push rbx
	push rdi
	push r8

	call Get_Pos_Addres
	
	mov rax, rdx
	shr rax, 32

	xor rbx, rbx

_1:
	mov ax, [ r8 ]

	cmp ax, 0
	je _exit

	add r8, 2

	stosd
	inc rbx
	jmp _1

_exit:
	mov rax, rbx

	pop r8
	pop rdi
	pop rbx

	ret

Draw_Text endp
;--------------------------------------------------------------------------------------------------------------
Draw_Limited_Text proc
;extern "C" void Draw_Limited_Text(CHAR_INFO *screen_buffer, SText_Pos pos, const wchar_t *str, unsigned short limit)
;Parametrs
;RCX - screen_buffer
;RDX - pos
;R8 - str
;R9 - limit
;Return: RAX - lenght stroke

	push rax
	push rcx
	push rdi
	push r8
	push r9

	call Get_Pos_Addres
	
	mov rax, rdx
	shr rax, 32

_1:
	mov ax, [ r8 ]

	cmp ax, 0
	je _fill_spaces

	add r8, 2

	stosd

	dec r9
	cmp r9, 0
	je _exit

	jmp _1

_fill_spaces:
	mov ax, 020h
	mov rcx, r9

	rep stosd

_exit:

	pop r9
	pop r8
	pop rdi
	pop rcx
	pop rax

	ret

Draw_Limited_Text endp
;--------------------------------------------------------------------------------------------------------------
Test_Command proc

	mov bx, 5
	mov cx, 7

	mov al, 1
	cmp al, 1

	cmove dx, bx
	cmovne dx, cx

	ret

Test_Command endp
;--------------------------------------------------------------------------------------------------------------
end