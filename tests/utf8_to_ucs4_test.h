#pragma once

void
test_utf8_to_ucs4(const char *utf8_input,
                  int32_t ucs4_expected,
                  size_t length_input,
                  const char *utf8_expected,
                  size_t length_expected);

#define RUN_TEST_UTF8_TO_UCS4()    (      \
  test_utf8_to_ucs4(utf8_input,           \
                    ucs4_expected,        \
                    length_input,         \
                    utf8_expected,        \
                    length_expected)      \
                    )

void
test_utf8_to_ucs4_success(const char *utf8_input,
                          int32_t ucs4_expected,
                          size_t bytes_per_glyph);

