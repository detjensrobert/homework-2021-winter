TITLE CS 271 Assignment 2 (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:					1/14/21
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:			2
; Description:						String input & loops

INCLUDE Irvine32.inc
INCLUDE Macros.inc

.DATA

usn_len			=				20
usn					BYTE		usn_len+1 DUP (?)

fib_n2			DWORD		0
fib_n1			DWORD		1

column			DWORD		1

.CODE
main PROC

	; 	== INTRO ==

  ; print info string
	mWriteLn			"PROGRAM 2: Fibbonaci - Robert Dejens"

	; get username as input
	mWrite				"What is your name? "
	mov						edx, offset usn
	mov 					ecx, usn_len
	call					ReadString

	; greet user
	mWrite				"Howdy, "
	mWriteString 	offset usn
	call					Crlf

	; 	== INSTRUCTIONS ==

  mWriteLn		"How many Fibonacci terms would you like to see?"
	jmp 				getinput

	; 	== GET INFO ==

tryagain:
		mWriteLn 	"That is not a valid input."
getinput:
  mWrite			"Enter a number between 1 and 46: "
  call				ReadInt

	; bounds checking: [1..46]
	mov 				edx, 46
	cmp					edx, eax
	jc					tryagain
	mov 				edx, 1
	cmp					eax, edx
	jc					tryagain

	; 	== DISPLAY SEQUENCE ==

	; create loop counter from input
	mov					ecx, eax

	; first term not generated by loop
	; print manually
	mov					eax, 1
	call				WriteDec
	jmp loopenter

fibloop:
	; add n-1 and n-2 to get n
	mov	 				eax, fib_n1
	add					eax, fib_n2
	call				WriteDec

	; write new values out
	mov 				edx, eax
	mov 				eax, fib_n1
	mov 				fib_n2, eax
	mov 				fib_n1, edx

loopenter:
	mWrite		 	"     "
	; print a new line if we're on column 5
	mov 				eax, 4
	cmp					eax, column
	jnc					skip_nl
	; if column > 4
	mov				column, 0
	call			Crlf
skip_nl:

	inc 				column
	loop 				fibloop

	; 	== GOODBYE ==

	; dismiss user
	call					Crlf
	mWrite				"Farewell, "
	mWriteString 	offset usn
	call					Crlf

	exit
main ENDP

END main