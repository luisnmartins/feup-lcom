#include "i8042.h"

.globl _keyboardasm
_keyboardasm:

	xor %eax, %eax
	movl 5, %ecx
	cicle:

 		inb  $STATUS_REG
 		andl $OBF, %eax
		cmpl %eax, 0
		loope cicle
		xor %eax,%eax
		in $KBD_OUT_BUF, %eax
		ret



