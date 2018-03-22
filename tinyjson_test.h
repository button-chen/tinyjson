#pragma once

#include "tinyjson.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
using namespace tiny;

string jsonstring = "\
{\
	\"name\":\"liergou\",\
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
	\"name\":\"liergou\",\
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


// read demo
void TEST1() {
	cout << "\nTEST 1 READ JSON" << endl;
	// read
	TinyJson json;
	json.ReadJson(jsonstring);

	string name = json.Get<string>("name");
	float age = json.Get<float>("age");
	string lang = json.Get<string>("lang");

	assert(name == "liergou");
	assert(age > 26 && age < 27);
	assert(lang == "cpp");

	Values data = json.GetChild("data");
	for (int i = 0; i < data.GetCount(); i++) {
		data.Parse(i);
		string one = data.Get<string>("one");
		if (i == 0)
		{
			assert(one == "chenone");
		}
		if (i == 1)
		{
			assert(one == "chen22");
		}
		Values two = data.GetChild("two");
		for (int ii = 0; ii < two.GetCount(); ii++) {
			two.Parse(ii);
			string love1 = two.Get<string>("love1");
			int love2 = two.Get<int>("love2");
			if (i == 0)
			{
				assert(love1 == "2233");
				assert(love2 == 44444);
			}
			if (i == 1)
			{
				assert(love1 == "8899");
				assert(love2 == 10000);
			}

		}
	}
	cout << "TEST 1 PASS" << endl;
}

// read demo
void TEST2() {
	cout << "\nTEST 2 READ JSON" << endl;
	// read
	TinyJson json;
	json.ReadJson(jsonstring2);

	string name = json.Get<string>("name");
	float age = json.Get<float>("age");
	string lang = json.Get<string>("lang");

	assert(name == "liergou");
	assert(age > 26 && age < 27);
	assert(lang == "cpp");

	Values data = json.GetChild("data");
	for (int i = 0; i < data.GetCount(); i++) {
		data.Parse(i);
		string one = data.Get<string>("one");
		if (i == 0)
		{
			assert(one == "chenone");
		}
		if (i == 1)
		{
			assert(one == "chen22");
		}
		Values two = data.GetChild("two");
		for (int ii = 0; ii < two.GetCount(); ii++) {
			two.Parse(ii);
			string val = two.GetValue<string>();
			if (i == 0 && ii == 0)
			{
				assert(val == "love_chen");
			}
			if (i == 0 && ii == 1)
			{
				assert(val == "love_hui");
			}
			if (i == 1 && ii == 0)
			{
				assert(val == "love_chen2");
			}
			if (i == 1 && ii == 1)
			{
				assert(val == "love_hui2");
			}
		}
	}
	cout << "TEST 2 PASS" << endl;
}

// write demo TEST3()

/*   write result

{
    "name": "liergou",
    "age": 26,
    "handsome": true,
    "data": {
        "love1": "book",
        "love2": 666
    },
    "data2": {
        "love1": "book2",
        "love2": 6662
    }
}

*/

void TEST3() {
	cout << "\nTEST 3 WRITE JSON" << endl;
	// write
	TinyJson wjson;
	wjson["name"].Set("liergou");
	wjson["age"].Set(26);
	wjson["handsome"].Set(true);

	TinyJson subjson;
	subjson["love1"].Set("book");
	subjson["love2"].Set(666);

	TinyJson subjson2;
	subjson2["love1"].Set("book2");
	subjson2["love2"].Set(6662);

	wjson["data"].Set(subjson);
	wjson["data2"].Set(subjson2);

	string str = wjson.WriteJson();
	cout << "json string: \r\n" << endl;
	cout << str << endl;
}

// write demo TEST4()

/*   write result

{
    "name": "liergou",
    "age" : 26,
    "handsome" : true,
    "data" : [
      {
        "love1": "book",
        "love2" : 666
      },
      {
        "love1": "book2",
        "love2" : 6662
      }
    ]
}

*/

void TEST4() {
    cout << "\nTEST 4 WRITE JSON" << endl;
    // write
    TinyJson wjson;
    wjson["name"].Set("liergou");
    wjson["age"].Set(26);
    wjson["handsome"].Set(true);

    TinyJson subjson;
    subjson["love1"].Set("book");
    subjson["love2"].Set(666);

    TinyJson subjson2;
    subjson2["love1"].Set("book2");
    subjson2["love2"].Set(6662);

    TinyJson jsonarray;
    jsonarray[""].Put(subjson);
    jsonarray[""].Put(subjson2);

    wjson["data"].SetChild(jsonarray);

    string str = wjson.WriteJson();
    cout << "json string: \r\n" << endl;
    cout << str << endl;
}

// write demo TEST5()

/*   write result

{
    "name": "liergou",
    "age" : 26,
    "handsome" : true,
    "data" : [
         "book",
         666
    ]
}

*/

void TEST5() {
    cout << "\nTEST 5 WRITE JSON" << endl;
    // write
    TinyJson wjson;
    wjson["name"].Set("liergou");
    wjson["age"].Set(26);
    wjson["handsome"].Set(true);

    TinyJson subjson;
    subjson[""].Set("book");
    subjson[""].Set(666);

    TinyJson jsonarray;
    jsonarray[""].Put(subjson);

    wjson["data"].SetChild(jsonarray);

    string str = wjson.WriteJson();
    cout << "json string: \r\n" << endl;
    cout << str << endl;
}
