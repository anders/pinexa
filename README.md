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

## HomeKit integration

With `homebridge` and `homebridge-cmdswitch2` you can use Siri to control your NEXA devices. Relevant part of my `config.json`:

````json
"platforms": [
	{
		"platform": "cmdSwitch2",
		"switches": [
			{
				"name": "TV",
				"on_cmd": "/home/pi/onoff 0 1 0",
				"off_cmd": "/home/pi/onoff 0 0 0"
			},
			{
				"name": "Lamp",
				"on_cmd": "/home/pi/onoff 0 1 1",
				"off_cmd": "/home/pi/onoff 0 0 1"
			},
			{
				"name": "HVAC",
				"on_cmd": "/home/pi/onoff 0 1 2",
				"off_cmd": "/home/pi/onoff 0 0 2"
			}
		]
	}
]
````