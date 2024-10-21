global flush_tlb_entry
global enable_paging

flush_tlb_entry:
	cli
	mov eax, [esp + 4]
	invlpg [eax]
	sti

enable_paging:
	mov cr0, eax
	mov ecx, [esp + 4]
	cmp ecx, 1
	je enable
	jne disable
	ret

enable:
	or eax, 0x80000000
	mov eax, cr0
	mov eax, [esp + 8]
	mov cr3, eax
	ret

disable:
	and eax, 0x7FFFFFFF
	mov cr0, eax
	ret
