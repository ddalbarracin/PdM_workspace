/**
 ******************************************************************************
 * @file    API_cli.h
 * @author  Daniel David Albarracin
 * @github  ddalbarracin
 * @brief   Header of API_cli.c
 *
 ******************************************************************************
 **/
/* Includes guard ------------------------------------------------------------- */
#ifndef API_CLI
#define API_CLI

/* Includes ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/* Prototype Functions -------------------------------------------------------- */
_Bool cliInit(void);
_Bool cliDeInit(void);
_Bool cliClear(void);
void cliPrint(uint8_t*, uint8_t*, uint8_t*);


#endif /* API_CLI */
