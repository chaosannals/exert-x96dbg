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
    
HasHeapFlagByPEB proc
    mov rax, QWORD PTR gs:[60h]
    mov rax, QWORD PTR [rax + 18h]
    mov rax, QWORD PTR [rax + 10h] ; 定位的字段好像不对，这个位移排排序链表头
    ret
HasHeapFlagByPEB endp

AxDivZero proc
    xor rax, rax;
    div rax
    ret
AxDivZero endp

end