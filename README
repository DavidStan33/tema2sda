Stan David-Gabriel 313CD
# Documentație Tema2 SDA - Sistem simplificat de indexare a fișierelor

Această arhivă conține rezolvarea completă a temei 2 la materia SDA.

## Structura Proiectului

```
../search_index
├── main.c - Conține bucla main, unde sunt citite comenzile.
├── commands.c - Conține implementarea comenzilor ADD, DEL, ADDKW, DELKW, FIND, TOPK, PRINT și PREFIX.
├── commands.h - Conține semnăturile funcțiilor folosite de commands.c.
├── files.c - Conține funcții pentru lista dublu înlănțuită de fișiere și listele de cuvinte ale acestora.
├── files.h - Definește structurile WordNode, NodeFile și ListFile, împreună cu funcțiile asociate.
├── tree.c - Conține funcțiile pentru arborele multicăi de regăsire.
├── tree.h - Definește structurile Tree și RefFileList, împreună cu semnăturile funcțiilor pentru arbore.
├── heap.c - Conține funcțiile pentru heap-ul folosit la TOPK.
├── heap.h - Definește structura Heap și semnăturile funcțiilor folosite de heap.c.
├── read.c - Conține funcția de citire dinamică a id-urilor de fișierelor.
├── read.h - Conține semnătura funcției folosite de read.c.
├── utils.c - Conține funcții ajutătoare simple.
├── utils.h - Conține semnăturile funcțiilor folosite de utils.c.
├── README - Detalii despre rezolvarea temei.
└── Makefile - Compilarea, rularea, curățarea și arhivarea temei.
```

## Structuri de date folosite

- **Lista dublu înlănțuită de fișiere**
  Fiecare nod de tip NodeFile reține identificatorul fișierului, scorul de
  relevanță, lista sa de cuvinte-cheie și legăturile prev/next. Fișierele sunt
  păstrate în ordinea în care apar în sistem.

- **Lista de cuvinte a unui fișier**
  Fiecare fișier are o listă simplu înlănțuită de WordNode. În această listă nu
  sunt păstrate duplicate, astfel încât un fișier nu poate avea același cuvânt
  de mai multe ori.

- **Arborele multicăi de regăsire**
  Fiecare nod din arbore corespunde unui caracter. Un drum de la rădăcină până
  la un nod terminal reprezintă un cuvânt-cheie complet. În nodurile terminale
  se păstrează o listă de referințe către fișierele care conțin acel cuvânt.

- **Listele de referințe din arbore**
  În nodurile terminale nu sunt copiate fișierele, ci se păstrează pointeri
  către nodurile reale din lista de fișiere.

- **Heap-ul pentru TOPK**
  Pentru fiecare comandă TOPK se construiește temporar un max-heap de referințe
  către fișiere. Prioritatea este dată de scorul descrescător, iar la scor egal
  departajarea se face lexicografic după id.

## Comenzi implementate

- **ADD**
  Se citește id-ul, scorul și lista de cuvinte-cheie. Dacă fișierul
  există deja, se afișează EXISTS. Altfel, se creează nodul de fișier și se
  inserează la finalul listei dublu înlănțuite. Pentru fiecare cuvânt-cheie se
  inserează cuvântul în arbore, iar în nodul terminal se adaugă o referință
  către fișier.

- **DEL**
  Se caută fișierul după id. Dacă nu există, se afișează NOT FOUND.
  Dacă există, se parcurge lista lui de cuvinte și se elimină referința către
  fișier din fiecare nod terminal corespunzător. Dacă un cuvânt rămâne fără
  referințe, acesta este eliminat din arbore prin ștergerea nodurilor devenite
  inutile. La final, fișierul este scos din lista dublu înlănțuită și memoria
  sa este eliberată.

- **ADDKW**
  Se caută fișierul după id. Dacă nu există, se afișează NOT FOUND.
  Dacă fișierul are deja cuvântul respectiv, operația este considerată reușită
  și se afișează OK fără alte modificări. Altfel, cuvântul este adăugat în lista
  de cuvinte a fișierului, este inserat în arbore și în nodul terminal se adaugă
  referința către fișier.

- **DELKW**
  Se caută fișierul după id. Dacă nu există, se afișează NOT FOUND.
  Dacă fișierul nu conține cuvântul, operația este considerată reușită și se
  afișează OK. Dacă perechea există, referința fișierului este eliminată din
  nodul terminal al cuvântului, cuvântul este șters din lista fișierului, iar
  nodurile inutile din arbore sunt eliminate. Dacă fișierul rămâne fără cuvinte,
  acesta este șters complet din sistem.

- **FIND**
  Se caută în arbore nodul terminal al cuvântului cerut. Dacă acesta nu există
  sau nu are fișiere asociate, se afișează EMPTY. Altfel, referințele către
  fișiere sunt copiate temporar într-un vector, sortate lexicografic după id și
  afișate.

- **TOPK**
  Se caută nodul terminal al cuvântului. Dacă nu există rezultate, se afișează
  EMPTY. Altfel, referințele către fișiere sunt introduse într-un max-heap. Din
  heap se extrag cel mult k fișiere, în ordinea scorului descrescător, iar la
  egalitate după identificator în ordine lexicografică.

- **PRINT**
  Se parcurge recursiv arborele multicăi în ordine lexicografică. Pentru fiecare
  nod terminal se reconstruiește cuvântul curent, se sortează fișierele asociate
  după id și se afișează cuvântul, numărul de fișiere și id-urile acestora.
  Dacă arborele nu conține niciun cuvânt, se afișează EMPTY.

- **PREFIX**
  Se caută mai întâi nodul corespunzător ultimului caracter din prefix. Dacă
  prefixul nu există în arbore, se afișează EMPTY. Altfel, se parcurge recursiv
  întregul subarbore pornind din acel nod. Pentru fiecare nod terminal întâlnit
  se colectează referințele către fișiere. Pentru a evita duplicatele, fiecare
  fișier este adăugat o singură dată în vectorul temporar de rezultate. La final,
  rezultatele sunt sortate lexicografic după id și afișate.

## Compilarea și rularea programului

```
make build			# Compilează programul
make run			# Rulează programul
make pack			# Împachetează programul într-un fișier zip pentru a fi gata de trimitere
make clean			# Șterge fișierele create de build
```
