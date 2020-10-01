/***************************************************************************//**
* \file SPIM_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_SPIM_H)
#define CY_SCB_PINS_SPIM_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define SPIM_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define SPIM_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define SPIM_REMOVE_TX_SDA_MISO_PIN      (1u)
#define SPIM_REMOVE_SCLK_PIN      (1u)
#define SPIM_REMOVE_SS0_PIN      (1u)
#define SPIM_REMOVE_SS1_PIN                 (1u)
#define SPIM_REMOVE_SS2_PIN                 (1u)
#define SPIM_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define SPIM_REMOVE_I2C_PINS                (1u)
#define SPIM_REMOVE_SPI_MASTER_PINS         (0u)
#define SPIM_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define SPIM_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define SPIM_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define SPIM_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define SPIM_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define SPIM_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define SPIM_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define SPIM_REMOVE_SPI_SLAVE_PINS          (1u)
#define SPIM_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define SPIM_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define SPIM_REMOVE_UART_TX_PIN             (1u)
#define SPIM_REMOVE_UART_RX_TX_PIN          (1u)
#define SPIM_REMOVE_UART_RX_PIN             (1u)
#define SPIM_REMOVE_UART_RX_WAKE_PIN        (1u)
#define SPIM_REMOVE_UART_RTS_PIN            (1u)
#define SPIM_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define SPIM_RX_WAKE_SCL_MOSI_PIN (0u == SPIM_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define SPIM_RX_SCL_MOSI_PIN     (0u == SPIM_REMOVE_RX_SCL_MOSI_PIN)
#define SPIM_TX_SDA_MISO_PIN     (0u == SPIM_REMOVE_TX_SDA_MISO_PIN)
#define SPIM_SCLK_PIN     (0u == SPIM_REMOVE_SCLK_PIN)
#define SPIM_SS0_PIN     (0u == SPIM_REMOVE_SS0_PIN)
#define SPIM_SS1_PIN                (0u == SPIM_REMOVE_SS1_PIN)
#define SPIM_SS2_PIN                (0u == SPIM_REMOVE_SS2_PIN)
#define SPIM_SS3_PIN                (0u == SPIM_REMOVE_SS3_PIN)

/* Mode defined pins */
#define SPIM_I2C_PINS               (0u == SPIM_REMOVE_I2C_PINS)
#define SPIM_SPI_MASTER_PINS        (0u == SPIM_REMOVE_SPI_MASTER_PINS)
#define SPIM_SPI_MASTER_SCLK_PIN    (0u == SPIM_REMOVE_SPI_MASTER_SCLK_PIN)
#define SPIM_SPI_MASTER_MOSI_PIN    (0u == SPIM_REMOVE_SPI_MASTER_MOSI_PIN)
#define SPIM_SPI_MASTER_MISO_PIN    (0u == SPIM_REMOVE_SPI_MASTER_MISO_PIN)
#define SPIM_SPI_MASTER_SS0_PIN     (0u == SPIM_REMOVE_SPI_MASTER_SS0_PIN)
#define SPIM_SPI_MASTER_SS1_PIN     (0u == SPIM_REMOVE_SPI_MASTER_SS1_PIN)
#define SPIM_SPI_MASTER_SS2_PIN     (0u == SPIM_REMOVE_SPI_MASTER_SS2_PIN)
#define SPIM_SPI_MASTER_SS3_PIN     (0u == SPIM_REMOVE_SPI_MASTER_SS3_PIN)
#define SPIM_SPI_SLAVE_PINS         (0u == SPIM_REMOVE_SPI_SLAVE_PINS)
#define SPIM_SPI_SLAVE_MOSI_PIN     (0u == SPIM_REMOVE_SPI_SLAVE_MOSI_PIN)
#define SPIM_SPI_SLAVE_MISO_PIN     (0u == SPIM_REMOVE_SPI_SLAVE_MISO_PIN)
#define SPIM_UART_TX_PIN            (0u == SPIM_REMOVE_UART_TX_PIN)
#define SPIM_UART_RX_TX_PIN         (0u == SPIM_REMOVE_UART_RX_TX_PIN)
#define SPIM_UART_RX_PIN            (0u == SPIM_REMOVE_UART_RX_PIN)
#define SPIM_UART_RX_WAKE_PIN       (0u == SPIM_REMOVE_UART_RX_WAKE_PIN)
#define SPIM_UART_RTS_PIN           (0u == SPIM_REMOVE_UART_RTS_PIN)
#define SPIM_UART_CTS_PIN           (0u == SPIM_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (SPIM_RX_WAKE_SCL_MOSI_PIN)
    #include "SPIM_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (SPIM_RX_SCL_MOSI) */

#if (SPIM_RX_SCL_MOSI_PIN)
    #include "SPIM_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (SPIM_RX_SCL_MOSI) */

#if (SPIM_TX_SDA_MISO_PIN)
    #include "SPIM_uart_tx_i2c_sda_spi_miso.h"
#endif /* (SPIM_TX_SDA_MISO) */

#if (SPIM_SCLK_PIN)
    #include "SPIM_spi_sclk.h"
#endif /* (SPIM_SCLK) */

#if (SPIM_SS0_PIN)
    #include "SPIM_spi_ss0.h"
#endif /* (SPIM_SS0_PIN) */

#if (SPIM_SS1_PIN)
    #include "SPIM_spi_ss1.h"
#endif /* (SPIM_SS1_PIN) */

#if (SPIM_SS2_PIN)
    #include "SPIM_spi_ss2.h"
#endif /* (SPIM_SS2_PIN) */

