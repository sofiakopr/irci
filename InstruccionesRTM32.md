
# Instrucciones_rtm32

Se encuentra disponible el Documento de Google por si se quiere apreciar mejor.
https://docs.google.com/document/d/1g78n8BffJCK6uq4r9ATktBEaJNMx5wPxH5_tD2Urzg4/edit?usp=sharing

**Instrucciones que no se realizan: CTS CFS TRAP RTF**


**LUI + ORI (para poder asignarles valores a los registros y probar las otras instrucciones)**

**LUI:**

Formato L:
opcode | rs | rt | h | imm

opcode=00111
rs = 00000
rt = 01011
h = 0
imm = 0000000000000001

Instrucción completa
00111 00000 01011 0 0000000000000001

Pasando esto a Hexadecimal:
0x38160001

Precondiciones:
Ninguna

Resultado de ingresar s [0x00] 0x38160001:

DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000000
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000000
TRACE [src/cpu.c:466]: Instruction: 0x38160001
TRACE [src/cpu.c:467]: Opcode: 0b00111
TRACE [src/cpu.c:479]: [LUI] R11 = 0x00000000
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.



**ORI:**

Formato L:
opcode | rs | rt | h | imm

opcode = 00101
rs = 01011
rt = 01011
h = 0
imm = 0000000011111111

Instrucción completa:
00101 01011 01011 0 0000000011111111

Pasando esto a Hexadecimal:
0x2AD600FF

Precondiciones:
Ninguna

Resultado de ingresar s [0x04] 0x2AD600FF:

DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000004
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000004
TRACE [src/cpu.c:466]: Instruction: 0x2AD600FF
TRACE [src/cpu.c:467]: Opcode: 0b00101
TRACE [src/opcodes/logical.m:6]: [ORI] R11 (0x00000000) = R11 (0x00000000) | 0x000E
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.


**XORI:**

Formato L:
opcode | rs | rt | h | imm

opcode = 00110
rs = 01011
rt = 01011
h = 0
imm = 0000000011111111

Instrucción completa
00110 01011 01011 0 0000000011111111

Pasando esto a Hexadecimal:
0x32D600FF

Precondiciones:
Ninguna


**ADD: (usando LUI y ORI)**

Primer Registro:

**LUI $t1,0**

opcode=00111
rs=00000
rt=01011
h=0
imm=0000000000000000

Instrucción completa:
00111000000101100000000000000000

Pasando esto a Hexadecimal:
0x38160000

**ORI $t1,$t1,10**

opcode=00101
rs=01011
rt=01011
h=0
imm=0000000000001010

Instrucción completa:
00101010110101100000000000001010

Pasando esto a Hexadecimal:

0x2AD6000A

Segundo registro:

**LUI $t2,0**

opcode=00111
rs=00000
rt=01100
h=0
imm=0000000000000000

Instrucción completa:
00111000000110000000000000000000

Pasando esto a Hexadecimal:
0x38180000

**ORI $t2,$t2,5**

opcode=00101
rs=01100
rt=01100
h=0
imm=0000000000000101

Instrucción completa:
00101011000110000000000000000101

Pasando esto a Hexadecimal:

0x2B180005

ADD
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode=00000
rs=01011
rt=01100
rd=01010
aux=00000
X=0
funct=011100

Sustituyendo esto por sus valores binarios:
00000 01011 01100 01010 00000 0 011100

Pasando esto a Hexadecimal:
0x02D8A01C

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:

Primer Registro:

RTM32> s PC 0x00
Program Counter (PC) set to 0x00000000
RTM32> s [0x00] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x00000004
RTM32> s [0x04] 0x2AD6000A
RTM32> n 1

Segundo Registro:
RTM32> s [0x08] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x0000000C
RTM32> s [0x0C] 0x2B180005
RTM32> n 1

ADD:
RTM32> s PC 0x10
Program Counter (PC) set to 0x00000010
RTM32> s [0x10] 0x02D8A01C
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000010
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000010
TRACE [src/cpu.c:466]: Instruction: 0x02D8A01C
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/opcodes/arithmetic.m:44]: [ADD] R10 (0x0000000F) = R11 (0x0000000A) + R12 (0x00000005)
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.


**SUB: (usando LUI y ORI)**

**Se repite el mismo procedimiento que el anterior con LUI y ORI, usando los mismos registros y valores en estos, lo único que cambia es que se usa SUB:**

Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode=00000
rs=01011
rt=01100
rd=01010
aux=00000
X=0
funct=011101

Instrucción completa:
00000010110110001010000000011101

Pasando esto a Hexadecimal:
0x02D8A01D

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:

