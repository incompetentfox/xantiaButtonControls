# xantiaButtonControls
##Arduino code to interpret the analog voltage output from certain Citroen steering wheel button controls and convert it to a digital output to control a modern amplifier.

![Amplifier Datasheet.](http://www.st.com/content/ccc/resource/technical/document/datasheet/35/01/97/6b/20/ce/40/6f/CD00211320.pdf/files/CD00211320.pdf/jcr:content/translations/en.CD00211320.pdf)

Citroen steering wheel buttons designed to interact with factory supplied Blaupunkt and Clarion head units are multiplexed using resistor ladders. 
[Wiring Diagram](https://github.com/incompetentfox/xantiaButtonControls/blob/master/X1.odpory.dalkoveho.ovladani.radia.cc.gif)

The aim of this project is to convert this signal to a digital output for each button in order to control a more modern audio system. 

A side effect will be enabling 'chording' of two buttons on either side to effectively act as an extra button.
