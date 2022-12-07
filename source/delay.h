/*
 * File: delay.h
 *
 * This header file contains functions declarations and defines for
 * SysTick initialisation and creating the desired delay in
 * unit of 50 milliseconds.
 *
 * Author: Ritika Ramchandani <Ritika.Ramchandani@colorado.edu>
 *
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* Number of processor cycles required with a 48MHz clock for 1ms */
#define PROC_1_MS 48000000

/* Minimum unit used in delays and polls = 50 ms */
#define MIN_UNIT 500

typedef uint32_t ticktime_t;

/*
 * init_systick: Function to initialise the SysTick registers
 *
 * Parameters: none
 *
 * Returns: void
 */
void init_systick();


/*
 * now: Function that returns current system time
 *
 * Parameters: none
 *
 * Return: time since start-up
 *
 */
ticktime_t now();


/*
 * SysTick_msDelay: Function to create a delay in units of
 * 50 milliseconds
 *
 * Parameters:
 * 	delay: time in terms of 50 milliseconds
 *
 * Returns: void
 *
 */
void SysTick_msDelay(uint16_t delay);

uint32_t read_input_val();


#endif /* DELAY_H_ */