Primer Registro:
RTM32> s PC 0x00
Program Counter (PC) set to 0x00000000
RTM32> s [0x00] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x00000004
RTM32> s [0x04] 0x2AD6000A
RTM32> n 1

Segundo Registro:
RTM32> s [0x08] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x0000000C
RTM32> s [0x0C] 0x2B180005
RTM32> n 1

SUB:
RTM32> s PC 0x10
Program Counter (PC) set to 0x00000010
RTM32> s [0x10] 0x02D8A01D
RTM32> n 1

Resultado:

DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000010
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000010
TRACE [src/cpu.c:466]: Instruction: 0x02D8A01D
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/opcodes/arithmetic.m:48]: [SUB] R10 (0x00000005) = R11 (0x00000
00A) - R12 (0x00000005)
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.


**AND**

**Se repite el mismo procedimiento que el anterior con LUI y ORI, usando los mismos registros y valores en estos, lo único que cambia es que se usa AND:**

Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 001000

Instrucción completa:
00000010110110001010000000001000

Pasando esto a Hexadecimal:
0x02D8A008

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
Primer Registro:
RTM32> s PC 0x00
Program Counter (PC) set to 0x00000000
RTM32> s [0x00] 0x38160000
RTM32> n 1
Stepped instructions. Target PC: 0x00000004
RTM32> s [0x04] 0x2AD6000A
RTM32> n 1

Segundo Registro:
RTM32> s [0x08] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x0000000C
RTM32> s [0x0C] 0x2B180005
RTM32> n 1

AND:
RTM32> s PC 0x10
Program Counter (PC) set to 0x00000010
RTM32> s [0x10] 0x02D8A008
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr NOR:
R[10]: 0x0000000A

Que tiene sentido, porque AND compara los bits en común de dos registros, y si comparamos:

E: 1110
A: 1010

y esta comparación devuelve 1010 o A, que es el valor del registro 10.


**OR**

**Se repite el mismo procedimiento que el de AND, usando los mismos registros y valores en estos, lo único que cambia es que se usa OR:**

Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode=00000
rs=01011
rt=01100
rd=01010
aux=00000
X=0
funct= 001001

Instrucción completa:
00000010110110001010000000001001

Pasando esto a Hexadecimal:
0x02D8A009

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:

Primer Registro:
RTM32> s PC 0x00
Program Counter (PC) set to 0x00000000
RTM32> s [0x00] 0x38160000
RTM32> n 1
Stepped instructions. Target PC: 0x00000004
RTM32> s [0x04] 0x2AD6000E
RTM32> n 1

Segundo Registro:
RTM32> s [0x08] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x0000000C
RTM32> s [0x0C] 0x2B18000A
RTM32> n 1

OR:
RTM32> s PC 0x10
Program Counter (PC) set to 0x00000010
RTM32> s [0x10] 0x02D8A009
RTM32> n 1

DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Curr
ent PC: 0x00000010
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read:0x00000010
TRACE [src/cpu.c:466]: Instruction: 0x02D8A009
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr OR:
R[10]: 0x0000000E


**ANDI**

**Se repite el mismo procedimiento que el anterior con LUI y ORI, usando los mismos registros y valores en estos, lo único que cambia es que se usa ANDI:**

Formato I:
opcode | rs | rt | imm 

opcode=00100
rs=01011
rt=01100
imm=01010000000001000

Instrucción completa:
00100010110110001010000000001000

Pasando esto a Hexadecimal:
0x22D8A008

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
Primer Registro:
RTM32> s PC 0x00
Program Counter (PC) set to 0x00000000
RTM32> s [0x00] 0x38160000
RTM32> n 1
Stepped instructions. Target PC: 0x00000004
RTM32> s [0x04] 0x2AD6000A
RTM32> n 1

Segundo Registro:
RTM32> s [0x08] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x0000000C
RTM32> s [0x0C] 0x2B180005
RTM32> n 1

ANDI:
RTM32> s PC 0x10
Program Counter (PC) set to 0x00000010
RTM32> s [0x10] 0x22D8A008
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000010
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000010
TRACE [src/cpu.c:466]: Instruction: 0x22D8A008
TRACE [src/cpu.c:467]: Opcode: 0b00100
TRACE [src/opcodes/logical.m:3]: [ANDI] R12 (0x00000008) = R11 (0x0000000A) & 0xA008
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.


**XOR**

**Se repite el mismo procedimiento que el anterior con LUI y ORI, usando los mismos registros y valores en estos, lo único que cambia es que se usa XOR:**

Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 001010

Instrucción completa:
00000010110110001010000000001010

