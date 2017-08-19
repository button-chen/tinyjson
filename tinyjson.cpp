#include "tinyjson.h"


TinyJson::TinyJson() {}
TinyJson::~TinyJson() {}

bool TinyJson::ReadJson(std::string json) {
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

ParseJson::ParseJson() {}
ParseJson::~ParseJson() {}

bool ParseJson::ParseArray(std::string json, std::vector<std::string>& vo) {
	json = Trims(json, '[', ']');
	std::string tokens;
	int i = 0;
	for (; i < json.size(); ++i) {
		char c = json[i];
		if (isspace(c) || c == '\"') continue;
		if (c == ':' || c == ',' || c == '{') {
			if (!tokens.empty()) {
				vo.push_back(tokens);
				tokens.clear();
			}
			if (c == ',') continue;
			int offset = 0;
			char nextc = c;
			for (; c != '{';) {
				nextc = json[++i];
				if (isspace(nextc)) continue;
				break;
			}
			if (nextc == '{') {
				tokens = FetchObjStr(json, i, offset);
			}
			else if (nextc == '[') {
				tokens = FetchArrayStr(json, i, offset);
			}
			i += offset;
			continue;
		}
		tokens.push_back(c);
	}
	if (!tokens.empty()) {
		vo.push_back(tokens);
	}
	return true;
}

// 解析为 key-value 调用一次解析一个层次
bool ParseJson::ParseObj(std::string json) {
	json = Trims(json, '{', '}');
	std::string tokens;
	int i = 0;
	for (; i < json.size(); ++i) {
		char c = json[i];
		if (isspace(c) || c == '\"') continue;
		if (c == ':' || c == ',') {
			keyval_.push_back(tokens);
			tokens.clear();
			if (c == ',') continue;
			int offset = 0;
			char nextc;
			for (;;) {
				nextc = json[++i];
				if (isspace(nextc)) continue;
				break;
			}
			if (nextc == '{') {
				tokens = FetchObjStr(json, i, offset);
			}
			else if (nextc == '[') {
				tokens = FetchArrayStr(json, i, offset);
			}
			else {
				--i;
			}
			i += offset;
			continue;
		}
		tokens.push_back(c);
	}
	if (!tokens.empty()) {
		keyval_.push_back(tokens);
	}
	return true;
}

std::string ParseJson::Trims(std::string s, char lc, char rc)
{
	std::string ss = s;
	if (s.find(lc) != std::string::npos && s.find(rc) != std::string::npos) {
		size_t b = s.find_first_of(lc);
		size_t e = s.find_last_of(rc);
		ss = s.substr(b + 1, e - b - 1);
	}
	return ss;
}

std::string ParseJson::FetchArrayStr(std::string inputstr, int inpos, int& offset)
{
	int tokencount = 0;
	std::string objstr;
	int i = inpos;
	for (; i < inputstr.size(); i++) {
		char c = inputstr[i];
		if (isspace(c)) continue;
		if (c == '[') {
			++tokencount;
		}
		if (c == ']') {
			--tokencount;
		}
		objstr.push_back(c);
		if (tokencount == 0) {
			break;
		}
	}
	offset = i - inpos;
	return objstr;
}

std::string ParseJson::FetchObjStr(std::string inputstr, int inpos, int& offset)
{
	int tokencount = 0;
	std::string objstr;
	int i = inpos;
	for ( ; i < inputstr.size(); i++) {
		char c = inputstr[i];
		if (isspace(c)) continue;
		if (c == '{') {
			++tokencount;
		}
		if (c == '}') {
			--tokencount;
		}
		objstr.push_back(c);
		if (tokencount == 0) {
			break;
		}
	}
	offset = i - inpos;
	return objstr;
}

std::vector<std::string> ParseJson::GetKeyVal() {
	return keyval_;
}
