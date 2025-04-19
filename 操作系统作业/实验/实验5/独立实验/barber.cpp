#include "common.h"
#include <exception>
#include <iostream>
#include <thread>
#include <unistd.h>
bool is_working = false;

void provide_service()
{
  while (true)
  {
    if (is_working)
    {
      continue;
    }
    needed_services_cnt.down();
    log() << "barber is providing a service..." << std::endl;
    is_working = true;
    sleep(BARBER_BARBE_TIME_INTERVAL);
    barber_finish_service.up();
    is_working = false;
  }
}

void cashier_service()
{
  while (true)
  {
    if (is_working)
    {
      continue;
    }
    needed_pay_money_cnt.down();
    is_someone_is_receiving_money.down();
    log() << "barber is taking money..." << std::endl;
    is_working = true;
    sleep(CASHIER_CASH_TIME_INTERVAL);
    barber_finish_receive_money.up();
    is_someone_is_receiving_money.up();
    is_working = false;
  }
}

void have_a_break()
{
  static bool is_resting = false;
  while (true)
  {
    sleep(REST_CHECK_TIME_INTERVAL);
    if (!is_working && !is_resting)
    {
      is_resting = true;
      log() << "barber taking a break..." << std::endl;
    }
    if (is_resting && is_working)
    {
      is_resting = false;
      log() << "barber stopped resting..." << std::endl;
    }
  }
}
bool is_closed = false;
void check_is_barber_closed()
{
  while (true)
  {
    sleep(1);
    int status = 1;
    is_closing.read(status);
    if (status != 666)
    {
      is_closed = true;
    }
  }
}

void run()
{
  log() << "barber came to work..." << std::endl;
  int status = 0;
  is_closing.read(status);
  if (status != 666)
  {
    log() << "barbershop is closed, barber is leaving..." << std::endl;
    return;
  }
  std::thread provide_service_thread(provide_service);
  std::thread cashier_service_thread(cashier_service);
  std::thread have_a_break_thread(have_a_break);
  std::thread check_is_barber_closed_thread(check_is_barber_closed);
  provide_service_thread.detach();
  cashier_service_thread.detach();
  have_a_break_thread.detach();
  check_is_barber_closed_thread.detach();
  while (!is_closed)
  {
    sleep(1);
  }
  log() << "barbershop is closed, barber is leaving..." << std::endl;
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
}
