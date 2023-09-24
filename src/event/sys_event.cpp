#include "sys_event.h"
#include <bits/stdc++.h>


/**
 * @brief 
 * 
 * @param event_name 
 * @param queue 
 */
void Event::register_event(const char* event_name, k_msgq* queue ) 
{
    // Find the index of the event name in the subscribers_array_ array
    uint32_t index = std::find(m_reg_events.begin(), 
                               m_reg_events.end(), 
                               event_name) - m_reg_events.begin();

    // If the event name is not found, create a new entry for it
    if (index == m_reg_events.size()) 
    {
      m_reg_events.push_back(event_name);
      m_reg_events_array[index] = queue;
    } 
    else 
    {
      // Update the subscriber callback for the existing event name
      m_reg_events_array[index] = queue;
    }
}

k_msgq* Event::get_event(const char* event_name)
{
    
   uint32_t index = std::find(m_reg_events.begin(), 
                               m_reg_events.end(), 
                               event_name) - m_reg_events.begin();
    // If the event name is not found, create a new entry for it
    if (index == m_reg_events.size()) 
    {
        return (k_msgq*)nullptr;
    } 
    else 
    {
      return m_reg_events_array[index];
    }

    
}