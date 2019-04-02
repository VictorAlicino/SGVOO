#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32 //Este segmento do código garante que o Sistema Operacional usado é o Windows
#include <windows.h>
#endif

typedef struct flight{ //Estrura das variáveis de informações sobre o Voo
    char prefix[50];         //Nome da Aeronave
    char ap_dep[4];          //Aeroporto de Origem (Departure)
    char ap_arv[4];          //Aeroporto de Destino (Arrival)
    char dp_time[6];         //Horário de Decolagem (Departure Time)
    char arv_time[6];        //Horário de Aterrissagem (Arrival Time)
    char flight_dur[6];      //Duração do Voo
    char aircraft_model[30]; //Modelo e Fabricante da Aeronave
}voo;

typedef struct aircraft{ //Estrutura das variáveis de informações sobre o Avião
    char model[20];          //Modelo da Aeronave
    char lenght[8];          //Comprimento
    char height[8];          //Altura
    char wingspan[8];        //Envergadura
    char cruise_speed[8];    //Velocidade de Cruzeiro
    char range[8];           //Alcance Máximo
    char seats[5];           //Quantidade de Assentos
    char bathrooms[3];       //Quantidade de banheiros
}aviao;

typedef struct person{ //Estrutura das variáveis de informações sobre o usuário do Programa de Milhas
    char pProgram[20]; //Programa de Milhagem
    char name[100];    //Nome da Pessoa
    char CPF[15];      //Certificado de Pessoa Física
    char category[10]; //Categoria no Programa (Gold, Silver, Bronze)
    int balance;       //Saldo de Milhas
}pessoa;

typedef struct inputFlight{ //Estrutura temporária para os input de usuário
    char prefix[50];         //Nome da Aeronave
    char ap_dep[4];          //Aeroporto de Origem (Departure)
    char ap_arv[4];          //Aeroporto de Destino (Arrival)
    char dp_time[6];         //Horário de Decolagem (Departure Time)
    char arv_time[6];        //Horário de Aterrissagem (Arrival Time)
    char flight_dur[6];      //Duração do Voo
    char aircraft_model[30]; //Modelo e Fabricante da Aeronave
}inputF;

typedef struct inputAircraft{ //Estrutura temporária para os input de usuário
    char model[20];           //Modelo da Aeronave
    char lenght[8];           //Comprimento
    char height[8];           //Altura
    char wingspan[8];         //Envergadura
    char cruise_speed[8];     //Velocidade de Cruzeiro
    char range[8];            //Alcance Máximo
    char seats[5];            //Quantidade de Assentos
    char bathrooms[3];        //Quantidade de banheiros
}inputA;

typedef struct inputPerson{ //Estrutura temporária para os input de usuário
    char pProgram[20];      //Programa de Milhagem
    char name[100];         //Nome da Pessoa
    char CPF[15];           //Certificado de Pessoa Física
    char category[10];      //Categoria no Programa (Gold, Silver, Bronze)
    int balance;            //Saldo de Milhas
}inputP;

