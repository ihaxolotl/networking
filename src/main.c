#include "ip.h"

int main(void)
{
    const unsigned char bytes[] = {
        0x45, 0x0,  0x0,  0x54, 0x85, 0x82, 0x40, 0x0, 0x40, 0x1,
        0xb7, 0x24, 0x7f, 0x0,  0x0,  0x1,  0x7f, 0x0, 0x0,  0x1,
    };

    ipv4_dump((struct ipv4_header *)bytes);

    return 0;
}
