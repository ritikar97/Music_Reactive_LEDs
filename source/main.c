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
#include "process_data.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Task priorities. */
#define ADC_task_PRIORITY (configMAX_PRIORITIES - 1)
#define neopixel_task_PRIORITY (configMAX_PRIORITIES - 2)
#define process_tak_PRIORITY (configMAX_PRIORITIES - 3)
#define GREEN (0)
#define RED (1)
#define BLUE (2)

/* Task Prototypes */
static void ADC_task(void *pvParameters);
static void neopixel_task(void *pvParameters);
static void process_task(void *pvParameters);

TaskHandle_t ADC_handle;
TaskHandle_t neopixel_handle;
TaskHandle_t process_handle;

QueueHandle_t xQueue_sample;
SemaphoreHandle_t xMutex;

uint8_t colors[NUM_COLORS];


/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    xMutex = xSemaphoreCreateMutex();
    PRINTF("Hello World\n");
    clock_init();
    ADC_init();
    TPM1_init();
    GPIO_init();
    DMA_init();
    TPM0_init();
    Neo_output();

    xQueue_sample = xQueueCreate(1, sizeof(uint32_t));

    xTaskCreate(ADC_task, "ADC_task", configMINIMAL_STACK_SIZE + 10, NULL, ADC_task_PRIORITY, &ADC_handle);
    xTaskCreate(neopixel_task, "neopixel_task", configMINIMAL_STACK_SIZE + 10, NULL, neopixel_task_PRIORITY, &neopixel_handle);
    xTaskCreate(process_task, "process_task", configMINIMAL_STACK_SIZE + 10, NULL, ADC_task_PRIORITY, &process_handle);


    vTaskStartScheduler();
    while(1)
    {
    }

    return 0 ;
}


static void ADC_task(void *pvParameters)
{
	uint32_t input_sample = ADC_sampling();

	uint32_t TickDelay = pdMS_TO_TICKS(20);
	PRINTF("Inside ADC task\n");

	while(1)
	{
		if(xQueueSend(xQueue_sample, &input_sample, 0) != pdPASS)
		{
			PRINTF("ERROR in adding to queue\n");
		}
		vTaskDelay(TickDelay);
	}
}


static void process_task(void *pvParameters)
{
	uint32_t input_sample = 0;
	uint32_t TickDelay = pdMS_TO_TICKS(30);
	PRINTF("Inside process task\n");

	//Wait on Queue Receieve
	while(1)
	{
		if (xQueueReceive(xQueue_sample, &input_sample, portMAX_DELAY) == pdTRUE)
		{
			xSemaphoreTake(xMutex, portMAX_DELAY);
			colors[RED] = (input_sample & 0xF) * 16;
			colors[GREEN] = ((input_sample & 0xF0) >> 4) * 16;
			colors[BLUE] = ((input_sample & 0xF00) >> 8) * 16;
			xSemaphoreGive(xMutex);

			vTaskResume(neopixel_handle);
		}

		vTaskDelay(TickDelay);
	}
}


static void neopixel_task(void *pvParameters)
{
	PRINTF("Inside neopixel task\n");
	xSemaphoreTake(xMutex, portMAX_DELAY);
	Neo_loop(colors);
	xSemaphoreGive(xMutex);

	vTaskSuspend(NULL);
}


