#include "constants.h"

.globl _keyboardasm

.globl _readoutbuf;
.globl _outbufassem
.globl _statusandobf
.text
_keyboardasm:

 		inb  $STATUS_REG, %al
 		andl $OBF, %eax
		mov %al,_statusandobf
		ret

_readoutbuf:

inb $KBD_OUT_BUF, %al
mov %al, _outbufassem
ret
