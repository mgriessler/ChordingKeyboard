/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*
 * ======== hal.h ========
 *
 * Device and board specific pins need to be configured here
 *
 */

// Only one of the following board defines should be enabled!
#define MSP430F5529LP       // F5529 LaunchPad
#define INTERRUPT_PIN   GPIO_PIN6

#define BUTTON_FAR_PORT         GPIO_PORT_P6
#define BUTTON_FAR_PIN          GPIO_PIN1
#define BUTTON_FAR_VECTOR       PORT6_VECTOR

#define BUTTON_CENTER_PORT      GPIO_PORT_P6
#define BUTTON_CENTER_PIN       GPIO_PIN0
#define BUTTON_CENTER_VECTOR    PORT6_VECTOR

#define BUTTON_NEAR_PORT        GPIO_PORT_P6
#define BUTTON_NEAR_PIN         GPIO_PIN5
#define BUTTON_NEAR_VECTOR      PORT6_VECTOR

#define BUTTON_INDEX_PORT       GPIO_PORT_P6
#define BUTTON_INDEX_PIN        GPIO_PIN2
#define BUTTON_INDEX_VECTOR     PORT6_VECTOR

#define BUTTON_MIDDLE_PORT      GPIO_PORT_P6
#define BUTTON_MIDDLE_PIN       GPIO_PIN6
#define BUTTON_MIDDLE_VECTOR    PORT6_VECTOR

#define BUTTON_RING_PORT        GPIO_PORT_P6
#define BUTTON_RING_PIN         GPIO_PIN3
#define BUTTON_RING_VECTOR      PORT6_VECTOR

#define BUTTON_PINKY_PORT       GPIO_PORT_P6
#define BUTTON_PINKY_PIN        GPIO_PIN4
#define BUTTON_PINKY_VECTOR     PORT6_VECTOR


/*----------------------------------------------------------------------------
 * The following function names are deprecated.  These were updated to new 
 * names to follow OneMCU naming convention.
 +---------------------------------------------------------------------------*/

#ifndef DEPRECATED
#define   initPorts       USBHAL_initPorts
#define   initClocks      USBHAL_initClocks
#define   initButtons     USBHAL_initButtons
#endif

void USBHAL_initPorts(void);
void USBHAL_initClocks(uint32_t mclkFreq);
void USBHAL_initButtons(void);
//Released_Version_5_20_06_02
