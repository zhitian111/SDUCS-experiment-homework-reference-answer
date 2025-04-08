username=str(input("please enter your username : "))
password=str(input("please enter your password : "))
if username=='admin' and password=='12345':
    print("认证成功")
else:
    print("认证失败")