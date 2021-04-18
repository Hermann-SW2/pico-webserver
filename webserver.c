#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "tusb_lwip_glue.h"

void core1_entry()
{
    // Initialize tinyusb, lwip, dhcpd and httpd
    init_lwip();
    wait_for_netif_is_up();
    dhcpd_init();
    httpd_init();

    while (true)
    {
        tud_task();
        service_traffic();
    }
}

int main()
{
    sys_timeouts_init();

    multicore_launch_core1(core1_entry);

    while (true)
        tight_loop_contents();

    return 0;
}
