/**
 ******************************************************************************
 * @file    API_bmp_port.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   PdM - Final Work
 * 		 	Header of API_bmp_port.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_BMP
#define API_BMP

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/* Functions ------------------------------------------------------------------ */
_Bool bmpInit(void);
_Bool bmpDeInit(void);
uint8_t bmpGet_ID(void);
float bmpGet_Temp(void);
float bmpGet_Press(void);
float bmpGet_Alt(void);



#endif /* API_BMP */
