/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#include "pinmap.h"
#include "mbed_error.h"

PinMap* pinmap_find(PinName pin, const PinMap* map, uint8_t idx) {
	PinMap *item_first, *item_curr;
    uint8_t found=0;
    while (map->pin != NC) {
        if (map->pin == pin) {
            if(!found)
                item_curr = item_first = map;
            else
                item_curr = map;
            found = 1;
            idx--;
        }
        if(found && idx == 0)
            return item_curr;
        map++;
    }
    if(found && map->pin == NC)
        return item_first;
    return NULL;

}

void pinmap_pinout(PinName pin, const PinMap *map) {
    if (pin == NC)
        return;

	PinMap* ret = pinmap_find(pin, map, 1);
	if(ret!=NULL) {
        pin_function(pin, ret->function);

		pin_mode(pin, PullNone);
		return;
	}
    error("could not pinout");
}

void pinmap_pinout_ex(PinName pin, const PinMap *map, const uint8_t idx) {
    if (pin == NC)
        return;

	PinMap* ret = pinmap_find(pin, map, idx);
	if(ret!=NULL) {
        pin_function(pin, ret->function);

		pin_mode(pin, PullNone);
		return;
	}
    error("could not pinout");
}

uint32_t pinmap_merge(uint32_t a, uint32_t b) {
    // both are the same (inc both NC)
    if (a == b)
        return a;

    // one (or both) is not connected
    if (a == (uint32_t)NC)
        return b;
    if (b == (uint32_t)NC)
        return a;

    // mis-match error case
    error("pinmap mis-match");
    return (uint32_t)NC;
}

uint32_t pinmap_find_peripheral(PinName pin, const PinMap* map) {
	PinMap* ret = pinmap_find(pin, map, 1);
	if(ret!=NULL)
		return ret->peripheral;
    return (uint32_t)NC;
}

uint32_t pinmap_find_peripheral_ex(PinName pin, const PinMap* map, const uint8_t idx) {
	PinMap* ret = pinmap_find(pin, map, idx);
	if(ret!=NULL)
		return ret->peripheral;
    return (uint32_t)NC;
}

uint32_t pinmap_peripheral(PinName pin, const PinMap* map) {
    return pinmap_peripheral_ex(pin, map, 1);
}

uint32_t pinmap_peripheral_ex(PinName pin, const PinMap* map, const uint8_t idx) {
    uint32_t peripheral = (uint32_t)NC;

    if (pin == (PinName)NC)
        return (uint32_t)NC;
    peripheral = pinmap_find_peripheral_ex(pin, map, idx);
    if ((uint32_t)NC == peripheral) // no mapping available
        error("pinmap not found for peripheral");
    return peripheral;
}

uint32_t pinmap_find_function(PinName pin, const PinMap* map) {
	PinMap* ret = pinmap_find(pin, map, 1);
	if(ret!=NULL)
		return ret->function;
    return (uint32_t)NC;
}

uint32_t pinmap_find_function_ex(PinName pin, const PinMap* map, const uint8_t idx) {
	PinMap* ret = pinmap_find(pin, map, idx);
	if(ret!=NULL)
		return ret->function;
    return (uint32_t)NC;
}

uint32_t pinmap_function(PinName pin, const PinMap* map) {
	return pinmap_function_ex(pin, map, 1);
}

uint32_t pinmap_function_ex(PinName pin, const PinMap* map, const uint8_t idx) {
    uint32_t function = (uint32_t)NC;

    if (pin == (PinName)NC)
        return (uint32_t)NC;
    function = pinmap_find_function_ex(pin, map, idx);
    if ((uint32_t)NC == function) // no mapping available
        error("pinmap not found for function");
    return function;
}
