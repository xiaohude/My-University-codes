;=========================================
; 2440汇编启动代码
; 初始化，之后跳转到C代码部分
;=========================================

	GET option.inc
	GET memcfg.inc
	GET 2440addr.inc

;Pre-defined constants
USERMODE    EQU 	0x10
FIQMODE     EQU 	0x11
IRQMODE     EQU 	0x12
SVCMODE     EQU 	0x13
ABORTMODE   EQU 	0x17
UNDEFMODE   EQU 	0x1b
MODEMASK    EQU 	0x1f
NOINT       EQU 	0xc0

;The location of stacks
UserStack	EQU	(_STACK_BASEADDRESS-0x3800)	;0x33ff4800 ~
SVCStack	EQU	(_STACK_BASEADDRESS-0x2800)	;0x33ff5800 ~
UndefStack	EQU	(_STACK_BASEADDRESS-0x2400)	;0x33ff5c00 ~
AbortStack	EQU	(_STACK_BASEADDRESS-0x2000)	;0x33ff6000 ~
IRQStack	EQU	(_STACK_BASEADDRESS-0x1000)	;0x33ff7000 ~
FIQStack	EQU	(_STACK_BASEADDRESS-0x0)	;0x33ff8000 ~

 		MACRO
$HandlerLabel HANDLER $HandleLabel

