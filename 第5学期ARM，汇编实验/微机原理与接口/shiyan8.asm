DATA    SEGMENT
   X    DB 5       ;���������ַ���
	DB ?
	DB 5 DUP(?)       ;���һ���ֽڴ���ǻس���
   Y    DB 5       ;���������ַ���
	DB ?
	DB 5 DUP(?)       ;���һ���ֽڴ���ǻس���
   Z    DB 20       ;���������ַ���
	DB 0
	DB 20 DUP(0)       ;���һ���ֽڴ���ǻس���
   RESULT DW 4 DUP(?)
   S    DB 'D:/A.TXT',0
   CRLF DB 0AH,0DH,'$'      ;;;;�س����еİ�˹��ֵ��          
  ;OAH,ODH�ǻس��ͻ��з��İ�˹��ֵ��$�������ַ������ս��־������������ϵͳ���Զ�ת���ɰ�˹��ֵ���롣�ڴ��ж�����ǰ�˹��ֵ��
   ANSWER DB 'the answer is:$'
   STR  DB 'and the remainder is:$'
   STRX DB 'BEGIN',0AH,0DH,'input x:$'
   STRY DB '+$'
   STRZ DB '=$'
   FILE DW ?		;���������ļ��š�
DATA    ENDS

STACK SEGMENT STACK
	DB 20 DUP(?)
STACK ENDS


CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA,SS:STACK


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
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����Ҳ���ܵ�ʵ�Σ������������AH��DH������
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
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����Ҳ���ܵ�ʵ�Σ�����
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
	;�ļ����Ż᷵�ص�AX�У����Բ��ܱ���AX 
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����Ҳ���ܵ�ʵ�Σ�����
	NEWFILE MACRO 
	   PUSH AX             ;�ǵ��ڵ���������������ұ������ļ���AX����POP AX
	   PUSH DX
	   PUSH BX
	   PUSH CX
		MOV AH,3CH
		LEA DX,S
		INT 21H
	   POP CX
	   POP BX
	   POP DX
	ENDM


	;����ꡣ����д���ļ����� 
	;���ڲ����ļ�������FILE�У�XΪҪ��������ݵ�ͷ��ַ��YΪ���ȡ�
	;��Ϊ�����õ�AX,BX,CX,DX���Բ���X��Y���������ĸ��Ĵ�������������
	;Ҫд���ļ��Ĳ���ΪX�����ǼĴ�����Ҳ�����Ǳ��������泤��ΪY
        ; һ���ǵ�Ҫ�Ѻ�Ķ���д�ں����ǰ��,�ǵ�������б�����AX��DX�����Բ������������Ĵ��������ڲ�����Ҳ���ܵ�ʵ�Σ�����
	SAVE MACRO X,Y
	   PUSH DX
	   PUSH BX
	   PUSH CX
	   PUSH AX
		MOV AH,40H
		MOV BX,FILE   ;���ļ���file�ŵ�BX��	
		MOV CX,Y
		LEA DX,X
		INT 21H
	   POP AX   
	   POP CX
	   POP BX
	   POP DX
	ENDM




	;�ӳ����ܣ������־�����˹��ת��
	;AX����������ڵ��׵�ַ��
	;��ڲ�����AX
	;���ڲ�����AX
	SHOW PROC NEAR
	    PUSH BX
	    PUSH DX
		MOV DX,0
		MOV BX,0AH     
		CWD
		IDIV BX
		ADD AX,30H          
		ADD DX,30H
		MOV RESULT,AX  
		MOV RESULT+2,DX
	  
	;;;	SAVE RESULT,2  
	;;;	SAVE RESULT+2,2

	;;;	DOUT RESULT
	;;;	DOUT RESULT+2

	    POP DX
	    POP BX
	    RET
	SHOW ENDP   

            
	;����ꣻ���ܣ���dos������ĵ������־�����˹��ת����AX��
	;��ڲ�����dos����
	;���ڲ�����AL
	INPUT MACRO 
		MOV AH,01H  ;����dos����ĵ����ַ��ŵ�x��
		INT 21H
		SUB AL,30H    
	ENDM




	;����꣺��dos�����ַ�������ŵ���Ӧλ��,����XΪ��ŵ��׵�ַ��
	STRIN MACRO X
		MOV AH,0AH
		LEA DX,X
		INT 21H
	ENDM
	
	;����꣬�������ָ���׵�ַ���ַ���
	STROUT MACRO X
		MOV CL,X+1
		LEA SI,X+2
	  NEXT: MOV DL,[SI]
		MOV AH,02H
		INT 21H
		INC SI
		DEC CL
		JNZ NEXT
	ENDM

	;�����ӳ����������ָ���׵�ַ���ַ�����
	;��ڲ���DI�����ǵ�ַ��
	ZSTROUT PROC NEAR
		MOV CL,[DI+1]
		LEA SI,[DI+2]
	  NEXT: MOV DL,[SI]
		MOV AH,02H
		INT 21H
		INC SI
		DEC CL
		JNZ NEXT
	     RET
	ZSTROUT ENDP

	;����꣬�����������ָ���׵�ַ���ַ���
	STROUTN MACRO X
		MOV CL,X+1
		LEA SI,X+2

		MOV AL,CL	;Ŀ�ģ���SIָ���ַ������ 
		MOV AH,0	;Ŀ�ģ���SIָ���ַ������ 
		ADD SI,AX	;Ŀ�ģ����հ�SIָ���ַ������ĺ�һλ��
	  NEXTN: 
		DEC SI
		MOV DL,[SI]
		MOV AH,02H
		INT 21H
		DEC CL
		JNZ NEXTN
	ENDM

	;�����ӳ��������������ָ���׵�ַ���ַ���
	;��ڲ���DI�����ǵ�ַ��
	ZSTROUTN PROC NEAR
		MOV CL,[DI+1]
		LEA SI,[DI+2]


		MOV AL,CL	;Ŀ�ģ���SIָ���ַ������ 
		MOV AH,0	;Ŀ�ģ���SIָ���ַ������ 
		ADD SI,AX	;Ŀ�ģ����հ�SIָ���ַ������ĺ�һλ��
	  NEXTN: 
		DEC SI
		MOV DL,[SI]
		MOV AH,02H
		INT 21H
		DEC CL
		JNZ NEXTN
	     RET
	ZSTROUTN ENDP

	;����꣬���ַ����ڵ�����ת����BCD�롣
	TOBCD MACRO X
		MOV CL,X+1
		LEA SI,X+2
	  TOBCDT:
		MOV DL,[SI] 
		SUB DL,30H
		MOV [SI],DL
		INC SI
		DEC CL
		JNZ TOBCDT
	ENDM
	
	;�����ӳ��򣬽��ַ����ڵ�����ת����BCD�롣
	;��ڲ���DI�����ǵ�ַ��
	ZTOBCD PROC NEAR 
		MOV CL,[DI+1]
		LEA SI,[DI+2]
	  ZTOBCDT:
		MOV DL,[SI] 
		SUB DL,30H
		MOV [SI],DL
		INC SI
		DEC CL
		JNZ ZTOBCDT
	    RET
	ZTOBCD ENDP

	;����꣬���ַ����ڵ�BCD��ת���ɰ�˹�ꡣ
	FROMBCD MACRO X
		MOV CL,X+1
		LEA SI,X+2
	  FROMBCDT: 
		MOV DL,[SI] 
		ADD DL,30H
		MOV [SI],DL
		INC SI
		DEC CL
		JNZ FROMBCDT
	ENDM

	;�����ӳ��򣬽��ַ����ڵ�BCD��ת���ɰ�˹��
	;��ڲ���DI�����ǵ�ַ��
	ZFROMBCD PROC NEAR 
		MOV CL,[DI+1]
		LEA SI,[DI+2]
	  ZFROMBCDT:
		MOV DL,[SI] 
		ADD DL,30H
		MOV [SI],DL
		INC SI
		DEC CL
		JNZ ZFROMBCDT
	    RET
	ZFROMBCD ENDP

	;�����ӳ���Ŀ�ģ���һ���ַ�����˳�������
	;��ڲ���DI���ַ����׵�ַ��
	DIAOGE PROC NEAR
		MOV AL,[DI+1]			
		LEA SI,[DI+1]
		MOV AH,0	;Ŀ�ģ���SIָ���ַ������ 
		ADD SI,AX	;Ŀ�ģ����հ�SIָ���ַ������ĺ�һλ��


		CBW 				;���ַ������ȵ�һ�룬�ŵ�cl�С�����ԭ������AL��
		MOV BL,2
		DIV BL
		MOV CL,AL			;���ַ������ȵ�һ�룬�ŵ�cl�С�
		MOV CH,0

		ADD DI,2	;DIָ�������ݵ��׵�ַ��
	    TDIAOGE:
		MOV AH,[DI]
		MOV AL,[SI]
		MOV BYTE PTR [DI],AL
		MOV BYTE PTR [SI],AH		
		INC DI
		DEC SI
	    LOOP TDIAOGE

		RET
	DIAOGE ENDP

