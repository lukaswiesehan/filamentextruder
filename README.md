# Filament-Extruder <!-- omit in toc -->

<p align="center"><img src="/rendering.png?raw=true" alt="HMI Preview"></p>

Bachelorprojekt im Studiengang Mechatronik, HAW Hamburg.  
*Entwickelt von Tobias Freytag, Anton Neike, Max Sahlke, Lukas Wiesehan.  
Betreut von Prof. Dr. Dietmar Pähler.*

- [Einführung](#einführung)
- [Repo-Struktur](#repo-struktur)
- [Hardware](#hardware)
  - [Bestellliste](#bestellliste)
  - [Verdrahtung des Systems](#verdrahtung-des-systems)

## Einführung

Im Rahmen des Bachelorprojekts im 5. Semester des Bachelorstudiengangs Mechatronik an der HAW Hamburg soll eine Anlage konstruiert und realisiert werden, 
die aus Kunststoffgranulat 3D-Druck Filament extrudiert und dieses auf entsprechende Rollen aufspult. Übergeordnetes Ziel ist es, Prototypen oder 
fehlgeschlagene Druckteile zu schreddern, um sie erneut zu Filament zu extrudieren und dieses erneut zu verwenden. Da sowohl die Qualität des Kunststoffs, als
auch die Verarbeitbarkeit unter häufigem Aufschmelzen leiden, soll das mit der Anlage hergestellte Filament lediglich für den Druck von Prototypen verwendet
werden.

###### Funktionsschema <!-- omit in toc -->
![Funktionsschema](/funktionsschema.png "Funktionsschema")

Die im Funktionsschema grün dargestellten Elemente sind Teil dieses Projekts. Die Konstruktion eines Schredders ist im Rahmen dieses Projekts nicht möglich, allerdings
kann das System in Folgeprojekten durchaus mit einem Schredder erweitert werden, der auf den Trichter des Extruders aufgesetzt werden sollte.

## Repo-Struktur

Das Stammverzeichnis des Repositorys beinhaltet alles, was für eine Rekonstruktion des Systems notwendig ist. Es teilt sich in folgende Unterverzeichnisse auf.

| Verzeichnis | Inhalt |
|---|---|
| [`/arduino`](/arduino/filamentextruder) | Arduino-Projekt, Liste der notwendigen Libraries, Anleitung zur notwendigen Modifikation der Nextion-Library |
| [`/cad`](/cad) | CAD-Modell des fertigen Systems, `.stl`-Dateien der gedruckten Einzelteile |
| [`/hmi`](/hmi) | `.HMI`-Datei und Anleitung zur Installation des Interfaces auf dem Nextion Display, Screenshots des Interfaces |

Die hier abgelegten Daten entsprechen dem finalen Entwicklungsstand des Systems. Die **ausführliche Projektdokumentation**, in der die einzelnen Entwicklungsschritte 
während des Projekts näher ausgeführt sind, ist als [Wiki dieses Repos](https://github.com/lukaswiesehan/filamentextruder/wiki) realisiert.

## Hardware

Nachfolgend werden alle Komponenten aufgelistet, die bestellt werden müssen. Gehäuse- und Druckteile sind in [`/cad`](/cad) abgelegt und können auf unterschiedliche Weise gefertigt 
werden, weshalb sie in der Kostenaufstellung nicht berücksichtigt werden. Zudem werden Kabel zur Verdrahtung des Systems benötigt, die hier ebenfalls nicht aufgelistet sind.

### Bestellliste

| Anzahl | Bezeichnung | Beschreibung | Preis |
|:---:| --- | --- |:---:|
| 1x | [Felfil Evo Basic Kit](https://felfil.com/shop/felfil-evo-basic-kit/?v=5ea34fa833a1) | Basiskomponenten des Extruders als Bausatz | 299,00€ |
| 1x | [Kaltgeräte-Einbaubuchse](https://www.conrad.de/de/p/kaltgeraete-steckverbinder-stecker-einbau-vertikal-gesamtpolzahl-2-pe-10-a-schwarz-1-st-501638.html) | Spannungsversorgung des Systems | 4,77€ |
| 1x | [Kaltegeräte-Anschlusskabel](https://www.conrad.de/de/p/hawa-1008230-kaltgeraete-anschlusskabel-schwarz-2-00-m-621535.html) | Spannungsversorgung des Systems | 4,86€ |
| 1x | [Netzteil 24V 320W](https://www.conrad.de/de/p/mean-well-rsp-320-24-ac-dc-netzteilbaustein-geschlossen-13-4-a-321-6-w-24-v-dc-1293056.html) | Primäre Spannungsquelle des Systems | 62,38€ |
| 1x | [Spannungswandler XL4016](https://www.az-delivery.de/products/xl4016-step-down-buck-converter-dc-dc?_pos=5&_sid=a325961b4&_ss=r) | Spannungsversorgung der 12V-Komponenten (Extrudermotor & Lüfter) | 8,49€ |
| 1x | [Spannungswandler LM2596S](https://www.az-delivery.de/products/lm2596s-dc-dc-step-down-modul-1?_pos=6&_sid=619fecdd6&_ss=r) | Spannungsversorgung der 5V-Komponenten (Display & Arduino) | 5,29€ |
| 3x | [Mosfet Modul IRF520](https://www.az-delivery.de/products/irf520-mos-driver-modul-0-24v-5a?_pos=1&_sid=0db666f69&_ss=r) | Steuerung der Heizpatronen | 4,29€ |
| 3x | [Heizpatrone 24V](https://www.conrad.de/de/p/24v-40w-heizpatrone-j-head-hotend-heater-cartridge-3d-drucker-802287254.html) | Heizmodule des Extruders | 4,50€ |
| 1x | [Temperatursensor PT100](https://www.conrad.de/de/p/heraeus-nexensos-w-eyk-6-pt100-platin-temperatursensor-40-bis-500-c-100-3850-ppm-k-172412.html) | Sensor zur Bestimmung der Extrudertemperatur | 15,03€ |
| 1x | [Adafruit MAX31865](https://www.conrad.de/de/p/adafruit-pt1000-rtd-temperature-sensor-amplifier-max31865-802235187.html) | Modul zur Wandlung des Sensorsignals des PT100 | 19,33€ |
| 2x | [Schrittmotortreiber SMD356C](https://www.conrad.de/de/p/waveshare-smd356c-three-phase-hybrid-stepper-motor-driver-806805951.html) | Steuerung der Wicklungsmotoren | 41,44€ |
| 2x | [Schrittmotor NEMA-17](https://www.conrad.de/de/p/joy-it-schrittmotor-nema-17-01-nema-17-01-0-4-nm-1-68-a-wellen-durchmesser-5-mm-1597325.html) | Antriebe des Wicklungsmechanismus | 27,20€ |
| 1x | [Nextion Display NX4024K032](https://www.amazon.de/MakerHawk-Nextion-NX4024K032-erweiterte-Versionen/dp/B072FN3SFH/) | Anzeige und Touch-Interface zur Steuerung des Systems | 38,44€ |
| 1x | [Arduino Mega](https://www.az-delivery.de/products/mega-2560-r3-board-mit-atmega2560-100-arduino-kompatibel-ohne-usb-kabel?_pos=15&_sid=7e3e6e2d1&_ss=r) | Steuerung des Extruder-Systems und des HMI | 13,79€ |

Die Hardware-Kosten summieren sich damit auf **635,03€** zzgl. diverser Versandkosten sowie der Gehäuse- bzw. Druckteile.

### Verdrahtung des Systems

tbd
