#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint32_t ucs4_t;

#ifdef __cplusplus
extern "C" {
#endif

#if UNUSED_CODE

enum convert_result_e {
  RESULT_SUCCESS,
  RESULT_WRONG_RESULT,
  RESULT_WRONG_BEHAVIOUR,
  RESULT_INVALID_CHAR,
  RESULT_NOT_ENOUGH_SPACE,
};

#endif

uint32_t
glyph_ucs4_to_utf8(uint32_t glyph);


int32_t ucs4_read_glyph_utf8(const char **text,
                     size_t *length);


#ifdef __cplusplus
}
#endif
