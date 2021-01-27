TITLE CS 271 Assignment 3 (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:					1/26/21
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:			3
; Description:						User input validation and data averages

INCLUDE Irvine32.inc
INCLUDE Macros.inc

USN_LEN					=				20
BOUND_LOWER			=				-100

.DATA

usn							BYTE		USN_LEN+1 DUP (?)

data_count			SDWORD	0
data_avg				SDWORD	0

.CODE
main PROC

	; 	== INTRO ==

  ; print info string
	mWriteLn			"PROGRAM 2: Average - Robert Dejens"

	; get username as input
	mWrite				"What is your name? "
	mov						edx, offset usn
	mov 					ecx, USN_LEN
	call					ReadString

	; greet user
	mWrite				"Salutations, "
	mWriteString 	offset usn
	call					Crlf
	call					Crlf


	;		== INSTRUCTIONS ==

  mWriteLn		"Please enter numbers in the range [-100..-1]."
	mWriteLn		"Enter a non-negative number when finished to see results."
	call 				Crlf


	;		== COLLECT INPUT ==

	; setup registers
	mov					ebx, 0	;	sum
	mov					ecx, 0	;	count
	jmp 				inputloop

badinput:
	mWriteLn		"Invalid number, please enter numbers in [-100..-1]."
inputloop:
	mWrite	 		"Enter number: "
	call				ReadInt

	jo					badinput	; if input is bad (overflow set), reprompt
	jns					inputdone	;	if input is positive (not signed), exit loop

	; check against lower bound
	cmp 				eax, BOUND_LOWER
	jl					badinput

	add					ebx, eax
	inc					ecx

	jmp inputloop


	;		== DISPLAY AVERAGE ==

inputdone:
	call			Crlf

	; if user entered no numbers
	cmp 			ebx, 0
	je				nothing_entered

	; display count
	mWrite		"You entered "
	mov 			eax, ecx
	call			WriteDec
	mWriteLn	" numbers."


	; display sum
	mWrite		"The sum of those numbers is "
	mov 			eax, ebx
	call			WriteInt
	mWriteLn	"."

	; calc average (sum / count)
	mov				eax, ebx
	cdq				; extend eax sign into edx
	idiv			ecx

	; display average
	mWrite		"The rounded average is "
	call			WriteInt
	mWriteLn	"."

	jmp goodbye

nothing_entered:
	mWriteLn	"You didnt enter anything to average!"


	; 	== FAREWELL	==

goodbye:
	; dismiss user
	call					Crlf
	mWrite				"Farewell, "
	mWriteString 	offset usn
	mWriteLn	"."

	exit	; exit to operating system
main ENDP

END main
