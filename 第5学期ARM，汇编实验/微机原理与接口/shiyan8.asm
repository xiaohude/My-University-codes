DATA    SEGMENT
   X    DB 5       ;存放输入的字符串
	DB ?
	DB 5 DUP(?)       ;最后一个字节存的是回车。
   Y    DB 5       ;存放输入的字符串
	DB ?
	DB 5 DUP(?)       ;最后一个字节存的是回车。
   Z    DB 20       ;存放输入的字符串
	DB 0
	DB 20 DUP(0)       ;最后一个字节存的是回车。
   RESULT DW 4 DUP(?)
   S    DB 'D:/A.TXT',0
   CRLF DB 0AH,0DH,'$'      ;;;;回车换行的阿斯玛值。          
  ;OAH,ODH是回车和换行符的阿斯玛值，$符号是字符串的终结标志符，带上引号系统会自动转换成阿斯玛值存入。内存中都存的是阿斯玛值。
   ANSWER DB 'the answer is:$'
   STR  DB 'and the remainder is:$'
   STRX DB 'BEGIN',0AH,0DH,'input x:$'
   STRY DB '+$'
   STRZ DB '=$'
   FILE DW ?		;用来保存文件号。
DATA    ENDS

STACK SEGMENT STACK
	DB 20 DUP(?)
STACK ENDS


CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA,SS:STACK


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
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。也不能当实参！！！这个宏中AH和DH都可以
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
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。也不能当实参！！！
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
	;文件代号会返回到AX中，所以不能保护AX 
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。也不能当实参！！！
	NEWFILE MACRO 
	   PUSH AX             ;记得在调用完这个函数并且保存完文件号AX后有POP AX
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


	;定义宏。用来写入文件东西 
	;进口参数文件代号在FILE中，X为要保存的数据的头地址，Y为长度。
	;因为里面用到AX,BX,CX,DX所以参数X，Y不能是这四个寄存器。！！！！
	;要写入文件的参数为X可以是寄存器，也可以是变量。保存长度为Y
        ; 一定记得要把宏的定义写在宏调用前面,记得这个宏中保护了AX和DX。所以不能用这两个寄存器当出口参数。也不能当实参！！！
	SAVE MACRO X,Y
	   PUSH DX
	   PUSH BX
	   PUSH CX
	   PUSH AX
		MOV AH,40H
		MOV BX,FILE   ;把文件号file放到BX中	
		MOV CX,Y
		LEA DX,X
		INT 21H
	   POP AX   
	   POP CX
	   POP BX
	   POP DX
	ENDM




	;子程序功能：将数字经过阿斯玛转换
	;AX存放数字所在的首地址。
	;入口参数：AX
	;出口参数：AX
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

            
	;定义宏；功能：将dos下输入的单个数字经过阿斯玛转换到AX中
	;入口参数：dos输入
	;出口参数：AL
	INPUT MACRO 
		MOV AH,01H  ;来把dos输入的单个字符放到x中
		INT 21H
		SUB AL,30H    
	ENDM




	;定义宏：从dos输入字符串，存放到相应位置,参数X为存放的首地址。
	STRIN MACRO X
		MOV AH,0AH
		LEA DX,X
		INT 21H
	ENDM
	
	;定义宏，用来输出指定首地址的字符串
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

	;定义子程序，用来输出指定首地址的字符串、
	;入口参数DI传的是地址。
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

	;定义宏，用来反向输出指定首地址的字符串
	STROUTN MACRO X
		MOV CL,X+1
		LEA SI,X+2

		MOV AL,CL	;目的：把SI指向字符串最后。 
		MOV AH,0	;目的：把SI指向字符串最后。 
		ADD SI,AX	;目的：最终把SI指向字符串最后的后一位。
	  NEXTN: 
		DEC SI
		MOV DL,[SI]
		MOV AH,02H
		INT 21H
		DEC CL
		JNZ NEXTN
	ENDM

	;定义子程序，用来反向输出指定首地址的字符串
	;入口参数DI传的是地址。
	ZSTROUTN PROC NEAR
		MOV CL,[DI+1]
		LEA SI,[DI+2]


		MOV AL,CL	;目的：把SI指向字符串最后。 
		MOV AH,0	;目的：把SI指向字符串最后。 
		ADD SI,AX	;目的：最终把SI指向字符串最后的后一位。
	  NEXTN: 
		DEC SI
		MOV DL,[SI]
		MOV AH,02H
		INT 21H
		DEC CL
		JNZ NEXTN
	     RET
	ZSTROUTN ENDP

	;定义宏，将字符串内的数字转换成BCD码。
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
	
	;定义子程序，将字符串内的数字转换成BCD码。
	;入口参数DI传的是地址。
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

	;定义宏，将字符串内的BCD码转换成阿斯玛。
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

	;定义子程序，将字符串内的BCD码转换成阿斯玛
	;入口参数DI传的是地址。
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

	;定义子程序，目的，将一个字符串的顺序掉个。
	;入口参数DI传字符串首地址。
	DIAOGE PROC NEAR
		MOV AL,[DI+1]			
		LEA SI,[DI+1]
		MOV AH,0	;目的：把SI指向字符串最后。 
		ADD SI,AX	;目的：最终把SI指向字符串最后的后一位。


		CBW 				;求字符串长度的一半，放到cl中。现在原长度在AL中
		MOV BL,2
		DIV BL
		MOV CL,AL			;求字符串长度的一半，放到cl中。
		MOV CH,0

		ADD DI,2	;DI指向了数据的首地址。
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

