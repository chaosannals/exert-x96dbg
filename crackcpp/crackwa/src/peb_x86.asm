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

end
