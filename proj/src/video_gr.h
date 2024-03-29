#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8
#define ABSOL(a) ((a) >= 0 ? (a) : -(a))




/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

 /** @} end of video_gr */


/**
 * @brief returns the resolution of the video mode that is being used
 * @return the size of the horizontal line of the screen
 * */
unsigned getHorResolution();


/**
 *  @brief returns the resolution of the video mode that is being used
 * @return the size of the vertical line of the screen
 * */
unsigned getVerResolution();

/**
 * @brief returns the double buffer
 * @returns the double buffer
 * */
char* getDouleBuffer();


/**
 * @brief copies what is in the double buffer to the video mem
 * */
void print_buffer();


#endif /* __VIDEO_GR_H */
