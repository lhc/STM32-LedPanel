/**
 * @file    setup_debug.h
 * @author  Jorge Guzman,
 * @date    Set 28, 2019
 * @brief   Biblioteca que contem as rotinas de configuracao de debug
 * @details
 */

#ifndef _SETUP_DEBUG_H_
#define	_SETUP_DEBUG_H_

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "setup_hw.h"
#include <stdint.h>

//==============================================================================
// DEFINITIONS TO DEBUG SECTION
//==============================================================================

#if ENABLE_DEBUG > 0

/* Enable full assert of CubeMX */
#if !defined(USE_FULL_ASSERT)
#define USE_FULL_ASSERT
#endif

#define DBG_BKPT()		   					asm("BKPT #0")
#define DBG_PRINTF(fmt, ...) 				Debug_Printf(fmt, ##__VA_ARGS__)
#define DBG_PRINTFLN(fmt, ...) 				Debug_Printf(fmt"\r\n", ##__VA_ARGS__)
#define DBG_SEND(buff, size)				Debug_SendBuffer(buff, size)
#define DBG_ASSERT_PARAM(x)	 				SYSLOG_ASSERT_PARAM(x)

#define DBG(fmt, ...) 						Debug_Printf(fmt"\r\n", ##__VA_ARGS__)
#define INFO(fmt, ...) 						Syslog_Msg(LOG_INFO,  fmt, ##__VA_ARGS__)
#define ERR(fmt, ...) 						Syslog_Msg(LOG_ERROR, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)						Syslog_Msg(LOG_WARN,  fmt, ##__VA_ARGS__)

#define configMICROSHELL_RX_BUFFER_SIZE		300
#define MICROSHELL_PRINTF(fmt, ...)			DBG_PRINTFLN(fmt, ##__VA_ARGS__)

#else

#define DBG_BKPT()		   				__NOP()
#define DBG_PRINTFLN(fmt, ...)	   		__NOP()
#define DBG_LOG_MSG(err, fmt, ...) 		__NOP()
#define DBG_SEND(buff, size)			__NOP()
#define DBG_ASSERT(x)	 				__NOP()

#define DBG(fmt, ...) 					__NOP()
#define INFO(fmt, ...) 					__NOP()
#define ERR(fmt, ...) 					__NOP()

#endif /* ENABLE_DEBUG */

#endif /* _SETUP_DEBUG_H_ */