#if (SPIM_SS3_PIN)
    #include "SPIM_spi_ss3.h"
#endif /* (SPIM_SS3_PIN) */

#if (SPIM_I2C_PINS)
    #include "SPIM_scl.h"
    #include "SPIM_sda.h"
#endif /* (SPIM_I2C_PINS) */

#if (SPIM_SPI_MASTER_PINS)
#if (SPIM_SPI_MASTER_SCLK_PIN)
    #include "SPIM_sclk_m.h"
#endif /* (SPIM_SPI_MASTER_SCLK_PIN) */

#if (SPIM_SPI_MASTER_MOSI_PIN)
    #include "SPIM_mosi_m.h"
#endif /* (SPIM_SPI_MASTER_MOSI_PIN) */

#if (SPIM_SPI_MASTER_MISO_PIN)
    #include "SPIM_miso_m.h"
#endif /*(SPIM_SPI_MASTER_MISO_PIN) */
#endif /* (SPIM_SPI_MASTER_PINS) */

#if (SPIM_SPI_SLAVE_PINS)
    #include "SPIM_sclk_s.h"
    #include "SPIM_ss_s.h"

#if (SPIM_SPI_SLAVE_MOSI_PIN)
    #include "SPIM_mosi_s.h"
#endif /* (SPIM_SPI_SLAVE_MOSI_PIN) */

#if (SPIM_SPI_SLAVE_MISO_PIN)
    #include "SPIM_miso_s.h"
#endif /*(SPIM_SPI_SLAVE_MISO_PIN) */
#endif /* (SPIM_SPI_SLAVE_PINS) */

#if (SPIM_SPI_MASTER_SS0_PIN)
    #include "SPIM_ss0_m.h"
#endif /* (SPIM_SPI_MASTER_SS0_PIN) */

#if (SPIM_SPI_MASTER_SS1_PIN)
    #include "SPIM_ss1_m.h"
#endif /* (SPIM_SPI_MASTER_SS1_PIN) */

#if (SPIM_SPI_MASTER_SS2_PIN)
    #include "SPIM_ss2_m.h"
#endif /* (SPIM_SPI_MASTER_SS2_PIN) */

#if (SPIM_SPI_MASTER_SS3_PIN)
    #include "SPIM_ss3_m.h"
#endif /* (SPIM_SPI_MASTER_SS3_PIN) */

#if (SPIM_UART_TX_PIN)
    #include "SPIM_tx.h"
#endif /* (SPIM_UART_TX_PIN) */

#if (SPIM_UART_RX_TX_PIN)
    #include "SPIM_rx_tx.h"
#endif /* (SPIM_UART_RX_TX_PIN) */

#if (SPIM_UART_RX_PIN)
    #include "SPIM_rx.h"
#endif /* (SPIM_UART_RX_PIN) */

#if (SPIM_UART_RX_WAKE_PIN)
    #include "SPIM_rx_wake.h"
#endif /* (SPIM_UART_RX_WAKE_PIN) */

#if (SPIM_UART_RTS_PIN)
    #include "SPIM_rts.h"
#endif /* (SPIM_UART_RTS_PIN) */

#if (SPIM_UART_CTS_PIN)
    #include "SPIM_cts.h"
#endif /* (SPIM_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (SPIM_RX_SCL_MOSI_PIN)
    #define SPIM_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SPIM_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define SPIM_RX_SCL_MOSI_HSIOM_MASK      (SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SPIM_RX_SCL_MOSI_HSIOM_POS       (SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define SPIM_RX_SCL_MOSI_HSIOM_SEL_GPIO  (SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define SPIM_RX_SCL_MOSI_HSIOM_SEL_I2C   (SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define SPIM_RX_SCL_MOSI_HSIOM_SEL_SPI   (SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define SPIM_RX_SCL_MOSI_HSIOM_SEL_UART  (SPIM_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_MASK      (SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_POS       (SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define SPIM_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define SPIM_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SPIM_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) SPIM_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SPIM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (SPIM_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define SPIM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) SPIM_INTCFG_TYPE_MASK << \
                                                                           SPIM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins SPIM_RX_SCL_MOSI_PIN or SPIM_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (SPIM_RX_SCL_MOSI_PIN) */

#if (SPIM_TX_SDA_MISO_PIN)
    #define SPIM_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SPIM_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define SPIM_TX_SDA_MISO_HSIOM_MASK      (SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define SPIM_TX_SDA_MISO_HSIOM_POS       (SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define SPIM_TX_SDA_MISO_HSIOM_SEL_GPIO  (SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define SPIM_TX_SDA_MISO_HSIOM_SEL_I2C   (SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define SPIM_TX_SDA_MISO_HSIOM_SEL_SPI   (SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define SPIM_TX_SDA_MISO_HSIOM_SEL_UART  (SPIM_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (SPIM_TX_SDA_MISO_PIN) */

#if (SPIM_SCLK_PIN)
    #define SPIM_SCLK_HSIOM_REG   (*(reg32 *) SPIM_spi_sclk__0__HSIOM)
    #define SPIM_SCLK_HSIOM_PTR   ( (reg32 *) SPIM_spi_sclk__0__HSIOM)
    
    #define SPIM_SCLK_HSIOM_MASK      (SPIM_spi_sclk__0__HSIOM_MASK)
    #define SPIM_SCLK_HSIOM_POS       (SPIM_spi_sclk__0__HSIOM_SHIFT)
    #define SPIM_SCLK_HSIOM_SEL_GPIO  (SPIM_spi_sclk__0__HSIOM_GPIO)
    #define SPIM_SCLK_HSIOM_SEL_I2C   (SPIM_spi_sclk__0__HSIOM_I2C)
    #define SPIM_SCLK_HSIOM_SEL_SPI   (SPIM_spi_sclk__0__HSIOM_SPI)
    #define SPIM_SCLK_HSIOM_SEL_UART  (SPIM_spi_sclk__0__HSIOM_UART)
