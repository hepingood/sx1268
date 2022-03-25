/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_sx1268.h
 * @brief     driver sx1268 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-01-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/01/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef _DRIVER_SX1268_H_
#define _DRIVER_SX1268_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sx1268_driver sx1268 driver function
 * @brief    sx1268 driver modules
 * @{
 */

/**
 * @addtogroup sx1268_command_driver
 * @{
 */

/**
 * @brief sx1268 bool enumeration definition
 */
typedef enum
{
    SX1268_BOOL_FALSE = 0x00,        /**< disable function */
    SX1268_BOOL_TRUE  = 0x01,        /**< enable function */
} sx1268_bool_t;

/**
 * @brief sx1268 start mode enumeration definition
 */
typedef enum
{
    SX1268_START_MODE_COLD = 0x00,        /**< cold start mode */
    SX1268_START_MODE_WARM = 0x01,        /**< warm start mode */
} sx1268_start_mode_t;

/**
 * @brief sx1268 clock source enumeration definition
 */
typedef enum
{
    SX1268_CLOCK_SOURCE_RC_13M     = 0x00,        /**< rc 13MHz */
    SX1268_CLOCK_SOURCE_XTAL_32MHZ = 0x01,        /**< xtal 32MHz */
} sx1268_clock_source_t;

/**
 * @brief sx1268 regulator mode enumeration definition
 */
typedef enum
{
    SX1268_REGULATOR_MODE_ONLY_LDO  = 0x00,        /**< only ldo used for all modes */
    SX1268_REGULATOR_MODE_DC_DC_LDO = 0x01,        /**< dc_dc + ldo used for stby_xosc, fs, rx and rx modes */
} sx1268_regulator_mode_t;

/**
 * @brief sx1268 calibration enumeration definition
 */
typedef enum
{
    SX1268_CALIBRATION_RC64K      = (1 << 0),        /**< rc64k calibration */
    SX1268_CALIBRATION_RC13M      = (1 << 1),        /**< rc13M calibration */
    SX1268_CALIBRATION_PLL        = (1 << 2),        /**< pll calibration */
    SX1268_CALIBRATION_ADC_PULSE  = (1 << 3),        /**< adc pulse calibration */
    SX1268_CALIBRATION_ADC_BULK_N = (1 << 4),        /**< adc bulk n calibration */
    SX1268_CALIBRATION_ADC_BULK_P = (1 << 5),        /**< adc bulk p calibration */
    SX1268_CALIBRATION_IMAGE      = (1 << 6),        /**< image calibration */
} sx1268_calibration_t;

/**
 * @brief sx1268 irq enumeration definition
 */
typedef enum
{
    SX1268_IRQ_TX_DONE           = (1 << 0),        /**< packet transmission completed */
    SX1268_IRQ_RX_DONE           = (1 << 1),        /**< packet received */
    SX1268_IRQ_PREAMBLE_DETECTED = (1 << 2),        /**< preamble detected */
    SX1268_IRQ_SYNC_WORD_VALID   = (1 << 3),        /**< valid sync word detected */
    SX1268_IRQ_HEADER_VALID      = (1 << 4),        /**< valid header */
    SX1268_IRQ_HEADER_ERR        = (1 << 5),        /**< header error */
    SX1268_IRQ_CRC_ERR           = (1 << 6),        /**< crc error */
    SX1268_IRQ_CAD_DONE          = (1 << 7),        /**< cad done */
    SX1268_IRQ_CAD_DETECTED      = (1 << 8),        /**< cad detected */
    SX1268_IRQ_TIMEOUT           = (1 << 9),        /**< timeout */
} sx1268_irq_t;

/**
 * @brief sx1268 rx tx fallback mode enumeration definition
 */
typedef enum
{
    SX1268_RX_TX_FALLBACK_MODE_FS         = 0x40,        /**< the radio goes into fs mode after tx or rx */
    SX1268_RX_TX_FALLBACK_MODE_STDBY_XOSC = 0x30,        /**< the radio goes into stdby_xosc mode after tx or rx */
    SX1268_RX_TX_FALLBACK_MODE_STDBY_RC   = 0x20,        /**< the radio goes into stdby_rc mode after tx or rx */
} sx1268_rx_tx_fallback_mode_t;

/**
 * @brief sx1268 tcxo voltage enumeration definition
 */
typedef enum
{
    SX1268_TCXO_VOLTAGE_1P6V = 0x00,        /**< dio3 outputs 1.6 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_1P7V = 0x01,        /**< dio3 outputs 1.7 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_1P8V = 0x02,        /**< dio3 outputs 1.8 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_2P2V = 0x03,        /**< dio3 outputs 2.2 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_2P4V = 0x04,        /**< dio3 outputs 2.4 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_2P7V = 0x05,        /**< dio3 outputs 2.7 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_3P0V = 0x06,        /**< dio3 outputs 3.0 V to supply the tcxo */
    SX1268_TCXO_VOLTAGE_3P3V = 0x07,        /**< dio3 outputs 3.3 V to supply the tcxo */
} sx1268_tcxo_voltage_t;

/**
 * @brief sx1268 packet type enumeration definition
 */
typedef enum
{
    SX1268_PACKET_TYPE_GFSK = 0x00,        /**< gfsk mode */
    SX1268_PACKET_TYPE_LORA = 0x01,        /**< lora mode */
} sx1268_packet_type_t;

/**
 * @brief sx1268 ramp time enumeration definition
 */
typedef enum
{
    SX1268_RAMP_TIME_10US   = 0x00,        /**< 10us */
    SX1268_RAMP_TIME_20US   = 0x01,        /**< 20us */
    SX1268_RAMP_TIME_40US   = 0x02,        /**< 40us */
    SX1268_RAMP_TIME_80US   = 0x03,        /**< 80us */
    SX1268_RAMP_TIME_200US  = 0x04,        /**< 200us */
    SX1268_RAMP_TIME_800US  = 0x05,        /**< 800us */
    SX1268_RAMP_TIME_1700US = 0x06,        /**< 1700us */
    SX1268_RAMP_TIME_3400US = 0x07,        /**< 3400us */
} sx1268_ramp_time_t;

/**
 * @brief sx1268 gfsk pulse shape enumeration definition
 */
typedef enum
{
    SX1268_GFSK_PULSE_SHAPE_NO_FILTER       = 0x00,        /**< no filter applied */
    SX1268_GFSK_PULSE_SHAPE_GAUSSIAN_BT_0P3 = 0x08,        /**< gaussian bt 0.3 */
    SX1268_GFSK_PULSE_SHAPE_GAUSSIAN_BT_0P5 = 0x09,        /**< gaussian bt 0.5 */
    SX1268_GFSK_PULSE_SHAPE_GAUSSIAN_BT_0P7 = 0x0A,        /**< gaussian bt 0.7 */
    SX1268_GFSK_PULSE_SHAPE_GAUSSIAN_BT_1   = 0x0B,        /**< gaussian bt 1 */
} sx1268_gfsk_pulse_shape_t;

/**
 * @brief sx1268 gfsk bandwidth enumeration definition
 */
typedef enum
{
    SX1268_GFSK_BANDWIDTH_4P8_KHZ   = 0x1F,        /**< 4.8 kHz */
    SX1268_GFSK_BANDWIDTH_5P8_KHZ   = 0x17,        /**< 5.8 kHz */
    SX1268_GFSK_BANDWIDTH_7P3_KHZ   = 0x0F,        /**< 7.3 kHz */
    SX1268_GFSK_BANDWIDTH_9P7_KHZ   = 0x1E,        /**< 9.7 kHz */
    SX1268_GFSK_BANDWIDTH_11P7_KHZ  = 0x16,        /**< 11.7 kHz */
    SX1268_GFSK_BANDWIDTH_14P6_KHZ  = 0x0E,        /**< 14.6 kHz */
    SX1268_GFSK_BANDWIDTH_19P5_KHZ  = 0x1D,        /**< 19.5 kHz */
    SX1268_GFSK_BANDWIDTH_23P4_KHZ  = 0x15,        /**< 23.4 kHz */
    SX1268_GFSK_BANDWIDTH_29P3_KHZ  = 0x0D,        /**< 29.3 kHz */
    SX1268_GFSK_BANDWIDTH_39_KHZ    = 0x1C,        /**< 39 kHz */
    SX1268_GFSK_BANDWIDTH_46P9_KHZ  = 0x14,        /**< 46.9 kHz */
    SX1268_GFSK_BANDWIDTH_58P6_KHZ  = 0x0C,        /**< 58.6 kHz */
    SX1268_GFSK_BANDWIDTH_78P2_KHZ  = 0x1B,        /**< 78.2 kHz */
    SX1268_GFSK_BANDWIDTH_93P8_KHZ  = 0x13,        /**< 93.8 kHz */
    SX1268_GFSK_BANDWIDTH_117P3_KHZ = 0x0B,        /**< 117.3 kHz */
    SX1268_GFSK_BANDWIDTH_156P2_KHZ = 0x1A,        /**< 156.2 kHz */
    SX1268_GFSK_BANDWIDTH_187P2_KHZ = 0x12,        /**< 187.2 kHz */
    SX1268_GFSK_BANDWIDTH_232P3_KHZ = 0x0A,        /**< 232.3 kHz */
    SX1268_GFSK_BANDWIDTH_312_KHZ   = 0x19,        /**< 312 kHz */
    SX1268_GFSK_BANDWIDTH_373P6_KHZ = 0x11,        /**< 373.6 kHz */
    SX1268_GFSK_BANDWIDTH_467_KHZ   = 0x09,        /**< 467 kHz */
} sx1268_gfsk_bandwidth_t;

/**
 * @brief sx1268 lora spreading factor enumeration definition
 */
typedef enum
{
    SX1268_LORA_SF_5  = 0x05,        /**< spreading factor 5 */
    SX1268_LORA_SF_6  = 0x06,        /**< spreading factor 6 */
    SX1268_LORA_SF_7  = 0x07,        /**< spreading factor 7 */
    SX1268_LORA_SF_8  = 0x08,        /**< spreading factor 8 */
    SX1268_LORA_SF_9  = 0x09,        /**< spreading factor 9 */
    SX1268_LORA_SF_10 = 0x0A,        /**< spreading factor 10 */
    SX1268_LORA_SF_11 = 0x0B,        /**< spreading factor 11 */
    SX1268_LORA_SF_12 = 0x0C,        /**< spreading factor 12 */
} sx1268_lora_sf_t;

/**
 * @brief sx1268 lora bandwidth enumeration definition
 */
typedef enum
{
    SX1268_LORA_BANDWIDTH_7P81_KHZ  = 0x00,        /**< 7.81 kHz */
    SX1268_LORA_BANDWIDTH_10P42_KHZ = 0x08,        /**< 10.42 kHz */
    SX1268_LORA_BANDWIDTH_15P63_KHZ = 0x01,        /**< 15.63 kHz */
    SX1268_LORA_BANDWIDTH_20P83_KHZ = 0x09,        /**< 20.83 kHz */
    SX1268_LORA_BANDWIDTH_31P25_KHZ = 0x02,        /**< 31.25 kHz */
    SX1268_LORA_BANDWIDTH_41P67_KHZ = 0x0A,        /**< 41.67 kHz */
    SX1268_LORA_BANDWIDTH_62P50_KHZ = 0x03,        /**< 62.50 kHz */
    SX1268_LORA_BANDWIDTH_125_KHZ   = 0x04,        /**< 125 kHz */
    SX1268_LORA_BANDWIDTH_250_KHZ   = 0x05,        /**< 250 kHz */
    SX1268_LORA_BANDWIDTH_500_KHZ   = 0x06,        /**< 500 kHz */
} sx1268_lora_bandwidth_t;

/**
 * @brief sx1268 lora coding rate enumeration definition
 */
typedef enum
{
    SX1268_LORA_CR_4_5 = 0x01,        /**< cr 4/5 */
    SX1268_LORA_CR_4_6 = 0x01,        /**< cr 4/6 */
    SX1268_LORA_CR_4_7 = 0x01,        /**< cr 4/7 */
    SX1268_LORA_CR_4_8 = 0x01,        /**< cr 4/8 */
} sx1268_lora_cr_t;

/**
 * @brief sx1268 gfsk preamble detector length enumeration definition
 */
typedef enum
{
    SX1268_GFSK_PREAMBLE_DETECTOR_LENGTH_OFF     = 0x00,        /**< preamble detector length off */
    SX1268_GFSK_PREAMBLE_DETECTOR_LENGTH_8_BITS  = 0x04,        /**< preamble detector length 8 bits */
    SX1268_GFSK_PREAMBLE_DETECTOR_LENGTH_16_BITS = 0x05,        /**< preamble detector length 16 bits */
    SX1268_GFSK_PREAMBLE_DETECTOR_LENGTH_24_BITS = 0x06,        /**< preamble detector length 24 bits */
    SX1268_GFSK_PREAMBLE_DETECTOR_LENGTH_32_BITS = 0x07,        /**< preamble detector length 32 bits */
} sx1268_gfsk_preamble_detector_length_t;

/**
 * @brief sx1268 gfsk addr filter enumeration definition
 */
typedef enum
{
    SX1268_GFSK_ADDR_FILTER_DISABLE                       = 0x00,        /**< address filtering disable */
    SX1268_GFSK_ADDR_FILTER_ACTIVATED_NODE_ADDR           = 0x01,        /**< address filtering activated on node address */
    SX1268_GFSK_ADDR_FILTER_ACTIVATED_NODE_BROADCAST_ADDR = 0x02,        /**< address filtering activated on node and broadcast addresses */
} sx1268_gfsk_addr_filter_t;

/**
 * @brief sx1268 gfsk packet type enumeration definition
 */
typedef enum
{
    SX1268_GFSK_PACKET_TYPE_KNOWN_LENGTH  = 0x00,        /**< the packet length is known on both sides, 
                                                              the size of the payload is not added to the packet */
    SX1268_GFSK_PACKET_TYPE_VARIABLE_SIZE = 0x01,        /**< the packet is on variable size, the first byte of the payload will be the
                                                              size of the packet*/
} sx1268_gfsk_packet_type_t;

/**
 * @brief sx1268 gfsk crc type enumeration definition
 */
typedef enum
{
    SX1268_GFSK_CRC_TYPE_OFF        = 0x00,        /**< no crc */
    SX1268_GFSK_CRC_TYPE_1_BYTE     = 0x00,        /**< crc computed on 1 byte */
    SX1268_GFSK_CRC_TYPE_2_BYTE     = 0x00,        /**< crc computed on 2 byte */
    SX1268_GFSK_CRC_TYPE_1_BYTE_INV = 0x00,        /**< crc computed on 1 byte and inverted */
    SX1268_GFSK_CRC_TYPE_2_BYTE_INV = 0x00,        /**< crc computed on 2 byte and inverted */
} sx1268_gfsk_crc_type_t;

/**
 * @brief sx1268 lora header enumeration definition
 */
typedef enum
{
    SX1268_LORA_HEADER_EXPLICIT = 0x00,        /**< explicit header */
    SX1268_LORA_HEADER_IMPLICIT = 0x01,        /**< implicit header */
} sx1268_lora_header_t;

/**
 * @brief sx1268 lora crc type enumeration definition
 */
typedef enum
{
    SX1268_LORA_CRC_TYPE_OFF = 0x00,        /**< crc off */
    SX1268_LORA_CRC_TYPE_ON  = 0x01,        /**< crc on */
} sx1268_lora_crc_type_t;

/**
 * @brief sx1268 lora cad symbol num enumeration definition
 */
typedef enum
{
    SX1268_LORA_CAD_SYMBOL_NUM_1  = 0x00,        /**< 1 symbol */
    SX1268_LORA_CAD_SYMBOL_NUM_2  = 0x01,        /**< 2 symbol */
    SX1268_LORA_CAD_SYMBOL_NUM_4  = 0x02,        /**< 4 symbol */
    SX1268_LORA_CAD_SYMBOL_NUM_8  = 0x03,        /**< 8 symbol */
    SX1268_LORA_CAD_SYMBOL_NUM_16 = 0x04,        /**< 16 symbol */
} sx1268_lora_cad_symbol_num_t;

/**
 * @brief sx1268 lora cad exit mode enumeration definition
 */
typedef enum
{
    SX1268_LORA_CAD_EXIT_MODE_ONLY = 0x00,        /**< once done and whatever the activity on the channel,
                                                       the chip goes back to STBY_RC mode */
    SX1268_LORA_CAD_EXIT_MODE_RX   = 0x01,        /**< the chip performs a cad operation and if an activity is detected, it stays in rx until
                                                       a packet is detected or the timer reaches the timeout defined by
                                                       cad timeout * 15.625 us */
} sx1268_lora_cad_exit_mode_t;

/**
 * @brief sx1268 fsk rx status enumeration definition
 */
typedef enum
{
    SX1268_FSK_RX_STATUS_PREAMBLE_ERR = (1 << 7),        /**< preamble err */
    SX1268_FSK_RX_STATUS_SYNC_ERR     = (1 << 6),        /**< sync err */
    SX1268_FSK_RX_STATUS_ADRS_ERR     = (1 << 5),        /**< adrs err */
    SX1268_FSK_RX_STATUS_CRC_ERR      = (1 << 4),        /**< crc err*/
    SX1268_FSK_RX_STATUS_LENGTH_ERR   = (1 << 3),        /**< length err */
    SX1268_FSK_RX_STATUS_ABORT_ERR    = (1 << 2),        /**< abort err */
    SX1268_FSK_RX_STATUS_PKT_RECEIVED = (1 << 1),        /**< pkt received */
    SX1268_FSK_RX_STATUS_PKT_SENT     = (1 << 0),        /**< pkt sent */
} sx1268_fsk_rx_status_t;

/**
 * @brief sx1268 op error enumeration definition
 */
typedef enum
{
    SX1268_OP_ERROR_PA_RAMP_ERR     = (1 << 8),        /**< pa ramping failed */
    SX1268_OP_ERROR_PLL_LOCK_ERR    = (1 << 6),        /**< pll failed to lock */
    SX1268_OP_ERROR_XOSC_START_ERR  = (1 << 5),        /**< xosc failed to start */
    SX1268_OP_ERROR_IMG_CALIB_ERR   = (1 << 4),        /**< img calibration failed */
    SX1268_OP_ERROR_ADC_CALIB_ERR   = (1 << 3),        /**< adc calibration failed */
    SX1268_OP_ERROR_PLL_CALIB_ERR   = (1 << 2),        /**< pll calibration failed */
    SX1268_OP_ERROR_RC13M_CALIB_ERR = (1 << 1),        /**< rc13M calibration failed */
    SX1268_OP_ERROR_RC64K_CALIB_ERR = (1 << 0),        /**< rc64k calibration failed */
} sx1268_op_error_t;

/**
 * @brief sx1268 handle structure definition
 */
typedef struct sx1268_handle_s
{
    uint8_t (*reset_gpio_init)(void);                                     /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                                   /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t value);                           /**< point to a reset_gpio_write function address */
    uint8_t (*busy_gpio_init)(void);                                      /**< point to a busy_gpio_init function address */
    uint8_t (*busy_gpio_deinit)(void);                                    /**< point to a busy_gpio_deinit function address */
    uint8_t (*busy_gpio_read)(uint8_t *value);                            /**< point to a busy_gpio_read function address */
    uint8_t (*spi_init)(void);                                            /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                          /**< point to a spi_deinit function address */
    uint8_t (*spi_write_read)(uint8_t *in_buf, uint32_t in_len,
                              uint8_t *out_buf, uint32_t out_len);        /**< point to a spi_write_read function address */
    void (*delay_ms)(uint32_t ms);                                        /**< point to a delay_ms function address */
    uint16_t (*debug_print)(char *fmt, ...);                              /**< point to a debug_print function address */
    uint8_t (*receive_callback)(uint16_t type,
                                uint8_t *buf, uint16_t len);              /**< point to a receive_callback function address */
    uint8_t inited;                                                       /**< inited flag */
    uint8_t tx_done;                                                      /**< tx done flag */
    uint8_t cad_done;                                                     /**< cad done flag */
    uint8_t cad_detected;                                                 /**< cad detected flag */
    uint8_t crc_error;                                                    /**< crc error flag */
    uint8_t timeout;                                                      /**< timeout flag */
    uint8_t buf[384];                                                     /**< inner buffer */
    uint8_t receive_buf[256];                                             /**< receive buffer */
} sx1268_handle_t;

