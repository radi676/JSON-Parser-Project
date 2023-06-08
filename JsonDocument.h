#pragma once
#include <fstream>
#include "./Elements/Base/Compound/Object/JsonObject.h"
#include "./Elements/Base/Compound/Array/JsonArray.h"
#include "./Parser/Path/JsonPath.h"
#include "./Exceptions/PathAlreadyExistsException.h"
#include "./Exceptions/NoPathFoundException.h"

// JsonDocument is a JsonObject
class JsonDocument : private JsonElement
{

    void traverseSearch(const &MyString key, List<JsonElement> &result, const JsonElement &element)
    {
        if (element.value()->getType() == JsonElementBaseType::Object)
        {
            const JsonObject &object = dynamic_cast<const JsonObject &>(element);
            for (size_t i = 0; i < object.getCount(); i++)
            {
                if (object[i].first() == key)
                {
                    result.pushBack(object[i].second);
                }

                traverseSearch(key, result, object[i].second());
            }
        }
        else if (element.value()->getType() == JsonElementBaseType::Array)
        {
            const JsonArray &array = dynamic_cast<const JsonArray &>(element);
            for (size_t i = 0; i < array.getCount(); i++)
            {
                traverseSearch(key, result, array[i]);
            }
        }
    }

    Optional<JsonElement *> findParent(const JsonPath &path, JsonElement &root)
    {
        return find(path.parent(), &root);
    }
    Optional<JsonElement*> find(const JsonPath& path, JsonElement* root)
	{
		JsonElement* current = root;
		size_t levels = path.length();

		for (size_t i = 0; i < levels; i++)
		{
			if (current->value()->getType() == JsonElementBaseType::Array && path.isArray(i))
			{
				// Possible throw
				current = &(*dynamic_cast<JsonArray*>(current->value().ptr()))[path.arrayIndex(i)];
			}
			else if (current->value()->getType() == JsonElementBaseType::Object && !path.isArray(i))
			{
				// Possible throw
				Optional<Pair<MyString, JsonElement>*> opt = (*dynamic_cast<JsonObject*>(current->value().ptr())).getByKey(path.key(i));
				if (!opt)
				{
					throw std::exception();
				}

				current = &(*opt)->second();
			}
			else
			{
				return Optional<JsonElement*>::empty();
			}
		}

		return current;
	}

public:
	JsonDocument() : JsonDocument(JsonObject())
	{
	}

	JsonDocument(const JsonElement& obj) : JsonElement(obj.value())
	{

	}

	void print(std::ostream& ouputStream) const
	{
		_value->print(ouputStream);
	}

	JsonElement find(const JsonPath& path) // throws NoFoundPath
	{
		Optional<JsonElement*> result = find(path, this);
		if (!result)
		{
			throw std::exception();
		}

		return **result;
	}

	List<JsonElement> search(const MyString& key) const // No throws
	{
		List<JsonElement> result;
		traverseSearch(key, result, *this);
		return std::move(result);
	}

	void set(const JsonPath& path, const JsonElement& value) // throws by getByPath
	{
		Optional<JsonElement* >searched = find(path, this);
		if (!searched)
		{
			throw std::exception();
		}

		(*searched)->setValue(value.value());

		//catch (const NoKeyFoundException& ex)
		//{
		//	throw NoPathFoundException(path, ex.what());
		//}
	}

	// Throws PathAlreadyExistsException
	void create(const JsonPath& path, const JsonElement& value)
	{
		JsonElement* current = this;
		size_t levels = path.length();

		for (size_t i = 0; i < levels; i++)
		{
			if (current->value()->getType() == JsonElementBaseType::Array && path.isArray(i))
			{
				// Possible throw
				JsonArray* arr = dynamic_cast<JsonArray*>(current->value().ptr());
				if (i == levels - 1)
				{
					try
					{
						arr->insertAt(value, path.arrayIndex(i));
						return;
					}
					catch (std::exception& e)
					{

						//TODO: rethrow -> it is invalid index, more than count
					}
				}
				else
				{
					if (arr->getCount() == path.arrayIndex(i))
					{
						//create
						JsonElement toAdd = JsonObject();
						if (i <= levels - 3 && path.isArray(i + 2))
						{
							toAdd = JsonElement(JsonArray());
						}

						arr->pushBack(toAdd);
						current = &(arr->getLast());
					}
					else if (path.arrayIndex(i) < arr->getCount())
					{
						current = &((*arr)[path.arrayIndex(i)]);
					}
					else
					{
						throw std::exception(); // Invalid index to add;
					}

				}

			}
			else if (current->value()->getType() == JsonElementBaseType::Object && !path.isArray(i))
			{
				JsonObject* obj = dynamic_cast<JsonObject*>(current->value().ptr());
				Optional<Pair<MyString, JsonElement>*> opt = obj->getByKey(path.key(i));
				if (opt)
				{
					if (i == levels - 1)
					{
						// path exists already
						throw std::exception();
					}
					current = &(*opt)->second();
				}
				else
				{
					Pair<MyString, JsonElement> toAdd(path.key(i), JsonObject());
					if (i != levels - 1 && path.isArray(i + 1))
					{
						toAdd.second() = JsonArray();
					}

					obj->pushBack(toAdd);
					current = &(obj->getLast().second());
				}
			}
			else
			{
				// Path exists to somewhere but cannot continue/ i.e. in the middle of path threre is no obj/arr element but str/int
				throw std::exception();
			}

		}

		current->setValue(value.value());
	}

	void deleteElement(const JsonPath& path)
	{
		JsonKey key = path.getLast();

		Optional<JsonElement*> opt = findParent(path, *this);
		if (!opt)
		{
			throw std::exception();
		}

		JsonElement* parent = *opt;

		if (key.isArray() && parent->value()->getType() == JsonElementBaseType::Array)
		{
			// Posible throw -> handle
			dynamic_cast<JsonArray*>(parent->value().ptr())->removeAt(key.arrayIndex());
		}
		else if (!key.isArray() && parent->value()->getType() == JsonElementBaseType::Object)
		{
			MyString _key = key.key();
			// Check if removed
			dynamic_cast<JsonObject*>(parent->value().ptr())->removeFirstWhere([_key](Pair<MyString, JsonElement>& element)
			{ return element.first() == _key; });
		}
		else
		{
			throw std::exception();
		}

		//catch (const std::exception& e)
		//{
		//	// TODO: rethrow
		//	std::cerr << e.what() << '\n';
		//}
	}

	bool move(const JsonPath& from, const JsonPath& to) // No throws
	{
		Optional<JsonElement*> toMove = find(from, this);

		if (!toMove)
		{
			throw std::exception();
		}

		JsonElement toAdd((**toMove).value());

		try
		{
			deleteElement(from);
			create(to, toAdd);
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what();
		}
	}


	bool save(std::ofstream& file, const JsonPath& path = JsonPath()) // No throws
	{
		if (!file.is_open())
		{
			return false;
		}

		if (!file.good())
		{
			return false;
		}

		try
		{
			JsonElement toSave = find(path);
			toSave.print(file);
			return file.good();
		}
		catch (const std::exception& e)
		{
			// TODO: rethrow
			std::cerr << e.what() << '\n';
		}
	}
};
