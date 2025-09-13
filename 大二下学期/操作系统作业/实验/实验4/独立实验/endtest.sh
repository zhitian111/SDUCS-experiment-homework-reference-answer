if ! ps | grep -q producer || ! ps | grep -q consumer; then
  echo "No producer or consumer process found."
  exit 1
fi
echo "these following processes will be killed:\n"

ps | grep producer
ps | grep consumer

pkill -f "producer"
pkill -f "consumer"

echo "Done."
