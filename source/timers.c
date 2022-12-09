/*
 * timers.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */


#include "timers.h"
#include "common_defines.h"


#define TIME_PERIOD (60) /* ((1/48MHz) * 1.25us) */

/* TPM0 intialization */
//void TPM0_init()
//{
//	/* Turn on clock to TPM */
//	SIM -> SCGC6 |= SIM_SCGC6_TPM0_MASK;
//
//	/* Set clock source for TPM */
//	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
//
//	/* Disable TPM */
//	TPM0 -> SC = TPM_SC_CMOD(0);
//
//	/* Load the counter and mod */
//	TPM0 -> CNT = 0;
//	TPM0 -> MOD = TPM_MOD_MOD(TIME_PERIOD);
//	TPM0 -> CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
//
//	/* Set TPM to count up and divide by 0 prescalar and enable DMA on overflow */
//	TPM0 -> SC = (TPM_SC_DMA_MASK | TPM_SC_PS(0));
//
//	/* Start TPM0 count */
//	TPM0 -> SC |= TPM_SC_CMOD(1);
//}

void TPM0_init()
{
	/* Turn on clock to TPM */
	SIM -> SCGC6 |= SIM_SCGC6_TPM0_MASK;

	/* Set clock source for TPM */
	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	TPM0 -> SC = TPM_SC_CPWMS(0) | TPM_SC_CMOD_MASK;

	TPM0 -> MOD = 59;

	TPM0 -> CONTROLS[0].CnSC &= TPM_CnSC_MSA(0) | TPM_CnSC_ELSA(0);

	TPM0 -> CONTROLS[0].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1) | TPM_CnSC_DMA_MASK;

	TPM0 -> CONTROLS[0].CnV = 0;

}

//void TPM0_IRQHandler(void)
//{
//		TPM0 -> SC |= TPM_SC_TOF_MASK;
//
//		/* Disable TPM */
//		TPM0 -> SC = TPM_SC_CMOD(0);
//		TPM0 -> CNT = 0;
//		TPM0 -> SC &= ~TPM_SC_TOIE_MASK;
//		TPM0 -> CONTROLS[0].CnSC |= TPM_CnSC_DMA_MASK;
//
//		//Check
//		DMA0 -> DMA[0].DCR |= DMA_DCR_ERQ_MASK;
//
//}