#endif /* (SPIM_SCLK_PIN) */

#if (SPIM_SS0_PIN)
    #define SPIM_SS0_HSIOM_REG   (*(reg32 *) SPIM_spi_ss0__0__HSIOM)
    #define SPIM_SS0_HSIOM_PTR   ( (reg32 *) SPIM_spi_ss0__0__HSIOM)
    
    #define SPIM_SS0_HSIOM_MASK      (SPIM_spi_ss0__0__HSIOM_MASK)
    #define SPIM_SS0_HSIOM_POS       (SPIM_spi_ss0__0__HSIOM_SHIFT)
    #define SPIM_SS0_HSIOM_SEL_GPIO  (SPIM_spi_ss0__0__HSIOM_GPIO)
    #define SPIM_SS0_HSIOM_SEL_I2C   (SPIM_spi_ss0__0__HSIOM_I2C)
    #define SPIM_SS0_HSIOM_SEL_SPI   (SPIM_spi_ss0__0__HSIOM_SPI)
#if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
    #define SPIM_SS0_HSIOM_SEL_UART  (SPIM_spi_ss0__0__HSIOM_UART)
#endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
#endif /* (SPIM_SS0_PIN) */

#if (SPIM_SS1_PIN)
    #define SPIM_SS1_HSIOM_REG  (*(reg32 *) SPIM_spi_ss1__0__HSIOM)
    #define SPIM_SS1_HSIOM_PTR  ( (reg32 *) SPIM_spi_ss1__0__HSIOM)
    
    #define SPIM_SS1_HSIOM_MASK     (SPIM_spi_ss1__0__HSIOM_MASK)
    #define SPIM_SS1_HSIOM_POS      (SPIM_spi_ss1__0__HSIOM_SHIFT)
    #define SPIM_SS1_HSIOM_SEL_GPIO (SPIM_spi_ss1__0__HSIOM_GPIO)
    #define SPIM_SS1_HSIOM_SEL_I2C  (SPIM_spi_ss1__0__HSIOM_I2C)
    #define SPIM_SS1_HSIOM_SEL_SPI  (SPIM_spi_ss1__0__HSIOM_SPI)
#endif /* (SPIM_SS1_PIN) */

#if (SPIM_SS2_PIN)
    #define SPIM_SS2_HSIOM_REG     (*(reg32 *) SPIM_spi_ss2__0__HSIOM)
    #define SPIM_SS2_HSIOM_PTR     ( (reg32 *) SPIM_spi_ss2__0__HSIOM)
    
    #define SPIM_SS2_HSIOM_MASK     (SPIM_spi_ss2__0__HSIOM_MASK)
    #define SPIM_SS2_HSIOM_POS      (SPIM_spi_ss2__0__HSIOM_SHIFT)
    #define SPIM_SS2_HSIOM_SEL_GPIO (SPIM_spi_ss2__0__HSIOM_GPIO)
    #define SPIM_SS2_HSIOM_SEL_I2C  (SPIM_spi_ss2__0__HSIOM_I2C)
    #define SPIM_SS2_HSIOM_SEL_SPI  (SPIM_spi_ss2__0__HSIOM_SPI)
#endif /* (SPIM_SS2_PIN) */

#if (SPIM_SS3_PIN)
    #define SPIM_SS3_HSIOM_REG     (*(reg32 *) SPIM_spi_ss3__0__HSIOM)
    #define SPIM_SS3_HSIOM_PTR     ( (reg32 *) SPIM_spi_ss3__0__HSIOM)
    
    #define SPIM_SS3_HSIOM_MASK     (SPIM_spi_ss3__0__HSIOM_MASK)
    #define SPIM_SS3_HSIOM_POS      (SPIM_spi_ss3__0__HSIOM_SHIFT)
    #define SPIM_SS3_HSIOM_SEL_GPIO (SPIM_spi_ss3__0__HSIOM_GPIO)
    #define SPIM_SS3_HSIOM_SEL_I2C  (SPIM_spi_ss3__0__HSIOM_I2C)
    #define SPIM_SS3_HSIOM_SEL_SPI  (SPIM_spi_ss3__0__HSIOM_SPI)
#endif /* (SPIM_SS3_PIN) */

#if (SPIM_I2C_PINS)
    #define SPIM_SCL_HSIOM_REG  (*(reg32 *) SPIM_scl__0__HSIOM)
    #define SPIM_SCL_HSIOM_PTR  ( (reg32 *) SPIM_scl__0__HSIOM)
    
    #define SPIM_SCL_HSIOM_MASK     (SPIM_scl__0__HSIOM_MASK)
    #define SPIM_SCL_HSIOM_POS      (SPIM_scl__0__HSIOM_SHIFT)
    #define SPIM_SCL_HSIOM_SEL_GPIO (SPIM_sda__0__HSIOM_GPIO)
    #define SPIM_SCL_HSIOM_SEL_I2C  (SPIM_sda__0__HSIOM_I2C)
    
    #define SPIM_SDA_HSIOM_REG  (*(reg32 *) SPIM_sda__0__HSIOM)
    #define SPIM_SDA_HSIOM_PTR  ( (reg32 *) SPIM_sda__0__HSIOM)
    
    #define SPIM_SDA_HSIOM_MASK     (SPIM_sda__0__HSIOM_MASK)
    #define SPIM_SDA_HSIOM_POS      (SPIM_sda__0__HSIOM_SHIFT)
    #define SPIM_SDA_HSIOM_SEL_GPIO (SPIM_sda__0__HSIOM_GPIO)
    #define SPIM_SDA_HSIOM_SEL_I2C  (SPIM_sda__0__HSIOM_I2C)
