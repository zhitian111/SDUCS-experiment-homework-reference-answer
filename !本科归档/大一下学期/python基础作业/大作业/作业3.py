class book:
    name=''
    author=''
    data=0
    check=1
    def __init__(self,name,author,data):
        self.name=name
        self.author=author
        self.data=data
        self.check=1
    #借书
    def borrow(self):
        self.check=0
    #还书
    def back(self):
        self.check=1
    def display(self):
        print(self.name,
                  self.author,
                  self.data,end=' ')
        if self.check==1:
            print("可借阅")
        else:
            print("已借出")

#测试
book1=book('三体','刘慈欣',2024)
book1.display()
book1.borrow()
book1.display()
book1.back()
book1.display()