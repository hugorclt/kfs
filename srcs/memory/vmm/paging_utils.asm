global flush_tlb_entry
global enable_paging

flush_tlb_entry:
	cli
	mov eax, [esp + 4]
	invlpg [eax]
	sti

; enable_paging:
; 	mov ecx, [esp + 4]
; 	cmp ecx, 1
; 	je enable
; 	jne disable
; 	ret

; enable:
; 	mov eax, cr0
; 	or eax, 0x80000000
; 	mov cr0, eax
; 	mov eax, [esp + 8]
; 	mov cr3, eax
; 	ret

; disable:
; 	and eax, 0x7FFFFFFF
; 	mov cr0, eax
; 	ret

enable_paging:
    mov eax, [esp + 4]    ; 1st parameter : pointer to the page directory
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000000  ; set the PG bit
    mov cr0, eax
    ret
