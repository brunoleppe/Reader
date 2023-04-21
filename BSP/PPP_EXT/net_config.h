/*
 * File:   net_config.h
 * Author: bleppe
 *
 * Created on 6 de junio de 2022, 8:23
 */

#ifndef NET_CONFIG_H
#define	NET_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MEM_TRACE_LEVEL          TRACE_LEVEL_INFO
#define NIC_TRACE_LEVEL          TRACE_LEVEL_INFO
#define ETH_TRACE_LEVEL          TRACE_LEVEL_OFF
#define LLDP_TRACE_LEVEL         TRACE_LEVEL_OFF
#define ARP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define IP_TRACE_LEVEL           TRACE_LEVEL_OFF
#define IPV4_TRACE_LEVEL         TRACE_LEVEL_OFF
#define IPV6_TRACE_LEVEL         TRACE_LEVEL_OFF
#define ICMP_TRACE_LEVEL         TRACE_LEVEL_OFF
#define IGMP_TRACE_LEVEL         TRACE_LEVEL_OFF
#define ICMPV6_TRACE_LEVEL       TRACE_LEVEL_OFF
#define MLD_TRACE_LEVEL          TRACE_LEVEL_OFF
#define NDP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define UDP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define TCP_TRACE_LEVEL          TRACE_LEVEL_OFF
#define SOCKET_TRACE_LEVEL       TRACE_LEVEL_OFF
#define RAW_SOCKET_TRACE_LEVEL   TRACE_LEVEL_OFF
#define BSD_SOCKET_TRACE_LEVEL   TRACE_LEVEL_OFF
#define WEB_SOCKET_TRACE_LEVEL   TRACE_LEVEL_OFF
#define AUTO_IP_TRACE_LEVEL      TRACE_LEVEL_INFO
#define SLAAC_TRACE_LEVEL        TRACE_LEVEL_INFO
#define DHCP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define DHCPV6_TRACE_LEVEL       TRACE_LEVEL_INFO
#define DNS_TRACE_LEVEL          TRACE_LEVEL_INFO
#define MDNS_TRACE_LEVEL         TRACE_LEVEL_OFF
#define NBNS_TRACE_LEVEL         TRACE_LEVEL_OFF
#define LLMNR_TRACE_LEVEL        TRACE_LEVEL_OFF
#define COAP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define FTP_TRACE_LEVEL          TRACE_LEVEL_INFO
#define HTTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define MQTT_TRACE_LEVEL         TRACE_LEVEL_INFO
#define MQTT_SN_TRACE_LEVEL      TRACE_LEVEL_INFO
#define SMTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define SNMP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define SNTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define TFTP_TRACE_LEVEL         TRACE_LEVEL_INFO
#define MODBUS_TRACE_LEVEL       TRACE_LEVEL_INFO


#define PIC32MZ_ETH_RX_BUFFER_COUNT 12


//Number of network adapters
#define NET_INTERFACE_COUNT 1

////LLC support (IEEE 802.2)
//#define ETH_LLC_SUPPORT ENABLED
////Switch port tagging
//#define ETH_PORT_TAGGING_SUPPORT ENABLED

//Size of the MAC address filter
#define MAC_ADDR_FILTER_SIZE 12

//IPv4 support
#define IPV4_SUPPORT ENABLED
//Size of the IPv4 multicast filter
#define IPV4_MULTICAST_FILTER_SIZE 4

//IPv4 fragmentation support
#define IPV4_FRAG_SUPPORT DISABLED
//Maximum number of fragmented packets the host will accept
//and hold in the reassembly queue simultaneously
#define IPV4_MAX_FRAG_DATAGRAMS 4
//Maximum datagram size the host will accept when reassembling fragments
#define IPV4_MAX_FRAG_DATAGRAM_SIZE 8192

//Size of ARP cache
#define ARP_CACHE_SIZE 8
//Maximum number of packets waiting for address resolution to complete
#define ARP_MAX_PENDING_PACKETS 2

//IGMP host support
#define IGMP_HOST_SUPPORT DISABLED

//IPv6 support
#define IPV6_SUPPORT DISABLED
//Size of the IPv6 multicast filter
#define IPV6_MULTICAST_FILTER_SIZE 8

//IPv6 fragmentation support
#define IPV6_FRAG_SUPPORT DISABLED
//Maximum number of fragmented packets the host will accept
//and hold in the reassembly queue simultaneously
#define IPV6_MAX_FRAG_DATAGRAMS 4
//Maximum datagram size the host will accept when reassembling fragments
#define IPV6_MAX_FRAG_DATAGRAM_SIZE 8192

//MLD support
#define MLD_SUPPORT DISABLED

//Neighbor cache size
#define NDP_NEIGHBOR_CACHE_SIZE 8
//Destination cache size
#define NDP_DEST_CACHE_SIZE 8
//Maximum number of packets waiting for address resolution to complete
#define NDP_MAX_PENDING_PACKETS 2

//TCP support
#define TCP_SUPPORT ENABLED
//Default buffer size for transmission
#define TCP_DEFAULT_TX_BUFFER_SIZE (1430*2)
//Default buffer size for reception
#define TCP_DEFAULT_RX_BUFFER_SIZE (1430*2)
//Default SYN queue size for listening sockets
#define TCP_DEFAULT_SYN_QUEUE_SIZE 4
//Maximum number of retransmissions
#define TCP_MAX_RETRIES 5
//Selective acknowledgment support
#define TCP_SACK_SUPPORT DISABLED
//TCP keep-alive support
#define TCP_KEEP_ALIVE_SUPPORT DISABLED

//UDP support
#define UDP_SUPPORT ENABLED
//Receive queue depth for connectionless sockets
#define UDP_RX_QUEUE_SIZE 4

//Raw socket support
#define RAW_SOCKET_SUPPORT ENABLED
//Receive queue depth for raw sockets
#define RAW_SOCKET_RX_QUEUE_SIZE 4

//Number of sockets that can be opened simultaneously
#define SOCKET_MAX_COUNT 10

//LLMNR responder support
#define LLMNR_RESPONDER_SUPPORT DISABLED

//SNMP agent support
#define SNMP_AGENT_SUPPORT DISABLED
//SNMP MIB module support
#define SNMP_MIB_SUPPORT DISABLED

#define GPL_LICENSE_TERMS_ACCEPTED

#define DNS_CLIENT_SUPPORT DISABLED
#define MDNS_CLIENT_SUPPORT DISABLED
#define MDNS_RESPONDER_SUPPORT DISABLED
#define NBNS_CLIENT_SUPPORT DISABLED
#define NBNS_RESPONDER_SUPPORT DISABLED
#define DHCP_CLIENT_SUPPORT DISABLED


#ifdef	__cplusplus
}
#endif

#endif	/* NET_CONFIG_H */
