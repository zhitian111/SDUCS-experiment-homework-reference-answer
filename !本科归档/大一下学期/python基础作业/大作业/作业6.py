age=eval(input("Please enter the age: "))
if age<18:
    print("未成年人")
elif age>=18 and age<=65:
    print("成年人")
else:
    print("老年人")