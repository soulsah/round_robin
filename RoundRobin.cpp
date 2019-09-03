#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct leTimes{
	char nome_time[25];
}nomes;

typedef struct parteUm{
	char nome_time;
}rodadas;

typedef struct resultados{
	char nome_time[25];
	int jogos, pontos, vitorias,
		empates, derrotas, gp, gc,
		saldo;
}result;

leTimes *arqTimes(int *q);
parteUm *montaRodadas(nomes *times, int qtde, result *dados);

int main(){
	int times,cont;
	
	nomes *v_times;	
	v_times = arqTimes(&times);
	
	result *dados;
	dados = (result *)malloc(sizeof(result) * times);
	
	for(cont=0;cont<times;cont++){
		strcpy(dados[cont].nome_time,v_times[cont].nome_time);
	}
	
	rodadas *v_rodadas;
	v_rodadas = montaRodadas(v_times,times,dados);
}

leTimes *arqTimes(int *q){
	int cont,i,j,x, n_linha=0;
	char nomeLido[25];
	nomes *vetor;
	*q = 0;
	vetor = NULL;
	FILE *arquivo;
	arquivo = fopen("TIMES.txt","r");
	
	while(fscanf(arquivo,"%25s\n",&nomeLido) != EOF){
		cont++;
		vetor = (nomes *)realloc(vetor,sizeof(nomes) * cont);
		strcpy(vetor[cont-1].nome_time,nomeLido);
		(*q)++;
	}
	return(vetor);
}

