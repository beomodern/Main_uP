/*******************************************************************************
* \file SENT_TX_1.c
* \version 1.0
*
*  This file provides all API functionality of the SENT component
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SENT_TX_1.h"

static uint8 SENT_TX_1_CalculateCrc(uint8 const data[]);
static void SENT_TX_1_SwapBuffers(void);

#if (SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED)
    static uint8 SENT_TX_1_CalculatePauseData(uint8 const data[]);
#endif /* SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED */


/*******************************************************************************
*   Global variables
*******************************************************************************/

/** The global variable that indicates the initialization status of the 
*  SENT_TX_1 component
*/
uint8 SENT_TX_1_initVar = 0U;

/** The variable that indicates a component status, see \ref group_sent_status */
uint8 SENT_TX_1_status = SENT_TX_1_READY;


/*******************************************************************************
*       Local variables
*******************************************************************************/

/* The buffers that provide continuous data transmission */
static uint8 SENT_TX_1_buf0[SENT_TX_1_LAST_IDX];
static uint8 SENT_TX_1_buf1[SENT_TX_1_LAST_IDX];

/* The pointers to switch through the buffers */
static uint8 *SENT_TX_1_bufTx; /* Pointer to the "transfer" data buffer */
static uint8 *SENT_TX_1_bufPr; /* Pointer to the "prepare" data buffer */

/* The local index used to jump through pulses */
static uint8 SENT_TX_1_idx = SENT_TX_1_NEW_FRAME;


/*******************************************************************************
* Function Name: SENT_TX_1_Interrupt
****************************************************************************//**
*
* Provides SENT transmission.
*
* This is the interrupt handler which prepares the TCPWM component for the next 
* nibble pulse generation.
*
*******************************************************************************/
CY_ISR(SENT_TX_1_Interrupt)
{
    switch(SENT_TX_1_idx)
    {

    #if (SENT_TX_1_TRANSMIT_MODE == SENT_TX_1__SINGLE_MODE)

        /* Prepare PWM to be stopped on the next PWM interrupt */
        case SENT_TX_1_PREPARE_TO_STOP_COUNTER:
        {
            SENT_TX_1_PWM_WritePeriod(SENT_TX_1_TICKS_PREP_TO_STOP);
            SENT_TX_1_PWM_WriteCompare(SENT_TX_1_COMP_PREP_TO_STOP);

            /* Update the index value to stop the counter in the next interrupt */
            SENT_TX_1_idx = SENT_TX_1_STOP_COUNTER;
        }
        break;

        /* One frame transmission was done (Single mode). Stop the PWM and 
        *  prepare the PWM to sent new frame
        */
        case SENT_TX_1_STOP_COUNTER:
        {
            SENT_TX_1_PWM_TriggerCommand(SENT_TX_1_PWM_MASK, SENT_TX_1_PWM_CMD_STOP);

            /* Prepare PWM to sent sync pulse if new frame transmission would be
            *  requested.
            */
            SENT_TX_1_PWM_WritePeriod(SENT_TX_1_SYNC_TICKS - 1U);
            
            /* Clear all required PWM registers */
            SENT_TX_1_PWM_WriteCompare(0U);
            SENT_TX_1_PWM_WriteCounter(0U);
            SENT_TX_1_PWM_WritePeriodBuf(0U);

            SENT_TX_1_status = SENT_TX_1_READY;
        }
        break;
    #else

        /* One frame transmission was done (Continuous mode). If new data is 
        *  ready swap the buffers, and send the sync pulse
        */
        case SENT_TX_1_END_OF_FRAME:
        {
            SENT_TX_1_PWM_WriteCompare(SENT_TX_1_PWM_LOW_TICKS);
            SENT_TX_1_idx = SENT_TX_1_NEW_FRAME;

            /* Check for the new data available */
            if (SENT_TX_1_status == SENT_TX_1_BUSY)
            {
                SENT_TX_1_SwapBuffers();
                SENT_TX_1_status = SENT_TX_1_READY;
            }

            SENT_TX_1_PWM_WritePeriodBuf(SENT_TX_1_SYNC_TICKS - 1U);

        }
        break;
    #endif /* SENT_TX_1_TRANSMIT_MODE == SENT_TX_1__SINGLE_MODE */

        /* The default case indicates that message sending is in progress and 
        *  the next nibble pulse should be prepared
        */
        default:
        {
            SENT_TX_1_PWM_WritePeriodBuf((SENT_TX_1_ZERO_TICKS - 1U) + 
            (uint32) SENT_TX_1_bufTx[SENT_TX_1_idx]);

            ++SENT_TX_1_idx;
        }
        break;
    }
    /* Set a switch trigger flag in the TCPWM trigger register */
    SENT_TX_1_PWM_TriggerCommand(SENT_TX_1_PWM_MASK, SENT_TX_1_PWM_CMD_CAPTURE);

    /* Clear the interrupt pending flag*/
    SENT_TX_1_PWM_ClearInterrupt(SENT_TX_1_PWM_INTR_MASK_TC);
}


