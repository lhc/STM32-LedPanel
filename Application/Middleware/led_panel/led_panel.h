/**
 * @file    ws2812b.h
 * @author  Jorge Guzman
 * @date    Fev 7, 2019
 * @brief   Bibliteoca para o uso dos Leds ws2812b
 */

#ifndef _LED_PANEL_H_
#define _LED_PANEL_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// CHECK TO ENABLE LIBRARY
//==============================================================================

#include "setup_hw.h"
#if defined(HAL_TIM_MODULE_ENABLED) && \
	defined(MIDDLEWARE_LED_PANEL_ENABLED)

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "led_panel_font.h"

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

//==============================================================================
// PUBLIC DEFINITIONS
//==============================================================================

//==============================================================================
// PUBLIC TYPEDEFS
//==============================================================================


//==============================================================================
// EXTERN VARIABLES
//==============================================================================

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

typedef struct
{
	uint8_t green;
	uint8_t red;
	uint8_t blue;
}RGB_t;

typedef struct
{
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} LedPanel_t;

typedef struct
{
	uint16_t xi;
	uint16_t yi;
	uint16_t r;
	RGB_t c;
} LedPanelCircDisplay_t;

typedef struct
{
	uint16_t x0;
	uint16_t y0;
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
	RGB_t c;
} LedPanelTriangDisplay_t;

typedef struct
{
	uint16_t x0;
	uint16_t y0;
	uint16_t x1;
	uint16_t y1;
	RGB_t c;
} LedPanelLineDisplay_t;

void LedPanel_clear(void);
void LedPanel_led_drawPixel(uint16_t x, uint16_t y, RGB_t color);
void LedPanel_UpdateScreen(void);
void LedPanel_clearPixel(uint16_t x, uint16_t y);
void LedPanel_drawLine(LedPanelLineDisplay_t lineParameters);
void LedPanel_colorFill(RGB_t _color);
void LedPanel_DrawCircle(LedPanelCircDisplay_t circParameters);
void LedPanel_drawPixel(uint16_t x, uint16_t y, RGB_t _color);
void LedPanel_drawTriangle(LedPanelTriangDisplay_t triParameters);
void LedPanel_setCursor(uint16_t xPos, uint16_t yPos);
void LedPanel_printChar(uint8_t caracter, FontDef_t Font, RGB_t color);

void LedPanel_ex1(void);

#endif /* MIDDLEWARE_LED_PANEL_ENABLED */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* _LED_PANEL_H_ */
