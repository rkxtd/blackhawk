/*
  Blackhawk.h - Library for Blackhawk project - library should help arduino to connect to MQTT topic, register itself and watch for sensor changes
  Copyright (c) 2017 Roman Shuvaryk.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Blackhawk_h
#define Blackhawk_h
#include "PubSubClient.h"
#include "Servo.h"

// library interface description
class Blackhawk
{
  // user-accessible "public" interface
  public:
    JmriBlackhawk(String inBoardsChannel, String inSensorsChannel, String inBoardName, PubSubClient inClient, String inDevices[]);
    String captureCommand(char* topic, char* payload, unsigned int length);
    void reconnect(void);
    
  // library-accessible "private" interface
  private:
    String boardName;
    String sensorsChannel;
    String boardsChannel;
    PubSubClient client;
    String* devices;
    
    void registerBoard(void);
};

#endif

