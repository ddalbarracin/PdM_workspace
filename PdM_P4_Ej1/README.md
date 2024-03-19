# CESE - FIUBA - 2024 - Cohorte 22
![](/PdM_P3_Ej3/Docs/Images/CESE.png)
## Materia
    Progamacion de Microcontroladores
## Docente
    Mag. Ing. Patricio Bos
## Autor 
    Ing. Daniel David Albarracin
## Date
	21/03/2024

# STM32CubeIDE Workshop
![](/PdM_P4_Ej1/Docs/Images/ST14179_STM32CubeIDE.png)

# Práctica 4
## Objetivo:
- Implementar un MEF para trabajar con anti-rebotes por software.  
## Punto 1
- Implementar una MEF anti-rebote que permita leer el estado del pulsador de la 
placa NUCLEO-F4 y generar acciones o eventos ante un flanco descendente o ascendente, 
de acuerdo al siguiente diagrama:
![](/PdM_P4_Ej1/Docs/Images/PdM_P4_EJ1_FSM.png)
## Punto 2
- Implementar un módulo de software en un archivo fuente API_debounce.c con su 
correspondiente archivo de cabecera API_debounce.h
- Implementar un programa que cambie la frecuencia de parpadeo del LED entre 100 ms 
y 500 ms cada vez que se presione la tecla.  El programa debe usar las funciones 
anti-rebote del módulo API_debounce y los retardos no bloqueantes del módulo 
API_delay y la función readKey.
 