;;	;定义宏，X+Y放到Z中。
;;	STRADD MACRO Z,X,Y
;;		LEA SI,X+1          ;间接寻址的寄存器只有SI,DI,BX
;;		LEA DI,Y+1
;;		LEA BX,Z+1


	;定义子程序，Z=X+Y
	;入口参数：[BX]=[SI]+[DI]传递的全是地址
	STRADD PROC NEAR
		ADD SI,1
		ADD DI,1
		ADD BX,1



		MOV DH,[SI]     ;目的先把这两个字符串的长度个记录下来。以后需要用。
		MOV DL,[DI]

		MOV AL,[SI]	;目的：把SI指向字符串最后。 
		MOV AH,0	;目的：把SI指向字符串最后。 
		ADD SI,AX	;目的：把SI指向字符串最后。
 
		MOV AL,[DI]	;目的：把DI指向字符串最后。 
		MOV AH,0	;目的：把DI指向字符串最后。 
		ADD DI,AX	;目的：把DI指向字符串最后。
		

				
		CMP DH,DL	  ;CL决定循环次数为两个数字最长的那个
		JG G
		MOV CL,DL  
		JMP D
		G:MOV CL,DH   
		D:		 ;CL决定循环次数为两个数字最长的那个


		MOV CH,0
		MOV BYTE PTR [BX],CL
		ADD BYTE PTR [BX],1        ;把Z长度加1，为了输出进位时的数。
			
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



	;定义子程序，Z=X+Z
	;入口参数：[DI]=[SI]+[DI]传递的全是地址
	ZSTRADD PROC NEAR
		ADD SI,1
		ADD DI,1

		MOV BX,DI	;记住z字符串长度的地址。

		MOV DH,[DI]     ;目的先把这两个字符串的长度个记录下来。以后需要用。
		MOV DL,[SI]

		MOV AL,[SI]	;目的：把SI指向字符串最后。 
		MOV AH,0	;目的：把SI指向字符串最后。 
		ADD SI,AX	;目的：把SI指向字符串最后。


				
		MOV CL,DL      ;CL控制循环次数
		MOV CH,0



		MOV AL,0		;初始化AL用来记录运算过的数字长度的，
			
	  ZADDNEXT:
		INC DI


		MOV AH,[SI]
		ADD BYTE PTR [DI],AH		;记得这里，ADD命令不能两个都是间接寻址
		
		INC AL		;用来记录运算过的数字长度的，

		
		CMP BYTE PTR [DI],0AH			;这里记得，cmp指令间接寻址的时候也需要 BYTE PTR 
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
	  MOV BYTE PTR [BX],AL		;如果AL比字符串Z的长度大，就把AL作为Z的长度，
	XIAO:

	RET
	ZSTRADD ENDP



START:  MOV AX,DATA
	MOV DS,AX
	MOV AX,STACK
	MOV SS,AX
	MOV SP,20


	
	
	LEA DX,STRX          ;提示输入X
	MOV AH,09H	    
	INT 21H		
	HUICHE

	STRIN X	
	LEA DI,X
	CALL ZTOBCD
	HUICHE

