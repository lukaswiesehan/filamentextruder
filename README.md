# Filament Extruder

Bachelorprojekt im Studiengang Mechatronik, HAW Hamburg.  
*Entwickelt von Tobias Freytag, Anton Neike, Max Sahlke, Lukas Wiesehan.  
Betreut von Prof. Dr. Dietmar Pähler.*

1. [Projektstruktur](#projektstruktur)
2. [Nextion Library Setup](#nextion-library-setup)

### Projektstruktur

Die Steuerung des Extruders erfolgt mittels Arduino, wobei ein Nextion Display zur 
Realisierung des HMI verwendet wird.

### Nextion Library Setup

#### Konfiguration

Zur einfachen Kommunikation zwischen Display und Arduino wird die offizielle 
[Nextion Library](https://github.com/itead/ITEADLIB_Arduino_Nextion) verwendet.
Damit diese auch mit einem Arduino Uno/Nano verwendet werden kann, muss die 
`NexConfig.h` angepasst werden, da kleinere Arduino Boards nur einen Hardware Serial Kanal 
besitzen.

###### NexConfig.h bearbeiten
```c++
//#define DEBUG_SERIAL_ENABLE
//#define dbSerial Serial
#define nexSerial Serial
```

Es wird also der Debug-Serial abgeschaltet, damit der einzige Serial-Kanal des Arduinos für 
die Kommunikation mit dem Display verwendet werden kann.

#### Komponenten ein-/ausblenden

Weiterhin werden der `NexButton`- und der `NexPicture`-Klasse Methoden hinzugefügt, die es
ermöglichen, diese Komponenten ein- bzw. auszublenden.

###### NexButton.h erweitern
```c++
bool hide();
bool show();
```

###### NexButton.cpp erweitern
```c++
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

###### NexPicture.h erweitern
```c++
bool hide();
bool show();
```

###### NexPicture.cpp erweitern
```c++
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

