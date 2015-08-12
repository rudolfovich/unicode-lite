#include "unicodelite.h"
#include <iostream>
#include <string>

#define CHECK(val)        if (!(val)) return false
#define TEST(utf8, ucs4)  CHECK(test(utf8, ucs4))

using namespace std;

static int _test_id = 1;

bool test(string const &utf8_char, uint32_t unicode_index)
{
  const uint8_t *utf8_ptr = (const uint8_t *) utf8_char.c_str();
  size_t length = utf8_char.length();

  uint16_t utf8_char0 = utf8_ptr[0];
  uint16_t utf8_char1 = utf8_ptr[1];
  uint16_t utf8_char2 = utf8_ptr[2];
  uint16_t utf8_char3 = utf8_ptr[3];

  const char *utf8_text = utf8_char.c_str();
  int32_t ucs4 = ucs4_read_glyph_utf8(&utf8_text, &length);

  uint32_t unicode_glyph = glyph_ucs4_to_utf8(unicode_index);
  uint8_t *unicode_ptr = (uint8_t *)&unicode_glyph;

  uint16_t unicode_char0 = unicode_ptr[0];
  uint16_t unicode_char1 = unicode_ptr[1];
  uint16_t unicode_char2 = unicode_ptr[2];
  uint16_t unicode_char3 = unicode_ptr[3];

  cout << "Test #" << _test_id++ << endl <<
          "  input: " << utf8_char << " : " << unicode_index <<
          endl <<
          "  ucs4: " << ucs4 <<
          endl <<
          "  original : " <<
          utf8_char0 << " " << utf8_char1 << " " <<
          utf8_char2 << " " << utf8_char3 << " " <<
          endl <<
          "  converted: " <<
          unicode_char0 << " " << unicode_char1 << " " <<
          unicode_char2 << " " << unicode_char3 << " " <<
          endl <<
          endl;

  return true;
}


bool do_test()
{
  TEST("А", 0x0410);
  TEST("Б", 0x0411);
  TEST("Я", 0x042F);

  TEST("а", 0x0430);
  TEST("б", 0x0431);
  TEST("я", 0x044F);

  TEST("0", 0x0030);
  TEST("9", 0x0039);

  TEST("A", 0x0041);
  TEST("B", 0x0042);
  TEST("Z", 0x005A);

  TEST("a", 0x0061);
  TEST("b", 0x0062);
  TEST("z", 0x007A);

  return true;
}

int main()
{
  cout << "Sterted!" << endl;

  if (do_test())
  {
    cout << "..Success!" << endl;
  }
  else
  {
    cout << "..Failed!" << endl;
  }

  cout << "Completed!" << endl;

  return 0;
}

