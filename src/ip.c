#include <arpa/inet.h>
#include <stdio.h>

#include "ip.h"

void ipv4_format(const unsigned char bytes[4], char *buf, size_t buflen)
{
    snprintf(buf, buflen, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2],
             bytes[3]);
}

void ipv4_dump(const struct ipv4_header *header)
{
    char dstaddr[20], srcaddr[20];

    ipv4_format((unsigned char *)&header->src_addr, srcaddr, sizeof(srcaddr));
    ipv4_format((unsigned char *)&header->dst_addr, dstaddr, sizeof(dstaddr));

    fprintf(stderr, "Internet Protocol Version 4\n");
    fprintf(stderr, "  | Version: %u\n", header->version);
    fprintf(stderr, "  | Internet Header Length: %u bytes (%u)\n",
            header->ihl * 4, header->ihl);
    fprintf(stderr, "  | Type Of Service: %u\n", header->tos);
    fprintf(stderr, "  | Total Length: %u bytes\n",
            ntohs(header->total_length));
    fprintf(stderr, "  | Identification: %u\n", ntohs(header->id));
    fprintf(stderr, "  | Time To Live: %u\n", header->ttl);
    fprintf(stderr, "  | Protocol: %u\n", header->protocol);
    fprintf(stderr, "  | Header Checksum: 0x%4x\n", ntohs(header->checksum));
    fprintf(stderr, "  | Source IP: %s\n", srcaddr);
    fprintf(stderr, "  | Destination IP: %s\n", dstaddr);
}
