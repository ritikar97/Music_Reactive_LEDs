/*
 * timers.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */


#include "timers.h"

#define TIME_PERIOD (60) /* ((1/48MHz) * 1.25us) */

/* TPM0 intialization */
void TPM0_init()
{
	/* Turn on clock to TPM */
	SIM -> SCGC6 |= SIM_SCGC6_TPM0_MASK;

	/* Set clock source for TPM */
	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	/* Disable TPM */
	TPM0 -> SC = TPM_SC_CMOD(0);

	/* Load the counter and mod */
	TPM0 -> CNT = 0;
	TPM0 -> MOD = TPM_MOD_MOD(TIME_PERIOD);

	/* Set TPM to count up and divide by 0 prescalar and enable DMA on overflow */
	TPM0 -> SC = (TPM_SC_DMA_MASK | TPM_SC_PS(0));

	/* Start TPM0 count */
	TPM0 -> SC |= TPM_SC_CMOD(1);
}
