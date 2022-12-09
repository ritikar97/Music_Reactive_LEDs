/*
 * dma.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */


#include "dma.h"
#include "common_defines.h"

#define TPM0_TRIG (54)


void DMA_init()
{
	/* Clock to DMA */
	SIM -> SCGC7 |= SIM_SCGC7_DMA_MASK;

	/* Clock to DMAMUX */
	SIM -> SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	/* Disable DMA channel to allow configuration */
	DMAMUX0 -> CHCFG[0] = 0;


	/* Generate DMA interrupt when done
	 * Increment source, transfer words (16 bits)
	 * Enable peripheral request */
	DMA0 -> DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | DMA_DCR_DINC_MASK |
												DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
												DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK | DMA_DCR_D_REQ_MASK
												| DMA_DCR_EADREQ_MASK;

	/* Configure NVIC for DMA ISR */
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	/* Enable DMA MUX channel with TPM0 overflow as trigger */
	DMAMUX0 -> CHCFG[0] = DMAMUX_CHCFG_SOURCE(TPM0_TRIG);
}


