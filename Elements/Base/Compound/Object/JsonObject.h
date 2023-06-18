#pragma once
#include "../CompoundJsonElement.hpp"
#include "../../../JsonElement.h"
#include "../../../../Utils/Optional/Optional.hpp"
#include "../../../../Utils/Pair/Pair.hpp"

class JsonObject : public CompoundJsonElement<Pair<MyString, JsonElement>>
{

public:
	JsonObject();
	virtual void print(std::ostream& o, size_t inset = 0) const override;
	Optional<Pair<MyString, JsonElement>*> getByKey(const MyString& key);
	bool removeByKey(const MyString& key);
	bool pushBack(const MyString& key, const JsonElement& value);
	virtual JsonElementBase* clone() const override;
};