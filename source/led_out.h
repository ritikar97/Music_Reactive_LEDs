/*
 * led_out.h
 *
 *  Created on: 7 Dec 2022
 *      Author: ritik
 */

#ifndef LED_OUT_H_
#define LED_OUT_H_

void GPIO_init();

void DMA_SetValues();

void Neo_output();

void clock_init();

void DMA_init();

void TPM0_init();


#endif /* LED_OUT_H_ */
