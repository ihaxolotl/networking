#include <arpa/inet.h>
#include <stdio.h>

#include "icmp.h"

void icmp_dump(const struct icmp_header *header, const unsigned char *payload,
               size_t payload_length)
{
    fprintf(stderr, "Internet Control Message Protocol\n");
    fprintf(stderr, "  | Type: %u\n", header->type);
    fprintf(stderr, "  | Code: %u\n", header->code);
    fprintf(stderr, "  | Checksum: 0x%04x\n", ntohs(header->checksum));
    fprintf(stderr, "  | Identifier: 0x%04x\n", ntohs(header->un.echo.id));
    fprintf(stderr, "  | Sequence Number: 0x%04x\n",
            ntohs(header->un.echo.sequence));

    fprintf(stderr, "\n");
}
