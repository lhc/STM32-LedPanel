#ifndef __ws2812
#define __ws2812

#include <stdio.h>
#include <string.h>
#include "setup_hw.h"
#include "led_panel/led_panel.h"

#define TIMER_PERIOD				45 //							(TIMER_CLOCK_FREQ / WS2812_FREQ)

#define LED_NUMBER                  (17*16)	//16				// how many LEDs the MCU should control?
#define LED_DATA_SIZE               (LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN           (50)
#define RESET_SLOTS_END             (50)
#define WS2812_LAST_SLOT            (1)
#define LED_BUFFER_SIZE             (RESET_SLOTS_BEGIN + LED_DATA_SIZE + WS2812_LAST_SLOT + RESET_SLOTS_END)
#define WS2812_0                    (TIMER_PERIOD / 3)				// WS2812's zero high time is long about one third of the period
#define WS2812_1                    (TIMER_PERIOD * 2 / 3)		// WS2812's one high time is long about two thirds of the period
#define WS2812_RESET                (0)

void ws2812b_pwm_attach( TIM_HandleTypeDef *htim, uint32_t channel);
void ws2812_update(void);
void setLEDcolor(uint32_t LEDnumber, RGB_t color);
void setWHOLEcolor(RGB_t color);
void fillBufferBlack(void);
void fillBufferWhite(void);
void TIMx_DMA_IRQHandler(void);
void clearBuffer(void);

#endif
