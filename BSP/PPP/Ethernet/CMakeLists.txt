add_library(CycloneTCP OBJECT
        common/compiler_port.h
        common/cpu_endian.c
        common/cpu_endian.h
        common/date_time.c
        common/date_time.h
        common/debug.c
        common/debug.h
        common/error.h
        common/os_port.h
        common/os_port_freertos.c
        common/os_port_freertos.h
        common/path.c
        common/path.h
        common/resource_manager.c
        common/resource_manager.h
        common/str.c
        common/str.h
        cyclone_tcp/core/bsd_socket.c
        cyclone_tcp/core/bsd_socket.h
        cyclone_tcp/core/bsd_socket_misc.c
        cyclone_tcp/core/bsd_socket_misc.h
        cyclone_tcp/core/ethernet.c
        cyclone_tcp/core/ethernet.h
        cyclone_tcp/core/ethernet_misc.c
        cyclone_tcp/core/ethernet_misc.h
        cyclone_tcp/core/ip.c
        cyclone_tcp/core/ip.h
        cyclone_tcp/core/net.c
        cyclone_tcp/core/net.h
        cyclone_tcp/core/net_legacy.h
        cyclone_tcp/core/net_mem.c
        cyclone_tcp/core/net_mem.h
        cyclone_tcp/core/net_misc.c
        cyclone_tcp/core/net_misc.h
        cyclone_tcp/core/nic.c
        cyclone_tcp/core/nic.h
        cyclone_tcp/core/ping.c
        cyclone_tcp/core/ping.h
        cyclone_tcp/core/raw_socket.c
        cyclone_tcp/core/raw_socket.h
        cyclone_tcp/core/socket.c
        cyclone_tcp/core/socket.h
        cyclone_tcp/core/socket_misc.c
        cyclone_tcp/core/socket_misc.h
        cyclone_tcp/core/tcp.c
        cyclone_tcp/core/tcp.h
        cyclone_tcp/core/tcp_fsm.c
        cyclone_tcp/core/tcp_fsm.h
        cyclone_tcp/core/tcp_misc.c
        cyclone_tcp/core/tcp_misc.h
        cyclone_tcp/core/tcp_timer.c
        cyclone_tcp/core/tcp_timer.h
        cyclone_tcp/core/udp.c
        cyclone_tcp/core/udp.h
        cyclone_tcp/drivers/mac/pic32mx_eth_driver.c
        cyclone_tcp/drivers/mac/pic32mx_eth_driver.h
#        cyclone_tcp/drivers/mac/pic32mz_eth_driver.c
#        cyclone_tcp/drivers/mac/pic32mz_eth_driver.h
        cyclone_tcp/drivers/phy/ksz8041_driver.c
        cyclone_tcp/drivers/phy/ksz8041_driver.h
        cyclone_tcp/igmp/igmp_common.c
        cyclone_tcp/igmp/igmp_common.h
        cyclone_tcp/igmp/igmp_host.c
        cyclone_tcp/igmp/igmp_host.h
        cyclone_tcp/igmp/igmp_host_misc.c
        cyclone_tcp/igmp/igmp_host_misc.h
        cyclone_tcp/igmp/igmp_router.c
        cyclone_tcp/igmp/igmp_router.h
        cyclone_tcp/igmp/igmp_router_misc.c
        cyclone_tcp/igmp/igmp_router_misc.h
        cyclone_tcp/igmp/igmp_snooping.c
        cyclone_tcp/igmp/igmp_snooping.h
        cyclone_tcp/igmp/igmp_snooping_misc.c
        cyclone_tcp/igmp/igmp_snooping_misc.h
        cyclone_tcp/ipv4/arp.c
        cyclone_tcp/ipv4/arp.h
        cyclone_tcp/ipv4/auto_ip.c
        cyclone_tcp/ipv4/auto_ip.h
        cyclone_tcp/ipv4/auto_ip_misc.c
        cyclone_tcp/ipv4/auto_ip_misc.h
        cyclone_tcp/ipv4/icmp.c
        cyclone_tcp/ipv4/icmp.h
        cyclone_tcp/ipv4/ipv4.c
        cyclone_tcp/ipv4/ipv4.h
        cyclone_tcp/ipv4/ipv4_frag.c
        cyclone_tcp/ipv4/ipv4_frag.h
        cyclone_tcp/ipv4/ipv4_misc.c
        cyclone_tcp/ipv4/ipv4_misc.h
        cyclone_tcp/ipv4/ipv4_routing.h
        )