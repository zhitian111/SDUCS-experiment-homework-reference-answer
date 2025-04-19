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
touch barber.log
touch user.log
echo -e "启动测试...\n\n"

current_time=$(date "+%Y-%m-%d-%H-%M-%S")
mkdir $current_time
echo -e "拉起理发店进程...\n"

./barbershop >> barbershop.log 2>> barbershop.log &

echo -e "拉起理发师进程...\n"
./barber >> barber.log 2>> barber.log &

echo -e "以下为测试中固定使用的进程：\n"
ps | grep barber
ps | grep barbershop

echo -e "开始随机唤起顾客进程...\n"
for i in $(seq 1 15); do
  echo -e "拉起顾客进程 $i...\n"
  ./user $i >> user.log 2>> user.log &
  sleep 1
done
mv *.log $current_time/
mv $current_time 实验日志
echo -e "测试结束，请查看日志文件。\n\n"
