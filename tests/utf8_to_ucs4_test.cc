#include "unicodelite.h"
#include <gtest/gtest.h>

void
test_utf8_to_ucs4(const char *utf8_input,
                  int32_t ucs4_expected,
                  size_t length_input,
                  const char *utf8_expected,
                  size_t length_expected)
{
  int32_t ucs4_result = ucs4_read_glyph_utf8(&utf8_input, &length_input);

  EXPECT_EQ(ucs4_result, ucs4_expected);
  EXPECT_EQ(length_input, length_expected);
  EXPECT_EQ(utf8_input, utf8_expected);

  uint8_t *expect_ptr = reinterpret_cast<uint8_t *>(&ucs4_expected);
  uint8_t *result_ptr = reinterpret_cast<uint8_t *>(&ucs4_result);

  EXPECT_EQ(result_ptr[0], expect_ptr[0]);
  EXPECT_EQ(result_ptr[1], expect_ptr[1]);
  EXPECT_EQ(result_ptr[2], expect_ptr[2]);
  EXPECT_EQ(result_ptr[3], expect_ptr[3]);
}

