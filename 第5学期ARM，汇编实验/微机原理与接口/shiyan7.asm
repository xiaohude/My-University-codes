DATA    SEGMENT
   X    DB 0
   Y    DW 0
   Z    DW 1
   S    DB 'D:/A.TXT',0
   CRLF DB 0AH,0DH,'$'                
  ;OAH,ODH�ǻس��ͻ��з��İ�˹��ֵ��$�������ַ������ս��־������������ϵͳ���Զ�ת���ɰ�˹��ֵ���롣�ڴ��ж�����ǰ�˹��ֵ��
   ANSWER DB 'the answer is:$'
   STR  DB 'and the remainder is:$'
   STRX DB 'cout:S=(X+4*Y)/Z',0AH,0DH,'input x:$'
   STRY DB 'input y:$'
   STRZ DB 'input z:$'
DATA    ENDS
CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA


	;����ꡣ��ʾ�س�����
	HUICHE MACRO
	    PUSH AX
	    PUSH DX
		LEA DX,CRLF
		MOV AH,09H
		INT 21H
	    POP DX
	    POP AX	
	ENDM


	;����ꡣ�������ַ�X�����dos��   
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����
	DOUT MACRO X
	   PUSH DX
	   PUSH AX
		MOV DX,X
		MOV AH,02H
		INT 21H
	   POP AX
	   POP DX
	ENDM
	
	;����ꡣ�������ù��λ��   
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����
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




	;����ꡣ�����½��ļ�  
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����
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






	;�ӳ����ܣ������־�����˹��ת�������dos�����£������˺�DOUT��
	;��ڲ�����AX
	;���ڲ�����AH
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

            
	;�ӳ����ܣ���dos������ĵ����ַ������֣�������˹��ת����AX��
	;��ڲ�����dos����
	;���ڲ�����AX
	INPUT PROC NEAR
		MOV AH,01H  ;����dos����ĵ����ַ��ŵ�x��
		INT 21H
		SUB AX,30H
	    RET
	INPUT ENDP


START:  MOV AX,DATA
	MOV DS,AX
	
	LEA DX,STRX          ;��ʾ����X
	MOV AH,09H	    
	INT 21H		
	CALL INPUT
	MOV X,AL
	HUICHE
	LEA DX,STRY          ;��ʾ����Y
	MOV AH,09H	    
	INT 21H		
	CALL INPUT
	MOV AH,0
	MOV Y,AX
	HUICHE
	LEA DX,STRZ          ;��ʾ����Z
	MOV AH,09H	    
	INT 21H		
	CALL INPUT
	MOV AH,0
	MOV Z,AX	
	HUICHE
	HUICHE


	MOV AX,4           ;���￪ʼ���㹫ʽS=(X+4*Y)/Z  
	IMUL Y
	MOV CX,AX
	MOV BX,DX
	MOV AL,X
	CBW
	CWD
	ADD AX,CX
	ADC DX,BX
	IDIV Z		    ;�ó�����AX��������DX�С�

	NEWFILE


	PUSH DX		    ;��������dx
	PUSH AX
	AOUT 9H,9H
	LEA DX,ANSWER          ;��ʾ��the answer��is��
	MOV AH,09H	    ;dos����ʾ���ַ���
	INT 21H
	POP AX
	POP DX	
	HUICHE
	AOUT 11,11
	CALL SHOW            ; ����̵�dos��
	HUICHE
	PUSH DX		    ;��������dx
	AOUT 13,13
	LEA DX,STR          ;��ʾ��and the remainder is��
	MOV AH,09H	    ;dos����ʾ���ַ���
	INT 21H
	POP DX
	HUICHE
	AOUT 15,15
	mov ax,dx           ;����������ax
	call SHOW 	    ; ���������dos��	
	MOV AH,4CH
	INT 21H


	
	

CODE    ENDS
        END START