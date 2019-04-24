/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A program that collects statistics from a network of Tmote Sky nodes
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "sys/cc.h"
#include "dev/leds.h"
#include "dev/light-sensor.h"

#include <stdio.h>
#include <string.h>

PROCESS(antitheft_process, "antitheft_process");    
AUTOSTART_PROCESSES(&antitheft_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antitheft_process, ev, data)
{
  PROCESS_BEGIN();
  uint16_t light1;
  uint16_t light2;
  static struct etimer et;
  etimer_set(&et, CLOCK_SECOND * 0.2);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    SENSORS_ACTIVATE(light_sensor);
    light1 = light_sensor.value(LIGHT_SENSOR_PHOTOSYNTHETIC);
    light2 = light_sensor.value(LIGHT_SENSOR_TOTAL_SOLAR);
    printf("light 1: %d, light2 :%d\n", light1, light2);
    if(light1<91||light2<91){
      leds_on(LEDS_RED);
    }
    else{
      leds_off(LEDS_RED);
    }
    SENSORS_DEACTIVATE(light_sensor);
    etimer_reset(&et);
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
