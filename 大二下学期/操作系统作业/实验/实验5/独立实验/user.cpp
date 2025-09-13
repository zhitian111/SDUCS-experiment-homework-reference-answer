#include "common.h"
#include <cstdlib>
#include <ctime>
#include <thread>
double money_for_haircut = 10.0;
bool is_closed = false;
bool end_consumption = false;
void check_is_barber_closed()
{
  while (true)
  {
    sleep(1);
    int status = 1;
    is_closing.read(status);
    if (status == 1)
    {
      is_closed = true;
      break;
    }
  }
}
void consume()
{
  log() << "spawned" << std::endl;
  is_someone_is_entrying.down();
  int customer_count;
  barber_shop_capacity.read(customer_count);
  log() << "customer_count: " << customer_count << std::endl;
  int status = 0;
  is_closing.read(status);
  if (status != 666)
  {
    log() << "barber shop is closed, cannot enter" << std::endl;
    return;
  }

  if (customer_count >= BARBERSHOP_SIZE)
  {
    log() << "too many customers, this customer leaves" << std::endl;
    return;
  }
  else
  {
    log() << "capacity available, customer enters" << std::endl;
    new_customer_come.up();
    new_customer_in.down();
    for_sys_key_cnt.read(key_cnt);
    log() << "key_cnt: " << key_cnt << std::endl;
    user_sems local_user;
    is_someone_is_entrying.up();
    local_user.wait_for_move_to_sofa();
    log() << "customer is seated" << std::endl;
    log() << "customer is ready to cut hair" << std::endl;
    local_user.wait_for_get_service();
    log() << "customer finished getting hair cut" << std::endl;
    log() << "customer is waiting for payment" << std::endl;
    local_user.wair_for_give_money();
    is_someone_is_paying.down();
    money_trade_buffer.write(money_for_haircut);
    is_someone_is_paying.up();
    the_man_who_is_paying_is_done.up();
    log() << "customer paid: " << money_for_haircut << std::endl;
    log() << "customer is leaving" << std::endl;
    int current_customer_count;
    barber_shop_capacity.read(current_customer_count);
    current_customer_count--;
    barber_shop_capacity.write(current_customer_count);
    end_consumption = true;
  }
}
void run()
{
  std::thread check_is_barber_closed_thread(check_is_barber_closed);
  check_is_barber_closed_thread.detach();
  std::thread consume_thread(consume);
  consume_thread.detach();
  while (true)
  {
    if (end_consumption)
    {
      break;
    }
    if (is_closed)
    {
      log() << "barber shop is closed, have to end consumption" << std::endl;
      break;
    }
  }
}

int main()
{
  try
  {
    std::srand(std::time(0));
    double random_number = (std::rand() / (RAND_MAX + 1.0)) * 20.0;
    money_for_haircut = random_number;
    run();
  }
  catch (std::exception& e)
  {
    log() << e.what() << std::endl;
  }
  return 0;
}
