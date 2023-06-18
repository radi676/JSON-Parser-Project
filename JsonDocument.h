#pragma once

#include "./Elements/Base/Compound/Object/JsonObject.h"
#include "./Elements/Base/Compound/Array/JsonArray.h"

#include "./Path/JsonPath.h"

#include "./Exceptions/NoKeyFoundException.h"
#include "./Exceptions/PathAlreadyExistsException.h"
#include "./Exceptions/NoPathFoundException.h"
#include "./Exceptions/FileWriteException.h"

#include "./Utils/Parser/Parser.h"
#include "./Utils/Regex/Regex.h"

#include <fstream>
#include <sstream>

class JsonDocument : private JsonElement
{
	void traverseSearch(const Regex& regex, List<JsonElement>& result, JsonElement* element) const
	{
		if (element->type() == JsonElementBaseType::Object)
		{
			JsonObject* object = element->to<JsonObject>();
			for (size_t i = 0; i < object->getCount(); i++)
			{
				if (regex.match((*object)[i].first()))
				{
					result.pushBack(object->at(i).second());
				}

				traverseSearch(regex, result, &object->at(i).second());
			}
		}
		else if (element->value()->getType() == JsonElementBaseType::Array)
		{
			JsonArray* array = element->to<JsonArray>();
			for (size_t i = 0; i < array->getCount(); i++)
			{
				traverseSearch(regex, result, &array->at(i));
			}
		}
	}

	JsonElement* findParent(const JsonPath& path, JsonElement& root)
	{
		return find(path.parent(), &root);
	}

