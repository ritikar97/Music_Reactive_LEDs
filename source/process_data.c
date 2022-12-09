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
#define MOD_4 (0x3)

uint8_t constant_multipliers[3][3] = {{255, 25, 2}, {2, 255, 25}, {25, 2, 255}};

void calculate_color(uint32_t input_sample, uint8_t* colors)
{
	uint8_t remainder = input_sample % 3;

	PRINTF("Input sample is %d and remainder is %d\n", input_sample, remainder);

	colors[RED] = constant_multipliers[remainder][0];// * (input_sample - MIN_SAMPLE) * 10) / 60000;
	colors[GREEN] = constant_multipliers[remainder][1];// * (input_sample - MIN_SAMPLE) * 10) / 60000;
	colors[BLUE] = constant_multipliers[remainder][2]; //* (input_sample - MIN_SAMPLE) * 10) / 60000;


//	if(remainder == 0)
//	{
//		colors[RED] = (255 * (input_sample - MIN_SAMPLE) * 1000) / 60000;
//		colors[RED] = (25 * (input_sample - MIN_SAMPLE) * 1000) / 60000;
//		colors[RED] = (2 * (input_sample - MIN_SAMPLE) * 1000) / 60000;
//	}
//	else if(remainder == 1)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 30;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 300;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 300;
//	}
//	else if(remainder == 2)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 400;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 10;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 300;
//	}
//	else
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 300;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 100;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 20;
//	}

//	if(input_sample < MIN_SAMPLE)
//	{
//		colors[RED] = 255;
//		colors[GREEN] = 50;
//		colors[BLUE] = 100;
//	}
//	else if(input_sample >= 48000 && input_sample < 48500)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 30;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 300;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 150;
//	}
//	else if(input_sample >= 48500 && input_sample < 49000)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 300;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 150;
//	}
//	else if(input_sample >= 49000 && input_sample < 49500)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 150;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 300;
//	}
//	else if(input_sample >= 49500 && input_sample < 50000)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 150;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 10;
//	}
//	else if(input_sample >= 50000 && input_sample < 50500)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 15;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 300;
//	}
//	else if(input_sample >= 50500 && input_sample < 51000)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 220;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 100;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 40;
//	}
//	else if(input_sample >= 51000 && input_sample < 51500)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 10;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 30;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 30;
//	}
//	else if(input_sample >= 51500 && input_sample < 52000)
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 100;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 100;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 100;
//	}
//	else
//	{
//		colors[RED] = (input_sample - MIN_SAMPLE) / 150;
//		colors[GREEN] = (input_sample - MIN_SAMPLE) / 150;
//		colors[BLUE] = (input_sample - MIN_SAMPLE) / 150;
//	}
}

