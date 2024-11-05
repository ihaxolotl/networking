#ifndef __NETEXP_IP_H__
#define __NETEXP_IP_H__

#include <stddef.h>

struct ipv4_header {
    unsigned char ihl : 4;
    unsigned char version : 4;
    unsigned char tos;
    unsigned short total_length;
    unsigned short id;
    unsigned short fragment_offset;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short checksum;
    unsigned int src_addr;
    unsigned int dst_addr;
};

extern void ipv4_format(const unsigned char bytes[4], char *buf, size_t buflen);
extern void ipv4_dump(const struct ipv4_header *header);

#endif
