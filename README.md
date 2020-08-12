# Filament Extruder

Bachelorprojekt im Studiengang Mechatronik, HAW Hamburg

*Tobias Freytag, Anton Neike, Max Sahlke, Lukas Wiesehan*

### Projektstruktur

Die Steuerung des Extruders erfolgt mittels Arduino, wobei ein Nextion Display zur 
Realisierung des HMI verwendet wird.

### Nextion Library Setup

Damit die Nextion Library auch mit einem Arduino Uno/Nano verwendet werden kann, muss die 
*NexConfig* angepasst werden, da kleinere Arduino Boards nur einen Hardware Serial Kanal 
besitzen.

```c++
/* Edit in NexConfig.h */

//#define DEBUG_SERIAL_ENABLE
//#define dbSerial Serial
#define nexSerial Serial
```

Es wird also der Debug-Serial abgeschaltet, damit der einzige Serial-Kanal des Arduinos für 
die Kommunikation mit dem Display verwendet werden kann.

Weiterhin werden der *NexButton*- und der *NexPicture*-Klasse Methoden hinzugefügt, die es
ermöglichen, diese Komponenten ein- bzw. auszublenden.

```c++
/* Add to NexButton.h */

bool hide();
bool show();
```
```c++
/* Add to NexButton.cpp */

bool NexButton::hide()
{
  String cmd;

  cmd += "vis ";
  cmd += getObjName();
  cmd += ",0";
  sendCommand(cmd.c_str());
  return recvRetCommandFinished();
}

bool NexButton::show()
{
  String cmd;

  cmd += "vis ";
  cmd += getObjName();
  cmd += ",1";
  sendCommand(cmd.c_str());
  return recvRetCommandFinished();
}
```
```c++
/* Add to NexPicture.h */

bool hide();
bool show();
```
```c++
/* Add to NexPicture.cpp */

bool NexPicture::hide()
{
  String cmd;

  cmd += "vis ";
  cmd += getObjName();
  cmd += ",0";
  sendCommand(cmd.c_str());
  return recvRetCommandFinished();
}

bool NexPicture::show()
{
  String cmd;

  cmd += "vis ";
  cmd += getObjName();
  cmd += ",1";
  sendCommand(cmd.c_str());
  return recvRetCommandFinished();
}
```

