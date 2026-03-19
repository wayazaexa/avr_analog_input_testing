## Uppgift

Koppla in en LED matris och en analog joystick till en arduino. Skriv ut en etta på samma sätt som en tärning på LED matrisen.
Klickar man joysticken åt något håll ska talet ändras och det nya värdet skrivas ut på LED matrisen.
Rörs joysticken åt höger ska 1 adderas till talet, åt vänster ska talet 1 subtraheras från talet, uppåt ska 2 adderas till talet, och ner ska 2 subtraheras från talet.

## Wokwi

https://wokwi.com/projects/456953521227841537


## Branches

Detta repo innehåller flera grenar för de olika situationer vi kommer titta på

**OBS!** I denna branch kollar vi på den känsliga joystick vi har där input kan ses som digital i den mån att väldigt lite rörelse av joysticken ger max-utslag på mätta värden (dvs vi får nästan bara 0 eller 1023).


## make kommandon

* ```make``` - kompilerar programmet till bin-mappen, användbart om man vill ladda upp hex-filen till wokwi
* ```make isp``` - kompilerar programmet och flashar det till en inkopplad Arduino, förutsatt att man har kopplat in en Arduino till sin dator och satt rätt port (se kommentarer i Makefile)
* ```make clean``` - rensar genom att ta bort obj-mappen
* ```make fresh``` - rensar genom att ta bort alla obj-mappen samt bin-mappen
