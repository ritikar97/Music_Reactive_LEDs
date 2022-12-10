/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MKL25Z4_Project.c
 * @brief   Application entry point.
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "pin_mux.h"
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "analog_in.h"
#include "neopixel_lib.h"
#include "led_out.h"

/* Task priorities. */
#define ADC_task_PRIORITY (configMAX_PRIORITIES - 1)
#define neopixel_task_PRIORITY (configMAX_PRIORITIES - 3)
#define process_task_PRIORITY (configMAX_PRIORITIES - 2)

/* For WS128B, the order for storing color values
 * is green, red and blue */
#define GREEN (0)
#define RED (1)
#define BLUE (2)

/* Constant multiplier to calculate RGB values */
#define CONST_MUL (16)
#define RED_MASK (0xF) /* Mask to calculate red value */
#define GREEN_MASK (0xF0) /* Mask to calculate green value */
#define BLUE_MASK (0xF00) /* Mask to calculate blue value */

/* Delay for 1ms in number of ticks */
#define DELAY_1MS (1000)

/* Task Prototypes */
static void ADC_task(void *pvParameters);
static void neopixel_task(void *pvParameters);
static void process_task(void *pvParameters);

/* Task handles for accessing the tasks later if needed */
TaskHandle_t ADC_handle;
TaskHandle_t neopixel_handle;
TaskHandle_t process_handle;

QueueHandle_t xQueue_sample; /* Handle to access queue */
SemaphoreHandle_t xMutex; /* Handle to access mutex */

/* Array to store color values */
uint8_t colors[NUM_COLORS];

/* Main function that spwans three threads to run in parallel with different priorities */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    /* Create mutex*/
    xMutex = xSemaphoreCreateMutex();

    /* Initialize peripherals */
    clock_init();
    ADC_init();
    TPM1_init();
    GPIO_init();
    DMA_init();
    TPM0_init();
    Neo_output();

    /* Create queue */
    xQueue_sample = xQueueCreate(1, sizeof(uint32_t));

    /* Creating three tasks:
     * One for analog sampling (audio collection)
     * One for processing the collected samples
     * One for updating the neopixel LED strip with a new trail
     */
    xTaskCreate(ADC_task, "ADC_task", 512, NULL, ADC_task_PRIORITY, &ADC_handle);
    xTaskCreate(neopixel_task, "neopixel_task", 512, NULL, neopixel_task_PRIORITY, &neopixel_handle);
    xTaskCreate(process_task, "process_task", 512, NULL, process_task_PRIORITY, &process_handle);

    /* Spawn the three threads and start in parallel.
     * The tasks are run according to their priorities */
    vTaskStartScheduler();
    while(1);

    return 0 ;
}


/* Task for analog sampling (audio collection) */
static void ADC_task(void *pvParameters)
{
	uint32_t input_sample;

	while(1)
	{
		/* Collect ADC sample and write it into the queue */
		input_sample = ADC_sampling();
		if(xQueueOverwrite(xQueue_sample, (void*)&input_sample) != pdPASS)
		{
			PRINTF("Could not write to queue\n");
		}
		vTaskDelay(DELAY_1MS/portTICK_PERIOD_MS);
	}
}


/* Task processing the collected samples */
static void process_task(void *pvParameters)
{
	uint32_t input_sample = 0;

	while(1)
	{
		/* Wait for queue to receive the input sample */
		if(xQueueReceive(xQueue_sample, (void*)&input_sample, 0) == pdTRUE)
		{
			/* Protect colors with a mutex to prevent writing while
			 * another task is reading the array */
			xSemaphoreTake(xMutex, portMAX_DELAY);

			/* Update color values based on logic of choice */
			colors[RED] = (input_sample & RED_MASK) * CONST_MUL;
			colors[GREEN] = ((input_sample & GREEN_MASK) >> 4) * CONST_MUL;
			colors[BLUE] = ((input_sample & BLUE_MASK) >> 8) * CONST_MUL;
			xSemaphoreGive(xMutex);

			/* Once color values have been updated, neopixel task can be called */
			vTaskResume(neopixel_handle);
		}

		vTaskDelay(DELAY_1MS/portTICK_PERIOD_MS);
	}
}


/* Task updating the neopixel LED strip with a new trail */
static void neopixel_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Neo_loop(colors); /* Update LED strip*/
		xSemaphoreGive(xMutex);
		vTaskSuspend(NULL); /* Suspend task until new values are calculated */
	}

}


