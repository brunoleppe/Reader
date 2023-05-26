/**
 * @file dma.h
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
 * @brief DMA Interface.
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright (c) 2023
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
 */

#ifndef DMA_H
#define DMA_H

/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define DMA_CHANNEL_0                                       (0)
#define DMA_CHANNEL_1                                       (1)
#define DMA_CHANNEL_2                                       (2)
#define DMA_CHANNEL_3                                       (3)
#define DMA_CHANNEL_4                                       (4)
#define DMA_CHANNEL_5                                       (5)
#define DMA_CHANNEL_6                                       (6)
#define DMA_CHANNEL_7                                       (7)

#define DMA_CHANNEL_PRIORITY_3                              (0x0003)
#define DMA_CHANNEL_PRIORITY_2                              (0x0002)
#define DMA_CHANNEL_PRIORITY_1                              (0x0001)
#define DMA_CHANNEL_PRIORITY_0                              (0x0000)

#define DMA_CHANNEL_ABORT_IRQ                               (0x0004)
#define DMA_CHANNEL_START_IRQ                               (0x0008)
#define DMA_CHANNEL_CHAIN_LOWER                             (0x0010)
#define DMA_CHANNEL_CHAIN_UPPER                             (0x0020)
#define DMA_CHANNEL_CHAINED                                 (0x0040)
/**********************************************************************
* Typedefs
**********************************************************************/

/**
 * @brief Data type representing a DMA channel.
 */
typedef uint32_t DMA_Channel;

/**
 * @brief Structure representing the configuration for a DMA channel.
 */
typedef struct {
    uint8_t abortIrq;        ///< Abort interrupt flag.
    uint8_t startIrq;        ///< Start interrupt flag.
    uint16_t srcSize;        ///< Source transfer size.
    uint16_t dstSize;        ///< Destination transfer size.
    uint16_t cellSize;       ///< Cell transfer size.
    uint32_t srcAddress;     ///< Source address.
    uint32_t dstAddress;     ///< Destination address.
} DMA_CHANNEL_Config;

/**
 * @brief Enumeration representing the cause of a DMA interrupt.
 */
typedef enum {
    DMA_IRQ_CAUSE_TRANSFER_COMPLETE,  ///< Transfer complete interrupt cause.
    DMA_IRQ_CAUSE_ABORT,              ///< Abort interrupt cause.
    DMA_IRQ_CAUSE_ERROR               ///< Error interrupt cause.
} DMA_IRQ_CAUSE;

/**
 * @brief Function pointer type for DMA callback functions.
 *
 * @param channel   DMA channel.
 * @param cause     Cause of the DMA interrupt.
 * @param context   User-defined context.
 */
typedef void (*DMA_Callback)(DMA_Channel channel, DMA_IRQ_CAUSE cause, uintptr_t context);

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the DMA module.
 *
 * @return 0 on success.
 */
int DMA_init();

/**
 * @brief Initializes a DMA channel.
 *
 * @param channel       DMA channel to initialize.
 * @param configFlags   Configuration flags for the DMA channel.
 *
 * @return 0 on success.
 */
int DMA_channel_init(DMA_Channel channel, int configFlags);

/**
 * @brief Configures a DMA channel.
 *
 * @param channel   DMA channel to configure.
 * @param config    Pointer to the DMA channel configuration.
 *
 * @return 0 on success.
 */
int DMA_channel_config(DMA_Channel channel, DMA_CHANNEL_Config *config);

/**
 * @brief Initiates a transfer on a DMA channel.
 *
 * @param channel   DMA channel to initiate the transfer on.
 *
 * @return 0 on success.
 */
int DMA_channel_transfer(DMA_Channel channel);

/**
 * @brief Registers a callback function for a DMA channel.
 *
 * @param channel   DMA channel to register the callback for.
 * @param callback  Callback function to register.
 * @param context   User-defined context for the callback.
 */
void DMA_callback_register(DMA_Channel channel, DMA_Callback callback, uintptr_t context);

#ifdef __cplusplus
}
#endif

#endif /* DMA_H */