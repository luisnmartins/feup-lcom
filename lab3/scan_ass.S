#include "i8042.h"

.globl _keyboardasm
_keyboardasm:

	xor %eax, %eax
	xor %ebx, %ebx
	movl 5, %ecx
	cicle:

 		inb  $STATUS_REG ,%ebx
 		andl $OBF, %ebx
		cmpl %ebx, 0
		loope cicle
		in $KBD_OUT_BUF, %eax
		ret



