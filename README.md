# pinexa

This program lets you control NEXA PE-3 remote power sockets using Raspberry Pi.

## What you need

  * Raspberry Pi
  * TX433N module
  * NEXA PE-3

## Usage

LED connected to pin 24, TX433N data on pin 25.

````
$ make
# pinexa <group?> <on/off?> <target> [id]

# turn the 2nd device on
$ ./pinexa 0 1 1

# turn everything off
$ ./pinexa 1 0 0
````
