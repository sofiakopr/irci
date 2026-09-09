#include <stdio.h>
#include <stdlib.h>

typedef struct CPU {
    unsigned int pc;
    unsigned int psw;
    unsigned int regs[16];
    unsigned char data_memory [65536];
    unsigned int program_memory [65536];
}cpu;



int main (){

    cpu estado = {0}; //inicia todos los miembros de la struct en 0
    int bandera = 1;
    while (bandera){
        
        unsigned int instruccion = estado.program_memory[estado.pc];
        switch (instruccion & 0b1111) {
            case 0: //add
                unsigned int guardar = (instruccion >> 4) & 0b1111;
                unsigned int v1 = (instruccion >> 8) & 0b1111;
                unsigned int v2 = (instruccion >> 12) & 0b1111;
                estado.regs[guardar] = estado.regs[v1] + estado.regs[v2];
                break;
            case 1: //
                break;
            case 2: //lw
                unsigned int guardar = (instruccion >> 4) & 0b1111;
                unsigned int lectura = (instruccion >> 8) & 0b1111;
                unsigned int offset = (instruccion >> 12) & 0b11111111;
                estado.regs[guardar] = estado.data_memory[estado.regs[lectura] + offset];
                break;
            case 3: //sw
                unsigned int guardar = (instruccion >> 4) & 0b1111;
                unsigned int lectura = (instruccion >> 8) & 0b1111;
                unsigned int offset = (instruccion >> 12) & 0b11111111;
                estado.data_memory[estado.regs[lectura] + offset] = estado.regs[guardar];
                break;
            case 4: //beq
                unsigned int v1 = (instruccion >> 4) & 0b1111;
                unsigned int v2 = (instruccion >> 8) & 0b1111;
                unsigned int offset = (instruccion >> 12) & 0b11111111;
                if (estado.regs[v1] == estado.regs[v2]) {
                    estado.pc += (offset << 24) >> 24;
                }
                break;
            case 5: //j
                unsigned int offset = (instruccion >> 12);

            default:
                break;
        }

    }
}
