.386
.model flat,stdcall
option casemap:NONE

.code
HasPEBBeingDebuggedFlag proc
    ; push ebp
    ; mov esp, ebp
    ASSUME fs:NOTHING
	mov eax, fs:[30h]
    ASSUME fs:ERROR
    mov al, BYTE PTR[eax + 2]
    and eax, 11111111b
    ; leave
    ret
HasPEBBeingDebuggedFlag endp

HasPEBNtGlobalFlag proc
    ASSUME fs:NOTHING
	mov eax, fs:[30h]
    ASSUME fs:ERROR
    mov eax, [eax + 68h]
    and eax, 70h
    ret
HasPEBNtGlobalFlag endp

HasHeapFlagByPEB proc
    ASSUME fs:NOTHING
    mov eax, fs:[30h]
    ASSUME fs:ERROR
    mov eax, DWORD PTR [eax + 18h]
    mov eax, DWORD PTR [eax + 10h]; 定位的字段好像不对，这个位移排排序链表头
    ret
HasHeapFlagByPEB endp

AxDivZero proc
    xor eax, eax;
    div eax
    ret
AxDivZero endp

end
