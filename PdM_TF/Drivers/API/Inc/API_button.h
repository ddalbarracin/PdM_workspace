/**
 ******************************************************************************
 * @file    API/Inc/API_button.h
 * @author  Daniel David Albarracin
 * @brief   Header for API_button.c module
 ******************************************************************************
 */
/* include guard -------------------------------------------------------------*/
#ifndef API_BUTTON
#define API_BUTTON

/* include -------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include "API_Delay.h"

/* Typedef -------------------------------------------------------------------*/
typedef enum{
	BUTTON_UP = 0,
	BUTTON_DOWN = 1,
	BUTTON_ENTER = 2,
	BUTTON_BACK = 3,
	BUTTON_NONE = 4,
}Button_t;

typedef enum{
	BUTTON_PRESSED,
	BUTTON_RELEASE
}ButtonSate_t;

typedef enum {
	PB_STATE_UP, PB_STATE_FALL, PB_STATE_DOWN, PB_STATE_RISE,
} debounceState_t;

typedef struct {
	uint8_t PB_PRESSED;
	uint8_t PB_RELEASE;
}btnFSM_Press;

typedef struct{
	uint8_t index;
	debounceState_t state;
	delay_t delay;
	btnFSM_Press btnPress;
}btnFSM_State;

/* Private define ------------------------------------------------------------*/
#define UPTOFALL 		40
#define RISETODOWN 		40
#define PRESSED 		1
#define NOT_PRESSED 	0
#define RELEASE 		1
#define NOT_RELEASE		0

/* Prototype Functions ------------------------------------------------------------ */
_Bool PB_Init(Button_t);
Button_t PB_Pressed(uint8_t);
void debounceFSM_init(void);
void debounceFSM_update(void);

#endif /* API_BUTTON */
