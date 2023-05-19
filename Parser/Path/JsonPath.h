#pragma once
#include "../../Utils/List/List.hpp"
#include "./JsonKey.h"

// TODO:make it to class
struct JsonPath
{
    List<JsonKey> path;

    MyString toString() const noexcept
    {
        MyString result;
        for (size_t i = 0; i < path.getCount(); i++)
        {
            if (path[i].isArray)
            {
                // TODO: fix
                result += "NumberHere";
            }
            else
            {
                // TODO: точки
                result += path[i].key;
            }
        }
        return std::move(result);
    }
};