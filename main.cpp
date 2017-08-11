#include "tinyjson.h"
#include <string>
#include <iostream>
using namespace std;

string jsonstring = "\
{\
	\"name\":\"chenhuizong\",\
	\"age\" : 26.9,\
	\"data\" : [\
	{\
		\"one\":\"chenone\",\
		\"two\" : {\
			\"love1\":\"2233\",\
			\"love2\":44444,\
		}\
	},\
	{\
		\"one\":\"chen22\",\
		\"two\" : {\
			\"love1\":\"8899\",\
			\"love2\":10000,\
		}\
	}\
	],\
	\"lang\":\"cpp\"\
}\
";

int main()
{
	TinyJson json;
	json.ReadJson(jsonstring);

	string name = json.Get<string>("name");
	float age = json.Get<float>("age");
	string lang = json.Get<string>("lang");

	cout << "name: " << name << "  age: " << age << "  lang: " << lang << endl;

	Values data = json.GetChild("data");
	cout << "data: " << endl;
	for (int i = 0; i < data.GetCount(); i++) {
		data.Parse(i);
		string one = data.Get<string>("one");
		cout << "one: " << one << endl;
		Values two = data.GetChild("two");
		for (int ii = 0; ii < two.GetCount(); ii++) {
			two.Parse(ii);
			string love1 = two.Get<string>("love1");
			int love2 = two.Get<int>("love2");

			cout << "love1: " << love1 << "  love2: " << love2 << endl;
		}
	}

	return 0;
}

