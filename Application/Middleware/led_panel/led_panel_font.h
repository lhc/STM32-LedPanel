/**
 * @file    painel_led_font.h
 * @author  Jorge Guzman
 * @date    Fev 7, 2019
 * @brief   Bibliteoca para o uso dos Leds ws2812b
 */


#ifndef _PAINEL_LED_FONT_H_
#define _PAINEL_LED_FONT_H_

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// CHECK TO ENABLE LIBRARY
//==============================================================================

#include "setup_hw.h"
#if defined( MIDDLEWARE_WS2812B_ENABLED )

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include <stdint.h>
#include "string.h"

//==============================================================================
// PUBLUC TYPEDEFS
//==============================================================================

typedef struct
{
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} 	FontDef_t;

typedef struct
{
	uint16_t Length;      /*!< String length in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} Fonts_Size_t;


extern const FontDef_t Font_5x7;
extern const FontDef_t Font_7x10;
extern const FontDef_t Font_11x18;
extern const FontDef_t Font_16x26;

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

/**
 *
 * @param str
 * @param SizeStruct
 * @param Font
 * @return
 */
char* tp_FONTS_GetStringSize( char* str, Fonts_Size_t* SizeStruct, FontDef_t* Font );

#endif /* MIDDLEWARE_WS2812B_ENABLED */

#ifdef __cplusplus
}
#endif


#endif /* _PAINEL_LED_FONT_H_ */
