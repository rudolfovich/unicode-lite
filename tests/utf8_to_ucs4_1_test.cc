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
TEST(ucs4_read_glyph_utf8, single_byte_success_x00)
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
### Test 2 (success)
  input
    binary    0b00000001
    decimal   1
    hexical   0x01
    length    1
    text      "\x01"
  result
    binary    0b00000001
    decimal   1
    hexical   0x01
    length    0
    text      (text + 1)
 */
TEST(ucs4_read_glyph_utf8, single_byte_success_x01)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x01";
    int32_t ucs4_expected     = 0x01;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 3 (success)
  input
    binary    0b01110011 0b00000001
    decimal   115
    hexical   0x73
    length    2
    text      "\x73\x01"
  result
    binary    0b01110011
    decimal   115
    hexical   0x73
    length    (length - 1)
    text      (text + 1)
 */
TEST(ucs4_read_glyph_utf8, single_byte_success_x73)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x73\x01";
    int32_t ucs4_expected     = 0x73;
    size_t length_input       = bytes_per_glyph * 2;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 4 (success)
  input
    binary    0b01111111
    decimal   127
    hexical   0x7F
    length    1
    text      "\x7F"
  result
    binary    0b01111111
    decimal   127
    hexical   0x7F
    length    0
    text      (text + 1)

 */
TEST(ucs4_read_glyph_utf8, single_byte_success_x7F)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x7F";
    int32_t ucs4_expected     = 0x7F;
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
TEST(ucs4_read_glyph_utf8, single_byte_failure_bad_char_x80)
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


/**
### Test 2 (bad character)
  input
    binary    0b10111111
    decimal   191
    hexical   0xBF
    length    1
    text      "\xBF"
  result
    binary    -0b00000001
    decimal   -1
    hexical   -0x01
    length    length
    text      text
 */
TEST(ucs4_read_glyph_utf8, single_byte_failure_bad_char_xBF)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\xBF";
    int32_t ucs4_expected     = -1;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input;
    size_t length_expected    = length_input;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 3 (bad character)
  input
    binary    0b11111110
    decimal   254
    hexical   0xFE
    length    1
    text      "\xFE"
  result
    binary    -0b00000001
    decimal   -1
    hexical   -0x01
    length    length
    text      text
 */
TEST(ucs4_read_glyph_utf8, single_byte_failure_bad_char_xFE)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\xFE";
    int32_t ucs4_expected     = -1;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input;
    size_t length_expected    = length_input;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 4 (bad character)
  input
    binary    0b11111111 0b00000001
    decimal   255
    hexical   0xFF
    length    2
    text      "\xFF\x01"
  result
    binary    -0b00000001
    decimal   -1
    hexical   -0x01
    length    length
    text      text
 */
TEST(ucs4_read_glyph_utf8, single_byte_failure_bad_char_x7F)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\xFF\x01";
    int32_t ucs4_expected     = -1;
    size_t length_input       = bytes_per_glyph * 2;
    const char *utf8_expected = utf8_input;
    size_t length_expected    = length_input;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 5 (bad length: zero length correct character)
  input
    binary    0b01110011
    decimal   115
    hexical   0x73
    length    0
    text      "\x73"
  result
    binary    -0b00000001
    decimal   -1
    hexical   -0x01
    length    0
    text      text
 */
TEST(ucs4_read_glyph_utf8, single_byte_failure_zero_length)
{
  {
    const char *utf8_input    = "\x73";
    int32_t ucs4_expected     = -1;
    size_t length_input       = 0;
    const char *utf8_expected = utf8_input;
    size_t length_expected    = length_input;

    RUN_TEST_UTF8_TO_UCS4();
  }
}


/**
### Test 6 (bad length: one byte and 2 bytes signature)
  input
    binary    0b11011111
    decimal   223
    hexical   0xDF
    length    1
    text      "\xDF"
  result
    binary    -0b00000001
    decimal   -1
    hexical   -0x01
    length    length
    text      text
 */
TEST(ucs4_read_glyph_utf8, single_byte_failure_uncompleted)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\xDF";
    int32_t ucs4_expected     = -1;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input;
    size_t length_expected    = length_input;

    RUN_TEST_UTF8_TO_UCS4();
  }
}

