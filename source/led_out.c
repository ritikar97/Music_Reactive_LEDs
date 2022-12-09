/*
 * led_out.c
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */
#include "neopixel_lib.h"
#include "common_defines.h"

#define MUX_ALT3 (3)
#define NEO_DMA_NUM_BYTES BUFF_SIZE
#define NEO_DIG_IN (1)
#define NEO_DIG_IN_PORT (PTC)
#define NEO_DIG_IN_PCR (PORTC -> PCR[NEO_DIG_IN])

/* Mask to write set the desired bit */
#define MASK(x) (1UL << x)

uint16_t LED_buffer[BUFF_SIZE];
uint16_t dummy_buffer[BUFF_SIZE] = {0};
uint8_t transfer_done = 0;

RGB colors_initial = {255, 255, 0};
uint8_t num_bytes_transferred = 0;


void GPIO_init()
{
	/* Enabling clock to Port B and D for 3 LEDs */
		SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;

		/* Muxing pin to an alternate MUX slot */
		NEO_DIG_IN_PCR &= ~PORT_PCR_MUX_MASK;
		NEO_DIG_IN_PCR |= PORT_PCR_MUX(MUX_ALT3);

		/* Setting direction of GPIO pins */
		NEO_DIG_IN_PORT -> PDDR |= MASK(NEO_DIG_IN);
}


void DMA_SetValues()
{
	PRINTF("Value of num_bytes_transferred inside = %d\n", num_bytes_transferred);
	/* Initialize source and destination pointers */
	DMA0 -> DMA[0].SAR = DMA_SAR_SAR((uint32_t) &LED_buffer[0]);
	DMA0 -> DMA[0].DAR = DMA_DAR_DAR((uint32_t) &dummy_buffer[0]);//&TPM0 -> CONTROLS[0].CnV);

	/* Byte count */
	DMA0 -> DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(NEO_DMA_NUM_BYTES);

	/* Clear done flag */
	DMA0 -> DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;

	/* Set enable flag */
	DMAMUX0 -> CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}


void DMA0_IRQHandler(void)
{
	//transfer_done = 1;
	uint32_t status;

	status = DMA0 -> DMA[0].DSR_BCR & DMA_DSR_BCR_BCR_MASK;

	if((status & DMA_DSR_BCR_BED_MASK) || (status & DMA_DSR_BCR_BES_MASK)
			|| (status & DMA_DSR_BCR_CE_MASK))
	{
		PRINTF("ERROR\n");
	}

	if(status & DMA_DSR_BCR_DONE_MASK)
	{
		DMA0 -> DMA[0].DSR_BCR = 0;
	}

	/* Clear done flag */
//	DMA0 -> DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
//
//	num_bytes_transferred++;

	/* Continue DMA playback */
	//DMA_SetValues();

//	if(num_bytes_transferred == NEO_DMA_NUM_BYTES)
//	{
//		DMAMUX0 -> CHCFG[0] &= ~DMAMUX_CHCFG_ENBL_MASK;
//		transfer_done = 1;
//	}

	//TPM0 -> SC |= TPM_SC_TOIE_MASK;
	//TPM0 -> CONTROLS[0].CnSC &= ~TPM_CnSC_DMA_MASK;

	transfer_done = 1;




}


void Neo_output()
{
  Neo_init(LED_buffer);

  for(uint8_t i = 0; i < NEO_DMA_NUM_BYTES; i++)
  {
  	dummy_buffer[i] = 0;
  }

  PRINTF("After init\n");
	Neo_SetPixel(LED_buffer, 0, colors_initial);

	for(uint8_t i = 0; i < NEO_DMA_NUM_BYTES; i++)
	{
		PRINTF("LED_buffer[%d] = %d\n", i, LED_buffer[i]);
	}

	PRINTF("After set pixel\n");
	DMA_SetValues();
//	PRINTF("After DMA\n");
	while(!transfer_done);
	PRINTF("Value of num_bytes_transferred = %d\n", num_bytes_transferred);
	for(uint8_t i = 0; i < NEO_DMA_NUM_BYTES; i++)
	{
		PRINTF("DUMMY Buffer [%d] = %d\n", i, dummy_buffer[i]);
	}
	//PRINTF("After DMA++\n");
	//Neo_Transfer();
	transfer_done = 0;
}
