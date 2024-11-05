#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#include "ip.h"

#define IPV4_HEADER_LENGTH_MIN (20)
#define IPV4_HEADER_LENGTH_MAX (0xf * 4)

/**
 * Format an IPv4 address structure to a NULL-teriminated string.
 */
void ipv4_format(const struct ipv4_address *address, char buf[], size_t buflen)
{
    snprintf(buf, buflen, "%d.%d.%d.%d", address->as.bytes[0],
             address->as.bytes[1], address->as.bytes[2], address->as.bytes[3]);
}

static unsigned short read_u16_be(unsigned char a, unsigned char b)
{
    return (unsigned short)(b | a << 8);
}

static unsigned int read_u32_le(const unsigned char data[])
{
    unsigned int value;

    memcpy(&value, data, sizeof(value));

    return value;
}

/**
 * Deserialize an IPv4 packet header from raw bytes.
 */
int ipv4_parse_header(const unsigned char bytes[], size_t length,
                      struct ipv4_header *header)
{
    unsigned char version, ihl, tos, ttl, protocol;
    unsigned short total_length, id, fragment_offset, checksum;
    unsigned int src_addr, dst_addr;

    if (length < IPV4_HEADER_LENGTH_MIN)
        return -IPV4_INVALID;

    version = bytes[0] >> 4;
    ihl = bytes[0] & 0xf;

    if (version != 4 || ihl < 5)
        return -IPV4_INVALID;

    if (ihl * 4 > IPV4_HEADER_LENGTH_MAX)
        return -IPV4_INVALID;

    tos = bytes[1];
    total_length = read_u16_be(bytes[2], bytes[3]);
    id = read_u16_be(bytes[4], bytes[5]);
    fragment_offset = read_u16_be(bytes[6], bytes[7]);
    ttl = bytes[8];
    protocol = bytes[9];
    checksum = read_u16_be(bytes[10], bytes[11]);
    src_addr = read_u32_le(bytes + 12);
    dst_addr = read_u32_le(bytes + 16);

    header->version = version;
    header->ihl = ihl;
    header->tos = tos;
    header->total_length = total_length;
    header->id = id;
    header->fragment_offset = fragment_offset;
    header->ttl = ttl;
    header->protocol = protocol;
    header->checksum = checksum;
    header->source.as.integer = src_addr;
    header->destination.as.integer = dst_addr;

    return IPV4_OK;
}

/**
 * Serialize an IPv4 packet header into raw bytes.
 */
int ipv4_build_header(const struct ipv4_header *header, unsigned char bytes[],
                      size_t length)
{
    if (length < IPV4_HEADER_LENGTH_MIN)
        return -IPV4_INVALID;

    return IPV4_OK;
}

/**
 * Dump an IPv4 packet header.
 */
void ipv4_dump_header(const struct ipv4_header *header)
{
    char dstaddr[20], srcaddr[20];

    ipv4_format(&header->source, srcaddr, sizeof(srcaddr));
    ipv4_format(&header->destination, dstaddr, sizeof(dstaddr));

    fprintf(stderr, "Internet Protocol Version 4\n");
    fprintf(stderr, "  | Version: %u\n", header->version);
    fprintf(stderr, "  | Internet Header Length: %u bytes (%u)\n",
            header->ihl * 4, header->ihl);
    fprintf(stderr, "  | Type Of Service: %u\n", header->tos);
    fprintf(stderr, "  | Total Length: %u bytes\n", header->total_length);
    fprintf(stderr, "  | Identification: 0x%04x (%u)\n", header->id,
            header->id);
    fprintf(stderr, "  | Time To Live: %u\n", header->ttl);
    fprintf(stderr, "  | Protocol: %u\n", header->protocol);
    fprintf(stderr, "  | Header Checksum: 0x%04x\n", header->checksum);
    fprintf(stderr, "  | Source IP: %s\n", srcaddr);
    fprintf(stderr, "  | Destination IP: %s\n", dstaddr);
}
