/*
  2005-05-01
  Autor: Vinicius Gomes

  Universidade Federal de Pelotas
  Instituto de Física e Matemática
  Departamento de Informática
  Bacharelado em Ciência da Computação
  Disciplina de Fundamentos de Física 
  Professor Bardo E. J. Bodmann
 
  Tarefa n° 1: Lei de Hook
 
  Gerador de arquivo de coordenadas para gráfico padrão Excel que descreve o 
  comportamento oscilatório de um corpo de massa 'm' kg sob a Constante de Hook
  de 'k' N/m em 'y' instantes, a partir de valores obtidos na equação de Hook:

  Xi+1 = 2Xi - Xi-1 - (K/m)Xi(deltaT)²
  
  Parâmetros de entrada:
  - valor do intervalo de tempo em segundos (deltaT);
  - valor da massa do corpo em kg;
  - valor da Constante de Hook em N/m;  
  - número de coordenadas da tabela que gera o gráfico; 
  - 'help' para instruções de uso.
   
  Saída:
  - arquivo no formato padrão de gráficos para Excel;
  - o nome do arquivo é gerado pelo nome do programa, a data e a hora da geração.

  Visualização do gráfico:
  - o arquivo XLS (planília do excel) gerado na execussão estará localizado no mesmo
    diretório do executável (hook.exe), dê um duplo clique sobre ele;
  - no excel, clique no botão 'assistente de gráfico' na barra de ferramentas;
  - em 'tipos padrão' selecione 'linha' e clique 'avançar';
  - em 'intervalo de dados' selecione na planília somente a coluna 'B', marque
    'seqüências em colunas' e clique em 'avançar';  
  - nas etapas 3 e 4 clique em 'avançar' e 'concluir' respectivamente. 
  
  Observação:
  - este programa deve ser executado via linha de comando a partir do seu diretório; 
  - a linha de comando para ativar o programa deve ser composta do nome do programa 
    os parâmetros desejados. Exemplo: 
    
    hook 1 90 5 20
    hook 0.1 100 65 100
    hook help
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct coordenada {
  float tempo;
  float posicao;
} COORDENADA;

int help(int n, char *argv1); 
int valor_valido(char *entrada);
int parametros_adequados(int n,char *argv1, char *argv2, char *argv3, char *argv4); 
COORDENADA *gera_tabela(char *argv1, char *argv2, char *argv3, char *argv4);
char *formata_numero(char *str);
char *gera_nome_arquivo(void);
char *gera_arquivo(COORDENADA *tbl, char *argv4); 

int main(int argc, char *argv[]) {
  if(help(argc, argv[1])) {
    if(parametros_adequados(argc, argv[1], argv[2], argv[3], argv[4])) {
      COORDENADA *tabela = gera_tabela(argv[1], argv[2], argv[3], argv[4]);
      char *string = gera_arquivo(tabela, argv[4]);
      printf("\nArquivo %s gerado com sucesso!\n", string);
    }
    else {
      printf("\nParametros inadequados. Consulte o parametro 'help'.\n\n");   
    }
  }
  return 0;
}

int help(int n,char *argv1) {
  if(n > 1) {
    if(strcasecmp(argv1, "help") == 0) {
      printf("\n2005-05-01");
      printf("\nAutor: Vinicius Gomes\n\n");
      printf("\nUniversidade Federal de Pelotas");   
      printf("\nInstituto de Fisica e Matematica");
      printf("\nDepartamento de Informatica");
      printf("\nBacharelado em Ciencia da Computacao");
      printf("\nDisciplina de Fundamentos de Fisica");
      printf("\nProfessor Bardo E. J. Bodmann\n\n");
      printf("\nTarefa n.o 1: Lei de Hook\n\n");
      printf("\nGerador de arquivo de coordenadas para grafico padrao Excel que descreve o ");
      printf("\ncomportamento oscilatorio de um corpo de massa 'm' kg sob a constante de Hook");
      printf("\nde 'k' N/m em 'y' instantes, a partir de valores obtidos na equacao de Hook:\n\n");
      printf("\nXi+1 = 2Xi - Xi-1 - (K/m)Xi(deltaT)^2\n\n"); 
      printf("\nParametros de entrada:");
      printf("\n- valor do intervalo de tempo em segundos (deltaT);");
      printf("\n- valor da massa do corpo em kg;");
      printf("\n- valor da Constante de Hook em N/m;");  
      printf("\n- numero de coordenadas da tabela que gera o grafico;"); 
      printf("\n- 'help' para instrucoes de uso.\n");
      printf("\nSaida:\n- arquivo texto ASCII formatado no padrao de graficos para Excel");     
      printf("\n- o nome do arquivo e' gerado pelo nome do programa, a data e a hora da geracao\n");
      printf("\nVisualizacao do grafico:");
      printf("\n- o arquivo XLS (planilia do excel) gerado na execucao estara localizado no ");
      printf("\nmesmo diretorio do executavel (hook.exe), de um duplo clique sobre ele;");
      printf("\n- no excel, clique no botao 'assistente de grafico' na barra de ferramentas;");
      printf("\n- em 'tipos padrao' selecione 'linha' e clique 'avancar';");
      printf("\n- em 'intervalo de dados' selecione na planilia somente a coluna 'B', marque");
      printf("\n'sequencias em colunas' e clique em 'avancar'; ");
      printf("\n- nas etapas 3 e 4 clique em 'avancar' e 'concluir' respectivamente.\n\n\n");
      return 0;
    }
    else {
      return 1;   
    }
  }
  else {
    return 1;
  }
}

int valor_valido(char *entrada) {
  int result = 1;
  int i = 0;
  int flagponto = 0;
  while(entrada[i] != '\0') {
    if(entrada[i] == 46) {
      flagponto++;
    }
    if(flagponto > 1 || (entrada[i] != 46 && (entrada[i] < 48 || entrada[i] > 57)))
      result=0;
    i++;
  }
  return result;   
}

int parametros_adequados(int n, char *argv1, char *argv2, char *argv3, char *argv4) {
  if(n == 5) {
    int ok=1;
    int a1=valor_valido(argv1);
    int a2=valor_valido(argv2);
    int a3=valor_valido(argv3);
    int a4=valor_valido(argv4);
    if((a1 + a2 + a3 + a4) != 4)
       ok = 0;
    return ok;     
  }
  else
    return 0;
}

COORDENADA *gera_tabela(char *argv1, char *argv2, char *argv3, char *argv4) {
  float deltat = atof(argv1);
  float m = atof(argv2);
  float k = atof(argv3);
  int n_coordenadas = atoi(argv4);
  COORDENADA *tab=malloc(n_coordenadas *sizeof(COORDENADA));
  tab[0].tempo = 0;
  tab[0].posicao = 1;
  tab[1].tempo = deltat;
  tab[1].posicao = 1;
  int i;
  float aux1 = tab[0].posicao;  // serve como o Xi-1
  float aux2 = tab[1].posicao;  // serve como o Xi 
  for(i = 2; i < n_coordenadas; i++) {
    float x = 2 * aux2 - aux1 - ((k / m) * aux2) * (deltat * deltat);
    tab[i].tempo = i * deltat;
    tab[i].posicao = x;
    aux1 = aux2;
    aux2 = x;
  }
  return tab;
}

char *formata_numero(char *str) {
  char *nova = malloc(50 * sizeof(char));
  int i = 0;
  while(str[i] != '.') {
     nova[i] = str[i];
     i++;
  }
  nova[i] = ',';
  int j = i + 1;
  while(j < i + 4) {
    nova[j] = str[j];
    j++;
  }
  nova[j] = '\0';
  return nova;   
}

char *gera_nome_arquivo(void) { // modelo: hook_<dia>-<mês>-<ano>_<hora>-<min>-<seg>.xls
  char *arqv = malloc(5 * sizeof(char));
  struct tm *tempo;
  time_t tempo_;
  time(&tempo_); 
  tempo = localtime(&tempo_);
  char data[12], hora[9];
  sprintf(data, "%d-%d-%d_", tempo->tm_mday, tempo->tm_mon + 1, tempo->tm_year + 1900); 
  sprintf(hora, "%d-%d-%d", tempo->tm_hour, tempo->tm_min, tempo->tm_sec);
  strcpy(arqv, "Hook_");
  strcat(arqv, data);
  strcat(arqv, hora);
  strcat(arqv, ".xls");
  return arqv;
}

char *gera_arquivo(COORDENADA *tbl, char *argv4) {
  char *nome = gera_nome_arquivo();
  FILE *arq = fopen(nome,"w");
  int i;
  int iteracoes = atoi(argv4);
  for(i = 1; i < iteracoes; i++) {
    char str_tempo[50];
    char str_posicao[50];
    sprintf(str_tempo, "%f", tbl[i].tempo);
    sprintf(str_posicao, "%f", tbl[i].posicao);
    char *aux1=formata_numero(str_tempo);
    char *aux2=formata_numero(str_posicao);
    fprintf(arq, "%s\t%s\n", aux1, aux2);
  }
  fclose(arq);
  return nome;   
}