#endif /* (SPIM_I2C_PINS) */

#if (SPIM_SPI_SLAVE_PINS)
    #define SPIM_SCLK_S_HSIOM_REG   (*(reg32 *) SPIM_sclk_s__0__HSIOM)
    #define SPIM_SCLK_S_HSIOM_PTR   ( (reg32 *) SPIM_sclk_s__0__HSIOM)
    
    #define SPIM_SCLK_S_HSIOM_MASK      (SPIM_sclk_s__0__HSIOM_MASK)
    #define SPIM_SCLK_S_HSIOM_POS       (SPIM_sclk_s__0__HSIOM_SHIFT)
    #define SPIM_SCLK_S_HSIOM_SEL_GPIO  (SPIM_sclk_s__0__HSIOM_GPIO)
    #define SPIM_SCLK_S_HSIOM_SEL_SPI   (SPIM_sclk_s__0__HSIOM_SPI)
    
    #define SPIM_SS0_S_HSIOM_REG    (*(reg32 *) SPIM_ss0_s__0__HSIOM)
    #define SPIM_SS0_S_HSIOM_PTR    ( (reg32 *) SPIM_ss0_s__0__HSIOM)
    
    #define SPIM_SS0_S_HSIOM_MASK       (SPIM_ss0_s__0__HSIOM_MASK)
    #define SPIM_SS0_S_HSIOM_POS        (SPIM_ss0_s__0__HSIOM_SHIFT)
    #define SPIM_SS0_S_HSIOM_SEL_GPIO   (SPIM_ss0_s__0__HSIOM_GPIO)  
    #define SPIM_SS0_S_HSIOM_SEL_SPI    (SPIM_ss0_s__0__HSIOM_SPI)
#endif /* (SPIM_SPI_SLAVE_PINS) */

#if (SPIM_SPI_SLAVE_MOSI_PIN)
    #define SPIM_MOSI_S_HSIOM_REG   (*(reg32 *) SPIM_mosi_s__0__HSIOM)
    #define SPIM_MOSI_S_HSIOM_PTR   ( (reg32 *) SPIM_mosi_s__0__HSIOM)
    
    #define SPIM_MOSI_S_HSIOM_MASK      (SPIM_mosi_s__0__HSIOM_MASK)
    #define SPIM_MOSI_S_HSIOM_POS       (SPIM_mosi_s__0__HSIOM_SHIFT)
    #define SPIM_MOSI_S_HSIOM_SEL_GPIO  (SPIM_mosi_s__0__HSIOM_GPIO)
    #define SPIM_MOSI_S_HSIOM_SEL_SPI   (SPIM_mosi_s__0__HSIOM_SPI)
#endif /* (SPIM_SPI_SLAVE_MOSI_PIN) */

#if (SPIM_SPI_SLAVE_MISO_PIN)
    #define SPIM_MISO_S_HSIOM_REG   (*(reg32 *) SPIM_miso_s__0__HSIOM)
    #define SPIM_MISO_S_HSIOM_PTR   ( (reg32 *) SPIM_miso_s__0__HSIOM)
    
    #define SPIM_MISO_S_HSIOM_MASK      (SPIM_miso_s__0__HSIOM_MASK)
    #define SPIM_MISO_S_HSIOM_POS       (SPIM_miso_s__0__HSIOM_SHIFT)
    #define SPIM_MISO_S_HSIOM_SEL_GPIO  (SPIM_miso_s__0__HSIOM_GPIO)
    #define SPIM_MISO_S_HSIOM_SEL_SPI   (SPIM_miso_s__0__HSIOM_SPI)
#endif /* (SPIM_SPI_SLAVE_MISO_PIN) */

#if (SPIM_SPI_MASTER_MISO_PIN)
    #define SPIM_MISO_M_HSIOM_REG   (*(reg32 *) SPIM_miso_m__0__HSIOM)
    #define SPIM_MISO_M_HSIOM_PTR   ( (reg32 *) SPIM_miso_m__0__HSIOM)
    
    #define SPIM_MISO_M_HSIOM_MASK      (SPIM_miso_m__0__HSIOM_MASK)
    #define SPIM_MISO_M_HSIOM_POS       (SPIM_miso_m__0__HSIOM_SHIFT)
    #define SPIM_MISO_M_HSIOM_SEL_GPIO  (SPIM_miso_m__0__HSIOM_GPIO)
    #define SPIM_MISO_M_HSIOM_SEL_SPI   (SPIM_miso_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_MISO_PIN) */

#if (SPIM_SPI_MASTER_MOSI_PIN)
    #define SPIM_MOSI_M_HSIOM_REG   (*(reg32 *) SPIM_mosi_m__0__HSIOM)
    #define SPIM_MOSI_M_HSIOM_PTR   ( (reg32 *) SPIM_mosi_m__0__HSIOM)
    
    #define SPIM_MOSI_M_HSIOM_MASK      (SPIM_mosi_m__0__HSIOM_MASK)
    #define SPIM_MOSI_M_HSIOM_POS       (SPIM_mosi_m__0__HSIOM_SHIFT)
    #define SPIM_MOSI_M_HSIOM_SEL_GPIO  (SPIM_mosi_m__0__HSIOM_GPIO)
    #define SPIM_MOSI_M_HSIOM_SEL_SPI   (SPIM_mosi_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_MOSI_PIN) */

