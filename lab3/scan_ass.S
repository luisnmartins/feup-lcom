#include "i8042.h"

.globl _keyboardasm

.globl _readoutbuf;
.globl _outbufass
.globl _statusandobf
.text
_keyboardasm:

/*inb $KBD_OUT_BUF, %al
mov %al, _outbufass

ret*/

 		inb  $STATUS_REG, %al
 		andl $OBF, %eax
		mov %al,_statusandobf
		ret

_readoutbuf:

inb $KBD_OUT_BUF, %al
mov %al, _outbufass
ret
