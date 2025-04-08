def create_or_write_file():
    file_name = input("请输入文件名：")

    try:
        f = open(file_name, 'a')  # 以追加模式打开文件
    except IOError:
        print("文件打开失败")
        return

    while True:
        content = input("请输入文件内容：")

        try:
            f.write(content + "\n")  # 写入文件内容
        except IOError:
            print("写入文件失败")
            f.close()
            return

        choice = input("是否继续输入内容？(y/n)")
        if choice.lower() != 'y':
            break

    f.close()
    print("文件写入成功")


create_or_write_file()