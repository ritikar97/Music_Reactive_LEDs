/*
 * neopixel_lib.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */

#include "neopixel_lib.h"
#include "common_defines.h"


#define BIT_0 (17) /* 17:60::0.35:1.25 */
#define BIT_1 (32) /* 32:60::0.7/1.3 */
#define RESET (0)
#define NUM_COLOR_BITS (8)
#define GET_MSB (0x80)


static void clear_LED_buffer(uint16_t* LED_buffer)
{
  uint32_t i;

  for(i = 0; i < NEO_BITS_INIT; i++)
  {
  	LED_buffer[i] = 0; /* pre sequence */
  }

  Neo_ClearAllPixel(LED_buffer);

  for(i = NEO_NUM_LEDS + (NEO_NUM_LEDS * NEO_BITS_LEDS); i < BUFF_SIZE; i++)
  {
  	LED_buffer[i] = 0; /* post sequence */
  }
}


void Neo_init(uint16_t* LED_buffer)
{
	clear_LED_buffer(LED_buffer);
	//TPM0_init();
	//DMA_init();
}


void Neo_ClearAllPixel(uint16_t* LED_buffer)
{
	RGB val = {0, 0, 0};
	for(uint8_t i = 0; i < NEO_NUM_LEDS; i++)
	{
		Neo_SetPixel(LED_buffer, i, val);
	}

}


static uint32_t Neo_SetColor(uint16_t* LED_buffer, uint32_t in_idx, uint8_t color)
{
	for(uint8_t i = 0 ; i < NUM_COLOR_BITS; i++)
	{
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


void Neo_SetPixel(uint16_t* LED_buffer, uint32_t pixel_idx, RGB colors)
{
	uint32_t buff_idx = 0;

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


void Neo_Transfer(void)
{
	//DMA0 -> DMA[0].DCR |= DMA_DCR_ERQ_MASK;

}
