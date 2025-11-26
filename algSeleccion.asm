; Función de algoritmo de ordenamiento de Selección
; Este consiste en: Ir dividiendo una lista en una parte ordenada y otra desordenada.
; Repetidamente, busca el elemento más pequeño (o más grande) de la parte desordenada y 
; lo intercambia con el primer elemento de esa sección, haciendo que la parte ordenada crezca 
; en un elemento.

 global asm_seleccion

section .text
; int asm_seleccion(int* arr, int n, int* buffer)
asm_seleccion:
    ; TODO: implementar seleccion
    xor eax, eax
    ret
