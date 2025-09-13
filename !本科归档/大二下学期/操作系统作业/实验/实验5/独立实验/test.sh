#!/bin/bash


mkdir 实验日志 2>/dev/null >> /dev/null
echo -e "Testing start runnning...\n\n"

make clean > /dev/null 2>/dev/null

echo -e "创建测试环境...\n\n"

echo -e "需要先清空ipc文件，否则可能导致测试失败。是否继续？(y/n)"
read choice
if [ "$choice" == "y" ]; then
  ipcrm -a
else
  echo -e "测试环境创建失败，请检查系统环境。\n\n"
  exit 1
fi


make all
touch barbershop.log
touch barber1.log
touch barber2.log
touch barber3.log
echo -e "启动测试...\n\n"

current_time=$(date "+%Y-%m-%d-%H-%M-%S")
mkdir $current_time
echo -e "拉起理发店进程...\n"

./barbershop >> barbershop.log 2>> barbershop.log &

echo -e "拉起理发师进程...\n"
./barber >> barber1.log 2>> barber1.log &
./barber >> barber2.log 2>> barber2.log &
./barber >> barber3.log 2>> barber3.log &

echo -e "以下为测试中固定使用的进程：\n"
ps | grep barber
ps | grep barbershop

echo -e "开始随机唤起顾客进程...\n"
echo -e "注意测试仅持续20秒，且顾客进程会在每1秒随机唤起随机数量(0-6)。若需要持续测试，请自行修改脚本。"

user_cnt=0 # 总数，用于修改日志文件名

for i in {1..20}
do
    random_num=$((RANDOM%7)) 
    for j in $(seq 1 $random_num)
    do
        user_cnt=($((user_cnt+1)))
        echo -e "唤起顾客进程 $user_cnt...\n"
        ./user >> $current_time/user$user_cnt.log 2>> $current_time/user$user_cnt.log &
    done
    sleep 1
done
sleep 2
echo -e "测试结束，请查看日志文件。\n\n"
./endtest.sh

mv *.log $current_time/ 2>/dev/null >> /dev/null
mv $current_time 实验日志/ 2>/dev/null >> /dev/null
