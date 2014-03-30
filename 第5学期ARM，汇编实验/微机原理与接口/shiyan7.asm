DATA    SEGMENT
   X    DB 0
   Y    DW 0
   Z    DW 1
   S    DB 'D:/A.TXT',0
   CRLF DB 0AH,0DH,'$'                
  ;OAH,ODH是回车和换行符的阿斯玛值，$符号是字符串的终结标志符，带上引号系统会自动转换成阿斯玛值存入。内存中都存的是阿斯玛值。
   ANSWER DB 'the answer is:$'
   STR  DB 'and the remainder is:$'
   STRX DB 'cout:S=(X+4*Y)/Z',0AH,0DH,'input x:$'
   STRY DB 'input y:$'
   STRZ DB 'input z:$'
DATA    ENDS
CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA


	;定义宏。显示回车换行
	HUICHE MACRO
	    PUSH AX
	    PUSH DX
		LEA DX,CRLF
		MOV AH,09H
		INT 21H
	    POP DX
	    POP AX	
	ENDM


	;定义宏。用来把字符X输出到dos上   
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。
	DOUT MACRO X
	   PUSH DX
	   PUSH AX
		MOV DX,X
		MOV AH,02H
		INT 21H
	   POP AX
	   POP DX
	ENDM
	
	;定义宏。用来设置光标位置   
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。
	AOUT MACRO X,Y
	   PUSH DX
	   PUSH AX
	   PUSH BX
	   PUSH CX
		MOV AH,02H
		MOV DH,X
		MOV DL,Y
		INT 10H
	   POP CX
	   POP BX
	   POP AX
	   POP DX
	ENDM




	;定义宏。用来新建文件  
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。
	NEWFILE MACRO 
	   PUSH DX
	   PUSH AX
	   PUSH BX
	   PUSH CX
		MOV AH,3CH
		LEA DX,S
		INT 21H
	   POP CX
	   POP BX
	   POP AX
	   POP DX
	ENDM






	;子程序功能：将数字经过阿斯玛转换输出在dos窗口下（调用了宏DOUT）
	;入口参数：AX
	;出口参数：AH
	SHOW PROC NEAR
	    PUSH BX
	    PUSH DX
		MOV DX,0
		MOV BX,0AH     
		CWD
		IDIV BX
		ADD AX,30H          
		ADD DX,30H
		DOUT AX
		DOUT DX
	    POP DX
	    POP BX
	    RET
	SHOW ENDP   

            
	;子程序功能：将dos下输入的单个字符（数字）经过阿斯玛转换到AX中
	;入口参数：dos输入
	;出口参数：AX
	INPUT PROC NEAR
		MOV AH,01H  ;来把dos输入的单个字符放到x中
		INT 21H
		SUB AX,30H
	    RET
	INPUT ENDP


START:  MOV AX,DATA
	MOV DS,AX
	
	LEA DX,STRX          ;提示输入X
	MOV AH,09H	    
	INT 21H		
	CALL INPUT
	MOV X,AL
	HUICHE
	LEA DX,STRY          ;提示输入Y
	MOV AH,09H	    
	INT 21H		
	CALL INPUT
	MOV AH,0
	MOV Y,AX
	HUICHE
	LEA DX,STRZ          ;提示输入Z
	MOV AH,09H	    
	INT 21H		
	CALL INPUT
	MOV AH,0
	MOV Z,AX	
	HUICHE
	HUICHE


	MOV AX,4           ;这里开始计算公式S=(X+4*Y)/Z  
	IMUL Y
	MOV CX,AX
	MOV BX,DX
	MOV AL,X
	CBW
	CWD
	ADD AX,CX
	ADC DX,BX
	IDIV Z		    ;得出商在AX中余数在DX中。

	NEWFILE


	PUSH DX		    ;保护余数dx
	PUSH AX
	AOUT 9H,9H
	LEA DX,ANSWER          ;显示“the answer　is”
	MOV AH,09H	    ;dos中显示出字符串
	INT 21H
	POP AX
	POP DX	
	HUICHE
	AOUT 11,11
	CALL SHOW            ; 输出商到dos上
	HUICHE
	PUSH DX		    ;保护余数dx
	AOUT 13,13
	LEA DX,STR          ;显示“and the remainder is”
	MOV AH,09H	    ;dos中显示出字符串
	INT 21H
	POP DX
	HUICHE
	AOUT 15,15
	mov ax,dx           ;将余数存入ax
	call SHOW 	    ; 输出余数到dos上	
	MOV AH,4CH
	INT 21H


	
	

CODE    ENDS
        END START