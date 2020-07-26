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

#ifndef OPEARATE_H_   /* Include guard */
#define OPERATE_H_

#include <project.h>

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
*  SYSTEM_STATE = 5 - RDS/FM display
*  SYSTEM_STATE = 6 - BlueTooth Rx
*  SYSTEM_STATE = 7 - BlueTooth Tx
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
* Function Name: BeoM_current_mode()
********************************************************************************
* Summary:
*  Function monitors SYSTEM STATE variabel and listen to incoming commands from
*  push buttons and over Datalink. 
*  it then reacts accordingly to active state. 
*  SYSTEM_STATE = 0 - power down
*  SYSTEM_STATE = 1 - Player
*  SYSTEM_STATE = 2 - iRadio
*  SYSTEM_STATE = 3 - DAB Radio
*  SYSTEM_STATE = 4 - Aux IN
*  SYSTEM_STATE = 5 - RDS/FM display
*  SYSTEM_STATE = 6 - BlueTooth Rx
*  SYSTEM_STATE = 7 - BlueTooth Tx
*
*   
* Parameters:
*  Function operates on global variable:
*  SYSTEM_STATE and expect to be called witch command nubmer
*  Input commands:
*  1 = UP
*  2 = DOWN
*  3 = NEXT
*  4 = PREVIUS
*  5 = OK/GO
*  6 = STOP
*  7 = Button: MODE SHORT
*  ??? = FM station nubmers
*
* Return:
*  Funciton returns current ????
*
*******************************************************************************/  
uint8 BeoM_PSU_current_mode(uint8 command);  


#endif // OPERATE_H_

/* [] END OF FILE */
