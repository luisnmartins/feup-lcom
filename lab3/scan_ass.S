#include "i8042.h"

_keyboardasm:

xor %eax, %eax
loop:
 in %STATUS_REG
 cmp %STATUS_REG %OBF