/*******************************************************************************
* Function Name: SENT_TX_1_Init
****************************************************************************//**
*
* Initialize/Restore default SENT_TX_1 configuration.
*
*******************************************************************************/
void   SENT_TX_1_Init(void)
{
    SENT_TX_1_CLK_SetDividerValue(SENT_TX_1_CLOCK_DIVIDER);
    
    SENT_TX_1_PWM_Init();
    SENT_TX_1_ISR_StartEx(&SENT_TX_1_Interrupt);
}


/*******************************************************************************
* Function Name: SENT_TX_1_Start
****************************************************************************//**
*
* Initializes SENT_TX_1 with default customizer values when called
* the first time and enables SENT_TX_1.
* For subsequent calls the configuration is left unchanged and only the 
* component is enabled.
*
* \param data
* The pointer to the uint8 array of length SENT_TX_1_USER_NIBBLES, where
* the 1st byte is the status nibble and the next 6 bytes are data nibbles.
*
* \globalvars 
* \ref SENT_TX_1_initVar
*
* Note each call of SENT_TX_1_Start() will restart the counter and the 
* message will be transmitted from the first nibble.
*
*******************************************************************************/
void SENT_TX_1_Start(uint8 const data[]) 
{
    if (SENT_TX_1_initVar == 0U)
    {
        SENT_TX_1_Init();
        SENT_TX_1_initVar = 1U; 
    }

    SENT_TX_1_bufPr = SENT_TX_1_buf0;
    SENT_TX_1_UpdateData(data);

    SENT_TX_1_bufTx = SENT_TX_1_buf0;
    SENT_TX_1_bufPr = SENT_TX_1_buf1;

#if (SENT_TX_1_TRANSMIT_MODE != SENT_TX_1__SINGLE_MODE)
    SENT_TX_1_status = SENT_TX_1_READY;
#endif /* SENT_TX_1_TRANSMIT_MODE != SENT_TX_1__SINGLE_MODE */

    /* Reset a SENT_TX interrupt state machine */
    SENT_TX_1_idx = SENT_TX_1_NEW_FRAME;
    SENT_TX_1_PWM_WritePeriod(SENT_TX_1_SYNC_TICKS - 1U);
    
    /* Enable the PWM component */
    SENT_TX_1_PWM_Enable();
}


/*******************************************************************************
* Function Name: SENT_TX_1_UpdateData
****************************************************************************//**
*
* Writes the frame with new data into the transfer buffer.
*
* \param data
* The pointer to the uint8 array of length SENT_TX_1_USER_NIBBLES, where
* the first byte is the status nibble and the next six bytes are data nibbles.
*
*******************************************************************************/
void SENT_TX_1_UpdateData(uint8 const data[])
{
    uint8 i;

    SENT_TX_1_status = SENT_TX_1_READY;

    /* Check for the "prepare" data buffer allocation */
    if (SENT_TX_1_bufPr != NULL)
    {
        for(i = 0U; i < SENT_TX_1_USER_NIBBLES; i++)
        {
            SENT_TX_1_bufPr[i] = data[i] & SENT_TX_1_NIBBLE_MASK;
        }

        SENT_TX_1_bufPr[SENT_TX_1_CRC_IDX] = SENT_TX_1_CalculateCrc(SENT_TX_1_bufPr);

    #if (SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED)

        /* Calculate pause pulse value */
        SENT_TX_1_bufPr[SENT_TX_1_PAUSE_IDX] = 
        SENT_TX_1_CalculatePauseData(SENT_TX_1_bufPr);
    #endif /* SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED */

    #if (SENT_TX_1_TRANSMIT_MODE == SENT_TX_1__SINGLE_MODE)

        /* Restart the PWM (Single mode), swap the buffers for the new frame
        *  transition
        */
        if (SENT_TX_1_idx == SENT_TX_1_STOP_COUNTER)
        {
            SENT_TX_1_idx = SENT_TX_1_NEW_FRAME;
            SENT_TX_1_SwapBuffers();

            SENT_TX_1_PWM_WriteCompare(SENT_TX_1_PWM_LOW_TICKS);
            SENT_TX_1_PWM_TriggerCommand(SENT_TX_1_PWM_MASK, SENT_TX_1_PWM_CMD_START);
        }
    #endif /* SENT_TX_1_TRANSMIT_MODE == SENT_TX_1__SINGLE_MODE */ 

        SENT_TX_1_status = SENT_TX_1_BUSY;
    }
    else
    {
       CYASSERT(0U != 0U);
    }
}


