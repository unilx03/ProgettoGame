# ProgettoGame
Progetto di Programmazione 2023

Checklist Mappe
- Adattare i codici per Nemici e Oggetti alla mappa
- Gestire collisioni tra Entità e Mappa
- Migliorare il caricamento da file della lista delle mappe
- Salvare su file la mappa con i nemici e oggetti generati (aggiornare quando un nemico viene sconfitto, un oggetto viene preso, un nuovo livello viene caricato)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OGGETTI (uso singolo) --> Un solo carattere descrive l'oggetto
[Ogni volta che viene terminata una stanza, ovvero che vengono uccisi tutti i nemici, viene droppato un oggetto in base alla probabilità ad esso associato] 
1.	Healing Potion
2. 	Carota magica (invincibilità per la stanza corrente)
3.	Boost punteggio (per la stanza corrente il punteggio è raddoppiato)
4.	Carota tagliente (aumento attacco per la stanza corrente)
5.	Boost soldi (per la stanza corrente i soldi sono doppi)
6.	Sconti (valido per la run successiva. Dimezza i prezzi di quanto venduto nel negozio)
7.	Scarpe carote (aumenta la velocità di movimento del personaggio per la stanza corrente) -- Da ragionare se fattibile con i thread
8.	Salterello (aumenta la potenza di salto)

OGGETTI (market) --> Più caratteri descrivono l'oggetto
[Il market è statico, quindi verrà caricato da file. Il personaggio appare nello schermo ma non si può muovere. La run inizia quando viene
cliccato l'apposito tasto]
1.	Boost HP (aumenta il numero di HP)
2. 	Boost attacco (aumenta i punti attacco)
3.	Boost velocità attacco (aumenta la velocità di attacco: diminuisce il delta di tempo tra lo sparo di un proiettile e l'altro)
4. 	Boost difesa (aumenta i punti difesa, riduce il danno inflitto dai nemici)
5.	Boost luck (aumenta i punti fortuna)
6.	Proiettili speciali (?) --Aggiunti in un secondo momento

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PERSONAGGI E NEMICI: note implementative e comandi

Gerarchia classi:
- Classe base -> Character
- Classi che ereditano Character -> Enemy, Hero
- Classi che ereditano Enemy -> JumpingEnemy, ThiefEnemy, FlyingEnemyY, FlyingEnemyX, BossEnemy

Breve descrizione classi:
- Character non istanzia niente, serve solo come superclasse.
- Hero istanzia il personaggio giocabile dall'utente -> può muoversi, saltare, sparare proiettili
- Enemy istanzia il nemico di tipo "base" -> si muove a dx e a sx
- JumpingEnemy istanzia il nemico di tipo "saltellante" -> saltella a dx e a sx
- ThiefEnemy istanzia il nemico di tipo "ladro" -> fa perdere soldi invece che punti vita al giocatore
- FlyingEnemyX/Y istanzia il nemico di tipo "volante X/Y" -> il tipo X fluttua in verticale (mantiene la x), il tipo Y fluttua in orizzontale (mantiene la y)
- BossEnemy istanzia il boss -> spara proiettili ed è il più potente tra tutti i nemici

Comandi da tastiera:
- Freccia dx/sx -> l'eroe fa un passo verso dx/sx
- Freccia dx/sx premuta -> l'eroe continua a muoversi verso dx/sx fino al rilascio
- Barra spaziatrice -> l'eroe spara un proiettile
- Freccia in su -> l'eroe salta in verticale
- Freccia in su + freccia dx/sx -> l'eroe salta verso dx/sx
- Freccia in su + barra spaziatrice -> l'eroe salta in verticale e contemporaneamente spara un proiettile

Note implementative:
- I nemici vengono istanziati e gestiti per mezzo di una lista. Ogni nodo contiene un nemico di classe Enemy; in ogni funzione è presente uno switch-case che permette di effetturare il downcasting dalla classe Enemy alla corretta sottoclasse del nemico considerato.

Alcuni punti ancora da finalizzare:
- Quanto indicato in "Note implementative"
- Gestione del BossEnemy
- Gestione del JumpingEnemy
- Gestione in generale delle funzioni Jump e Attack
- Tutto ciò che riguarda attacco/danno/punteggio/soldi
- Tutto ciò che riguarda l'interazione con le mappe dei livelli

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
