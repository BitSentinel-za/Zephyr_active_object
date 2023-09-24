#include <iostream>
#include <cstdint>

#include "control_thread.h"
#include "app_main.h"
#include "sys_event.h"


int main(void)
{

    Event main_event;
    app_main("app_main/", 5U, 500U , &main_event);

    return 0;
}

