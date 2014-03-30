DATA    SEGMENT
   X    DW 1
   Y    DW -1
   Z    DW ?
DATA    ENDS
CODE    SEGMENT
        ASSUME CS:CODE,DS:DATA
START:  MOV AX,DATA
	MOV DS,AX
        MOV BX,X
	CMP BX,0 
	
	JGE A
	NEG BX
A:    	
	
	MOV CX,Y
	CMP CX,0
 	
	JGE B
	NEG CX
B:
	
	ADD BX,CX
	MOV Z,BX
	MOV AH,4CH
	INT 21H
CODE    ENDS


;nej   bx;直接变正反数的
        END START