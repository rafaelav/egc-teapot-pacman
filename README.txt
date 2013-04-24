Version of teapot PacMan - 2011

Voiculescu Rafaela


1)Prezentare aplicatie: 

-sa se implementeze o versiune a jocului PacMan in care pentru fiecare nivel PacMan(reprezentat printr-un ceainic) trebuie sa aprinda felinare pentru a putea obtine cheia de trecere catre nivelul urmator (cheia apare cand toate felinarele - 4 la numar- sunt aprinse)
-felinarele sunt aprinse daca PacMan are aceeasi culoare de lumina cu culoare luminii felinarelor (PacMan va trebui sa isi schimbe culoare luminii pentru a aprinde fiecare felinar)
-PacMan are initial 2 vieti. El poate sa si le piarda daca intra in coliziune cu un 'Enemy' (la primul nivel sunt 2, numarul lor creste odata cu inaintarea in joc)

2)Utilizare:
-tastele folosite pentru joc:
	* (sageata dreapta) PacMan merge spre dreapta
	* (sageata stanga) PacMan merge spre stanga
	* (sageata sus)PacMan merge in sus
	* (sageata jos)PacMan merge in jos
	* (PGUP) creste intensitatea luminii lui PacMan
	* (PGDN) scade intensitatea luminii lui PacMan
	* (HOME) cicleaza in luminile lui PacMan inainte
	* (END) cicleaza in luminile lui PacMan inapoi
	* (ESC) inchide fereastra de joc	

3)Implementare:
-tema a fost scrisa in: Microsoft Visual C++ 2010 Express, sistem de operare: Windows 7

4)Testare:
-am testat programul rulandu-l in Microsoft Visula C++ 2010 Express

5)Probleme aparute:
	-din cauza faptului ca atat pozitia pe plan a lampilor cat si a inamicilor este generata aleator, uneori s-a intamplat ca, de exemplu o lampa sa fie pe aproximativ aceeasi pozitie cu ceainicul => coliziune din start => ceainicul nu poate fi mutat.
	-pentru a rezolva problema aparitiei de obiecte suprapuse din cauza generari aleatoare a pozitie acestora am creat o functie care este apelata dupa creerea obiectelor in init() (si dupa crearea fiecarui extra inamic). Scopul acestei functii este sa verifice deca exista obiecte suprapuse(adica au pozitii foarte apropiate - distanta dintre ele e mai mica decat suma razelor sferelor ce le pot contine) caz in care va schimba pozitia obiectului asupra careia a fost apelata. 


6)Explicatie aspecte importante din cod:

Obs: pozitia obiectelor este determinata aleator folosind rand() (dar astfel incat sa nu fie in afara planului => intre anumite margini); de asemenea si culoare lumininii unei lampi e generata aleator (tot cu rand si intre anumite limite astfel incat culoarea sa nu fie prea stearsa)

