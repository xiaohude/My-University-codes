DATA    SEGMENT
   var1   dw  2    dup(0)                   ;申请两个字大小的空间，（占4个字节）初始化为0
   var2   db  1,2,3,4,5,6,7,8,9,10,11       ；申请字节串，1，2，3，4，5，6，7，8，9，10，11
   org 18				    ；直接跳到偏移地址第18个位置。
   var3   db  10   dup(0,1,2 dup(4),5)      ；偏移地址从18到67.内容重复10次（0，1，4，4，5）
   var   dw  var2			    ；存上var2的偏移地址。大地址存大地址
   string db "Hello World!" ,'$','$'
   count equ $-string
   string0 db 20 dup(?)    ;如何实现字符串string到string0的复制？
DATA    ENDS

stack segment stack			    ；堆栈段
   dw 100 dup(?)
stack ends

code segment
  assume cs:code,ds:data,es:data,ss:stack
start:
  mov ax,data				    ；不区分大小写
  mov ds,ax
  mov es,ax    
  mov dx,offset string
  lea di,var3
  lea di,string0
  mov dl,0ah
  mov ah,2
  int 21h
 
 
  lea si,string
  mov cx,count
  rep movsb
  mov dx,offset string0
  mov ah,9
  int 21h
  mov ah,4ch           ;返回DOS
  int 21h
code ends
  end start

