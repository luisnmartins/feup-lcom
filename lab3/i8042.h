#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_


#define KB_IRQ 1    //Keyboard IRQ
#define STATUS_REG 0x64
#define KBD_OUT_BUF 0x60

#define ESC_CODE 0x81

#define BIT(n) (0x01<<(n))

#define OUT_BUF_2BYTES 0xE0


#endif /* _LCOM_I8042_H */
