/*
 * led_out.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */
#include "neopixel_lib.h"
#include "MKL25Z4.h"

#define NEO_DMA_NUM_BYTES sizeof(LED_buffer)

uint16_t LED_buffer[NEO_BITS_INIT + (NEO_NUM_LEDS * NEO_BITS_LEDS) + NEO_BITS_LATCH];

void DMA_SetValues()
{
	/* Initialize source and destination pointers */
	DMA0 -> DMA[0].SAR = DMA_SAR_SAR((uint32_t) &LED_buffer[0]);
	DMA0 -> DMA[0].DAR = DMA_DAR_DAR((uint32_t) &TPM0_C1V);

	/* Byte count */
	DMA0 -> DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(NEO_DMA_NUM_BYTES);

	/* Clear done flag */
	//DMA0 -> DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;

	/* Set enable flag */
	//DMAMUX0 -> CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}
