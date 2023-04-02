#ifndef KUTIL_H__
#define KUTIL_H__

#include <stdint.h>
#include <stddef.h>

typedef uint64_t mask64;
typedef uint32_t mask32;
typedef uint16_t mask16;
typedef uint8_t mask8;

void hang(void);

// a null-terminator is not written to `out_buf`.
// currently supported format specifiers:
// `%x`: (unsigned) hexadecimal integer.
// `%b`: (unsigned) binary integer.
// `%c`: character.
// `%s`: string.
// `%d`: (unsigned) decimal integer.
size_t buf_fmt(char out_buf[], char const *fmt, ...);

#endif
