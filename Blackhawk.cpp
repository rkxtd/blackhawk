/*
 Blackhawk.cpp - Library for Blackhawk project - library should help arduino to do some stupid commands
 Copyright (c) 2017 Roman Shuvaryk.  All right reserved.
 */

// include this library's description file
#include "Blackhawk.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

#include "PubSubClient.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Blackhawk::Blackhawk(char* inBoardsChannel, char* inSensorsChannel, char* inBoardName, PubSubClient inClient, char* inDevices[])
{
  // initialize this instance's variables
  char* sensorsChannel = inSensorsChannel;
  char* boardsChannel = inBoardsChannel;
  char* boardName = inBoardName;
  PubSubClient client = inClient;
  char* devices[] = inDevices;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

String Blackhawk::captureCommand(char* topic, char* payload, unsigned int length) {
    String command = String (payload);
    command = command.substring(0, length);
    
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.print(command);
    Serial.println();
    
    if (String(topic).equals(String(boardsChannel))) {
        if (command.equals("PING")) {
            client.publish(boardsChannel, "PONG::" + boardName);
        }
        
        if (command.equals("REGISTER")) {
            registerBoard();
        }
    }
    
    return command;
}

void Blackhawk::reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(boardName)) {
            Serial.println("connected as ");
            Serial.print(boardName);
            client.subscribe(boardsChannel);
            client.subscribe(sensorsChannel);
            registerBoard();
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void JmriBlackhawk::registerBoard() {
    char* registerCommand = "REGISTER::" + boardName;

    for(int i = 0; i < sizeof(devices) - 1; i++) {
        registerCommand += "::" + devices[i];
    }
    
    client.publish(boardsChannel, registerCommand);
    Serial.println("SEND[" + boardsChannel + "]: " + registerCommand);
}
