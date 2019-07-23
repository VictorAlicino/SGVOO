#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aircraft{ //Estrutura das variáveis de informações sobre o Avião
    char model[20];
    char matricula[10];
    int disponivel;
    char lenght[8];
    char height[8];
    char wingspan[8];
    char cruise_speed[8];
    char range[8];
    char seats[5];
    char bathrooms[3];
    struct aircraft * prox;
}aviao;

typedef struct flight{ //Estrura das variáveis de informações sobre o Voo
    char aircraft[50];       //Nome da Aeronave
    char ap_dep[4];          //Aeroporto de Origem (Departure)
    char ap_arv[4];          //Aeroporto de Destino (Arrival)
    char dp_time[6];         //Horário de Decolagem (Departure Time)
    char arv_time[6];        //Horário de Aterrissagem (Arrival Time)
    char flight_dur[6];      //Duração do Voo
    char matricula[30];  //Modelo e Fabricante da Aeronave
    struct flight * prox;
}voo;

int mostraviaodisponivel(aviao *a){
    aviao *b = a;
    int i=0;
    printf("Aviões disponiveis\n");
    while(b!=NULL){
        if(b->disponivel == 1){
        printf("Modelo: %s \n", b->model);
        printf("Matricula: %s \n", b->matricula);
        i++;
        }
        b = b->prox; 
    }
    if(i==0){
        printf("Todas aeronaves estao em uso\n");
        return 0;
    }
    return 1;
}

int  cadastraaviaocomvoo(voo* v, aviao *a, char matricula[]){

    
    while(a!= NULL && strcmp(matricula, a->matricula)) { // localiza o elemento
        a = a->prox; 
    }
   
    if(a != NULL) {
        a->disponivel = 0;
       return 1;
    }else{
        
        return 0;
    }
    
    
    
    return 1;
}
aviao* aviao_inserir(aviao *a, char model[], char lenght[], char height[], char wingspan[], char cruise_speed[], char range[], char seats[], char bathrooms[], char matricula[]){
    
    aviao* aux = (aviao*) malloc(sizeof(aviao));
    strcpy(aux->model, model);
    strcpy(aux->matricula, matricula);
    strcpy(aux->lenght, lenght);
    strcpy(aux->height, height);
    strcpy(aux->wingspan, wingspan);
    strcpy(aux->cruise_speed, cruise_speed);
    strcpy(aux->range, range);
    strcpy(aux->seats, seats);
    strcpy(aux->bathrooms, bathrooms);
    aux->disponivel =1;
    aux->prox = a;
  
    return aux;
}
voo* voo_inserir(voo* v, char aircraft[], char ap_dep[],char ap_arv[],char dp_time[], char arv_time[], char flight_dur[], char matricula[] ) {
    voo* aux = (voo*) malloc(sizeof(voo));
    strcpy(aux->aircraft, aircraft);
    strcpy(aux->ap_dep, ap_dep);
    strcpy(aux->ap_arv, ap_arv);
    strcpy(aux->dp_time, dp_time);
    strcpy(aux->arv_time, arv_time);
    strcpy(aux->flight_dur, flight_dur);
    strcpy(aux->matricula, matricula);//usara para linkar os avioes
    aux->prox = v;
    return aux;
}