#if (SPIM_SPI_MASTER_SCLK_PIN)
    #define SPIM_SCLK_M_HSIOM_REG   (*(reg32 *) SPIM_sclk_m__0__HSIOM)
    #define SPIM_SCLK_M_HSIOM_PTR   ( (reg32 *) SPIM_sclk_m__0__HSIOM)
    
    #define SPIM_SCLK_M_HSIOM_MASK      (SPIM_sclk_m__0__HSIOM_MASK)
    #define SPIM_SCLK_M_HSIOM_POS       (SPIM_sclk_m__0__HSIOM_SHIFT)
    #define SPIM_SCLK_M_HSIOM_SEL_GPIO  (SPIM_sclk_m__0__HSIOM_GPIO)
    #define SPIM_SCLK_M_HSIOM_SEL_SPI   (SPIM_sclk_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_SCLK_PIN) */

#if (SPIM_SPI_MASTER_SS0_PIN)
    #define SPIM_SS0_M_HSIOM_REG    (*(reg32 *) SPIM_ss0_m__0__HSIOM)
    #define SPIM_SS0_M_HSIOM_PTR    ( (reg32 *) SPIM_ss0_m__0__HSIOM)
    
    #define SPIM_SS0_M_HSIOM_MASK       (SPIM_ss0_m__0__HSIOM_MASK)
    #define SPIM_SS0_M_HSIOM_POS        (SPIM_ss0_m__0__HSIOM_SHIFT)
    #define SPIM_SS0_M_HSIOM_SEL_GPIO   (SPIM_ss0_m__0__HSIOM_GPIO)
    #define SPIM_SS0_M_HSIOM_SEL_SPI    (SPIM_ss0_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_SS0_PIN) */

#if (SPIM_SPI_MASTER_SS1_PIN)
    #define SPIM_SS1_M_HSIOM_REG    (*(reg32 *) SPIM_ss1_m__0__HSIOM)
    #define SPIM_SS1_M_HSIOM_PTR    ( (reg32 *) SPIM_ss1_m__0__HSIOM)
    
    #define SPIM_SS1_M_HSIOM_MASK       (SPIM_ss1_m__0__HSIOM_MASK)
    #define SPIM_SS1_M_HSIOM_POS        (SPIM_ss1_m__0__HSIOM_SHIFT)
    #define SPIM_SS1_M_HSIOM_SEL_GPIO   (SPIM_ss1_m__0__HSIOM_GPIO)
    #define SPIM_SS1_M_HSIOM_SEL_SPI    (SPIM_ss1_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_SS1_PIN) */

#if (SPIM_SPI_MASTER_SS2_PIN)
    #define SPIM_SS2_M_HSIOM_REG    (*(reg32 *) SPIM_ss2_m__0__HSIOM)
    #define SPIM_SS2_M_HSIOM_PTR    ( (reg32 *) SPIM_ss2_m__0__HSIOM)
    
    #define SPIM_SS2_M_HSIOM_MASK       (SPIM_ss2_m__0__HSIOM_MASK)
    #define SPIM_SS2_M_HSIOM_POS        (SPIM_ss2_m__0__HSIOM_SHIFT)
    #define SPIM_SS2_M_HSIOM_SEL_GPIO   (SPIM_ss2_m__0__HSIOM_GPIO)
    #define SPIM_SS2_M_HSIOM_SEL_SPI    (SPIM_ss2_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_SS2_PIN) */

#if (SPIM_SPI_MASTER_SS3_PIN)
    #define SPIM_SS3_M_HSIOM_REG    (*(reg32 *) SPIM_ss3_m__0__HSIOM)
    #define SPIM_SS3_M_HSIOM_PTR    ( (reg32 *) SPIM_ss3_m__0__HSIOM)
    
    #define SPIM_SS3_M_HSIOM_MASK      (SPIM_ss3_m__0__HSIOM_MASK)
    #define SPIM_SS3_M_HSIOM_POS       (SPIM_ss3_m__0__HSIOM_SHIFT)
    #define SPIM_SS3_M_HSIOM_SEL_GPIO  (SPIM_ss3_m__0__HSIOM_GPIO)
    #define SPIM_SS3_M_HSIOM_SEL_SPI   (SPIM_ss3_m__0__HSIOM_SPI)
#endif /* (SPIM_SPI_MASTER_SS3_PIN) */

#if (SPIM_UART_RX_PIN)
    #define SPIM_RX_HSIOM_REG   (*(reg32 *) SPIM_rx__0__HSIOM)
    #define SPIM_RX_HSIOM_PTR   ( (reg32 *) SPIM_rx__0__HSIOM)
    
    #define SPIM_RX_HSIOM_MASK      (SPIM_rx__0__HSIOM_MASK)
    #define SPIM_RX_HSIOM_POS       (SPIM_rx__0__HSIOM_SHIFT)
    #define SPIM_RX_HSIOM_SEL_GPIO  (SPIM_rx__0__HSIOM_GPIO)
    #define SPIM_RX_HSIOM_SEL_UART  (SPIM_rx__0__HSIOM_UART)
#endif /* (SPIM_UART_RX_PIN) */

