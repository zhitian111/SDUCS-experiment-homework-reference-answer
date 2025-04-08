f=open("my_file.txt",'w')
f.write("Hello,World!\n")
f.close()
f=open("my_file.txt",'r')
for i in f:
    print(i)

f.close()
f=open("my_file.txt","a")
f.write("This is a file operation example.")
f.close()
f=open("my_file.txt","r")
print(f.readline(),end='')
print(f.readline())