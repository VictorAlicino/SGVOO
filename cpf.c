#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char nomeprograma[15];
    char nomepessoa[50];
    char cpf[20];
    char categoria[10];
    int saldo;
    struct no * prox;
} pessoa;



pessoa* insere(pessoa* l, char categoria[], char nomepessoa[],char cpf[],char nomeprograma[], int saldo ) {
    pessoa* aux = (pessoa*) malloc(sizeof(pessoa));
    strcpy(aux->categoria, categoria);
    strcpy(aux->nomepessoa, nomepessoa);
    strcpy(aux->nomeprograma, nomeprograma);
    strcpy(aux->cpf, cpf);
    aux->saldo = saldo;
    
    aux->prox = l;
    printf("Elemento  inserido \n");
    return aux;
}


int verificacpf(pessoa *l,char cpf[]){
    int errocpf=0;
    pessoa *cabeca = l;
    while(l!=NULL){
        if(!strcmp(l->cpf,cpf)){
            errocpf++;
        }
        l = l->prox;
    }
    
    if(errocpf !=0){
        printf("CPF existente, insira novamente: \n");
        scanf("%[^\n]%*c",cpf);
        return  verificacpf(cabeca, cpf);
    }
    if( strlen(cpf) != 11){
        printf("CPF invalido com tamanho invalido\n");
        printf("Insira novamente:\n");
        scanf("%[^\n]%*c",cpf);
        return verificacpf(cabeca, cpf);
    }
    if(1!=1){
        printf("CPF invalido contem letras\n");
        printf("Insira novamente:\n");
        scanf("%[^\n]%*c",cpf);
        return verificacpf(cabeca, cpf);
    }
    
    return 0;
}
pessoa* cadastro( pessoa *l){
    char nomeprograma[15];
    char nomepessoa[50];
    char cpf[20];
    char categoria[10];
    int saldo;
    
    
    printf("Insira o CPF: \n");
    
    scanf("%*c%[^\n]%*c",cpf);
    verificacpf(l,cpf);
    printf("Insira seu nome: \n");
    scanf("%[^\n]%*c",nomepessoa);
    printf("Insira insira o programa: \n");
    scanf("%[^\n]%*c",nomeprograma);
    
    printf("Insira categoria: \n");
    scanf("%[^\n]%*c",categoria);
    
    printf("Insira saldo: \n");
    scanf("%d", &saldo);
    
    
    
    
    l =   insere(l, categoria,nomepessoa, cpf, nomeprograma, saldo);
    
    
    return l;
}

int consultar(pessoa *l){
    int opcao=0;
    char cpf[20];
    pessoa * ant = l; // elemento anterior
    pessoa * p = l;
    printf(" Consultar individual[1] Consultar todos os cadastros[2] \n");
    scanf("%d", &opcao);
    if(opcao==1){
        
        printf("Insira o CPF para consultar\n");
        scanf("%*c%[^\n]%*c",cpf);
        
        while(p!= NULL && strcmp(p->cpf, cpf)) { // localiza o elemento
            ant = p;
            p = p->prox;
            
        }
        if(p != NULL) {
            
            printf("CPF: %s\n", p->cpf);
            printf("Nome: %s\n", p->nomepessoa);
            printf("Programa: %s\n", p->nomeprograma);
            printf("Categoria: %s\n", p->categoria);
            printf("Saldo: %d\n\n", p->saldo);
            
        }
        
    }else if(opcao==2){
        
        while(l!=NULL){
            
            printf("CPF: %s\n", l->cpf);
            printf("Nome: %s\n", l->nomepessoa);
            printf("Programa: %s\n", l->nomeprograma);
            printf("Categoria: %s\n", l->categoria);
            printf("Saldo: %d\n\n", l->saldo);
            
            l = l->prox;
        }
    }
    
    
    return 0;
    
    
    
}
void  alterar(pessoa* l){
    
    while(l!=NULL){
        if(l->saldo < 100){
            strcpy(l->categoria , "BRONZE");
        }
        l = l->prox;
    }
}


pessoa * retira(pessoa* l, char cpf[]) {
    pessoa * ant = l; // elemento anterior
    pessoa * p = l; // usado para encontrar o elemento
    
    while(p!= NULL && strcmp(p->cpf, cpf)) { // localiza o elemento
        ant = p;
        p = p->prox;
        
    }
    if(p != NULL) {
        if(p == l)
            l = l->prox;
        else
            ant->prox = p->prox;
        free(p);
        printf("Removido com sucesso!\n");
    }
    else printf("Elemento nao encontrado\n");
    return l;
}


int editar (pessoa *l, char cpf[])
{
    int opcao1;
    pessoa * ant = l; // elemento anterior
    pessoa * p = l; // usado para encontrar o elemento
    
    
    while(p!= NULL && strcmp(p->cpf, cpf)) { // localiza o elemento
        ant = p;
        p = p->prox;
        
    }
    
    if(p != NULL) {
        
        printf ("Escolha o que deseja alterar: \n");
        printf ("Nome[1] CPF[2] Categoria[3] Programa[4] Saldo[5]");
        scanf ("%d", &opcao1);
        if (opcao1 == 1)
        {
            
            scanf("%[^\n]%*c",p->nomepessoa);
        }
        else if (opcao1 == 2)
        {
            
            scanf("%[^\n]%*c",p->cpf);
            verificacpf(l, p->cpf);
        }
        else if (opcao1 == 3)
        {
            
            scanf("%[^\n]%*c",p->categoria);
        }
        else if (opcao1 == 4)
        {
            
            scanf("%[^\n]%*c",p->nomeprograma);
        }
        else if (opcao1 == 5)
        {
            scanf ("%d", &p->saldo);
        }
        
    }else printf("Elemento nao encontrado\n");
    return 1;
}

int menucpf(pessoa *l){
    int opcao;
    l = NULL;
    char cpfpesquisa[20];
    while(1){
        printf("Inserir(1)  deletar(2)   editar(3) consultar(4) \n");
        scanf("%d", &opcao);
        
        if(opcao==1){
            l =  cadastro(l);
            
            
        }else if(opcao==2){
            printf("Insira o CPF para deletar\n");
            
            
            scanf("%*c%[^\n]%*c",cpfpesquisa);
            l =  retira(l, cpfpesquisa);
            
        }else if(opcao==3){
            printf("Insira o CPF para editar\n");
            
            
            scanf("%*c%[^\n]%*c",cpfpesquisa);
            editar(l, cpfpesquisa);
            
            
        }else if(opcao==4){
            
            consultar(l);
        }
    }
    return 0;
    
}




int main() {
    pessoa *l;

    l=NULL;
    menucpf(l);
    
    
    
    
    return 0;
}
