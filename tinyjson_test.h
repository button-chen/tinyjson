#pragma once

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
			\"love2\":44444\
		}\
	},\
	{\
		\"one\":\"chen22\",\
		\"two\" : {\
			\"love1\":\"8899\",\
			\"love2\":10000\
		}\
	}\
	],\
	\"lang\":\"cpp\"\
}\
";

string jsonstring2 = "\
{\
	\"name\":\"chenhuizong\",\
	\"age\" : 26.9,\
	\"data\" : [\
	{\
		\"one\":\"chenone\",\
		\"two\" : [\
			\"love_chen\",\
			\"love_hui\"\
		]\
	},\
	{\
		\"one\":\"chen22\",\
		\"two\" : [\
			\"love_chen2\",\
			\"love_hui2\"\
		]\
	}\
	],\
	\"lang\":\"cpp\"\
}\
";

void TEST1() {
	cout << "TEST1 ======================================================" << endl;
	// read
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
		cout << "two:" << endl;
		for (int ii = 0; ii < two.GetCount(); ii++) {
			two.Parse(ii);
			string love1 = two.Get<string>("love1");
			int love2 = two.Get<int>("love2");

			cout << "love1: " << love1 << "  love2: " << love2 << endl;
		}
	}
}

void TEST2() {
	cout << "TEST2 ======================================================" << endl;
	// read
	TinyJson json;
	json.ReadJson(jsonstring2);

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
		cout << "two:" << endl;
		for (int ii = 0; ii < two.GetCount(); ii++) {
			two.Parse(ii);
			string val = two.GetValue<string>();
			cout << val << endl;
		}
	}
}

void TEST3() {
	cout << "TEST3 ======================================================" << endl;
	// write
	TinyJson wjson;
	wjson["name"].Set("chenhuizong");
	wjson["age"].Set(26);
	wjson["handsome"].Set(true);

	TinyJson subjson;
	subjson["love1"].Set("book");
	subjson["love2"].Set(666);

	TinyJson subjson2;
	subjson2["love1"].Set("book2");
	subjson2["love2"].Set(6662);

	wjson["data"].Put(subjson);
	wjson["data"].Put(subjson2);

	string str = wjson.WriteJson();
	cout << "json string: " << endl;
	cout << str << endl;
}
