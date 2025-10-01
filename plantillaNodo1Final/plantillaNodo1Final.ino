/*
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2019 Sensnology AB
 * Full contributor list: https://github.com/mysensors/MySensors/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik Ekblad
 *
 * DESCRIPTION
 * Example sketch showing how to control physical relays.
 * This example will remember relay state after power failure.
 * http://www.mysensors.org/build/relay
 */

// Enable debug prints to serial monitor
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_RF24 
#define MY_RF24_CE_PIN 10
#define MY_RF24_CS_PIN 9
#define MY_RF24_CHANNEL 10 //27 el nuestro
#define MY_NODE_ID 44

// Enable repeater functionality for this node
#define MY_REPEATER_FEATURE //no hace falta

#include <MySensors.h>

#define RELAY_PIN 4  // Arduino Digital I/O pin number for first relay (second on pin+1 etc)
#define SENSOR_RELAY_ID 12
MyMessage relayCom(SENSOR_RELAY_ID,V_STATUS);

void presentation()
{
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo("Relay_PRUEBA", "1.0");
//PRESENTAR LOS SENSORES
	present(SENSOR_RELAY_ID,S_BINARY);
	
}


void setup()
{
	pinMode(RELAY_PIN,OUTPUT);
	//Solo para HomeAssistant
	
	//Modificar el dato
	relayCom.set(0);
	//Enviar dato
	send(relayCom);

}


void loop()
{

}

void receive(const MyMessage &message)
{
	Serial.println("entra en interrupción");
	if(message.getType()==V_STATUS){
		if(message.getSensor()==SENSOR_RELAY_ID){
				digitalWrite(RELAY_PIN, message.getInt());
		}
	}
}

