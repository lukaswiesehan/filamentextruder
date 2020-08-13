## Nextion Library Setup

Zur einfachen Kommunikation zwischen Display und Arduino wird die offizielle 
[Nextion Library](https://github.com/itead/ITEADLIB_Arduino_Nextion) verwendet.

### Konfiguration

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

Analog zu den Erweiterungen der `NexButton`-Klasse wird auch die `NexPicture`-Klasse erweitert.

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