;	LEA DX,STRY          ;提示输入Y
;	MOV AH,09H	    
;	INT 21H	
;	HUICHE
;
;	STRIN Y
;	LEA DI,Y
;	CALL ZTOBCD
;	HUICHE
;
;	LEA DX,ANSWER          ;提示结果是
;	MOV AH,09H	    
;	INT 21H
;	HUICHE	

	MOV CX,100		;CX在子程序中变了。！！！
PPPP:
	PUSH CX
	LEA SI,X
	LEA DI,Z
;;;	LEA BX,Z
;;;	CALL STRADD 
	CALL ZSTRADD
	LEA DI,Z
	CALL ZFROMBCD
	LEA DX,STRZ          ;提示结果是
	MOV AH,09H	    
	INT 21H
	;HUICHE	
	LEA DI,Z
	CALL ZSTROUTN
	LEA DI,Z	
	CALL ZTOBCD
	HUICHE
	
	
	LEA DX,STRY          ;提示继续输入X
	MOV AH,09H	    
	INT 21H		
	;HUICHE

	STRIN X	
	LEA DI,X
	CALL ZTOBCD
	HUICHE

	POP CX
LOOP PPPP




;	LEA DX,STRY          ;提示输入Y          ;;;;;;奇妙的事情发生了，当Y输入2 的时候，自己这个程序会把本地磁盘D的名字改成A TXT。
;	MOV AH,09H	    
;	INT 21H		
;	CALL INPUT
;	MOV AH,0
;	MOV Y,AX
;	HUICHE
;	LEA DX,STRZ          ;提示输入Z
;	MOV AH,09H	    
;	INT 21H		
;	CALL INPUT
;	MOV AH,0
;	MOV Z,AX	
;	HUICHE
;	HUICHE


	


;	MOV AX,4           ;这里开始计算公式S=(X+4*Y)/Z  
;	IMUL Y
;	MOV CX,AX
;	MOV BX,DX
;	MOV AL,X
;	CBW
;	CWD
;	ADD AX,CX
;	ADC DX,BX
;	IDIV Z		    ;得出商在AX中余数在DX中。
;	MOV RESULT,AX    
;	MOV RESULT+4,DX


;	NEWFILE　　　　　　　　　　　;;;;;;似乎在前面有的地方调用这个新建文件函数后，不会执行。没有新建。
;	MOV FILE,AX
;	POP AX	
	


	



;;;;;	PUSH DX		    ;保护余数dx
;;;;	PUSH AX
;	AOUT 9H,9H
;	LEA DX,ANSWER          ;显示“the answer is”
;	MOV AH,09H	    ;dos中显示出字符串
;	INT 21H
;;;;;	POP AX
;;;;;	POP DX	
;	HUICHE
;	AOUT 11,11
;	MOV AX,RESULT
;	CALL SHOW            ; 输出商到dos上
;	HUICHE
;;;;;	PUSH DX		    ;保护余数dx
;	AOUT 13,13
;	LEA DX,STR          ;显示“and the remainder is”
;	MOV AH,09H	    ;dos中显示出字符串
;	INT 21H
;;;;;	POP DX
;	HUICHE
;	AOUT 15,15
;	MOV AX,RESULT+4           ;将余数存入ax
;	CALL SHOW 	    ; 输出余数到dos上	
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



;小总结，在宏中如果定义了标志符，例如NEXT: 这个宏就只能被调用一次。
;因为如果调用两次时，宏展开的时候会出现两个NEXT标志符，
;就重复了，会报错。但是如过用子程序就可以被调用多次。
;所以以后用跳转语句的时候还是用子程序好。
;在同一位置的不同子程序里面的标志符也不可以一样，但可以和宏的标志符一样。(不过这里似乎也有点问题，有时候也会报错)

;定义子程序，用来反向输出指定首地址的字符串;;;;;
;这个后来就没用了。因为又写了一个让字符串掉个的子程序。
;因为连续加的;时候需要先把结果排成正常顺序。
;后来又有用了，因为Z＝Z＋X时，Z的顺序还是需要反的，所以就不必把Z掉个了。
;只要输出的时候反;向输出就行了