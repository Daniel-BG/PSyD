#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

/*********************** RING BUFFER *******************************/
// the ring buffer is the entry point for received bytes
// it fills up automatically on UART interrupts so that
// the MCU is free to do other things in the meantime

#define RING_BUF_SIZE   (2048+256)

typedef struct {
    uint8_t buffer[RING_BUF_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} RingBuffer;

uint8_t RingBuffer_Put(RingBuffer * buffer, uint8_t byte);
uint16_t RingBuffer_Count(RingBuffer * buffer);
uint8_t RingBuffer_Read(RingBuffer * buffer, uint8_t *byte);
uint8_t RingBuffer_Peek(RingBuffer * buffer, uint16_t offset, uint8_t *byte);
void RingBuffer_Discard(RingBuffer * buffer, uint16_t len);
void RingBuffer_Flush(RingBuffer * buffer);

#endif //RINGBUFFER_H_
