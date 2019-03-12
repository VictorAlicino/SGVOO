#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32 //Este segmento do código garante que o Sistema Operacional usado é o Windows
#include <windows.h>
#else
#error "Sistema nao suportado." //Seu SO não é o Windows
#endif


typedef struct flight{ //Estrura das variáveis de informações sobre o Voo
    char aircraft[50];       //Nome da Aeronave
    char ap_dep[4];          //Aeroporto de Origem (Departure)
    char ap_arv[4];          //Aeroporto de Destino (Arrival)
    char dp_time[6];         //Horário de Decolagem (Departure Time)
    char arv_time[6];        //Horário de Aterrissagem (Arrival Time)
    char flight_dur[6];      //Duração do Voo
    char aircraft_model[30]; //Modelo e Fabricante da Aeronave
}voo;

typedef struct aircraft{ //Estrutura das variáveis de informações sobre o Avião
    char model[20];
    char lenght[8];
    char height[8];
    char wingspan[8];
    char cruise_speed[8];
    char range[8];
    char seats[5];
    char bathrooms[3];
}aviao;

typedef struct person{
    char pProgram[20];
    char name[100];
    char CPF[15];
    char category[10];
    int balance;
}pessoa;

//Estruturas de Teste
/*
typedef struct flightTeste{
    char aircraft[30];
    char ap_dep[4];
    char ap_arv[4];
    char dp_time[6];
    char arv_time[6];
    char flight_dur[6];
    char aircraft_model[30];
}vooTEST; 
void flightTeste(vooTEST v[]){
    strcpy(v[0].aircraft, "GLO2112");
    strcpy(v[0].ap_dep, "GRU");
    strcpy(v[0].ap_arv, "IGU");
    strcpy(v[0].dp_time, "00:00");
    strcpy(v[0].arv_time, "10:01");
    strcpy(v[0].flight_dur, "10:01");
    strcpy(v[0].aircraft_model, "Embraer E195-E2");
}
typedef struct aircraftTeste{ //Estrutura das variáveis de informações sobre o Avião
    char model[20];
    float lenght[8];
    float height[8];
    float wingspan[8];
    float cruise_speed[8];
    float range[8];
    int seats[5];
    int bathrooms[3];
}aviaoTEST;
void aircraftTeste(aviaoTEST a[]){
    strcpy(a[0].model, "B737-800");
    strcpy(a[0].lenght, "39.52");
    strcpy(a[0].height, "12.42");
    strcpy(a[0].wingspan, "35.91");
    strcpy(a[0].cruise_speed, "860");
    strcpy(a[0].range, "6500");
    strcpy(a[0].seats, "186");
    strcpy(a[0].bathrooms, "3");
}
*/