parteUm *montaRodadas(nomes *times, int qtde, result *dados){
	srand(time(NULL));
	int partidas_rodadas, rodadas_turno, total_rodadas, total_jogos;
	int i,j,cont,aux_int;
	int gp, gc;
	char aux[25],ultimo[25];
	FILE *arqSaida;
	
	for(cont=0;cont<qtde;cont++){
		dados[cont].derrotas = 0;
		dados[cont].empates = 0;
		dados[cont].gc = 0;
		dados[cont].gp = 0;
		dados[cont].jogos = 0;
		dados[cont].pontos = 0;
		dados[cont].saldo = 0;
		dados[cont].vitorias = 0;
	}
	
	total_jogos = pow(qtde,2) - qtde;
	if(qtde % 2 == 0){
		partidas_rodadas = qtde / 2;
		rodadas_turno = qtde - 1;
		total_rodadas = 2 * (qtde - 1);
	} else {
		total_rodadas = 2 * qtde;
		partidas_rodadas = (qtde - 1) / 2;
		rodadas_turno = qtde;
	}
	
	arqSaida = fopen("RESULTADO.txt","w");
	fprintf(arqSaida,"Turno de Ida\n\n");
	printf("Turno de Ida\n\n");
	for(cont=0;cont<rodadas_turno;cont++){
		fprintf(arqSaida,"Rodada %d\n",cont+1);
		printf("Rodada %d\n",cont+1);
		for(i=0;i<partidas_rodadas;i++){
			gp = rand() % 5;
			gc = rand() % 5;
			fprintf(arqSaida,"%s    	[%d] x [%d]	    %s\n",times[i].nome_time,gp,gc, times[qtde-(i+1)].nome_time);
			printf("%s    	[%d] x [%d]	    %s\n",times[i].nome_time,gp,gc, times[qtde-(i+1)].nome_time);
			
			dados[i].gp += gp;
			dados[i].gc += gc;
			dados[i].jogos += 1;
			dados[i].saldo += gp - gc;
			
			dados[qtde-(i+1)].gp += gc;
			dados[qtde-(i+1)].gc += gp;
			dados[qtde-(i+1)].jogos += 1;
			dados[qtde-(i+1)].saldo += gc - gp;
			
			if(gp > gc){
				dados[i].vitorias += 1;
				dados[qtde-(i+1)].derrotas += 1;
				dados[i].pontos += 3;
			} else if(gc > gp){
				dados[qtde-(i+1)].vitorias += 1;
				dados[i].derrotas += 1;
				dados[qtde-(i+1)].pontos += 3;
			} else {
				dados[i].empates += 1;
				dados[qtde-(i+1)].empates += 1;
				dados[i].pontos += 1;
				dados[qtde-(i+1)].pontos += 1;
			}
		}
		strcpy(ultimo,times[qtde-1].nome_time);
		for(j=qtde;j>1;j--){
			strcpy(aux,times[j-1].nome_time);
			strcpy(times[j-1].nome_time,times[j].nome_time);
			strcpy(times[j].nome_time,aux);
		}
		strcpy(times[1].nome_time,ultimo);
		fprintf(arqSaida,"\n");
		printf("\n");
	}
	fprintf(arqSaida,"Turno de Volta\n\n");
	printf("Turno de Volta\n\n");
	for(cont=0;cont<rodadas_turno;cont++){
		printf("Rodada %d\n",cont+1+rodadas_turno);
		for(i=0;i<partidas_rodadas;i++){
			gp = rand() % 5;
			gc = rand() % 5;
			fprintf(arqSaida,"%s    	[%d] x [%d]	  %s\n",times[qtde-(i+1)].nome_time,gp,gc,times[i].nome_time);
			printf("%s    	[%d] x [%d]	  %s\n",times[qtde-(i+1)].nome_time,gp,gc,times[i].nome_time);
			
			dados[i].gc += gp;
			dados[i].gp += gc;
			dados[i].jogos += 1;
			dados[i].saldo += gc - gp;
			
			dados[qtde-(i+1)].gp += gc;
			dados[qtde-(i+1)].gc += gp;
			dados[qtde-(i+1)].jogos += 1;
			dados[qtde-(i+1)].saldo += gc - gp;
			
			if(gc > gp){
				dados[i].vitorias += 1;
				dados[i].pontos += 3;
				dados[qtde-(i+1)].derrotas += 1;
			} else if(gp > gc){
				dados[qtde-(i+1)].vitorias += 1;
				dados[qtde-(i+1)].pontos += 3;
				dados[i].derrotas += 1;
			} else {
				dados[i].empates += 1;
				dados[qtde-(i+1)].empates += 1;
				dados[i].pontos += 1;
				dados[qtde-(i+1)].pontos += 1;
			}
		}
		strcpy(ultimo,times[qtde-1].nome_time);
		for(j=qtde;j>1;j--){
			strcpy(aux,times[j-1].nome_time);
			strcpy(times[j-1].nome_time,times[j].nome_time);
			strcpy(times[j].nome_time,aux);
		}
		strcpy(times[1].nome_time,ultimo);
		fprintf(arqSaida,"\n");
		printf("\n");
	}
	
	do { //ordenando de modo decrescente
    	j = 0;
    	for(i=0;i<qtde;i++){
    		if(dados[i].pontos < dados[i+1].pontos) {
        		aux_int = dados[i].pontos;
        		dados[i].pontos = dados[i+1].pontos;
        		dados[i+1].pontos = aux_int;
        		
        		aux_int = dados[i].jogos;
        		dados[i].jogos = dados[i+1].jogos;
        		dados[i+1].jogos = aux_int;
        		
        		aux_int = dados[i].vitorias;
        		dados[i].vitorias = dados[i+1].vitorias;
        		dados[i+1].vitorias = aux_int;
        		
        		aux_int = dados[i].empates;
        		dados[i].empates = dados[i+1].empates;
        		dados[i+1].empates = aux_int;
        		
        		aux_int = dados[i].derrotas;
        		dados[i].derrotas = dados[i+1].derrotas;
        		dados[i+1].derrotas = aux_int;
        		
        		aux_int = dados[i].gp;
        		dados[i].gp = dados[i+1].gp;
        		dados[i+1].gp = aux_int;
        		
        		aux_int = dados[i].gc;
        		dados[i].gc = dados[i+1].gc;
        		dados[i+1].gc = aux_int;
        		
        		aux_int = dados[i].saldo;
        		dados[i].saldo = dados[i+1].saldo;
        		dados[i+1].saldo = aux_int;
        		
        		strcpy(aux,dados[i].nome_time);
        		strcpy(dados[i].nome_time,dados[i+1].nome_time);
        		strcpy(dados[i+1].nome_time,aux);
        		j = 1;
			} else if (dados[i].pontos == dados[i+1].pontos && dados[i].vitorias < dados[i+1].vitorias){
				aux_int = dados[i].pontos;
        		dados[i].pontos = dados[i+1].pontos;
        		dados[i+1].pontos = aux_int;
        		
        		aux_int = dados[i].jogos;
        		dados[i].jogos = dados[i+1].jogos;
        		dados[i+1].jogos = aux_int;
        		
        		aux_int = dados[i].vitorias;
        		dados[i].vitorias = dados[i+1].vitorias;
        		dados[i+1].vitorias = aux_int;
        		
        		aux_int = dados[i].empates;
        		dados[i].empates = dados[i+1].empates;
        		dados[i+1].empates = aux_int;
        		
        		aux_int = dados[i].derrotas;
        		dados[i].derrotas = dados[i+1].derrotas;
        		dados[i+1].derrotas = aux_int;
        		
        		aux_int = dados[i].gp;
        		dados[i].gp = dados[i+1].gp;
        		dados[i+1].gp = aux_int;
        		
        		aux_int = dados[i].gc;
        		dados[i].gc = dados[i+1].gc;
        		dados[i+1].gc = aux_int;
        		
        		aux_int = dados[i].saldo;
        		dados[i].saldo = dados[i+1].saldo;
        		dados[i+1].saldo = aux_int;
        		
        		strcpy(aux,dados[i].nome_time);
        		strcpy(dados[i].nome_time,dados[i+1].nome_time);
        		strcpy(dados[i+1].nome_time,aux);
        		j = 1;
			} else if (dados[i].pontos == dados[i+1].pontos && dados[i].vitorias == dados[i+1].vitorias && dados[i].saldo < dados[i+1].saldo){
				aux_int = dados[i].pontos;
        		dados[i].pontos = dados[i+1].pontos;
        		dados[i+1].pontos = aux_int;
        		
        		aux_int = dados[i].jogos;
        		dados[i].jogos = dados[i+1].jogos;
        		dados[i+1].jogos = aux_int;
        		
        		aux_int = dados[i].vitorias;
        		dados[i].vitorias = dados[i+1].vitorias;
        		dados[i+1].vitorias = aux_int;
        		
        		aux_int = dados[i].empates;
        		dados[i].empates = dados[i+1].empates;
        		dados[i+1].empates = aux_int;
        		
        		aux_int = dados[i].derrotas;
        		dados[i].derrotas = dados[i+1].derrotas;
        		dados[i+1].derrotas = aux_int;
        		
        		aux_int = dados[i].gp;
        		dados[i].gp = dados[i+1].gp;
        		dados[i+1].gp = aux_int;
        		
        		aux_int = dados[i].gc;
        		dados[i].gc = dados[i+1].gc;
        		dados[i+1].gc = aux_int;
        		
        		aux_int = dados[i].saldo;
        		dados[i].saldo = dados[i+1].saldo;
        		dados[i+1].saldo = aux_int;
        		
        		strcpy(aux,dados[i].nome_time);
        		strcpy(dados[i].nome_time,dados[i+1].nome_time);
        		strcpy(dados[i+1].nome_time,aux);
        		j = 1;
			} else if(dados[i].pontos == dados[i+1].pontos && dados[i].vitorias == dados[i+1].vitorias && dados[i].saldo == dados[i+1].saldo && dados[i].gp < dados[i+1].gp){
				aux_int = dados[i].pontos;
        		dados[i].pontos = dados[i+1].pontos;
        		dados[i+1].pontos = aux_int;
        		
        		aux_int = dados[i].jogos;
        		dados[i].jogos = dados[i+1].jogos;
        		dados[i+1].jogos = aux_int;
        		
        		aux_int = dados[i].vitorias;
        		dados[i].vitorias = dados[i+1].vitorias;
        		dados[i+1].vitorias = aux_int;
        		
        		aux_int = dados[i].empates;
        		dados[i].empates = dados[i+1].empates;
        		dados[i+1].empates = aux_int;
        		
        		aux_int = dados[i].derrotas;
        		dados[i].derrotas = dados[i+1].derrotas;
        		dados[i+1].derrotas = aux_int;
        		
        		aux_int = dados[i].gp;
        		dados[i].gp = dados[i+1].gp;
        		dados[i+1].gp = aux_int;
        		
        		aux_int = dados[i].gc;
        		dados[i].gc = dados[i+1].gc;
        		dados[i+1].gc = aux_int;
        		
        		aux_int = dados[i].saldo;
        		dados[i].saldo = dados[i+1].saldo;
        		dados[i+1].saldo = aux_int;
        		
        		strcpy(aux,dados[i].nome_time);
        		strcpy(dados[i].nome_time,dados[i+1].nome_time);
        		strcpy(dados[i+1].nome_time,aux);
        		j = 1;
			}
    	}
  	} while(j);	
	
	//Gerando arquivo de Saida
	fprintf(arqSaida,"Time:    	Jogos:    Pontos:    Vitorias:    Empates:    Derrotas:    GP:    GC:    Saldo:\n");
	printf("Time:    	Jogos:    Pontos:    Vitorias:    Empates:    Derrotas:    GP:    GC:    Saldo:\n");
	for(cont=0;cont<qtde;cont++){
		fprintf(arqSaida,"%s    	  %02d         %02d          %02d          %02d          %02d         %02d     %02d      %02d\n",dados[cont].nome_time,dados[cont].jogos,dados[cont].pontos,dados[cont].vitorias,dados[cont].empates,dados[cont].derrotas,dados[cont].gp,dados[cont].gc,dados[cont].saldo);
		printf("%s    	  %02d         %02d          %02d          %02d          %02d         %02d     %02d      %02d\n",dados[cont].nome_time,dados[cont].jogos,dados[cont].pontos,dados[cont].vitorias,dados[cont].empates,dados[cont].derrotas,dados[cont].gp,dados[cont].gc,dados[cont].saldo);
	}
	fclose(arqSaida);
	printf("\n\nFIM DO PROGRAMA\n\nPressione qualquer tecla para continuar...\n\n");
	system("pause");
}
