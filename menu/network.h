#ifndef NETWORK_H
#define NETWORK_H

#include "base.h"

MenuItem* Method::get_network_ptr(){
    MenuItem* network_ptr = new MenuItem;
    network_ptr->name = "network";
    network_ptr->submenu = {
        {"network +", {
            {"settings +", {{"show local network ip settings (default, loopback, link-local)#cat /etc/networks#"}}},
            {"ip +", {{"ip addr +", {{"ip addr show +", {{"show netdev info including ip address#ip addr show ${dev}#"},
                                                         {"..."}}},
                                     {"ip addr add +", {{"add ip/subnetmask to dev#ip addr add ${ip/subnetmask} dev ${dev}#"}}},
                                     {"ip addr del +", {{"del ip/subnetmask from dev#ip addr del ${ip/subnetmask} dev ${dev}#"}}}}},
                      {"ip link +", {{"ip link help#ip link help#"},
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
                                                         {"show brief itf info#ip -brief link show ${dev}#"},
                                                         {"show detailed itf info#ip -d link show ${dev}#"},
                                                         {"show all itfs in color#ip -c link#"},
                                                         {"show certain itfs info#ip -c link show ${dev}#"},
                                                         {"show itfs statistics#ip -s link#"},
                                                         {"show certain itfs statistic#ip -s link show ${dev}#"}}}}},
                      {"ip tuntap +", {{"show help#ip tuntap help#"},
                                       {"show available ip tuntaps#ip tuntap show#"}}},
                      {"ip route +", {{"ip route show +", {{"show netdev route info#ip route show dev ${dev}#"},
                                                           {"show all route info in neat format#ip route show | column '-t'#"}}},
                                      {"routel +", {{"show brief halp page#routel -h#"},
                                                    {"show manual#man routel#"},
                                                    {"list route with pretty output format#routel#"}}}}},
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
                                      {"monitor route changes of ipv4 inside certain netns#ip netns exec ${namepace} ip -4 monitor route#"}}},
                      {"ip monitor +", {{"monitor ip link changes live#ip monitor link#"}}}}},
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
            {"traceroute +", {{"show manual#man traceroute#"},
                              {"test route access to dst ip by sending tcp pkts#traceroute -T ${dst_ip}#"},
                              {"test route access to dst ip by sending icmp pkts#traceroute -I ${dst_ip}#"},
                              {"test route access to dst url by sending icmp pkts#traceroute ${dst_ip}#"}}},
            {"bridge +", {{"bridge manual ref#https://man.archlinux.org/man/bridge.8#"},
                          {"brctl +", {{"brctl show +", {{"show bridge general info#brctl show#"},
                                                         {"show bridge info#brctl show ${bridge}#"},
                                                         {"show bridge mac info#brctl showmacs ${bridge}#"},
                                                         {"show bridge stp info (if stp enabled, bridge not in hub mode)#brctl showstp ${bridge}#"}}},
                                       {"brctl addbr +", {{"add bridge#brctl addbr ${dev}#"}}},
                                       {"brctl delbr +", {{"del bridge#brctl delbr ${dev}#"}}},
                                       {"brctl addif +", {{"add itf to bridge#brctl addif ${bridge} ${interface}#"}}}}},
                          {"check group_fwd_mask (hub mode)#cat /sys/class/net/br_ethhigig1/bridge/group_fwd_mask#"},
                          {"set bridge group_fwd_mask (enable forwarding LACP, LLDP traffic, config bridge as l2/l3 switch)#cat /sys/class/net/br_ethhigig1/bridge/group_fwd_mask#"}}},
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
            {"conntrack +", {{"list established connection info: ip/port for dst/src#conntrack -L#"}}},
            {"lsof +", {{"show open files info associated with net connections#sudo lsof -i -P"}}},
            {"nc +", {{"show connection ip:port status info (zero I/O mode)#nc -zv ${ip}:${port}#"}}},
            {"ncat +", {{"listening on incoming tcp4 connections, maintain a que to accept multiple connections (as a server)#ncat -lk4 ${ip} ${port}#"}}},
            {"lsns +", {{"show manual#man lsns#"},
                        {"list all namespaces#lsns -l#"},
                        {"list all namespaces info associated with certain process#lsns -l -p ${pid}#"}}},
            {"nsenter +", {{"show manual for nsenter#man nsenter#"},
                           {"enter netns by name, enter bash asociated with that netns#nsenter --net=/var/run/netns/${netns_name} bash#"},
                           {"enter netns associated with pid, run net related cmd in that netns#sudo nsenter --target ${pid} --net ${some_net_cmd}#"},
                           {"enter netns associated with pid, display listening program-sock info#sudo nsenter --target ${pid} --net netstat -pnl#"},
                           {"enter netns associated with pid, display all program-sock info#sudo nsenter --target ${pid} --net netstat -pna#"}}},
            {"tcpdump +", {{"capture pkts, enable ip resolution (live)#tcpdump -i ${dev}#"},
                           {"capture pkts, disable ip resolution (live)#tcpdump -n -i ${dev}#"},
                           {"capture pkts, disable ip/port resolution (live & verbose)#tcpdump -n -i ${dev} -vvnnXX#"},
                           {"capture pkts, keep max pkt size limit as 2048 bytes (live & verbose)#tcpdump -vvnnXX -s 2048 -i ${dev}#"},
                           {"capture pkts, without verify checksum (sometime checksum offloading might report warning)#tcpdump -i ${dev} -vvnnXX --dont-verify-checksums#"},
                           {"capture pkts, dump to pcap file (only keep latest 4s data)#tcpdump -vvnnXX -i ${dev} -w out.pcap -G 4#"},
                           {"capture pkts, dump to pcap file (only keep latest 4Mb size)#tcpdump -vvnnXX -i ${dev} -w out.pcap -C 4#"},
                           {"capture pkts, dump to pcap file (only keep latest 4Mb size in 2 file)#tcpdump -vvnnXX -i ${dev} -w out.pcap -W 2 -C 4#"},
                           {"capture pkts, filter out pkts by certain conditions#tcpdump -vvnnXX -i ${dev} \(src ${src_ip} and port ${src_port}\) or \(dst ${dst_ip} and port ${dst_port}\)#"},
                           {"dump info from pcap file#tcpdump -r ${pcap.file}#"}}},
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
            {"termshark +", {{"todo#...#"}}},
            {"ssh +", {{"show ssh manual#man ssh#"},
                       {"identify private key for new server login#ssh -i ${private_key.pem}#"},
                       {"*ssh config#see desc/sshconfig for details#sshconfig"},
                       {"scp +", {{"test ssh connection to github site without create new tty#ssh -T git@github.com#"},
                                  {"download file from server to local#scp user@ip:${serverdir/file} ${localdir}#"},
                                  {"upload file from local to server#scp ${localdir/file} user@ip:${serverdir}#"},
                                  {"download dir from server to local under local dir#scp -r user@ip:${serverdir} ${localdir}#"},
                                  {"upload dir from local to server under serverdir#scp -r ${localdir} user@ip:${serverdir}#"}}}}},
            {"telnet +", {{"show manual#man telnet#"},
                          {"use telnet proto over tcp to setup connection with another host end#telnet ${dst_ip} ${dst_port}#"},
                          {"force use telnet proto over tcp4 for connection#telent -4 ${dst_ip} ${dst_port}#"},
                          {"force use telnet proto over tcp6 for connection#telent -6 ${dst_ip} ${dst_port}#"}}}}},
    };
    return network_ptr;
}

#endif
