/* ========================================
 *
 * Copyright HEMI, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * 
 * Functions used by BeoModern main PSoC to monitor input informaiton coming from
 * push buttons and over DataLink interface
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF HEMI.
 *
 * ========================================
*/

#ifndef INPUTS_H_   /* Include guard */
#define INPUTS_H_

#include <project.h>

uint8 MODE_SHORT_V;     /* variable storing MODE short button press event */
uint8 PWR_OK_SHORT_V;   /* variable storing PWR/OK short button press event */
uint8 MODE_LONG_V;      /* variable storing MODE long button press event  */
uint8 PWR_OK_LONG_V;    /* variable storing PWR/OK long button press event  */

uint8 DATALINK_TABLE[64];    
uint8 DATALINK_TABLE_COUNTER;
uint8 DATALINK_TABLE_COUNTER_MAX;

/*******************************************************************************
* Function Name: CY_ISR(PWR_OK_MODE_SHORT_ISR)
********************************************************************************
* Summary:
*  The Interrupt Service Routine. Triggered when PWR_OK or MODE button was released 
*  after pressing. Looks on faling edge. 
*  If falling edge is later than time assigned to long press, routine clears long 
*  press flag only.
*  If falling edge is earlier than time assigned to long press, routine blinks 
*  LED and set apriopriate variable MODE_SHORT_V or PWR_OK_SHORT_V
*  After that interrupt is cleared (after waiting fo 2mS to debounce.     
*   
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(PWR_OK_MODE_SHORT_ISR);

/*******************************************************************************
* Function Name: CY_ISR(MODE_LONG_ISR)
********************************************************************************
* Summary:
*  The Interrupt Service Routine. Triggered when Timer started by MODE button  
*  reaches pre-defined count. 
*  When triggered, interrupt source is cleared, MODE_SWITCH variable is set and
*  LED blinks
*   
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(MODE_LONG_ISR);


/*******************************************************************************
* Function Name: CY_ISR(PWR_OK_LONG_ISR)
********************************************************************************
* Summary:
*  The Interrupt Service Routine. Triggered when Timer started by PWR_OK button  
*  reaches pre-defined count. 
*  When triggered, interrupt source is cleared, PWR_OK_SWITCH variable is set and
*  LED blinks
*   
* Parameters:
*  None
*
* Return:
*  None
*
********************************************************************************/
CY_ISR(PWR_OK_LONG_ISR);


/*******************************************************************************
* Function Name: CY_ISR(DATALINK_INTRRUPTHandler)
********************************************************************************
* Summary:
*  The Interrupt Service Routine. Triggered by DATALINK counter exceeding timer 
*  count (STOP condition) or when timer FIFO is full (4 new bits)
*   
* Parameters:
*  None
*
* Return:
*  None
*
********************************************************************************/
CY_ISR(DATALINK_INTRRUPTHandler);


#endif // INPUTS_H_

/* [] END OF FILE */
