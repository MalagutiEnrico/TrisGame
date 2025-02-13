#include <stdio.h>
#include <stdlib.h>

char matrice[7][7] = {    //creazione della matrice
    {' ', '1', ' ', '3', ' ', '5', ' ',},
    {'1', ' ', '|', ' ', '|', ' ', ' '},
    {' ', '-', '+', '-', '+', '-', ' ',},
    {'3', ' ', '|', ' ', '|', ' ', ' '},
    {' ', '-', '+', '-', '+', '-', ' ',},
    {'5', ' ', '|', ' ', '|', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ',},
};

void stampa_menu(){    //funzione che stampa il menù di gioco
    system("clear");
    printf("----------Gioco del Tris---------\n");
    printf("Inserisci 1 per iniziare una partita\n");
    printf("Inserisci 0 per uscire dal gioco.\n");
    printf("Effettua la scelta: ");
}

void stampa_griglia(){    //funzione che stampa la griglia del tris
    for(int x=0; x<7; x++){
        for(int y=0; y<7; y++){
            printf("%c   ", matrice[x][y]);
        }
        printf("\n\n");
    }
}

char scegli_simbolo(char *_simbolo){    //funzione che permette all'utente di scegliere il simbolo che inizia a giocare
    do{
        printf("Inserisci il simbolo del giocatore che inzia: ");
        scanf(" %c", &*_simbolo);
        if(*_simbolo != 'x' && *_simbolo != 'o'){
            printf("Simbolo non valido. Ritenta\n");
        }
    }while(*_simbolo != 'x' && *_simbolo != 'o');
}

int controllo_inserimento(int *_x, int *_y){    //funzione che controlla le coordinate in input da parte dell'utente
    if(*_x==2 || *_y==2 || *_x==4 || *_y==4 || matrice[*_x][*_y]!=' '){
        return 1;
    }
    else{
        return 0;
    }
}

void scambia_simbolo(char *_simbolo1, char *_simbolo2){    //funzione che scambia i simboli permettendo di alternare i giocatori
    char temp;
    temp = *_simbolo1;
    *_simbolo1 = *_simbolo2;
    *_simbolo2 = temp;
}

void inserisci_simbolo(char *_simbolo, int *_x, int *_y){    //funzione che, dopo il controllo tramite la funzione apposita, inserisce il simbolo nella matrice
    do{
        printf("Inserisci la riga in cui posizionare il simbolo: ");
        scanf("%d", &*_x);
        printf("Inserisci la colonna in cui posizionare il simbolo: ");
        scanf("%d", &*_y);
        if(controllo_inserimento(&*_x, &*_y)==1){
            printf("L'input inserito non valido. Ritenta.\n");
        }
    }while(controllo_inserimento(&*_x, &*_y)!=0);
    matrice[*_x][*_y] = *_simbolo;
}

int controllo_vittoria(){    //funzione che controlla un'eventuale vittoria dei giocatori
    //controllo diagonale
    if((matrice[1][1]==matrice[3][3] && matrice[3][3]==matrice[5][5] && matrice[1][1]!=' ') || (matrice[1][5]==matrice[3][3] && matrice[3][3]==matrice[5][1] && matrice[1][5]!=' ')){
        return 1;
    }
    //controllo righe
    else if((matrice[1][1]==matrice[1][3] && matrice[1][3]==matrice[1][5] && matrice[1][1]!=' ') || (matrice[3][1]==matrice[3][3] && matrice[3][3]==matrice[3][5] && matrice[3][1]!=' ') || (matrice[5][1]==matrice[5][3] && matrice[5][3]==matrice[5][5] && matrice[5][1]!=' ')){  
        return 1;
    }
    //controllo colonne
    else if((matrice[1][1]==matrice[3][1] && matrice[3][1]==matrice[5][1] && matrice[1][1]!=' ') || (matrice[1][3]==matrice[3][3] && matrice[3][3]==matrice[5][3] && matrice[1][3]!=' ') || (matrice[1][5]==matrice[3][5] && matrice[3][5]==matrice[5][5] && matrice[1][5]!=' ')){
        return 1;
    }
    else{
        return 0;
    }
}

void pulisci_matrice(){    //funzione che pulisce la matrice, preparandola per una nuova partita
    for(int x=0; x<7; x++){
        for(int y=0; y<7; y++){
            if(matrice[x][y] == 'x' || matrice[x][y] == 'o'){
                matrice[x][y] = ' ';
            }
            printf("%c   ", matrice[x][y]);
        }
        printf("\n\n");
    }
}

int main(){
    int scelta, x=0, y=0, controllo, cnt=0;
    char simbolo, simbolo_invertito;
    do{
        stampa_menu();
        scanf("%d", &scelta);
        if(scelta==1){
            pulisci_matrice();
            scegli_simbolo(&simbolo);
            do{
                system("clear");
                stampa_griglia();
                inserisci_simbolo(&simbolo, &x, &y);
                cnt++;
                if(simbolo == 'x'){
                    simbolo_invertito='o';
                }
                else{
                    simbolo_invertito='x';
                }
                scambia_simbolo(&simbolo, &simbolo_invertito);
                controllo = controllo_vittoria();
            }while(controllo!=1 && cnt!=9);
        }
        else{
            printf("Il programma è terminato.\n");
        }
        scambia_simbolo(&simbolo, &simbolo_invertito);
        if(cnt==9 && controllo!=1){
            printf("I giocatori hanno pareggiato\n");
        }
        else{
            printf("Ha vinto il giocatore %c\n", simbolo);
        }
    }while(scelta!=0);
    return 0;
}
