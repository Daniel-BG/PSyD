#include "RingBuffer.h"


uint8_t RingBuffer_Put(RingBuffer * buffer, uint8_t byte) {
    uint16_t next = (buffer->head + 1) % RING_BUF_SIZE;
    if (next != buffer->tail) {
        buffer->buffer[buffer->head] = byte;
        buffer->head = next;
        return 0;
    }
    return 1; //FULL
}

uint16_t RingBuffer_Count(RingBuffer * buffer) {
    uint16_t h = buffer->head;
    uint16_t t = buffer->tail;
    return (h >= t) ? (h - t) : (RING_BUF_SIZE - t + h);
}

uint8_t RingBuffer_Read(RingBuffer * buffer, uint8_t *byte) {
    if (buffer->head == buffer->tail) return 0;
    *byte = buffer->buffer[buffer->tail];
    buffer->tail = (buffer->tail + 1) % RING_BUF_SIZE;
    return 1;
}

uint8_t RingBuffer_Peek(RingBuffer * buffer, uint16_t offset, uint8_t *byte) {
    if (offset >= RingBuffer_Count(buffer)) return 0;
    uint16_t idx = (buffer->tail + offset) % RING_BUF_SIZE;
    *byte = buffer->buffer[idx];
    return 1;
}

void RingBuffer_Discard(RingBuffer * buffer, uint16_t len) {
    uint16_t count = RingBuffer_Count(buffer);
    if (len > count) len = count;
    buffer->tail = (buffer->tail + len) % RING_BUF_SIZE;
}

void RingBuffer_Flush(RingBuffer * buffer) {
    buffer->head = buffer->tail;
}
