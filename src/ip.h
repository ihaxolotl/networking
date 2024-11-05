#ifndef __NETEXP_IP_H__
#define __NETEXP_IP_H__

#include <stddef.h>

struct ipv4_address {
    union {
        unsigned int integer;
        unsigned char bytes[4];
    } as;
};

struct ipv4_header {
    unsigned char vhl;
    unsigned char tos;
    unsigned short total_length;
    unsigned short id;
    unsigned short fragment_offset;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short checksum;
    struct ipv4_address source;
    struct ipv4_address destination;
};

enum ipv4_status {
    IPV4_OK = 0,
    IPV4_INVALID = 1,
};

extern void ipv4_format(const struct ipv4_address *address, char *buf,
                        size_t buflen);
extern int ipv4_parse_header(const unsigned char bytes[], size_t length,
                             struct ipv4_header *header);
extern int ipv4_build_header(const struct ipv4_header *header,
                             unsigned char bytes[], size_t length);
extern void ipv4_dump_header(const struct ipv4_header *header);

#endif
