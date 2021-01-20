## Author: Jonathan Macias
## Email: jonathanpj777@gmail.com
## Date: 01/07/2020
## License: MTI
---
# Project: Multisensor Car

This project uses 3 of the same ultrasonic sensors as the single sensor car. With these 3 it once again takes the distance of whatever may be in front of it and deicdes which direction to turn. With 3 sensors it can better decide as it has a front, left, and right value now.

---

## Requirements

For this project, you should probably have gone through the other 2 Arduino documents as there's only one thing I'll be going over.

---

## Functions with Returns

The only thing I feel I need to highlight that hasn't been mentioned in the other sets of code is functions that return values. They were not used in either of the codes but here I thought it was most efficient too. In another README I mentioned that the first word when making a function, in most cases you've seen me use "void" indicates return type. Void returns nothing but you can return any data type. This means that when you call the function, it will give a value back in return.

The benefits to using return values in functions is that if your funciton is doing something such as mine which finds out the distance of something. Rather than creating a variable and putting it into the function and having the function change it which can cause some issues, you set the variable equal to the function like we did here: 

```
distanceF = pingDistance(trigPinFront, echoPinFront);)
```

The thing about having a return value is somewhere in the code of the function, you need to make sure that some value of the same datatype gets returned. In our case it's this piece of code 
```
return distance;
```

The function calculates that distance value and it gets sent back, making distanceF equal to that.