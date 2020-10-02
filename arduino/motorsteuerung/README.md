# Arduino-Code: Motorsteuerung <!-- omit in toc -->

Da die Steuerung des Wicklungsmechanismus eine hohe Rechenfrequenz benötigt, wird diese
von der restlichen Steuerung entkoppelt und läuft auf einem Arduino Nano. Der Steuerungsalgorithmus der Wicklung basiert im Wesentlichen auf der [AccelStepper](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)-Library. 

###### Inhalt
- [Funktionsweise des Wicklungsmechanismus](#funktionsweise-des-wicklungsmechanismus)
        - [Rendering des Wicklungsmechanismus](#rendering-des-wicklungsmechanismus)
- [Steuerungsalgoritmus](#steuerungsalgoritmus)
        - [Schema des Steuerungsalgorithmus](#schema-des-steuerungsalgorithmus)
- [Benötigte Libraries](#benötigte-libraries)

## Funktionsweise des Wicklungsmechanismus

###### Rendering des Wicklungsmechanismus
![Wicklungsmechanismus](wicklungsmechanismus.png?raw=true)

Der Kern des Wicklungsmechanismus sind zwei Schrittmotoren. Einer dieser Motoren dreht die Spule, auf die das Filament aufgewickelt werden soll, der andere Motor positioniert das Filament auf der Breite der Spule.

Die Positionierung des Filaments erfolgt über die Rotation einer Gewindestange. Der Positionierer selbst ist mit einer Mutter verklebt, die sich auf der Gewindestange befindet. Die Wahl der Gewindegröße zu `M12` führt dazu, dass die Geschwindigkeiten der
beiden Motoren zu jedem Zeitpunkt gleich sind. Das liegt daran, dass die Steigung des 
Gewindes von `1,75 mm` der Filamentbreite entspricht. So muss der Führungsmotor genau
eine Umdrehung machen, um das Filament zu versetzen, während die Spule ebenfalls genau 
eine Umdrehung macht.

## Steuerungsalgoritmus

Der Ablauf der Steuerung wird im wesentlichen durch die Konstruktion des Wicklungsmechanismus bestimmt. Grundsätzlich werden die Motoren lediglich für einige Umdrehungen angesteuert, bevor die Rotationsgeschwindigkeit neu berechnet wird, da die Wicklung mit jeder Lage Filament auf der Spule verlangsamt werden muss, weil sich der
Wicklungsradius um einen Filamentdurchmesser erhöht.

Der Wicklungsmotor wird also ständig für eine volle Lage Filament, also einige volle Umdrehungen angesteuert, wobei die Drehrichtung gleich bleibt.

Der Positionierungsmotor hingegen muss nach jeder Lage Filament nicht nur seine
Drehgeschwindigkeit aktualisieren, sondern auch seine Drehrichtung ändern.

Der sich daraus ergebende Ablauf ist nachfolgend schematisch dargestellt.

###### Schema des Steuerungsalgorithmus
![Schema Motorsteuerung](motorsteuerung_scheme.png?raw=true)

## Benötigte Libraries

- [AccelStepper.h](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)