/*******************************************************************************
* Function Name: SENT_TX_1_CalculateCrc
****************************************************************************//**
*
* Calculates the cyclic redundancy check value.
*
* \param data
* The pointer to the uint8 array of length SENT_TX_1_USER_NIBBLES, where
* the 1st byte is the status nibble and the next 6 bytes are data nibbles.
*
* \return
* The cyclic redundancy check value of the new data nibbles.
*
*******************************************************************************/
static uint8 SENT_TX_1_CalculateCrc(uint8 const data[])
{
    /* This is a lookup table that writes in the RAM memory */
    static const uint8 crcTable[] = 
    {
        0U, 13U, 7U, 10U, 14U, 3U, 9U, 4U,
        1U, 12U, 6U, 11U, 15U, 2U, 8U, 5U
    };
    
    /* Write the seed value in the crc variable before calculations */
    uint8 crc = SENT_TX_1_SEED;
    uint32 i;
    
    /* Calculate the data CRC value */
    for(i = 1U; i < SENT_TX_1_USER_NIBBLES; i++)
    {
        crc = crcTable[crc] ^ (data[i] & SENT_TX_1_NIBBLE_MASK);
    }

#if (SENT_TX_1_CRC_IMPLEMENTATION == SENT_TX_1__NEWCRC)
    /* The checksum using new CRC method */
    crc = crcTable[crc];
#endif /* SENT_TX_1_CRC_IMPLEMENTATION == SENT_TX_1__NEWCRC */

    return (crc);
}

#if (SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED)

    /*******************************************************************************
    * Function Name: SENT_TX_1_CalculatePauseData
    ****************************************************************************//**
    *
    * Calculates the duration of the pause nibble, for the frame with new data.
    *
    * \param data
    * The pointer to the uint8 array of length SENT_TX_1_ALL_NIBBLES, where
    * the 1st byte is the status nibble, the next 6 bytes are data nibbles,
    * and the last nibble is a CRC value.
    *
    * \return
    * The duration of the pause period (in clock period units).
    *
    *******************************************************************************/
    static uint8 SENT_TX_1_CalculatePauseData(uint8 const data[])
    {
        uint8 frameDuration = SENT_TX_1_ALL_TICKS - ((uint8)SENT_TX_1_SYNC_TICKS + SENT_TX_1_ZERO_TICKS);

        uint8 i;

        for(i = 0U; i < SENT_TX_1_ALL_NIBBLES; i++)
        {
            frameDuration -= (SENT_TX_1_ZERO_TICKS + (data[i] & SENT_TX_1_NIBBLE_MASK));
        }

        return (frameDuration);
    }
#endif /* SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED */


/*******************************************************************************
* Function Name: SENT_TX_1_SwapBuffers
****************************************************************************//**
*
* Internal function which swaps the "transmition" and "prepare" buffers
*
*******************************************************************************/
static void SENT_TX_1_SwapBuffers(void)
{
    if (SENT_TX_1_bufTx == SENT_TX_1_buf0)
    {
        SENT_TX_1_bufTx = SENT_TX_1_buf1;
        SENT_TX_1_bufPr = SENT_TX_1_buf0;
    }
    else
    {
        SENT_TX_1_bufTx = SENT_TX_1_buf0;
        SENT_TX_1_bufPr = SENT_TX_1_buf1;
    }
}


/* [] END OF FILE */
