#include "unicodelite.h"
#include <gtest/gtest.h>
#include <string>

using std::string;


enum convert_result_e {
  RESULT_SUCCESS,
  RESULT_WRONG_RESULT,
  RESULT_WRONG_BEHAVIOUR,
  RESULT_INVALID_CHAR,
  RESULT_NOT_ENOUGH_SPACE,
};


static
convert_result_e
test_utf8_to_ucs4(const char *utf8_input,
                  int32_t ucs4_expected,
                  size_t length_input,
                  const char *utf8_expected,
                  size_t length_expected)
{
  const char *utf8_text_orig = utf8_input;
  const char *utf8_text_arg = utf8_text_orig;

  int32_t ucs4_result = ucs4_read_glyph_utf8(&utf8_text_arg, &length_input);

  EXPECT_EQ(ucs4_result, ucs4_expected);
  EXPECT_EQ(length_input, length_expected);
  EXPECT_EQ(utf8_input, utf8_expected);

  if (ucs4_result == -1)
  {

    return RESULT_WRONG_RESULT;
  }

  uint8_t *expect_ptr = reinterpret_cast<uint8_t *>(&ucs4_expected);
  uint8_t *result_ptr = reinterpret_cast<uint8_t *>(&ucs4_result);

  EXPECT_EQ(result_ptr[0], expect_ptr[0]);
  EXPECT_EQ(result_ptr[1], expect_ptr[1]);
  EXPECT_EQ(result_ptr[2], expect_ptr[2]);
  EXPECT_EQ(result_ptr[3], expect_ptr[3]);

  return RESULT_SUCCESS;
}


TEST(ucs4_read_glyph_utf8, single_byte_success_x00)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x00";
    int32_t ucs4_expected     = 0x00;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }
}


TEST(ucs4_read_glyph_utf8, single_byte_success_x01)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x01";
    int32_t ucs4_expected     = 0x01;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }
}


TEST(ucs4_read_glyph_utf8, single_byte_success_x73)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x73";
    int32_t ucs4_expected     = 0x73;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }
}


TEST(ucs4_read_glyph_utf8, single_byte_success_x7F)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\x7F";
    int32_t ucs4_expected     = 0x7F;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }
}


TEST(ucs4_read_glyph_utf8, single_byte_failure)
{
  const size_t bytes_per_glyph = 1;

  {
    const char *utf8_input    = "\xff";
    int32_t ucs4_expected     = 0xff;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }

  {
    const char *utf8_input    = "\x01";
    int32_t ucs4_expected     = 0x01;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }

  {
    const char *utf8_input    = "\x73";
    int32_t ucs4_expected     = 0x73;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }

  {
    const char *utf8_input    = "\x7F";
    int32_t ucs4_expected     = 0x7F;
    size_t length_input       = bytes_per_glyph;
    const char *utf8_expected = utf8_input   + bytes_per_glyph;
    size_t length_expected    = length_input - bytes_per_glyph;

    EXPECT_EQ(RESULT_SUCCESS,
              test_utf8_to_ucs4(utf8_input,
                                ucs4_expected,
                                length_input,
                                utf8_expected,
                                length_expected)
              );
  }
}


TEST(ucs4_read_glyph_utf8, double_byte_success)
{
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


