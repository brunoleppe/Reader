/**
 * @file hal_ring_buffer.h
 * @brief Header file for the HAL ring buffer.
 *
 * This file defines the interface for a ring buffer data structure used in the HAL (Hardware Abstraction Layer) module.
 * The ring buffer allows efficient storage and retrieval of data elements in a circular manner.
 *
 * @author Bruno Leppe (bruno.leppe.dev\@gmail.com)
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

#ifndef HAL_RING_BUFFER_H
#define HAL_RING_BUFFER_H

#include "hal_defs.h"

/**
 * @brief Structure representing a ring buffer.
 */
typedef struct {
    uint8_t *buffer; /**< Pointer to the buffer array. */
    int head;        /**< Index of the head element in the buffer. */
    int tail;        /**< Index of the tail element in the buffer. */
    size_t count;    /**< Current number of elements in the buffer. */
    size_t size;     /**< Maximum size of the buffer. */
} RingBuffer;

/**
 * @brief Initializes a ring buffer with the specified size and buffer.
 *
 * @param rbuf Pointer to the RingBuffer structure.
 * @param size Maximum size of the buffer.
 * @param buffer Pointer to the buffer array.
 */
void ring_buffer_initialize(RingBuffer *rbuf, int size, uint8_t *buffer);

/**
 * @brief Pushes a data element into the ring buffer.
 *
 * @param rbuf Pointer to the RingBuffer structure.
 * @param data Data element to push into the buffer.
 * @return True if the data was successfully pushed, false otherwise.
 */
bool ring_buffer_push(RingBuffer *rbuf, uint8_t data);

/**
 * @brief Pulls a data element from the ring buffer.
 *
 * @param rbuf Pointer to the RingBuffer structure.
 * @param data Pointer to store the pulled data element.
 * @return True if a data element was successfully pulled, false if the buffer is empty.
 */
bool ring_buffer_pull(RingBuffer *rbuf, uint8_t *data);

/**
 * @brief Retrieves the last data element in the ring buffer without removing it.
 *
 * @param rbuf Pointer to the RingBuffer structure.
 * @param data Pointer to store the last data element.
 * @return True if the last data element was successfully retrieved, false if the buffer is empty.
 */
bool ring_buffer_get_last(RingBuffer *rbuf, uint8_t *data);

/**
 * @brief Returns the current number of elements in the ring buffer.
 *
 * @param rbuf Pointer to the RingBuffer structure.
 * @return The number of elements in the buffer.
 */
size_t ring_buffer_count(RingBuffer *rbuf);

#endif //HAL_RING_BUFFER_H
