# Filament Extruder

Bachelorprojekt im Studiengang Mechatronik, HAW Hamburg.  
*Entwickelt von Tobias Freytag, Anton Neike, Max Sahlke, Lukas Wiesehan.  
Betreut von Prof. Dr. Dietmar Pähler.*

1. [Einführung](#einführung)
2. [Repo-Struktur](#repo-struktur)
3. [Hardware](#hardware)
4. [Nextion Library Setup](#nextion-library-setup)

## Einführung

Die Steuerung des Extruders erfolgt mittels Arduino, wobei ein Nextion Display zur 
Realisierung des HMI verwendet wird.

## Repo-Struktur

## Hardware

Nachfolgend werden alle Komponenten aufgelistet, die bestellt werden müssen. Gehäuse- und Druckteile sind in [/cad]() abgelegt und können auf unterschiedliche Weise gefertigt 
werden, weshalb sie in der Kostenaufstellung nicht berücksichtigt werden.

| Anzahl | Bezeichnung | Beschreibung | Preis |
|:---:| --- | --- |:---:|
| 1x | [Felfil Evo Basic Kit](https://felfil.com/shop/felfil-evo-basic-kit/?v=5ea34fa833a1) | Basiskomponenten des Extruders als Bausatz | 299,00€ |
| 1x | [Netzteil 24V 320W](https://www.conrad.de/de/p/mean-well-rsp-320-24-ac-dc-netzteilbaustein-geschlossen-13-4-a-321-6-w-24-v-dc-1293056.html) | Primäre Spannungsquelle des Systems | 62,38€ |
| 1x | [Spannungswandler XL4016](https://www.az-delivery.de/products/xl4016-step-down-buck-converter-dc-dc?_pos=5&_sid=a325961b4&_ss=r) | Spannungsversorgung der 12V-Komponenten (Extrudermotor & Lüfter) | 8,49€ |
| 1x | [Spannungswandler LM2596S](https://www.az-delivery.de/products/lm2596s-dc-dc-step-down-modul-1?_pos=6&_sid=619fecdd6&_ss=r) | Spannungsversorgung der 5V-Komponenten (Display & Arduino) | 5,29€ |
| 3x | [Mosfet Modul IRF520](https://www.az-delivery.de/products/irf520-mos-driver-modul-0-24v-5a?_pos=1&_sid=0db666f69&_ss=r) | Steuerung der Heizpatronen | 4,29€ |
| 3x | [Heizpatrone 24V](https://www.conrad.de/de/p/24v-40w-heizpatrone-j-head-hotend-heater-cartridge-3d-drucker-802287254.html) | Heizmodule des Extruders | 4,50€ |
| 1x | [Temperatursensor PT100](https://www.conrad.de/de/p/heraeus-nexensos-w-eyk-6-pt100-platin-temperatursensor-40-bis-500-c-100-3850-ppm-k-172412.html) | Sensor zur Bestimmung der Extrudertemperatur | 15,03€ |
| 1x | [Adafruit MAX31865](https://www.conrad.de/de/p/adafruit-pt1000-rtd-temperature-sensor-amplifier-max31865-802235187.html) | Modul zur Wandlung des Sensorsignals des PT100 | 19,33€ |

Die Hardware-Kosten summieren sich damit auf **299,00€** zzgl. diverser Versandkosten sowie der Gehäuse- bzw. Druckteile.

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

