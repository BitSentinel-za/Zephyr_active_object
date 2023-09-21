#ifndef _CONTROL_H_
#define _CONTROL_H_


#include <vector>
#include <iostream>
#include <array>
#include <cstdint>
#include <string>


#include <zephyr/kernel.h>
// #include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
// #include <zephyr/sys/printk.h>
// #include <zephyr/sys/__assert.h>

#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#include <esp_spi_flash.h>
#include <soc.h>

#include <zephyr/logging/log.h>


#define STACK_SIZE 500
#define PRIORITY 5
#define MAX_EVENTS 10

/*

extern void my_entry_point(void *, void *, void *);

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);

*/

class control_thread {
public:

  control_thread(char* name, uint32_t priority, uint32_t stack_size);
  virtual void run() = 0;
  void Subscribe(const char* event_name, void (*callback)(void));
  void PostEvent(uint32_t event);  

private:

  static void task_fn(void* obj, void*, void*) 
  {
      reinterpret_cast<control_thread*>(obj)->run();
  }

  k_tid_t m_tid;
  k_msgq m_queue_;
  struct k_thread my_thread_data;

  // Array of event names
  std::vector<std::string> event_names_;

  // Array of subscriber callbacks
  std::array<void(*)(void), MAX_EVENTS> subscribers_array_; // Assuming a maximum of 10 subscribers
};

#endif