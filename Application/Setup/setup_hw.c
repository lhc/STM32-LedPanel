/**
 * @file    setup_hw.h
 * @author  Jorge Guzman
 * @date    Set 28, 2019
 * @brief   Bibliteoca para configurar e inicializar a aplicacao.
 * @details
 */

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "setup_hw.h"
#include "setup_params.h"

#include "led_panel/led_panel.h"
#include "led_panel/led_panel_font.h"
#include "ws2812b/ws2812b.h"
#include "bitwise/bitwise.h"

#include <string.h>

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

#define TIMEOUT_PRESS_KEY_MS 			30000

#define USB_CDC_BUFSIZE     			64
#define SIZ_DMA_ADC						3

//==============================================================================
// EXTERN VARIABLES
//==============================================================================

extern IWDG_HandleTypeDef hiwdg;
extern SPI_HandleTypeDef hspi1;
extern ADC_HandleTypeDef hadc1;

//==============================================================================
// PRIVATE VARIABLES
//==============================================================================

RGB_t xColor;
LedPanelCircDisplay_t circulo;
LedPanelTriangDisplay_t triangle;

//==============================================================================
// PRIVATE FUNCTIONS
//==============================================================================

/** @brief create queues used in the application */
static void Setup_InitQueues(void);

/** @brief Start libraries of middlware */
static void Setup_InitMiddlware(void);

/** @brief Recover the causa of reset */
static void Setup_InitSanity(void);

/** @brief Read the parameters or configurations used for the application */
static void Setup_InitDatabase(void);

/** @brief Start Apps of application */
static void Setup_InitTasks(void);


//==============================================================================
// SOURCE CODE
//==============================================================================

void Setup_WdgClear(void)
{
	HAL_IWDG_Refresh(&hiwdg);
}

static void Setup_InitQueues(void)
{

}

static void Setup_InitMiddlware(void)
{
	/* Inicia serial de debug*/
	DBG("ARRAY-LEDS");

	//==============================================================================
	// Inicializa lib ws2812b
	//==============================================================================

	ws2812b_spi_attach(&hspi1);
}

static void Setup_InitSanity(void)
{

}

static void Setup_InitDatabase(void)
{
	DataBase_attach_params();
}

void setup_init(void)
{
	//==============================================================================
	// Inicializa Rotinas de Queue, Semp, etc
	//==============================================================================

	Setup_InitQueues();

	//==============================================================================
	// Inicializa Drivers usados pelas Libs
	//==============================================================================

	Setup_InitMiddlware();

	//==============================================================================
	// Visualiza causa do Reset
	//==============================================================================

	Setup_InitSanity();

	//==============================================================================
	// Inicializa os parametros de configuracao do equipamento
	//==============================================================================

	Setup_InitDatabase();

	//==============================================================================
	// Inicializa Tasks da Aplicacao
	//==============================================================================

	Setup_InitTasks();

	/* Envia mensagem de start do sistema */
	DBG("\r\nInit Program...\r\n");
}

static void Setup_InitTasks(void)
{
	LedPanel_setColor(225,255,255);

	for(;;)
	{

#if 0 /* Executa exemplo 1 */

		ws2812b_ex1();

#else /* Executa exemplo 2 */

		/* Desenha as letras LHC */
		LedPanel_clear();

		LedPanel_setCursor(0,0);
		xColor.blue = 0x10;
		xColor.green = 0x0f;
		xColor.red = 0xff;
		LedPanel_printChar('L', Font_7x10, xColor);

		LedPanel_setCursor(9,0);
		xColor.blue = 0x00;
		xColor.green = 0x00;
		xColor.red = 0xff;
		LedPanel_printChar('C', Font_7x10, xColor);

		LedPanel_setCursor(4,9);
		xColor.blue = 0x10;
		xColor.green = 0x00;
		xColor.red = 0x00;

		LedPanel_printChar('H', Font_7x10, xColor);
		LedPanel_UpdateScreen();
		HAL_Delay(3000);

		/* Desenha um triangulo */

		circulo.c = xColor;
		circulo.r = 5;
		circulo.yi = 7;
		circulo.xi = 7;
		LedPanel_clear();
		LedPanel_DrawCircle(circulo);
		HAL_Delay(3000);

		/* Desenha um triangulo */

		triangle.c = xColor;
		triangle.x0 = 1;
		triangle.y0 = 2;
		triangle.x1 = 7;
		triangle.y1 = 14;
		triangle.x2 = 14;
		triangle.y2 = 2;
		LedPanel_clear();
		LedPanel_drawTriangle(triangle);
		HAL_Delay(3000);

#endif

	}
}