void startup(voo f_num[], aviao a_num[]){ //Função para definir todos os valores de todas as posições do vetor como 0
    for(int i=0;i<50;i++){
        strcpy(f_num[i].prefix, "0");
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
        printf("\t%s\n", f_num[i].prefix);
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
    printf("%s\n", f_num[i].prefix);
    printf("%s\n", f_num[i].ap_dep);
    printf("%s\n", f_num[i].ap_arv);
    printf("%s PST\n", f_num[i].dp_time);
    printf("%s PST\n", f_num[i].arv_time);
    printf("%s\n", f_num[i].flight_dur);
    printf("%s\n", f_num[i].aircraft_model);
}

int isFlightAvailable(int i, voo f_num[]){ //Verifica se determinado índice do vetor está disponível para inserir novos valores
    //Se em determinado índice todos os valores forem iguais a 0, significa que este índice está disponível
    if(strcmp(f_num[i].prefix,"0")==0 && strcmp(f_num[i].ap_dep,"0")==0 &&
        strcmp(f_num[i].ap_arv,"0")==0 && strcmp(f_num[i].dp_time,"0")==0 && 
        strcmp(f_num[i].arv_time,"0")==0 && strcmp(f_num[i].flight_dur,"0")==0 && 
        strcmp(f_num[i].aircraft_model,"0")==0){ 
        return true;
    }else{ 
        return false;
    }
}

int TimeVerify(char hora_origem[]){ //Verifica se o horário digitado pelo usuário está correto
    //O horário deve ser igual ao formato HH:MM e não pode ultrapassar 23:59 ou ser negativo
    int a, b;
    sscanf(hora_origem, "%d:%d", &a, &b);        
    if(a>23 || b>59 || a<0 || b<0){
        return 0;
    }else{
        return 1;
    }
}

void reg_flight(voo f_num[], inputF f){ //Função para Registrar Voos
    int i=0;

    //Verifica qual índice está disponível
    while(isFlightAvailable(i, f_num)==false && i<50){
        i++;
    }
     
    //Alocando espaço para os dados temporários
    char *prefix; //Prefixo do Voo
    char *ap_dep; //(Airport_Departure) Aeroporto de Partida
    char *ap_arv; //(Airport_Arrival) Aeroporto de Destino
    char *dp_time; //(Departure_Time) Horário de Decolagem
    char *arv_time; //(Arrival_Time) Horário de Chegada
    char *flight_dur; //(Flight_Duration) Duração do Voo
    char *aircraft_model; //Modelo do Avião

    prefix = (char *)malloc(50 * sizeof(char));
    ap_dep = (char *)malloc(50 * sizeof(char));
    ap_arv = (char *)malloc(50 * sizeof(char));
    dp_time = (char *)malloc(8 * sizeof(char));
    arv_time = (char *)malloc(8 * sizeof(char));
    flight_dur = (char *)malloc(8 * sizeof(char));
    aircraft_model = (char *)malloc(30 * sizeof(char));

    //Copiando dados da Estrutura Temporária para Inputs
    strcpy(prefix, f.prefix);
    strcpy(ap_dep, f.ap_dep);
    strcpy(ap_arv, f.ap_arv);
    strcpy(dp_time, f.dp_time);
    strcpy(arv_time, f.arv_time);
    strcpy(flight_dur, f.flight_dur);
    strcpy(aircraft_model, f.aircraft_model);
    
    //Verificando erros
    strupr(prefix);
    strupr(ap_dep);
    strupr(ap_arv);
    strupr(aircraft_model);
    while(strlen(ap_dep)>3){
        printf("\a"); //Som de Alerta
        #ifdef _WIN32
            MessageBox(0, "Digite um Aeroporto Valido.", "\tAeroporto Invalido", MB_OK); //Função da Bilbioteca Windows.h que gera uma caixa de diálogo
        #else
            printf("\nDigite um aeroporto valido\n");
        #endif
        printf("Aeroporto de Partida: ");
        scanf("%[^\n]s", ap_dep);
        fflush(stdin);
        strupr(ap_dep);
    }
    while((strlen(ap_arv)>3) || (strcmp(ap_arv, ap_dep)==0)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "Digite um Aeroporto Valido.", "\tNome Invalido", MB_OK);
        #else
            printf("\nDigite um aeroporto valido\n");
        #endif
        printf("Aeroporto de Destino: ");
        scanf("%[^\n]s", ap_arv);
        strupr(ap_arv);
    }
    while(dp_time[2]!=':' || (strlen(dp_time)>5) || (TimeVerify(dp_time)!=1)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
        #else
            printf("\nDigite uma hora valida\n");
        #endif
        printf("Horario da Decolagem: ");
        scanf("%[^\n]s", dp_time);
    }
    while(arv_time[2]!=':' || (strlen(arv_time)>5) || (TimeVerify(arv_time)!=1)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
        #else
            printf("Digite uma hora valida\n");
        #endif
        printf("Horario da Aterrisagem: ");
        scanf("%[^\n]s", arv_time);
    }
    while(flight_dur[2]!=':' || (strlen(flight_dur)>5) || (TimeVerify(flight_dur)!=1)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
        #else
            printf("Digite uma hora valida\n");
        #endif
        printf("Duracao do Voo: ");
        scanf("%[^\n]s", flight_dur);
    }

    //Inserindo dados na estrutura
    strcpy(f_num[i].prefix, prefix);
    strcpy(f_num[i].ap_dep, ap_dep);
    strcpy(f_num[i].ap_arv, ap_arv);
    strcpy(f_num[i].dp_time, dp_time);
    strcpy(f_num[i].arv_time, arv_time);
    strcpy(f_num[i].flight_dur, flight_dur);
    strcpy(f_num[i].aircraft_model, aircraft_model);

    //liberando memória alocada
    free(prefix);
    free(ap_dep);
    free(ap_arv);
    free(dp_time);
    free(arv_time);
    free(flight_dur);
    free(aircraft_model);
}

