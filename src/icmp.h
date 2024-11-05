#ifndef __NETEXP_ICMP_H__
#define __NETEXP_ICMP_H__

#include <stddef.h>

struct icmp_header {
    unsigned char type;
    unsigned char code;
    unsigned short checksum;
    union {
        struct {
            unsigned short id;
            unsigned short sequence;
        } echo;
        unsigned int gateway;
        struct {
            unsigned short __unused;
            unsigned short mtu;
        } frag;
    } un;
};

extern void icmp_dump(const struct icmp_header *header,
                      const unsigned char *payload, size_t payload_length);

#endif
