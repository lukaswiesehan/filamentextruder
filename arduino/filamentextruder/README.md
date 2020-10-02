# Arduino-Code <!-- omit in toc -->

Die Steuerung des Systems ist als *Finite State Machine* umgesetzt und läuft auf einem Arduino Mega.
Die Temperaturregelung des Extruders erfolgt mithilfe eines Software-PID-Reglers, der die Leistung der Heizpatronen über Mosfets
steuern kann, welche per PWM-Signal angesprochen werden.

- [Finite State Machine](#finite-state-machine)
- [Benötigte Libraries](#benötigte-libraries)
- [Konfiguration des Systems](#konfiguration-des-systems)
- [Nextion Library Setup](#nextion-library-setup)
  - [Komponenten ein-/ausblenden](#komponenten-ein-ausblenden)
  - [Text bearbeiten](#text-bearbeiten)

## Finite State Machine

Die State Machine, die als Basis der Steuerung dient, kann wie folgt vereinfacht dargestellt werden. 

###### Finite State Machine <!-- omit in toc -->
![Finite State Machine](/arduino/filamentextruder/fsm_scheme.png?raw=true "Finite State Machine")

## Benötigte Libraries

- Nextion.h
- Adafruit_MAX31865.h
- PID_v1.h

## Nextion Library Setup

Zur einfachen Kommunikation zwischen Display und Arduino wird die offizielle 
[Nextion Library](https://github.com/itead/ITEADLIB_Arduino_Nextion) verwendet.
Für eine fehlerfreie Einbindung in das Projekt sind einige Änderungen an der Bibliothek notwendig, die nachfolgend kurz erläutert werden.

### Komponenten ein-/ausblenden

Der `NexButton`-, `NexText` und der `NexPicture`-Klasse Methoden werden hinzugefügt, die es
ermöglichen, diese Komponenten ein- bzw. auszublenden.

###### NexButton.h erweitern <!-- omit in toc -->
```c++
bool hide();
bool show();
```

###### NexButton.cpp erweitern <!-- omit in toc -->
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

Analog zu den Erweiterungen der `NexButton`-Klasse werden auch die `NexText`- und die `NexPicture`-Klasse erweitert.

### Text bearbeiten

Zudem wird die Methode `NexText.setText()` so verändert, dass zum Senden an das Display keine 
Konvertierung in Char-Arrays mehr vorgenommen werden muss.

###### NexText.h bearbeiten <!-- omit in toc -->
```c++
bool setText(String buffer);   
```

###### NexText.cpp bearbeiten <!-- omit in toc -->
```c++
bool NexText::setText(String buffer)
{
  ...
}
```