int availableFlights(voo f_num[]){ //Verifica quais índices já foram preenchidos e podem ser alterados
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

void change_flight(voo f_num[], inputF f, int i){ //Função para Alterar Voos
    printf("\tVoce esta alterando um voo\n");
    int n = availableFlights(f_num);
    if(n>0){
        int i;
        printf("Qual voo deseja alterar?\nVoo numero: ");
        scanf("%d", &i);

    //Alocando espaço para os dados temporários
    char *prefix; //Prefixo do Voo
    char *ap_dep; //(Airport_Departure) Aeroporto de Partida
    char *ap_arv; //(Airport_Arrival) Aeroporto de Destino
    char *dp_time; //(Departure_Time) Horário de Decolagem
    char *arv_time; //(Arrival_Time) Horário de Chegada
    char *flight_dur; //(Flight_Duration) Duração do Voo
    char *aircraft_model; //Modelo do Avião

    prefix = (char *)malloc(50 * sizeof(char));
    ap_dep = (char *)malloc(50 * sizeof(char));
    ap_arv = (char *)malloc(50 * sizeof(char));
    dp_time = (char *)malloc(8 * sizeof(char));
    arv_time = (char *)malloc(8 * sizeof(char));
    flight_dur = (char *)malloc(8 * sizeof(char));
    aircraft_model = (char *)malloc(30 * sizeof(char));

    //Copiando dados da Estrutura Temporária para Inputs
    strcpy(prefix, f.prefix);
    strcpy(ap_dep, f.ap_dep);
    strcpy(ap_arv, f.ap_arv);
    strcpy(dp_time, f.dp_time);
    strcpy(arv_time, f.arv_time);
    strcpy(flight_dur, f.flight_dur);
    strcpy(aircraft_model, f.aircraft_model);
    
    //Verificando erros
    strupr(prefix);
    strupr(ap_dep);
    strupr(ap_arv);
    strupr(aircraft_model);
    while(strlen(ap_dep)>3){
        printf("\a"); //Som de Alerta
        #ifdef _WIN32
            MessageBox(0, "Digite um Aeroporto Valido.", "\tAeroporto Invalido", MB_OK); //Função da Bilbioteca Windows.h que gera uma caixa de diálogo
        #else
            printf("\nDigite um aeroporto valido\n");
        #endif
        printf("Aeroporto de Partida: ");
        scanf("%[^\n]s", ap_dep);
        fflush(stdin);
        strupr(ap_dep);
    }
    while((strlen(ap_arv)>3) || (strcmp(ap_arv, ap_dep)==0)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "Digite um Aeroporto Valido.", "\tNome Invalido", MB_OK);
        #else
            printf("\nDigite um aeroporto valido\n");
        #endif
        printf("Aeroporto de Destino: ");
        scanf("%[^\n]s", ap_arv);
        strupr(ap_arv);
    }
    while(dp_time[2]!=':' || (strlen(dp_time)>5) || (TimeVerify(dp_time)!=1)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
        #else
            printf("\nDigite uma hora valida\n");
        #endif
        printf("Horario da Decolagem: ");
        scanf("%[^\n]s", dp_time);
    }
    while(arv_time[2]!=':' || (strlen(arv_time)>5) || (TimeVerify(arv_time)!=1)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
        #else
            printf("Digite uma hora valida\n");
        #endif
        printf("Horario da Aterrisagem: ");
        scanf("%[^\n]s", arv_time);
    }
    while(flight_dur[2]!=':' || (strlen(flight_dur)>5) || (TimeVerify(flight_dur)!=1)){
        printf("\a");
        #ifdef _WIN32
            MessageBox(0, "O horario deve ser no formato hh:mm", "\tHora Invalida", MB_OK);
        #else
            printf("Digite uma hora valida\n");
        #endif
        printf("Duracao do Voo: ");
        scanf("%[^\n]s", flight_dur);
    }

    //Inserindo dados na estrutura
    strcpy(f_num[i].prefix, prefix);
    strcpy(f_num[i].ap_dep, ap_dep);
    strcpy(f_num[i].ap_arv, ap_arv);
    strcpy(f_num[i].dp_time, dp_time);
    strcpy(f_num[i].arv_time, arv_time);
    strcpy(f_num[i].flight_dur, flight_dur);
    strcpy(f_num[i].aircraft_model, aircraft_model);

    //liberando memória alocada
    free(prefix);
    free(ap_dep);
    free(ap_arv);
    free(dp_time);
    free(arv_time);
    free(flight_dur);
    free(aircraft_model);
    }else{
        #ifdef _WIN32
            MessageBox(0, "Sem voos disponiveis para alteracao", "\tErro", MB_OK);
            printf("\a");
        #else
            printf("\t\tNao ha voos\n");
            printf("\a");
        #endif
    }
}