	JsonElement* find(const JsonPath& path, JsonElement* root) const
	{
		JsonElement* current = root;
		size_t levels = path.length();

		for (size_t i = 0; i < levels; i++)
		{
			if (current->type() == JsonElementBaseType::Array && path.isArray(i))
			{
				try
				{
					current = &(*current->to<JsonArray>())[path.arrayIndex(i)];
				}
				catch (const std::out_of_range&)
				{
					throw NoKeyFoundException(Parser::parseToString(path.arrayIndex(i)), "Invalid index supplied for array in json key @index=" + Parser::parseToString(i + 1));
				}
			}
			else if (current->type() == JsonElementBaseType::Object && !path.isArray(i))
			{
				Optional<Pair<MyString, JsonElement>*> opt = current->to<JsonObject>()->getByKey(path.key(i));
				if (!opt)
				{
					throw NoKeyFoundException(path.key(i), "Missing key @index=" + Parser::parseToString(i + 1) + " when expecting a valid key in json object: " + current->toString());
				}

				current = &(*opt)->second();
			}
			else
			{
				MyString _key = path.isArray(i) ? Parser::parseToString(path.arrayIndex(i)) : path.key(i);
				MyString _type = path.isArray(i) ? "array" : "object";
				throw NoKeyFoundException(_key, "Missing key @index=" + Parser::parseToString(i + 1) + " when expecting a deeper nesting, expected " + _type + " but got element: " + current->toString());
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

	void print(std::ostream& ouputStream, const JsonPath& path = JsonPath()) const
	{
		JsonElement* element = find(path, const_cast<JsonDocument*>(this));
		element->print(ouputStream);
	}

	List<JsonElement> search(const MyString& key) const
	{
		List<JsonElement> result;
		Regex regex(key);
		traverseSearch(regex, result, const_cast<JsonDocument*>(this));
		return result;
	}

	void set(const JsonPath& path, const JsonElement& value)
	{
		try
		{
			JsonElement* searched = find(path, this);
			searched->setValue(value.value());
		}
		catch (const NoKeyFoundException& ex)
		{
			throw NoPathFoundException(path, ex.what());
		}
	}

	void create(const JsonPath& path, const JsonElement& value)
	{
		JsonDocument substitute(this->value()->clone());
		JsonElement* current = &substitute;
		size_t levels = path.length();

		for (size_t i = 0; i < levels; i++)
		{
			if (current->type() == JsonElementBaseType::Array && path.isArray(i))
			{
				JsonArray* arr = current->to<JsonArray>();
				if (i == levels - 1)
				{
					if (arr->getCount() < path.arrayIndex(i))
					{
						throw PathAlreadyExistsException(path, "Cannot add element at unreachable index in json array, specified by key @index=" + Parser::parseToString(i + 1));
					}
					else if (arr->getCount() > path.arrayIndex(i))
					{
						throw PathAlreadyExistsException(path, "Cannot add element at already existing index in json array, specified by key @index=" + Parser::parseToString(i + 1));
					}

					arr->pushBack(value);
					*this = substitute;
					return;
				}
				else
				{
					if (arr->getCount() == path.arrayIndex(i))
					{
						//create
						JsonElement toAdd = JsonObject();
						if (path.isArray(i + 1))
						{
							toAdd = JsonElement(JsonArray());
						}

						arr->pushBack(toAdd);
						current = &(arr->getLast());
					}
					else if (path.arrayIndex(i) < arr->getCount())
					{
						//exists
						current = &((*arr)[path.arrayIndex(i)]);
					}
					else
					{
						throw PathAlreadyExistsException(path, "Cannot get element of path at unreachable index in json array, specified by key @index=" + Parser::parseToString(i + 1));
					}
				}
			}
			else if (current->type() == JsonElementBaseType::Object && !path.isArray(i))
			{
				JsonObject* obj = current->to<JsonObject>();
				Optional<Pair<MyString, JsonElement>*> opt = obj->getByKey(path.key(i));
				if (opt)
				{
					if (i == levels - 1)
					{
						// path exists already
						throw PathAlreadyExistsException(path, "Cannot add element where key already exists in json object, specified by key @index=" + Parser::parseToString(i + 1));
					}

					current = &(*opt)->second();
				}
				else
				{
					JsonElement toAdd = JsonObject();
					if (i != levels - 1 && path.isArray(i + 1))
					{
						toAdd = JsonArray();
					}

					if (!obj->pushBack(path.key(i), toAdd))
					{
						throw PathAlreadyExistsException(path, "Cannot add element where key already exists, specified by key @index=" + Parser::parseToString(i + 1));
					}

					current = &(obj->getLast().second());
				}
			}
			else
			{
				// Path exists to somewhere but cannot continue/ i.e. in the middle of path threre is no obj/arr element but str/int
				throw PathAlreadyExistsException(path, "Cannot add element where key already exists and is not of the right composite type, specified by key @index=" + Parser::parseToString(i + 1));
			}

		}

		current->setValue(value.value());
		*this = substitute;
	}

	// throws NoPathFoundException
	void deleteElement(const JsonPath& path)
	{
		try {
			JsonKey key = path.getLast();
			JsonElement* parent = findParent(path, *this);

			if (key.isArray() && parent->type() == JsonElementBaseType::Array)
			{
				try
				{
					parent->to<JsonArray>()->removeAt(key.arrayIndex());
				}
				catch (const std::out_of_range&)
				{
					throw NoKeyFoundException("Index of json array @" + Parser::parseToString(key.arrayIndex()), "Invalid index specified. Out of range.");
				}
			}
			else if (!key.isArray() && parent->type() == JsonElementBaseType::Object)
			{
				MyString _key = key.key();

				if (!parent->to<JsonObject>()->removeByKey(_key))
				{
					throw NoKeyFoundException(_key, "Couldn't find and delete key in json Object.");
				}
			}
			else
			{
				throw NoKeyFoundException(key.key(), "Missing key ");

				MyString _key = key.isArray() ? Parser::parseToString(key.arrayIndex()) : key.key();
				MyString _type = key.isArray() ? "array" : "object";
				throw NoKeyFoundException(_key, "Missing key when trying to delete element, expected " + _type + " but got element: " + parent->toString());
			}
		}
		catch (const NoKeyFoundException& e)
		{
			throw NoPathFoundException(path, e.what());
		}
		catch (const NoPathFoundException&)
		{
			throw;
		}
	}

	// throws NoPathFoundException, PathAlreadyExistsException
	void move(const JsonPath& from, const JsonPath& to)
	{
		JsonElement toAdd;

		try
		{
			JsonElement* toMove = find(from, this);
			toAdd = toMove->value();
		}
		catch (const NoKeyFoundException& ex)
		{
			throw NoPathFoundException(from, ex.what());
		}

		create(to, toAdd);
		deleteElement(from);
	}


	// No throws
	void save(const MyString& filePath, const JsonPath& path = JsonPath()) const
	{
		std::ofstream file(filePath.c_str());

		if (!file.is_open())
		{
			throw FileWriteException(filePath, "Couldn't open file for write.");
		}

		try
		{
			print(file, path);
		}
		catch (const NoPathFoundException& ex)
		{
			throw FileWriteException(filePath, ex.what());
		}

	}
};