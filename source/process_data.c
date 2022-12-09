/*
 * process_data.c
 *
 *  Created on: 9 Dec 2022
 *      Author: ritik
 */

#include "common_defines.h"
#include "neopixel_lib.h"
#define GREEN (0)
#define RED (1)
#define BLUE (2)
#define MIN_SAMPLE (43000)
#define MAX_SAMPLE (56000)

uint8_t* calculate_color(uint32_t input_sample)
{
	uint8_t* colors = (uint8_t*)malloc(sizeof(uint8_t)*NUM_COLORS);
	if(input_sample < MIN_SAMPLE)
	{
		colors[RED] = 255;
		colors[GREEN] = 50;
		colors[BLUE] = 100;
	}
	else if(input_sample >= 48000 && input_sample < 48500)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 30;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 300;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 150;
	}
	else if(input_sample >= 48500 && input_sample < 49000)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 300;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 150;
	}
	else if(input_sample >= 49000 && input_sample < 49500)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 150;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 300;
	}
	else if(input_sample >= 49500 && input_sample < 50000)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 150;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 10;
	}
	else if(input_sample >= 50000 && input_sample < 50500)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 15;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 300;
	}
	else if(input_sample >= 50500 && input_sample < 51000)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 220;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 100;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 40;
	}
	else if(input_sample >= 51000 && input_sample < 51500)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 10;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 30;
	}
	else if(input_sample >= 51500 && input_sample < 52000)
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 100;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 100;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 100;
	}
	else
	{
		colors[RED] = (input_sample - MIN_SAMPLE) / 150;
		colors[GREEN] = (input_sample - MIN_SAMPLE) / 150;
		colors[BLUE] = (input_sample - MIN_SAMPLE) / 150;
	}
	return colors;
}

