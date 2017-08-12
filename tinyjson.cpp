#include "tinyjson.h"


TinyJson::TinyJson() {}
TinyJson::~TinyJson() {}

bool TinyJson::ReadJson(std::string json) {
	// 去掉最开始与最后的{}
	size_t b = json.find_first_of('{');
	size_t e = json.find_last_of('}');
	json = json.substr(b+1, e-b);
	ParseJson p;
	p.ParseObj(json);
	KeyVal_ = p.GetKeyVal();
	return true;
}

Values TinyJson::GetChild(std::string key) {
	std::string val = Get<std::string>(key);
	ParseJson p;
	std::vector<std::string> vo;
	p.ParseArray(val, vo);
	Values vals(vo);
	return vals;
}

std::string TinyJson::WriteJson()
{
	std::ostringstream oss;
	oss << "{";
	std::map<std::string, std::vector<std::string>> arrays;
	int i = 0;
	int size = Items_.size();
	std::string seq = ",";
	for (; i < size; ++i) {
		Value& v = Items_[i];
		if (!v.GetSecond().empty()) {
			std::vector<std::string>& vs = arrays[v.GetRawValue()];
            vs.push_back(v.GetSecond());
			continue;
		}
		oss << v.GetRawValue() << seq;
	}
	// ...
	auto itr = arrays.begin();
	for (; itr != arrays.end(); itr++) {
		std::string key = itr->first;
        std::vector<std::string> vals = itr->second;
        std::string s;
        for (int i = 0; i < vals.size(); i++){
            if (i != vals.size() - 1){
                s = vals[i] + ',';
                continue;
            }
            s = vals[i];
        }
        s = key + "[" + s + "]";
        oss << s << ",";
	}
    std::string jsonstring = oss.str();
    if (jsonstring.back() == ','){
        jsonstring = jsonstring.substr(0, jsonstring.find_last_of(','));
    }
    
    jsonstring += "}";
    return jsonstring;
}


ParseJson::ParseJson() { token_flag_ = true; }
ParseJson::~ParseJson() {}

bool ParseJson::IsToken(char c) {
	if (token_flag_ == false) {
		return false;
	}
	if (c == '{' || c == '}' || c == '[' || c == ']'
		|| c == ':' || c == '"' || c == ',') {
		return true;
	}
	return false;
}

bool ParseJson::ParseArray(std::string json, std::vector<std::string>& vo) {
	std::string word;
	int cnt = 0;
	for (int i = 0; i < json.size(); ++i) {
		char c = json[i];
		if (isspace(c)) continue;
		if (c == '{') {
			++cnt;
		}
		if (c == '}') {
			--cnt;
		}
		if (c == ',' && cnt == 0) {
			continue;
		}
		word.push_back(c);
		if (cnt == 0) {
			vo.push_back(word);
			word.clear();
		}
	}
	return true;
}

bool ParseJson::ParseObj(std::string json) {
	std::string word;
	int  cntbig = 0;
	int  cntmil = 0;
	bool isbig = false;
	bool ismil = false;
	for (int i = 0; i < json.size(); ++i) {
		char c = json[i];
		if (isspace(c)) continue;

		if (c == '[' && !isbig) {
			token_flag_ = false;
			ismil = true;
			++cntmil;
			continue;
		}
		if (c == '{' && !ismil) {
			token_flag_ = false;
			isbig = true;
			++cntbig;
		}
		if (IsToken(c)) {
			token_.push_back(c);
			if (!word.empty()) {
				keyval_.push_back(word);
				word.clear();
			}
			continue;
		}
		if (c == ']') {
			--cntmil;
		}
		if (c == '}') {
			--cntbig;
		}
		if (ismil && cntmil == 0 && token_flag_ == false) {
			token_flag_ = true;
			continue;
		}
		if (isbig && cntbig == 0 && token_flag_ == false) {
			token_flag_ = true;
		}
		word.push_back(c);
	}
	token_flag_ = true;
	return true;
}

std::vector<std::string> ParseJson::GetKeyVal() {
	return keyval_;
}
