#ifndef BUTTON_TINY_JSON_H_
#define BUTTON_TINY_JSON_H_

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "value.hpp"

// 把json看做是对象'{}' 与 数组'[]' 的组合
class ParseJson
{
public:
	ParseJson();
	~ParseJson();

public:
	bool ParseArray(std::string json, std::vector<std::string>& vo);
	bool ParseObj(std::string json);
	std::vector<std::string> GetKeyVal();
	
protected:
	std::string Trims(std::string s, char lc, char rc);
	std::string FetchArrayStr(std::string inputstr, int inpos, int& offset);
	std::string FetchObjStr(std::string inputstr, int inpos, int& offset);

private:
	std::vector<char> token_;
	std::vector<std::string> keyval_;
};

class TinyJson;
typedef ValueArray<TinyJson> Values;

class TinyJson
{
	friend class ValueArray<TinyJson>;
    friend std::ostream & operator << (std::ostream& os, TinyJson& ob);
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

	template<typename R>
	R GetValue() {
		return Value(KeyVal_[0]).GetAs<R>();
	}

	Values GetChild(std::string key);

	// write
	Value& operator[](std::string k) {
		Items_.push_back(Value(k));
        Value& v = Items_[Items_.size() - 1];
        if (k == "") {
            nokey_ = true;
        }
		return v;
	}

    bool get_nokey() {
        return nokey_;
    }

    template<int fix = 1>
    std::string WriteJson();

private:
	std::vector<std::string> KeyVal_;
	std::vector<Value> Items_;
    bool nokey_;
};

template<int fix = 1>
std::string TinyJson::WriteJson()
{
    std::string prefix = fix == 1 ? "{" : "[";
    std::string suffix = fix == 1 ? "}" : "]";
    if (fix == 0) {
        prefix = "";
        suffix = "";
    }
    std::ostringstream oss;
    oss << prefix;
    std::map<std::string, std::vector<std::string>> arrays;
    int i = 0;
    int size = Items_.size();
    std::string seq = ",";
    for (; i < size; ++i) {
        Value& v = Items_[i];
        oss << v.value() << seq;
    }
    std::string jsonstring = oss.str();
    if (jsonstring.back() == ',') {
        jsonstring = jsonstring.substr(0, jsonstring.find_last_of(','));
    }

    jsonstring += suffix;
    return jsonstring;
}

#endif  // BUTTON_TINY_JSON_H_
