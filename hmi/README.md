# Human Machine Interface <!-- omit in toc -->

<p align="center"><img src="/hmi/preview.png?raw=true" alt="HMI Preview"></p>

Das Interface läuft auf einem [Nextion NX4024K032](https://nextion.tech/datasheets/nx4024k032/) Display und wurde mit dem
[Nextion Editor](https://nextion.tech/nextion-editor/#_section1) für Windows erstellt. Es besteht aus 6 Seiten, die im 
Wesentlichen den States der [FSM in der Steuerung](https://github.com/lukaswiesehan/filamentextruder/tree/master/arduino/filamentextruder#finite-state-machine) 
entsprechen. In [/screenshots](https://github.com/lukaswiesehan/filamentextruder/tree/master/hmi/screenshots) können die einzelnen
Seiten angeschaut werden.

- [Display Setup](#display-setup)
- [Font Awesome Icons](#font-awesome-icons)

## Display Setup

- Um das HMI-Programm auf das Display zu übertragen wird der [Nextion Editor](https://nextion.tech/nextion-editor/#_section1) benötigt. 
- Das Display muss per USB an den Computer angeschlossen werden, wofür ein [USB-TTL-Converter](https://www.az-delivery.de/products/ftdi-adapter-ft232rl?_pos=1&_sid=0be74c2ba&_ss=r) benötigt wird.
- Die [`extruder.HMI`](/hmi/extruder.HMI)-Datei wird im Nextion Editor geöffnet.
- Im Nextion Editor wird das Programm über den Upload-Button in der Werkzeugleiste auf das Display übertragen.
- Fertig!

## Font Awesome Icons

Alle im Interface verwendeten Icons stammen aus dem kostenlosen Symbolsatz von [Font Awesome](https://fontawesome.com/). Sie wurden
über die entsprechenden `.otf`-Dateien eingebunden, die unter [SIL OFL 1.1](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL) lizensiert sind.