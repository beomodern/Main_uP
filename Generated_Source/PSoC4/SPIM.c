/***************************************************************************//**
* \file SPIM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (SPIM_SCB_MODE_I2C_INC)
    #include "SPIM_I2C_PVT.h"
#endif /* (SPIM_SCB_MODE_I2C_INC) */

#if (SPIM_SCB_MODE_EZI2C_INC)
    #include "SPIM_EZI2C_PVT.h"
#endif /* (SPIM_SCB_MODE_EZI2C_INC) */

#if (SPIM_SCB_MODE_SPI_INC || SPIM_SCB_MODE_UART_INC)
    #include "SPIM_SPI_UART_PVT.h"
#endif /* (SPIM_SCB_MODE_SPI_INC || SPIM_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 SPIM_scbMode = SPIM_SCB_MODE_UNCONFIG;
    uint8 SPIM_scbEnableWake;
    uint8 SPIM_scbEnableIntr;

    /* I2C configuration variables */
    uint8 SPIM_mode;
    uint8 SPIM_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * SPIM_rxBuffer;
    uint8  SPIM_rxDataBits;
    uint32 SPIM_rxBufferSize;

    volatile uint8 * SPIM_txBuffer;
    uint8  SPIM_txDataBits;
    uint32 SPIM_txBufferSize;

    /* EZI2C configuration variables */
    uint8 SPIM_numberOfAddr;
    uint8 SPIM_subAddrSize;
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** SPIM_initVar indicates whether the SPIM 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the SPIM_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  SPIM_Init() function can be called before the 
*  SPIM_Start() or SPIM_Enable() function.
*/
uint8 SPIM_initVar = 0u;


#if (! (SPIM_SCB_MODE_I2C_CONST_CFG || \
        SPIM_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * SPIM_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent SPIM_Enable() call.
    */
    uint16 SPIM_IntrTxMask = 0u;
#endif /* (! (SPIM_SCB_MODE_I2C_CONST_CFG || \
              SPIM_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (SPIM_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SPIM_CUSTOM_INTR_HANDLER)
    void (*SPIM_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_SPIM_CUSTOM_INTR_HANDLER) */
#endif /* (SPIM_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void SPIM_ScbEnableIntr(void);
static void SPIM_ScbModeStop(void);
static void SPIM_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: SPIM_Init
****************************************************************************//**
*
*  Initializes the SPIM component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SPIM_I2CInit, SPIM_SpiInit, 
*  SPIM_UartInit or SPIM_EzI2CInit.
*
*******************************************************************************/
void SPIM_Init(void)
{
#if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SPIM_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPIM_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (SPIM_SCB_MODE_I2C_CONST_CFG)
    SPIM_I2CInit();

#elif (SPIM_SCB_MODE_SPI_CONST_CFG)
    SPIM_SpiInit();

#elif (SPIM_SCB_MODE_UART_CONST_CFG)
    SPIM_UartInit();

#elif (SPIM_SCB_MODE_EZI2C_CONST_CFG)
    SPIM_EzI2CInit();

#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIM_Enable
****************************************************************************//**
*
*  Enables SPIM component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  SPIM_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The SPIM configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured SPIM”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void SPIM_Enable(void)
{
#if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!SPIM_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPIM_CTRL_REG |= SPIM_CTRL_ENABLED;

        SPIM_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        SPIM_ScbModePostEnable();
    }
#else
    SPIM_CTRL_REG |= SPIM_CTRL_ENABLED;

    SPIM_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    SPIM_ScbModePostEnable();
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIM_Start
****************************************************************************//**
*
*  Invokes SPIM_Init() and SPIM_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  SPIM_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SPIM_Start(void)
{
    if (0u == SPIM_initVar)
    {
        SPIM_Init();
        SPIM_initVar = 1u; /* Component was initialized */
    }

    SPIM_Enable();
}


/*******************************************************************************
* Function Name: SPIM_Stop
****************************************************************************//**
*
*  Disables the SPIM component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function SPIM_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void SPIM_Stop(void)
{
#if (SPIM_SCB_IRQ_INTERNAL)
    SPIM_DisableInt();
#endif /* (SPIM_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    SPIM_ScbModeStop();

    /* Disable SCB IP */
    SPIM_CTRL_REG &= (uint32) ~SPIM_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    SPIM_SetTxInterruptMode(SPIM_NO_INTR_SOURCES);

#if (SPIM_SCB_IRQ_INTERNAL)
    SPIM_ClearPendingInt();
#endif /* (SPIM_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPIM_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void SPIM_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = SPIM_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~SPIM_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (SPIM_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SPIM_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: SPIM_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void SPIM_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = SPIM_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~SPIM_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (SPIM_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SPIM_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (SPIM_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: SPIM_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void SPIM_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_SPIM_CUSTOM_INTR_HANDLER)
        SPIM_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_SPIM_CUSTOM_INTR_HANDLER) */
    }
