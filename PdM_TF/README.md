# CESE - FIUBA - 2024 - Cohorte 22
![](/PdM_TPF/Docs/Images/CESE.png)
## Materias
    Progamacion de Microcontroladores
    Protocolos de Comunicacion Sistemas Embebidos
## Docentes
    Mag. Ing. Patricio Bos
    Ing. Israel Pavelek
    
## Autor 
    Ing. Daniel David Albarracin
## Date
	18/04/2024

# Entorno de Desarrolo
	STM32CubeIDE

# Trabajo Final de Materia
## Objetivo
- Desarrolo de un sistema de medicion de Alititud, Presion y Temperatura

## Diagrama en Bloques del Sistemas
![](/PdM_TPF/Docs/Images/Diagrama_Bloques.png)

## Maquina de Estados Finitos
![](/PdM_TPF/Docs/Images/FSM_States.png)
![](/PdM_TPF/Docs/Images/FSM.png)

## Stack de Software
![](/PdM_TPF/Docs/Images/Software_Stack.png)

## Tabla de Interconexiones
| ---------------------	| -------------	| ----------- |	--------- | --------- | ---------- |
| Device                | PROTOCOL      | PHERIPHERAL | CONNECTOR | PIN       | FUNCTION   |
| :---------------------| :-----------: | :---------: | :-------: | :-------: | :--------: |
| ---------------------	| -------------	| ----------- |	--------- | --------- | ---------- |
| BMP280				| SPI		    | SPI1		  |	7		  | PB3		  | SCK		   |
|						|				|			  |			  | PB5		  |	MOSI	   |
|						|				|			  |			  | PB4		  |	MISO	   |
|						|				| GPIOA		  |			  | PA4		  | CS		   |
| ---------------------	| -------------	| ----------- |	--------- | --------- | ---------- |
| LCD1602				| I2C			| I2C1		  |	7		  | PB8		  |	SCL		   |
|						|				|			  |			  | PB9		  |	SDA		   |	
| ---------------------	| -------------	| ----------- |	--------- | --------- | ---------- |
| CLI					| USART			| USART3	  | ST-Link	  | PB10	  |	Tx		   |
|						|				|			  |			  | PB11	  |	Rx		   |
| ---------------------	| -------------	| ----------- |	--------- | --------- | ---------- |
| Buttons				| -				| GPIOF		  |	7		  | PF12	  | UP 		   |
|						|				|			  |	10		  | PF13	  |	DOWN	   |
|						|				| GPIOG		  |	9		  | PG0		  |	ENTER	   |
|						|				|			  |	9		  | PG1		  |	BACK	   |  
| ---------------------	| -------------	| ----------- |	--------- | --------- | ---------- |
## Especificaciones para Conexion de Salida Estandar

| ------------------- | ------------- | ---------------------------- |
| DEVICE              | Parameter     | PHERIPHERAL 				 | 
| :-------------------| :-----------: | :--------------------------: | 
| ------------------- | ------------- | ---------------------------- |
| UART				  | BaudRate	  | 9600						 |
|					  | Mode		  | TxRx	    				 |
|					  | WordLength    | 8		    				 |
|					  | StopBits      | 1           				 |
|                     | Parity        | None        				 |
| ------------------- | ------------- | ---------------------------- |
| RTC                 | Hour          | RTC_SET_TIME_HOUR        	 |
|                     | Minute        | RTC_SET_TIME_MINUTE        	 |
|					  | Second		  | RTC_SET_TIME_SECOND			 |
|					  | Date		  | RTC_SET_DATE_DATE			 |
|					  | Month		  | RTC_SET_DATE_MONTH			 |
|					  | Year		  | RTC_SET_DATE_YEAR			 |
| ------------------- | ------------- | ---------------------------- |