void startup(voo f_num[], aviao a_num[]){
    for(int i=0;i<50;i++){
        strcpy(f_num[i].aircraft, "0");
        strcpy(f_num[i].ap_dep, "0");
        strcpy(f_num[i].ap_arv, "0");
        strcpy(f_num[i].dp_time,"0");
        strcpy(f_num[i].arv_time,"0");
        strcpy(f_num[i].flight_dur,"0");
        strcpy(f_num[i].aircraft_model, "0");
    }

    for(int i=0;i<50;i++){
        strcpy(a_num[i].model, "0");
        strcpy(a_num[i].lenght, "0");
        strcpy(a_num[i].height, "0");
        strcpy(a_num[i].wingspan,"0");
        strcpy(a_num[i].cruise_speed,"0");
        strcpy(a_num[i].range,"0");
        strcpy(a_num[i].seats, "0");
        strcpy(a_num[i].bathrooms, "0");
    }

    system("cls");
    printf("Limpeza de memoria pronta\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    system("cls");
    fflush(stdin);
}

void showFlights(voo f_num[]){ //Imprime na tela todos os voos na memória inclusive os vazios
    printf("\tO sistema possui os seguintes voos:\n\n");

    for(int i=0;i<50;i++){
        printf("\n\tVoo numero: %d\n", i);
        printf("\t%s\n", f_num[i].aircraft);
        printf("\t%s\n", f_num[i].ap_dep);
        printf("\t%s\n", f_num[i].ap_arv);
        printf("\t%s PST\n", f_num[i].dp_time);
        printf("\t%s PST\n", f_num[i].arv_time);
        printf("\t%s\n", f_num[i].flight_dur);
        printf("\t%s\n", f_num[i].aircraft_model);
        printf("\n\n");
    }
}

void showFlight(voo f_num[], int i){ //Imprime na tela apenas um voo selecionado pelo usuario
        printf("\nVoo numero: %d\n", i);
        printf("%s\n", f_num[i].aircraft);
        printf("%s\n", f_num[i].ap_dep);
        printf("%s\n", f_num[i].ap_arv);
        printf("%s PST\n", f_num[i].dp_time);
        printf("%s PST\n", f_num[i].arv_time);
        printf("%s\n", f_num[i].flight_dur);
        printf("%s\n", f_num[i].aircraft_model);
}

int isFlightAvailable(int i, voo f_num[]){  
    if(strcmp(f_num[i].aircraft,"0")==0 && strcmp(f_num[i].ap_dep,"0")==0 &&
        strcmp(f_num[i].ap_arv,"0")==0 && strcmp(f_num[i].dp_time,"0")==0 && 
        strcmp(f_num[i].arv_time,"0")==0 && strcmp(f_num[i].flight_dur,"0")==0 && 
        strcmp(f_num[i].aircraft_model,"0")==0){ 
        return true;
    }else{ 
        return false;
    }
}

int TimeVerify(char hora_origem[]){
    int a, b;
    sscanf(hora_origem, "%d:%d", &a, &b);        
    if(a>23 || b>59 || a<0 || b<0){
        return 0;
    }else{
        return 1;
    }
}

void reg_flight(voo f_num[]){ //Função para Registrar Voos
    int i=0;
    while(isFlightAvailable(i, f_num)==false && i<50){
        i++;
    }
    
    char aircraft[50];
    char ap_dep[50];
    char ap_arv[50];
    char dp_time[8];
    char arv_time[8];
    char flight_dur[8];
    char aircraft_model[30];
    
    printf("\tVoce esta registrando o Voo Numero %d\n\n", i);
    printf("Prefixo: ");
    scanf("%s%*c", aircraft);
        strupr(aircraft);
    printf("Aeroporto de Partida: ");
    scanf("%s%*c", ap_dep);
        strupr(ap_dep);
        while(strlen(ap_dep)>3){ //loop para garantir que o input do usuário está correto
            printf("\a"); //Som de Alerta
            MessageBox(0, "Digite um Aeroporto Valido.", "\tNome Invalido", MB_OK); //Função da Bilbioteca Windows.h que gera uma caixa de diálogo
            printf("Aeroporto de Partida: ");
            scanf("%s%*c", ap_dep);
            strupr(ap_arv);
        }
    printf("Aeroporto de Destino: ");
    scanf("%s%*c", ap_arv);
        strupr(ap_arv);
        while((strlen(ap_arv)>3) || (strcmp(ap_arv, ap_dep)==0)){
                printf("\a");
                MessageBox(0, "Digite um Aeroporto Valido.", "\tNome Invalido", MB_OK);
                printf("Aeroporto de Destino: ");
                scanf("%s%*c", ap_arv);
                strupr(ap_arv);
        }
    printf("Horario da Decolagem: ");
    scanf("%s%*c", dp_time);
        while(dp_time[2]!=':' || (strlen(dp_time)>5) || (TimeVerify(dp_time)!=1)){
                printf("\a");
                MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
                printf("Horario da Decolagem: ");
                scanf("%s%*c", dp_time);
        }
    printf("Horario da Aterrisagem: ");
    scanf("%s%*c", arv_time);
        while(arv_time[2]!=':' || (strlen(arv_time)>5) || (TimeVerify(arv_time)!=1)){
                printf("\a");
                MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
                printf("Horario da Aterrisagem: ");
                scanf("%s%*c", arv_time);
        }
    printf("Duracao do Voo: ");
    scanf("%s%*c", flight_dur);
        while(flight_dur[2]!=':' || (strlen(flight_dur)>5) || (TimeVerify(flight_dur)!=1)){
                printf("\a");
                MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
                printf("Duracao do Voo: ");
                scanf("%s%*c", flight_dur);
        }
    printf("Modelo da Aeronave: ");
    scanf("%s%*c", aircraft_model);

    //Inserindo dados na estrutura    
    strcpy(f_num[i].aircraft, aircraft);
    strcpy(f_num[i].ap_dep, ap_dep);
    strcpy(f_num[i].ap_arv, ap_arv);
    strcpy(f_num[i].dp_time, dp_time);
    strcpy(f_num[i].arv_time, arv_time);
    strcpy(f_num[i].flight_dur, flight_dur);
    strcpy(f_num[i].aircraft_model, aircraft_model);
    printf("\n");
}

int availableFlights(voo f_num[]){ //Função para Alterar Voos
    int i;
    int n = 0;
    printf("\n\tEstao disponiveis os voos:\n");
    for(i=0;i<50;i++){
        if(isFlightAvailable(i, f_num)==false){
            printf("Voo Numero: %d\n", i);
            n++;
        }
    }
    return n;
}

void change_flight(voo f_num[]){
    printf("\tVoce esta alterando um voo\n");
    int n = availableFlights(f_num);
    if(n>0){
        int i;
        printf("Qual voo deseja alterar?\nVoo numero: ");
        scanf("%d", &i);

        char aircraft[50];
        char ap_dep[50];
        char ap_arv[50];
        char dp_time[8];
        char arv_time[8];
        char flight_dur[8];
        char aircraft_model[30];

        printf("\tVoce esta alterando o Voo Numero %d\n\n", i);
        printf("Prefixo: ");
        scanf("%s", &aircraft);
            strupr(aircraft);
        printf("Aeroporto de Partida: ");
        scanf("%s", &ap_dep);
            strupr(ap_dep);
            while(strlen(ap_dep)>3){ //loop para garantir que o input do usuário está correto
                printf("\a"); //Som de Alerta
                MessageBox(0, "Digite um Aeroporto Valido.", "\tNome Invalido", MB_OK); //Função da Bilbioteca Windows.h que gera uma caixa de diálogo
                printf("Aeroporto de Partida: ");
                scanf("%s", &ap_dep);
                strupr(ap_arv);
            }
        printf("Aeroporto de Destino: ");
        scanf("%s", &ap_arv);
            strupr(ap_arv);
            while((strlen(ap_arv)>3) || (strcmp(ap_arv, ap_dep)==0)){
                    printf("\a");
                    MessageBox(0, "Digite um Aeroporto Valido.", "\tNome Invalido", MB_OK);
                    printf("Aeroporto de Destino: ");
                    scanf("%s", &ap_arv);
                    strupr(ap_arv);
            }
        printf("Horario da Decolagem: ");
        scanf("%s", &dp_time);
            while(dp_time[2]!=':' || (strlen(dp_time)>5) || (TimeVerify(dp_time)!=1)){
                    printf("\a");
                    MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
                    printf("Horario da Decolagem: ");
                    scanf("%s", &dp_time);
            }
        printf("Horario da Aterrisagem: ");
        scanf("%s", &arv_time);
            while(arv_time[2]!=':' || (strlen(arv_time)>5) || (TimeVerify(arv_time)!=1)){
                    printf("\a");
                    MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
                    printf("Horario da Aterrisagem: ");
                    scanf("%s", &arv_time);
            }
        printf("Duracao do Voo: ");
        scanf("%s", &flight_dur);
            while(flight_dur[2]!=':' || (strlen(flight_dur)>5) || (TimeVerify(flight_dur)!=1)){
                    printf("\a");
                    MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
                    printf("Duracao do Voo: ");
                    scanf("%s", &flight_dur);
            }
        printf("Modelo da Aeronave: ");
        scanf("%s", &aircraft_model);

        //Inserindo dados na estrutura
        strcpy(f_num[i].aircraft, aircraft);
        strcpy(f_num[i].ap_dep, ap_dep);
        strcpy(f_num[i].ap_arv, ap_arv);
        strcpy(f_num[i].dp_time, dp_time);
        strcpy(f_num[i].arv_time, arv_time);
        strcpy(f_num[i].flight_dur, flight_dur);
        strcpy(f_num[i].aircraft_model, aircraft_model);
    }else{
        //system("cls");
        system("color 0C");
        printf("\t\tNao ha voos\n");
        printf("\a");
        MessageBox(0, "Sem voos disponiveis para alteracao", "\tErro", MB_OK);
        system("color 07");
    }
}

void excludeFlight(voo f_num[]){
    int i;
    
    printf("\tOs voos disponiveis sao: ");
    for(int i=0;i<50;i++){
        if(isFlightAvailable(i, f_num)==false){ 
            printf("\nVoo numero: %d\n", i);
            printf("Prefixo: %s\n", f_num[i].aircraft);
            printf("Aeroporto de Partida: %s\n", f_num[i].ap_dep);
            printf("Aeroporto de Chegada: %s\n", f_num[i].ap_arv);
            printf("Hora de Partida: %s PST\n", f_num[i].dp_time);
            printf("Hora de Decolagem: %s PST\n", f_num[i].arv_time);
            printf("Duracao do Voo: %s\n", f_num[i].flight_dur);
            printf("Modelo da Aeronave: %s\n", f_num[i].aircraft_model);
            printf("\n");
        }
    }

    printf("Qual voo deseja excluir?\nVoo Numero: ");
    scanf("%d", &i);
        strcpy(f_num[i].aircraft, "0");
        strcpy(f_num[i].ap_dep, "0");
        strcpy(f_num[i].ap_arv, "0");
        strcpy(f_num[i].dp_time,"0");
        strcpy(f_num[i].arv_time,"0");
        strcpy(f_num[i].flight_dur,"0");
        strcpy(f_num[i].aircraft_model, "0");
    
    printf("\tOperacao concluida\n");
    printf("\tVoo Numero %d esta agora disponivel", i);
}

int isAircraftAvailable(int i, aviao a_num[]){  
    if(strcmp(a_num[i].model,"0")==0 && strcmp(a_num[i].lenght,"0")==0 &&
        strcmp(a_num[i].height,"0")==0 && strcmp(a_num[i].wingspan,"0")==0 && 
        strcmp(a_num[i].cruise_speed,"0")==0 && strcmp(a_num[i].range,"0")==0 && 
        strcmp(a_num[i].seats,"0")==0 && strcmp(a_num[i].bathrooms,"0")==0){ 
        return true;
    }else{ 
        return false;
    }
}

void addAircraft(aviao a_num[]){
    int i=0;
    while(isAircraftAvailable(i, a_num)==false && i<50){
        i++;
    }

    char model[20];
    char lenght[8];
    char height[8];
    char wingspan[8];
    char cruise_speed[8];
    char range[8];
    char seats[5];
    char bathrooms[3];

    printf("\tVoce esta registrando o Aviao Numero %d da Frota\n\n", i);
    printf("Modelo: ");
    scanf("%s%*c", model);
        strupr(model);
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
    strcpy(a_num[i].model, model);
    strcpy(a_num[i].lenght, lenght);
    strcpy(a_num[i].height, height);
    strcpy(a_num[i].wingspan, wingspan);
    strcpy(a_num[i].cruise_speed, cruise_speed);
    strcpy(a_num[i].range, range);
    strcpy(a_num[i].seats, seats);
    strcpy(a_num[i].bathrooms, bathrooms);
    printf("\n");
}


void FightStatus(voo f_num[]){
    int i;
    showFlights(f_num);
    printf("Digite o numero do voo que deseja consultar: ");
    scanf("%d", &i);

    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    char dia7[4]; char mes[4]; int dia30; int hora; int minutos; int segundos; int ano;
    sscanf(time_str, "%s %s %d %d:%d:%d %d", &dia7, &mes, &dia30, &hora, &minutos, &segundos, &ano);
    int hrVoo; int minVoo;
    sscanf(f_num[i].dp_time, "%d:%d", &hrVoo, &minVoo);

    if((hrVoo-hora)>=1){
        printf("Check-in Aberto\n");
    }else if((hrVoo-hora)==0 && (minVoo-minutos)<=59){
        printf("Check-in Fechado\n");
    }else if((hrVoo-hora)==0 && (minVoo-minutos)<=30){
        printf("Embarque Proximo\n");
    }else if((hrVoo-hora)==0 && (minVoo-minutos)<=20){
        printf("Embarque Imediato\n");
    }else if((hrVoo-hora)==0 && (minVoo-minutos)<=10){
        printf("Ultima Chamada\n");
    }else if((hrVoo-hora)==0 && (minVoo-minutos)<=0 && (minVoo-minutos)>=-10){
        printf("Partindo\n");
    }else if((hrVoo-hora)==0 && (minVoo-minutos)>=-10){
        printf("Voo Encerrado");
    }  
}

int main(){
    voo f_num[50]; //Gerando voos na memória
    aviao a_num[50]; //Gerando aviões na memória
    //Variáveis de Teste
    /*
    vooTEST v[1];
    aviaoTEST a[1];
    */

    startup(f_num, a_num);   
}