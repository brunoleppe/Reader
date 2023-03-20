//
// Created by bruno on 18/03/23.
//

#include "hal_ring_buffer.h"

void ring_buffer_initialize(RingBuffer *rbuf,int size, uint8_t *buffer){
    rbuf->buffer = buffer;
    rbuf->count = rbuf->head = rbuf->tail = 0;
    rbuf->size = size;
}

bool ring_buffer_push(RingBuffer *rbuf, uint8_t data){
    if(rbuf->count >= rbuf->size)
        return false;
    rbuf->buffer[rbuf->head++] = data;
    rbuf->count++;
    if(rbuf->head == rbuf->size){
        rbuf->head = 0;
    }
    return true;
}

bool ring_buffer_pull(RingBuffer *rbuf, uint8_t *data){
    if(rbuf->count == 0)
        return false;
    *data = rbuf->buffer[rbuf->tail++];
    rbuf->count --;
    if(rbuf->tail == rbuf->size)
        rbuf->tail = 0;

    return true;
}

size_t ring_buffer_count(RingBuffer *rbuf){
    return rbuf->count;
}