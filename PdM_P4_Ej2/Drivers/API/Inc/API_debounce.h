/**
 ******************************************************************************
 * @file    API_debounce.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Practical Work 4 - Exercise 2
 * 		 	Header file to API_debounce.c
 *
 ******************************************************************************
 **/
/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include "API_Delay.h"
/* Private define ------------------------------------------------------------*/
#define UPTOFALL 40
#define RISETODOWN 40

/* Private Functions ----------------------------------------------------------*/
bool_t readKey(void);
void debounceFSM_init(void);
void debounceFSM_update(void);
