/**
 ******************************************************************************
 * @file    API/Inc/API_debounce.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Practical Work 4 - Exercise 2
 * 		 	Header file to API_debounce.c
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#ifndef API_DEBOUNCE
#define API_DEBOUNCE

#include <stdio.h>
#include "API_Delay.h"
/* Public define ------------------------------------------------------------*/
#define UPTOFALL 40
#define RISETODOWN 40

/* Public typedef ------------------------------------------------------------*/
/* Button State enum */
typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RISING,
} debounceState_t;


/* Public Functions ----------------------------------------------------------*/
bool_t readKey(uint8_t);
void debounceFSM_init(void);
void debounceFSM_update(void);

#endif
