# Arduino-Code: Motorsteuerung <!-- omit in toc -->

Da die Steuerung des Wicklungsmechanismus eine hohe Rechenfrequenz benötigt, wird diese
von der restlichen Steuerung entkoppelt und läuft auf einem Arduino Nano. Der Steuerungsalgorithmus der Wicklung basiert im Wesentlichen auf der [AccelStepper](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)-Library. 

- [Funktionsweise des Wicklungsmechanismus](#funktionsweise-des-wicklungsmechanismus)
- [Steuerungsalgoritmus](#steuerungsalgoritmus)
- [Benötigte Libraries](#benötigte-libraries)

## Funktionsweise des Wicklungsmechanismus

![Wicklungsmechanismus](wicklungsmechanismus.png?raw=true)

## Steuerungsalgoritmus

Der Ablauf der 

## Benötigte Libraries

- [AccelStepper.h](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)