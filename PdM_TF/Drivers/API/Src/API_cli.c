/**
 ******************************************************************************
 * @file    API_cli.c
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	This file manage message to cli by uart and using rtc
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include "API_cli.h"


/* Private defines ------------------------------------------------------------*/
static void cliError_Handler(void);

/* Functions ------------------------------------------------------------------*/
/*
 * @func   cliInit
 * @brief
 * @param  None
 * @retval _Bool
 */
_Bool cliInit(void){

	_Bool stts = false;

	return(stts);

}

/*
 * @func   cliDeInit
 * @brief
 * @param  None
 * @retval _Bool
 */
_Bool cliDeInit(void){

	_Bool stts = false;

	return(stts);

}

/*
 * @func   cliClear
 * @brief
 * @param  None
 * @retval _Bool
 */
_Bool cliClear(void){

	_Bool stts = false;

	return(stts);

}

/*
 * @func   cliPrint
 * @brief
 * @param  uint8_t *
 * @retval _Bool
 */
void cliPrint(uint8_t *msg1, uint8_t *msg2, uint8_t *msg3){

	uint8_t message[60];
	uint8_t concat = 0;
	uint8_t indx = 0;
	uint8_t length = 0;

	memset(message, '\0', sizeof(message));

	if (( msg1 != NULL )&&( msg2 != NULL )&&( msg3 != NULL )){

		length =  strlen((const char *) msg1);
		for(indx = 0; indx < length; indx ++){
			message[indx] = msg1[indx];
		}
		concat = indx;
		length =  strlen((const char *) msg2);
		for(indx = concat; indx < (length + concat); indx ++){
			message[indx] = msg2[indx - concat];
		}
		concat = indx;
		length =  strlen((const char *) msg3);
		for(indx = concat; indx < (length + concat); indx ++){
			message[indx] = msg3[indx - concat];
		}
	}
	else{
		if(( msg1 != NULL )&&( msg2 != NULL )){

			length =  strlen((const char *) msg1);
			for(indx = 0; indx < length; indx ++){
				message[indx] = msg1[indx];
			}
			concat = indx;
			length =  strlen((const char *) msg2);
			for(indx = concat; indx < (length + concat); indx ++){
				message[indx] = msg2[indx - concat];
			}
			concat = indx;
		}else{
			if (msg1 != NULL){
			length =  strlen((const char *) msg2);
			for(indx = 0; indx < strlen((const char *) msg1); indx ++){
				message[indx] = msg1[indx];
				}
			}
		}
	}

	cliPORT_Print(message);

	return;

}


/*
 * @func   cliError_Handler
 * @brief
 * @param  uint8_t *
 * @retval _Bool
 */
static void cliError_Handler(void){
	while(1){
	}
}
