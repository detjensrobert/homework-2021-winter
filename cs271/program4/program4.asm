TITLE CS 271 Assignment 4 (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:          2/14/21
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:      4
; Description:            Displays cumulative composite numbers up to a inputted number after verifying user input.

INCLUDE Irvine32.inc
INCLUDE Macros.inc

UPPER_LIMIT     =   300

.DATA

user_input      DWORD   ?
current_number  DWORD   ?
current_sqrt    DWORD   ?
printed         DWORD   0

.CODE
; (insert additional procedures here)

main PROC
  call        info

  call        get_input

  call        show_composites

  call        goodbye
  exit
main ENDP

; prints greeting and program info
; @pre:   none
; @post:  no changes
info PROC
  mWriteLn    "PROGRAM 4: Composite Numbers - Robert Detjens"

  mWrite      "This program can generate a list of up to "
  mov         eax, UPPER_LIMIT
  call        WriteDec
  mWriteLn    " composite numbers."

  ret
info ENDP

; Gets valid user input and stores in global `user_input`
; @pre:   none
; @post:  Valid user input stored in `user_input`
;         EAX modified
get_input PROC
  jmp         prompt
  badinput:
  mWriteLn    "ERR: out of range"
  prompt:
  mWrite      "Enter the upper limit for a set of numbers to generate [1.."
  mov         eax, UPPER_LIMIT
  call        WriteDec
  mWrite      "]: "

  call        ReadInt
  jo          prompt  ; if input is not integer (overflow set), reprompt immediately

  call        validate_input
  jo          badinput

  mov         user_input, eax

  ret
get_input ENDP

; checks if EAX is valid in range, sets overflow flag if not
; @pre:   unsigned int in EAX
; @post:  Overflow flag set if not in bounds
;         EAX modified
validate_input PROC
  cmp         eax, 1  ; lower bound
  jl          bad

  cmp         eax, UPPER_LIMIT  ; upper bound
  jg          bad

  ret

  bad:
  ; set overflow flag
  mov         al,7Fh
  inc         al

  ret
validate_input ENDP

; prints all composite numbers from 1 to `user_input` (first one is 4)
; @pre:   unsigned integer in `user_input` -- upper bound to go to
; @post:  EAX, EBX, EDX modified
;         `user_input` modified
show_composites PROC
  mov         current_number, 4

  show_loop:
  call        is_composite
  jno         dont_print

  mov         eax, current_number
  call        WriteDec
  mWrite      "     "
  inc         printed

  ; eax % 10 == 0 ? print \n : dont
  mov         eax, printed
  mov         ebx, 10
  cdq
  div         ebx
  cmp         edx, 0
  jne         dont_print
  call        Crlf

  dont_print:
  inc         current_number
  mov         eax, printed
  cmp         eax, user_input
  jl          show_loop

  ret
show_composites ENDP

; sets overflow flag if ECX is not a composite number
; @pre:   unsigned int in EAX
; @post:  Overflow flag set if not in bounds
;         EAX modified
is_composite PROC

  ; use FPU to calc sqrt of current number
  finit
  fild        current_number
  fsqrt
  fist        current_sqrt

  ; loop over all numbers [2..sqrt(current_number)]
  mov         ecx, 2
  check_loop:

  ; current_number % ECX == 0 ? set overflow & return : keep going
  mov         eax, current_number
  cdq
  div         ecx
  cmp         edx, 0
  je          not_composite

  inc         ecx
  cmp         ecx, current_sqrt
  jle         check_loop

  ret

  not_composite:
  ; set overflow flag
  mov         al,7Fh
  inc         al

  ret
is_composite ENDP

; prints farewell
; @pre:   none
; @post:  no changes
goodbye PROC
  call        Crlf
  mWriteLn    "Goodbye, world!"
  ret
goodbye ENDP

END main  ; entrypoint
