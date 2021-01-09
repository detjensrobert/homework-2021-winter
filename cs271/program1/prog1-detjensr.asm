TITLE CS 271 Assignment 1 (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:          1/7/21
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:      1 (due 1/17)
; Description:            Perform math ops on entered numbers.

INCLUDE Irvine32.inc

.DATA

; STRING CONSTANTS:

greeting    BYTE "PROGRAM 1: Basic Arithmetic - Robert Dejens", 0

ec_size     BYTE "**EC: enforce $FIRST >= $SECOND", 0
ec_square   BYTE "**EC: squares both numbers", 0

prompt1     BYTE "Enter the first number: ", 0
prompt2     BYTE "Enter the second number: ", 0

size_err    BYTE "The first number must be larger than the second!", 0

add_str     BYTE " + ", 0
sub_str     BYTE " - ", 0
mul_str     BYTE " * ", 0
div_str     BYTE " / ", 0
rem_str     BYTE " rem ", 0
sqa_str     BYTE " ** 2", 0
eql_str     BYTE " = ", 0

farewell    BYTE "Goodbye! Farewell! Adios!", 0

; VARIABLES:

num1      DWORD 0
num2      DWORD 0

.CODE
main PROC

  ; print greeting string
  mov     edx, offset greeting
  call    WriteString
  call    Crlf

  ; print extra credit flags
  mov     edx, offset ec_size
  call    WriteString
  call    Crlf
  mov     edx, offset ec_square
  call    WriteString
  call    Crlf

  call    Crlf

  ; prompt/get first number
  mov     edx, offset prompt1
  call    WriteString
  call    ReadInt
  mov     num1, eax

  ; prompt/get second number
  mov     edx, offset prompt2
  call    WriteString
  call    ReadInt
  mov     num2, eax

  call    Crlf

  ; EXTRA CREDIT:
  ; make sure the first number is larger
  mov     eax, num1
  .IF eax < num2
    mov   edx, offset size_err
    call  WriteString
    call  Crlf
    exit
  .ENDIF

  ; add 'em
  mov     eax, num1
  call    WriteDec
  mov     edx, offset add_str
  call    WriteString
  mov     eax, num2
  call    WriteDec
  mov     edx, offset eql_str
  call    WriteString

  mov     eax, num1
  add     eax, num2
  call    WriteDec
  call    Crlf


  ; subtract 'em
  mov     eax, num1
  call    WriteDec
  mov     edx, offset sub_str
  call    WriteString
  mov     eax, num2
  call    WriteDec
  mov     edx, offset eql_str
  call    WriteString

  mov     eax, num1
  sub     eax, num2
  call    WriteDec
  call    Crlf


  ; multiply 'em
  mov     eax, num1
  call    WriteDec
  mov     edx, offset mul_str
  call    WriteString
  mov     eax, num2
  call    WriteDec
  mov     edx, offset eql_str
  call    WriteString

  mov     eax, num1
  mul     num2
  call    WriteDec
  call    Crlf


  ; divide 'em
  mov     eax, num1
  call    WriteDec
  mov     edx, offset div_str
  call    WriteString
  mov     eax, num2
  call    WriteDec
  mov     edx, offset eql_str
  call    WriteString

  mov     eax, num1
  mov     edx, 0
  div     num2
  call    WriteDec ; quotient already in eax
  mov     eax, edx  ; remainder in edx, move so can print str
  mov     edx, offset rem_str
  call    WriteString
  call    WriteDec
  call    Crlf


  call    Crlf

  ; EXTRA CREDIT:
  ; square 'em
  mov     eax, num1
  call    WriteDec
  mov     edx, offset sqa_str
  call    WriteString
  mov     edx, offset eql_str
  call    WriteString

  mov     eax, num1
  mul     num1
  call    WriteDec
  call    Crlf

  mov     eax, num2
  call    WriteDec
  mov     edx, offset sqa_str
  call    WriteString
  mov     edx, offset eql_str
  call    WriteString

  mov     eax, num2
  mul     num2
  call    WriteDec
  call    Crlf

  call    Crlf

  ; print farewell string
  mov     edx, offset farewell
  call    WriteString
  call    Crlf

  exit
main ENDP

END main
