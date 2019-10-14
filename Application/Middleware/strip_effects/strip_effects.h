#ifndef __STRIPEFFECTS
#define __STRIPEFFECTS

#include "main.h"
#include "led_panel/led_panel.h"

#define HEARTBEAT_STEPS		16

void stripEffect_CircularRing(uint32_t interval, RGB_t color);
void stripEffect_HeartBeat(uint32_t interval, RGB_t color);
void stripEffect_ColorWheel(uint32_t interval);
void stripEffect_AllColors(uint32_t interval);
void stripEffect_PatternMove(uint32_t interval, uint32_t parts,	RGB_t color);
void stripEffect_FullEmpty(uint32_t interval, RGB_t color);
void stripEffect_FromTo(uint32_t interval, uint32_t steps, RGB_t colorA, RGB_t colorB);
void stripEffect_AlternateColors(uint32_t interval, uint32_t steps, RGB_t colorA, RGB_t colorB);
void stripEffect_setColor(RGB_t *color, uint8_t red, uint8_t green, uint8_t blue);

#endif
