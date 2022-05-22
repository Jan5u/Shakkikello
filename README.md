<div align="center">

<img src="/kytkentakaavio.png">
<h1>Shakkikello</h1>

</div>

## Projektin tavoitteet

Projektin tavoitteena oli rakentaa ja koodata toimiva shakkikello, jota hyödyttämällä voitaisiin pelata vähintään shakin “Bullet” pelimuotoa.


## Ryhmän projektiaihe

Projektiaiheena on shakkikello, jossa voidaan pelin alussa valita haluttu ajan määrä pelaajille.

Kun aika on valittu se tulostuu molempien pelaajien  
7-segmenttinäytöille ja valkoisen pelaajan peliaika alkaa laskemaan nappia painamalla. Peli päättyy, kun jommankumman pelaajan aika on loppunut.


## Käytetyt tekniikat, komponentit ja työkalut

Shakkikello on rakennettu mikrokontrolleri Arduino Unon ympärille. Pelimuodot valitaan LCD-näytöltä painimien avulla. Molempien pelaajien ajat tulostuvat 7-segmenttinäytöille.

7-segmenttinäyttöjen ohjauksessa käytetään hyväksi kuutta Serial to Parallel (74HC595) piiriä.

Ajan kulumista ja vuoroja pelaajien välillä vaihdellaan kahden painikkeen avulla.
Laitteen ohjelmointi on tehty kokonaan Arduinon C/C++ -kielellä.

Projektin lopussa valmiina oli toimiva shakkikello, jolla pystytaan mittaamaan aikaa neljään eri pelimuotoon.


## Tekijät

* [Antti Alajääskö]()
* [Kimmo Korhonen]()
* [Jan-Henrik Lapinoja](https://www.linkedin.com/in/jan-henrik-lapinoja/)
