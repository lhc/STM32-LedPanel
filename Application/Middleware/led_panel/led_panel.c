/**
 * @file    led_panel.c
 * @author  Jorge Guzman
 * @date    Fev 7, 2019
 * @brief   Bibliteoca para o uso do painel de leds
 *
 */

//==============================================================================
// CHECK TO ENABLE LIBRARY
//==============================================================================
#include "led_panel.h"
#if defined(HAL_TIM_MODULE_ENABLED)    & \
	defined(MIDDLEWARE_LED_PANEL_ENABLED)

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "ws2812b/ws2812.h"
#include "bitwise/bitwise.h"
#include <stddef.h>
#include <string.h>

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

//==============================================================================
// PRIVATE TYPEDEFS
//==============================================================================

//==============================================================================
// PRIVATE VARIABLES
//==============================================================================

static LedPanel_t painelCtrl;

//==============================================================================
// EXTERN VARIABLES
//==============================================================================

//==============================================================================
// PRIVATE FUNCTIONS
//==============================================================================

static int16_t LedPanel_abs_(int16_t x);

//==============================================================================
// PRIVATE SOURCE CODE
//==============================================================================

void LedPanel_colorFill(RGB_t _color)
{
	ws2812_set_wholeColor(_color);
}

void LedPanel_DrawCircle(LedPanelCircDisplay_t circParameters)
{
	int16_t x0 = circParameters.xi, y0 = circParameters.yi, radius = circParameters.r;
	RGB_t color = circParameters.c;

	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t y = radius;

	LedPanel_drawPixel(x0, y0 + radius, color);
	LedPanel_drawPixel(x0, y0 - radius, color);
	LedPanel_drawPixel(x0 + radius, y0, color);
	LedPanel_drawPixel(x0 - radius, y0, color);

	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x;

		LedPanel_drawPixel(x0 + x, y0 + y, color);
		LedPanel_drawPixel(x0 - x, y0 + y, color);
		LedPanel_drawPixel(x0 + x, y0 - y, color);
		LedPanel_drawPixel(x0 - x, y0 - y, color);

		LedPanel_drawPixel(x0 + y, y0 + x, color);
		LedPanel_drawPixel(x0 - y, y0 + x, color);
		LedPanel_drawPixel(x0 + y, y0 - x, color);
		LedPanel_drawPixel(x0 - y, y0 - x, color);
	}

	LedPanel_UpdateScreen();
}

void LedPanel_drawTriangle(LedPanelTriangDisplay_t triParameters)
{
	LedPanelLineDisplay_t lineParameters[3];

	lineParameters[0].c = triParameters.c;
	lineParameters[1].c = triParameters.c;
	lineParameters[2].c = triParameters.c;

	lineParameters[0].x0 = triParameters.x0;
	lineParameters[0].x1 = triParameters.x1;
	lineParameters[0].y0 = triParameters.y0;
	lineParameters[0].y1 = triParameters.y1;
	LedPanel_drawLine(lineParameters[0]);

	lineParameters[1].x0 = triParameters.x1;
	lineParameters[1].x1 = triParameters.x2;
	lineParameters[1].y0 = triParameters.y1;
	lineParameters[1].y1 = triParameters.y2;
	LedPanel_drawLine(lineParameters[1]);

	lineParameters[2].x0 = triParameters.x2;
	lineParameters[2].x1 = triParameters.x0;
	lineParameters[2].y0 = triParameters.y2;
	lineParameters[2].y1 = triParameters.y0;
	LedPanel_drawLine(lineParameters[2]);
}

static int16_t LedPanel_abs_(int16_t x)
{
	if (x > 0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}
void LedPanel_drawLine(LedPanelLineDisplay_t lineParameters)
{
	int16_t startX = lineParameters.x0, startY = lineParameters.y0, endX = lineParameters.x1, endY = lineParameters.y1;
	RGB_t color = lineParameters.c;

	int16_t x0 = startX;
	int16_t x1 = endX;
	int16_t y0 = startY;
	int16_t y1 = endY;

	int16_t dx = LedPanel_abs_(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int16_t dy = LedPanel_abs_(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int16_t err1 = (dx > dy ? dx : -dy) / 2;
	int16_t e2;

	for (;;)
	{
		LedPanel_drawPixel(x0, y0, color);
		if (x0 == x1 && y0 == y1)
		{
			break;
		}

		e2 = err1;

		if (e2 > -dx)
		{
			err1 -= dy;
			x0 += sx;
		}

		if (e2 < dy)
		{
			err1 += dx;
			y0 += sy;
		}
	}

	LedPanel_UpdateScreen();
}
//==============================================================================
// PUBLIC SOURCE CODE
//==============================================================================

void LedPanel_drawPixel(uint16_t x, uint16_t y, RGB_t _color)
{
	uint16_t addrX = 0, addrY = 0, addr = 0;

	if (x % 2 == 0)
	{
		addrX = (x * configPAINEL_LED_WIDTH);
		addrY = (configPAINEL_LED_HEIGHT - y);
		addr = addrX + addrY;
	}
	else
	{
		addrX = (x * configPAINEL_LED_WIDTH);
		addrY = y ;
		addr = addrX + addrY;
	}

	ws2812_set_ledColor(addr, _color);
}

void LedPanel_UpdateScreen(void)
{
	ws2812_update();
}

void LedPanel_clearPixel(uint16_t x, uint16_t y)
{
	RGB_t _color = {0};

	LedPanel_drawPixel(x, y, _color);
}

void LedPanel_clear(void)
{
	RGB_t _color = {0};
	ws2812_set_wholeColor(_color);
}

void LedPanel_setCursor(uint16_t xPos, uint16_t yPos)
{
	painelCtrl.CurrentX = xPos;
	painelCtrl.CurrentY = yPos;
}

void LedPanel_printChar(uint8_t caracter, FontDef_t Font, RGB_t color)
{
	uint32_t i, b, j;

	if (caracter == '\n')
	{
		LedPanel_setCursor(painelCtrl.CurrentX, painelCtrl.CurrentY + Font.FontHeight + 3);
	}

	if (caracter == '\r')
	{
		LedPanel_setCursor(0, painelCtrl.CurrentY);
	}

	if (caracter == 176 /* ° */)
	{
		caracter = 127;
	}
	if (caracter < 0x20 || caracter > 0x7F)
	{
		return;
	}

	if (painelCtrl.CurrentX + Font.FontWidth >= configPAINEL_LED_WIDTH)
	{
		LedPanel_setCursor(0, painelCtrl.CurrentY + Font.FontHeight);
	}

	for (i = 0; i < Font.FontHeight; i++)
	{
		b = Font.data[(caracter - 32) * Font.FontHeight + i];

		for (j = 0; j < Font.FontWidth; j++)
		{
			if ((b << j) & 0x8000)
			{
				LedPanel_drawPixel(painelCtrl.CurrentX + j, (painelCtrl.CurrentY + i), (RGB_t) color);
			}
		}
	}

	painelCtrl.CurrentX += Font.FontWidth;
}

#endif /* MIDDLEWARE_LED_PANEL_ENABLED */
