#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint32_t ucs4_t;

#ifdef __cplusplus
extern "C" {
#endif


uint32_t
glyph_ucs4_to_utf8(uint32_t glyph);


uint32_t
ucs4_read_glyph_utf8(const char **text,
                     size_t *length);


#ifdef __cplusplus
}
#endif
