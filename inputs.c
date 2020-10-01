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
#include <project.h>
#include <modes.h>
#include <inputs.h>

/* global variables */
uint8 MODE_SWITCH = 0;    /* switch storing info on MODE button long press */
uint8 PWR_OK_SWITCH = 0;  /* switch storing info on Power/OK button long press */

uint8 MODE_SHORT_V = 0;     /* variable storing MODE short button press event */
uint8 PWR_OK_SHORT_V = 0;   /* variable storing PWR/OK short button press event */
uint8 MODE_LONG_V = 0;      /* variable storing MODE long button press event  */
uint8 PWR_OK_LONG_V = 0;    /* variable storing PWR/OK long button press event  */


// DATALINK DATA ARRAY
uint8 DATALINK_TABLE[64] = {0};
uint8 DATALINK_TABLE_COUNTER = 0;
uint8 DATALINK_TABLE_COUNTER_MAX = 0;



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
CY_ISR(PWR_OK_MODE_SHORT_ISR)
{
// Check if interrupt is triggered by MODE push button release (rising edge)
    if(PWR_OK_MODE_INTSTAT & 0x40u)
    { 
    if (MODE_SWITCH == 1)       // check if rising edge is after long press time
        {
            MODE_SWITCH = 0;    // if it is, clear flag and exit
        }
        else
        {
            MODE_SHORT_V = 1;   // if it is not, set variale indicating MODE short press
        }
    }
// Check if interrupt is triggered by PWR_OK push button release (rising edge)
    if(PWR_OK_MODE_INTSTAT & 0x80u)
    {
    if (PWR_OK_SWITCH == 1)     // check if rising edge is after long press time
        {
            PWR_OK_SWITCH = 0;  // if it is, clear flag and exit
        }
        else
        {
            PWR_OK_SHORT_V = 1;   // if it is not, set variale indicating PWR_OK short press
        }
    } 
// Wait 2mS before clearing interrupt to debounce push buttons
    CyDelay(2);
// Clear interrupt 
    PWR_OK_MODE_ClearInterrupt();  
}


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
CY_ISR(MODE_LONG_ISR)
{
    /* Check interrupt source and clear Interrupt */
    if (Timer_1_GetInterruptSourceMasked() == Timer_1_INTR_MASK_TC)
    {
        MODE_SWITCH = 1;        // set switch to prevent recognizing falling edge as short press
        MODE_LONG_V = 1;        // set variable indicating long press
        Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
                                // clear interrupt source from timer
    }
}


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
CY_ISR(PWR_OK_LONG_ISR)
{
    /* Check interrupt source and clear Interrupt */
    if (Timer_2_GetInterruptSourceMasked() == Timer_2_INTR_MASK_TC)
    {
        PWR_OK_SWITCH = 1;      // set switch to prevent recognizing falling edge as short press
        PWR_OK_LONG_V = 1;      // set variable indicating long press
        Timer_2_ClearInterrupt(Timer_2_INTR_MASK_TC);
                                // clear interrupt source from timer
    }
}


/*******************************************************************************
* Function Name: CY_ISR(DATALINK_INTRRUPTHandler)
********************************************************************************
* Summary:
*  The Interrupt Service Routine. Triggered by DATALINK counter exceeding timer 
*  count (STOP condition) or when timer FIFO is full (4 new bits)
*   
* Parameters:
*  Routine operates on 3 global vatiables (due to the fact that it can caleld in 
*  the middle of incomming command to clear 4 byte FIFO.
*  DATALINK_TABLE[64] - to store incoming information about timer values
*  DATALINK_TABLE_COUNTER - to store current posiiton in incoming command
*  DATALINK_TABLE_COUNTER_MAX - to store and indicate to the system that new 
*  command arrived. Serving routine (datalink)decoder) operate on it plus 
*  DATALINK_TABLE content. 
*
* Return:
*  Sets value of DATALINK_TABLE_COUNTER_MAX to the size of last DATALINK command.
*
********************************************************************************/
CY_ISR(DATALINK_INTRRUPTHandler)
{
// variable storing info on DATALINK interrupt source
    uint8 DATALINK_STATUS = 0; 
// read DATALINK timer status regiister    
    DATALINK_STATUS = DATALINK_Timer_ReadStatusRegister();
// Check if interrupt came from Timer Counter expired (indicating end of new command)
    if (0u != (DATALINK_STATUS & 0x01))
    {
// flush all data that is still in FIFO        
        while (0u != (DATALINK_Timer_ReadStatusRegister() & 0x08))
        {
// increase table pointer            
            DATALINK_TABLE_COUNTER = DATALINK_TABLE_COUNTER + 1;
// store data from fifo into table            
            DATALINK_TABLE[DATALINK_TABLE_COUNTER] = DATALINK_Timer_ReadCapture();
        }
// store latest table data size - this will indicate that new command was received
        DATALINK_TABLE_COUNTER_MAX = DATALINK_TABLE_COUNTER;
// reset table data pointer for next command        
        DATALINK_TABLE_COUNTER = 0;
// clear all remining interrupts        
        DATALINK_INTRRUPT_ClearPending();
    }
  
// Check interrupt came from FIFO full (4 new bits)
    if (0u != (DATALINK_STATUS & DATALINK_Timer_STATUS_FIFOFULL))
    {
// flush all data that is still in FIFO           
        while (0u != (DATALINK_Timer_ReadStatusRegister() & 0x08))
        {
// increase table pointer             
            DATALINK_TABLE_COUNTER = DATALINK_TABLE_COUNTER + 1;
// store data from fifo into table             
            DATALINK_TABLE[DATALINK_TABLE_COUNTER] = DATALINK_Timer_ReadCapture();
        }
    }
}


/*******************************************************************************
* Function Name: CY_ISR(DISPLAY_Timer_INTHandler)
********************************************************************************
* Summary:
*  The Interrupt Service Routine. Triggered by software when timer expires after 
*  DISPLAY_Timer_Start() is called. It uses timer to count 2 seconds wait.
*  This time is used to display information that are temporary (like button press
*  or BT status).
*   
* Parameters:
*  Timer interrupt handler 
*
* Return:
*  updates DISPLAY_UPDATE variable.when TC is called.
*
********************************************************************************/
CY_ISR(DISPLAY_Timer_INTHandler)
{
// Check if interrupt came from Timer Counter expired (indicating timer count elapsed)
    if (0u != (DISPLAY_Timer_ReadStatusRegister() & 0x01))
    {
// sets display update variable 
        DISPLAY_UPDATE = 1;
// clear all remining interrupts        
        DISPLAY_Timer_INT_ClearPending();
// stop timer and wait for another software call to start        
        DISPLAY_Timer_Stop();
    }

}


/* [] END OF FILE */