$HandlerLabel
	sub	sp,sp,#4	;decrement sp(to store jump address)
	stmfd	sp!,{r0}	;PUSH the work register to stack(lr does not push because it return to original address)
	ldr     r0,=$HandleLabel;load the address of HandleXXX to r0
	ldr     r0,[r0]	 ;load the contents(service routine start address) of HandleXXX
	str     r0,[sp,#4]      ;store the contents(ISR) of HandleXXX to stack
	ldmfd   sp!,{r0,pc}     ;POP the work register and pc(jump to ISR)
	MEND

	IMPORT  |Image$$RO$$Base|	; Base of ROM code
	IMPORT  |Image$$RO$$Limit|  ; End of ROM code (=start of ROM data)
	IMPORT  |Image$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$ZI$$Limit|  ; to zero initialise

	IMPORT  Main    ; The main entry of mon program

	AREA    Init,CODE,READONLY
	ENTRY
	EXPORT	__ENTRY
__ENTRY
ResetEntry
	b	ResetHandler
	b	HandlerUndef	;handler for Undefined mode
	b	HandlerSWI	;handler for SWI interrupt
	b	HandlerPabort	;handler for PAbort
	b	HandlerDabort	;handler for DAbort
	b	.		;reserved
	b	HandlerIRQ	;handler for IRQ interrupt
	b	HandlerFIQ	;handler for FIQ interrupt

HandlerFIQ      HANDLER HandleFIQ
HandlerIRQ      HANDLER HandleIRQ
HandlerUndef    HANDLER HandleUndef
HandlerSWI      HANDLER HandleSWI
HandlerDabort   HANDLER HandleDabort
HandlerPabort   HANDLER HandlePabort

IsrIRQ
	sub	sp,sp,#4       ;reserved for PC
	stmfd	sp!,{r8-r9}
	ldr	r9,=INTOFFSET
	ldr	r9,[r9]
	ldr	r8,=HandleEINT0
	add	r8,r8,r9,lsl #2
	ldr	r8,[r8]
	str	r8,[sp,#8]
	ldmfd	sp!,{r8-r9,pc}

	LTORG

;=======
; 上电复位启动后从这里开始
;=======
ResetHandler
	ldr	r0,=WTCON       ;watch dog disable
	ldr	r1,=0x0
	str	r1,[r0]

	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff  ;all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7fff		;all sub interrupt disable
	str	r1,[r0]

	;To reduce PLL lock time, adjust the LOCKTIME register.
	ldr	r0,=LOCKTIME
	ldr	r1,=0xffffff
	str	r1,[r0]

	ldr	r0,=CLKDIVN
	ldr	r1,=CLKDIV_VAL		; 0=1:1:1, 1=1:1:2, 2=1:2:2, 3=1:2:4, 4=1:4:4, 5=1:4:8, 6=1:3:3, 7=1:3:6.
	str	r1,[r0]
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000;R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	;Configure UPLL
	ldr	r0,=UPLLCON
	ldr	r1,=((U_MDIV<<12)+(U_PDIV<<4)+U_SDIV)  
	str	r1,[r0]
	nop	; Caution: After UPLL setting, at least 7-clocks delay must be inserted for setting hardware be completed.
	nop
	nop
	nop
	nop
	nop
	nop
	;Configure MPLL
	ldr	r0,=MPLLCON
	ldr	r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV) 
	str	r1,[r0]

	;Set memory control registers
 	adrl	r0, SMRDATA	;be careful!, hzh
	ldr	r1,=BWSCON	;BWSCON Address
	add	r2, r0, #52	;End address of SMRDATA

0
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r2, r0
	bne	%B0

	bl	InitStacks	
;===========================================================	
	ldr	r0, =BWSCON
	ldr	r0, [r0]
	ands	r0, r0, #6		;OM[1:0] != 0, NOR FLash boot
	bne	copy_proc_beg		;do not read nand flash
	adr	r0, ResetEntry		;OM[1:0] == 0, NAND FLash boot
	cmp	r0, #0				;if use Multi-ice, 
	bne	copy_proc_beg		;do not read nand flash for boot
;===========================================================	
nand_boot_beg
	mov	r5, #NFCONF
	;set timing value
	ldr	r0,	=(7<<12)|(7<<8)|(7<<4)
	str	r0,	[r5]
	;enable control
	ldr	r0, =(0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0)
	str	r0, [r5, #4]
	
	bl	ReadNandID
	mov	r6, #0
	ldr	r0, =0xec73
	cmp	r5,	r0
	beq	%F1
	ldr	r0, =0xec75
	cmp	r5, r0
	beq	%F1
	mov	r6, #1
1	
	bl	ReadNandStatus
	
	mov	r8, #0
	ldr	r9, =ResetEntry
2	
	ands	r0, r8, #0x1f
	bne		%F3
	mov		r0, r8
	bl		CheckBadBlk
	cmp		r0, #0
	addne	r8, r8, #32
	bne		%F4
3	
	mov	r0, r8
	mov	r1, r9
	bl	ReadNandPage
	add	r9, r9, #512
	add	r8, r8, #1
4	
	cmp	r8, #256
	bcc	%B2
	
	mov	r5, #NFCONF			;DsNandFlash
	ldr	r0, [r5, #4]
	bic r0, r0, #1
	str	r0, [r5, #4]
	ldr	pc, =copy_proc_beg
;===========================================================
copy_proc_beg
	adr	r0, ResetEntry
	ldr	r2, BaseOfROM
	cmp	r0, r2
	ldreq	r0, TopOfROM
	beq	InitRam	
	ldr r3, TopOfROM
0	
	ldmia	r0!, {r4-r7}
	stmia	r2!, {r4-r7}
	cmp	r2, r3
	bcc	%B0
	
	sub	r2, r2, r3
	sub	r0, r0, r2				
		
InitRam	
	ldr	r2, BaseOfBSS
	ldr	r3, BaseOfZero	
0
	cmp	r2, r3
	ldrcc	r1, [r0], #4
	strcc	r1, [r2], #4
	bcc	%B0	

	mov	r0,	#0
	ldr	r3,	EndOfBSS
1	
	cmp	r2,	r3
	strcc	r0, [r2], #4
	bcc	%B1
;===========================================================
  	; Setup IRQ handler
	ldr	r0,=HandleIRQ       ;This routine is needed
	ldr	r1,=IsrIRQ	  ;if there is not 'subs pc,lr,#4' at 0x18, 0x1c
	str	r1,[r0]

	b Main

;function initializing stacks
InitStacks
	;Do not use DRAM,such as stmfd,ldmfd......
	;SVCstack is initialized before
	;Under toolkit ver 2.5, 'msr cpsr,r1' can be used instead of 'msr cpsr_cxsf,r1'
	mrs	r0,cpsr
	bic	r0,r0,#MODEMASK
	orr	r1,r0,#UNDEFMODE|NOINT
	msr	cpsr_cxsf,r1		;UndefMode
	ldr	sp,=UndefStack		; UndefStack=0x33FF_5C00

	orr	r1,r0,#ABORTMODE|NOINT
	msr	cpsr_cxsf,r1		;AbortMode
	ldr	sp,=AbortStack		; AbortStack=0x33FF_6000

	orr	r1,r0,#IRQMODE|NOINT
	msr	cpsr_cxsf,r1		;IRQMode
	ldr	sp,=IRQStack		; IRQStack=0x33FF_7000

	orr	r1,r0,#FIQMODE|NOINT
	msr	cpsr_cxsf,r1		;FIQMode
	ldr	sp,=FIQStack		; FIQStack=0x33FF_8000

	bic	r0,r0,#MODEMASK|NOINT
	orr	r1,r0,#SVCMODE
	msr	cpsr_cxsf,r1		;SVCMode
	ldr	sp,=SVCStack		; SVCStack=0x33FF_5800

	;USER mode has not be initialized.

	mov	pc,lr
	;The LR register will not be valid if the current mode is not SVC mode.
;===========================================================
ReadNandID
	mov      r7,#NFCONF
	ldr      r0,[r7,#4]		;NFChipEn();
	bic      r0,r0,#2
	str      r0,[r7,#4]
	mov      r0,#0x90		;WrNFCmd(RdIDCMD);
	strb     r0,[r7,#8]
	mov      r4,#0			;WrNFAddr(0);
	strb     r4,[r7,#0xc]
1							;while(NFIsBusy());
	ldr      r0,[r7,#0x20]
	tst      r0,#1
	beq      %B1
	ldrb     r0,[r7,#0x10]	;id  = RdNFDat()<<8;
	mov      r0,r0,lsl #8
	ldrb     r1,[r7,#0x10]	;id |= RdNFDat();
	orr      r5,r1,r0
	ldr      r0,[r7,#4]		;NFChipDs();
	orr      r0,r0,#2
	str      r0,[r7,#4]
	mov		 pc,lr	
	
ReadNandStatus
	mov		 r7,#NFCONF
	ldr      r0,[r7,#4]		;NFChipEn();
	bic      r0,r0,#2
	str      r0,[r7,#4]
	mov      r0,#0x70		;WrNFCmd(QUERYCMD);
	strb     r0,[r7,#8]	
	ldrb     r1,[r7,#0x10]	;r1 = RdNFDat();
	ldr      r0,[r7,#4]		;NFChipDs();
	orr      r0,r0,#2
	str      r0,[r7,#4]
	mov		 pc,lr

WaitNandBusy
	mov      r0,#0x70		;WrNFCmd(QUERYCMD);
	mov      r1,#NFCONF
	strb     r0,[r1,#8]
1							;while(!(RdNFDat()&0x40));	
	ldrb     r0,[r1,#0x10]
	tst      r0,#0x40
	beq		 %B1
	mov      r0,#0			;WrNFCmd(READCMD0);
	strb     r0,[r1,#8]
	mov      pc,lr

CheckBadBlk
	mov		r7, lr
	mov		r5, #NFCONF
	
	bic      r0,r0,#0x1f	;addr &= ~0x1f;
	ldr      r1,[r5,#4]		;NFChipEn()
	bic      r1,r1,#2
	str      r1,[r5,#4]

	mov      r1,#0x50		;WrNFCmd(READCMD2)
	strb     r1,[r5,#8]
	mov      r1, #5;6		;6->5
	strb     r1,[r5,#0xc]	;WrNFAddr(5);(6) 6->5
	strb     r0,[r5,#0xc]	;WrNFAddr(addr)
	mov      r1,r0,lsr #8	;WrNFAddr(addr>>8)
	strb     r1,[r5,#0xc]
	cmp      r6,#0			;if(NandAddr)		
	movne    r0,r0,lsr #16	;WrNFAddr(addr>>16)
	strneb   r0,[r5,#0xc]
	
;	bl		WaitNandBusy	;WaitNFBusy()
	;do not use WaitNandBusy, after WaitNandBusy will read part A!
	mov	r0, #100
1
	subs	r0, r0, #1
	bne	%B1
2
	ldr	r0, [r5, #0x20]
	tst	r0, #1
	beq	%B2	

	ldrb	r0, [r5,#0x10]	;RdNFDat()
	sub		r0, r0, #0xff
	
	mov      r1,#0			;WrNFCmd(READCMD0)
	strb     r1,[r5,#8]
	
	ldr      r1,[r5,#4]		;NFChipDs()
	orr      r1,r1,#2
	str      r1,[r5,#4]
	
	mov		pc, r7
	
ReadNandPage
	mov		 r7,lr
	mov      r4,r1
	mov      r5,#NFCONF

	ldr      r1,[r5,#4]		;NFChipEn()
	bic      r1,r1,#2
	str      r1,[r5,#4]	

	mov      r1,#0			;WrNFCmd(READCMD0)
	strb     r1,[r5,#8]	
	strb     r1,[r5,#0xc]	;WrNFAddr(0)
	strb     r0,[r5,#0xc]	;WrNFAddr(addr)
	mov      r1,r0,lsr #8	;WrNFAddr(addr>>8)
	strb     r1,[r5,#0xc]	
	cmp      r6,#0			;if(NandAddr)		
	movne    r0,r0,lsr #16	;WrNFAddr(addr>>16)
	strneb   r0,[r5,#0xc]
	
	ldr      r0,[r5,#4]		;InitEcc()
	orr      r0,r0,#0x10
	str      r0,[r5,#4]
	
	bl       WaitNandBusy	;WaitNFBusy()
	
	mov      r0,#0			;for(i=0; i<512; i++)
1
	ldrb     r1,[r5,#0x10]	;buf[i] = RdNFDat()
	strb     r1,[r4,r0]
	add      r0,r0,#1
	bic      r0,r0,#0x10000
	cmp      r0,#0x200
	bcc      %B1
	
	ldr      r0,[r5,#4]		;NFChipDs()
	orr      r0,r0,#2
	str      r0,[r5,#4]
		
	mov		 pc,r7
;===========================================================

	LTORG

;GCS0->SST39VF1601
;GCS1->16c550
;GCS2->IDE
;GCS3->CS8900
;GCS4->DM9000
;GCS5->CF Card
;GCS6->SDRAM
;GCS7->unused

SMRDATA DATA
; Memory configuration should be optimized for best performance
; The following parameter is not optimized.
; Memory access cycle parameter strategy
; 1) The memory settings is  safe parameters even at HCLK=75Mhz.
; 2) SDRAM refresh period is for HCLK<=75Mhz.

	DCD (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
	DCD ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))   ;GCS0
	DCD ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))   ;GCS1
	DCD ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))   ;GCS2
	DCD ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))   ;GCS3
	DCD ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))   ;GCS4
	DCD ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))   ;GCS5
	DCD ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))    ;GCS6
	DCD ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))    ;GCS7
	DCD ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Tsrc<<18)+(Tchr<<16)+REFCNT)

	DCD 0x32	    ;SCLK power saving mode, BANKSIZE 128M/128M

	DCD 0x30	    ;MRSR6 CL=3clk
	DCD 0x30	    ;MRSR7 CL=3clk
	
BaseOfROM	DCD	|Image$$RO$$Base|
TopOfROM	DCD	|Image$$RO$$Limit|
BaseOfBSS	DCD	|Image$$RW$$Base|
BaseOfZero	DCD	|Image$$ZI$$Base|
EndOfBSS	DCD	|Image$$ZI$$Limit|
	

	ALIGN

	AREA RamData, DATA, READWRITE

	^   _ISR_STARTADDRESS		; _ISR_STARTADDRESS=0x33FF_FF00
HandleReset 	#   4
HandleUndef 	#   4
HandleSWI		#   4
HandlePabort    #   4
HandleDabort    #   4
HandleReserved  #   4
HandleIRQ		#   4
HandleFIQ		#   4

;Do not use the label 'IntVectorTable',
;The value of IntVectorTable is different with the address you think it may be.
;IntVectorTable
;@0x33FF_FF20
HandleEINT0		#   4
HandleEINT1		#   4
HandleEINT2		#   4
HandleEINT3		#   4
HandleEINT4_7	#   4
HandleEINT8_23	#   4
HandleCAM		#   4		; Added for 2440.
HandleBATFLT	#   4
HandleTICK		#   4
HandleWDT		#   4
HandleTIMER0 	#   4
HandleTIMER1 	#   4
HandleTIMER2 	#   4
HandleTIMER3 	#   4
HandleTIMER4 	#   4
HandleUART2  	#   4
;@0x33FF_FF60
HandleLCD 		#   4
HandleDMA0		#   4
HandleDMA1		#   4
HandleDMA2		#   4
HandleDMA3		#   4
HandleMMC		#   4
HandleSPI0		#   4
HandleUART1		#   4
HandleNFCON		#   4		; Added for 2440.
HandleUSBD		#   4
HandleUSBH		#   4
HandleIIC		#   4
HandleUART0 	#   4
HandleSPI1 		#   4
HandleRTC 		#   4
HandleADC 		#   4
;@0x33FF_FFA0
	END
