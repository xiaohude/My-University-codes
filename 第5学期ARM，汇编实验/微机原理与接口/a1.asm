DATA    SEGMENT
   var1   dw  2    dup(0)                   ;���������ִ�С�Ŀռ䣬��ռ4���ֽڣ���ʼ��Ϊ0
   var2   db  1,2,3,4,5,6,7,8,9,10,11       �������ֽڴ���1��2��3��4��5��6��7��8��9��10��11
   org 18				    ��ֱ������ƫ�Ƶ�ַ��18��λ�á�
   var3   db  10   dup(0,1,2 dup(4),5)      ��ƫ�Ƶ�ַ��18��67.�����ظ�10�Σ�0��1��4��4��5��
   var   dw  var2			    ������var2��ƫ�Ƶ�ַ�����ַ����ַ
   string db "Hello World!" ,'$','$'
   count equ $-string
   string0 db 20 dup(?)    ;���ʵ���ַ���string��string0�ĸ��ƣ�
DATA    ENDS

stack segment stack			    ����ջ��
   dw 100 dup(?)
stack ends

code segment
  assume cs:code,ds:data,es:data,ss:stack
start:
  mov ax,data				    �������ִ�Сд
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
  mov ah,4ch           ;����DOS
  int 21h
code ends
  end start

