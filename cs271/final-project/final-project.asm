TITLE CS 271 Final Project (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:					3/14/21
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:			Final
; Description:						En/decrypt a string accepting parameters on the stack, while providing decoy functionality.

INCLUDE Irvine32.inc
INCLUDE Macros.inc

.CODE

; == decoy(*dest, a, b) ==
; @param	dest	address to store result in
; @param 	a			Value to add
; @param 	b			Value to add
decoy PROC,	d:PTR DWORD, a:WORD, b:WORD

	mov 			edi, d

	mov 			eax, 0
	mov				ax, a
	add				ax, b

	mov 			[edi], eax

	ret
decoy ENDP

; == encode(*msg, *key) ==
; @param 	msg			String to encrypt in-place
; @param 	key			Cipherstring to encrpt with
encode PROC, msg:PTR BYTE, key:PTR BYTE
	cld

	; ecx = strlen(msg)
	invoke 	Str_length, msg
	mov 		ecx, eax

	mov 		ebx, key

	mov			esi, msg
	mov			edi, msg

	encode_loop:
		mov 		eax, 0
		lodsb		; load character from *msg
		cmp 		al, 0 ; break if null character reached (EOS)
		je			encode_exit

		; skip if not a letter
		cmp 		al, 97
		jl 			not_letter
		cmp 		al, 122
		jg 			not_letter
		; if (char >= a && char <= z)
			sub			al, 97
			mov 		al, [ebx + eax]

		not_letter:
		stosb		; store encoded character to *msg

		loop 		encode_loop
	encode_exit:

	ret
encode ENDP

; == decode(*msg, *key) ==
; @param 	msg			String to decrypt in-place
; @param 	key			Cipherstring to encrpt with
decode PROC, msg:PTR BYTE, key:PTR BYTE
	cld

	; ecx = strlen(msg)
	invoke 	Str_length, msg
	mov 		ecx, eax

	mov 		ebx, key

	mov			esi, msg
	mov			edi, msg

	decode_loop:
		mov 		eax, 0
		lodsb		; load character from *msg
		cmp 		al, 0 ; break if null character reached (EOS)
		je			decode_exit

		; skip if not a letter
		cmp 		al, 97
		jl 			not_letter
		cmp 		al, 122
		jg 			not_letter
		; if (char >= a && char <= z)
			; search key for index of cipherchar
			push 		edi
			push 		ecx

			mov 		edi, key
			mov 		ecx, 26
			repne		scasb ; scan edi (key) for al

			mov 		eax, edi
			sub			eax, key
			add 		eax, 96

			pop 		ecx
			pop 		edi
		not_letter:
		stosb		; store encoded character to *msg

		loop 		decode_loop
	decode_exit:

	ret
decode ENDP

; == compute(*dest, a, b) ==
; Based on inital value of `dest`, perform different functions
;	@param	dest	Destination for regular operation, or if initial value is:
; 								-1:   encode string (char*)a with keystring (char*)b
; 								-2:   decode string (char*)a with keystring (char*)b
; 								-3:   generate 26-char keystring into (char*)a
;								  else: add (int)a to (int)b and store into (int)dest
; @param 	a			Value to add or char array pointer
; @param 	b			Value to add or char array pointer
compute PROC
  enter     0,0

	; check mode argument
	mov 			ebx, [ebp + 8] ; *type
	mov 			eax, [ebx]
	cmp 			eax, -1
	jne				not_encode
		; if mode == -1, encrypt
		invoke		encode, [ebp + 12], [ebp + 16]
		leave
		ret 12
	not_encode:

	cmp 			eax, -2
	jne				not_decode
		; if mode == -2, decrypt
		invoke		decode, [ebp + 12], [ebp + 16]
		leave
		ret 12
	not_decode:

	; defaut decoy case
	; invoke		decoy, ebx, [ebp + 12], [ebp + 14]

	push [ebp + 14]
	push [ebp + 12]
	push ebx
	call decoy

	leave
	ret 10
compute ENDP
