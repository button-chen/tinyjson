#ifndef BUTTON_TINY_JSON_VALUE_H_
#define BUTTON_TINY_JSON_VALUE_H_

#include <string>
#include <sstream>

class Value
{
public:
    Value() { 
        value_.clear(); 
        nokey_ = false;
    }
	Value(std::string val) : value_(val) {
        if (value_ == "") {
            value_.clear();
            nokey_ = true;
        }
        else {
            nokey_ = false;
        }
    }
	~Value() {}

public:
    std::string value() {
        return value_;
    }

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

	template<typename V>
	void Set(V v) {
		std::ostringstream oss;
        if (nokey_) {
            oss << v;
        }else{
            oss << "\"" << value_ << "\"" << ":" << v;
        }
		value_ = oss.str();
	}

	template<>
	void Set(std::string v) {
		std::ostringstream oss;
        if (nokey_) {
            oss << "\"" << v << "\"";
        }
        else {
            oss << "\"" << value_ << "\"" << ":" << "\"" << v << "\"";
        }
		value_ = oss.str();
	}

	template<>
	void Set(const char* v) {
		std::ostringstream oss;
        if (nokey_) {
            oss << "\"" << v << "\"";
        }
        else {
            oss << "\"" << value_ << "\"" << ":" << "\"" << v << "\"";
        }
		value_ = oss.str();
	}

	template<>
	void Set(bool v) {
		std::ostringstream oss;
        std::string val = v == true ? "true" : "false";
        if (nokey_) {
            oss << val;
        }
        else {
            oss << "\"" << value_ << "\"" << ":" << val;
        }
		value_ = oss.str();
	}

    template<typename T>
    void Put(T& v){
        std::ostringstream oss;
        if (v.get_nokey()) {
            oss << v.WriteJson<0>();
        }
        else {
            oss << v.WriteJson();
        }
        value_ = oss.str();
    }

    template<typename T>
    void SetChild(T& v) {
        std::ostringstream oss;
        oss << "\"" << value_ << "\"" << ":" << v.WriteJson<2>();
        value_ = oss.str();
    }

private:
	std::string value_;
    bool nokey_;
};

template<typename T>
class ValueArray : public T
{
public:
	ValueArray() {}
	ValueArray(std::vector<std::string> vo) {
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