#if (SPIM_UART_RX_WAKE_PIN)
    #define SPIM_RX_WAKE_HSIOM_REG   (*(reg32 *) SPIM_rx_wake__0__HSIOM)
    #define SPIM_RX_WAKE_HSIOM_PTR   ( (reg32 *) SPIM_rx_wake__0__HSIOM)
    
    #define SPIM_RX_WAKE_HSIOM_MASK      (SPIM_rx_wake__0__HSIOM_MASK)
    #define SPIM_RX_WAKE_HSIOM_POS       (SPIM_rx_wake__0__HSIOM_SHIFT)
    #define SPIM_RX_WAKE_HSIOM_SEL_GPIO  (SPIM_rx_wake__0__HSIOM_GPIO)
    #define SPIM_RX_WAKE_HSIOM_SEL_UART  (SPIM_rx_wake__0__HSIOM_UART)
#endif /* (SPIM_UART_WAKE_RX_PIN) */

#if (SPIM_UART_CTS_PIN)
    #define SPIM_CTS_HSIOM_REG   (*(reg32 *) SPIM_cts__0__HSIOM)
    #define SPIM_CTS_HSIOM_PTR   ( (reg32 *) SPIM_cts__0__HSIOM)
    
    #define SPIM_CTS_HSIOM_MASK      (SPIM_cts__0__HSIOM_MASK)
    #define SPIM_CTS_HSIOM_POS       (SPIM_cts__0__HSIOM_SHIFT)
    #define SPIM_CTS_HSIOM_SEL_GPIO  (SPIM_cts__0__HSIOM_GPIO)
    #define SPIM_CTS_HSIOM_SEL_UART  (SPIM_cts__0__HSIOM_UART)
#endif /* (SPIM_UART_CTS_PIN) */

#if (SPIM_UART_TX_PIN)
    #define SPIM_TX_HSIOM_REG   (*(reg32 *) SPIM_tx__0__HSIOM)
    #define SPIM_TX_HSIOM_PTR   ( (reg32 *) SPIM_tx__0__HSIOM)
    
    #define SPIM_TX_HSIOM_MASK      (SPIM_tx__0__HSIOM_MASK)
    #define SPIM_TX_HSIOM_POS       (SPIM_tx__0__HSIOM_SHIFT)
    #define SPIM_TX_HSIOM_SEL_GPIO  (SPIM_tx__0__HSIOM_GPIO)
    #define SPIM_TX_HSIOM_SEL_UART  (SPIM_tx__0__HSIOM_UART)
#endif /* (SPIM_UART_TX_PIN) */

#if (SPIM_UART_RX_TX_PIN)
    #define SPIM_RX_TX_HSIOM_REG   (*(reg32 *) SPIM_rx_tx__0__HSIOM)
    #define SPIM_RX_TX_HSIOM_PTR   ( (reg32 *) SPIM_rx_tx__0__HSIOM)
    
    #define SPIM_RX_TX_HSIOM_MASK      (SPIM_rx_tx__0__HSIOM_MASK)
    #define SPIM_RX_TX_HSIOM_POS       (SPIM_rx_tx__0__HSIOM_SHIFT)
    #define SPIM_RX_TX_HSIOM_SEL_GPIO  (SPIM_rx_tx__0__HSIOM_GPIO)
    #define SPIM_RX_TX_HSIOM_SEL_UART  (SPIM_rx_tx__0__HSIOM_UART)
#endif /* (SPIM_UART_RX_TX_PIN) */

#if (SPIM_UART_RTS_PIN)
    #define SPIM_RTS_HSIOM_REG      (*(reg32 *) SPIM_rts__0__HSIOM)
    #define SPIM_RTS_HSIOM_PTR      ( (reg32 *) SPIM_rts__0__HSIOM)
    
    #define SPIM_RTS_HSIOM_MASK     (SPIM_rts__0__HSIOM_MASK)
    #define SPIM_RTS_HSIOM_POS      (SPIM_rts__0__HSIOM_SHIFT)    
    #define SPIM_RTS_HSIOM_SEL_GPIO (SPIM_rts__0__HSIOM_GPIO)
    #define SPIM_RTS_HSIOM_SEL_UART (SPIM_rts__0__HSIOM_UART)    
#endif /* (SPIM_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define SPIM_HSIOM_DEF_SEL      (0x00u)
#define SPIM_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for SPIM_CY_SCBIP_V0 
* and SPIM_CY_SCBIP_V1. It is not recommended to use them for 
* SPIM_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define SPIM_HSIOM_UART_SEL     (0x09u)
#define SPIM_HSIOM_I2C_SEL      (0x0Eu)
#define SPIM_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define SPIM_RX_SCL_MOSI_PIN_INDEX       (0u)
#define SPIM_TX_SDA_MISO_PIN_INDEX       (1u)
#define SPIM_SCLK_PIN_INDEX       (2u)
#define SPIM_SS0_PIN_INDEX       (3u)
#define SPIM_SS1_PIN_INDEX                  (4u)
#define SPIM_SS2_PIN_INDEX                  (5u)
#define SPIM_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define SPIM_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define SPIM_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << SPIM_RX_SCL_MOSI_PIN_INDEX)
#define SPIM_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << SPIM_TX_SDA_MISO_PIN_INDEX)
#define SPIM_SCLK_PIN_MASK     ((uint32) 0x01u << SPIM_SCLK_PIN_INDEX)
#define SPIM_SS0_PIN_MASK     ((uint32) 0x01u << SPIM_SS0_PIN_INDEX)
#define SPIM_SS1_PIN_MASK                ((uint32) 0x01u << SPIM_SS1_PIN_INDEX)
#define SPIM_SS2_PIN_MASK                ((uint32) 0x01u << SPIM_SS2_PIN_INDEX)
#define SPIM_SS3_PIN_MASK                ((uint32) 0x01u << SPIM_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define SPIM_INTCFG_TYPE_MASK           (0x03u)
#define SPIM_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define SPIM_PIN_DM_ALG_HIZ  (0u)
#define SPIM_PIN_DM_DIG_HIZ  (1u)
#define SPIM_PIN_DM_OD_LO    (4u)
#define SPIM_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define SPIM_DM_MASK    (0x7u)
#define SPIM_DM_SIZE    (3u)
#define SPIM_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) SPIM_DM_MASK << (SPIM_DM_SIZE * (pos)))) >> \
                                                              (SPIM_DM_SIZE * (pos)) )