#endif /* (SPIM_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: SPIM_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void SPIM_ScbEnableIntr(void)
{
#if (SPIM_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != SPIM_scbEnableIntr)
        {
            SPIM_EnableInt();
        }

    #else
        SPIM_EnableInt();

    #endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SPIM_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPIM_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void SPIM_ScbModePostEnable(void)
{
#if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!SPIM_CY_SCBIP_V1)
    if (SPIM_SCB_MODE_SPI_RUNTM_CFG)
    {
        SPIM_SpiPostEnable();
    }
    else if (SPIM_SCB_MODE_UART_RUNTM_CFG)
    {
        SPIM_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!SPIM_CY_SCBIP_V1) */

#elif (SPIM_SCB_MODE_SPI_CONST_CFG)
    SPIM_SpiPostEnable();

#elif (SPIM_SCB_MODE_UART_CONST_CFG)
    SPIM_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIM_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void SPIM_ScbModeStop(void)
{
#if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SPIM_SCB_MODE_I2C_RUNTM_CFG)
    {
        SPIM_I2CStop();
    }
    else if (SPIM_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SPIM_EzI2CStop();
    }
#if (!SPIM_CY_SCBIP_V1)
    else if (SPIM_SCB_MODE_SPI_RUNTM_CFG)
    {
        SPIM_SpiStop();
    }
    else if (SPIM_SCB_MODE_UART_RUNTM_CFG)
    {
        SPIM_UartStop();
    }
#endif /* (!SPIM_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (SPIM_SCB_MODE_I2C_CONST_CFG)
    SPIM_I2CStop();

#elif (SPIM_SCB_MODE_EZI2C_CONST_CFG)
    SPIM_EzI2CStop();

#elif (SPIM_SCB_MODE_SPI_CONST_CFG)
    SPIM_SpiStop();

#elif (SPIM_SCB_MODE_UART_CONST_CFG)
    SPIM_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SPIM_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void SPIM_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[SPIM_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!SPIM_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!SPIM_CY_SCBIP_V1) */
        
        uint32 hsiomSel[SPIM_SCB_PINS_NUMBER] = 
        {
            SPIM_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            SPIM_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (SPIM_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (SPIM_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < SPIM_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = SPIM_PIN_DM_ALG_HIZ;
        }

        if ((SPIM_SCB_MODE_I2C   == mode) ||
            (SPIM_SCB_MODE_EZI2C == mode))
        {
        #if (SPIM_RX_SCL_MOSI_PIN)
            hsiomSel[SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_PIN_DM_OD_LO;
        #elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPIM_PIN_DM_OD_LO;
        #else
        #endif /* (SPIM_RX_SCL_MOSI_PIN) */
        
        #if (SPIM_TX_SDA_MISO_PIN)
            hsiomSel[SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_PIN_DM_OD_LO;
        #endif /* (SPIM_TX_SDA_MISO_PIN) */
        }
    #if (!SPIM_CY_SCBIP_V1)
        else if (SPIM_SCB_MODE_SPI == mode)
        {
        #if (SPIM_RX_SCL_MOSI_PIN)
            hsiomSel[SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (SPIM_RX_SCL_MOSI_PIN) */
        
        #if (SPIM_TX_SDA_MISO_PIN)
            hsiomSel[SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (SPIM_TX_SDA_MISO_PIN) */
        
        #if (SPIM_SCLK_PIN)
            hsiomSel[SPIM_SCLK_PIN_INDEX] = SPIM_SCLK_HSIOM_SEL_SPI;
        #endif /* (SPIM_SCLK_PIN) */

            if (SPIM_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;
                pinsDm[SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                pinsDm[SPIM_SCLK_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;

            #if (SPIM_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SPIM_SS0_PIN_INDEX] = SPIM_SS0_HSIOM_SEL_SPI;
                pinsDm  [SPIM_SS0_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;
            #endif /* (SPIM_SS0_PIN) */

            #if (SPIM_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= SPIM_TX_SDA_MISO_PIN_MASK;
            #endif /* (SPIM_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                pinsDm[SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;
                pinsDm[SPIM_SCLK_PIN_INDEX] = SPIM_PIN_DM_STRONG;

            #if (SPIM_SS0_PIN)
                hsiomSel [SPIM_SS0_PIN_INDEX] = SPIM_SS0_HSIOM_SEL_SPI;
                pinsDm   [SPIM_SS0_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                pinsInBuf |= SPIM_SS0_PIN_MASK;
            #endif /* (SPIM_SS0_PIN) */

            #if (SPIM_SS1_PIN)
                hsiomSel [SPIM_SS1_PIN_INDEX] = SPIM_SS1_HSIOM_SEL_SPI;
                pinsDm   [SPIM_SS1_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                pinsInBuf |= SPIM_SS1_PIN_MASK;
            #endif /* (SPIM_SS1_PIN) */

            #if (SPIM_SS2_PIN)
                hsiomSel [SPIM_SS2_PIN_INDEX] = SPIM_SS2_HSIOM_SEL_SPI;
                pinsDm   [SPIM_SS2_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                pinsInBuf |= SPIM_SS2_PIN_MASK;
            #endif /* (SPIM_SS2_PIN) */

            #if (SPIM_SS3_PIN)
                hsiomSel [SPIM_SS3_PIN_INDEX] = SPIM_SS3_HSIOM_SEL_SPI;
                pinsDm   [SPIM_SS3_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                pinsInBuf |= SPIM_SS3_PIN_MASK;
            #endif /* (SPIM_SS3_PIN) */

                /* Disable input buffers */
            #if (SPIM_RX_SCL_MOSI_PIN)
                pinsInBuf |= SPIM_RX_SCL_MOSI_PIN_MASK;
            #elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= SPIM_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (SPIM_RX_SCL_MOSI_PIN) */

            #if (SPIM_SCLK_PIN)
                pinsInBuf |= SPIM_SCLK_PIN_MASK;
            #endif /* (SPIM_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (SPIM_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (SPIM_TX_SDA_MISO_PIN)
                hsiomSel[SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_PIN_DM_OD_LO;
            #endif /* (SPIM_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (SPIM_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (SPIM_RX_SCL_MOSI_PIN)
                    hsiomSel[SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [SPIM_RX_SCL_MOSI_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;
                #elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;
                #else
                #endif /* (SPIM_RX_SCL_MOSI_PIN) */
                }

                if (0u != (SPIM_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (SPIM_TX_SDA_MISO_PIN)
                    hsiomSel[SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [SPIM_TX_SDA_MISO_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= SPIM_TX_SDA_MISO_PIN_MASK;
                #endif /* (SPIM_TX_SDA_MISO_PIN) */
                }

            #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
                if (SPIM_UART_MODE_STD == subMode)
                {
                    if (0u != (SPIM_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (SPIM_SCLK_PIN)
                        hsiomSel[SPIM_SCLK_PIN_INDEX] = SPIM_SCLK_HSIOM_SEL_UART;
                        pinsDm  [SPIM_SCLK_PIN_INDEX] = SPIM_PIN_DM_DIG_HIZ;
                    #endif /* (SPIM_SCLK_PIN) */
                    }

                    if (0u != (SPIM_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (SPIM_SS0_PIN)
                        hsiomSel[SPIM_SS0_PIN_INDEX] = SPIM_SS0_HSIOM_SEL_UART;
                        pinsDm  [SPIM_SS0_PIN_INDEX] = SPIM_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= SPIM_SS0_PIN_MASK;
                    #endif /* (SPIM_SS0_PIN) */
                    }
                }
            #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
            }
        }
    #endif /* (!SPIM_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (SPIM_RX_SCL_MOSI_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_RX_SCL_MOSI_HSIOM_REG,
                                       SPIM_RX_SCL_MOSI_HSIOM_MASK,
                                       SPIM_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[SPIM_RX_SCL_MOSI_PIN_INDEX]);

        SPIM_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[SPIM_RX_SCL_MOSI_PIN_INDEX]);

        #if (!SPIM_CY_SCBIP_V1)
            SPIM_SET_INP_DIS(SPIM_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         SPIM_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & SPIM_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!SPIM_CY_SCBIP_V1) */
    
    #elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       SPIM_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       SPIM_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SPIM_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SPIM_SET_INP_DIS(SPIM_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     SPIM_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SPIM_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        SPIM_SET_INCFG_TYPE(SPIM_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        SPIM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        SPIM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        SPIM_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (SPIM_RX_WAKE_SCL_MOSI_PIN) */

    #if (SPIM_TX_SDA_MISO_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_TX_SDA_MISO_HSIOM_REG,
                                       SPIM_TX_SDA_MISO_HSIOM_MASK,
                                       SPIM_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[SPIM_TX_SDA_MISO_PIN_INDEX]);

        SPIM_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[SPIM_TX_SDA_MISO_PIN_INDEX]);

    #if (!SPIM_CY_SCBIP_V1)
        SPIM_SET_INP_DIS(SPIM_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     SPIM_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & SPIM_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!SPIM_CY_SCBIP_V1) */
    #endif /* (SPIM_RX_SCL_MOSI_PIN) */

    #if (SPIM_SCLK_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_SCLK_HSIOM_REG,
                                       SPIM_SCLK_HSIOM_MASK,
                                       SPIM_SCLK_HSIOM_POS,
                                       hsiomSel[SPIM_SCLK_PIN_INDEX]);

        SPIM_spi_sclk_SetDriveMode((uint8) pinsDm[SPIM_SCLK_PIN_INDEX]);

        SPIM_SET_INP_DIS(SPIM_spi_sclk_INP_DIS,
                                     SPIM_spi_sclk_MASK,
                                     (0u != (pinsInBuf & SPIM_SCLK_PIN_MASK)));
    #endif /* (SPIM_SCLK_PIN) */

    #if (SPIM_SS0_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_SS0_HSIOM_REG,
                                       SPIM_SS0_HSIOM_MASK,
                                       SPIM_SS0_HSIOM_POS,
                                       hsiomSel[SPIM_SS0_PIN_INDEX]);

        SPIM_spi_ss0_SetDriveMode((uint8) pinsDm[SPIM_SS0_PIN_INDEX]);

        SPIM_SET_INP_DIS(SPIM_spi_ss0_INP_DIS,
                                     SPIM_spi_ss0_MASK,
                                     (0u != (pinsInBuf & SPIM_SS0_PIN_MASK)));
    #endif /* (SPIM_SS0_PIN) */

    #if (SPIM_SS1_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_SS1_HSIOM_REG,
                                       SPIM_SS1_HSIOM_MASK,
                                       SPIM_SS1_HSIOM_POS,
                                       hsiomSel[SPIM_SS1_PIN_INDEX]);

        SPIM_spi_ss1_SetDriveMode((uint8) pinsDm[SPIM_SS1_PIN_INDEX]);

        SPIM_SET_INP_DIS(SPIM_spi_ss1_INP_DIS,
                                     SPIM_spi_ss1_MASK,
                                     (0u != (pinsInBuf & SPIM_SS1_PIN_MASK)));
    #endif /* (SPIM_SS1_PIN) */

    #if (SPIM_SS2_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_SS2_HSIOM_REG,
                                       SPIM_SS2_HSIOM_MASK,
                                       SPIM_SS2_HSIOM_POS,
                                       hsiomSel[SPIM_SS2_PIN_INDEX]);

        SPIM_spi_ss2_SetDriveMode((uint8) pinsDm[SPIM_SS2_PIN_INDEX]);

        SPIM_SET_INP_DIS(SPIM_spi_ss2_INP_DIS,
                                     SPIM_spi_ss2_MASK,
                                     (0u != (pinsInBuf & SPIM_SS2_PIN_MASK)));
    #endif /* (SPIM_SS2_PIN) */

    #if (SPIM_SS3_PIN)
        SPIM_SET_HSIOM_SEL(SPIM_SS3_HSIOM_REG,
                                       SPIM_SS3_HSIOM_MASK,
                                       SPIM_SS3_HSIOM_POS,
                                       hsiomSel[SPIM_SS3_PIN_INDEX]);

        SPIM_spi_ss3_SetDriveMode((uint8) pinsDm[SPIM_SS3_PIN_INDEX]);

        SPIM_SET_INP_DIS(SPIM_spi_ss3_INP_DIS,
                                     SPIM_spi_ss3_MASK,
                                     (0u != (pinsInBuf & SPIM_SS3_PIN_MASK)));
    #endif /* (SPIM_SS3_PIN) */
    }

#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPIM_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void SPIM_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (SPIM_CTRL_REG & SPIM_CTRL_EC_AM_MODE)) &&
            (0u == (SPIM_I2C_CTRL_REG & SPIM_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            SPIM_CTRL_REG &= ~SPIM_CTRL_EC_AM_MODE;
            SPIM_CTRL_REG |=  SPIM_CTRL_EC_AM_MODE;
        }

        SPIM_I2C_SLAVE_CMD_REG = SPIM_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */


/* [] END OF FILE */
