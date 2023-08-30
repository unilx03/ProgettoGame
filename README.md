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
1.	Healing Potion --> probabilità 30%
2. 	Carota magica (invincibilità per la stanza corrente) --> probabilità 8%
3.	Boost punteggio (per la stanza corrente il punteggio è raddoppiato) --> probabilità 10%
4.	Carota tagliente (aumento attacco per la stanza corrente) --> probabilità 15%
5.	Boost soldi (per la stanza corrente i soldi sono doppi) --> probabilità 10%
6.	Sconti (valido per la run successiva. Dimezza i prezzi di quanto venduto nel negozio) -->probabilità 2%
7.	Carota veloce (aumenta la velocità di sparo) --> probabilità 5%
8.	Salterello (aumenta la potenza di salto) --> probabilità 5%
9.	Scudo carota (aumenta la difesa del personaggio) --> probabilità 15%

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

PERSONAGGI E NEMICI:

Gerarchia classi:
- Classe base -> Character
- Classi che ereditano Character -> Enemy, Hero
- Classi che ereditano Enemy -> JumpingEnemy, ThiefEnemy, FlyingEnemyY, FlyingEnemyX, BossEnemy

Breve descrizione classi:
- Character non istanzia niente, serve solo come superclasse.
- Hero istanzia il personaggio giocabile dall'utente -> può muoversi, saltare, sparare proiettili. In questa classe viene inoltre gestita la meccanica dei proiettili e l'interazione tra l'eroe e gli oggetti sulla mappa.
- Enemy istanzia il nemico di tipo "base" -> si muove a dx e a sx. Se raggiunge la fine di una piattaforma elevata, cambia direzione, rimanendo così sulla piattaforma. In questa classe viene inoltre gestita l'interazione tra i nemici e l'eroe.
- JumpingEnemy istanzia il nemico di tipo "saltellante" -> saltella a dx e a sx. Se raggiunge la fine di una piattaforma elevata, cade giù.
- ThiefEnemy istanzia il nemico di tipo "ladro" -> fa perdere soldi invece che punti vita al giocatore. Se raggiunge la fine di una piattaforma elevata, cade giù.
- FlyingEnemyX/Y istanzia il nemico di tipo "volante X/Y" -> il tipo X fluttua in verticale (mantiene la x), il tipo Y fluttua in orizzontale (mantiene la y)
- BossEnemy istanzia il boss -> è il più forte tra tutti i nemici

Comandi da tastiera:
- Freccia dx/sx -> l'eroe fa un passo verso dx/sx
- Freccia dx/sx premuta -> l'eroe continua a muoversi verso dx/sx fino al rilascio
- Barra spaziatrice -> l'eroe spara un proiettile
- Freccia in su -> l'eroe salta

Meccanica di gioco:
- L'eroe perde punteggio quando entra a contatto con i nemici (tranne nel caso del nemico ladro). Se vi entra a contatto da dx o sx, viene "spostato" rispettivamente verso dx o sx. Se vi entra a contatto dal basso, viene "spinto" in giù. Se vi salta sopra, viene fatto "rimbalzare" verso l'alto.
- I nemici perdono punteggio quando vengono colpiti da un proiettile. Quando l'eroe colpisce il nemico guadagna un quinto del punteggio massimo che il nemico può rilasciare; quando il nemico muore, l'eroe guadagna soldi e il punteggio massimo che il nemico può rilasciare.
- I proiettili vengono distrutti (rimossi dalla lista) quando colpiscono una parete o un nemico.

Difficoltà di gioco:
- L'aumento della difficoltà di gioco è dato da un attributo diff_level (valore di default = 0). Tale attributo appartiene alla classe Hero.h. Inoltre, diff_level può solo aumentare, mai diminuire, e gli effetti dell'aumento del livello di difficoltà si verificheranno al raggiungimento della stanza successiva.
- Ogni score_count punti raccolti (valore di default = 100), diff_level aumenta di 1.
- Quando l'eroe acquista un oggetto dal mercato/raccoglie un oggetto dalla mappa, diff_level aumenta di 1 (nota: vale solo per gli oggetti che attuano modifiche permanenti sulle statistiche dell'eroe. Gli altri non modificano diff_level). 
- Quando diff_level aumenta di 5, viene aggiunto un nuovo nemico sulla mappa.
- Le statistiche dei nemici istanziati su una nuova mappa dipendono da diff_level: strenght += 2* diff_level, hp += 10* diff_level, defense += diff_level, money_released += 5* diff_level, score_released += 10* diff_level.

Altre note implementative:
- I nemici vengono istanziati e gestiti per mezzo di una lista. Ogni nodo contiene un nemico di classe Enemy; in ogni funzione è presente uno switch-case che permette di effetturare il downcasting dalla classe Enemy alla corretta sottoclasse del nemico considerato. Quando un nemico muore, per una frazione di secondo assume le sembianze di un fantasma, poi viene rimosso dalla lista.
- I proiettili vengono gestiti per mezzo di una lista; ciò permette di gestire più di un proiettile alla volta.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
