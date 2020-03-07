#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

typedef struct { //definição da struct pelo typedef, o que faz com que na hora de usar só seja necessário seu nome
	int codigo; //declaração do campo código da struct de tipo inteiro
	char titulo[50]; //declaração do campo título da struct de tipo array de caracteres
	float preco; //declaração do campo preço da struct de tipo decimal
	int idadeMinima; // declaração do campo idadeMinima da struct de tipo inteiro
} jogo;

typedef jogo elemento;

int main(){
    int TAM = 30;
    elemento jogos[30] = {{1, "GOF", 180, 18},
     {2, "Call of Duty", 280.00, 18},
      {3, "God of War", 60.00, 18},
       {4, "Rocket League", 120.00, 12},
        {5, "Toy Story - the video game", 40, 0},
         {6, "Mario", 0.00, 0},
          {7, "Fortnite", 0.00, 14},
           {8, "Battlefield", 300.00, 18},
            {9, "Halo", 90.00, 12},
             {10, "PUBG", 50.00, 18},
              {11, "Tomb Raider", 130.00, 12},
               {12, "Bloodborn", 100.00, 16},
                {13, "Red Dead", 240.00, 16},
                 {14, "GTA", 50.00, 18},
                  {15, "FIFA", 180.00, 0},
                   {16, "Minecraft", 50.00, 0},
                    {17, "The Crew", 100.00, 10},
                     {18, "Jurassic World", 110.00, 10},
                      {19, "Crash", 75.00, 0},
                       {20, "The Forest", 35.00, 12},
                        {21, "Warframe", 0.00, 14},
                         {22, "Journey", 90.00, 100},
                          {23, "NFL", 125.00, 0},
                           {24, "Assassins Creed", 265.00, 14},
                            {25, "Battlefront", 210, 12},
                             {26, "Days Gone", 90, 14},
                              {27, "Shadows of the Colossus", 100, 12},
                               {28, "Last Guardian", 120, 12},
                                {29, "Dead Cells", 30, 14},
                                 {30, "ICO", 110, 10}};
    FILE *arq1;
    arq1 = fopen ("JOGOSLT.DAT", "wb");
    if (arq1 == NULL){
        cout << "ERRO";
        exit(1);
    }
    fwrite(&TAM, sizeof(int), 1, arq1);
    fwrite(jogos, sizeof(elemento), TAM, arq1);
    fclose(arq1);
    return 0;
}