;;	;����꣬X+Y�ŵ�Z�С�
;;	STRADD MACRO Z,X,Y
;;		LEA SI,X+1          ;���Ѱַ�ļĴ���ֻ��SI,DI,BX
;;		LEA DI,Y+1
;;		LEA BX,Z+1


	;�����ӳ���Z=X+Y
	;��ڲ�����[BX]=[SI]+[DI]���ݵ�ȫ�ǵ�ַ
	STRADD PROC NEAR
		ADD SI,1
		ADD DI,1
		ADD BX,1



		MOV DH,[SI]     ;Ŀ���Ȱ��������ַ����ĳ��ȸ���¼�������Ժ���Ҫ�á�
		MOV DL,[DI]

		MOV AL,[SI]	;Ŀ�ģ���SIָ���ַ������ 
		MOV AH,0	;Ŀ�ģ���SIָ���ַ������ 
		ADD SI,AX	;Ŀ�ģ���SIָ���ַ������
 
		MOV AL,[DI]	;Ŀ�ģ���DIָ���ַ������ 
		MOV AH,0	;Ŀ�ģ���DIָ���ַ������ 
		ADD DI,AX	;Ŀ�ģ���DIָ���ַ������
		

				
		CMP DH,DL	  ;CL����ѭ������Ϊ������������Ǹ�
		JG G
		MOV CL,DL  
		JMP D
		G:MOV CL,DH   
		D:		 ;CL����ѭ������Ϊ������������Ǹ�


		MOV CH,0
		MOV BYTE PTR [BX],CL
		ADD BYTE PTR [BX],1        ;��Z���ȼ�1��Ϊ�������λʱ������
			
	  ADDNEXT:
		INC BX
		MOV AL,0

		CMP DH,0
		JLE XXX
		ADD AL,[SI]
		XXX:
		
		CMP DL,0
		JLE YYY
		ADD AL,[DI]
		YYY:

		CMP AL,0AH
		JL XIAOYU
		ADD BYTE PTR [BX+1],1
		SUB AL,0AH
	        XIAOYU:

		ADD BYTE PTR [BX],AL
		DEC SI
		DEC DH

		
		DEC DI
		DEC DL
	  LOOP ADDNEXT
	RET
	STRADD ENDP



;;	ENDM



	;�����ӳ���Z=X+Z
	;��ڲ�����[DI]=[SI]+[DI]���ݵ�ȫ�ǵ�ַ
	ZSTRADD PROC NEAR
		ADD SI,1
		ADD DI,1

		MOV BX,DI	;��סz�ַ������ȵĵ�ַ��

		MOV DH,[DI]     ;Ŀ���Ȱ��������ַ����ĳ��ȸ���¼�������Ժ���Ҫ�á�
		MOV DL,[SI]

		MOV AL,[SI]	;Ŀ�ģ���SIָ���ַ������ 
		MOV AH,0	;Ŀ�ģ���SIָ���ַ������ 
		ADD SI,AX	;Ŀ�ģ���SIָ���ַ������


				
		MOV CL,DL      ;CL����ѭ������
		MOV CH,0



		MOV AL,0		;��ʼ��AL������¼����������ֳ��ȵģ�
			
	  ZADDNEXT:
		INC DI


		MOV AH,[SI]
		ADD BYTE PTR [DI],AH		;�ǵ����ADD������������Ǽ��Ѱַ
		
		INC AL		;������¼����������ֳ��ȵģ�

		
		CMP BYTE PTR [DI],0AH			;����ǵã�cmpָ����Ѱַ��ʱ��Ҳ��Ҫ BYTE PTR 
		JL ZXIAOYU
		    ADD BYTE PTR [DI+1],1
		    SUB BYTE PTR [DI],0AH
		    CMP CL,1

		    JNE TIAO
		        INC AL
		    TIAO:

	        ZXIAOYU:

		DEC SI

	  LOOP ZADDNEXT

	CMP AL,DH
	JL XIAO
	  MOV BYTE PTR [BX],AL		;���AL���ַ���Z�ĳ��ȴ󣬾Ͱ�AL��ΪZ�ĳ��ȣ�
	XIAO:

	RET
	ZSTRADD ENDP



START:  MOV AX,DATA
	MOV DS,AX
	MOV AX,STACK
	MOV SS,AX
	MOV SP,20


	
	
	LEA DX,STRX          ;��ʾ����X
	MOV AH,09H	    
	INT 21H		
	HUICHE

	STRIN X	
	LEA DI,X
	CALL ZTOBCD
	HUICHE

