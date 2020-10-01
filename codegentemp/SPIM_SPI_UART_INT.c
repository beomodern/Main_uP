/***************************************************************************//**
* \file SPIM_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_PVT.h"
#include "SPIM_SPI_UART_PVT.h"


#if (SPIM_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: SPIM_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(SPIM_SPI_UART_ISR)
{
#if (SPIM_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SPIM_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (SPIM_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef SPIM_SPI_UART_ISR_ENTRY_CALLBACK
    SPIM_SPI_UART_ISR_EntryCallback();
#endif /* SPIM_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != SPIM_customIntrHandler)
    {
        SPIM_customIntrHandler();
    }

    #if(SPIM_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        SPIM_ClearSpiExtClkInterruptSource(SPIM_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (SPIM_CHECK_RX_SW_BUFFER)
    {
        if (SPIM_CHECK_INTR_RX_MASKED(SPIM_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (SPIM_rxBufferHead + 1u);

                /* Adjust local head index */
                if (SPIM_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == SPIM_rxBufferTail)
                {
                    #if (SPIM_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        SPIM_INTR_RX_MASK_REG &= ~SPIM_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) SPIM_RX_FIFO_RD_REG;
                        SPIM_rxBufferOverflow = (uint8) SPIM_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    SPIM_PutWordInRxBuffer(locHead, SPIM_RX_FIFO_RD_REG);

                    /* Move head index */
                    SPIM_rxBufferHead = locHead;
                }
            }
            while(0u != SPIM_GET_RX_FIFO_ENTRIES);

            SPIM_ClearRxInterruptSource(SPIM_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (SPIM_CHECK_TX_SW_BUFFER)
    {
        if (SPIM_CHECK_INTR_TX_MASKED(SPIM_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (SPIM_txBufferHead != SPIM_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (SPIM_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (SPIM_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    SPIM_TX_FIFO_WR_REG = SPIM_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    SPIM_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    SPIM_DISABLE_INTR_TX(SPIM_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (SPIM_SPI_UART_FIFO_SIZE != SPIM_GET_TX_FIFO_ENTRIES);

            SPIM_ClearTxInterruptSource(SPIM_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef SPIM_SPI_UART_ISR_EXIT_CALLBACK
    SPIM_SPI_UART_ISR_ExitCallback();
#endif /* SPIM_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (SPIM_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
