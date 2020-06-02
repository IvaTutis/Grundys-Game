# Grundys-Game
Artificial Intelligence project - alpha beta pruning

Na početku igre, postoji jedna hrpa objekata. Prvi igrač dijeli hrpu na dvije hrpe nejednakih veličina.
Igra završava kad ostanu samo hrpe s manje ili jednako dva objekta, jer je njih nemoguće podijeliti na
dvije nejednake hrpe. U igri pobjeđuje onaj igrač koji je zadnji odigrao dozvoljenu podjelu hrpi.
Proučite pravila Grundyjeve igre i implementirajte računalnog protivnika algoritmom MiniMax s
alpha-beta podrezivanjem. Analizirati odigravanja za gomile veličine do 100.

https://en.wikipedia.org/wiki/Grundy%27s_game

Budući da je moj zadatak bio konstruirati računalnog protivnika, nažalost nemam testnih primjera, nego samo igru.
Testne primjere sam se potrudila zamjeniti screenshotovima igranja protiv računala koji se nalaze u pdf dokumentaciji.
Sam kod je pisan u C++ jeziku, te sam ga osobno pokretala u QT Creator IDE-u, tj na g++ kompajleru koji nije imao problema sa nullptr izrazom ili sličnim kodom.
(primjetila sam da Codeblocks ima nekih problema pa je potrebno uključiti novije standarde pri kompajliranju)
Protiv programa možete igrati preko pokretanja c++ koda, dakle diretno u terminalu (tekstualna interakcija implementirana).

Hvala Vam na vremenu i sretno igranje, 
Iva Tutiš
