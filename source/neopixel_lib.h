/*
 * File: neopixel_lib.h
 *
 * This header file contains delcarations of functions developed for
 * handling data sent to / received from the Neopixel strip using
 * WS128B protocol.
 *
 * Author: Ritika Ramchandani <ritika.ramchandani@colorado.edu>
 *
 */

#ifndef NEOPIXEL_LIB_H_
#define NEOPIXEL_LIB_H_

#include "common_defines.h"

#define NEO_NUM_LEDS (20) /* Number of LEDs being used on the strip */
#define NEO_BITS_INIT (3) /* Sending leading bits to clear  leftover PWM pulses */
#define NEO_BITS_LEDS (24) /* 8 bits for each of R/G/B */
/* Number of trailing bits to provide enough time
for the oulses to latch on */
#define NEO_BITS_LATCH (10)
#define NUM_COLORS (3) /* R, G and B */
/* Size of the including leading and trailing dummy bits */
#define BUFF_SIZE (NEO_BITS_INIT + (NEO_NUM_LEDS * NEO_BITS_LEDS) + NEO_BITS_LATCH)

/* Array typedef to store colors */
typedef uint8_t RGB[NUM_COLORS];


/*
 * Neo_init: Intializes the LED buffer for the neopixel strip
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 *
 * Returns: void
 *
 */
void Neo_init(uint16_t* LED_buffer);


/*
 * Neo_ClearAllPixel: Clears the LED buffer for all pixels
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 *
 * Returns: void
 *
 */
void Neo_ClearAllPixel(uint16_t* LED_buffer);


/*
 * Neo_SetPixel: Sets the given pixel in the LED_buffer with the desired color
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 * pixel_idx - Index on the LED strip
 * colors - RGB values of the pixel to be set
 *
 * Returns: void
 *
 */
void Neo_SetPixel(uint16_t* LED_buffer, uint32_t pixel_idx, RGB colors);


/*
 * Neo_PixelBrightness: Dims pixel brightness of the given LED
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 * pixel_idx - Index on the LED strip
 * percent - Percentage by which the LED value should be dimmed
 *
 * Returns: void
 *
 */
void Neo_PixelBrightness(uint16_t* LED_buffer, uint32_t pixel_idx, uint8_t percent);


/*
 * Neo_GetPixel: Gets RGB values of the desried pixel
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 * pixel_idx - Index on the LED strip
 * colors - Pointer to the array of RGB values of the pixel to be set
 *
 * Returns: void
 *
 */
void Neo_GetPixel(uint16_t* LED_buffer, uint32_t pixel_idx, uint8_t* colors);


/*
 * Neo_PixelTrail: Updates LED strip to be a color trail
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 * first_pixel_idx - Index of the first pixel of the trail
 * last_pixel_idx - Index of the last pixel of the trail
 * colors - Pointer to the array of RGB values of the pixel to be set
 * num_trail - Number of LEDs to be glowing on the trail at any given time
 * percent_dim - Percentage by which an LED should be dimmed compared to it's
 * 							original value
 *
 * Returns: void
 *
 */
void Neo_PixelTrail(uint16_t* LED_buffer, RGB colors, uint32_t first_pixel_idx, uint32_t last_pixel_idx,
		uint32_t num_trail, uint8_t percent_dim);


#endif /* NEOPIXEL_LIB_H_ */
