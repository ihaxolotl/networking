#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "ip.h"

static const unsigned char TEST_IPV4_BYTES[20] = {
    0x45, 0x0,  0x0,  0x54, 0x85, 0x82, 0x40, 0x0, 0x40, 0x1,
    0xb7, 0x24, 0x7f, 0x0,  0x0,  0x1,  0x7f, 0x0, 0x0,  0x1,
};

static unsigned char TEST_IPV4_BYTES_2[20] = {0};

void hexdump(const void *bytes, unsigned int length, unsigned int cols)
{
    for (unsigned int i = 0;
         i < length + ((length % cols) ? (cols - length % cols) : 0); i++) {
        if (i % cols == 0) {
            printf("0x%06x: ", i);
        }
        if (i < length) {
            printf("%02x ", 0xFF & ((unsigned char *)bytes)[i]);
        } else {
            printf("   ");
        }
        if (i % cols == (cols - 1)) {
            for (unsigned int j = i - (cols - 1); j <= i; j++) {
                if (j >= length) {
                    putchar(' ');
                } else if (isprint(((unsigned char *)bytes)[j])) {
                    putchar(0xFF & ((unsigned char *)bytes)[j]);
                } else {
                    putchar('.');
                }
            }
            putchar('\n');
        }
    }
}

int main(void)
{
    int rc = -1;
    struct ipv4_header header;

    rc = ipv4_parse_header(TEST_IPV4_BYTES, sizeof(TEST_IPV4_BYTES), &header);
    if (rc < 0) {
        printf("Could not parse IPv4 header!\n");
        return EXIT_FAILURE;
    }

    ipv4_dump_header(&header);
    ipv4_build_header(&header, TEST_IPV4_BYTES_2, sizeof(TEST_IPV4_BYTES));

    hexdump(TEST_IPV4_BYTES, sizeof(TEST_IPV4_BYTES), 16);
    hexdump(TEST_IPV4_BYTES_2, sizeof(TEST_IPV4_BYTES_2), 16);

    return EXIT_SUCCESS;
}
