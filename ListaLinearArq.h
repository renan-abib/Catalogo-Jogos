//
//  ListaLinearArq.h
//  Biblioteca Lista linear ligada dinamica
//
//  Created by Angela Engelbrecht on 23/10/2018.
//  Copyright © 2018 Angela Engelbrecht. All rights reserved.
//

#ifndef ListaLinearArq_h
#define ListaLinearArq_h
// Listaarq.h
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

// o comprimento ser· armazenado nos 4 primeiros bytes
using namespace std;
struct Lista{
    FILE *arq;
};

void init   (Lista&);
void inserir(Lista&, elemento, int);
void alterar(Lista&, elemento, int);
int  vazia  (Lista);
int  compr  (Lista&);
elemento eliminar (Lista&, int);
elemento consultar(Lista , int);


void init(Lista& l)
{
    
    int comp=0;
    l.arq = fopen(nome_arquivo, "wb");
    
    if   (l.arq == NULL)
    {
        cout<< " ERRO na abertura do arquivo";
        exit(1);
    }
    fwrite(&(comp), sizeof(comp),1,l.arq);
    fclose(l.arq);
}

void inserir(Lista& l, elemento y, int i)
{
    elemento x;
    int comp;
    
    l.arq = fopen(nome_arquivo, "rb+");
    
    // teste para verificar se ocorreu algum erro com a abertura
    
    if   (l.arq == NULL)
    {
        cout<< " ERRO na abertura do arquivo";
        exit(1);
    }
    
    fseek(l.arq, 0,0);
    fread(&comp, sizeof(int),1,l.arq);
    
    if((i <= 0) || (i> comp+1))
    {
        cout<< "posicao invalida";
        exit(1);
    }
    else
    {
        if(i<= comp)
            
            for(int k=comp; k>=i;k--)
            {
                fseek (l.arq,(k-1)*sizeof(elemento)+sizeof(int),0);
                fread (&x,sizeof(elemento),1,l.arq);
                fseek (l.arq,(k)*sizeof(elemento)+sizeof(int),0);
                fwrite(&x,sizeof(elemento),1,l.arq);
            }
        
        fseek(l.arq,(i-1)*sizeof(elemento)+sizeof(int),0);
        fwrite(&y,sizeof(elemento),1,l.arq);
        
        comp++;
        fseek(l.arq,0,0);
        fwrite(&comp,sizeof(comp),1,l.arq);
    }
    fclose(l.arq);
}

elemento eliminar(Lista& l, int i)
{
    elemento x;
    int comp;
    
    l.arq = fopen(nome_arquivo, "rb+");
    
    // teste para verificar se ocorreu algum erro com a abertura
    
    if   (l.arq == NULL)
    {
        cout<< " ERRO na abertura do arquivo";
        exit(1);      // usa biblioteca stdlib.h
    }
    
    fseek(l.arq, 0,0);
    fread(&comp, sizeof(comp),1,l.arq);
    
    if((i<=0) || (i>comp))
    {
        cerr<< "posicao invalida ou underflow ";
        exit(1);
    }
    else
    {
        fseek(l.arq,(i-1)*sizeof(elemento)+sizeof(int),0);
        fread(&x,sizeof(elemento),1,l.arq);
        
        if(i<comp)
            for ( int k = i; k<=comp-1; k++)
            {
                fseek (l.arq,(k)*sizeof(elemento)+sizeof(int),0);
                fread (&x,sizeof(elemento),1,l.arq);
                fseek (l.arq,(k-1)*sizeof(elemento)+sizeof(int),0);
                fwrite(&x,sizeof(elemento),1,l.arq);
            }
        comp--;
        fseek(l.arq,0,0);
        fwrite(&comp,sizeof(comp),1,l.arq);
        fclose(l.arq);
        return x;
    }
}

elemento consultar(Lista l, int i)
{
    
    elemento x;
    int comp;
    l.arq = fopen(nome_arquivo, "rb");
    
    // teste para verificar se ocorreu algum erro com a abertura
    
    if   (l.arq == NULL)
    {
        cout<< " ERRO na abertura do arquivo";
        exit(1);      // usa biblioteca stdlib.h
    }
    
    fseek(l.arq, 0,0);
    fread(&comp, sizeof(comp),1,l.arq);
    
    if((i<=0) || (i>comp))
    {
        cerr<< "posicao invalida ou underflow ";
        exit(1);
    }
    else
    {
        fseek(l.arq,(i-1)*sizeof(elemento)+sizeof(int),0);
        fread(&x, sizeof(elemento), 1,l.arq);
        fclose(l.arq);
        return x;
    }
}

void alterar(Lista& l, elemento x, int i)
{
    
    int comp;
    l.arq = fopen(nome_arquivo, "rb+");
    
    // teste para verificar se ocorreu algum erro com a abertura
    
    if   (l.arq == NULL)
    {
        cout<< " ERRO na abertura do arquivo";
        exit(1);      // usa biblioteca stdlib.h
    }
    
    fseek(l.arq, 0,0);
    fread(&comp, sizeof(comp),1,l.arq);
    
    if((i<=0) || (i>comp))
    {
        cout<< "posicao invalida ou underflow ";
        exit(1);
    }
    else
    {
        fseek (l.arq,(i-1)*sizeof(elemento)+sizeof(int),0);
        fwrite(&x, sizeof(elemento), 1,l.arq);
        fclose(l.arq);
    }
    
}

int vazia(Lista l)
{
    if(compr(l) == 0) return 1;
    else return 0;
}

int compr (Lista& l)
{
    int comp;
    l.arq = fopen(nome_arquivo, "rb");
    
    if(l.arq == NULL)
    {
        cout<<"\nErro ao abrir o arquivo";
        exit(1);
    }
    else
    {
        fseek(l.arq, 0,0);
        fread(&comp, sizeof(comp),1,l.arq);
        return comp;
    }
}


#endif /* ListaLinearArq_h */
