TITLE CS 271 Assignment 5 (Robert Detjens)

; Author:                 Robert Detjens
; Last Modified:					2/28/21
; OSU email address:      detjensr@oregonstate.edu
; Course number/section:  CS 271 (001)
; Assignment Number:			5
; Description:						Using procedures and parameter passing to generate,
;                         sort, and analyse an array of random numbers.

INCLUDE Irvine32.inc
INCLUDE Macros.inc

INPUT_MIN		  =		15
INPUT_MAX		  =		200

RANDOM_MIN	  =		100
RANDOM_MAX	  =		999

.DATA

count					DWORD   0
numbers				DWORD		INPUT_MAX DUP(0)

str_unsorted	BYTE		"Unsorted:", 0
str_sorted		BYTE		"After sorting:", 0

.CODE

main PROC

  call      info

  push      OFFSET count
  call      get_data

  push      count
  push      OFFSET numbers
  call      fill_array

  push      OFFSET str_unsorted
  push      count
  push      OFFSET numbers
  call      show_list

  push      count
  push      OFFSET numbers
  call      sort_list

  push      count
  push      OFFSET numbers
  call      show_median

  push      OFFSET str_sorted
  push      count
  push      OFFSET numbers
  call      show_list

  exit	; exit to operating system
main ENDP

; -- info() --
; Prints information about the program and seeds the RNG.
;   @pre:   (none)
;   @post:  (none)
info PROC
  mWriteLn  "PROGRAM 5: Random Integer Sort - Robert Detjens"
  call      Crlf

  mWriteLn  "This program generates random numbers in the range [100..999],"
  mWriteLn  "display the original list, sorts the list, and calculates the"
  mWriteLn  "median value. Finally, it displays the list sorted in"
  mWriteLn  "descending order."
  call      Crlf

  ; seed RNG once
  call      Randomize

  ret
info ENDP

; -- get_data(*input) --
; Prompts the user for a range between INPUT_MIN and INPUT_MAX and stores that into `input`.
;   @param: input   pointer to store the valid user data into
;
;   @pre:   arguments pushed onto stack
;   @post:  value at `input` updated with user input
get_data PROC
  enter       0,0
  jmp         prompt

  badinput:
  mWriteLn    "[ ERR ] Bad input"

  prompt:
  mWrite      "Enter the upper limit for a set of numbers to generate ["
  mov         eax, INPUT_MIN
  call        WriteDec
  mWrite      ".."
  mov         eax, INPUT_MAX
  call        WriteDec
  mWrite      "]: "

  call        ReadInt
  jo          prompt  ; if input is not integer (overflow set), reprompt immediately

  cmp         eax, INPUT_MIN
  jl          badinput

  cmp         eax, INPUT_MAX
  jg          badinput

  mov         esi, [ebp + 8]  ; *input
  mov         [esi], eax

  leave
  ret         4   ; 1 parameter * 4 bytes
get_data ENDP

; -- fill_array(*arr, len) --
; Fills the given array `arr` with `len` random numbers.
;   @param: arr   pointer to start of array
;   @param: len   length of `arr`
;
;   @pre:   arguments pushed onto stack
;   @pre:   `arr` is large enough to store `len` values
;   @post:  `len` values stored in `arr`
fill_array PROC
  enter       0,0

  mov         edi, [ebp + 8]    ; *arr
  mov         ecx, [ebp + 12]   ; length

  cld         ; iterate in forward direction

  ; range: [0..(MAX - MIN + 1)] + MIN
  mov         ebx, RANDOM_MAX
  sub         ebx, RANDOM_MIN
  inc         ebx

  fill_loop:
    mov         eax, ebx
    call        RandomRange
    add         eax, RANDOM_MIN
    stosd       ; store EAX to [EDI++]
  loop        fill_loop  ; while ECX > 0

  leave
  ret         8
fill_array ENDP

; -- show_list(*arr, length, *title) --
; Prints `title` and the contents of array `arr` as unsigned DWORDs (10 per line).
;   @param: arr     pointer to start of array
;   @param: len     length of `arr`
;   @param: title   pointer to string
;
;   @pre:   arguments pushed onto stack
;   @pre:   `arr` has data
;   @post:  (none)
show_list PROC
  enter       0,0

  ; print title arg
  mov         edx, [ebp + 16]  ; *title
  call        WriteString
  call        Crlf

  mov         esi, [ebp + 8]    ; *arr
  mov         ecx, [ebp + 12]   ; length

  mov         ebx, 0  ; number of elems printed per line

  cld         ; iterate in forward direction

  print_loop:
    lodsd       ; load EAX from [ESI++]
    call        WriteDec
    mWriteSpace 5

    inc         ebx
    cmp         ebx, 10
    jl          no_newline
      ; if ECX >= 10
      mov         ebx, 0
      call        Crlf
    no_newline:
  loop        print_loop  ; while ECX > 0

  call        Crlf

  leave
  ret         12  ; 3 args * 4 bytes
show_list ENDP

; -- sort_list(*arr, length) --
; Sorts `arr` descending in-place.
;   @param: arr   pointer to start of array
;   @param: len   length of `arr`
;
;   @pre:   arguments pushed onto stack
;   @pre:   `arr` has data
;   @post:  contents of `arr` has been sorted
sort_list PROC
  enter   0,0

  ; for (i = 0; i < length - 1; i++)
  mov     ecx, [ebp + 12]  ; length
  dec     ecx
  outer:
    push    ecx

    ; for (j = 0; j < length - 1; j++)
    mov     ecx, [ebp + 12]  ; length
    dec     ecx
    mov     esi, [ebp + 8]   ; *arr
    inner:

      lodsd   ; load EAX from [ESI++]
      cmp     eax, [esi]
      jge     no_swap
        ; if arr[i] < arr[i+1]
        push    esi  ; save current esi
        push    esi
        sub     esi, 4
        push    esi  ; esi - 4 (previous elem)
        call    swap_elems
        pop     esi  ; restore old esi
      no_swap:
    loop    inner

    pop     ecx
  loop    outer

  leave
  ret     8
sort_list ENDP

; -- swap_elems(*a, *b) --
; Swaps the data at each arg with the other.
;   @param: a   pointer to first value to swap
;   @param: b   pointer to second value to swap
;
;   @pre:   arguments pushed onto stack
;   @post:  values have been swapped
swap_elems PROC
  enter   0,0

  mov     esi, [ebp + 8]
  mov     edi, [ebp + 12]

  push    [esi]
  push    [edi]

  pop     [esi]
  pop     [edi]

  leave
  ret     8
swap_elems ENDP

; -- show_median(*arr, length) --
; Calculates and prints median value of array `arr`.
;   @param: arr   pointer to start of array
;   @param: len   length of `arr`
;
;   @pre:   arguments pushed onto stack
;   @pre:   `arr` has data
;   @pre:   `arr` has been sorted
;   @post:  (none)
show_median PROC
  enter     0,0

  mov       eax, [ebp + 12]  ; length
  mov       esi, [ebp + 8]   ; *arr

  mov       ebx, 2
  cdq
  div       ebx
  ; EAX = length / 2, EDX = length % 2

  mov       ebx, [esi + eax*sizeof DWORD]

  cmp       edx, 0
  jne       no_avg
    ; if length % 2 == 0
    dec       eax
    add       ebx, [esi + eax*sizeof DWORD]
    sar       ebx, 1  ; ebx / 2
  no_avg:

  mWrite    "Median value is: "
  mov       eax, ebx
  call      WriteDec
  call      Crlf

  leave
  ret       8
show_median ENDP

END main  ; entrypoint
