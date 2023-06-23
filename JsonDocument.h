#pragma once

#include "./Utils/String/MyString.h"
#include "./Utils/List/List.hpp"
#include "./Utils/List/List.hpp"
#include "./Elements/JsonElement.h"

#include "./Path/JsonPath.h"

#include "./Utils/Regex/Regex.h"

class JsonDocument : private JsonElement
{
	void traverseSearch(const Regex &regex, List<JsonElement> &result, JsonElement *element) const;

	JsonElement *findParent(const JsonPath &path, JsonElement &root);
	JsonElement *find(const JsonPath &path, JsonElement *root) const;

public:
	JsonDocument();
	JsonDocument(const JsonElement &obj);

	// throws NoPathFoundException
	void print(std::ostream &ouputStream, const JsonPath &path = JsonPath()) const;

	// throws NoPathFoundException
	List<JsonElement> search(const MyString &key) const;

	// throws NoPathFoundException
	void set(const JsonPath &path, const JsonElement &value);

	// throws NoPathFoundException, PathAlreadyExistsException
	void create(const JsonPath &path, const JsonElement &value);

	// throws NoPathFoundException
	void deleteElement(const JsonPath &path);

	// throws NoPathFoundException, PathAlreadyExistsException
	void move(const JsonPath &from, const JsonPath &to);

	// throws NoPathFoundException
	void save(const MyString &filePath, const JsonPath &path = JsonPath()) const;
};