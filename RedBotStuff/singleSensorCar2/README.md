### Author: Jonathan Macias
### Email: jonathanpj777@gmail.com
### Date: 01/21/2020
### License: MIT
---
# Project: Sensor Object Detecting Car

## Requirements

This project requires that you have 2 motors in some car like fashion and an ultrasonic sensor, specifically the [HC-SRO4](https://www.sparkfun.com/products/15569)

Along with that just some general beginner knowledge of Arduino like making variables and using libraries

---

## Takeaways
1. If else statements
2. While statements

---

## If Else Statements

If statements are to check if something is true or not, the syntax for these is as follows

```
if(condition1) {
  stuff;
}
else if(condition2) {
  stuff;
}
else {
  stuff;
}
```

What happens here is if the condition you give it is true it will only do the stuff in those brackets and ignore the rest. If the first condition is false and the second condition is true then the stuff in that bracket will execute and everything else will be ignored. As you could've guessed if neither of the conditions are true, the stuff in else will be executed.

A couple of things to note is that you *DO NOT* need else if or an else statement, if you want you could only have an if statement to check 1 condition. You can have as many else if statements but you can only have one else statement.

You can have the following conditions <, >, <=, >= == != or just insert a true or false value. The == means equal to and != means not equal to. <= and >= mean less than or equal to and greater than or equal to respectively

If you want multiple statements in one condition you can do || meaning OR, or && meaning AND, so 

```
if(condition1 || condition2) {
  stuff;
}
```

Will execute if either one is true and

```
if(condition1 && condition2) {
  stuff;
}
```
Will only execute if both are true

---
## While Statements

While statements will execute as long as the condition you provide it is true. The syntax for this is as follows 
```
while(condition) {
  stuff;
}
```
In the code there's a statement that says 
```
While(distance <15) {
  stuff;
}
```
The stuff will continue to turnand shine its light while continuously checking the distance in front of it. If the obstacle is gone and the distance is above 15 cm it will break this loop and begin to go straight again.