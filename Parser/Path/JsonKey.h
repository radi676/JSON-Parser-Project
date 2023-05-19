#include "../../Utils/String/MyString.h"

struct JsonKey
{
    // union?
    MyString key;
    size_t arrayIndex = 0;
    bool isArray = false;
};