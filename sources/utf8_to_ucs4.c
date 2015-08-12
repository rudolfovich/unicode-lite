#include "unicodelite.h"

// -----------------------------------------------------------------------------------------------------------
// Bits of       First       Last        Bytes in  Byte 1    Byte 2    Byte 3    Byte 4    Byte 5    Byte 6
// code point    code point  code point  sequence
// -----------------------------------------------------------------------------------------------------------
//   7            U+0000     U+007F       1        0xxxxxxx
//  11            U+0080     U+07FF       2        110xxxxx  10xxxxxx
//  16            U+0800     U+FFFF       3        1110xxxx  10xxxxxx  10xxxxxx
//  21            U+10000    U+1FFFFF     4        11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
//  26            U+200000   U+3FFFFFF    5        111110xx  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx
//  31            U+4000000  U+7FFFFFFF   6        1111110x  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx
// -----------------------------------------------------------------------------------------------------------

/**
 * @brief unicode_lite_ucs4_read_glyph_utf8
 * @param text    Pointer to pointer of zero-terminated array of characters
 * @param length  Length of string
 * @return On success increase str pointer to
 */
uint32_t
ucs4_read_glyph_utf8(const char **text,
                     size_t *length)
{
  struct utf8_bytes_s
  {
    uint32_t indicator_mask;
    uint32_t indicator_value;
    uint32_t value_mask;
    uint32_t offset;
  };
  const static struct utf8_bytes_s utf8_bytes[] =
  {
    //                       //    { ind_mask,   ind_value,   value_mask }
    { 0xC0, 0x80, 0x3F, 6 }, // 0: { 0b11000000, 0b10 000000, 0b00111111 }
    { 0x80, 0x00, 0x7F, 7 }, // 1: { 0b10000000, 0b0 0000000, 0b01111111 }
    { 0xE0, 0xC0, 0x1F, 5 }, // 2: { 0b11100000, 0b110 00000, 0b00011111 }
    { 0xF0, 0xE0, 0x0F, 4 }, // 3: { 0b11110000, 0b1110 0000, 0b00001111 }
    { 0xF8, 0xF0, 0x07, 3 }, // 4: { 0b11111000, 0b11110 000, 0b00000111 }
    { 0xFC, 0xF8, 0x03, 2 }, // 5: { 0b11111100, 0b111110 00, 0b00000011 }
    { 0xFE, 0xFC, 0x01, 1 }, // 6: { 0b11111110, 0b1111110 0, 0b00000001 }
  };
  const static uint32_t utf8_bytes_length = ( sizeof(utf8_bytes) /
                                              sizeof(struct utf8_bytes_s) );
//  const static char offset[4][4] = {
//    { 0,  0,  0,  0, },
//    { 0,  7,  0,  0, },
//    { 0,  5, 11,  0, },
//    { 0,  4, 10, 16, },
//  };
  uint32_t bytes_count;

  if (*length == 0) {
    return -1;
  }

  uint32_t character =  (*text)[0];

  bytes_count = 0;
  while( ++bytes_count < utf8_bytes_length )
  {
    uint32_t indicator = character & utf8_bytes[bytes_count].indicator_mask;
    if (indicator == utf8_bytes[bytes_count].indicator_value)
    {
      for (int32_t index = 1; index < bytes_count; index++)
      {
        char c = (*text)[index];
        int32_t cc = c;
        indicator = cc & utf8_bytes[0].indicator_mask;
        if (indicator != utf8_bytes[0].indicator_value)
        {
          return -1;
        }
      }
      break;
    }
  }

  if (bytes_count == utf8_bytes_length )
  {
    // Invalid UTF8 character
    return -1;
  }

  switch (bytes_count)
  {
    case 1:
    {
      int32_t ucs4_glyph = 0;
      character = (*text)[0] & utf8_bytes[bytes_count].value_mask;
      ucs4_glyph |= character << 0;

      (*text)   += bytes_count;
      (*length) -= bytes_count;
      return ucs4_glyph;
    }
    case 2:
    {
      int32_t ucs4_glyph = 0;
      character = (*text)[0] & utf8_bytes[bytes_count].value_mask;
      ucs4_glyph |= character << (5 + 1);

      character = (*text)[1] & utf8_bytes[0].value_mask;
      ucs4_glyph |= character << 0;

      (*text)   += bytes_count;
      (*length) -= bytes_count;
      return ucs4_glyph;
    }
    case 3:
    {
      int32_t ucs4_glyph = 0;
      character = (*text)[0] & utf8_bytes[bytes_count].value_mask;
      ucs4_glyph |= character << (6 + 1 + 4 + 1);

      character = (*text)[1] & utf8_bytes[0].value_mask;
      ucs4_glyph |= character << (6 + 1);
      
      character = (*text)[2] & utf8_bytes[0].value_mask;
      ucs4_glyph |= character << 0;

      (*text)   += bytes_count;
      (*length) -= bytes_count;
      return ucs4_glyph;
    }
    case 4:
    {
      int32_t ucs4_glyph = 0;

      //UNDONE: not implemented

      (*text)   += bytes_count;
      (*length) -= bytes_count;
      return ucs4_glyph;
    }
    case 5:
    {
      int32_t ucs4_glyph = 0;

      //UNDONE: not implemented

      (*text)   += bytes_count;
      (*length) -= bytes_count;
      return ucs4_glyph;
    }
    case 6:
    {
      int32_t ucs4_glyph = 0;

      //UNDONE: not implemented

      (*text)   += bytes_count;
      (*length) -= bytes_count;
      return ucs4_glyph;
    }
  }
  return -1;
}

