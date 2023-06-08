#include <iostream>

#include "./Elements/Base\Primitive\String\StringJsonElement.h"
#include "./Elements/Base\Primitive\Number\IntegerJsonElement.h"
#include "./Elements/Base\Primitive\Number\DecimalJsonElement.h"
#include "./Elements/Base\Primitive\Null\NullJsonElement.h"
#include "./Elements/Base\Primitive\Boolean\BooleanJsonElement.h"
#include "./Elements/Base\Compound\Array/JsonArray.h"
#include "./Elements/Base\Compound\Object/JsonObject.h"

int main()
{
    JsonElementBase *k1 = new StringJsonElement("asd");
    StringJsonElement k8("asd");
    IntegerJsonElement k2(5);
    DecimalJsonElement k3(2.34);
    JsonArray k5;
    JsonObject k6;
    Pair<MyString, JsonElement> p("T1:", k8);
    Pair<MyString, JsonElement> p1("T2:", k5);
    k5.pushBack(k8);
    k5.pushBack(k3);
    k5.pushBack(k2);
    k6.pushBack(p);
    k6.pushBack(p1);
    k6.print(std::cout);

    // JsonElementBase &k5 = JsonObject();
    //     JsonObject &k = dynamic_cast<JsonObject &>(k5);
    //     JsonElement& k7(SharedPtr<IntegerJsonElement> &k1);
    //    k.pushBack()
}