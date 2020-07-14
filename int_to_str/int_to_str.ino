#include <sstream>
#include <string>
#include <iostream>

using namespace std;

void setup() {
  Serial.begin(9600);
  Serial.print("Welcome to hell");
}

void loop() {
  
  //string text = std::to_string(Number);
  int Number = 123;       // number to be converted to a string
  string test;
  string Result;        // string which will contain the result

  ostringstream convert;   // stream used for the conversion

  convert << Number;      // insert the textual representation of 'Number' in the characters in the stream

  Result = convert.str(); // set 'Result' to the contents of the stream

  Serial.print(Result.c_str());
  delay(1000);
}

template <typename T>
string NumberToString ( T Number )
{
  ostringstream ss;
  ss << Number;
  return ss.str();
}
