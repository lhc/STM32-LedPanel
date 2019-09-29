/**
 * @file    setup_params.h
 * @author  Jorge Guzman
 * @date    Set 28, 2019
 * @brief   Aplicacao que contem as variaveis de configuracao do projeto.
 */


#ifndef _SETUP_PARAMS_H_
#define _SETUP_PARAMS_H_

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "setup_hw.h"

//==============================================================================
// PUBLIC DEFINES
//==============================================================================

//==============================================================================
// PUBLIC TYPEDEFS
//==============================================================================

typedef struct
{
	uint32_t numSerie;
	uint16_t version;
	uint8_t device[20];
	uint8_t company[20];
}FabParams_t;

typedef struct
{
	FabParams_t fabParams;
	uint32_t checkCRC;
}DataBase_t;

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

void DataBase_attach_params(void);

/**
 *
 * @return
 */
HAL_StatusTypeDef database_load_params(void);

#endif /* _SETUP_PARAMS_H_ */
