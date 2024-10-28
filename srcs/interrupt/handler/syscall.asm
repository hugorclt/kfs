global	syscall_handler_wrapper
extern	syscall_handler

; syscall_handler_wrapper:
; 	pushad
; 	push ds
; 	push fs
; 	push gs
; 	push es

; 	mov ax, 0x10 ; kernel data seg
; 	mov ds, ax
; 	mov es, ax
; 	mov fs, ax
; 	mov gs, ax

; 	push edi
; 	push esi
; 	push edx
; 	push ecx
; 	push ebx
; 	push eax
; 	call syscall_handler

; 	pop es
; 	pop gs
; 	pop fs
; 	pop ds

; 	popad
; 	iretd

syscall_handler_wrapper:
	dd syscall_handler_test

syscall_handler_test:
    ; Save registers and segment registers
    push eax      ; Save eax (will hold the syscall number)
    push gs       ; Save gs segment register
    push fs       ; Save fs segment register
    push es       ; Save es segment register
    push ds       ; Save ds segment register

    ; Save general-purpose registers
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push esp            ; Push pointer to pt_regs structure

    ; Call the C function to handle the syscall
    call syscall_handler

    ; Clean up the stack (remove the pointer we pushed)
    add esp, 4

    ; Restore general-purpose registers
    pop ebx             ; Restore ebx
    pop ecx             ; Restore ecx
    pop edx             ; Restore edx
    pop esi             ; Restore esi
    pop edi             ; Restore edi
    pop ebp             ; Restore ebp



    ; Restore segment registers
    pop ds              ; Restore ds
    pop es              ; Restore es
    pop fs              ; Restore fs
    pop gs              ; Restore gs

    ; Final cleanup and return from interrupt
    add esp, 4          ; Remove extra stack space for old eax
    iretd               ; Return to user space
