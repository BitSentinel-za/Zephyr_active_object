#include "control_thread.h"
#include <bits/stdc++.h>

K_THREAD_STACK_DEFINE(threadStack, STACK_SIZE);

control_thread::control_thread(char* name, uint32_t priority, uint32_t stack_size)
{
   m_tid = k_thread_create(&my_thread_data, threadStack,
                           K_THREAD_STACK_SIZEOF(threadStack),
                           control_thread::task_fn,
                           this, NULL, NULL,
                           PRIORITY, 0, K_NO_WAIT);
}

void control_thread::PostEvent(uint32_t event) 
{
  k_msgq_put(&m_queue_, &event, K_FOREVER);
}

void control_thread::Subscribe(const char* event_name, void (*callback)(void)) 
{
    // Find the index of the event name in the subscribers_array_ array
    uint32_t index = std::find(event_names_.begin(), 
                               event_names_.end(), 
                               event_name) - event_names_.begin();

    // If the event name is not found, create a new entry for it
    if (index == event_names_.size()) 
    {
      event_names_.push_back(event_name);
      subscribers_array_[index] = callback;
    } 
    else 
    {
      // Update the subscriber callback for the existing event name
      subscribers_array_[index] = callback;
    }
}