int TimeVerify(char hora_origem[]){ //verifica horario
    int a, b;
    sscanf(hora_origem, "%d:%d", &a, &b);
    if(a>23 || b>59 || a<0 || b<0){
        return 0;
    }else{
        return 1;
    }
}
voo* reg_flight(voo *v, aviao *a){ //Função para Registrar Voos
    
    char aircraft[50];
    char ap_dep[50];
    char ap_arv[50];
    char dp_time[8];
    char arv_time[8];
    char flight_dur[8];
    char matricula[30];

     printf("Prefixo: ");
     scanf("%s%*c", aircraft);
    printf("Aeroporto de Partida: ");
    scanf("%s%*c", ap_dep);
    while(strlen(ap_dep)>3){ //loop para garantir que o input do usuário está correto
        printf("Digite um Aeroporto Valido."); //Função da Bilbioteca Windows.h que gera uma caixa de diálogo
        printf("Aeroporto de Partida: ");
       scanf("%s%*c", ap_dep);
        
    }
    printf("Aeroporto de Destino: ");
    scanf("%s%*c", ap_arv);
    
    while((strlen(ap_arv)>3) || (strcmp(ap_arv, ap_dep)==0)){
        printf("Digite um Aeroporto Valido.");
        printf("Aeroporto de Destino: ");
        scanf("%s%*c", ap_arv);
        
    }
    printf("Horario da Decolagem: ");
    scanf("%s%*c", dp_time);
    while(dp_time[2]!=':' || (strlen(dp_time)>5) || (TimeVerify(dp_time)!=1)){
        printf("\a");
        printf("O horario deve ser no formato hh:mm");
        printf("Horario da Decolagem: ");
        scanf("%s%*c", dp_time);
    }
    printf("Horario da Aterrisagem: ");
    scanf("%s%*c", arv_time);
    while(arv_time[2]!=':' || (strlen(arv_time)>5) || (TimeVerify(arv_time)!=1)){
        printf("\a");
        printf("O horario deve ser no formato hh:mm");
        printf("Horario da Aterrisagem: ");
        scanf("%s%*c", arv_time);
    }
    printf("Duracao do Voo: ");
    scanf("%s%*c", flight_dur);
    while(flight_dur[2]!=':' || (strlen(flight_dur)>5) || (TimeVerify(flight_dur)!=1)){
        printf("\a");
        printf("O horario deve ser no formato hh:mm");
        printf("Duracao do Voo: ");
        scanf("%s%*c", flight_dur);
    }
    printf("Escolha o aviao: ");
    
    
    mostraviaodisponivel(a);
    printf("Insira a matricula: \n");
    scanf("%s%*c", matricula);
    printf("Matricula inserida:  %s \n", matricula);


    while(cadastraaviaocomvoo(v,a, matricula) == 0){
    cadastraaviaocomvoo(v,a, matricula);
    printf("Insira a matricula: \n");
    scanf("%s%*c", matricula);
    }

    
    
        v =   voo_inserir(v, aircraft, ap_dep, ap_arv, dp_time, arv_time, flight_dur, matricula);
    
    printf("\n");
    
    return v;
}
aviao* insereaviao(aviao *a){
    
    char model[20];
    char lenght[8];
    char height[8];
    char wingspan[8];
    char cruise_speed[8];
    char range[8];
    char seats[5];
    char bathrooms[3];
    char matricula[10];
    
    printf("\tVoce esta registrando o Aviao\n");
    printf("Modelo: ");
    scanf("%s%*c", model);
    printf("Matricula: ");
    scanf("%s%*c", matricula);
    
    printf("Comprimento: ");
    scanf("%s%*c", lenght);
    printf("Altura: ");
    scanf("%s%*c", height);
    printf("Envergadura: ");
    scanf("%s%*c", wingspan);
    printf("Velocidade de Cruzeiro: ");
    scanf("%s%*c", cruise_speed);
    printf("Alcance Maximo: ");
    scanf("%s%*c", range);
    printf("Quantidade de Assentos: ");
    scanf("%s%*c", seats);
    printf("Quantidade de Banheiros: ");
    scanf("%s%*c", bathrooms);
    
    //Inserindo dados na estrutura
    
    a = aviao_inserir(a, model, lenght, height, wingspan, cruise_speed, range, seats, bathrooms, matricula);
    printf("\n");
    return a;
}
int printvoos(voo *v, aviao * a){
    voo *vv = v;
    aviao*aa =a;
    
    while(vv!=NULL){
        printf("Numero do voo: %s \n", vv->aircraft);
        printf("Matricula: %s \n", vv->matricula);
        
        while(aa!=NULL && strcmp(vv->matricula, aa->matricula)){    
            
            aa = aa->prox;
        }
        if(aa!=NULL){
            printf( "Aviao: %s \n", aa->model);
        }
        
        vv = vv->prox;
        printf( "----------------------------\n");
    }
    
    
    return 0;
    
}

int menuvoo(voo *v, aviao *a){

    while(1){
        int opcao;
        printf("Inserir aeronave (1)  Inserir voo(2) Consultar voos(3) \n");
        scanf("%d", &opcao);
        
        if(opcao==1){
            a = insereaviao(a);
            
            
        }else if(opcao==2){
            
            v = reg_flight(v, a);
        }else if(opcao==3) {
            
           // printaaeronaves(a);
            printvoos(v,a);
        }
    }
    return 0;
    
    
    
    
    return 0;
}
int main() {

    voo *v;
    aviao *a;
    v=NULL;
    a=NULL;
    //menucpf(l);
    menuvoo(v,a);
    
    
    
    return 0;
}
