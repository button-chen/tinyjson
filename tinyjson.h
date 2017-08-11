#ifndef BUTTON_TINY_JSON_H_
#define BUTTON_TINY_JSON_H_

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

class Value 
{
public:
	Value() { value_.clear(); }
	Value(std::string val) : value_(val) {}
	~Value() {}

public:
	template<typename R>
	R Format() {
		std::istringstream iss(value_);
		R v;
		iss >> v;
		return v;
	}
private:
	std::string value_;
};

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

class TinyJson
{
	friend class Values;
public:
	TinyJson();
	~TinyJson();

public:
	bool ReadJson(std::string json);

	template<typename R>
	R Get(std::string key) {
		auto itr = std::find(KeyVal_.begin(), KeyVal_.end(), key);
		if (itr == KeyVal_.end()) {
			return R();
		}
		return Value(*(++itr)).Format<R>();
	}
	Values GetChild(std::string key);

private:
	std::vector<std::string> KeyVal_;
};

class Values : public TinyJson
{
public:
	Values() {}
	Values(std::vector<std::string> vo) {
		vo_ = vo;
	}

	bool Parse(int i) {
		std::string obj = vo_[i];
		return ReadJson(obj);
	}

	int GetCount() {
		return vo_.size();
	}

private:
	std::vector<std::string> vo_;
};

#endif  // BUTTON_TINY_JSON_H_
