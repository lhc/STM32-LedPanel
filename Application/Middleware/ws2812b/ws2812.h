#ifndef __WS2812_H
#define __WS2812_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include <stdio.h>
#include <string.h>
#include "setup_hw.h"
#include "led_panel/led_panel.h"

//==============================================================================
// PUBLIC DEFINITIONS
//==============================================================================

#define constLED_NUMBER     (configPAINEL_LED_WIDTH * configPAINEL_LED_HEIGHT)//	how many LEDs the MCU should control?

//==============================================================================
// PUBLIC TYPEDEFS
//==============================================================================

//==============================================================================
// PUBLIC VARIABLES
//==============================================================================

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

void ws2812b_pwm_attach( TIM_HandleTypeDef *htim, uint32_t channel);
void ws2812_update(void);
void ws2812_set_ledColor(uint32_t LEDnumber, RGB_t color);
void ws2812_set_wholeColor(RGB_t color);
void ws2812_fill_bufferBlack(void);
void ws2812_fill_bufferWhite(void);
void ws2812_clearBuffer(void);

/* C++ detection */
#ifdef __cplusplus
}
#endif


#endif /* __WS2812_H */
