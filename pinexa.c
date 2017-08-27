/*
 * pinexa
 * Copyright (C) 2017 Anders Bergh
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <wiringPi.h>

static void sendBit(int pin, int bit) {
  if (bit) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(200);

    digitalWrite(pin, LOW);
    delayMicroseconds(1240);
  } else {
    digitalWrite(pin, HIGH);
    delayMicroseconds(200);

    digitalWrite(pin, LOW);
    delayMicroseconds(200);
  }
}

/* 1 is encoded as 10, 0 as 01 */
static void sendPair(int pin, int bit) {
  if (bit) {
    sendBit(pin, 1);
    sendBit(pin, 0);
  } else {
    sendBit(pin, 0);
    sendBit(pin, 1);
  }
}

int main(int argc, char *argv[]) {
  int ledPin = 24;
  int txPin = 25;

  wiringPiSetupGpio();

  pinMode(txPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  uint32_t id = 0x147914a;
  int group = 0;
  int onoff = 0;
  int device = 1;

  /* ./onoff [group] [onoff] [device] [ID] */
  if (argc >= 4) {
    group = atoi(argv[1]) & 0x1;
    onoff = atoi(argv[2]) & 0x1;
    device = atoi(argv[3]) & 0xf;
  }
  if (argc >= 5) {
    id = atoi(argv[4]) & 0x3ffffff;
  }

  uint32_t msg = id << 6 | group << 5 | onoff << 4 | device;

  printf("sending:\n");
  printf("  id      = 0x%x\n", id);
  printf("  group   = %s\n", group == 1 ? "yes" : "no");
  printf("  on/off  = %s\n", onoff == 1 ? "on" : "off");
  printf("  device  = %d\n", device);

  /* not entirely correct but it works for me */
  digitalWrite(ledPin, HIGH);
  for (int i = 0; i < 4; i++) {
    /* latch 1 */
    digitalWrite(txPin, HIGH);
    delayMicroseconds(220);
    digitalWrite(txPin, LOW);
    delayMicroseconds(10450);

    /* latch 2 */
    digitalWrite(txPin, HIGH);
    delayMicroseconds(220);
    digitalWrite(txPin, LOW);
    delayMicroseconds(2650);

    /* message */
    for (int i = 0; i < 32; i++) {
      sendPair(txPin, (msg >> (31-i)) & 0x1);
    }
  }
  digitalWrite(ledPin, LOW);

  return 0;
}
