

/* Private functions ---------------------------------------------------------*/
#include <API_Delay.h>
/**
  * @brief  delayInit function initialize a delay
  * @param  delay_t struct, tick_t
  * @retval None
  */
void delayInit( delay_t *delay, tick_t duration ){
	if (delay != NULL){
		if ((0<=duration)&&(duration<=DELAY_MAX)){
			delay->duration = duration;
			delay->running = false;
		}
	}
}

/**
  * @brief  delayRead function read and check a delay
  * @param  delay_t struct
  * @retval bool_t
  */
bool_t delayRead( delay_t *delay ){

	tick_t get_tick = 0;
	bool_t delay_flg = false;
	if (delay != NULL){
		if (delay->running){
			get_tick = HAL_GetTick();
			if ((get_tick - delay->startTime) >= delay->duration){
				delay->running = false;
				delay_flg = true;
			}
		}
		else{
			delay->startTime = HAL_GetTick();
			delay->running = true;
		}
	}
	return delay_flg;
}

/**
  * @brief  delayWrite function change duration of a delay
  * @param  delay_t struct, tick_t
  * @retval None
  */
void delayWrite( delay_t *delay, tick_t duration ){
	if(delay != NULL){
		if ((!delay->running)&&(0<=duration)&&(duration<=DELAY_MAX)){
			delay->duration = duration;
		}
	}
}
