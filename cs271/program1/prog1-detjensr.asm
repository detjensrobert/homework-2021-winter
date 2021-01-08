TITLE CS 271 Assignment 1 (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:			1 (due 1/17)
; Description:						Perform math ops on entered numbers.

INCLUDE Irvine32.inc

.data
greeting  BYTE "PROGRAM 1: Basic Arithmetic - Robert Dejens", 0

prompt1		BYTE "Enter the first number: ", 0
prompt2		BYTE "Enter the second number: ", 0

add_str   BYTE " + ", 0
sub_str   BYTE " - ", 0
mul_str   BYTE " * ", 0
div_str   BYTE " / ", 0
rem_str   BYTE " rem ", 0
eql_str   BYTE " = ", 0

farewell  BYTE "Goodbye! Farewell! Adios!", 0

num1      DWORD 0
num2      DWORD 0

.code
main PROC

  ; print greeting string
  mov edx, offset greeting
  call WriteString
  call Crlf
  call Crlf

  ; prompt/get first number
  mov edx, offset prompt1
  call WriteString
  call ReadInt
  mov num1, eax

  ; prompt/get second number
  mov edx, offset prompt2
  call WriteString
  call ReadInt
  mov num2, eax

  call Crlf


  ; add 'em
  mov eax, num1
  call WriteDec
  mov edx, offset add_str
  call WriteString
  mov eax, num2
  call WriteDec
  mov edx, offset eql_str
  call WriteString

  mov eax, num1
  add eax, num2
  call WriteDec
  call Crlf


  ; subtract 'em
  mov eax, num1
  call WriteDec
  mov edx, offset sub_str
  call WriteString
  mov eax, num2
  call WriteDec
  mov edx, offset eql_str
  call WriteString

  mov eax, num1
  sub eax, num2
  call WriteDec
  call Crlf


  ; multiply 'em
  mov eax, num1
  call WriteDec
  mov edx, offset mul_str
  call WriteString
  mov eax, num2
  call WriteDec
  mov edx, offset eql_str
  call WriteString

  mov eax, num1
  mul num2
  call WriteDec
  call Crlf


  ; divide 'em
  mov eax, num1
  call WriteDec
  mov edx, offset div_str
  call WriteString
  mov eax, num2
  call WriteDec
  mov edx, offset eql_str
  call WriteString

  mov eax, num1
  mov edx, 0
  div num2
  call WriteDec ; quotient already in eax
  mov eax, edx  ; remainder in edx, move so can print str
  mov edx, offset rem_str
  call WriteString
  call WriteDec
  call Crlf


  ; (stick 'em in a stew)

  call Crlf

  ; print farewell string
  mov edx, offset farewell
  call WriteString
  call Crlf

	exit
main ENDP

END main