#if (SPIM_TX_SDA_MISO_PIN)
    #define SPIM_CHECK_TX_SDA_MISO_PIN_USED \
                (SPIM_PIN_DM_ALG_HIZ != \
                    SPIM_GET_P4_PIN_DM(SPIM_uart_tx_i2c_sda_spi_miso_PC, \
                                                   SPIM_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (SPIM_TX_SDA_MISO_PIN) */

#if (SPIM_SS0_PIN)
    #define SPIM_CHECK_SS0_PIN_USED \
                (SPIM_PIN_DM_ALG_HIZ != \
                    SPIM_GET_P4_PIN_DM(SPIM_spi_ss0_PC, \
                                                   SPIM_spi_ss0_SHIFT))
#endif /* (SPIM_SS0_PIN) */

/* Set bits-mask in register */
#define SPIM_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define SPIM_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define SPIM_SET_HSIOM_SEL(reg, mask, pos, sel) SPIM_SET_REGISTER_BITS(reg, mask, pos, sel)
#define SPIM_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        SPIM_SET_REGISTER_BITS(reg, mask, pos, intType)
#define SPIM_SET_INP_DIS(reg, mask, val) SPIM_SET_REGISTER_BIT(reg, mask, val)

/* SPIM_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  SPIM_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (SPIM_CY_SCBIP_V0)
#if (SPIM_I2C_PINS)
    #define SPIM_SET_I2C_SCL_DR(val) SPIM_scl_Write(val)

    #define SPIM_SET_I2C_SCL_HSIOM_SEL(sel) \
                          SPIM_SET_HSIOM_SEL(SPIM_SCL_HSIOM_REG,  \
                                                         SPIM_SCL_HSIOM_MASK, \
                                                         SPIM_SCL_HSIOM_POS,  \
                                                         (sel))
    #define SPIM_WAIT_SCL_SET_HIGH  (0u == SPIM_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
    #define SPIM_SET_I2C_SCL_DR(val) \
                            SPIM_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define SPIM_SET_I2C_SCL_HSIOM_SEL(sel) \
                    SPIM_SET_HSIOM_SEL(SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   SPIM_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   SPIM_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define SPIM_WAIT_SCL_SET_HIGH  (0u == SPIM_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (SPIM_RX_SCL_MOSI_PIN)
    #define SPIM_SET_I2C_SCL_DR(val) \
                            SPIM_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define SPIM_SET_I2C_SCL_HSIOM_SEL(sel) \
                            SPIM_SET_HSIOM_SEL(SPIM_RX_SCL_MOSI_HSIOM_REG,  \
                                                           SPIM_RX_SCL_MOSI_HSIOM_MASK, \
                                                           SPIM_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define SPIM_WAIT_SCL_SET_HIGH  (0u == SPIM_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define SPIM_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define SPIM_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define SPIM_WAIT_SCL_SET_HIGH  (0u)
#endif /* (SPIM_I2C_PINS) */

/* SCB I2C: sda signal */
#if (SPIM_I2C_PINS)
    #define SPIM_WAIT_SDA_SET_HIGH  (0u == SPIM_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (SPIM_TX_SDA_MISO_PIN)
    #define SPIM_WAIT_SDA_SET_HIGH  (0u == SPIM_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define SPIM_WAIT_SDA_SET_HIGH  (0u)
#endif /* (SPIM_MOSI_SCL_RX_PIN) */
#endif /* (SPIM_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (SPIM_RX_SCL_MOSI_PIN)
    #define SPIM_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (SPIM_RX_WAKE_SCL_MOSI_PIN)
    #define SPIM_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) SPIM_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(SPIM_UART_RX_WAKE_PIN)
    #define SPIM_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) SPIM_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (SPIM_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define SPIM_REMOVE_MOSI_SCL_RX_WAKE_PIN    SPIM_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define SPIM_REMOVE_MOSI_SCL_RX_PIN         SPIM_REMOVE_RX_SCL_MOSI_PIN
#define SPIM_REMOVE_MISO_SDA_TX_PIN         SPIM_REMOVE_TX_SDA_MISO_PIN
#ifndef SPIM_REMOVE_SCLK_PIN
#define SPIM_REMOVE_SCLK_PIN                SPIM_REMOVE_SCLK_PIN
#endif /* SPIM_REMOVE_SCLK_PIN */
#ifndef SPIM_REMOVE_SS0_PIN
#define SPIM_REMOVE_SS0_PIN                 SPIM_REMOVE_SS0_PIN
#endif /* SPIM_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define SPIM_MOSI_SCL_RX_WAKE_PIN   SPIM_RX_WAKE_SCL_MOSI_PIN
#define SPIM_MOSI_SCL_RX_PIN        SPIM_RX_SCL_MOSI_PIN
#define SPIM_MISO_SDA_TX_PIN        SPIM_TX_SDA_MISO_PIN
#ifndef SPIM_SCLK_PIN
#define SPIM_SCLK_PIN               SPIM_SCLK_PIN
#endif /* SPIM_SCLK_PIN */
#ifndef SPIM_SS0_PIN
#define SPIM_SS0_PIN                SPIM_SS0_PIN
#endif /* SPIM_SS0_PIN */

#if (SPIM_MOSI_SCL_RX_WAKE_PIN)
    #define SPIM_MOSI_SCL_RX_WAKE_HSIOM_REG     SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIM_MOSI_SCL_RX_WAKE_HSIOM_PTR     SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIM_MOSI_SCL_RX_WAKE_HSIOM_MASK    SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIM_MOSI_SCL_RX_WAKE_HSIOM_POS     SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SPIM_MOSI_SCL_RX_WAKE_INTCFG_REG    SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIM_MOSI_SCL_RX_WAKE_INTCFG_PTR    SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SPIM_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIM_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  SPIM_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (SPIM_RX_WAKE_SCL_MOSI_PIN) */

#if (SPIM_MOSI_SCL_RX_PIN)
    #define SPIM_MOSI_SCL_RX_HSIOM_REG      SPIM_RX_SCL_MOSI_HSIOM_REG
    #define SPIM_MOSI_SCL_RX_HSIOM_PTR      SPIM_RX_SCL_MOSI_HSIOM_PTR
    #define SPIM_MOSI_SCL_RX_HSIOM_MASK     SPIM_RX_SCL_MOSI_HSIOM_MASK
    #define SPIM_MOSI_SCL_RX_HSIOM_POS      SPIM_RX_SCL_MOSI_HSIOM_POS
#endif /* (SPIM_MOSI_SCL_RX_PIN) */

#if (SPIM_MISO_SDA_TX_PIN)
    #define SPIM_MISO_SDA_TX_HSIOM_REG      SPIM_TX_SDA_MISO_HSIOM_REG
    #define SPIM_MISO_SDA_TX_HSIOM_PTR      SPIM_TX_SDA_MISO_HSIOM_REG
    #define SPIM_MISO_SDA_TX_HSIOM_MASK     SPIM_TX_SDA_MISO_HSIOM_REG
    #define SPIM_MISO_SDA_TX_HSIOM_POS      SPIM_TX_SDA_MISO_HSIOM_REG
#endif /* (SPIM_MISO_SDA_TX_PIN_PIN) */

#if (SPIM_SCLK_PIN)
    #ifndef SPIM_SCLK_HSIOM_REG
    #define SPIM_SCLK_HSIOM_REG     SPIM_SCLK_HSIOM_REG
    #define SPIM_SCLK_HSIOM_PTR     SPIM_SCLK_HSIOM_PTR
    #define SPIM_SCLK_HSIOM_MASK    SPIM_SCLK_HSIOM_MASK
    #define SPIM_SCLK_HSIOM_POS     SPIM_SCLK_HSIOM_POS
    #endif /* SPIM_SCLK_HSIOM_REG */
#endif /* (SPIM_SCLK_PIN) */

#if (SPIM_SS0_PIN)
    #ifndef SPIM_SS0_HSIOM_REG
    #define SPIM_SS0_HSIOM_REG      SPIM_SS0_HSIOM_REG
    #define SPIM_SS0_HSIOM_PTR      SPIM_SS0_HSIOM_PTR
    #define SPIM_SS0_HSIOM_MASK     SPIM_SS0_HSIOM_MASK
    #define SPIM_SS0_HSIOM_POS      SPIM_SS0_HSIOM_POS
    #endif /* SPIM_SS0_HSIOM_REG */
#endif /* (SPIM_SS0_PIN) */

#define SPIM_MOSI_SCL_RX_WAKE_PIN_INDEX SPIM_RX_WAKE_SCL_MOSI_PIN_INDEX
#define SPIM_MOSI_SCL_RX_PIN_INDEX      SPIM_RX_SCL_MOSI_PIN_INDEX
#define SPIM_MISO_SDA_TX_PIN_INDEX      SPIM_TX_SDA_MISO_PIN_INDEX
#ifndef SPIM_SCLK_PIN_INDEX
#define SPIM_SCLK_PIN_INDEX             SPIM_SCLK_PIN_INDEX
#endif /* SPIM_SCLK_PIN_INDEX */
#ifndef SPIM_SS0_PIN_INDEX
#define SPIM_SS0_PIN_INDEX              SPIM_SS0_PIN_INDEX
#endif /* SPIM_SS0_PIN_INDEX */

#define SPIM_MOSI_SCL_RX_WAKE_PIN_MASK SPIM_RX_WAKE_SCL_MOSI_PIN_MASK
#define SPIM_MOSI_SCL_RX_PIN_MASK      SPIM_RX_SCL_MOSI_PIN_MASK
#define SPIM_MISO_SDA_TX_PIN_MASK      SPIM_TX_SDA_MISO_PIN_MASK
#ifndef SPIM_SCLK_PIN_MASK
#define SPIM_SCLK_PIN_MASK             SPIM_SCLK_PIN_MASK
#endif /* SPIM_SCLK_PIN_MASK */
#ifndef SPIM_SS0_PIN_MASK
#define SPIM_SS0_PIN_MASK              SPIM_SS0_PIN_MASK
#endif /* SPIM_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_SPIM_H) */


/* [] END OF FILE */
