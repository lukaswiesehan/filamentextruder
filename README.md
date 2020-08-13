# Filament Extruder

Bachelorprojekt im Studiengang Mechatronik, HAW Hamburg.  
*Entwickelt von Tobias Freytag, Anton Neike, Max Sahlke, Lukas Wiesehan.  
Betreut von Prof. Dr. Dietmar Pähler.*

1. [Projektstruktur](#projektstruktur)
2. [Nextion Library Setup](#nextion-library-setup)

## Projektstruktur

Die Steuerung des Extruders erfolgt mittels Arduino, wobei ein Nextion Display zur 
Realisierung des HMI verwendet wird.

## Hardware

| Anzahl | Bezeichnung | Beschreibung | Preis |
|:---:| --- | --- |:---:|
| 1x | [Felfil Evo Basic Kit](https://felfil.com/shop/felfil-evo-basic-kit/?v=5ea34fa833a1) | Basiskomponenten des Extruders als Bausatz | 299,00€ |
| 1x | [24V Netzteil]() | Primäre Spannungsquelle des Systems | |
| 1x | [Spannungswandler 24V -> 12V]() | Spannungsversorgung der 12V-Komponenten (Extrudermotor & Lüfter) | |
| 1x | [Spannungswandler LM2596]() | Spannungsversorgung der 5V-Komponenten (Display & Arduino) | |
| 3x | [Mosfet Modul]() | Steuerung der Heizpatronen | |
| 3x | [Heizpatrone]() | Heizmodule des Extruders | |
| 1x | [Temperatursensor PT100]() | Sensor zur Bestimmung der Extrudertemperatur | |
| 1x | [Adafruit MAX31865]() | Modul zur Wandlung des Sensorsignals des PT100 | |

Die Hardware-Kosten summieren sich damit auf **299,00€** zzgl. diverser Versandkosten.

## Nextion Library Setup

### Konfiguration

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

### Komponenten ein-/ausblenden

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

