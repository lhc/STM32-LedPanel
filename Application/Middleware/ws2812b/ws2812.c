#include "ws2812.h"

/* Variables -----------------------------------------------*/
uint8_t LEDbuffer[LED_BUFFER_SIZE];

TIM_HandleTypeDef *TimHandle = NULL;
uint32_t timer_hannel;

void ws2812b_pwm_attach( TIM_HandleTypeDef *htim, uint32_t channel)
{
	TimHandle = htim;
	timer_hannel = channel;
	fillBufferBlack();

	if(TimHandle != NULL)
	{
		HAL_TIM_PWM_Start_DMA(TimHandle, timer_hannel, (uint32_t *) LEDbuffer, LED_BUFFER_SIZE);
	}
}

void ws2812_update(void)
{
	if(TimHandle != NULL)
	{
		HAL_TIM_PWM_Start_DMA(TimHandle, timer_hannel, (uint32_t *) LEDbuffer, LED_BUFFER_SIZE);
	}
}

void setLEDcolor(uint32_t LEDnumber, RGB_t color)
{
	uint8_t tempBuffer[24];
	uint32_t i;
	uint32_t LEDindex;
	LEDindex = LEDnumber % LED_NUMBER;

	for (i = 0; i < 8; i++) // GREEN data
	{
		tempBuffer[i] = ((color.green << i) & 0x80) ? WS2812_1 : WS2812_0;
	}
	for (i = 0; i < 8; i++) // RED
	{
		tempBuffer[8 + i] = ((color.red << i) & 0x80) ? WS2812_1 : WS2812_0;
	}
	for (i = 0; i < 8; i++) // BLUE
	{
		tempBuffer[16 + i] = ((color.blue << i) & 0x80) ? WS2812_1 : WS2812_0;
	}

	for (i = 0; i < 24; i++)
	{
		LEDbuffer[RESET_SLOTS_BEGIN + LEDindex * 24 + i] = tempBuffer[i];
	}
}

void setWHOLEcolor(RGB_t color)
{
	uint32_t index;

	for (index = 0; index < LED_NUMBER; index++)
	{
		setLEDcolor(index, color);
	}
}

void fillBufferBlack(void)
{
	/*Fill LED buffer - ALL OFF*/
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < RESET_SLOTS_BEGIN; index++)
	{
		LEDbuffer[buffIndex] = WS2812_RESET;
		buffIndex++;
	}

	for (index = 0; index < LED_DATA_SIZE; index++)
	{
		LEDbuffer[buffIndex] = WS2812_0;
		buffIndex++;
	}
	LEDbuffer[buffIndex] = WS2812_0;
	buffIndex++;

	for (index = 0; index < RESET_SLOTS_END; index++)
	{
		LEDbuffer[buffIndex] = 0;
		buffIndex++;
	}
}

void fillBufferWhite(void)
{
	/*Fill LED buffer - ALL OFF*/
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < RESET_SLOTS_BEGIN; index++)
	{
		LEDbuffer[buffIndex] = WS2812_RESET;
		buffIndex++;
	}
	for (index = 0; index < LED_DATA_SIZE; index++)
	{
		LEDbuffer[buffIndex] = WS2812_1;
		buffIndex++;
	}

	LEDbuffer[buffIndex] = WS2812_0;
	buffIndex++;

	for (index = 0; index < RESET_SLOTS_END; index++)
	{
		LEDbuffer[buffIndex] = 0;
		buffIndex++;
	}
}

void clearBuffer(void)
{
	memset(LEDbuffer, WS2812_RESET, sizeof(LEDbuffer));
}
//=============================================

