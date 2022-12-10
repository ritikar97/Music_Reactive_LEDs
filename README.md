# Music_Reactive_LEDs
Code for Final Project of PES, Fall 2022, ECEN-5813(B)


## Table of Contents

- [Project Functionality](#project-functionality)
- [Report](#report)
- [Challenges](#challenges)
- [Demo Video](#demo-video)
- [References](#references)
- [Acknowledgement](#acknowledgement)


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

## Acknowledgement




 
