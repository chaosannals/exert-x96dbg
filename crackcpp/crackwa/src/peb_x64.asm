.code
HasPEBBeingDebuggedFlag proc
    ; push ebp
    ; mov esp, ebp
	mov rax, QWORD PTR gs:[60h]
    mov al, BYTE PTR[rax + 2]
    and rax, 11111111b
    ; leave
    ret
HasPEBBeingDebuggedFlag endp

end