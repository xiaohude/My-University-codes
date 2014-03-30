;===========================================
;栈的地址，时钟参数等常量定义，主要用于2440init.s中的初始化
;===========================================

;Start address of each stacks,
_STACK_BASEADDRESS	EQU 0x33ff8000
_ISR_STARTADDRESS	EQU 0x33ffff00

;Select Clock Division (Fclk:Hclk:Pclk)
CLKDIV_VAL	EQU	5	; 0=1:1:1, 1=1:1:2, 2=1:2:2, 3=1:2:4, 4=1:4:4, 5=1:4:8, 6=1:3:3, 7=1:3:6.
M_MDIV		EQU	92		;Fin=12.0MHz Fout=400MHz
M_PDIV		EQU	1
M_SDIV		EQU	1		; 2440A
U_MDIV		EQU	56		;Fin=12.0MHz Fout=48MHz
U_PDIV		EQU	2
U_SDIV		EQU	2		; 2440A

	END

