# Arduino-Code: Motorsteuerung <!-- omit in toc -->

Da die Steuerung des Wicklungsmechanismus eine hohe Rechenfrequenz benötigt, wird diese
von der restlichen Steuerung entkoppelt und läuft auf einem Arduino Nano. Der Steuerungsalgorithmus der Wicklung basiert im Wesentlichen auf der [AccelStepper](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)-Library. 

###### Inhalt <!-- omit in toc -->
- [Funktionsweise des Wicklungsmechanismus](#funktionsweise-des-wicklungsmechanismus)
- [Steuerungsalgoritmus](#steuerungsalgoritmus)
- [Kommunikation mit dem Arduino Mega](#kommunikation-mit-dem-arduino-mega)
- [Benötigte Libraries](#benötigte-libraries)

## Funktionsweise des Wicklungsmechanismus

###### Rendering des Wicklungsmechanismus <!-- omit in toc -->
![Wicklungsmechanismus](wicklungsmechanismus.png?raw=true)

Der Kern des Wicklungsmechanismus sind zwei Schrittmotoren. Einer dieser Motoren dreht die Spule, auf die das Filament aufgewickelt werden soll, der andere Motor positioniert das Filament auf der Breite der Spule.

Die Positionierung des Filaments erfolgt über die Rotation einer Gewindestange. Der Positionierer selbst ist mit einer Mutter verklebt, die sich auf der Gewindestange befindet. Die Wahl der Gewindegröße zu `M12` führt dazu, dass die Geschwindigkeiten der
beiden Motoren zu jedem Zeitpunkt gleich sind. Das liegt daran, dass die Steigung des 
Gewindes von `1,75 mm` der Filamentbreite entspricht. So muss der Führungsmotor genau
eine Umdrehung machen, um das Filament zu versetzen, während die Spule ebenfalls genau 
eine Umdrehung macht.

## Steuerungsalgoritmus

Der Ablauf der Steuerung wird im wesentlichen durch die Konstruktion des Wicklungsmechanismus 
bestimmt. Grundsätzlich werden die Motoren lediglich für einige Umdrehungen angesteuert, bevor die 
Rotationsgeschwindigkeit neu berechnet wird, da die Wicklung mit jeder Lage Filament auf der Spule 
verlangsamt werden muss, weil sich der
Wicklungsradius um einen Filamentdurchmesser erhöht.

Der Wicklungsmotor wird also ständig für eine volle Lage Filament, also einige volle Umdrehungen 
angesteuert, wobei die Drehrichtung gleich bleibt.

Der Positionierungsmotor hingegen muss nach jeder Lage Filament nicht nur seine
Drehgeschwindigkeit aktualisieren, sondern auch seine Drehrichtung ändern.

Der sich daraus ergebende Ablauf ist nachfolgend schematisch dargestellt.

###### Schema des Steuerungsalgorithmus <!-- omit in toc -->
<p align="center"><img src="motorsteuerung_scheme.png?raw=true" alt="Schema Motorsteuerung"></p>

## Kommunikation mit dem Arduino Mega

Da das System einige Einstellungen durch den Bediener ermöglicht, die dementsprechend auf dem Display 
getätigt werden und damit auf dem Arduino Mega gespeichert werden, muss dieser mit dem Arduino Nano
kommunizieren. Die Größe der eingesetzten Spule zur Wicklung des Filaments ist maßgeblich für die 
Steuerung der Motoren. Da Filamentspulen in leicht unterschiedlichen Ausführungen geliefert werden,
können die wesentlichen Abmaße der Spule über das Display angepasst werden. 

Um diese Parameter an den Arduino Nano zu übertragen, bietet sich die serielle Schnittstelle an. Die 
Parameter werden nacheinander in einen String gespeichert und durch ein Semikolon getrennt. So ergibt 
sich ein Muster, welchem jede Nachricht entsprechen muss, die vom Arduino Mega an den Nano gesendet 
wird: `SPOOL_WIDTH;SPOOL_PICKUP_DIAMETER;SPOOL_INNER_DIAMETER;SPOOL_OUTER_DIAMETER;SPEED_OFFSET;`.

Da die aktuelle Wicklungsgeschwindigkeit mithilfe dieser Parametern auf dem Arduino Nano berechnet
wird, aber auf dem Display angezeigt werden soll, muss sie nach jeder Aktualisierung an den 
Arduino Mega zurück gesendet werden. Diese Nachrichten entsprechen folgendem Muster: `WINDUP_SPEED;`.

## Benötigte Libraries

- [AccelStepper.h](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)