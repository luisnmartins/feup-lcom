#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_
#include "i8254.h"


#define KB_IRQ 1    //Keyboard IRQ
#define STATUS_REG 0x64
#define KBD_OUT_BUF 0x60
#define OBF BIT(0)
#define IBF BIT(1)

#define ESC_CODE 0x81


#define NBIT(n) (0xFF^BIT(n))

#define OUT_BUF_2BYTES 0xE0
#define DELAY_US 20000

#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)


#define ON_OFF_LEDS 0xED
#define KBC_CMD_REG 0x64
#define ACK 0xFA
#define RESEND 0xFE
#define ERROR 0xFC

#endif /* _LCOM_I8042_H */
