#include "unicodelite.h"
#include "utf8_to_ucs4_test.h"
#include <gtest/gtest.h>


#define DO_TEST_SUCCESS(bytes, hex_glyph, char_glyph)         \
TEST(ucs4_read_glyph_utf8, double_byte_success_ ## hex_glyph)     \
{                                                             \
  test_utf8_to_ucs4_success(char_glyph, hex_glyph, 2);        \
}

DO_TEST_SUCCESS(2, 0x0080, "\u0080")
DO_TEST_SUCCESS(2, 0x0410, "\u0410")
DO_TEST_SUCCESS(2, 0x0411, "\u0411")
DO_TEST_SUCCESS(2, 0x0417, "\u0417")
DO_TEST_SUCCESS(2, 0x041A, "\u041A")
DO_TEST_SUCCESS(2, 0x041F, "\u041F")
DO_TEST_SUCCESS(2, 0x0420, "\u0420")
DO_TEST_SUCCESS(2, 0x0421, "\u0421")
DO_TEST_SUCCESS(2, 0x0427, "\u0427")
DO_TEST_SUCCESS(2, 0x042A, "\u042A")
DO_TEST_SUCCESS(2, 0x042F, "\u042F")
DO_TEST_SUCCESS(2, 0x0430, "\u0430")
DO_TEST_SUCCESS(2, 0x0431, "\u0431")
DO_TEST_SUCCESS(2, 0x0437, "\u0437")
DO_TEST_SUCCESS(2, 0x043A, "\u043A")
DO_TEST_SUCCESS(2, 0x043F, "\u043F")
DO_TEST_SUCCESS(2, 0x0440, "\u0440")
DO_TEST_SUCCESS(2, 0x0441, "\u0441")
DO_TEST_SUCCESS(2, 0x0447, "\u0447")
DO_TEST_SUCCESS(2, 0x044A, "\u044A")
DO_TEST_SUCCESS(2, 0x044F, "\u044F")
DO_TEST_SUCCESS(2, 0x04FF, "\u04FF")
DO_TEST_SUCCESS(2, 0x06FF, "\u06FF")
DO_TEST_SUCCESS(2, 0x0700, "\u0700")
DO_TEST_SUCCESS(2, 0x07FF, "\u07FF")

//TODO: Failure tests
