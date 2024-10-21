# Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause-Clear

#!/bin/sh
echo "ip_config_wlan"

cmd=$1

echo "ip_config_wlan: $cmd"
PLATFORM=`uname -a| cut -d ' ' -f2`
IP_ADDRESS=`cat /etc/someip/vsomeip_server.json | grep unicast |cut -d '"' -f4`
WLAN_KO_PATH=`find /lib/modules/ -name "wlan-hamilton.ko"`

insmod_ko()
{
    insmod $WLAN_KO_PATH
    while true
    do
        result=$(ifconfig wlan0 2>&1)
        if echo "$result" | grep -q "error fetching interface"; then
            sleep 0.5
        else
            break
        fi
    done
}

config_vlan()
{
    echo $IP_ADDRESS
        case "$PLATFORM" in
        imx8*)
            echo "config vlan"
            ip link add link eth0 name vlan41 type vlan id 41
            ip addr add 10.41.3.203/16 dev vlan41
            ip link set vlan41 up
            ip link add link eth0 name vlan43 type vlan id 43
            ip link set vlan43 up
            ;;
        *)
            echo "Unknown platform: $PLATFORM"
            ;;
    esac
}

config_ethernet()
{
    echo "ip_address:" $IP_ADDRESS
        case "$PLATFORM" in
        imx8*)
            echo "config ethernet"
            ;;
        *)
            echo "Unknown platform: $PLATFORM"
            ;;
    esac
}

case "$cmd" in
    vlan)
        insmod_ko
        config_vlan
        ;;
    ethernet)
        insmod_ko
        config_ethernet
        ;;
    *)
        echo "unknown para: $cmd"
        exit 1
        ;;
esac
exit 0