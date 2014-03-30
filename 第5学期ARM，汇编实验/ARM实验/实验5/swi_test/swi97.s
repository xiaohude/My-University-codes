	EXPORT swi97_int
	AREA my_swi97,CODE,READONLY
swi97_int
	stmfd sp!, {lr}
    swi 97
    ldmfd sp!, {lr}
finish    
    mov pc, lr		
	NOP
	NOP
	NOP
	NOP
	NOP
	END