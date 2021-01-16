#include <sstream>
#include <string>
#include <iostream>
#include <list>

using namespace std;

void setup() {
  Serial.begin(9600);
  Serial.print("Welcome to hell");
}

void loop() {
  
  std::list<string> myList(3, "yes", "no", "maybe");

  for(i = 0; i<myList.size(); i++) {
    
  
  }
  /* commenting out while testing
  //string text = std::to_string(Number);
  int Number = 123;       // number to be converted to a string
  string test;
  string Result;        // string which will contain the result

  ostringstream convert;   // stream used for the conversion

  convert << Number;      // insert the textual representation of 'Number' in the characters in the stream

  Result = convert.str(); // set 'Result' to the contents of the stream

  Serial.print(Result.c_str()); */
  delay(1000);
}

template <typename T>
string NumberToString ( T Number )
{
  ostringstream ss;
  ss << Number;
  return ss.str();
}
