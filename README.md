# ProgettoGame
Progetto di Programmazione 2023 - BUNNY FURY

L'eroe perde punteggio quando entra a contatto diretto con i nemici (tranne nel caso del nemico ladro, spiegato più avanti). Se vi entra a contatto da destra o sinistra, viene "spostato" rispettivamente verso destra o sinistra. Se vi entra a contatto dal basso, viene "spinto" in giù. Se vi salta sopra, viene fatto "rimbalzare" verso l'alto, a meno che non sia in modalità "attacco dall'alto" (spiegata successivamente): in tal caso è il nemico a perdere vita, e non l'eroe.

I nemici, d’altro canto, perdono vita quando vengono colpiti da un proiettile. Quando l'eroe colpisce il nemico, guadagna un quinto del punteggio massimo che il nemico può rilasciare; quando il nemico muore, l'eroe guadagna denaro e in più il punteggio massimo che il nemico può rilasciare.

All’eroe è data la possibilità sia di acquistare oggetti speciali (descritti successivamente) dall’apposito market, sia di raccogliere oggetti presenti nei vari livelli durante la partita.

Comandi
Freccia destra/sinistra: l'eroe fa un passo verso destra/sinistra.
Freccia destra/sinistra premuta: l'eroe continua a muoversi verso destra/sinistra fino al rilascio, aumentando inoltre la velocità d'esecuzione del loop di gioco (temporaneo aumento di difficoltà di gioco).
Barra spaziatrice: l'eroe attacca sparando un proiettile.
Freccia in su: l'eroe salta. Raggiunta la massima forza di salto (numero di righe dello schermo che è possibile saltare), cade fino a toccare terra. Durante le azioni di salto/caduta è possibile continuare a sparare proiettili e cambiare direzione.
Freccia in giù: se l'eroe sta già saltando, entra in modalità "attacco dall'alto", che permette di colpire e causare danno ai nemici saltandoci sopra.

g++ ProgettoGame.cpp Map.cpp MapList.cpp MapManager.cpp Character.cpp Hero.cpp Enemy.cpp SetEnemiesList.cpp FlyingEnemyX.cpp FlyingEnemyY.cpp ThiefEnemy.cpp JumpingEnemy.cpp Drop.cpp OggettoMappa.cpp OggettoMarket.cpp MarketScreen.cpp EnemiesManager.cpp FileManager.cpp -lncurses -o game.exe
