producer_process_name="producer"
if [ -f log.txt ] ; then
  echo "log.txt already exists. Do you want to overwrite it?(y/n)"
    read answer
    if [ $"answer" = "y" ] ; then
      rm log.txt
    fi
fi
touch log.txt
# if ! pgrep "$producer_process_name" >> ./log.txt ; then
#   ./producer 1 > /dev/null &
# fi
./producer >> ./log.txt &
./producer >> ./log.txt &
./consumer -t 0 >> ./log.txt &
./consumer -t 1 >> ./log.txt &
./consumer -t 2 >> ./log.txt &
echo "All processes started successfully\n"
ps | grep producer
ps | grep consumer
