# ProgettoGame
## Progetto di Programmazione 2023 - BUNNY FURY
Sconfiggi nemici e colleziona oggetti per incrementare il tuo punteggio. Scala la classifica aumentando la difficoltà e comprando oggetti dal market.

## Meccaniche di gioco
- L'eroe si muove da una piattaforma all'altra per collezionare oggetti e sconfiggere i nemici attraverso proiettili e un attacco dall'alto.
- Quando l'eroe raggiunge la fine di un livello, accede a una nuova area con nuovi nemici o a una precedentemente esplorata nello stato in cui l'aveva precedentemente lasciata.
- Quando un nemico viene sconfitto, l'eroe guadagna punti e denaro.
- Quando l'eroe viene a contatto con un nemico, perde vita fino a quando non viene sconfitto.
- In caso di morte, il giocatore può continuare la partita corrente mantenendo le statistiche dell'eroe, il denaro e la difficoltà di gioco.
- Prima di entrare nella fase di gioco, il giocatore entra in un livello market dove può acquistare oggetti benefici.

## Comandi
- Freccia destra/sinistra: l'eroe fa un passo verso destra/sinistra.
- Freccia destra/sinistra premuta: l'eroe continua a muoversi verso destra/sinistra fino al rilascio, aumentando inoltre la velocità d'esecuzione del loop di gioco (temporaneo aumento di difficoltà di gioco).
- Barra spaziatrice: l'eroe attacca sparando un proiettile.
- Freccia in su: l'eroe salta. Raggiunta la massima forza di salto (numero di righe dello schermo che è possibile saltare), cade fino a toccare terra. Durante le azioni di salto/caduta è possibile continuare a sparare proiettili e cambiare direzione.
- Freccia in giù: se l'eroe sta già saltando, entra in modalità "attacco dall'alto", che permette di colpire e causare danno ai nemici saltandoci sopra.

## Avvio del gioco
Una volta eseguita la fetch del progetto, eseguire il comando 'make' per compilare il tutto e generare l'eseguibile BunnyFury.exe tramite l'apposito makefile.
