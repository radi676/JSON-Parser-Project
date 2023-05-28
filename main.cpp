#include <iostream>

#include "./Elements/Base\Primitive\String\StringJsonElement.h"
#include "./Elements/Base\Primitive\Number\IntegerJsonElement.h"
#include "./Elements/Base\Primitive\Number\DecimalJsonElement.h"
#include "./Elements/Base\Primitive\Null\NullJsonElement.h"
#include "./Elements/Base\Primitive\Boolean\BooleanJsonElement.h"
#include "./Elements/Base\Compound\Array\JsonArray.h"

int main()
{
    BooleanJsonElement k0(false);
    StringJsonElement k1("ehrdfni");
    DecimalJsonElement k2(2.34);
    NullJsonElement k3;
    JsonArray k5;
    k5.pushFront(k0);
    k5.pushBack(k1);
    k5.pushBack(k2);
    k5.pushBack(k3);
    k5.print(std::cout);
}