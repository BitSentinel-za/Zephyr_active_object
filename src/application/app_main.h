#ifndef APP_MAIN_H
#define APP_MAIN_H

#include "control_thread.h"


class app_main : public control_thread
{
    public:
        app_main(char* name, 
                 uint32_t priority, 
                 uint32_t stack_size, 
                 Event* event): control_thread(name, priority, stack_size, event){}
    protected:

    private:
        void run() override 
        {
            while (1) 
            {
                // task code goes here

            }
        }


};

#endif
