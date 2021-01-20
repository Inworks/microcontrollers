### Author: jonathanmacias
### Email: jonathanpj777@gmail.com
### Date: 02/18/2020
### License: MIT

---
# Project: Simple Car

## Requirements

This project requires that you're using a Sparkfun Redbot Board. This board has just a bunch of SMD components, we will be using the motors to drive a car and create functions.

Along with that of course you need the necessary libraries listed at the top of the code. This was written on an Arduino Uno

This project assumes you know the basics of coding in Arduino and want to begin to expand what you know. The code has simple explanations but if for any of the takeaways you need a deeper explanation it should be here.

---

## Takeaways

1. Using libraries
2. Creating functions
3. Simple loops 

---

## Using Libraries

Libraries are part of the bread and butter of arduino. When you first start coding you can get away with not using them, but as you go onto using more complex components these can determine whether you code for 15 minutes or 2 minutes

At the top of almost every arduino example code you'll see something resembling this

`#include <RedBot.h>`

What this does is let me use functions and the contents of whatever may be in the file RedBot.h. In the project linked, there is a part where I create a variable 

`RedBotMotor motors;`

Without diving too deep into it, they created something called an abstract data type called "RedBotMotor" and gave it properties and functions. Now my object "motors" has inherited all of those same properties and functions, making operating it much easier. Under the documentation for the library it lists every function they have for the motors such as driving and stopping. With the library we have already made functions to operate the motors.

---

## Creating Functions

Functions are something I feel I don't see enough of in tutorials. They're incredibly useful and very transferrable to other programming areas. Not to mention it makes your code a lot more readable.

I mentioned in libraries that they typically come with functions that we can use to make our lives easier. Sometimes however we need to make our own custom functions. We can write functions to do certain things any time we call that function. This also means if we ever need to change our function, we only change it in one place and it changes it anywhere it's used in your code.

The syntax for making a function is

```
whatToReturn functionName(parameter){
  stuffToDo;
}
```

The whatToReturn means what is being given back, this can be any datatype or void which doesn't return anything and just executes code. Function name is self explanatory. A parameter is a variable you can give the function so that it does something with it. Finally stuffToDo is just what gets executed each time you call it. To call your function in your actual code that gets executed do this:

`functionName(parameter);`

You don't have to include the whatToReturn part, that's only for when you define it.

---
## Simple Loops

We only use for loops in this code, arguably the simplest type of loop. This loop is mainly for looping a certain number of times, allowing you to do something multiple times. The syntax I use can be broken down into this
```
for(int i=0; i<numberOfTimes; i++) {
  stuff;
}
```
This is a really easy way to memorize how to make a for loop to stuff for a certain number of times. The int i=0 creates a variable to compare to something, in our case it's numberOfTimes, then each time we do the stuff the i++ means increment by 1.

You can refer to the variable i if you ever want to do anything with it but only in the actual loop because it won't work outside of it. 