#ifndef NETWORK_H
#define NETWORK_H

#include "base.h"

MenuItem* Method::get_network_ptr(){
    MenuItem* network_ptr = new MenuItem;
    network_ptr->name = "network";
    network_ptr->submenu = {
        {"network +", {
            {"ip +", {
                {"ip addr +", {{"ip addr show +", {{"show netdev info including ip address#ip addr show ${dev}#"},
                                                   {"..."}}},
                {"ip addr add +", {{"add ip/subnetmask to dev#ip addr add ${ip/subnetmask} dev ${dev}#"}}},
                {"ip addr del +", {{"del ip/subnetmask from dev#ip addr del ${ip/subnetmask} dev ${dev}#"}}}}},
                {"ip link +", {
                    {"ip link help#ip link help#"},
                    {"ip link add +", {{"add veth pair#ip link add ${veth} type veth peer name ${veth_p}#"},
                                       {"add veth pair with netns#ip link add ${veth} netns ${netns} type veth peer ${veth_p} netns ${peer_netns}#"},
                                       {"add bridge#ip link add name ${bridge} type bridge#"}}},
                    {"ip link delete +", {{"ip link delete ${bridge} type bridge#"},
                                          {"..."}}},
                    {"ip link set +", {{"put veth peer to netns#ip link set ${veth_p} netns ${peer_netns}#"},
                                       {"remove netdev from its master#ip link set ${dev} nomaster#"},
                                       {"set bridge up#ip link set dev ${bridge} up#"},
                                       {"set bridge down#ip link set dev ${bridge} down#"},
                                       {"set veth up#ip link set ${veth} up#"},
                                       {"set veth down#ip link set ${veth} down#"},
                                       {"set veth on bridge#ip link set ${veth} master ${bridge}#"},
                                       {"set veth off bridge#ip link set ${veth} nomaster#"}}},
                    {"ip link show +", {{"show all itfs info#ip link show#"},
                                        {"show certain itf info#ip link show ${dev}#"},
                                        {"show brief itf info#ip -brief link show ${dev}#"}}},
                    {"ip [option] link +", {{"show all itfs in color#ip -c link#"},
                                            {"show certain itfs info#ip -c link show ${dev}#"},
                                            {"show itfs statistics#ip -s link#"},
                                            {"show certain itfs info#ip -s link show ${dev}#"}}}}},
                    {"ip route +", {{"ip route show +", {{"show netdev route info#ip route show dev ${dev}#"}}}}},
                    {"ip neigh +", {{"show all ipv4 arp neighbor entries#ip neigh#"},
                                    {"show ipv4 arp neighbor entries for dev#ip neigh show dev ${dev}#"},
                                    {"add ip <-> mac entry for arptable of dev#ip neigh add ${ip} lladdr ${mac} dev ${dev}#"},
                                    {"del the arp entry of ip for dev#ip neigh del ${ip} dev ${dev}"},
                                    {"replace/add the arp entry of ip to new mac for dev#ip neigh replace ${ip} lladdr ${mac} dev ${dev}#"}}},
                    {"ip netns +", {{"show ip netns subcmd help#ip netns help#"},
                                    {"list existed netns#ip netns list#"},
                                    {"create netns by name#ip netns add ${netnsname}#"},
                                    {"delete netns by name#ip netns delete ${netnsname}#"},
                                    {"*execute cmd in a netns#ip netns exec ${netnsname} ${cmd}#ipnetns"},
                                    {"monitor route changes of ipv4 inside certain netns#ip netns exec ${namepace} ip -4 monitor route#"}}}}},
        {"iptables +", {{"show cmd help#iptables --help#"},
                        {"show detailed manual#man iptables#"},
                        {"list iptable rules +", {{"*list rules of all chains in table(raw mangle nat filter)#iptables -n -v -L -t ${table}#iptables"},
                                                  {"*list rules of a chain in all table#iptables -nvL ${chainname}#dockeriptables"},
                                                  {"list rules of certain chain in certain table#iptables -n -v -L ${chain} -t ${table}#iptables"}}},
                        {"iptables-save +", {{"show manual page#man iptables-save#"},
                                             {"show iptable rules in plain txt for certain table#iptables-save -t ${table}#"}}}}},
        {"dns +", {{"get ip for domain name (nslookup)#nslookup ${domain_name}#"},
                   {"get ip for domain name (dig)#dig ${domain_name}#"},
                   {"check nameserver config file#cat /etc/resolv.conf (see: https://linux.die.net/man/5/resolv.conf)#"}}},
        {"brctl +", {{"brctl show +", {{"show bridge general info#brctl show#"},
                                       {"show bridge info#brctl show ${bridge}#"},
                                       {"show bridge mac info#brctl showmacs ${bridge}#"},
                                       {"show bridge stp info#brctl showstp ${bridge}#"}}},
                     {"brctl addbr +", {{"add bridge#brctl addbr ${dev}#"}}},
                     {"brctl delbr +", {{"del bridge#brctl delbr ${dev}#"}}},
                     {"brctl addif +", {{"add itf to bridge#brctl addif ${bridge} ${interface}#"}}}}},
        {"bridge +", {{"bridge manual ref#https://man.archlinux.org/man/bridge.8#"}}},
        {"ethtool +", {{"ethtool: query network driver/hardware settings#https://man7.org/linux/man-pages/man8/ethtool.8.html#"},
                       {"show network receive/transmit/drop statistics of a nic#ethtool -S ${nic}#"},
                       {"show driver info of a nic#ethtool -i ${nic}#"},
                       {"show ring buffer info of a nic#ethtool -g ${nic}#"},
                       {"show EEPROM data of a nic#ethtool -e ${nic}#"},
                       {"*show checksum offload info of a nic#ethtool --show-offload ${nic}#ethtoolchecksum"},
                       {"shutdown checksum offload of a nic#ethtool --offload ${nic} tx off#"},
                       {"show nic by sight in physical world: make the light of the chosen nic blinking#ethtool -g ${nic}#"}}},
        {"netstat +", {{"show ip routing tables (ip:numerical)#netstat -rn#"},
                       {"show active tcp/udp listening sockets (numerical)#netstat -tu -pnl#"},
                       {"show all tcp/udp sockets (numerical)#netstat -tu -pna#"},
                       {"show statistics of pkts of each itf#netstat -i#"}}},
        {"nc +", {{"show connection ip:port status info (zero I/O mode)#nc -zv ${ip}:${port}#"}}},
        {"ncat +", {{"listening on incoming tcp4 connections, maintain a que to accept multiple connections (as a server)#ncat -lk4 ${ip} ${port}#"}}},
        {"nsenter +", {{"show manual for nsenter#man nsenter#"},
                       {"enter into netns of pid, run cmd in that netns#sudo nsenter --target ${pid} --net ${ip link show}#"},
                       {"enter into netns of pid, display listening program-sock info#sudo nsenter --target ${pid} --net netstat -pnl#"},
                       {"enter into netns of pid, display all program-sock info#sudo nsenter --target ${pid} --net netstat -pna#"}}},
        {"tcpdump +", {{"capture pkts, enable ip resolution (live)#tcpdump -i ${dev}#"},
                       {"capture pkts, disable ip resolution (live)#tcpdump -n -i ${dev}#"},
                       {"capture pkts, disable ip/port resolution (live & verbose)#tcpdump -n -i ${dev} -vvnnXX#"},
                       {"capture pkts, keep max pkt size limit as 2048 bytes (live & verbose)#tcpdump -vvnnXX -s 2048 -i ${dev}#"},
                       {"capture pkts, dump to pcap file (only keep latest 4s data)#tcpdump -vvnnXX -i ${dev} -w output.pcap -G 4#"}}},
        {"tshark +", {{"show itfs available to tshark#tshark -D#"},
                      {"capture the pkts from a itf#tshark -i ${interface}#"},
                      {"capture 10 pkts from a itf#tshark -i ${interface} -c 10#"},
                      {"capture pkts with verbose info#tshark -i ${interface} -V#"},
                      {"capture pkts with timestamp info#tshark -i eth0 -t ad#"},
                      {"capture pkts & disable name resolution#tshark -n -i eth0#"},
                      {"capture pkts of certain proto from a itf (tcp/udp/icmp...)#tshark -i ${interface} ${proto}#"},
                      {"capture 2 pkts content filtered by involving ip through eth0#tshark -i eth0 -x -c 2 -f 'host 192.168.0.20'#"},
                      {"dump pkts from a itf to pcap file#tshark -w output.pcap -i eth0#"},
                      {"read pkts content in pcap files#tshark -r output.pcap#"}}},
        {"termshark +", {{"todo#...#"}}}}},
    };
    return network_ptr;
}

#endif
