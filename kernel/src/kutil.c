#include "kutil.h"

#include <stdarg.h>

static size_t fmt_spec_x(char out_buf[], uint64_t x)
{
	static char const fmt_lut[] = "0123456789abcdef";

	if (!x) {
		out_buf[0] = '0';
		return 1;
	}

	size_t ch_cnt;
	for (ch_cnt = 0; ch_cnt < 16 && x >> 4 * ch_cnt; ++ch_cnt);

	for (size_t i = 0; i < ch_cnt; ++i)
		out_buf[ch_cnt - 1 - i] = fmt_lut[x >> 4 * i & 0xf];

	return ch_cnt;
}

static size_t fmt_spec_b(char out_buf[], uint64_t b)
{
	if (!b) {
		out_buf[0] = '0';
		return 1;
	}

	size_t ch_cnt;
	for (ch_cnt = 0; ch_cnt < 64 && b >> ch_cnt; ++ch_cnt);

	for (size_t i = 0; i < ch_cnt; ++i)
		out_buf[ch_cnt - 1 - i] = b >> i & 0x1 ? '1' : '0';

	return ch_cnt;
}

static size_t fmt_spec_c(char out_buf[], char c)
{
	out_buf[0] = c;
	return 1;
}

static size_t fmt_spec_s(char out_buf[], char const *s)
{
	size_t wr;
	
	for (wr = 0; s[wr] != '\0'; ++wr)
		out_buf[wr] = s[wr];

	return wr;
}

size_t buf_fmt(char out_buf[], char const *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	size_t wr_ind = 0;
	
	for (size_t i = 0; fmt[i] != '\0'; ++i) {
		if (fmt[i] != '%') {
			out_buf[wr_ind++] = fmt[i];
			continue;
		}

		switch (fmt[i + 1]) {
		case '%':
			out_buf[wr_ind++] = '%';
			break;
		case 'x':
			wr_ind += fmt_spec_x(&out_buf[wr_ind], va_arg(args, uint64_t));
			break;
		case 'b':
			wr_ind += fmt_spec_b(&out_buf[wr_ind], va_arg(args, uint64_t));
			break;
		case 'c':
			wr_ind += fmt_spec_c(&out_buf[wr_ind], (char)va_arg(args, int));
			break;
		case 's':
			wr_ind += fmt_spec_s(&out_buf[wr_ind], va_arg(args, char const *));
			break;
		case 'd':
			break;
		default:
			break;
		}
		
		++i; // skip the format specifier's character.
	}

	va_end(args);
	return wr_ind;
}
