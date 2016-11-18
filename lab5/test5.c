#include "timer.h"
#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"
#include  <machine/int86.h>

unsigned int hook_id = T0_IRQSET;
unsigned int contador = 0;

void *test_init(unsigned short mode, unsigned short delay) {
	struct reg86u *reg;
	int r;
	struct mem_range mr;
	unsigned int vram_base;
	unsigned int vram_size;
	void *video_mem;
	sys_int86(reg);

	reg.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	reg.u.w.bx = 1 << 14 | mode; // set bit 14: linear framebuffer
	reg.u.b.intno = 0x10;
	if (sys_int86(&r) != OK) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return 1;
	}
	int ipc_status, irq_set = timer_subscribe_int();
	message msg;
	int a;
	if (delay <= 0) {
		printf("Time not valid!");
		return 1;
	}
	while (contador <= (delay * 60)) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((a = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					contador++;
				}
			}
		}
	}
	if (timer_unsubscribe_int() != 0) {
		return 1;
	} else {
		if (vg_exit() != 0)
			return 1;
		else {

			mr.mr_base = (phys_bytes) vram_base;
			mr.mr_limit = mr.mr_base + vram_size;
			if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
				panic("sys_privctl (ADD_MEM) failed: %d\n", r);
			/* Map memory */
			video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
			if (video_mem == MAP_FAILED)
				panic("couldn’t map video memory");
		}
	}

}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {

	/* To be completed */

}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {

	/* To be completed */

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	/* To be completed */

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	/* To be completed */

}

int test_controller() {

	/* To be completed */

}

