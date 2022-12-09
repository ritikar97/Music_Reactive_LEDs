/*
 * analog_in.c
 *
 * This source file contains functions to initialize ADC and TPM1
 * and sample ADC.
 *
 * Author: Ritika Ramchandani <ritika.ramchandani@colorado.edu>
 *
 * Reference: Embedded Systems Fundamentals by Alexander G. Dean -
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code
 *
 */

#include "analog_in.h"
#include <stdio.h>
#include "fsl_debug_console.h"
#include "common_defines.h"



#define MOD_VAL (48000) /* (48MHz / 0.33 Hz) : Sampling takes place once in 3 seconds */
#define ADC_POS (20) /* PORT E, pin 20 is used an input for ADC */
#define SAMPLING_SIZE (1024) /* ADC sampling size */
#define AD0_CH (0) /* ADC channel 0 is used to collect ADC input */
#define ADC0_TPM1_TRIG (9) /* Using TPM1 as hardware trigger for ADC */
#define SAMPLING_RATE (96000) /* Sampling frequency */


/* Buffer to hold ADC samples */
uint16_t adc_sample_buff[SAMPLING_SIZE];
int adc_period;
uint32_t min = 50000;
uint32_t max = 48000;


/* TPM1 Initialization */
void TPM1_init()
{
	/* Turn on clock to TPM */
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	/* Set clock source for TPM */
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	/* Disable TPM */
	TPM1->SC |= TPM_SC_CMOD(0);

	/* Load the counter and mod */
	TPM1 -> CNT = 0;
	TPM1 -> MOD = TPM_MOD_MOD(MOD_VAL);

	/* Set TPM to count up and divide by 0 prescalar */
	TPM1 -> SC |= (TPM_SC_PS(0));

}


/* ADC Initialization */
void ADC_init()
{
	/* Enabling clock to ADC and PORT E */
	SIM -> SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM -> SCGC5 |= SIM_SCGC5_PORTE_MASK;

	/* Select TPM1 as ADC trigger, alternate trigger selected */
	SIM -> SOPT7 |= SIM_SOPT7_ADC0TRGSEL(ADC0_TPM1_TRIG) | SIM_SOPT7_ADC0ALTTRGEN(1);

	/* Select analog pin */
	PORTE->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);

	/* 16 bit single-ended conversion, bus clock input */
	ADC0 -> CFG1 |=  ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

	/* Hardware trigger, voltage references VREFH and VREFL */
	ADC0 -> SC2 |= ADC_SC2_REFSEL(0) | ADC_SC2_ADTRG(1);

	/* Conversion interrupt disabled, input channel 0 is selected */
	ADC0->SC1[0] = ADC_SC1_AIEN(0) | ADC_SC1_ADCH(AD0_CH);
}


/* Collecting ADC Samples */
uint32_t ADC_sampling()
{
	uint32_t adc_sample;

	/* Start TPM1 */
	TPM1 -> SC |= TPM_SC_CMOD(1);

	/* Check for conversion completion and fill buffer*/
	for(uint32_t i = 0; i < 200; i++)
	{
		/* Wait on completion flag */
		while(!(ADC0 -> SC1[0] & ADC_SC1_COCO_MASK));
		adc_sample = ADC0 -> R[0];
		if(adc_sample > max)
		{
			max = adc_sample;
		}
		if(adc_sample < min)
		{
			min = adc_sample;
		}

	}

	/* Stop TPM1 */
	TPM1 -> SC |= TPM_SC_CMOD(0);

	/* Get ADC period in terms of number of samples */
	//adc_period = autocorrelate_detect_period(adc_sample_buff, SAMPLING_SIZE, kAC_16bps_unsigned);

	/* Print analysis data */
	//DAC_analysis();
	//ADC_analysis();
	//for(uint32_t i = 0; i < 1024; i++)
	//{
	 //}
	return adc_sample;
}