Pasando esto a Hexadecimal:
0x02D8A00A

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
Primer registro:
RTM32> s PC 0
Program Counter (PC) set to 0x00000000
RTM32> s [0x00] 0x38160000
RTM32> n 1
Stepped instructions. Target PC: 0x00000004
RTM32> s [0x04] 0x2AD6000E
RTM32> n 1
Stepped instructions. Target PC: 0x00000008

Segundo registro:
RTM32> s [0x08] 0x38180000
RTM32> n 1
Stepped instructions. Target PC: 0x0000000C
RTM32> s [0x0C] 0x2B18000A
RTM32> n 1

XOR: 
RTM32> s [0x10] 0x02D8A00A
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000014
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000014
TRACE [src/cpu.c:466]: Instruction: 0x02D8A00A
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr XOR:
R[10]: 0x00000004

Que tiene sentido, ya que XOR es un OR exclusivo, y al comparar:

E: 1110
A: 1010 

devuelve un 4, ya que los bits que coinciden devuelven 0 y los que no, devuelven 1, por lo que el único bit que devolvería 1 es el segundo desde la izquierda, que pertenece al 4. 

**NOR**

**Se repite el mismo procedimiento que el anterior de XOR con LUI y ORI, usando los mismos registros y valores en estos, lo único que cambia es que se usa NOR. Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron estos registros.**

Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 001011

Instrucción completa:
00000010110110001010000000001011

Pasando esto a Hexadecimal:
0x02D8A00B

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x1C] 0x02D8A00B
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x0000001C
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x0000001C
TRACE [src/cpu.c:466]: Instruction: 0x02D8A00B
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr NOR:
R[10]: 0xFFFFFFF1

Que tiene sentido, ya que NOR es un OR opuesto, y al comparar:

E: 1110
A: 1010 

devuelve FFFFFFF1, que tiene sentido, porque NOR solo devuelve 1 cuando ambos bits que se comparan son 0. Ambos registros tienen 0 en todos sus nibbles a excepción del último, que devuelve 0’s en todos sus bits menos el último, que ambos son 0, por lo que devuelve 1. 


**MUL** 

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 010101

Instrucción completa:
00000010110110001010000000010101

Pasando esto a Hexadecimal:
0x02D8A015

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x20] 0x02D8A015
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr MUL:
R[10]: 0x0000008C

Que tiene sentido, ya que al multiplicar:

E: 0000 1110 = 14
x
A: 0000 1010 = 10
=
8C: 1000 1100 = 140


**MULH**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 010110

Instrucción completa:
00000010110110001010000000010110

Pasando esto a Hexadecimal:
0x02D8A016

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x24] 0x02D8A016
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr MULH:
R[10]: 0x00000000

Que tiene sentido, ya que MULH guarda los 32 bits superiores


**MULHU**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 010111

Instrucción completa:
00000010110110001010000000010111

Pasando esto a Hexadecimal:
0x02D8A017

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x28] 0x02D8A017
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr MULHU:
R[10]: 0x00000000


**DIV**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 011000

Instrucción completa:
00000010110110001010000000011000

Pasando esto a Hexadecimal:
0x02D8A018

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x2C] 0x02D8A018
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr DIV:
R[10]: 0x00000001
 
Que tiene sentido, porque DIV devuelve la cantidad de veces que el segundo registro “entra” o “es contenido” en el primero, en este caso se hace:

E / A = 1110 / 1010 = 14 / 10 => 1 <- 10 “entra” solo una vez en 14. 

**DIVU**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 011001

Instrucción completa:
00000010110110001010000000011001

Pasando esto a Hexadecimal:
0x02D8A019

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x30] 0x02D8A019
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr DIVU:
R[10]: 0x00000001
 
Que tiene sentido, porque DIVU hace lo mismo que DIV, solo que es división de enteros sin signo, por lo que devuelve lo mismo que DIV en este caso ya que no usamos signos. 


**REST**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 011010

Instrucción completa:
00000010110110001010000000011010

Pasando esto a Hexadecimal:
0x02D8A01A

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x34] 0x02D8A01A
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr REST:
R[10]: 0x00000004
 
Que tiene sentido, porque REST devuelve el resto de una división, y en este caso se hace:

REST E A = módulo (E / A) = módulo (14 / 10) => 4


**RESTU**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 01100
rd= 01010
aux= 00000
X= 0
funct= 011011

Instrucción completa:
00000010110110001010000000011011

Pasando esto a Hexadecimal:
0x02D8A01B

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x38] 0x02D8A01B
RTM32> n 1

Resultado:
Los valores en los registros:
R[11]: 0x0000000E
R[12]: 0x0000000A

