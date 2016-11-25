#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)
#define VBE_INFO_SIZE 256

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {
	mmap_t mp;
	struct reg86u r;
	lm_init();
	lm_alloc(VBE_INFO_SIZE,&mp);
		r.u.w.ax = 0x4F01; // VBE call, function 01 -- return vbe mode
		r.u.w.es = PB2BASE(mp.phys);
		r.u.w.di = PB2OFF(mp.phys);
		r.u.w.cx = mode;
		r.u.b.intno = 0x10;
		if( sys_int86(&r) != OK ) {
			printf("Error\n");
			return 1;
	}

		memcpy(vmi_p,mp.virtual,VBE_INFO_SIZE);
		lm_free(&mp);
  
  return 1;
}


