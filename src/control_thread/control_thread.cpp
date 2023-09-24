#include <bits/stdc++.h>
#include "control_thread.h"

K_THREAD_STACK_DEFINE(threadStack, STACK_SIZE);

/**
 * @brief Construct a new control thread::control thread object
 * 
 * @param name 
 * @param priority 
 * @param stack_size
 * @param Events 
 */
control_thread::control_thread(char* name, uint32_t priority, 
                               uint32_t stack_size, Event* event):m_event{event}
{
   m_tid = k_thread_create(&my_thread_data, threadStack,
                           K_THREAD_STACK_SIZEOF(threadStack),
                           control_thread::task_fn,
                           this, NULL, NULL,
                           PRIORITY, 0, K_NO_WAIT);
}


/**
 * @brief 
 * 
 * @param event 
 */
void control_thread::PostEvent(void* event) 
{
  for (auto i: subscribers_array)
  {
    k_msgq_put(i, event, K_FOREVER);
  }
}


/**
 * @brief 
 * 
 * @param event_name 
 */
void control_thread::Subscribe(const char* event_name) 
{
  auto evt = m_event->get_event(event_name);

  if (evt == nullptr)
  {
    //TODO: cause exception
  }
  else
  {
    subscribers_array[m_index++] = evt;
  }
}

void control_thread::register_event(const char* event_name)
{
  m_event->register_event(event_name, &m_queue);
}