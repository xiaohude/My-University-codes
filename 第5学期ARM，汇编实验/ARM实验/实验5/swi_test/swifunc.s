	EXPORT handle_swi
	IMPORT swi97_func
	IMPORT swi98_func
	IMPORT swi99_func
	AREA my_swi,CODE,READONLY
handle_swi
    ;�����ֳ�
	stmfd sp!, {r0-r3, r4, r12, lr}
	ldr r4, [lr, #-4]
	bic r4, r4, #0xff000000	
    ;����97�����жϣ��޷���ֵ	
	cmp r4, #97
	bleq swi97_func
    beq finish_1 	
    ;����98�����жϣ��޷���ֵ	
	cmp r4, #98
	bleq swi98_func
    beq finish_1 
    ;����99�����жϣ��з���ֵ	
	cmp r4, #99
	bleq swi99_func
	add sp, sp, #4
	ldmfd sp!, {r1-r3, r4, r12}
	beq finish_2
	;�ָ��ֳ�	
finish_1	
	ldmfd sp!, {r0-r3, r4, r12}
finish_2
	;���жϷ���
	ldmfd sp!, {pc}^		
	NOP
	NOP
	NOP
	NOP
	NOP
	END