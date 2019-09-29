/**
 * @file    setup_params.c
 * @author  Jorge Guzman
 * @date    Set 28, 2019
 * @brief   Aplicacao que contem as variaveis de configuracao do projeto.
 */

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "setup_params.h"

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

//==============================================================================
// PRIVATE TYPEDEFS
//==============================================================================

//==============================================================================
// PRIVATE VARIABLES
//==============================================================================

DataBase_t xSystemParams;

//==============================================================================
// PRIVATE FUNCTIONS
//==============================================================================

static HAL_StatusTypeDef DataBase_write(DataBase_t *data);
static HAL_StatusTypeDef DataBase_read(DataBase_t *data);

//==============================================================================
// PRIVATE FUNCTIONS
//==============================================================================

static HAL_StatusTypeDef DataBase_write(DataBase_t *data)
{
	HAL_StatusTypeDef resp = HAL_ERROR;

	data->checkCRC = 0x00000000;

	return resp;
}

static HAL_StatusTypeDef DataBase_read(DataBase_t *data)
{
	uint32_t resp = HAL_ERROR;
	//	uint32_t aux_checkCRC;

	return resp;
}

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

void DataBase_load_default_params(void)
{
	xSystemParams.checkCRC = 0x00;
}

void DataBase_attach_params(void)
{

}

HAL_StatusTypeDef DataBase_load_params(void)
{
	HAL_StatusTypeDef err = HAL_OK;

	err = DataBase_read(&xSystemParams);

	if(err == HAL_ERROR)
	{
		DataBase_load_default_params();
		DataBase_write(&xSystemParams);
	}

	return err;
}

HAL_StatusTypeDef DataBase_save(void)
{
	return HAL_OK;
}
