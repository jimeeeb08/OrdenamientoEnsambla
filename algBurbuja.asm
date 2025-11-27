; Función en la cual se implementa el algoritmo de ordenamiento de burbuja 
; El cual compara repetidamente pares de elementos adyacentes en una lista y los intercambia si están en el orden incorrecto, 
; como si fueran burbujas que "suben". Este proceso se repite a través de la lista hasta que no se necesiten más intercambios, 
; lo que indica que la lista está completamente ordenada

section .note.GNU-stack noalloc noexec nowrite progbits

section .data
    ; No es necesario

section .bss
    ; No es necesario

section .text
    global asm_burbuja

; Función: asm_burbuja
; Parámetros:
;   rdi = int *arr (puntero al arreglo original)
;   rsi = int n (tamaño del arreglo)
;   rdx = int *buffer (puntero al buffer de salida)
; Retorna: cantidad de pasos en rax

asm_burbuja:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 8            ; Alinear stack a 16 bytes y espacio para contador
    
    ; Guardar parámetros en registros preservados
    mov r12, rdi          ; r12 = puntero al arreglo original
    mov r13, rsi          ; r13 = n (tamaño)
    mov r14, rdx          ; r14 = puntero al buffer de pasos
    
    ; Verificar si n <= 1 (ya ordenado)
    cmp r13, 1
    jle .fin_sin_pasos
    
    ; Inicializar contador de pasos
    xor r15, r15          ; r15 = 0 (contador de pasos)
    
    ; Guardar el estado inicial (paso 0)
    mov rdi, r14          ; destino = buffer
    mov rsi, r12          ; origen = arreglo
    mov rdx, r13          ; tamaño = n
    call copiar_arreglo
    
    inc r15               ; contador_pasos++
    
    ; Bubble Sort: ciclo externo (pasadas)
    mov rbx, r13          ; rbx = n (límite externo)
    
.ciclo_externo:
    cmp rbx, 1
    jle .fin_ordenamiento
    
    ; Ciclo interno: comparar elementos adyacentes
    xor rcx, rcx          ; rcx = 0 (índice i)
    mov r8, rbx
    dec r8                ; r8 = límite - 1
    
.ciclo_interno:
    cmp rcx, r8
    jge .fin_interno
    
    ; Calcular &arr[i]
    mov rax, rcx
    shl rax, 2            ; rax = i * 4 (cada int son 4 bytes)
    lea r9, [r12 + rax]   ; r9 = &arr[i]
    
    ; Cargar arr[i] y arr[i+1]
    mov r10d, [r9]        ; r10d = arr[i] (32 bits)
    mov r11d, [r9+4]      ; r11d = arr[i+1] (32 bits)
    
    ; Comparar: si arr[i] > arr[i+1], intercambiar
    cmp r10d, r11d
    jle .no_intercambio
    
    ; Realizar intercambio
    mov [r9], r11d        ; arr[i] = arr[i+1]
    mov [r9+4], r10d      ; arr[i+1] = arr[i] (antiguo)
    
    ; Guardar estado después del intercambio
    push rcx
    push rbx
    push r8
    
    ; Calcular posición en buffer: buffer + (contador_pasos * n * 4)
    mov rax, r15          ; rax = contador_pasos
    imul rax, r13         ; rax = contador_pasos * n
    shl rax, 2            ; rax = contador_pasos * n * 4
    lea rdi, [r14 + rax]  ; rdi = buffer + offset (destino)
    
    ; Copiar estado actual al buffer
    mov rsi, r12          ; rsi = origen (arreglo)
    mov rdx, r13          ; rdx = tamaño (n)
    call copiar_arreglo
    
    inc r15               ; contador_pasos++
    
    pop r8
    pop rbx
    pop rcx
    
.no_intercambio:
    inc rcx               ; i++
    jmp .ciclo_interno
    
.fin_interno:
    dec rbx               ; límite--
    jmp .ciclo_externo
    
.fin_ordenamiento:
    mov rax, r15          ; retornar contador de pasos
    jmp .salir
    
.fin_sin_pasos:
    ; Si n <= 1, retornar 1 (solo el estado inicial)
    mov r15, 1
    
    ; Copiar el arreglo inicial al buffer
    mov rdi, r14          ; destino = buffer
    mov rsi, r12          ; origen = arreglo
    mov rdx, r13          ; tamaño = n
    call copiar_arreglo
    
    mov rax, r15
    
.salir:
    add rsp, 8
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

; Función auxiliar: copiar_arreglo (64 bits)
; Parámetros:
;   rdi = destino
;   rsi = origen
;   rdx = tamaño (n)
copiar_arreglo:
    push rbp
    mov rbp, rsp
    
    ; Verificar si n == 0
    test rdx, rdx
    jz .fin_copia
    
    mov rcx, rdx          ; rcx = contador
    
.loop_copia:
    mov eax, [rsi]        ; leer de origen (32 bits)
    mov [rdi], eax        ; escribir a destino (32 bits)
    
    add rsi, 4            ; avanzar origen
    add rdi, 4            ; avanzar destino
    dec rcx
    jnz .loop_copia
    
.fin_copia:
    pop rbp
    ret