Prezentare Clase Introduse:
	Clasa Teapot:
	- obiectul de tip Teapot este de fapt PacMan (jucatorul)
	- acest obiect are o functie de mutare MoveTeapot care in functie de tasta apasta realizeaza mutarea ceainicului pe ecran. Tot in aceasta functie se face verificarea pentru a vedea daca ceainicul "cade" de pe plan (se revine la pozitia initiala daca mutarea a facut ca ceainicul sa nu mai fie situat pe plan), tot aici se verifica daca ceainicul a intrat in coliziune cu o lampa (nu i se permite sa treaca prin ea), aici se verifica si daca ceainicul aprinde o lampa si daca a luat cheia de trecere la nivelul urmator (a intrat in coliziune cu ea)
	- functiitle ce mai apar aici sunt IncreaseLight (la apasarea tastei PGUP se apeleaza din MoveTeapot aceasta functie pentru a creste raza si intensitatea luminii ceainicului), DecreaseLight (analog IncreaseLight - la apasarea tastei PGDN - scade intensitatea si raza luminii ceainicului), ShiftColor (la apasarea tastei HOME se apeleaza aceasta functie din MoveTeapot cu parametrul 0 pentru a stii ca se face ciclare prin lumini in sens "inainte", respectiv la apasarea tastei END se apeleaza functia cu parametrul 1 pentru a se stii ca se face ciclarea prin culorile luminii ceainicului "inapoi")
	-functia SetPosition - apelata in programul principal pentru a aseza corect ceainicul pe plan (initial este jumatate deasupra, jumatate sub - originea sa aflandu-se in centrul sau -> trebuie ridicat pe Oy)
	- functia addColor apelata in programul principal de fiecare data cand se creaza o lampa pentru a se adauga culoare ce i-a revenit acelei lampi si lui PacMan (ca acesta sa stie ce lumina au toate lampile si pentru a avea luminile respective pentru a putea sa aprinda lampile ulterior in joc)

	Clasa Enemy:
	-un obiect de tip Enemy este inamicul lui PacMan (daca intra in coliziune cu acesta, PacMan o sa isi piarda din vieti)
	-are o functie de mutare MoveEnemy unde se realizeaza mutarea inamicului (acesta isi schimba aleator modul in care se misca) si tot aici se verifica daca inamicul intra in coliziune cu alti inamici cu ceainicul (caz in care se va intoarce valoarea true -> adica PacMan a pierdut o viata), sau cu lampile
	!Observatie: cand intra in coliziune cu ceainicul, inamicul isi va schimba traiectoria, pentru a nu ramane in coliziune permanenta cu ceainicul si astfel consumandu-i toate vietile

	Clasa Lamp:
	-un obiect de tip Lamp este un felinar
	-acesta se aprinde daca ceainicul are o lumina de culoare echivalenta si se afla suficient e aproape de el. Lumina generata de el va scade in intensitate pana se va stinge. (se aprinde iar daca ceainicul il activeaza)
	-pentru a "aprinde" o lampa aceasta trebuie sa se afle la o anuita distanta de ceainic, distanta unde intensitatea luminii acestuia este suficient de puternica. Acest lucru se testeaza in Teapot calculand distanta dintre lampa si ceainic si apoi calculand cu formula 1/(atenuare_constanta + atenuare_liniara*dist + atenuare_quadrica*dist*dist) intensitatea luminii ceainicului pentru pozitia in care se afla lampa. daca valoarea obtinuta este mai mare decat o intensitatea minima atunci lampa se poate aprinde

	Pentru a se verifica coliziunile intre 2 obiecte:
	-in clasa Object3D exista functia ColisionDetected care returneaza true daca intre obiectul de care este apelata si obiectul dat ca parametru exista coliziune.
	-intre doua obiecte apare coliziune daca suma razelor sferelor ce "contin" aceste obiecte este mai mica decat disctanta dintre centrele lor. 
	-raza sferei setate in program pentru ceainic este 1, pentru dodecaedru este sqrt(3), iar pentru lampa 1.05. Bineinteles ca acestea sunt scalate in functie de modul in care au fost scalate si obiectele.

	Program principal:
	-aici se realizeaza initializarile si se implementeaza partea de joc
	-exista varibilele gameover, gamewon, lives si level.
	-de fiecare data cand se realizeaza o mutare si imaginea trebuie reinoita se va verifica daca variabila lives este egala cu 0  caz in care jocul se incheie =>variabila gameover devine true (pentru a se iesi din fereastra se apasa <ESC>) (se afiseaza mesaj corespunzator pentru pierderea jocului ("Game over! Press <ESC> to exit"))
	-pentru fiecare inamic se verifica daca in urma mutarii acesta a intrat in coliziune cu ceainicul, caz in care se decrementeaza numarul de vieti ale jucatorului si se afiseaza mesajul "You have x lives left!"
	-tot aici se verifica daca toate lampile sunt aprinse, caz in care obiectul cheie (myKey) ce reprezinta cheia de trecere la nivelul urmator, va deveni vizibil (myKey->Visible=true)
	-cand ceainicul va fi mutat functia sa de mutare va returna true daca acesta va intra in coliziune cu cheia de trecere la nivelul urmator => variabila gamewon devine true
	-in cazul in care nivelul curent a fost trecut se trece la nivelul urmator avand un numar mai mare de inamici (cu 1 inamic in plus), dupa ce s-a apelat functia RestartLights care seteaza baseId-ul la 0 (adica practic, va reseta luminile; alfel la un moment dat in memorie ar fi fost mai mult de 7 lumini -> imposibil)
	-functia update() care face reinoirea imaginii afisate pe ecran are un Sleep(15).


6) Functionalitati bonus:
	-viteza de rotatie a luminii lampilor difera in functie de lampa 
	-cat timp este aprinsa o lampa aceasta "emite" lumina (GL_EMiSSION)
	-exista nivele suplimentare, la fiecare numarul de inamici crescand cu 1 fata de nivelul precedent
	-la switch intre culorile luminii ceainicului se retine deschiderea si apoi la switch inapoi pe acea lumin se intoarce la ultima deschidere retinuta
	-pentru fiecare nivel mai apar in scena cel mult 2 inamici suplimentari care sunt de tip tetraedru (acestia apar in scena dupa un anumit timp si raman pana la trecerea la nivelul urmator sau pana cand ceainicul pierde toate vietile)

7)Continut arhiva:

README.txt

In PacManEgc sunt:
	-PacManEgc.sln
	-folder PacManEgc:
	contine fisierele .cpp si .h