El valor que toma el registro 10 (en el que se guarda el resultado de la instrucción) después de correr RESTU:
R[10]: 0x00000004
 
Que tiene sentido, porque RESTU devuelve el resto de una división sólo que esta no acepta números negativos, por lo que en este caso devuelve lo mismo que REST.


**LHX**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt=01010 
rd=01100
aux= 00000
X= 0
funct= 010000

Instrucción completa:
00000010110110001010000000010000

Pasando esto a Hexadecimal:
0x02D8A010

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x40] 0x02D8A010
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000040
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000040
TRACE [src/cpu.c:466]: Instruction: 0x02D8A010
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/opcodes/loads_idx.m:6]: [LHX] R12 = 0xFFFFA00A (MEM[0x00000018])
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0xFFFFA00A

Que tiene sentido, porque LHX suma los valores de rs y rd (11 y 10) y busca el resultado en la memoria ram y de esta RAM saca 2 bytes, o 4 dígitos Hexadecimal, y los pone en los 4 bits mas bajos del registro rt (12). Dependiendo del valor de esos hexadecimales, si son negativos rellena los bits más altos con 1’s, y si es positivo rellena con 0’s. Como A es 1010 el primer bit es 1, entonces se lo considera como negativo, por lo que los bits más altos se rellenan todos con 1’s.


**LHUX**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt=01010 
rd=01100
aux= 00000
X= 0
funct= 010001

Instrucción completa:
00000010110110001010000000010001

Pasando esto a Hexadecimal:
0x02D8A011

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x44] 0x02D8A011
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000044
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000044
TRACE [src/cpu.c:466]: Instruction: 0x02D8A011
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/opcodes/loads_idx.m:15]: [LHUX] R12 = 0x0000A00A (MEM[0x00000018])
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000A00A
 
Que tiene sentido, porque LHUX hace lo mismo que LHX, solo que sin signos. El resultado de 0xFFFFA00A anterior no puede ser posible, ya que LHX rellena con 1’s en caso de que el valor sea negativo, y como LHUX no toma signos, devuelve el mismo resultado solo que sin la consideración de signo negativo.


**LBX**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt=01010 
rd=01100
aux= 00000
X= 0
funct= 010010

Instrucción completa:
00000010110110001010000000010010

Pasando esto a Hexadecimal:
0x02D8A012

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x48] 0x02D8A012
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000048
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000048
TRACE [src/cpu.c:466]: Instruction: 0x02D8A012
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/opcodes/loads_idx.m:24]: [LBX] R12 = 0x0000000A (MEM[0x00000018])
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000A00A

Funciona.

**LBUX**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt=01010 
rd=01100
aux= 00000
X= 0
funct= 010011

Instrucción completa:
00000010110110001010000000010011

Pasando esto a Hexadecimal:
0x02D8A013

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x10] 0x02D8A013
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000010
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read: 0x00000010
TRACE [src/cpu.c:466]: Instruction: 0x02D8A013
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/opcodes/loads_idx.m:33]: [LBUX] R12 = 0x00000018 (MEM[0x0000000E])
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x00000018

Funciona.


**LWX**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt=01010 
rd=01100
aux= 00000
X= 0
funct= 010100

Instrucción completa:
00000010110110001010000000010100

Pasando esto a Hexadecimal:
0x02D8A014

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x14] 0x02D8A014
RTM32> n 1

Resultado:
DEBUG [src/debug/execution.m:17]: Stepping CPU pipeline for 1 cycles. Current PC: 0x00000014
TRACE [src/cpu.c:245]: RAM size: 0x00001000 read:0x00000014
TRACE [src/cpu.c:466]: Instruction: 0x02D8A014
TRACE [src/cpu.c:467]: Opcode: 0b00000
TRACE [src/cpu.c:371]: Fetch vector table address: 0xF0000014
FATAL [src/cpu.c:377]: DOUBLE FAULT: Vector table fetch failed at 0xF0000014
TRACE [src/opcodes/loads_idx.m:40]: [LWX] R12 = 0x00000018 (MEM[0x0000000E])
TRACE [src/debug/debug.c:295]: [5] Handler finished execution successfully.

Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x00000018

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x00000018

Funciona.


**JR**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 00000
rd= 00000
aux= 00000
X= 0
funct= 001110

Instrucción completa:
00000010110000000000000000001110

Pasando esto a Hexadecimal:
0x02C0000E

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x00] 0x02C0000E
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E

Stepped instructions. Target PC: 0x0000000E

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E

Funciona, ya que el comando de resultado muestra que la máquina ahora toma que el PC se encuentra en 0x0000000E (14)


