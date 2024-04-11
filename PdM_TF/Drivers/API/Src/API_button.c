/**
 ******************************************************************************
 * @file    API/Inc/API_button.h
 * @author  Daniel David Albarracin
 * @brief   Header for API_button.c module
 ******************************************************************************
 */
/* includes  -----------------------------------------------------------------*/
#include <API_button.h>
#include <API_button_port.h>

/* Private variables ---------------------------------------------------------*/

static btnFSM_State btnState[4];


/* Prototype Private Functions -----------------------------------------------*/
static uint8_t PB_GetState(Button_t);
static void btnError_Handler(_Bool);
static void buttonPressed(Button_t);
static void buttonReleased(Button_t);

/* Private Functions */
/*
 * @func   GPIO_Init
 * @brief  Press Button event
 * @param  button_t
 * @retval None
 */
_Bool PB_Init(Button_t button){

	_Bool stts = false;
	stts = PB_PORT_Init(button);
	if (stts == true){
		btnState[button].index = button;
	}
	else{
		btnError_Handler(stts);
	}
	return(stts);
}

/*
 * @func   PB_GetState
 * @brief  Push Button Get State
 * @param  Button_t
 * @retval None
 */
static uint8_t PB_GetState(Button_t button){

	uint8_t pb_stts;

	pb_stts = PB_PORT_GetState(button);
	/*if (pb_stts == PRESSED){
		pb_stts = NOT_PRESSED;
	}else{
		pb_stts = PRESSED;
	}*/

	return(pb_stts);
}

/*
 * @func   btnError_Handler
 * @brief
 * @param  _Bool
 * @retval None
 */
static void btnError_Handler(_Bool stts){
	while(1){

	}
}

/*
 * @func   buttonPressed
 * @brief  Press Button event
 * @param  button_t
 * @retval None
 */
static void buttonPressed(Button_t button) {
	btnState[button].btnPress.PB_PRESSED = PRESSED;
	return;
}

/*
 * @func   buttonReleased
 * @brief  Released Button event
 * @param  None
 * @retval None
 */
static void buttonReleased(Button_t button) {
	btnState[button].btnPress.PB_RELEASE = RELEASE;
	return;
}

/*
 * @func   debounceFSM_init
 * @brief  Initialize FSM
 * @param  Button_st *, uint8_t
 * @retval None
 */
void debounceFSM_init(void) {

	uint8_t btn_indx;
	uint8_t btn_count = sizeof(btnState)/sizeof(btnFSM_State);

	for (btn_indx = 0; btn_indx < btn_count; btn_indx++) {
			btnState[btn_indx].state = PB_STATE_UP;
		}
	return;
}
/*
 * @func   debounceFSM_update
 * @brief  Initialize FSM
 * @param  Button_st *, uint8_t
 * @retval None
 */
void debounceFSM_update(void) {

	uint8_t indx_btn;
	uint8_t count = sizeof(btnState)/sizeof(btnFSM_State);

	for (indx_btn = 0; indx_btn < count; indx_btn++) {

		switch (btnState[indx_btn].state) {
		case PB_STATE_UP:
			if (!PB_GetState(btnState[indx_btn].index)) {
				delayInit(&btnState[indx_btn].delay, UPTOFALL);
				btnState[indx_btn].state = PB_STATE_FALL;
			}
			break;
		case PB_STATE_FALL:
			if (delayRead(&btnState[indx_btn].delay)) {
				if (!PB_GetState(btnState[indx_btn].index)) {
					buttonPressed(btnState[indx_btn].index);
					btnState[indx_btn].state = PB_STATE_DOWN;
				} else {
					btnState[indx_btn].state = PB_STATE_UP;
				}
			}
			break;
		case PB_STATE_DOWN:
			if (PB_GetState(btnState[indx_btn].index)) {
				delayInit(&btnState[indx_btn].delay, RISETODOWN);
				btnState[indx_btn].state = PB_STATE_RISE;
			}
			break;
		case PB_STATE_RISE:
			if (delayRead(&btnState[indx_btn].delay)) {
				if (PB_GetState(btnState[indx_btn].index)) {
					buttonReleased(btnState[indx_btn].index);
					btnState[indx_btn].state = PB_STATE_UP;
				} else {
					btnState[indx_btn].state = PB_STATE_DOWN;
				}
			}
			break;
		default:
			debounceFSM_init();
			break;
		}
	}
	return;
}


/*
 * @func   readKey
 * @brief  signal API modules
 * @param  None
 * @retval bool_t
 */
Button_t PB_Pressed(uint8_t state) {

	Button_t btn_stts = BUTTON_NONE;

	uint8_t btn_indx;
	uint8_t count = sizeof(btnState)/sizeof(btnFSM_State);

	uint8_t btnP_count = 0;
	uint8_t btnR_count = 0;
	uint8_t btnP_name;
	uint8_t btnR_name;

	if (state == PB_STATE_FALL) {
		for (btn_indx = 0; btn_indx < count; btn_indx ++){
			if (btnState[btn_indx].btnPress.PB_PRESSED == PRESSED) {
				btnP_count ++;
				btnState[btn_indx].btnPress.PB_PRESSED = NOT_PRESSED;
				if (btnP_count){
					btnP_name = btnState[btn_indx].index;
				}
			}
		}

	}
	if (state == PB_STATE_RISE) {
		for (btn_indx = 0; btn_indx < count; btn_indx ++){
			if (btnState[btn_indx].btnPress.PB_RELEASE == RELEASE) {
				btnR_count ++;
				btnState[btn_indx].btnPress.PB_RELEASE = NOT_RELEASE;
				if (btnR_count){
					btnR_name = btnState[btn_indx].index;
				}
			}
		}
	}

	if (btnP_count == 1) {
		btn_stts = btnP_name;
	}
	if (btnR_count == 1) {
		btn_stts = btnR_name;
	}

	return (btn_stts);
}
