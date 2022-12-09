/*
 * neopixel_lib.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */

#include "neopixel_lib.h"
#include "led_out.h"
#include "common_defines.h"


#define BIT_0 (17) /* 17:60::0.35:1.25 */
#define BIT_1 (32) /* 32:60::0.7/1.3 */
#define RESET (0)
#define NUM_COLOR_BITS (8)
#define GET_MSB (0x80)

RGB clear_pixel = {0, 0, 0};

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


static uint8_t Neo_GetColor(uint16_t* LED_buffer, uint32_t in_idx)
{
	uint8_t color = 0;
	for(uint8_t i = 0; i < NUM_COLOR_BITS; i++)
	{
	   color <<= 1;
	   if (LED_buffer[in_idx] == BIT_1)
	   {
	      color |= 1;
	    }
	   in_idx++; /* next bit */
	 }
	return color;
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


//void Neo_Transfer(void)
//{
//	//DMA0 -> DMA[0].DCR |= DMA_DCR_ERQ_MASK;
//
//}


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



