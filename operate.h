/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef OPERATE_H_   /* Include guard */
#define OPERATE_H_

#include <project.h>


uint8 FM_RADIO_STATION;// variable used to store intercepted FM radio station number

   
    
    
/*******************************************************************************
* Function Name: BeoM_PSU_state()
********************************************************************************
* Summary:
*  Function monitors SYSTEM and BlueToot state global variables and 
*  enables/disab;es power supply domains accordingly. 
*  SYSTEM_STATE = 0 - power down
*  SYSTEM_STATE = 1 - Player
*  SYSTEM_STATE = 2 - iRadio
*  SYSTEM_STATE = 3 - DAB Radio
*  SYSTEM_STATE = 4 - Aux IN
*  SYSTEM_STATE = 5 - Clock
*  SYSTEM_STATE = 6 - RDS/FM display
*  SYSTEM_STATE = 7 - BlueTooth Rx
*  SYSTEM_STATE = 8 - BlueTooth Tx
*  BT_Tx_STATE = 0  - BT Tx OFF
*  BT_Tx_STATE = 1  - BT Tx ON
*   
* Parameters:
*  Function operates on global variables:
*  SYSTEM_STATE and BT_Tx_STATE
*
* Return:
*  Funciton returns current SYSTEM_STATE nubmer
*
*******************************************************************************/  
uint8 BeoM_PSU_state();  




/*******************************************************************************
* Function Name: display_update()
********************************************************************************
* Summary:
*  Function monitors SYSTEM STATE variable and listen to incoming UART messages
*  from RPi. When they arrive, push them to the display module over SPI. 
*  SYSTEM_STATE = 0 - power down    -   NO COMMANDS from RPi
*  SYSTEM_STATE = 1 - Player        -   COMMANDS
*  SYSTEM_STATE = 2 - iRadio        -   COMMANDS
*  SYSTEM_STATE = 3 - DAB Radio     -   COMMANDS
*  SYSTEM_STATE = 4 - Aux IN        -   NO COMMANDS from RPi
*  SYSTEM_STATE = 5 - Clock         -   NO COMMANDS from RPi
*  SYSTEM_STATE = 6 - RDS/FM display-   COMMANDS
*  SYSTEM_STATE = 7 - BlueTooth Rx  -   NO COMMANDS from RPi
*  SYSTEM_STATE = 8 - BlueTooth Tx  -   NO COMMANDS from RPi
*
*   
* Parameters:
*  Function operates on global variable: 
*  SYSTEM_STATE and DISPLAY_STATE
*
* Return:
*  Funciton returns current ????
*
*******************************************************************************/  
uint8 display_update(void);


/*******************************************************************************
* Function Name: datalink_check()
********************************************************************************
* Summary:
*  Functon responsible for interpetting remote control commands and moving system
*  state based on datalink input
*   
* Parameters:
*  command - number reported back by datalink_decoder function. List as follow:
*   0 - no new command
*   1 - incorrect start and/or stop value
*   2 - if t = 0 and t+1 = t1 -> error or t = 1 and t+1 = t3 -> error
*  10 - only Aux button pressed - power up to last state
*  11 - Aux button pressed plus one digit number 1 or nubmer one to any of five aux devices
*  12 - Aux button pressed plus one digit number 2 or nubmer two  to any of five aux devices
*  13 - Aux button pressed plus one digit number 3 or nubmer three to any of five aux devices
*  14 - Aux button pressed plus one digit number 4 or nubmer four to any of five aux devices
*  15 - Aux button pressed plus one digit number 5 or nubmer five to any of five aux devices
*  16 - Digit number 6 to any of five aux devices
*  17 - Digit number 7 to any of five aux devices
*  18 - Digit number 8 to any of five aux devices
*  20 - OK/GO/PLAY to any of five aux devices
*  21 - UP/STEP > to any of five aux devices
*  22 - DOWN/< STEP to any of five aux devices
*  23 - LEFT/<< to any of five aux devices
*  24 - RIGHT/>> to any of five aux devices
*  25 - STOP to any of five aux devices
*  26 - POWER OFF to any of five aux devices
*  31 - DISPLAY or yellow to any of five aux devices
*  32 - green to any of five aux devices
*  41 - FM Radio station 1
*  42 - FM Radio station 2
*  43 - FM Radio station 3
*  44 - FM Radio station 4
*  45 - FM Radio station 5
*  46 - FM Radio station 6
*  47 - FM Radio station 7
*  48 - FM Radio station 8
*  49 - FM Radio station 9
*  50 - FM Radio station 10
*  51 - FM Radio station 11
*  52 - FM Radio station 12
*  53 - FM Radio station 13
*  54 - FM Radio station 14
*  55 - FM Radio station 15
*  56 - FM Radio station 16
*  57 - FM Radio station 17
*  58 - FM Radio station 18
*  59 - FM Radio station 19
*  60 - FM Radio station 20
*
* Return:
*  zero
*
*******************************************************************************/  
uint8 datalink_check(uint8 command);


#endif // OPERATE_H_

/* [] END OF FILE */