/**
 * @brief sx1268 information structure definition
 */
typedef struct sx1268_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} sx1268_info_t;

/**
 * @}
 */

/**
 * @defgroup sx1268_link_driver sx1268 link driver function
 * @brief    sx1268 link driver modules
 * @ingroup  sx1268_driver
 * @{
 */

/**
 * @brief     initialize sx1268_handle_t structure
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] STRUCTURE is sx1268_handle_t
 * @note      none
 */
#define DRIVER_SX1268_LINK_INIT(HANDLE, STRUCTURE)                memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a spi_init function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_SPI_INIT(HANDLE, FUC)                  (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a spi_deinit function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_SPI_DEINIT(HANDLE, FUC)                (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write_read function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a spi_write_read function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_SPI_WRITE_READ(HANDLE, FUC)            (HANDLE)->spi_write_read = FUC

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_RESET_GPIO_INIT(HANDLE, FUC)           (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)         (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_RESET_GPIO_WRITE(HANDLE, FUC)          (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link busy_gpio_init function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a busy_gpio_init function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_BUSY_GPIO_INIT(HANDLE, FUC)            (HANDLE)->busy_gpio_init = FUC

/**
 * @brief     link busy_gpio_deinit function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a busy_gpio_deinit function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_BUSY_GPIO_DEINIT(HANDLE, FUC)          (HANDLE)->busy_gpio_deinit = FUC

/**
 * @brief     link busy_gpio_read function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a busy_gpio_read function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_BUSY_GPIO_READ(HANDLE, FUC)            (HANDLE)->busy_gpio_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_DELAY_MS(HANDLE, FUC)                  (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_DEBUG_PRINT(HANDLE, FUC)               (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE points to a sx1268 handle structure
 * @param[in] FUC points to a receive_callback function address
 * @note      none
 */
#define DRIVER_SX1268_LINK_RECEIVE_CALLBACK(HANDLE, FUC)          (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup sx1268_command_driver sx1268 command driver function
 * @brief    sx1268 command driver modules
 * @ingroup  sx1268_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a sx1268 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sx1268_info(sx1268_info_t *info);

/**
 * @brief     irq handler
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sx1268_irq_handler(sx1268_handle_t *handle);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset gpio initialization failed
 *            - 5 busy gpio initialization failed
 *            - 6 reset chip failed
 * @note      none
 */
uint8_t sx1268_init(sx1268_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 *            - 5 power down failed
 *            - 6 busy gpio deinit failed
 *            - 7 reset gpio deinit failed
 * @note      none
 */
uint8_t sx1268_deinit(sx1268_handle_t *handle);

/**
 * @brief     sent the lora data
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] standby_src is the clock source
 * @param[in] preamble_length is the preamble length
 * @param[in] header_type is the header type
 * @param[in] crc_type is the crc type
 * @param[in] invert_iq_enable is a bool value
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @param[in] us is the timeout
 * @return    status code
 *            - 0 success
 *            - 1 sent failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 *            - 5 sent timeout
 *            - 6 irq timeout
 *            - 7 unknown result
 * @note      none
 */
uint8_t sx1268_lora_sent(sx1268_handle_t *handle, sx1268_clock_source_t standby_src,
                         uint16_t preamble_length, sx1268_lora_header_t header_type,
                         sx1268_lora_crc_type_t crc_type, sx1268_bool_t invert_iq_enable,
                         uint8_t *buf, uint16_t len, uint32_t us);

/**
 * @brief      run the cad
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *enable points to a enable buffer
 * @return     status code
 *             - 0 success
 *             - 1 lora cad failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 *             - 5 cad timeout
 * @note       none
 */
uint8_t sx1268_lora_cad(sx1268_handle_t *handle, sx1268_bool_t *enable);

/**
 * @brief     enter to the single receive mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] us is the rx timeout
 * @return    status code
 *            - 0 success
 *            - 1 lora single receive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_single_receive(sx1268_handle_t *handle, double us);

/**
 * @brief     enter to the continuous receive mode
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 lora continuous receive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_continuous_receive(sx1268_handle_t *handle);

/**
 * @brief     write the register
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] reg is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write register failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_write_register(sx1268_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      read the register
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  reg is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read register failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_read_register(sx1268_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief     write the buffer
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] offset is the buffer offset
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write buffer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_write_buffer(sx1268_handle_t *handle, uint8_t offset, uint8_t *buf, uint16_t len);

/**
 * @brief      read the buffer
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  offset is the buffer offset
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read buffer failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_read_buffer(sx1268_handle_t *handle, uint8_t offset, uint8_t *buf, uint16_t len);

/**
 * @brief      check the packet error
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *enable points to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_check_packet_error(sx1268_handle_t *handle, sx1268_bool_t *enable);

/**
 * @brief     enter to the sleep mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] mode is the start mode
 * @param[in] rtc_wake_up_enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_sleep(sx1268_handle_t *handle, sx1268_start_mode_t mode, sx1268_bool_t rtc_wake_up_enable);

/**
 * @brief     enter to the standby mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] src is the clock source
 * @return    status code
 *            - 0 success
 *            - 1 set standby failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_standby(sx1268_handle_t *handle, sx1268_clock_source_t src);

/**
 * @brief     enter to the frequency synthesis mode
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set frequency synthesis failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_frequency_synthesis(sx1268_handle_t *handle);

/**
 * @brief     enter to the tx mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] timeout is the tx timeout
 * @return    status code
 *            - 0 success
 *            - 1 set tx failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      0x000000 means timeout disable, tx single mode
 */
uint8_t sx1268_set_tx(sx1268_handle_t *handle, uint32_t timeout);

/**
 * @brief     enter to the rx mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] timeout is the rx timeout
 * @return    status code
 *            - 0 success
 *            - 1 set rx failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      0x000000 means timeout disable, rx single mode
 *            0xFFFFFF means rx continuous mode
 */
uint8_t sx1268_set_rx(sx1268_handle_t *handle, uint32_t timeout);

/**
 * @brief      convert the timeout to the register raw data
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  us is the timeout
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_timeout_convert_to_register(sx1268_handle_t *handle, double us, uint32_t *reg);

/**
 * @brief      convert the register raw data to the timeout
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *us points to a us buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_timeout_convert_to_data(sx1268_handle_t *handle, uint32_t reg, double *us);

/**
 * @brief     stop timer on preamble
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set stop timer on preamble failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_stop_timer_on_preamble(sx1268_handle_t *handle, sx1268_bool_t enable);

/**
 * @brief     set the rx duty cycle
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] rx_period is the rx period
 * @param[in] sleep_period is the sleep period
 * @return    status code
 *            - 0 success
 *            - 1 set rx duty cycle failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      t_preamble + t_header <= 2 * rx_period + sleep_period
 */
uint8_t sx1268_set_rx_duty_cycle(sx1268_handle_t *handle, uint32_t rx_period, uint32_t sleep_period);

/**
 * @brief     run the cad
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set cad failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_cad(sx1268_handle_t *handle);

/**
 * @brief     enter to the tx continuous wave mode
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set tx continuous wave failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_tx_continuous_wave(sx1268_handle_t *handle);

/**
 * @brief     enter to the tx infinite preamble mode
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set tx infinite preamble failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_tx_infinite_preamble(sx1268_handle_t *handle);

/**
 * @brief     set the regulator_mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] mode is the regulator mode
 * @return    status code
 *            - 0 success
 *            - 1 set regulator mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_regulator_mode(sx1268_handle_t *handle, sx1268_regulator_mode_t mode);

/**
 * @brief     set the calibration settings
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] settings is the calibration param
 * @return    status code
 *            - 0 success
 *            - 1 set calibration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_calibration(sx1268_handle_t *handle, uint8_t settings);

/**
 * @brief     set the calibration image frequence
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] freq1 is the image frequence 1
 * @param[in] freq2 is the image frequence 2
 * @return    status code
 *            - 0 success
 *            - 1 set calibration image failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_calibration_image(sx1268_handle_t *handle, uint8_t freq1, uint8_t freq2);

/**
 * @brief     set the pa config
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] pa_duty_cycle is the pa duty cycle
 * @param[in] hp_max is the max power
 * @return    status code
 *            - 0 success
 *            - 1 set the pa config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_pa_config(sx1268_handle_t *handle, uint8_t pa_duty_cycle, uint8_t hp_max);

/**
 * @brief     set the rx tx fallback mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] mode is the rx tx fallback mode
 * @return    status code
 *            - 0 success
 *            - 1 set rx tx fallback mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_rx_tx_fallback_mode(sx1268_handle_t *handle, sx1268_rx_tx_fallback_mode_t mode);

/**
 * @brief     set the dio irq params
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] irq_mask is the irq mask
 * @param[in] dio1_mask is the dio1 mask
 * @param[in] dio2_mask is the dio2 mask
 * @param[in] dio3_mask is the dio3 mask
 * @return    status code
 *            - 0 success
 *            - 1 set dio irq params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_dio_irq_params(sx1268_handle_t *handle, uint16_t irq_mask, uint16_t dio1_mask,
                                  uint16_t dio2_mask, uint16_t dio3_mask);

/**
 * @brief      get the irq status
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get irq status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_irq_status(sx1268_handle_t *handle, uint16_t *status);

/**
 * @brief     clear the irq status
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] clear_irq_param is the irq mask
 * @return    status code
 *            - 0 success
 *            - 1 clear irq status failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_clear_irq_status(sx1268_handle_t *handle, uint16_t clear_irq_param);

/**
 * @brief     set dio2 as rf switch ctrl
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dio2 as rf switch ctrl failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_dio2_as_rf_switch_ctrl(sx1268_handle_t *handle, sx1268_bool_t enable);

/**
 * @brief     set dio3 as tcxo ctrl
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] voltage is the tcxo voltage
 * @param[in] delay is the tcxo ctrl delay
 * @return    status code
 *            - 0 success
 *            - 1 set dio3 as tcxo ctrl failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_dio3_as_tcxo_ctrl(sx1268_handle_t *handle, sx1268_tcxo_voltage_t voltage, uint32_t delay);

/**
 * @brief      convert the frequency to the register raw data
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  freq is the frequency
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_frequency_convert_to_register(sx1268_handle_t *handle, uint32_t freq, uint32_t *reg);

/**
 * @brief      convert the register raw data to the frequency
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *freq points to a frequency buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_frequency_convert_to_data(sx1268_handle_t *handle, uint32_t reg, uint32_t *freq);

/**
 * @brief     set the rf frequency
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] reg is the rf frequency register data
 * @return    status code
 *            - 0 success
 *            - 1 set rf frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_rf_frequency(sx1268_handle_t *handle, uint32_t reg);

/**
 * @brief     set the packet type
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] type is the packet type
 * @return    status code
 *            - 0 success
 *            - 1 set packet type failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_packet_type(sx1268_handle_t *handle, sx1268_packet_type_t type);

/**
 * @brief      get the packet type
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *type points to a packet type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get packet type failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_packet_type(sx1268_handle_t *handle, sx1268_packet_type_t *type);

/**
 * @brief     set the tx params
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] dbm is the rf power 
 * @param[in] time is the ramp time
 * @return    status code
 *            - 0 success
 *            - 1 set tx params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_tx_params(sx1268_handle_t *handle, int8_t dbm, sx1268_ramp_time_t time);

/**
 * @brief     set the modulation params in GFSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] br is the bit rate
 * @param[in] shape is the pulse shape
 * @param[in] bw is the bandwidth
 * @param[in] fdev is the frequency deviation
 * @return    status code
 *            - 0 success
 *            - 1 set gfsk modulation params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_gfsk_modulation_params(sx1268_handle_t *handle, uint32_t br, sx1268_gfsk_pulse_shape_t shape, 
                                          sx1268_gfsk_bandwidth_t bw, uint32_t fdev);

/**
 * @brief      convert the bit rate to the register raw data
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  br is the bit rate
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_gfsk_bit_rate_convert_to_register(sx1268_handle_t *handle, uint32_t br, uint32_t *reg);

/**
 * @brief      convert the register raw data to the bit rate
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *br points to a bit rate buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_gfsk_bit_rate_convert_to_data(sx1268_handle_t *handle, uint32_t reg, uint32_t *br);

/**
 * @brief      convert the frequency deviation to the register raw data
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  freq is the frequency deviation
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_gfsk_frequency_deviation_convert_to_register(sx1268_handle_t *handle, uint32_t freq, uint32_t *reg);

/**
 * @brief      convert the register raw data to the frequency deviation
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *freq points to a frequency deviation buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_gfsk_frequency_deviation_convert_to_data(sx1268_handle_t *handle, uint32_t reg, uint32_t *freq);

/**
 * @brief     set the modulation params in LoRa mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] sf is the spreading factor
 * @param[in] bw is the bandwidth
 * @param[in] cr is coding rate
 * @param[in] low_data_rate_optimize_enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lora modulation params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_lora_modulation_params(sx1268_handle_t *handle, sx1268_lora_sf_t sf, sx1268_lora_bandwidth_t bw, 
                                          sx1268_lora_cr_t cr, sx1268_bool_t low_data_rate_optimize_enable);

/**
 * @brief     set the packet params in GFSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] preamble_length is the preamble length
 * @param[in] detector_length is the preamble detector length
 * @param[in] sync_word_length is the sync word length
 * @param[in] filter is the address filter
 * @param[in] packet_type is the packet type
 * @param[in] payload_length is the length of the payload
 * @param[in] crc_type is the crc type
 * @param[in] whitening_enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set gfsk packet params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 *            - 5 sync word length is over 0x40
 * @note      none
 */
uint8_t sx1268_set_gfsk_packet_params(sx1268_handle_t *handle, uint16_t preamble_length,
                                      sx1268_gfsk_preamble_detector_length_t detector_length,
                                      uint8_t sync_word_length, sx1268_gfsk_addr_filter_t filter,
                                      sx1268_gfsk_packet_type_t packet_type, uint8_t payload_length,
                                      sx1268_gfsk_crc_type_t crc_type, sx1268_bool_t whitening_enable);

/**
 * @brief     set the packet params in LoRa mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] preamble_length is the preamble length
 * @param[in] header_type is the header type
 * @param[in] payload_length is the length of payload
 * @param[in] crc_type is the crc type
 * @param[in] invert_iq_enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lora packet params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_lora_packet_params(sx1268_handle_t *handle, uint16_t preamble_length,
                                      sx1268_lora_header_t header_type, uint8_t payload_length,
                                      sx1268_lora_crc_type_t crc_type, sx1268_bool_t invert_iq_enable);

/**
 * @brief     set the cad params
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] num is the cad symbol number
 * @param[in] cad_det_peak is the cad detection peak
 * @param[in] cad_det_min is the min cad detection peak 
 * @param[in] mode is the cad exit mode
 * @param[in] timeout is the cad timeout
 * @return    status code
 *            - 0 success
 *            - 1 set cad params failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_cad_params(sx1268_handle_t *handle, sx1268_lora_cad_symbol_num_t num,
                              uint8_t cad_det_peak, uint8_t cad_det_min, sx1268_lora_cad_exit_mode_t mode,
                              uint32_t timeout);

/**
 * @brief     set the buffer base address
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] tx_base_addr is the tx base address
 * @param[in] rx_base_addr is the rx base address
 * @return    status code
 *            - 0 success
 *            - 1 set buffer base address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_buffer_base_address(sx1268_handle_t *handle, uint8_t tx_base_addr, uint8_t rx_base_addr);

/**
 * @brief     set the lora symbol number timeout
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] symb_num is the symbol number
 * @return    status code
 *            - 0 success
 *            - 1 set lora symb num timeout failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_lora_symb_num_timeout(sx1268_handle_t *handle, uint8_t symb_num);

/**
 * @brief      get the status
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_status(sx1268_handle_t *handle, uint8_t *status);

/**
 * @brief      get the rx buffer status
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *payload_length_rx points to a rx payload length buffer
 * @param[out] *rx_start_buffer_pointer points to a rx start pointer buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rx buffer status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_rx_buffer_status(sx1268_handle_t *handle, uint8_t *payload_length_rx, uint8_t *rx_start_buffer_pointer);

/**
 * @brief      get the packet status in GFSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *rx_status points to a rx status buffer
 * @param[out] *rssi_sync_raw points to a rssi sync raw buffer
 * @param[out] *rssi_avg_raw points to a rssi avg raw buffer
 * @param[out] *rssi_sync points to a rssi sync buffer
 * @param[out] *rssi_avg points to a rssi avg buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gfsk packet status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_gfsk_packet_status(sx1268_handle_t *handle, uint8_t *rx_status, uint8_t *rssi_sync_raw,
                                      uint8_t *rssi_avg_raw, float *rssi_sync, float *rssi_avg);

/**
 * @brief      get the packet status in LoRa mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *rssi_pkt_raw points to a rssi packet raw buffer
 * @param[out] *snr_pkt_raw points to a snr packet raw buffer
 * @param[out] *signal_rssi_pkt_raw points to a signal rssi packet raw buffer
 * @param[out] *rssi_pkt points to a rssi packet buffer
 * @param[out] *snr_pkt points to a snr packet buffer
 * @param[out] *signal_rssi_pkt points to a signal rssi packet buffer
 * @return     status code
 *             - 0 success
 *             - 1 get lora packet status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_lora_packet_status(sx1268_handle_t *handle, uint8_t *rssi_pkt_raw, uint8_t *snr_pkt_raw,
                                      uint8_t *signal_rssi_pkt_raw, float *rssi_pkt, float *snr_pkt, float *signal_rssi_pkt);

/**
 * @brief      get the instantaneous rssi
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *rssi_inst_raw points to a rssi instantaneous raw buffer
 * @param[out] *rssi_inst points to a rssi instantaneous buffer
 * @return     status code
 *             - 0 success
 *             - 1 get instantaneous rssi failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_instantaneous_rssi(sx1268_handle_t *handle, uint8_t *rssi_inst_raw, float *rssi_inst);

/**
 * @brief      get the stats
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *pkt_received points to a packet received counter buffer
 * @param[out] *pkt_crc_error points to a packet crc error buffer
 * @param[out] *pkt_length_header_error points to a packet length header error buffer
 * @return     status code
 *             - 0 success
 *             - 1 get stats failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_stats(sx1268_handle_t *handle, uint16_t *pkt_received, uint16_t *pkt_crc_error, uint16_t *pkt_length_header_error);

/**
 * @brief     reset the stats
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] pkt_received is the received packet counter mask
 * @param[in] pkt_crc_error is the packet crc error mask
 * @param[in] pkt_length_header_error is the packet length header error mask
 * @return    status code
 *            - 0 success
 *            - 1 reset stats failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_reset_stats(sx1268_handle_t *handle, uint16_t pkt_received, uint16_t pkt_crc_error, uint16_t pkt_length_header_error);

/**
 * @brief      get the device errors
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *op_error points to a op error buffer
 * @return     status code
 *             - 0 success
 *             - 1 get device errors failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_device_errors(sx1268_handle_t *handle, uint16_t *op_error);

/**
 * @brief     clear the device errors
 * @param[in] *handle points to a sx1268 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear device errors failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_clear_device_errors(sx1268_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup sx1268_register_driver sx1268 register driver function
 * @brief    sx1268 register driver modules
 * @ingroup  sx1268_driver
 * @{
 */

/**
 * @brief     set the whitening initial value in FSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] value is the set value
 * @return    status code
 *            - 0 success
 *            - 1 set fsk whitening initial value failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_fsk_whitening_initial_value(sx1268_handle_t *handle, uint16_t value);

/**
 * @brief      get the whitening initial value in FSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *value points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fsk whitening initial value failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_fsk_whitening_initial_value(sx1268_handle_t *handle, uint16_t *value);

/**
 * @brief     set the crc initical value in FSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] value is the set value
 * @return    status code
 *            - 0 success
 *            - 1 set fsk crc initical value failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_fsk_crc_initical_value(sx1268_handle_t *handle, uint16_t value);

/**
 * @brief      get the crc initical value in FSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *value points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fsk crc initical value failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_fsk_crc_initical_value(sx1268_handle_t *handle, uint16_t *value);

/**
 * @brief     set the crc polynomial value in FSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] value is the set value
 * @return    status code
 *            - 0 success
 *            - 1 set fsk crc polynomial value failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_fsk_crc_polynomial_value(sx1268_handle_t *handle, uint16_t value);

/**
 * @brief      get the crc polynomial value in FSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *value points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fsk crc polynomial value failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_fsk_crc_polynomial_value(sx1268_handle_t *handle, uint16_t *value);

/**
 * @brief     set the sync word in FSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] *sync_word points to sync word buffer
 * @return    status code
 *            - 0 success
 *            - 1 set fsk sync word failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_fsk_sync_word(sx1268_handle_t *handle, uint8_t sync_word[8]);

/**
 * @brief      get the sync word in FSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *sync_word points to sync word buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fsk sync word failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_fsk_sync_word(sx1268_handle_t *handle, uint8_t sync_word[8]);

/**
 * @brief     set the node address in FSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] addr is the node address
 * @return    status code
 *            - 0 success
 *            - 1 set fsk node address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_fsk_node_address(sx1268_handle_t *handle, uint8_t addr);

/**
 * @brief      get the node address in FSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *addr points to a node address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fsk node address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_fsk_node_address(sx1268_handle_t *handle, uint8_t *addr);

/**
 * @brief     set the broadcast address in FSK mode
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] addr is the broadcast address
 * @return    status code
 *            - 0 success
 *            - 1 set fsk broadcast address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_fsk_broadcast_address(sx1268_handle_t *handle, uint8_t addr);

/**
 * @brief      get the broadcast address in FSK mode
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *addr points to a broadcast address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fsk broadcast address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_fsk_broadcast_address(sx1268_handle_t *handle, uint8_t *addr);

/**
 * @brief     set the iq polarity
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] setup is the settings
 * @return    status code
 *            - 0 success
 *            - 1 set iq polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_iq_polarity(sx1268_handle_t *handle, uint8_t setup);

/**
 * @brief      get the iq polarity
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *setup points to a settings buffer
 * @return     status code
 *             - 0 success
 *             - 1 get iq polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_iq_polarity(sx1268_handle_t *handle, uint8_t *setup);

/**
 * @brief     set the lora sync word
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] sync_word is the sync word
 * @return    status code
 *            - 0 success
 *            - 1 set lora sync word failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_lora_sync_word(sx1268_handle_t *handle, uint16_t sync_word);

/**
 * @brief      get the lora sync word
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *sync_word points to a sync word buffer
 * @return     status code
 *             - 0 success
 *             - 1 get lora sync word failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_lora_sync_word(sx1268_handle_t *handle, uint16_t *sync_word);

/**
 * @brief      get the random number
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *rand points to a random number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get random number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_random_number(sx1268_handle_t *handle, uint32_t *rand);

/**
 * @brief     set the tx modulation
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] modulation is the tx modulation
 * @return    status code
 *            - 0 success
 *            - 1 set tx modulation failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_tx_modulation(sx1268_handle_t *handle, uint8_t modulation);

/**
 * @brief      get the tx modulation
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *modulation points to a tx modulation buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tx modulation failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_tx_modulation(sx1268_handle_t *handle, uint8_t *modulation);

/**
 * @brief     set the rx gain
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] gain is the rx gain
 * @return    status code
 *            - 0 success
 *            - 1 set rx gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_rx_gain(sx1268_handle_t *handle, uint8_t gain);

/**
 * @brief      get the rx gain
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *gain points to a rx gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rx gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_rx_gain(sx1268_handle_t *handle, uint8_t *gain);

/**
 * @brief     set the tx clamp config
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] config is the tx clamp config
 * @return    status code
 *            - 0 success
 *            - 1 set tx clamp config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_tx_clamp_config(sx1268_handle_t *handle, uint8_t config);

/**
 * @brief      get the tx clamp config
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *config points to a tx clamp config buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tx clamp config failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_tx_clamp_config(sx1268_handle_t *handle, uint8_t *config);

/**
 * @brief     set the ocp
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] ocp is the over current protection level
 * @return    status code
 *            - 0 success
 *            - 1 set ocp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_ocp(sx1268_handle_t *handle, uint8_t ocp);

/**
 * @brief      get the ocp
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *ocp points to a over current protection level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get ocp failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_ocp(sx1268_handle_t *handle, uint8_t *ocp);

/**
 * @brief     set the rtc control
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] control is the rtc control
 * @return    status code
 *            - 0 success
 *            - 1 set rtc control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_rtc_control(sx1268_handle_t *handle, uint8_t control);

/**
 * @brief      get the rtc control
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *control points to a rtc control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rtc control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_rtc_control(sx1268_handle_t *handle, uint8_t *control);

/**
 * @brief     set the xta trim
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] trim is the xta trim
 * @return    status code
 *            - 0 success
 *            - 1 set xta trim failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_xta_trim(sx1268_handle_t *handle, uint8_t trim);

/**
 * @brief      get the xta trim
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *trim points to a xta trim buffer
 * @return     status code
 *             - 0 success
 *             - 1 get xta trim failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_xta_trim(sx1268_handle_t *handle, uint8_t *trim);

/**
 * @brief     set the xtb trim
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] trim is the xtb trim
 * @return    status code
 *            - 0 success
 *            - 1 set xtb trim failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_xtb_trim(sx1268_handle_t *handle, uint8_t trim);

/**
 * @brief      get the xtb trim
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *trim points to a xtb trim buffer
 * @return     status code
 *             - 0 success
 *             - 1 get xtb trim failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_xtb_trim(sx1268_handle_t *handle, uint8_t *trim);

/**
 * @brief     set the dio3 output
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] control is the dio3 output control
 * @return    status code
 *            - 0 success
 *            - 1 set dio3 output control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_dio3_output_control(sx1268_handle_t *handle, uint8_t control);

/**
 * @brief      get the dio3 output
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *control points to a dio3 output control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dio3 output control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_dio3_output_control(sx1268_handle_t *handle, uint8_t *control);

/**
 * @brief     set the event mask
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] mask is the event mask
 * @return    status code
 *            - 0 success
 *            - 1 set event mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_event_mask(sx1268_handle_t *handle, uint8_t mask);

/**
 * @brief      get the event mask
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *mask points to a event mask buffer
 * @return     status code
 *             - 0 success
 *             - 1 get event mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_event_mask(sx1268_handle_t *handle, uint8_t *mask);

/**
 * @brief     set the dio output enable
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] enable is the enable settings
 * @return    status code
 *            - 0 success
 *            - 1 set dio output enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_dio_output_enable(sx1268_handle_t *handle, uint8_t enable);

/**
 * @brief      get the dio output enable
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *enable points to a enable settings buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dio output enable failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_dio_output_enable(sx1268_handle_t *handle, uint8_t *enable);

/**
 * @brief     set the dio input enable
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] enable is the enable settings
 * @return    status code
 *            - 0 success
 *            - 1 set dio input enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_dio_input_enable(sx1268_handle_t *handle, uint8_t enable);

/**
 * @brief      get the dio input enable
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *enable points to a enable settings buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dio input enable failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_dio_input_enable(sx1268_handle_t *handle, uint8_t *enable);

/**
 * @brief     set the pull up control
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] control is the pull up control
 * @return    status code
 *            - 0 success
 *            - 1 set pull up control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_pull_up_control(sx1268_handle_t *handle, uint8_t control);

/**
 * @brief      get the pull up control
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *control points to a pull up control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pull up control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_pull_up_control(sx1268_handle_t *handle, uint8_t *control);

/**
 * @brief     set the pull down control
 * @param[in] *handle points to a sx1268 handle structure
 * @param[in] control is the pull down control
 * @return    status code
 *            - 0 success
 *            - 1 set pull down control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t sx1268_set_pull_down_control(sx1268_handle_t *handle, uint8_t control);

/**
 * @brief      get the pull down control
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[out] *control points to a pull down control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pull down control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 chip is busy
 * @note       none
 */
uint8_t sx1268_get_pull_down_control(sx1268_handle_t *handle, uint8_t *control);

/**
 * @}
 */

/**
 * @defgroup sx1268_extern_driver sx1268 extern driver function
 * @brief    sx1268 extern driver modules
 * @ingroup  sx1268_driver
 * @{
 */

/**
 * @brief      write and read register
 * @param[in]  *handle points to a sx1268 handle structure
 * @param[in]  *in_buf points to a input buffer
 * @param[in]  in_len is the input length
 * @param[out] *out_buf points to a output buffer
 * @param[in]  out_len is the output length
 * @return     status code
 *             - 0 success
 *             - 1 write read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sx1268_write_read_reg(sx1268_handle_t *handle, uint8_t *in_buf, uint32_t in_len,
                              uint8_t *out_buf, uint32_t out_len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
