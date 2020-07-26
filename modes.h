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
*  number of decoded command
*  0 - no new command
*
*******************************************************************************/  
uint8 datalink_decoder();



#endif // MODES_H_

/* [] END OF FILE */
