#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

struct Buffer {
	// size in bits
	unsigned int size;
	// bits written to buffer
	unsigned int written;
	// bits consumed from buffer
	unsigned int consumed;

	unsigned char *data;
};

static inline void InitBuffer(struct Buffer *buf, int size) {
	buf->size = size;
	buf->written = 0;
	buf->consumed = 0;

	buf->data = malloc(size);
}

static inline void BufWrite(struct Buffer *buf, char bit) {
	int i = buf->written / 8;
	int n = buf->written % 8;

	// set nth bit in ith byte to bit
	buf->data[i] ^= (-(bit & 1) ^ buf->data[i]) & 1u << n;
	buf->written += 1;
}

static inline void BufWriteHalf(struct Buffer *buf, char half) {
	for (int i = 3; i >= 0; i--)
	BufWrite(buf, half >> i);
}

static inline void BufWriteByte(struct Buffer *buf, char byte) {
	for (int i = 7; i >= 0; i--)
	BufWrite(buf, byte >> i);
}

static inline void BufWriteComp(struct Buffer *buf, char bit) {
	// write a bit using complimentary format
	BufWrite(buf, bit); BufWrite(buf, ~bit);
}

static inline void BufWriteHalfComp(struct Buffer *buf, char half) {
	for (int i = 3; i >= 0; i--)
	BufWriteComp(buf, half >> i);
}

static inline void BufWriteByteComp(struct Buffer *buf, char byte) {
	for (int i = 7; i >= 0; i--)
	BufWriteComp(buf, byte >> i);
}

static inline int BufConsume(struct Buffer *buf, char *c) {
	if (buf->consumed >= buf->size) {
		return 0;
	}

	int i = buf->consumed / 8;
	int n = buf->consumed % 8;

	*c = buf->data[i] >> n & 1;
	buf->consumed += 1;
	return 1;
}
//tømmer 
static inline void FreeBuffer(struct Buffer *buf) {
	free(buf->data);
}
//
static inline void BufWriteAddress(struct Buffer *buf, char house, char address) {
	// start code
	BufWriteHalf(buf, 0b1110);
	// house code
	BufWriteHalfComp(buf, house);
	// address
	BufWriteHalfComp(buf, address);
	// suffix
	BufWriteComp(buf, 0b0);
}
//fylder bufferen med en kommando
static inline void BufWriteCommand(struct Buffer *buf, char house, char order) {
	// start code
	BufWriteHalf(buf, 0b1110);
	// house code
	BufWriteHalfComp(buf, house);
	// order
	BufWriteHalfComp(buf, order);
	// suffix
	BufWriteComp(buf, 0b1);
}

#endif