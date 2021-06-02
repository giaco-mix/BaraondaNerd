# BaraondaNerd
Generatore di torneo baraonda. Random team tournament generator.

Compilato con GNU gcc Compiler, non richiede argomenti as long as viene fornito un file giocatori nominato "giocatori.txt". 
Richiede di inserire 3 parametri:
* numero giocatori per ciascuna squadra
* tempo di durata per ogni match
* quandi round generare
E.g. un torneo di Beach 4v4, con 5 giri di giocate, 20 minuti a partita (conta sempre 5 minuti per il cambio squadre in campo. 

Prossime possibili implementazioni: 
- [ ] possibilità di inserire le quote rosa nelle squadre
- [ ] controllo oltre che sul non giocare subito dopo una partita appena giocata, anche sul rigiocare entro tot partite dall'ultima giocata (tempo di attesa minimo 2 massimo 4 partite)

Contenuto: 
* giocatori.txt -> inpuit file
* squadre.c -> core functions
* match.txt -> ordine di gioco e stats

Funzioni in squadre.c:
* void print_vector (int length, int *vector) -> stampa un vettore, mi serviva per il debug
* int check_presence(int length, int to_check, int*vector, int range) -> controllo per evitare di giocare a meno di due partite di distanza dall'ultima giocata
* int main(int argc, char *argv[]) -> controllo argomenti, lettura file, caricamento dei giocatori, richieste di parametri, calcolo tempo di gioco, generazione di vettore randomico con controlli su ultima partita giocata, numeor di tentativi per riempire la posizione corrente, riempimento quilibrando fra i vari giocatori il numero di partite giocate
