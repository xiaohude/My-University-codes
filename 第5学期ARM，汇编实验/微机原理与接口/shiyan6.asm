DATA    SEGMENT
   X    DB 4
   Y    DW 7
   Z    DW 2
DATA    ENDS
CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA
START:  MOV AX,DATA
	MOV DS,AX		
	MOV AX,4             ;10
	IMUL Y
	MOV CX,AX
	MOV BX,DX
	MOV AL,X
	CBW
	CWD
	ADD AX,CX
	ADC DX,BX
	IDIV Z
	CALL ASM            ;20
	MOV AH,4CH
	INT 21H


	;����ꡣ�������ַ�X�����dos��    һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��
	DOUT MACRO X
	   PUSH DX
		MOV DX,X
		MOV AH,02H
		INT 21H
	   POP DX
	ENDM


	;�ӳ����ܣ����ַ������dos�����£������˺�DOUT��
	;��ڲ�����AX
	;���ڲ�����AH
	ASM PROC NEAR
		PUSH BX
		PUSH DX
		MOV DX,0
		MOV BX,0AH     ;
		CWD
		IDIV BX
		ADD AX,30H          
		ADD DX,30H
		DOUT AX
		DOUT DX
		POP DX
		POP BX
		RET
	ASM ENDP               

	

CODE    ENDS
        END START