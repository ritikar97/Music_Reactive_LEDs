/*
 * File: delay.c
 *
 * This source file contains functions definitions for
 * SysTick initialisation and creating the desired delay in
 * unit of 50 milliseconds.  It also has an interrupt handler that
 * keep track of time since startup.
 *
 * Author: Ritika Ramchandani <Ritika.Ramchandani@colorado.edu>
 *
 */

#include "delay.h"
#include "MKL25Z4.h"


/* To keep track of time since start-up */
ticktime_t t_val = 0;
uint32_t digital_in = 5;

void init_systick()
{
	t_val = 0;

	/* Loading the delay value */
	SysTick -> LOAD = (PROC_1_MS - 1);

	NVIC_SetPriority(SysTick_IRQn, 3);

	SysTick -> VAL = 0;


	/* Enabling SysTick, using the processor clock
	 * and enabling interrupt */
	SysTick -> CTRL |=
			SysTick_CTRL_ENABLE_Msk |
			SysTick_CTRL_CLKSOURCE_Msk |
			SysTick_CTRL_TICKINT_Msk;

}


ticktime_t now()
{
	return t_val;
}


void SysTick_msDelay(uint16_t delay)
{

	for(unsigned long i = 0; i < MIN_UNIT*delay ; i++)
	{

		/* Loading the delay value */
		SysTick -> LOAD = (24000000);

		/* Resetting the count flag */
		SysTick -> VAL = 0;

		/*Waiting for count flag to go high*/
		while(((SysTick -> CTRL) & SysTick_CTRL_COUNTFLAG_Msk) == 0);

	}


}

void SysTick_Handler()
{
	/* Increment t_val every ms */
	digital_in = PTE -> PDIR;
	t_val++;
}

uint32_t read_input_val()
{
	PRINTF("Tval = %d\n", t_val);
	return digital_in;
}





