# ProgettoGame
Progetto di Programmazione 2023

Checklist Mappe
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
