/**
 ******************************************************************************
 * @file    API_bmp.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header of API_bmp.c
 *
 ******************************************************************************
 **/
/* Includes guard -----------------------------------------------------------*/
#ifndef API_BMP
#define API_BMP

/* Includes -----------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Functions ----------------------------------------------------------------*/
_Bool bmpInit(void);
void bmpDeInit(void);
float bmpGet_Temp(void);
float bmpGet_Press(void);
float bmpGet_Alt(void);

#endif /* API_BMP */
