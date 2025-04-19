#include "common.h"
#include <chrono>
#include <cmath>
#include <thread>
#include <unistd.h>

static std::queue<service_sems*> wait_room_queue;
static std::queue<service_sems*> sofa_queue;
static std::queue<service_sems*> cashier_queue;
static std::queue<service_sems*> barber_queue;
bool is_ending = false;
void customer_receiver()
{
  log() << "customer receiver start running..." << std::endl;
  while (true)
  {
    sleep(RECEIVER_TIME_INTERVAL);
    new_customer_come.down();
    new_customer_in.up();
    for_sys_key_cnt.write(key_cnt);
    log() << "key_cnt: " << key_cnt << std::endl;
    auto service_obj = new service_sems;
    wait_room_queue.push(service_obj);
    int current_customer_cnt = 0;
    barber_shop_capacity.read(current_customer_cnt);
    current_customer_cnt++;
    barber_shop_capacity.write(current_customer_cnt);
    log() << "customer received and moved to wait room"
          << " id: " << service_obj->get_id() << std::endl;
    log() << "current customer count: " << current_customer_cnt << std::endl;
  }
}

void customer_mover()
{
  log() << "customer mover start running..." << std::endl;
  while (true)
  {
    sleep(MOVER_MOVE_TIME_INTERVAL);
    if (sofa_queue.size() < SOFA_SIZE)
    {
      if (!wait_room_queue.empty())
      {
        sofa_queue.push(wait_room_queue.front());
        wait_room_queue.front()->let_user_move_to_sofa();
        log() << "customer moved to sofa"
              << " id: " << wait_room_queue.front()->get_id() << std::endl;
        wait_room_queue.pop();
      }
    }
  }
}

void cashier_mover()
{
  log() << "cashier mover start running..." << std::endl;
  while (true)
  {
    sleep(CASHIER_CASH_TIME_INTERVAL);
    if (!sofa_queue.empty())
    {
      barber_finish_service.down();
      cashier_queue.push(sofa_queue.front());
      cashier_queue.front()->support_service_for_user();
      log() << "customer finished service and moved to cashier"
            << " id: " << sofa_queue.front()->get_id() << std::endl;
      sofa_queue.pop();
    }
  }
}

void cashier_receiver()
{
  log() << "cashier receiver start running..." << std::endl;
  while (true)
  {
    if (!cashier_queue.empty())
    {
      sleep(RECEIVER_TIME_INTERVAL);
      barber_finish_receive_money.down();
      cashier_queue.front()->let_user_pay_money();
      log() << "customer paid money"
            << " id: " << cashier_queue.front()->get_id() << std::endl;
      cashier_queue.pop();
      the_man_who_is_paying_is_done.down();
      double received_money = 0;
      double current_money = 0;
      money_trade_buffer.read(received_money);
      sum_money.read(current_money);
      current_money += received_money;
      sum_money.write(current_money);
      log() << "received money: " << received_money << std::endl;
      log() << "current money: " << current_money << std::endl;
      barber_finish_receive_money.up();
    }
  }
}

void shop_running_timer()
{
  log() << "shop running timer start running..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(SHOP_RUNNING_TIME));
  is_ending = true;
  is_closing.write(1);
}

void run()
{
  barber_shop_capacity.write(0);
  int status = 666;
  is_closing.write(status);
  log() << "barbershop start running..." << std::endl;
  std::thread customer_receiver_thread(customer_receiver);
  std::thread customer_mover_thread(customer_mover);
  std::thread cashier_mover_thread(cashier_mover);
  std::thread cashier_receiver_thread(cashier_receiver);
  std::thread shop_running_timer_thread(shop_running_timer);
  customer_mover_thread.detach();
  customer_receiver_thread.detach();
  cashier_mover_thread.detach();
  cashier_receiver_thread.detach();
  shop_running_timer_thread.detach();
  while (true)
  {
    if (is_ending)
    {
      log() << "barbershop is closing..." << std::endl;
      break;
    }
  }
}

int main()
{
  try
  {
    run();
  }
  catch (std::exception& e)
  {
    log() << e.what() << std::endl;
  }
  return 0;
}
