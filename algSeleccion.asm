; Función en la cual se implementa el algoritmo de ordenamiento de burbuja 
; El cual compara repetidamente pares de elementos adyacentes en una lista y los intercambia si están en el orden incorrecto, 
; como si fueran burbujas que "suben". Este proceso se repite a través de la lista hasta que no se necesiten más intercambios, 
; lo que indica que la lista está completamente ordenada
section .note.GNU-stack noalloc noexec nowrite progbits
section .text
    global asm_seleccion

asm_seleccion:
    push rbp
    mov  rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub  rsp, 8         

    mov  r12, rdi        ; arreglo
    mov  r13, rsi        ; n
    mov  r14, rdx        ; buffer

   
    cmp  r13, 1
    jle  .sin_pasos

    
    xor  r15, r15

    mov  rdi, r14        ; destino
    mov  rsi, r12        ; origen
    mov  rdx, r13        ; tamaño
    call copiar_arreglo
    inc  r15             ; incrementar paso

    xor  rbx, rbx        ; i = 0

.externo:
    ; mientras i < n-1
    mov  rax, r13
    dec  rax            
    cmp  rbx, rax
    jge  .fin

 
    mov  r8, rbx
    
    mov  r9, rbx
    inc  r9

.interno:
    cmp  r9, r13
    jge  .intercambio

 
    mov  eax, [r12 + r9*4]
 
    mov  edx, [r12 + r8*4]
    cmp  eax, edx
    jge  .no_actualizar

    ; nuevo mínimo
    mov  r8, r9

.no_actualizar:
    inc  r9
    jmp  .interno

.intercambio:
 
    cmp  r8, rbx
    je   .siguiente

    mov  eax, [r12 + rbx*4]  
    mov  edx, [r12 + r8*4]   
    mov  [r12 + rbx*4], edx  
    mov  [r12 + r8*4], eax  

    mov  rax, r15           
    imul rax, r13            
    shl  rax, 2              
    lea  rdi, [r14 + rax]    
    mov  rsi, r12            
    mov  rdx, r13            
    call copiar_arreglo
    inc  r15                 
.siguiente:
    inc  rbx                 
    jmp  .externo

.fin:
    mov  rax, r15            ; devolver número de pasos
    jmp  .salida

.sin_pasos:
    ; n <= 1 guardar solo el estado inicial y devolver 1
    mov  r15, 1
    mov  rdi, r14
    mov  rsi, r12
    mov  rdx, r13
    call copiar_arreglo
    mov  rax, r15

.salida:
    add  rsp, 8              
    pop  r15
    pop  r14
    pop  r13
    pop  r12
    pop  rbx
    pop  rbp
    ret


copiar_arreglo:
    push rbp
    mov  rbp, rsp

    test rdx, rdx
    jz   .fin_copia

    mov  rcx, rdx

.loop_copia:
    mov  eax, [rsi]
    mov  [rdi], eax
    add  rsi, 4
    add  rdi, 4
    dec  rcx
    jnz  .loop_copia

.fin_copia:
    pop  rbp
    ret
