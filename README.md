# Music_Reactive_LEDs
Code for Final Project of PES, Fall 2022, ECEN-5813(B)


## Table of Contents

- [Project Functionality](#project-functionality)
- [Report](#report)
- [Challenges](#challenges)
- [Demo Video](#demo-video)
- [References](#references)
- [Acknowledgements](#acknowledgement)


## Project Functionality 

The objective of this project was to build a music reactive LED strip that ran on KL25Z, with the help of FreeRTOS. A neopixel strip was connected to the microcontroller, which glowed in different colors based on the amplitude of the sound sensed by the external microphone sensor.  

A function library was developed in accordance with the WS2812B protocol, to address to individually accessible LEDs on the neopixel strip.

All the requirements laid out in the project proposal were met and nothing was left incomplete. 

## Report

A brief report of the project can be found [here](https://github.com/ritikar97/Music_Reactive_LEDs/blob/main/PES-Final-Project-Report.pdf).

## Challenges

I ran into several memory (heap and stack overflow challenges while working with the LED Buffer and the stack sizes for spawing threads.
Initializing DMA and TPM0 to continuously generate PWM pulses with precise timing also required considerable effort. 

## Demo Video



## References 

[WS2812B reference](https://cdn-shop.adafruit.com/datasheets/WS2812.pdf)   
[Alexander G. Dean for initialization routines](https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)  
[Generating continuous PWM pulses - NXP App Note](https://www.nxp.com/docs/en/application-note/AN5121.pdf)  
[Neopixel Library reference](https://github.com/ErichStyger/mcuoneclipse/tree/master/Examples/Eclipse/FRDM-KL25Z/FRDM-KL25Z_NeoPixel)  

## Acknowledgements 

I would like to thank Nimish Bhide for his time to help me debug several of my issues, and Ajay Kandagal for his help with RTOS. 



 
