#ifndef _CONTROL_H_
#define _CONTROL_H_


#include <vector>
#include <iostream>
#include <array>
#include <cstdint>
#include <string>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/logging/log.h>

#include <esp_spi_flash.h>
#include <soc.h>

#include "sys_event.h"


#define STACK_SIZE 500
#define PRIORITY 5
#define MAX_EVENTS 10

class control_thread {
public:

  control_thread(char* name, uint32_t priority, uint32_t stack_size, Event* event);
  

protected:

  void Subscribe(const char* event_name);
  void PostEvent(void* event);
  void register_event(const char* event_name);

  virtual void run() = 0;
  virtual void init() = 0;

private:

  static void task_fn(void* obj, void*, void*) 
  {
      reinterpret_cast<control_thread*>(obj)->run();
  }

  k_tid_t m_tid;
  k_msgq m_queue;
  struct k_thread my_thread_data;

  // Array of event names
  std::vector<std::string> event_names;

  // Array of subscriber callbacks
  std::array<k_msgq*, MAX_EVENTS> subscribers_array; // Assuming a maximum of 10 subscribers

  Event* m_event;
  uint16_t m_index{0};
};

#endif