/***************************************************************************//**
* \file SPIM_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_PVT.h"
#include "SPIM_SPI_UART_PVT.h"

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SPIM_SPI_INIT_STRUCT SPIM_configSpi =
    {
        SPIM_SPI_MODE,
        SPIM_SPI_SUB_MODE,
        SPIM_SPI_CLOCK_MODE,
        SPIM_SPI_OVS_FACTOR,
        SPIM_SPI_MEDIAN_FILTER_ENABLE,
        SPIM_SPI_LATE_MISO_SAMPLE_ENABLE,
        SPIM_SPI_WAKE_ENABLE,
        SPIM_SPI_RX_DATA_BITS_NUM,
        SPIM_SPI_TX_DATA_BITS_NUM,
        SPIM_SPI_BITS_ORDER,
        SPIM_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) SPIM_SCB_IRQ_INTERNAL,
        SPIM_SPI_INTR_RX_MASK,
        SPIM_SPI_RX_TRIGGER_LEVEL,
        SPIM_SPI_INTR_TX_MASK,
        SPIM_SPI_TX_TRIGGER_LEVEL,
        (uint8) SPIM_SPI_BYTE_MODE_ENABLE,
        (uint8) SPIM_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) SPIM_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: SPIM_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SPIM for SPI operation.
    *
    *  This function is intended specifically to be used when the SPIM 
    *  configuration is set to “Unconfigured SPIM” in the customizer. 
    *  After initializing the SPIM in SPI mode using this function, 
    *  the component can be enabled using the SPIM_Start() or 
    * SPIM_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void SPIM_SpiInit(const SPIM_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SPIM_SetPins(SPIM_SCB_MODE_SPI, config->mode, SPIM_DUMMY_PARAM);

            /* Store internal configuration */
            SPIM_scbMode       = (uint8) SPIM_SCB_MODE_SPI;
            SPIM_scbEnableWake = (uint8) config->enableWake;
            SPIM_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SPIM_rxBuffer      =         config->rxBuffer;
            SPIM_rxDataBits    = (uint8) config->rxDataBits;
            SPIM_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            SPIM_txBuffer      =         config->txBuffer;
            SPIM_txDataBits    = (uint8) config->txDataBits;
            SPIM_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            SPIM_CTRL_REG     = SPIM_GET_CTRL_OVS(config->oversample)           |
                                            SPIM_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            SPIM_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            SPIM_CTRL_SPI;

            SPIM_SPI_CTRL_REG = SPIM_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SPIM_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SPIM_SPI_MODE_TI_PRECEDES_MASK) |
                                            SPIM_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SPIM_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SPIM_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            SPIM_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            SPIM_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SPIM_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SPIM_RX_CTRL_REG     =  SPIM_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SPIM_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SPIM_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SPIM_SPI_RX_CTRL;

            SPIM_RX_FIFO_CTRL_REG = SPIM_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SPIM_TX_CTRL_REG      = SPIM_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SPIM_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SPIM_SPI_TX_CTRL;

            SPIM_TX_FIFO_CTRL_REG = SPIM_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (SPIM_ISR_NUMBER);
            CyIntSetPriority(SPIM_ISR_NUMBER, SPIM_ISR_PRIORITY);
            (void) CyIntSetVector(SPIM_ISR_NUMBER, &SPIM_SPI_UART_ISR);

            /* Configure interrupt sources */
            SPIM_INTR_I2C_EC_MASK_REG = SPIM_NO_INTR_SOURCES;
            SPIM_INTR_SPI_EC_MASK_REG = SPIM_NO_INTR_SOURCES;
            SPIM_INTR_SLAVE_MASK_REG  = SPIM_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SPIM_INTR_MASTER_MASK_REG = SPIM_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SPIM_INTR_RX_MASK_REG     = SPIM_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SPIM_INTR_TX_MASK_REG     = SPIM_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            SPIM_IntrTxMask = LO16(SPIM_INTR_TX_MASK_REG);

            /* Set active SS0 */
            SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            SPIM_rxBufferHead     = 0u;
            SPIM_rxBufferTail     = 0u;
            SPIM_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SPIM_txBufferHead = 0u;
            SPIM_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SPIM_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void SPIM_SpiInit(void)
    {
        /* Configure SPI interface */
        SPIM_CTRL_REG     = SPIM_SPI_DEFAULT_CTRL;
        SPIM_SPI_CTRL_REG = SPIM_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SPIM_RX_CTRL_REG      = SPIM_SPI_DEFAULT_RX_CTRL;
        SPIM_RX_FIFO_CTRL_REG = SPIM_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SPIM_TX_CTRL_REG      = SPIM_SPI_DEFAULT_TX_CTRL;
        SPIM_TX_FIFO_CTRL_REG = SPIM_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(SPIM_SCB_IRQ_INTERNAL)
            CyIntDisable    (SPIM_ISR_NUMBER);
            CyIntSetPriority(SPIM_ISR_NUMBER, SPIM_ISR_PRIORITY);
            (void) CyIntSetVector(SPIM_ISR_NUMBER, &SPIM_SPI_UART_ISR);
    #endif /* (SPIM_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        SPIM_INTR_I2C_EC_MASK_REG = SPIM_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SPIM_INTR_SPI_EC_MASK_REG = SPIM_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SPIM_INTR_SLAVE_MASK_REG  = SPIM_SPI_DEFAULT_INTR_SLAVE_MASK;
        SPIM_INTR_MASTER_MASK_REG = SPIM_SPI_DEFAULT_INTR_MASTER_MASK;
        SPIM_INTR_RX_MASK_REG     = SPIM_SPI_DEFAULT_INTR_RX_MASK;
        SPIM_INTR_TX_MASK_REG     = SPIM_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        SPIM_IntrTxMask = LO16(SPIM_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (SPIM_SPI_MASTER_CONST)
        SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT0);
    #endif /* (SPIM_SPI_MASTER_CONST) */

    #if(SPIM_INTERNAL_RX_SW_BUFFER_CONST)
        SPIM_rxBufferHead     = 0u;
        SPIM_rxBufferTail     = 0u;
        SPIM_rxBufferOverflow = 0u;
    #endif /* (SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SPIM_INTERNAL_TX_SW_BUFFER_CONST)
        SPIM_txBufferHead = 0u;
        SPIM_txBufferTail = 0u;
    #endif /* (SPIM_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SPIM_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void SPIM_SpiPostEnable(void)
{
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SPIM_CHECK_SPI_MASTER)
    {
    #if (SPIM_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SCLK_HSIOM_REG, SPIM_SCLK_HSIOM_MASK,
                                       SPIM_SCLK_HSIOM_POS, SPIM_SCLK_HSIOM_SEL_SPI);
    #endif /* (SPIM_SCLK_PIN) */

    #if (SPIM_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS0_HSIOM_REG, SPIM_SS0_HSIOM_MASK,
                                       SPIM_SS0_HSIOM_POS, SPIM_SS0_HSIOM_SEL_SPI);
    #endif /* (SPIM_SS0_PIN) */

    #if (SPIM_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS1_HSIOM_REG, SPIM_SS1_HSIOM_MASK,
                                       SPIM_SS1_HSIOM_POS, SPIM_SS1_HSIOM_SEL_SPI);
    #endif /* (SPIM_SS1_PIN) */

    #if (SPIM_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS2_HSIOM_REG, SPIM_SS2_HSIOM_MASK,
                                       SPIM_SS2_HSIOM_POS, SPIM_SS2_HSIOM_SEL_SPI);
    #endif /* (SPIM_SS2_PIN) */

    #if (SPIM_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS3_HSIOM_REG, SPIM_SS3_HSIOM_MASK,
                                       SPIM_SS3_HSIOM_POS, SPIM_SS3_HSIOM_SEL_SPI);
    #endif /* (SPIM_SS3_PIN) */
    }

