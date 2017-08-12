#ifndef BUTTON_TINY_JSON_VALUE_H_
#define BUTTON_TINY_JSON_VALUE_H_

#include <string>
#include <sstream>

class Value
{
public:
	Value() { value_.clear(); }
	Value(std::string val) : value_(val) {}
	~Value() {}

public:
	template<typename R>
	R GetAs() {
		std::istringstream iss(value_);
		R v;
		iss >> v;
		return v;
	}

	template<>
	bool GetAs() {
		return value_ == "true" ? true : false;
	}

	std::string GetRawValue() {
		return value_;
	}

	std::string GetSecond() {
		return second_;
	}

	template<typename V>
	void Set(V v) {
		std::ostringstream oss;
		oss << "\"" << value_ << "\"" << ":" << v;
		value_ = oss.str();
	}

	template<>
	void Set(std::string v) {
		std::ostringstream oss;
		oss << "\"" << value_ << "\"" << ":" << "\"" << v << "\"";
		value_ = oss.str();
	}

	template<>
	void Set(const char* v) {
		std::ostringstream oss;
		oss << "\"" << value_ << "\"" << ":" << "\"" << v << "\"";
		value_ = oss.str();
	}

	template<>
	void Set(bool v) {
		std::ostringstream oss;
		std::string val = v == true ? "true" : "false";
		oss << "\"" << value_ << "\"" << ":" << val;
		value_ = oss.str();
	}

	template<typename T>
	void Put(T& tj) {
		std::ostringstream oss;
		oss << "\"" << value_ << "\"" << ":";

		value_ = oss.str();
		second_ = tj.WriteJson();
	}

private:
	std::string value_;
	std::string second_;
};

template<typename T>
class ValueS : public T
{
public:
	ValueS() {}
	ValueS(std::vector<std::string> vo) {
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

#endif  // BUTTON_TINY_JSON_VALUE_H_
