/*
 * File: neopixel_lib.c
 *
 * This source file contains a function library developed for
 * handling data sent to / received from the Neopixel strip using
 * WS128B protocol.
 *
 * Author: Ritika Ramchandani <ritika.ramchandani@colorado.edu>
 *
 */

#include "neopixel_lib.h"
#include "led_out.h"
#include "common_defines.h"

/* For bit 0, to get a high of 0.35us out of 1.25us
 * 17/60 clock ticks need to held high */
#define BIT_0 (17)

/* For bit 0, to get a high of 0.7us out of 1.25us
 * 32/60 clock ticks need to held high */
#define BIT_1 (32)

#define RESET (0)
#define NUM_COLOR_BITS (8) /* Number of bits in a color (r/g/b) value */
#define GET_MSB (0x80) /* Mask to get MSB of the byte */

/* RGB values = 0, to clear the pixel */
RGB clear_pixel = {0, 0, 0};


/*
 * clear_LED_buffer: Clears the LED buffer and sets all values to 0
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 *
 * Returns: void
 */
static void clear_LED_buffer(uint16_t* LED_buffer)
{
  /* Set initial LED buffer bits to 0 - used for clearing
   * leftover trails */
	for(uint32_t i = 0; i < NEO_BITS_INIT; i++)
  {
  	LED_buffer[i] = 0;
  }

	/* Clear all LEDs on the strip */
  Neo_ClearAllPixel(LED_buffer);

  /* Sending dummy 0s to give data the time to latch on */
  for(uint32_t i = NEO_NUM_LEDS + (NEO_NUM_LEDS * NEO_BITS_LEDS); i < BUFF_SIZE; i++)
  {
  	LED_buffer[i] = 0;
  }
}


/* Clear buffer as a part of initialization */
void Neo_init(uint16_t* LED_buffer)
{
	clear_LED_buffer(LED_buffer);
}


/* Clear all LEDs on the strip */
void Neo_ClearAllPixel(uint16_t* LED_buffer)
{
	RGB val = {0, 0, 0};
	for(uint8_t i = 0; i < NEO_NUM_LEDS; i++)
	{
		Neo_SetPixel(LED_buffer, i, val);
	}

}


/*
 * Neo_SetColor: Set the buffer value of the given pixel index with
 * the provided color
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 * in_idx - LED index on the LED strip
 * color - RGB values to be written to the desired LED index
 *
 * Returns: Index of the next LED on the strip
 */
static uint32_t Neo_SetColor(uint16_t* LED_buffer, uint32_t in_idx, uint8_t color)
{
	/* For each color (r/g/b), calculate the 8 byte LED_buffer value */
	for(uint8_t i = 0 ; i < NUM_COLOR_BITS; i++)
	{
		/* Using binary representation of the color to
		 * calculate the 8-byte value to be sent to the PWM */
		if(color & GET_MSB)
		{
			LED_buffer[in_idx] = BIT_1;
		}
		else
		{
			LED_buffer[in_idx] = BIT_0;
		}
		color <<= 1;
		in_idx++;
	}

	return in_idx;
}


/*
 * Neo_SetColor: Calculate the color (r/g/b) value of
 * a given LED based on the values stored in the LED_buffer
 *
 * Parameters:
 * LED_buffer - pointer to the RGB values of each individual pixel
 * in_idx - LED index on the LED strip
 *
 * Returns: R/G/B value of the desired LED index
 */
static uint8_t Neo_GetColor(uint16_t* LED_buffer, uint32_t in_idx)
{
	uint8_t color = 0;
	/* Calculate 8-bit value of the color, based on its
	 * 8-byte representation in the LED_buffer */
	for(uint8_t i = 0; i < NUM_COLOR_BITS; i++)
	{
	   color <<= 1;
	   if (LED_buffer[in_idx] == BIT_1)
	   {
	      color |= 1;
	    }
	   in_idx++; /* Next bit */
	 }
	return color;
}


/* Set the given pixel in the LED_buffer with the desired color */
void Neo_SetPixel(uint16_t* LED_buffer, uint32_t pixel_idx, RGB colors)
{
	uint32_t buff_idx = 0;

	/* Out-of-range check */
	if(pixel_idx >= NEO_NUM_LEDS)
	{
		return;
	}


	buff_idx = NEO_BITS_INIT + (pixel_idx * NEO_BITS_LEDS);

	/* The order for transmission for WS2812 is Green,
	 * Red and Blue in that order. MSB is sent out first.
	 */
	for(uint8_t i = 0 ; i < NUM_COLORS; i++)
	{
		buff_idx = Neo_SetColor(LED_buffer, buff_idx, colors[i]);
	}
}


void Neo_PixelBrightness(uint16_t* LED_buffer, uint32_t pixel_idx, uint8_t percent)
{
	uint8_t colors[NUM_COLORS];
  RGB dimmed_colors;
  Neo_GetPixel(LED_buffer, pixel_idx, colors);

  for(uint8_t i = 0; i < NUM_COLORS; i++)
  {
  	dimmed_colors[i] = ((uint32_t)colors[i] * (100-percent))/100;
  }

  Neo_SetPixel(LED_buffer, pixel_idx, dimmed_colors);
}



void Neo_GetPixel(uint16_t* LED_buffer, uint32_t pixel_idx, uint8_t* colors)
{
  if (pixel_idx >= NEO_NUM_LEDS)
  {
    return;
  }

  pixel_idx = NEO_BITS_INIT + (pixel_idx * NEO_BITS_LEDS);

  for(uint8_t i = 0; i < NUM_COLORS; i++)
  {
  	colors[i] = Neo_GetColor(LED_buffer, pixel_idx + (i << 3));
  }

}


void Neo_PixelTrail(uint16_t* LED_buffer, RGB colors, uint32_t first_pixel_idx, uint32_t last_pixel_idx,
		uint32_t num_trail, uint8_t percent_dim)
{
  uint32_t pixel_num = 0;
  for(pixel_num = first_pixel_idx; pixel_num <= last_pixel_idx + num_trail + 1; pixel_num++)
  {
    if(pixel_num <= last_pixel_idx)
    {
      Neo_SetPixel(LED_buffer, pixel_num, colors);
    }
    if(pixel_num - first_pixel_idx > num_trail &&
    		pixel_num - (num_trail + 1) <= last_pixel_idx)
    {
      Neo_SetPixel(LED_buffer, (pixel_num - num_trail - 1), clear_pixel);
    }

    for(uint8_t i = 0; i < num_trail; i++)
    {
    	if ((pixel_num - first_pixel_idx > i) && (pixel_num - (i + 1) <= last_pixel_idx))
      {
        Neo_PixelBrightness(LED_buffer, pixel_num - i - 1, percent_dim);
      }
    }
    Neo_UpdateStrip();

    /* Delay */
    for(uint32_t i = 0; i< 100000; i++);
  }
}



