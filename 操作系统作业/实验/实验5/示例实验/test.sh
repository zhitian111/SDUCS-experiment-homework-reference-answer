#!/bin/bash
mkdir 实验日志 2>/dev/null >> /dev/null
echo -e "启用make clean命令\n"
make clean 2>/dev/null
echo -e "编译程序\n"
make 2>/dev/null

touch control_log.txt
touch writer_log.txt
touch reader1_log.txt
touch reader2_log.txt


current_time=$(date "+%Y-%m-%d-%H-%M-%S")
mkdir $current_time
mkdir 标准运行测试
echo -e "开始进行标准运行测试\n"


./control >>./control_log.txt&
echo -e "已启动control进程\n"
ps | grep control

./reader 10 >>./reader1_log.txt&
./reader 1 >>./reader2_log.txt&
echo -e "已启动reader1进程和reader2进程\n"
ps | grep reader

echo -e "等待5秒后启动writer进程\n"
sleep 5

./writer 8 >>./writer_log.txt&

echo -e "controler , writer , reader1 , reader2 process start!\n"
ps | grep controler
ps | grep writer
ps | grep reader
echo -e "\n"

echo -e "等待10秒后杀掉writer进程\n"
sleep 10

./endtest.sh

echo -e "标准运行测试结束\n"

mv control_log.txt 标准运行测试
mv writer_log.txt 标准运行测试
mv reader1_log.txt 标准运行测试
mv reader2_log.txt 标准运行测试
mv 标准运行测试 $current_time
echo -e "实验日志已保存至 $current_time 目录下\n"


echo -e "---------------分割线---------------\n"


echo -e "开始进行随机读写测试\n"

random_test_time=$((RANDOM%10+10))
echo -e "随机读写测试将持续 $random_test_time 秒(每秒随机创建读写进程)\n"

touch control_log.txt
./control >> ./control_log.txt&
echo -e "已启动control进程\n"
ps | grep control

touch writer_log.txt
touch reader_log.txt
for i in $(seq 1 $random_test_time)
do 
    sleep 1
    random_num=$((RANDOM%2+1))
    if [ $random_num -eq 1 ]
    then
        echo -e "随机创建writer进程\n"
        random_writer_time=$((RANDOM%8+1))
        echo -e "启动进程 ./writer $random_writer_time >> ./writer_log.txt&\n"
        ./writer $random_writer_time >>./writer_log.txt&
    else
        echo -e "随机创建reader进程\n"
        random_reader_time=$((RANDOM%8+1))
        echo -e "启动进程 ./reader $random_reader_time >> ./reader_log.txt&\n"
        ./reader $random_reader_time >>./reader_log.txt&
    fi
done
echo -e "writer , reader process start!\n"
ps | grep writer
ps | grep reader
echo -e "\n"
random_test_time=$((RANDOM%10+5))
echo -e "等待 $random_test_time 秒后结束测试\n"
sleep $random_test_time

./endtest.sh
echo -e "随机读写测试结束\n"
mkdir 随机读写测试
mv control_log.txt 随机读写测试
mv writer_log.txt 随机读写测试
mv reader_log.txt 随机读写测试
mv 随机读写测试 $current_time
echo -e "实验日志已保存至 $current_time 目录下\n"


echo -e "---------------分割线---------------\n"
echo -e "开始进行进程饥饿测试\n"
touch control_log.txt
./control >>./control_log.txt&
echo -e "已启动control进程\n"
ps | grep control
touch writer_log.txt
./writer 8 >>./writer_log.txt&
echo -e "已启动writer进程\n"
ps | grep writer
touch reader1_log.txt
./reader 10 >>./reader1_log.txt&
touch reader2_log.txt
./reader 1 >>./reader2_log.txt&
echo -e "已启动reader1进程和reader2进程\n"
ps | grep reader
echo -e "等待10秒后杀掉writer进程\n"
sleep 10
./endtest.sh
echo -e "进程饥饿测试结束\n"
mkdir 进程饥饿测试
mv control_log.txt 进程饥饿测试
mv writer_log.txt 进程饥饿测试
mv reader1_log.txt 进程饥饿测试
mv reader2_log.txt 进程饥饿测试
mv 进程饥饿测试 $current_time
echo -e "实验日志已保存至 $current_time 目录下\n"
echo -e "---------------分割线---------------\n"
echo -e "实验结束\n"
mv $current_time 实验日志
echo -e "实验日志已保存至 实验日志 目录下\n"
