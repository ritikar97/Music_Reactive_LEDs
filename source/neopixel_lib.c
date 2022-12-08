/*
 * neopixel_lib.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */

#include "neopixel_lib.h"


#define BIT_0 (17) /* 17:60::0.35:1.25 */
#define BIT_1 (32) /* 32:60::0.7/1.3 */
#define RESET (0)
#define NUM_COLOR_BITS (8)
#define NUM_COLORS (3)
#define GET_MSB (0x80)



typedef uint8_t RGB[NUM_COLORS];



static void clear_LED_buffer(uint32_t* LED_buffer)
{
  uint32_t i;

  for(i = 0; i < NEO_BITS_INIT; i++)
  {
  	LED_buffer[i] = 0; /* pre sequence */
  }

  Neo_ClearAllPixel();

  for(i = NEO_NUM_LEDS + (NEO_NUM_LEDS * NEO_BITS_LEDS); i < sizeof(LED_buffer)/sizeof(LED_buffer[0]); i++)
  {
  	LED_buffer[i] = 0; /* post sequence */
  }
}

void neo_init(void)
{
	clear_LED_buffer();
	TPM0_init();
	DMA_init();
}

void Neo_ClearAllPixel()
{
	RGB val = {0, 0, 0};
	for(i = 0; i < NEO_NUM_LEDS; i++)
	{
		Neo_SetPixel(i, val);
	}

}


static uint32_t Neo_SetColor(uint32_t* LED_buffer, uint32_t in_idx, uint8_t color)
{
	for(uint8_t i = 0 ; i < NUM_COLOR_BITS; i++)
	{
		if(color & GET_MSB)
		{
			LED_buffer[in_idx] = BIT1;
		}
		else
		{
			LED_buffer[in_idx] = BIT0;
		}
		color <<= 1;
		in_idx++;
	}

	return in_idx;
}


void Neo_SetPixel(uint32_t pixel_idx, RGB colors)
{
	uint32_t buff_idx = 0;

	if(pixel_idx >= NEO_NUM_LEDS)
	{
		return;
	}

	buff_idx = NEO_BITS_INIT + (idx * NEO_BITS_LEDS);

	/* The order for transmission for WS2812 is Green,
	 * Red and Blue in that order. MSB is sent out first.
	 */
	for(uint8_t i = 0 ; i < NUM_COLORS; i++)
	{
		buff_idx = Neo_SetColor(buff_idx, colors[i]);
	}
}