**JALR**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs= 01011
rt= 00000
rd= 00001
aux= 00000
X= 0
funct= 001111

Instrucción completa:
00000010110000000001000000001111

Pasando esto a Hexadecimal:
0x02C0100F

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x04] 0x02C0000F
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[1]: 0x00000000 (el registro en el que guardo el resultado)
R[11]: 0x0000000E

Stepped instructions. Target PC: 0x0000000E

Los valores en los registros después de correr la instrucción:
R[1]: 0x00000008
R[11]: 0x0000000E

Funciona, ya que JALR en el rd especificado (1 en este caso) guarda el valor del PC (0x04) + 4 (= 8), y esto se demuestra al ver que el registro 1 cambió, y hace que el PC tome la posición en memoria del valor del rs (11), el cual es 14, y se demuestra al hacer el comando “n” y que este devuelve “Stepped instructions. Target PC: 0x0000000E”

**SLT**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs=01100 (12, tiene 0x0A)
rt=01011 (11, tiene 0x0E)
rd=01010 (10, tiene 0x00)
aux= 00000
X= 0
funct= 001100

Instrucción completa:
00000011000101101010000000001100

Pasando esto a Hexadecimal:
0x0316A00C

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x08] 0x0316A00C
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A
R[10]: 0x00000000

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A
R[10]: 0x00000001

Funciona, ya que SLT (setear menor a) toma rs y rt y evalúa si rs es menor que rt, si llega a serlo, devuelve un 1 en el rd, sino, devuelve un 0. En este caso, nuestro rs es R[12], que tiene valor 0x0A, y rt es R[11] que tiene valor 0x0E, por lo que rs es menor que rt, y se demuestra con el cambio del registro R[10], que es el rd, a un 1.


**SLTU**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs=01100 (12, tiene 0x0A)
rt=01011 (11, tiene 0x0E)
rd=01000 (8, tiene 0x00)
aux= 00000
X= 0
funct= 001101

Instrucción completa:
00000011000101101000000000001101

Pasando esto a Hexadecimal:
0x0316800D

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x10] 0x0316A00D
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A
R[8]: 0x00000000

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A
R[8]: 0x00000001

Funciona, ya que SLTU hace lo mismo que SLT solo que sin signos. 

**SLL**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs=00000 (no se utiliza)
rt=01011 (11, tiene 0x0E)
rd=01010 (10, tiene 0x00)
aux= 00010
X= 0
funct= 000000

Instrucción completa:
00000000000101101010000100000000

Pasando esto a Hexadecimal:
0x0016A100

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x1C] 0x0016A100
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[10]: 0x00000000

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[10]: 0x00000038

No funciona? Este ejemplo (si entiendo bien el corrimiento) debería guardar en el registro R[10] = 0x28.


**SRL**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs=00000 (no se utiliza)
rt=01011 (11, tiene 0x0E)
rd=01010 (10, tiene 0x00)
aux= 00010
X= 0
funct= 000001

Instrucción completa:
00000000000101101010000100000001

Pasando esto a Hexadecimal:
0x0016A101

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x20] 0x0016A101
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[10]: 0x00000000

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[10]: 0x00000003

No funciona? Este ejemplo (si entiendo bien el corrimiento) debería guardar en el registro R[10] = 0x07.

**SRA**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.**
Formato R:
opcode | rs | rt | rd | aux | X | funct

opcode= 00000
rs=00000 (no se utiliza)
rt=01011 (11, tiene 0x0E)
rd=01010 (10, tiene 0x00)
aux= 00010
X= 0
funct= 000010

Instrucción completa:
00000000000101101010000100000010

Pasando esto a Hexadecimal:
0x0016A102

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x10] 0x0016A102
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[10]: 0x00000000

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[10]: 0x00000003

No funciona? Este ejemplo (si entiendo bien el corrimiento) debería guardar en el registro R[10] = 0x07.


**ADDI**

**Los comandos para ingresar valores en los registros no se corren devuelta ya que no se modificaron los registros utilizados.** 

Formato I:
opcode | rs | rt | imm 

opcode=00001
rs=01011
rt=01100
imm=01010000000001000

Instrucción completa:
00001010110110001010000000001000

Pasando esto a Hexadecimal:
0x0AD8A008

Se muestran los comandos ingresados en consola y el resultado:

Ingresados:
RTM32> s [0x18] 0x0AD8A008
RTM32> n 1

Resultado:
Los valores en los registros antes de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000000A

Los valores en los registros después de correr la instrucción:
R[11]: 0x0000000E
R[12]: 0x0000A016

Lo que tiene sentido, ya que en R[12] se guarda el resultado de R[11] + 0x0A008. 
