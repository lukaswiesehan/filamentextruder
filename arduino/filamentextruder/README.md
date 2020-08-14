# Arduino-Code

Die Steuerung des Systems ist als *Finite State Machine* umgesetzt und läuft grundsätzlich auf allen gängigen Arduinos.
Vom Arduino Nano wird allerdings abgeraten, da der Variablenspeicher nur knapp ausreicht, was Performance-Nachteile mit sich bringen kann.
Die Temperaturregelung des Extruders erfolgt mithilfe eines Software-PID-Reglers, der die Leistung der Heizpatronen über Mosfets
steuern kann, welche per PWM-Signal angesprochen werden.

## Finite State Machine

Die State Machine, die als Basis der Steuerung dient, kann wie folgt vereinfacht dargestellt werden.

###### Finite State Machine
![Finite State Machine](/arduino/filamentextruder/fsm_scheme.png?raw=true "Finite State Machine")

## Nextion Library Setup

Zur einfachen Kommunikation zwischen Display und Arduino wird die offizielle 
[Nextion Library](https://github.com/itead/ITEADLIB_Arduino_Nextion) verwendet.
Für eine fehlerfreie Einbindung in das Projekt sind einige Änderungen an der Bibliothek notwendig, die nachfolgend kurz erläutert werden.

### Konfiguration

Falls das System mit einem Arduino Uno/Nano gesteuert werden soll, muss die 
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

Analog zu den Erweiterungen der `NexButton`-Klasse wird auch die `NexPicture`-Klasse erweitert.

### Text bearbeiten

Zudem wird die Methode `NexText.setText()` so verändert, dass zum Senden an das Display keine 
Konvertierung in Char-Arrays mehr vorgenommen werden muss.

###### NexText.h bearbeiten
```c++
bool setText(String buffer);   
```

###### NexText.cpp bearbeiten
```c++
bool NexText::setText(String buffer)
{
  [...]  
}
```
