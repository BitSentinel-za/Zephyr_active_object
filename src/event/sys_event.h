#ifndef SYS_EVENT_H
#define SYS_EVENT_H

#include <array>
#include <vector>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/logging/log.h>

#define STORED_MAX_EVENTS 100

typedef struct sys_evt
{
    int event_size;
    void* data;

}sys_evt_t; 

class Event 
{
public:
  Event(){}
  void register_event(const char* event_name, k_msgq* queue );
  k_msgq* get_event(const char* event_name);

private:
  //TODO: Need to find a more static way to store the strings
  std::vector<const char*> m_reg_events;
  std::array<k_msgq*, STORED_MAX_EVENTS> m_reg_events_array;
  

};

#endif
