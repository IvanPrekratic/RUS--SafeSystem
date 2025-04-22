# RUS--SafeSystem
## Opis sustava
Sustav za sef je ugradbeni sustav razvijen na platformi Arduino, dizajniran za sigurno čuvanje vrijednosti. Sustav omogućuje otključavanje vrata pomoću tipkovnice, pri čemu korisnik unosi ispravan PIN kod. Ako je unos ispravan, aktivira se servo motor koji otključava sef te se na ekranu prikazuje poruka koja ukazuje na uspješno otključavanje sefa. U suprotnom, ekran ukazuje na neuspjeli pokušaj uz odgovarajuću poruku (krivi PIN ili temperatura izvan postavljenih granica). Sustav dodatno uključuje analogni temperaturni senzor koji onemogućuje otključavanje ako je temperatura manja od 0° C ili veća od 38° C. Sustav također omogućava promjenu PIN-a.
## Slika spoja
![spoj_safe](https://github.com/user-attachments/assets/e621cd60-f28e-445a-8e11-6868f3404aee)
## Cilj projekta
Cilj projekta je razviti siguran, pouzdan i lako implementiran sustav za sef koji koristi Arduino platformu. Sustav omogućava:<br>
•	Sigurno otključavanje pomoću PIN-a<br>
•	Vizualnu signalizaciju uspješnih i neuspješnih pokušaja otključavanja preko LCD ekrana<br>
•	Mehaničku kontrolu putem servo motora<br>
•	Sigurnosnu funkciju blokiranja otključavanja pri visokim temperaturama<br>
•	Promjenu zadane lozinke<br>
## Potencijalna korist projekta
•	Povećanje sigurnosti za osobne i poslovne prostore<br>
•	Implementacija u kućne sefove, uredske ladice ili druge sustave zaključavanja<br>
•	Mogućnost proširenja funkcionalnosti za daljinsku kontrolu ili biometrijsku autentifikaciju<br>
## Postojeća slična rješenja
Na tržištu postoje komercijalni digitalni sefovi koji koriste PIN kod, RFID kartice ili biometrijske metode. Međutim, većina njih ne uključuje temperaturnu zaštitu niti mogućnost prilagodbe i programiranja prema specifičnim zahtjevima korisnika.
## Skup korisnika
•	Pojedinci koji žele osigurati osobne vrijednosti<br>
•	Uredi i tvrtke s potrebom za sigurnim spremanjem dokumenata<br>
•	Studenti i hobisti zainteresirani za razvoj ugradbenih sustava<br>
## Mogućnost prilagodbe rješenja
Sustav se u budućnosti može nadograditi dodavanjem:<br>
•	RFID autentifikacije<br>
•	Biometrijskih senzora<br>
•	Bluetooth/Wi-Fi povezivosti za daljinsko upravljanje<br>
•	Prikaza informacija na mobilnoj aplikaciji<br>
## Opseg projektnog zadatka
Projekt uključuje:<br>
•	Razvoj softvera za Arduino<br>
•	Dizajn i implementaciju elektroničkih komponenti<br>
•	Testiranje sigurnosnih aspekata sustava<br>
•	Dokumentaciju i analizu izvedbe sustava<br>
## Moguće nadogradnje
•	Višekorisnički sustav s različitim PIN-ovima<br>
•	Dnevnik otključavanja i neuspjelih pokušaja<br>
•	Integracija sa sigurnosnim alarmom<br>
•	IoT povezivost za nadzor putem interneta<br>

## Dijagram aktivnosti (UML)
1.	Korisnik unosi PIN<br>
2.	Sustav provjerava ispravnost PIN-a<br>
o	Ako je PIN točan i temperatura prihvatljiva → otključavanje<br>
o	Ako je PIN netočan → signalizacija neuspjeha<br>
o	Ako je temperatura previsoka → zabrana otključavanja<br>
3.	Prikaz statusa na LCD ekranu<br>
## Plan ispitivanja
•	Testiranje ispravnog i neispravnog unosa PIN-a<br>
•	Provjera rada servo motora pri otključavanju<br>
•	Testiranje temperaturnog senzora pri različitim temperaturama<br>
•	Testiranje vizualne signalizacije<br>
## Shema sustava
Električna shema sustava uključuje povezivanje tipkovnice, LCD ekrana, servo motora i temperaturnog senzora s Arduino mikrokontrolerom.
## Dokumentirani kôd
Sav kôd će biti detaljno komentiran, s objašnjenjem funkcija, ulaznih i izlaznih parametara te glavnih dijelova sustava. To će omogućiti laku prilagodbu i nadogradnju sustava.
