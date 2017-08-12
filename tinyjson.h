#ifndef BUTTON_TINY_JSON_H_
#define BUTTON_TINY_JSON_H_

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include "value.hpp"

class ParseJson
{
public:
	ParseJson();
	~ParseJson();

public:
	bool IsToken(char c);
	bool ParseArray(std::string json, std::vector<std::string>& vo);
	bool ParseObj(std::string json);
	std::vector<std::string> GetKeyVal();

private:
	std::vector<char> token_;
	std::vector<std::string> keyval_;
	bool token_flag_;
};

class TinyJson;
typedef ValueS<TinyJson> Values;

class TinyJson
{
	friend class ValueS<TinyJson>;
public:
	TinyJson();
	~TinyJson();

public:
	// read
	bool ReadJson(std::string json);

	template<typename R>
	R Get(std::string key) {
		auto itr = std::find(KeyVal_.begin(), KeyVal_.end(), key);
		if (itr == KeyVal_.end()) {
			return R();
		}
		return Value(*(++itr)).GetAs<R>();
	}
	Values GetChild(std::string key);

	// write
	Value& operator[](std::string k) {
		Items_.push_back(Value(k));
		return Items_[Items_.size() - 1];
	}

	std::string WriteJson();

private:
	std::vector<std::string> KeyVal_;
	std::vector<Value> Items_;
};

#endif  // BUTTON_TINY_JSON_H_
