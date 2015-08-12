#include "unicodelite.h"

// -----------------------------------------------------------------------------------------------------------
// Bits of    First       Last        Bytes in  Byte 1    Byte 2    Byte 3    Byte 4    Byte 5    Byte 6
// code point code point  code point  sequence
// -----------------------------------------------------------------------------------------------------------
//   7        U+0000     U+007F       1        0xxxxxxx
//  11        U+0080     U+07FF       2        110xxxxx  10xxxxxx
//  16        U+0800     U+FFFF       3        1110xxxx  10xxxxxx  10xxxxxx
//  21        U+10000    U+1FFFFF     4        11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
//  26        U+200000   U+3FFFFFF    5        111110xx  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx
//  31        U+4000000  U+7FFFFFFF   6        1111110x  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx  10xxxxxx
// -----------------------------------------------------------------------------------------------------------

/**
 * @brief unicode_lite_glyph_ucs4_to_utf8
 * @param str
 * @param utf8
 * @return On success increase str pointer to
 */
uint32_t
glyph_ucs4_to_utf8(uint32_t glyph)
{

  const static int32_t mask[7] = {
    0x3F, /* 0b00111111 */
    0x7F, /* 0b01111111 */
    0x1F, /* 0b00011111 */
    0x0F, /* 0b00001111 */
    0x07, /* 0b00000111 */
    0x03, /* 0b00000011 */
    0x01, /* 0b00000001 */
  };
  const static int32_t indicator[7] = {
    0x80, /* 0b10000000 */
    0x00, /* 0b00000000 */
    0xC0, /* 0b11000000 */
    0xE0, /* 0b11100000 */
    0xF0, /* 0b11110000 */
    0xF8, /* 0b11111000 */
    0xFC, /* 0b11111100 */
  };

  const static uint32_t unicode_bytes_count[8] =
  {
    0x00000000, /* 0 */
    0x0000007F, /* 1 */
    0x000007FF, /* 2 */
    0x0000FFFF, /* 3 */
    0x001FFFFF, /* 4 */
    0x03FFFFFF, /* 5 */
    0x7FFFFFFF, /* 6 */
    0xFFFFFFFF, /* 7 */
  };

  uint8_t bytes_count = 0;
  while(glyph > unicode_bytes_count[bytes_count])
  {
    ++bytes_count;
  }

  uint32_t glyph_utf8 = 0;
  char *output_str = (char *)(&glyph_utf8);

  switch (bytes_count)
  {
    case 1:
    {
      *(output_str + 0) = ((glyph >>  0) & mask[1]) | indicator[1];
      break;
    }
    case 2:
    {
      *(output_str + 0) = ((glyph >>  6) & mask[2]) | indicator[2];
      *(output_str + 1) = ((glyph >>  0) & mask[0]) | indicator[0];
      break;
    }
    case 3:
    {
      *(output_str + 0) = ((glyph >>  10) & mask[3]) | indicator[3];
      *(output_str + 1) = ((glyph >>   4) & mask[0]) | indicator[0];
      *(output_str + 2) = ((glyph >>   0) & mask[0]) | indicator[0];
      break;
    }
    case 4:
    {
      *(output_str + 0) = ((glyph >>  15) & mask[4]) | indicator[4];
      *(output_str + 1) = ((glyph >>   9) & mask[0]) | indicator[0];
      *(output_str + 2) = ((glyph >>   3) & mask[0]) | indicator[0];
      *(output_str + 3) = ((glyph >>   0) & mask[0]) | indicator[0];
      break;
    }
    case 5:
      //TODO:
    case 6:
      //TODO:
    default:
    {
      return (uint32_t)(-1);
    }
  }
  return glyph_utf8;
}


/**
 * @brief glyph_ucs4_to_utf8
 * @param str
 * @param utf8
 * @return On success increase str pointer to
 */
//int
//__ucs4_to_utf8(const char * *input_str,
//                   uint32_t *in_bytes,
//                   char * *output_str,
//                   uint32_t *out_bytes)
//{
//  return -1;
//}


