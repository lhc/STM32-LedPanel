/**
 * @file    ws2812b.h
 * @author  Jorge Guzman
 * @date    Fev 7, 2019
 * @brief   Bibliteoca para o uso dos Leds ws2812b
 */

#ifndef _WS2812B_H_
#define _WS2812B_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// CHECK TO ENABLE LIBRARY
//==============================================================================

#include "setup_hw.h"
#if defined(HAL_SPI_MODULE_ENABLED) & \
	defined(MIDDLEWARE_WS2812B_ENABLED)

//==============================================================================
// INCLUDE FILES
//==============================================================================

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

//==============================================================================
// PUBLIC DEFINITIONS
//==============================================================================

#define WS2812_BIT_ON			0B110 /* value 6 */
#define WS2812_BIT_OFF			0B100 /* value 4 */

//==============================================================================
// PUBLIC TYPEDEFS
//==============================================================================

//==============================================================================
// EXTERN VARIABLES
//==============================================================================

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

HAL_StatusTypeDef ws2812b_spi_attach(SPI_HandleTypeDef *spi);
HAL_StatusTypeDef ws2812b_write(uint8_t *data, uint16_t size);

#endif /* MIDDLEWARE_WS2812B_ENABLED */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* _WS2812B_H_ */
