# Solution to Sleeping Barber Problem

*This soulution is build in Visual Studio 2017 in Windows, which includes three files that one header file and two cpp files.*

## Solution Description

I create two classes, one is Barber, the other is Customer, each one simulates its object. I use three locks here to prevent the resource race, one for controlling barbar's sleeping, one for controlling how many customer sit in the waiting room and another for printing the states of barber, customer and waiting room. Although less lock is good to avoid deadlock, I think three locks is needed here.

Another thing I want to explain is that the important things about customer is its ID ,waiting order and whether he comes or not in this problem. In other words, I just want to know three things about customers that listing above, if I were the barber. So, when the customer thread pass this three parameter to the barber it was done.

## Implementation Details

Please input the number of waiting chairs at first.

The time of cutting hair and new customer generating is set according to the requirement, where cutting hair needs [1:5] seconds and new customer arrives every 3 seconds. But you can find and change them in "barbershop.cpp" at line 41 and line 109.

## Output

The first customer will arrive 3 seconds later at first. And note that please be patient, it may take 2 to 3 minutes to see all three cases listing below.

---

**Case 1**

No customer arrives and barber is sleeping at first. 

```
Barber sleeping
Waiting room:
```

---

**Case 2**

The barber is cutting the hair of customer 20 and customers 21, 22, 23, 24 are waiting.

```
Barber cutting the hair of customer 20
Waiting room : 21  22  23  24
```

---

**Case 3**

The barber is cutting the hair of customer 23 and customers 24 to 28 are waiting, but customer 29 leaving with no avaliable seats in waiting room.

```
Barber cutting the hair of customer 23
Waiting room : 24  25  26  27  28
Customer 29 leaving
```

---
## The Next

I am working on implementing a base class called "Barbershop", and "Barber" and "Customer" become its derived class. So they may share information in the base class instead of setting global variables.

> If you have any specific questions, please contact me at clu12@stevens.edu.
