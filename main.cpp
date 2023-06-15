#include <iostream>

#include "JsonDocument.h"
#include "./Elements/Base\Primitive\String\StringJsonElement.h"
#include "./Elements/Base\Primitive\Number\IntegerJsonElement.h"
#include "./Elements/Base\Primitive\Number\DecimalJsonElement.h"
#include "./Elements/Base\Primitive\Null\NullJsonElement.h"
#include "./Elements/Base\Primitive\Boolean\BooleanJsonElement.h"
#include "./Elements/Base\Compound\Array\JsonArray.h"


int main()
{
    //     JsonElementBase *k1 = new StringJsonElement("asd");
    //     StringJsonElement k8("asd");
    //     IntegerJsonElement k2(5);
    //     DecimalJsonElement k3(2.34);
    //     JsonElementBase* k10 = new JsonArray();

    //     JsonArray k5;
    //     JsonObject k6;
    //     Pair<MyString, JsonElement> p("T1:", k8);
    //     Pair<MyString, JsonElement> p1("T2:", k5);
    //     k5.pushBack(k8);
    //     k5.pushBack(k3);
    //     k5.pushBack(k2);
    //     k6.pushBack(p);
    //     k6.pushBack(p1);
    //     k6.print(std::cout);

    //     // JsonElementBase &k5 = JsonObject();
    //     //     JsonObject &k = dynamic_cast<JsonObject &>(k5);
    //     //     JsonElement& k7(SharedPtr<IntegerJsonElement> &k1);
    //     //    k.pushBack()

    JsonDocument document;
    BooleanJsonElement k0(false);
    StringJsonElement k1("ehrdfni");
    DecimalJsonElement k2(2.34);
    NullJsonElement k3;
    JsonObject k4;
    JsonArray k5;

    k4.pushBack(KeyedJsonElement("T1", k3));
    k4.pushBack(KeyedJsonElement("T2", k2));

    k5.pushBack(JsonElement(k1));
    k5.pushBack(JsonElement(k4));

    JsonPath path;
    path.push(JsonKey("Hello"));

    document.create(path, JsonElement(k1));
    document.set(path, JsonElement(k3));
    document.deleteElement(path);
    document.create(path, JsonElement(k4));
    path.push(JsonKey("asd"));
    document.create(path, JsonElement(k0));
    document.set(path, JsonElement(k4));
    path.push("arr");
    path.push((size_t)0);
    document.create(path, JsonElement(k2));
    document.print(std::cout);

    std::cout << "\n";

    JsonPath from;
    from.push("Heelo");
    from.push("asd");
    from.push("arr");
    from.push((size_t)0);

    JsonPath to;
    to.push("Heelo");
    to.push("arr");

    document.move(from, to);
    document.print(std::cout);

    JsonPath from2;
    from2.push("Heelo");
    from2.push("asd");
    from2.push("T1");

    JsonPath to2;
    to2.push("Heelo");
    to2.push("asd");
    to2.push("arr");
    to2.push((size_t)0);

    document.move(from2, to2);
    document.print(std::cout);
}