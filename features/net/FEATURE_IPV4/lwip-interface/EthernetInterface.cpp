/* LWIP implementation of NetworkInterfaceAPI
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "EthernetInterface.h"
#include "lwip_stack.h"


/* Interface implementation */
EthernetInterface::EthernetInterface()
{
    _dhcp = true;
}

int EthernetInterface::set_dhcp(bool dhcp)
{
    _dhcp = dhcp;
    return 0;
}

int EthernetInterface::connect()
{
    return lwip_bringup(_dhcp,
            NetworkInterface::get_ip_address(),
            NetworkInterface::get_netmask(),
            NetworkInterface::get_gateway());
}

int EthernetInterface::disconnect()
{
    lwip_bringdown();
    return 0;
}

const char *EthernetInterface::get_mac_address()
{
    return lwip_get_mac_address();
}

const char *EthernetInterface::get_ip_address()
{
    return lwip_get_ip_address();
}

const char *EthernetInterface::get_netmask()
{
    return lwip_get_netmask();
}

const char *EthernetInterface::get_gateway()
{
    return lwip_get_gateway();
}

NetworkStack *EthernetInterface::get_stack()
{
    return nsapi_create_stack(&lwip_stack);
}
