/*
 * File: led_out.h
 *
 * This header file contains function declarations to output the
 * desired RGB values on the neopixel strip and
 * initialize the TPM1 and DMA for PWM
 *
 * Author: Ritika Ramchandani <ritika.ramchandani@colorado.edu>
 *
 */

#ifndef LED_OUT_H_
#define LED_OUT_H_


/*
 * GPIO_init: Enables clocks to for the the digital output pin, initialises pin
 * mux to TPM0_CH0 mode, sets GPIO pins as output
 *
 * Parameters: none
 *
 * Returns: void
 *
 */
void GPIO_init();


/*
 * DMA_SetValues: Configures source and destination
 * parameters and starts DMA transfer.
 *
 * Parameters: none
 *
 * Returns: void
 *
 */
void DMA_SetValues();


/*
 * Neo_output: Initialized the LED buffer to 0 and
 * sets an intial color for the first pixel
 *
 * Parameters: none
 *
 * Returns: void
 *
 */
void Neo_output();


/*
 * clock_init: Enables clocks to TPM0, DMA and DMAMUX
 *
 * Parameters: none
 *
 * Returns: void
 *
 */
void clock_init();


/*
 * DMA_init: Initialization routine for DMA
 *
 * Parameters: none
 *
 * Returns: void
 */
void DMA_init();


/*
 * TPM0_init: Initialization routine for TPM0
 *
 * Parameters: none
 *
 * Returns: void
 */
void TPM0_init();


/*
 * Neo_UpdateStrip: Updates the LED strip by starting DMA and waiting
 * for transfer to end
 *
 * Parameters: none
 *
 * Returns: void
 *
 */
void Neo_UpdateStrip();


/*
 * Neo_loop: Updates the LED strip with a fading trail of a new color
 *
 * Parameters:
 * new_colors - The RGB values of the trail
 *
 * Returns: void
 *
 */
void Neo_loop(RGB new_colors);


#endif /* LED_OUT_H_ */
