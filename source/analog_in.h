/*
 * analog_in.h
 *
 * This header file contains function headers to initialize ADC and TPM1
 * and sample ADC.
 *
 * Author: Ritika Ramchandani <ritika.ramchandani@colorado.edu>
 *
 * Reference: Embedded Systems Fundamentals by Alexander G. Dean -
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code
 *
 */

#ifndef ANALOG_IN_H_
#define ANALOG_IN_H_

#include <stdlib.h>
#include "MKL25Z4.h"


/*
 * TPM1_init: Initialization routine for TPM1
 *
 * Parameters: none
 *
 * Returns: void
 */
void TPM1_init();


/*
 * ADC_init: Initialization routine for ADC0
 *
 * Parameters: none
 *
 * Returns: void
 */
void ADC_init();


/*
 * ADC_sampling: Function to sample input analog wave
 * and store the values in a buffer
 *
 * Parameters: none
 *
 * Returns: void
 */
uint32_t ADC_sampling();




#endif /* ANALOG_IN_H_ */