void excludeFlight(voo f_num[]){ //Função para Excluir Voo
    int i;
    
    printf("\tOs voos disponiveis sao: ");
    for(int i=0;i<50;i++){
        if(isFlightAvailable(i, f_num)==false){ 
            printf("\nVoo numero: %d\n", i);
            printf("Prefixo: %s\n", f_num[i].prefix);
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
        strcpy(f_num[i].prefix, "0");
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

void addAircraft(aviao a_num[], inputA a){
    int i=0;
    while(isAircraftAvailable(i, a_num)==false && i<50){
        i++;
    }

    //Alocando espaço para os dados temporários
    char *model;
    char *lenght;
    char *height;
    char *wingspan;
    char *cruise_speed;
    char *range;
    char *seats;
    char *bathrooms;

    model = (char *)malloc(20 * sizeof(char));
    lenght = (char *)malloc(8 * sizeof(char));
    height = (char *)malloc(8 * sizeof(char));
    wingspan = (char *)malloc(8 * sizeof(char));
    cruise_speed = (char *)malloc(8 * sizeof(char));
    range = (char *)malloc(8 * sizeof(char));
    seats = (char *)malloc(5 * sizeof(char));
    bathrooms = (char *)malloc(3 * sizeof(char));

    //Copiando dados da Estrutura Temporária para Inputs
    strcpy(model, a.model);
    strcpy(lenght, a.lenght);
    strcpy(height, a.height);
    strcpy(wingspan, a.wingspan);
    strcpy(cruise_speed, a.cruise_speed);
    strcpy(range, a.range);
    strcpy(seats, a.seats);
    strcpy(bathrooms, a.bathrooms);

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

    //Liberando memória alocada
    free(model);
    free(lenght);
    free(height);
    free(wingspan);
    free(cruise_speed);
    free(range);
    free(seats);
    free(bathrooms);
}

void changeAircraft(aviao a_num[], inputA a, int i){
    //Alocando espaço para os dados temporários
    char *model;
    char *lenght;
    char *height;
    char *wingspan;
    char *cruise_speed;
    char *range;
    char *seats;
    char *bathrooms;

    model = (char *)malloc(20 * sizeof(char));
    lenght = (char *)malloc(8 * sizeof(char));
    height = (char *)malloc(8 * sizeof(char));
    wingspan = (char *)malloc(8 * sizeof(char));
    cruise_speed = (char *)malloc(8 * sizeof(char));
    range = (char *)malloc(8 * sizeof(char));
    seats = (char *)malloc(5 * sizeof(char));
    bathrooms = (char *)malloc(3 * sizeof(char));

    //Copiando dados da Estrutura Temporária para Inputs
    strcpy(model, a.model);
    strcpy(lenght, a.lenght);
    strcpy(height, a.height);
    strcpy(wingspan, a.wingspan);
    strcpy(cruise_speed, a.cruise_speed);
    strcpy(range, a.range);
    strcpy(seats, a.seats);
    strcpy(bathrooms, a.bathrooms);

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

    //Liberando memória alocada
    free(model);
    free(lenght);
    free(height);
    free(wingspan);
    free(cruise_speed);
    free(range);
    free(seats);
    free(bathrooms);
}

void showAircrafts(aviao a_num[]){
    printf("\tO sistema possui as seguintes aeronaves:\n\n");

    for(int i=0;i<50;i++){
        printf("\n\tAviao numero: %d\n", i);
        printf("\t%s\n", a_num[i].model);
        printf("\t%s\n", a_num[i].lenght);
        printf("\t%s\n", a_num[i].height);
        printf("\t%s\n", a_num[i].wingspan);
        printf("\t%s\n", a_num[i].cruise_speed);
        printf("\t%s\n", a_num[i].range);
        printf("\t%s\n", a_num[i].seats);
        printf("\t%s\n", a_num[i].bathrooms);
        printf("\n\n");
    }
}

void showAircraft(aviao a_num[], int i){
    printf("\n\tAviao numero: %d\n", i);
    printf("\t%s\n", a_num[i].model);
    printf("\t%s\n", a_num[i].lenght);
    printf("\t%s\n", a_num[i].height);
    printf("\t%s PST\n", a_num[i].wingspan);
    printf("\t%s PST\n", a_num[i].cruise_speed);
    printf("\t%s\n", a_num[i].range);
    printf("\t%s\n", a_num[i].seats);
    printf("\t%s\n", a_num[i].bathrooms);
    printf("\n\n");
}

void excludeAircraft(aviao a_num[], int i){
    strcpy(a_num[i].model, "0");
    strcpy(a_num[i].lenght, "0");
    strcpy(a_num[i].height, "0");
    strcpy(a_num[i].wingspan, "0");
    strcpy(a_num[i].cruise_speed, "0");
    strcpy(a_num[i].range, "0");
    strcpy(a_num[i].seats, "0");
    strcpy(a_num[i].bathrooms, "0");

    printf("\tOperacao concluida\n");
    printf("\tVoo Numero %d esta agora disponivel", i);
}

void FlightStatus(voo f_num[], int i){
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

void reg_cpf(pessoa p_num[], inputP p){
    //int i=0;

    ////Verifica qual índice está disponível
    //while(isFlightAvailable(i, f_num)==false && i<50){
    //    i++;
    //}
     
    //Alocando espaço para os dados temporários
    char *pProgram; //Nome do Programa
    char *name; //Nome completo da pessoa
    char *CPF; //Certificado de Pessoa Física
    char *category; //Categoria no Programa (Gold, Silver, Bronze)
    int *balance; //Saldo de Milhas

    pProgram = (char *)malloc(20 * sizeof(char));
    name = (char *)malloc(100 * sizeof(char));
    CPF = (char *)malloc(15 * sizeof(char));
    category = (char *)malloc(10 * sizeof(char));
    balance = (int *)malloc(sizeof(int));

    //Copiando dados da Estrutura Temporária para Inputs
    //strcpy(pProgram, p.prefix);
    //strcpy(name, p.ap_dep);
    //strcpy(CPF, p.ap_arv);
    //strcpy(category, p.dp_time);
    //strcpy(balance, p.arv_time);

    //Liberação de memória
    free(pProgram);
    free(name);
    free(CPF);
    free(category);
    free(balance);
}

int main(){
    voo f_num[50];
    aviao a_num[50];
    inputF f;
    inputA a;
    inputP p;

    startup(f_num, a_num);

    return 0;
}