Lukas Persson
C++
STI

Datainsamling:
* Kan skriva in valfritt antal mätvärden
* Exempelvis bokstäver hanteras robust
* Heltal och decimaltal stöds

Statistik:
* Antal värden
* Summa
* Varians
* Medelvärde
* Min- och maxvärde
* Standardavvikelse

Menygränssnitt:
1. Lägg till mätvärden
2. Visa Statistik
3. Söka efter ett värde
4. Sortera efter stigande/fallande
5. Generera slumpmässiga mätvärden
6. Avsluta Programmet

* Tidsstämplade mätningar - Varje värde sparas med aktuell klocktid
* Sensorstimulering - Kan generera valfritt antal slumpmässiga mätvärden mellan 20-30 grader celsius

Såhär kör du programmet:
1. Öppna Powershell i mappen där main.cpp ligger
2. Skriv följa kommandon i terminalen
* chcp 65001
* g++ main.cpp -o matvarden
* ./matvarden för att köra
3. Följ sedan menyn

* Anledningen till varför jag valde just c++ är för att den har en tydlig struktur samt att den ger möjlighet för mig att ha god kontroll över datatyper.
* Datastruktur - std::vector<double> väldigt flexibel lista som kan växa dynamiskt samt hantera både heltal och flyttal
* Felhantering - Inmatningen valideras med cin.fail() för att undvika krascher vid ogiltig input
* Slumpgenerering - Använder <random> för att stimulera sensordata på realistiskt sätt
* Tidsstämplar - Implementerade med std::chrono
* Statistikberäkningar - Genomförs med standardbibliotekets algoritmer och for-loopar som ger tydlighet


Exempel:
===== MENY =====
1. Lägg till nya mätvärden
2. Visa statistik
3. Söka efter ett värde
4. Sortera listan
5. Generera slumpmässiga mätvärden
6. Avsluta
================
Välj ett alternativ: 5
Hur många värden ska simuleras? 3
3 slumpmässiga värden (20–30 °C) har genererats.

Välj ett alternativ: 2
--- Statistik ---
Antal värden: 3
Summa: 77.25
Medelvärde: 25.75
Minvärde: 21.3 (kl. 10:42:31)
Maxvärde: 29.8 (kl. 10:42:33)
Varians: 12.25
Standardavvikelse: 3.5
