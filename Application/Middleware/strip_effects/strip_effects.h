#ifndef __STRIPEFFECTS
#define __STRIPEFFECTS

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "led_panel/led_panel.h"
#include <stdint.h>

//==============================================================================
// PUBLIC DEFINITIONS
//==============================================================================

//==============================================================================
// PUBLIC TYPEDEFS
//==============================================================================

//==============================================================================
// PUBLIC VARIABLES
//==============================================================================

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

void stripEffect_CircularRing(uint32_t interval, RGB_t color);
void stripEffect_HeartBeat(uint32_t interval, RGB_t color);
void stripEffect_ColorWheel(uint32_t interval);
void stripEffect_AllColors(uint32_t interval);
void stripEffect_PatternMove(uint32_t interval, uint32_t parts,	RGB_t color);
void stripEffect_FullEmpty(uint32_t interval, RGB_t color);
void stripEffect_FromTo(uint32_t interval, uint32_t steps, RGB_t colorA, RGB_t colorB);
void stripEffect_AlternateColors(uint32_t interval, uint32_t steps, RGB_t colorA, RGB_t colorB);
void stripEffect_setColor(RGB_t *color, uint8_t red, uint8_t green, uint8_t blue);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
