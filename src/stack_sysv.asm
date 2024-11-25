; Copyright (C) 2024 Ethan Uppal. All rights reserved.

bits 64

section .text
    align 64

%ifidn %substr(__?OUTPUT_FORMAT?__, 1, 3), elf

global get_rbp
get_rbp:
    mov rax, rbp
    ret

global get_rsp
get_rsp:
    mov rax, rsp
    ret

%else

global _get_rbp
_get_rbp:
    mov rax, rbp
    ret

global _get_rsp
_get_rsp:
    mov rax, rsp
    ret

%endif


