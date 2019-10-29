//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "ws2812.h"

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================


#ifndef configPAINEL_LED_WIDTH
#error "LedPanel_LCD_WIDTH was not declared"
#endif

#ifndef configPAINEL_LED_HEIGHT
#error "LedPanel_LCD_HEIGHT was not declared"
#endif

#define configTIMER_PERIOD			45 			// (TIMER_CLOCK_FREQ / WS2812_FREQ)
#define constLED_DATA_SIZE          (constLED_NUMBER * 24)
#define constRESET_SLOTS_BEGIN      (50)
#define constRESET_SLOTS_END        (50)
#define constWS2812_LAST_SLOT       (1)
#define constLED_BUFFER_SIZE        (constRESET_SLOTS_BEGIN + constLED_DATA_SIZE + constWS2812_LAST_SLOT + constRESET_SLOTS_END)

#define constWS2812_0               (configTIMER_PERIOD / 3)		// WS2812's zero high time is long about one third of the period
#define constWS2812_1               (configTIMER_PERIOD * 2 / 3)	// WS2812's one high time is long about two thirds of the period
#define constWS2812_RESET           (0)

//==============================================================================
// PRIVATE TYPEDEFS
//==============================================================================

//==============================================================================
// PRIVATE VARIABLES
//==============================================================================

static uint32_t timer_hannel;
static TIM_HandleTypeDef *TimHandle = NULL;
static uint8_t LEDbuffer[constLED_BUFFER_SIZE];

//==============================================================================
// SOURCE CODE
//==============================================================================

void ws2812b_pwm_attach( TIM_HandleTypeDef *htim, uint32_t channel)
{
	TimHandle = htim;
	timer_hannel = channel;
	ws2812_fill_bufferBlack();

	if(TimHandle != NULL)
	{
		HAL_TIM_PWM_Start_DMA(TimHandle, timer_hannel, (uint32_t *) LEDbuffer, constLED_BUFFER_SIZE);
	}
}

void ws2812_update(void)
{
	if(TimHandle != NULL)
	{
		HAL_TIM_PWM_Start_DMA(TimHandle, timer_hannel, (uint32_t *) LEDbuffer, constLED_BUFFER_SIZE);
	}
}

void ws2812_set_ledColor(uint32_t LEDnumber, RGB_t color)
{
	uint8_t tempBuffer[24];
	uint32_t i;
	uint32_t LEDindex;
	LEDindex = LEDnumber % constLED_NUMBER;

	for (i = 0; i < 8; i++) // GREEN data
	{
		tempBuffer[i] = ((color.green << i) & 0x80) ? constWS2812_1 : constWS2812_0;
	}

	for (i = 0; i < 8; i++) // RED
	{
		tempBuffer[8 + i] = ((color.red << i) & 0x80) ? constWS2812_1 : constWS2812_0;
	}

	for (i = 0; i < 8; i++) // BLUE
	{
		tempBuffer[16 + i] = ((color.blue << i) & 0x80) ? constWS2812_1 : constWS2812_0;
	}

	for (i = 0; i < 24; i++)
	{
		LEDbuffer[constRESET_SLOTS_BEGIN + LEDindex * 24 + i] = tempBuffer[i];
	}
}

void ws2812_set_wholeColor(RGB_t color)
{
	uint32_t index;

	for (index = 0; index < constLED_NUMBER; index++)
	{
		ws2812_set_ledColor(index, color);
	}
}

void ws2812_fill_bufferBlack(void)
{
	/*Fill LED buffer - ALL OFF*/
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < constRESET_SLOTS_BEGIN; index++)
	{
		LEDbuffer[buffIndex] = constWS2812_RESET;
		buffIndex++;
	}

	for (index = 0; index < constLED_DATA_SIZE; index++)
	{
		LEDbuffer[buffIndex] = constWS2812_0;
		buffIndex++;
	}

	LEDbuffer[buffIndex] = constWS2812_0;
	buffIndex++;

	for (index = 0; index < constRESET_SLOTS_END; index++)
	{
		LEDbuffer[buffIndex] = 0;
		buffIndex++;
	}
}

void ws2812_fill_bufferWhite(void)
{
	/*Fill LED buffer - ALL OFF*/
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < constRESET_SLOTS_BEGIN; index++)
	{
		LEDbuffer[buffIndex] = constWS2812_RESET;
		buffIndex++;
	}
	for (index = 0; index < constLED_DATA_SIZE; index++)
	{
		LEDbuffer[buffIndex] = constWS2812_1;
		buffIndex++;
	}

	LEDbuffer[buffIndex] = constWS2812_0;
	buffIndex++;

	for (index = 0; index < constRESET_SLOTS_END; index++)
	{
		LEDbuffer[buffIndex] = 0;
		buffIndex++;
	}
}

void ws2812_clearBuffer(void)
{
	memset(LEDbuffer, constWS2812_RESET, sizeof(LEDbuffer));
}

