/*
 * Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 * Updated 2020 TMRh20
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

/**
 * Channel scanner and Continuous Carrier Wave Output
 *
 * Example to detect interference on the various channels available.
 * This is a good diagnostic tool to check whether you're picking a
 * good channel for your application.
 *
 * Run this sketch on two devices. On one device, start CCW output by sending a 'g'
 * character over Serial. The other device scanning should detect the output of the sending
 * device on the given channel. Adjust channel and output power of CCW below.
 *
 * Inspired by cpixip.
 * See http://arduino.cc/forum/index.php/topic,54795.0.html
 */

#include <SPI.h>
#include "printf.h"
#include "RF24Revamped.h"

// instantiate an object for the nRF24L01 transceiver
RF24Revamped radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Channel info
const uint8_t num_channels = 126;
uint8_t values[num_channels];

void setup(void)
{
  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  Serial.println(F("RF24Revamped/examples/scanner/"));

  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  printf_begin(); // needed for printDetails()
  radio.printDetails();

  // Print out header, high then low digit
  int i = 0;
  while ( i < num_channels )
  {
    Serial.print(i >> 4, HEX);
    ++i;
  }
  Serial.println();
  i = 0;
  while ( i < num_channels )
  {
    Serial.print(i & 0xf, HEX);
    ++i;
  }
  Serial.println();
}

const int num_reps = 100;
bool constCarrierMode = 0;

void loop(void)
{
  /****************************************/
  // Send g over Serial to begin CCW output
  // Configure the channel and power level below
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'g') {
      constCarrierMode = 1;
      radio.stopListening();
      delay(2);
      Serial.println("Starting Carrier Out");
      radio.setChannel(40);
      radio.setPaLevel(RF24_PA_LOW);
      radio.startCarrierWave();
    } else if (c == 'e') {
      constCarrierMode = 0;
      radio.stopCarrierWave();
      Serial.println("Stopping Carrier Out");
    }
  }
  /****************************************/

  if (constCarrierMode == 0) {
    // Clear measurement values
    memset(values, 0, sizeof(values));

    // Scan all channels num_reps times
    int rep_counter = num_reps;
    while (rep_counter--)
    {
      int i = num_channels;
      while (i--)
      {
        // Select this channel
        radio.setChannel(i);

        // Listen for a little
        radio.startListening();
        delayMicroseconds(128);
        radio.stopListening();

        // Did we get a carrier?
        if (radio.testRpd()) {
          ++values[i];
        }
      }
    }


    // Print out channel measurements, clamped to a single hex digit
    int i = 0;
    while ( i < num_channels )
    {
      if (values[i])
        Serial.print(min(0xf, values[i]), HEX);
      else
        Serial.print(F("-"));

      ++i;
    }
    Serial.println();

  }//If constCarrierMode == 0
}
