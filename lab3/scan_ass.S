#include "i8042.h"

.globl _keyboardasm

.globl _outbufass
.text
_keyboardasm:

//inb $KBD_OUT_BUF, %al
//mov %al, _outbufass

//ret


	xor %eax, %eax
	movl 5, %ecx
	cicle:

 		inb  $STATUS_REG, %al
 		and $OBF, %al
		cmp %al, 0
		loope cicle
		inb $KBD_OUT_BUF, %al
		mov %al, _outbufass
		ret