#else

    #if (SPIM_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SCLK_M_HSIOM_REG, SPIM_SCLK_M_HSIOM_MASK,
                                       SPIM_SCLK_M_HSIOM_POS, SPIM_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (SPIM_MISO_SDA_TX_PIN_PIN) */

    #if (SPIM_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS0_M_HSIOM_REG, SPIM_SS0_M_HSIOM_MASK,
                                       SPIM_SS0_M_HSIOM_POS, SPIM_SS0_M_HSIOM_SEL_SPI);
    #endif /* (SPIM_SPI_MASTER_SS0_PIN) */

    #if (SPIM_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS1_M_HSIOM_REG, SPIM_SS1_M_HSIOM_MASK,
                                       SPIM_SS1_M_HSIOM_POS, SPIM_SS1_M_HSIOM_SEL_SPI);
    #endif /* (SPIM_SPI_MASTER_SS1_PIN) */

    #if (SPIM_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS2_M_HSIOM_REG, SPIM_SS2_M_HSIOM_MASK,
                                       SPIM_SS2_M_HSIOM_POS, SPIM_SS2_M_HSIOM_SEL_SPI);
    #endif /* (SPIM_SPI_MASTER_SS2_PIN) */

    #if (SPIM_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS3_M_HSIOM_REG, SPIM_SS3_M_HSIOM_MASK,
                                       SPIM_SS3_M_HSIOM_POS, SPIM_SS3_M_HSIOM_SEL_SPI);
    #endif /* (SPIM_SPI_MASTER_SS3_PIN) */

#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    SPIM_SetTxInterruptMode(SPIM_IntrTxMask);
}


