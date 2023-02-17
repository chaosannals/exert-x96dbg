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

HasPEBNtGlobalFlag proc
    mov rax, QWORD PTR gs:[60h]
    mov al, BYTE PTR[rax + 0bch]
    and rax, 70h
    ret
HasPEBNtGlobalFlag endp

end