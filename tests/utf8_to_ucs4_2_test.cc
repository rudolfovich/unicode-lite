#include "unicodelite.h"
#include "utf8_to_ucs4_test.h"
#include <gtest/gtest.h>


/**
### Test 1 (success)
  input
    binary    0b00000000
    decimal   0
    hexical   0x00
    length    1
    text      "\x00"
  result
    binary    0b00000000
    decimal   0
    hexical   0x00
    length    0
    text      (text + 1)
 */
TEST(ucs4_read_glyph_utf8, double_byte_success_x00)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x00";
    int32_t ucs4_expected     = 0x00;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 1 (bad character)
  input
    binary    0b10000000
    decimal   128
    hexical   0x80
    length    1
    text      "\x80"
  result
    binary    -0b00000001
    decimal   -1
    hexical   -0x01
    length    length
    text      text
 */
TEST(ucs4_read_glyph_utf8, double_byte_failure_bad_char_x80)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x80";
    int32_t ucs4_expected     = -1;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input;
    size_t length_expected    = length_input;

    RUN_TEST_UTF8_TO_UCS4();
  }
}



//bool do_test()
//{
//  TEST("А", 0x0410);
//  TEST("Б", 0x0411);
//  TEST("Я", 0x042F);

//  TEST("а", 0x0430);
//  TEST("б", 0x0431);
//  TEST("я", 0x044F);

//  TEST("0", 0x0030);
//  TEST("9", 0x0039);

//  TEST("A", 0x0041);
//  TEST("B", 0x0042);
//  TEST("Z", 0x005A);

//  TEST("a", 0x0061);
//  TEST("b", 0x0062);
//  TEST("z", 0x007A);

//  return true;
//}


