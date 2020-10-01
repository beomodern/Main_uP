/* ========================================
 *
 * Copyright HEMI, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * 
 * Functions used by BeoModern main PSoC to switch unit into different states including
 * OFF, Clock, Player, iRadio, RDS/FM display, DAB radio, BT Rx, BT Tx, AuxIN
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF HEMI.
 *
 * ========================================
*/

#ifndef MODES_H_   /* Include guard */
#define MODES_H_

#include <project.h>

/*Logical Size of Em_EEPROM*/
#define LOGICAL_EEPROM_SIZE     3u
#define LOGICAL_EEPROM_START    0u


// EEPROM writes
// [0] = SYSTEM_STATE 
// [1] = DISPLAY_STATE
// [2] = BT_Tx_STATE
uint8 array[3];
uint8 eepromArray[3];


uint8 SYSTEM_STATE;    // variable used to store whole system state 
uint8 DISPLAY_STATE;   // variable used to store display state
uint8 BT_Tx_STATE;     // variable used to store BT Tx state   

// flag used to indicate new data ready to be sent over SPI to display module
uint8 new_display_data_flag;
// new data that needs to be sent over SPI to display module
uint8 new_display_data_buffer[24];
uint8 new_disp_ctrl1;
uint8 new_disp_ctrl2;

// structure type to store Power Supply state
struct Power_Supply_State { 
    uint8 RPI_PWR;
    uint8 RPi_GPIO_state;
    uint8 SigmaDSP_PWR;
    uint8 BlueTooth_PWR;
    uint8 Display_PWR;
}; 
  
typedef struct Power_Supply_State psuState; 

psuState next_PSUstate, current_PSUstate;

/*******************************************************************************
* Function Name: buttons_check()
********************************************************************************
* Summary:
*  Button press funciton that checkc button actions. It also initialize state
*  of main system to the latest one stored in emulated EEPROM space. 
*   
* Parameters:
*  None
*
* Return:
*  1 if button was pressed
*  0 if no button were pressed
*
*******************************************************************************/  
uint8 buttons_check();    





/*******************************************************************************
* Function Name: BT_control()
********************************************************************************
* Summary:
*  BlueTooth control funciton. Allows set all available bluetooth functions 
*  as well as it reads back BlueTooth module current status
*   
* Parameters:
*  mode:
*    0 = report back status only
*    1 = switch to Tx
*    2 = switch to Rx
*  action:
*    0 = report back status only
*    1 = start pairing
*    2 = re-connect
*    3 = clear all recorded devices
*    4 = pause/mute
*    5 = back (in Rx mode, previus song)
*    6 = next (in Rx mode, next song)
*
* Return:
*    0 = power down
*    1 = connected
*    2 = searching
*    3 = sleep
*    4 = SBC
*    5 = AAC
*    6 = aptX
*    7 = aptxHD
*    8 = aptxLL
*
*******************************************************************************/  
uint8 BT_control(uint8, uint8);



/*******************************************************************************
* Function Name: psu_config()
********************************************************************************
* Summary:
*  Power supply control funciton that enables/disables differnt BeoModern blocks
*  and reports back their current state.
*  It controls power supplies to:
*  - Raspberry Pi
*     - it reads back and reports state of RPi GPIO indicatign its state ON/OFF
*  - SigmaDSP EVB
*  - BlueTooth module
*  - Display module
*   
* Parameters:
*  switch to set or report back PSU states
*  structure with expected stated of controlled blocks 
*
* Return:
*  structure with current states of controlled blocks 
*
*******************************************************************************/  
psuState psu_config(uint8, psuState);    



/*******************************************************************************
* Function Name: datalink_decoder()
********************************************************************************
* Summary:
*  Function responsible for encoding raw datalink timing informaiton into
*  commands
*   
* Parameters:
*  No parameters as input. Function operates on global varaibles set by interrupt 
*  routine
*
* Return:
*  code represents error or decoded command as follow:
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
*  27 - MENU(onBeo4)/TURN(on MCP) to any of five aux devices
*  28 - EXIT(on Beo4)/RESET(on MCP) to any of five aux devices
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
*******************************************************************************/  
uint8 datalink_decoder();




/*******************************************************************************
* Function Name: SigmaDSP_to_display()
********************************************************************************
* Summary:
*  Function 
*   
* Parameters:
*  0 - read back signal level values and encode them into information sent to 
*      display module
*  1 - read back spectrum analyser info and encode it into informaiton sent to
*      display module
*
* Return:
*  Funciton returns zero value
*
*******************************************************************************/  
uint8 SigmaDSP_to_display(uint8 mode);  



/*******************************************************************************
* Function Name: DATALINK_times()
********************************************************************************
* Summary:
*  Function responsible for producing activity on DATALINK line following
*  DATALINK standard.
*   
* Parameters:
*  time - 1 for t1 = 3.125mS 
*         2 for t2 = 6.250mS
*         3 for t3 = 9.375mS
*         4 for t4 = 12.500mS
*         5 for t5 = 15.625mS
*
* Return:
*  1 if all good
*  0 if there was a clash on datalink port (another device transmitted)
*
*******************************************************************************/  
uint8 DATALINK_times(uint8 time);


/*******************************************************************************
* Function Name: DATALINK_out()
********************************************************************************
* Summary:
*  Function reposnisble for sending data over datalink port. Implementaton is quite 
*  crude due to the fact that device will require only two commands. Power up 
*  (in Aux mode) and power down.
*   
* Parameters:
*  command = 0 -> power down 
*          = 1 -> power up in Aux mode
* Return:
*  0 = conflict on DATALINK port was recorded function didn't finish its 
*      command transmission
*  1 = command sent succesfully (no confilct on DATALINK line)
*
*******************************************************************************/  
uint8 DATALINK_out(uint8 command);  


#endif // MODES_H_

/* [] END OF FILE */
