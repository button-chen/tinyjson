#pragma once

#include "tinyjson.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
using namespace tiny;

string jsonstring = "\
{\
	\"name\":\"lier  gou\",\
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
	\"lang\":\"2cpp\"\
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

string jsonstring3 = "\
{\
	\"xx\": {\
		\"a\": 1,\
		\"b\" : 2\
	}\
}";

// read demo
void TEST99() {
	cout << "\nTEST 99 READ JSON" << endl;
	// read
	TinyJson json;
	json.ReadJson(jsonstring3);

	xobject data = json.Get<xobject>("xx");
	for (int i = 0; i < data.Count(); i++) {
		data.Enter(i);
		int one = data.Get<int>("a");
		int two = data.Get<int>("b");
		int three = data.Get<int>("c", 99);
		assert(one == 1);
		assert(two == 2);
		assert(three == 99);
	}
	cout << "TEST 99 PASS" << endl;
}


// read demo
void TEST1() {
	cout << "\nTEST 1 READ JSON" << endl;
	// read
	TinyJson json;
	json.ReadJson(jsonstring);

	string name = json.Get<string>("name");
	float age = json.Get<float>("age");
	string lang = json.Get<string>("lang");

	assert(name == "lier  gou");
	assert(age > 26 && age < 27);
	assert(lang == "2cpp");

	xarray data = json.Get<xarray>("data");
	for (int i = 0; i < data.Count(); i++) {
		data.Enter(i);
		string one = data.Get<string>("one");
		if (i == 0)
		{
			assert(one == "chenone");
		}
		if (i == 1)
		{
			assert(one == "chen22");
		}
		xobject two = data.Get<xobject>("two");
		for (int ii = 0; ii < two.Count(); ii++) {
			two.Enter(ii);
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

	xarray data = json.Get<xarray>("data");
	for (int i = 0; i < data.Count(); i++) {
		data.Enter(i);
		string one = data.Get<string>("one");
		if (i == 0)
		{
			assert(one == "chenone");
		}
		if (i == 1)
		{
			assert(one == "chen22");
		}
		xarray two = data.Get<xarray>("two");
		for (int ii = 0; ii < two.Count(); ii++) {
			two.Enter(ii);
			string val = two.Get<string>();
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
    jsonarray.Push(subjson);
    jsonarray.Push(subjson2);

    wjson["data"].Set(jsonarray);

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
    jsonarray.Push(subjson);

    wjson["data"].Set(jsonarray);

    string str = wjson.WriteJson();
    cout << "json string: \r\n" << endl;
    cout << str << endl;
}