;	LEA DX,STRY          ;��ʾ����Y
;	MOV AH,09H	    
;	INT 21H	
;	HUICHE
;
;	STRIN Y
;	LEA DI,Y
;	CALL ZTOBCD
;	HUICHE
;
;	LEA DX,ANSWER          ;��ʾ�����
;	MOV AH,09H	    
;	INT 21H
;	HUICHE	

	MOV CX,100		;CX���ӳ����б��ˡ�������
PPPP:
	PUSH CX
	LEA SI,X
	LEA DI,Z
;;;	LEA BX,Z
;;;	CALL STRADD 
	CALL ZSTRADD
	LEA DI,Z
	CALL ZFROMBCD
	LEA DX,STRZ          ;��ʾ�����
	MOV AH,09H	    
	INT 21H
	;HUICHE	
	LEA DI,Z
	CALL ZSTROUTN
	LEA DI,Z	
	CALL ZTOBCD
	HUICHE
	
	
	LEA DX,STRY          ;��ʾ��������X
	MOV AH,09H	    
	INT 21H		
	;HUICHE

	STRIN X	
	LEA DI,X
	CALL ZTOBCD
	HUICHE

	POP CX
LOOP PPPP




;	LEA DX,STRY          ;��ʾ����Y          ;;;;;;��������鷢���ˣ���Y����2 ��ʱ���Լ���������ѱ��ش���D�����ָĳ�A TXT��
;	MOV AH,09H	    
;	INT 21H		
;	CALL INPUT
;	MOV AH,0
;	MOV Y,AX
;	HUICHE
;	LEA DX,STRZ          ;��ʾ����Z
;	MOV AH,09H	    
;	INT 21H		
;	CALL INPUT
;	MOV AH,0
;	MOV Z,AX	
;	HUICHE
;	HUICHE


	


;	MOV AX,4           ;���￪ʼ���㹫ʽS=(X+4*Y)/Z  
;	IMUL Y
;	MOV CX,AX
;	MOV BX,DX
;	MOV AL,X
;	CBW
;	CWD
;	ADD AX,CX
;	ADC DX,BX
;	IDIV Z		    ;�ó�����AX��������DX�С�
;	MOV RESULT,AX    
;	MOV RESULT+4,DX


;	NEWFILE����������������������;;;;;;�ƺ���ǰ���еĵط���������½��ļ������󣬲���ִ�С�û���½���
;	MOV FILE,AX
;	POP AX	
	


	



;;;;;	PUSH DX		    ;��������dx
;;;;	PUSH AX
;	AOUT 9H,9H
;	LEA DX,ANSWER          ;��ʾ��the answer is��
;	MOV AH,09H	    ;dos����ʾ���ַ���
;	INT 21H
;;;;;	POP AX
;;;;;	POP DX	
;	HUICHE
;	AOUT 11,11
;	MOV AX,RESULT
;	CALL SHOW            ; ����̵�dos��
;	HUICHE
;;;;;	PUSH DX		    ;��������dx
;	AOUT 13,13
;	LEA DX,STR          ;��ʾ��and the remainder is��
;	MOV AH,09H	    ;dos����ʾ���ַ���
;	INT 21H
;;;;;	POP DX
;	HUICHE
;	AOUT 15,15
;	MOV AX,RESULT+4           ;����������ax
;	CALL SHOW 	    ; ���������dos��	
;
;
;
;	;NEWFILE
;	;MOV FILE,AX
;	;POP AX


	MOV AH,4CH
	INT 21H


	
	

CODE    ENDS
        END START



;С�ܽᣬ�ں�����������˱�־��������NEXT: ������ֻ�ܱ�����һ�Ρ�
;��Ϊ�����������ʱ����չ����ʱ����������NEXT��־����
;���ظ��ˣ��ᱨ������������ӳ���Ϳ��Ա����ö�Ρ�
;�����Ժ�����ת����ʱ�������ӳ���á�
;��ͬһλ�õĲ�ͬ�ӳ�������ı�־��Ҳ������һ���������Ժͺ�ı�־��һ����(���������ƺ�Ҳ�е����⣬��ʱ��Ҳ�ᱨ��)

;�����ӳ��������������ָ���׵�ַ���ַ���;;;;;
;���������û���ˡ���Ϊ��д��һ�����ַ����������ӳ���
;��Ϊ�����ӵ�;ʱ����Ҫ�Ȱѽ���ų�����˳��
;�����������ˣ���ΪZ��Z��Xʱ��Z��˳������Ҫ���ģ����ԾͲ��ذ�Z�����ˡ�
;ֻҪ�����ʱ��;�����������