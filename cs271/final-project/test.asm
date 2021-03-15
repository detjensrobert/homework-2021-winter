INCLUDE final-project.asm

.DATA

msg_key			BYTE   	"efbcdghijklmnopqrstuvwxyza"
message			BYTE   	"the contents of this message will be a mystery.",0
dest				DWORD		0

.CODE

main PROC
	mWrite  			"Original string:  "
	mWriteString 	OFFSET message
	call 					Crlf

	mov 					dest, -1
	push 					OFFSET msg_key
	push 					OFFSET message
	push 					OFFSET dest
	call					compute

	mWrite				"Encrypted string: "
	mWriteString 	OFFSET message
	call 					Crlf

	mov 					dest, -2
	push 					OFFSET msg_key
	push 					OFFSET message
	push 					OFFSET dest
	call					compute

	mWrite 				"Decrypted string: "
	mWriteString 	OFFSET message
	call 					Crlf

	mov 					dest, 0
	push 					10
	push 					25
	push					OFFSET dest
	call 					compute

	mWrite				"Decoy sum (= 35): "
	mov 					eax, dest
	call					WriteDec
	call					Crlf

	exit
main ENDP

END main
