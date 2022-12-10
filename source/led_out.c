/*
 * File: led_out.c
 *
 * This source file contains functions to output the
 * desired RGB values on the neopixel strip and
 * initialize the TPM1 and DMA for PWM
 *
 * Author: Ritika Ramchandani <ritika.ramchandani@colorado.edu>
 *
 * Reference: https://www.nxp.com/docs/en/application-note/AN5121.pdf
 */
#include "neopixel_lib.h"
#include "common_defines.h"
#include "led_out.h"

#define FIRST_LED (0) /* Index of first LED */
#define LAST_LED (20) /* Index of last LED */
#define TRAIL_LEN (6) /* Length of LED trail */
#define BRIGHTNESS_DIM (50) /* Trailing LED should be 50% dimmer than it's original value */


#define MUX_ALT4 (4) /* Alternate MUX Channel for TPM0_CH0 */
#define NEO_DMA_NUM_BYTES BUFF_SIZE /* Number of bytes to be transferred */

/* Pin 1 of Port C is used as digital output to LED strip */
#define NEO_DIG_IN (1)
#define NEO_DIG_IN_PORT (PTC)
#define NEO_DIG_IN_PCR (PORTC -> PCR[NEO_DIG_IN])

/* TPM0 Trigger for DMA */
#define TPM0_TRIG (24)

/* For WS28121B time period of 1.25us, 48MHz requires 60 ticks */
#define TPM0_MOD_VAL (60)

/* Mask to write set the desired bit */
#define MASK(x) (1UL << x)

/* Buffer to store all pixel values for the strip*/
uint16_t LED_buffer[BUFF_SIZE];

/* Variable to keep track of whether or not DMA transfers are done */
uint8_t transfer_done = 0;

/* Testing first LED with Green color*/
RGB colors_initial = {255, 0, 0};


void GPIO_init()
{
	/* Enabling clock to Port B and D for 3 LEDs */
	SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;

	/* Muxing pin to an alternate MUX slot */
	NEO_DIG_IN_PCR &= ~PORT_PCR_MUX_MASK;
	NEO_DIG_IN_PCR |= PORT_PCR_MUX(MUX_ALT4);

	/* Setting direction of GPIO pin (output) */
	NEO_DIG_IN_PORT -> PDDR |= MASK(NEO_DIG_IN);
}


void clock_init()
{
	/* Clock to DMA */
	SIM -> SCGC7 |= SIM_SCGC7_DMA_MASK;

	/* Clock to DMAMUX */
	SIM -> SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	/* Turn on clock to TPM */
	SIM -> SCGC6 |= SIM_SCGC6_TPM0_MASK;
}


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
	DMA0 -> DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | //DMA_DCR_DINC_MASK |
												DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
												DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	/* DMA disable request when byte count = 0, enable async requests */
	DMA0 -> DMA[0].DCR |= DMA_DCR_D_REQ_MASK | DMA_DCR_EADREQ_MASK;

	/* Configure NVIC for DMA ISR */
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	/* Enable DMA MUX channel with TPM0 overflow as trigger */
	DMAMUX0 -> CHCFG[0] = DMAMUX_CHCFG_SOURCE(TPM0_TRIG);
}


void TPM0_init()
{

	/* Set clock source for TPM */
	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	/* Disable TPM0 */
	TPM0 -> SC = 0;

	/* Set MOD and counter values for a time period of 1.25 us*/
	TPM0 -> MOD = TPM0_MOD_VAL;
	TPM0 -> CNT = 0;

	/* Continue operation in debug mode */
	TPM0 -> CONF |= TPM_CONF_DBGMODE(3);

	/* Set prescalar to 1 and timer counts in up counter mode */
	TPM0 -> SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0);

	/* High true pulses */
	TPM0 -> CONTROLS[0].CnSC &= TPM_CnSC_MSA(0) | TPM_CnSC_ELSA(0);
	TPM0 -> CONTROLS[0].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1) | TPM_CnSC_DMA_MASK;

	/* Channel 0 */
	TPM0 -> CONTROLS[0].CnV = 0;

	/* Start TPM0 timer */
	TPM0 -> SC |= TPM_SC_CMOD(1);
}


void DMA0_IRQHandler(void)
{
	/* Check for bus config err, config err, bus errors on source /dest */
	uint32_t errors = DMA_DSR_BCR_CE_MASK | DMA_DSR_BCR_BES_MASK |
			              DMA_DSR_BCR_BED_MASK | DMA_DSR_BCR_REQ_MASK;

	if (DMA0 -> DMA[0].DSR_BCR & errors)
	{
		PRINTF("Errors in DMA\n");
	}

	/* DMA done flag */
	DMA0 -> DMA[0].DSR_BCR |= DMA_DSR_BCR_BCR_MASK;

	transfer_done = 1;
}


void Neo_output()
{
  /* Clearing the LED */
	Neo_init(LED_buffer);

	/* Setting an intial color for the first LED for testing */
	Neo_SetPixel(LED_buffer, FIRST_LED, colors_initial);
}


void Neo_loop(RGB new_colors)
{
	/* Update the LED strip with a fading trail of a new color */
	Neo_PixelTrail(LED_buffer, new_colors, FIRST_LED, LAST_LED, TRAIL_LEN, BRIGHTNESS_DIM);
}


void DMA_SetValues()
{
	/* Initialize source and destination pointers */
	DMA0 -> DMA[0].SAR = DMA_SAR_SAR((uint32_t) &LED_buffer[0]);
	DMA0 -> DMA[0].DAR = DMA_DAR_DAR((uint32_t) &TPM0 -> CONTROLS[0].CnV);

	/* Byte count */
	DMA0 -> DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(NEO_DMA_NUM_BYTES * 2);

	/* Set enable flag */
	DMAMUX0 -> CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;

	/*Set Enable Peripheral Request */
	DMA0 -> DMA[0].DCR |= DMA_DCR_ERQ_MASK;
}


/* Update the LED strip by starting DMA and waiting
 * for transfer to end */
void Neo_UpdateStrip()
{
	DMA_SetValues();
	while(!transfer_done);
  transfer_done = 0;
}