/*******************************************************************************
* Function Name: SPIM_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void SPIM_SpiStop(void)
{
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SPIM_CHECK_SPI_MASTER)
    {
    #if (SPIM_SCLK_PIN)
        /* Set output pin state after block is disabled */
        SPIM_spi_sclk_Write(SPIM_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SCLK_HSIOM_REG, SPIM_SCLK_HSIOM_MASK,
                                       SPIM_SCLK_HSIOM_POS, SPIM_SCLK_HSIOM_SEL_GPIO);
    #endif /* (SPIM_spi_sclk_PIN) */

    #if (SPIM_SS0_PIN)
        /* Set output pin state after block is disabled */
        SPIM_spi_ss0_Write(SPIM_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS0_HSIOM_REG, SPIM_SS0_HSIOM_MASK,
                                       SPIM_SS0_HSIOM_POS, SPIM_SS0_HSIOM_SEL_GPIO);
    #endif /* (SPIM_spi_ss0_PIN) */

    #if (SPIM_SS1_PIN)
        /* Set output pin state after block is disabled */
        SPIM_spi_ss1_Write(SPIM_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS1_HSIOM_REG, SPIM_SS1_HSIOM_MASK,
                                       SPIM_SS1_HSIOM_POS, SPIM_SS1_HSIOM_SEL_GPIO);
    #endif /* (SPIM_SS1_PIN) */

    #if (SPIM_SS2_PIN)
        /* Set output pin state after block is disabled */
        SPIM_spi_ss2_Write(SPIM_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS2_HSIOM_REG, SPIM_SS2_HSIOM_MASK,
                                       SPIM_SS2_HSIOM_POS, SPIM_SS2_HSIOM_SEL_GPIO);
    #endif /* (SPIM_SS2_PIN) */

    #if (SPIM_SS3_PIN)
        /* Set output pin state after block is disabled */
        SPIM_spi_ss3_Write(SPIM_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        SPIM_SET_HSIOM_SEL(SPIM_SS3_HSIOM_REG, SPIM_SS3_HSIOM_MASK,
                                       SPIM_SS3_HSIOM_POS, SPIM_SS3_HSIOM_SEL_GPIO);
    #endif /* (SPIM_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        SPIM_IntrTxMask = LO16(SPIM_GetTxInterruptMode() & SPIM_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        SPIM_IntrTxMask = LO16(SPIM_GetTxInterruptMode() & SPIM_INTR_SPIS_TX_RESTORE);
    }

#else

#if (SPIM_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    SPIM_sclk_m_Write(SPIM_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    SPIM_SET_HSIOM_SEL(SPIM_SCLK_M_HSIOM_REG, SPIM_SCLK_M_HSIOM_MASK,
                                   SPIM_SCLK_M_HSIOM_POS, SPIM_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (SPIM_MISO_SDA_TX_PIN_PIN) */

#if (SPIM_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    SPIM_ss0_m_Write(SPIM_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    SPIM_SET_HSIOM_SEL(SPIM_SS0_M_HSIOM_REG, SPIM_SS0_M_HSIOM_MASK,
                                   SPIM_SS0_M_HSIOM_POS, SPIM_SS0_M_HSIOM_SEL_GPIO);
#endif /* (SPIM_SPI_MASTER_SS0_PIN) */

#if (SPIM_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    SPIM_ss1_m_Write(SPIM_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    SPIM_SET_HSIOM_SEL(SPIM_SS1_M_HSIOM_REG, SPIM_SS1_M_HSIOM_MASK,
                                   SPIM_SS1_M_HSIOM_POS, SPIM_SS1_M_HSIOM_SEL_GPIO);
#endif /* (SPIM_SPI_MASTER_SS1_PIN) */

#if (SPIM_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    SPIM_ss2_m_Write(SPIM_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    SPIM_SET_HSIOM_SEL(SPIM_SS2_M_HSIOM_REG, SPIM_SS2_M_HSIOM_MASK,
                                   SPIM_SS2_M_HSIOM_POS, SPIM_SS2_M_HSIOM_SEL_GPIO);
#endif /* (SPIM_SPI_MASTER_SS2_PIN) */

#if (SPIM_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    SPIM_ss3_m_Write(SPIM_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    SPIM_SET_HSIOM_SEL(SPIM_SS3_M_HSIOM_REG, SPIM_SS3_M_HSIOM_MASK,
                                   SPIM_SS3_M_HSIOM_POS, SPIM_SS3_M_HSIOM_SEL_GPIO);
#endif /* (SPIM_SPI_MASTER_SS3_PIN) */

    #if (SPIM_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        SPIM_IntrTxMask = LO16(SPIM_GetTxInterruptMode() & SPIM_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        SPIM_IntrTxMask = LO16(SPIM_GetTxInterruptMode() & SPIM_INTR_SPIS_TX_RESTORE);
    #endif /* (SPIM_SPI_MASTER_CONST) */

#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SPIM_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: SPIM_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - SPIM_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - SPIM_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - SPIM_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - SPIM_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void SPIM_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = SPIM_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~SPIM_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  SPIM_GET_SPI_CTRL_SS(slaveSelect);

        SPIM_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (SPIM_SPI_MASTER_CONST) */


#if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPIM_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - SPIM_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - SPIM_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - SPIM_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - SPIM_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - SPIM_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - SPIM_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void SPIM_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = SPIM_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            SPIM_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            SPIM_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */


#if(SPIM_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SPIM_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void SPIM_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        SPIM_ClearSpiExtClkInterruptSource(SPIM_INTR_SPI_EC_WAKE_UP);
        SPIM_SetSpiExtClkInterruptMode(SPIM_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SPIM_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void SPIM_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        SPIM_SetSpiExtClkInterruptMode(SPIM_NO_INTR_SOURCES);
    }
#endif /* (SPIM_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
