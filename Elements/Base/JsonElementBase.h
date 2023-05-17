#include "JsonElementBaseType.h"

class JsonElementBase
{
    JsonElementBaseType type;

public:
    JsonElementBase(const JsonElementBaseType &type) : type(type) {}
    const JsonElementBaseType &getType() const
    {
        return this->type;
    }
    virtual void print(std::ostream &o, size_t inset = 0) const = 0;
    virtual JsonElementBase *clone() const = 0;
};