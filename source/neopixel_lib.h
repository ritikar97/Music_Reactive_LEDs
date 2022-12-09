/*
 * neopixel_lib.h
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */

#ifndef NEOPIXEL_LIB_H_
#define NEOPIXEL_LIB_H_

#include "common_defines.h"

#define NEO_NUM_LEDS (30)
#define NEO_BITS_INIT (3)
#define NEO_BITS_LEDS (24)
#define NEO_BITS_LATCH (10)
#define NUM_COLORS (3)
#define BUFF_SIZE (NEO_BITS_INIT + (NEO_NUM_LEDS * NEO_BITS_LEDS) + NEO_BITS_LATCH)



typedef uint8_t RGB[NUM_COLORS];


void Neo_init(uint16_t* LED_buffer);
void Neo_ClearAllPixel(uint16_t* LED_buffer);
void Neo_SetPixel(uint16_t* LED_buffer, uint32_t pixel_idx, RGB colors);
void Neo_Transfer(void);
void Neo_PixelBrightness(uint16_t* LED_buffer, uint32_t pixel_idx, uint8_t percent);
uint8_t* Neo_GetPixel(uint16_t* LED_buffer, uint32_t pixel_idx);
void Neo_PixelTrail(uint16_t* LED_buffer, RGB colors, uint32_t first_pixel_idx, uint32_t last_pixel_idx,
		uint32_t num_trail, uint8_t percent_dim);



#endif /* NEOPIXEL_LIB_H_ */
