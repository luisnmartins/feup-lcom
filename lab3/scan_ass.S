#include "i8042.h"

.globl _keyboardasm

.globl _outbufass
.text
_keyboardasm:

inb $KBD_OUT_BUF, %al
mov %al, _outbufass

ret


	/*xor %eax, %eax
	cicle:

 		inb  $STATUS_REG, %al
 		andl $OBF, %eax
		cmpl %eax, 0
		je cicle
		xor %eax,%eax
		inb $KBD_OUT_BUF, %al
		mov %al, _outbufass
		ret*/



