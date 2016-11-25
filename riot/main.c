#include <stdio.h>
#include "xtimer.h"

extern void coap_server_loop(void);
extern int _netif_config(int argc, char **argv);

int main(void)
{
    puts("RIOT libcoap example application");
    puts("Waiting for address autoconfiguration...");
    xtimer_sleep(3);
    puts("Configured network interfaces:");
    _netif_config(0, NULL);
    puts("CoAP server will be initialized");
    coap_server_loop();
    return 0;
}
