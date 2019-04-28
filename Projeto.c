#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct calendario{
	int mes[5][7];
}Data;

// fazendo e imprimindo mes
void imprimemes(int m, int bissexto, Data print){
	int i, j, d=1, parar;
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		parar = 32;
	else if(m == 4 || m == 6 || m == 9 || m == 11)
		parar = 31;
	else if(m == 2 && bissexto == 1)
		parar = 30;
	else if(m == 2 && bissexto == 0)
		parar = 29;
	
	for(i=0;i<5;i++){
		for(j=0;j<7;j++){
			print.mes[i][j] = d;
			if(d == NULL)
				d = NULL;
			else
				d += 1;
			if(d == parar)
				d = NULL;}
		}
	for(i=0;i<5;i++){
		printf("|");
		for(j=0;j<7;j++){
			printf("%3.d",print.mes[i][j]);}
		puts(" |");}
}
// calculando o dia da semana
char* diasemana(int ano, int m, int d){
	char data[15];
	int k = d + (2*m) + (3*(m+1)/5) + ano + (ano/4) - (ano/100) + (ano/400) + 2;
	if(k % 7 == 0)
		strcpy(data,"Sábado");
	else if(k % 7 == 1)
		strcpy(data,"Domingo");
	else if(k % 7 == 2)
		strcpy(data,"Segunda-feira");
	else if(k % 7 == 3)
		strcpy(data,"Terça-feira");
	else if(k % 7 == 4)
		strcpy(data,"Quarta-feira");
	else if(k % 7 == 5)
		strcpy(data,"Quinta-feira");
	else if(k % 7 == 6)
		strcpy(data,"Sexta-feira"); 
	return data;
}
// função para calcular feriados fixos
void calcula_fixo(int ano, int m){
	int d;
	char d_con[15], d_niver[15], d_natal[15];
	if(m == 1){
		m = 13;
		ano -= 1;
		d = 1;
		strcpy(d_con,diasemana(ano,m,d));}
    else if(m == 8){
    	d = 20;
		strcpy(d_niver,diasemana(ano,m,d));}
    else if(m == 12){
    	d = 25;
		strcpy(d_natal,diasemana(ano,m,d));} 
	// exibindo feriados fixos
	if(m == 13)
		printf("\nDia 1 - Confraternização Universal - %s\n" , d_con);
	else if(m == 8)
		printf("\nDia 20 - Aniversário de São Bernardo do Campo - %s\n" , d_niver);
	else if(m == 12)
		printf("\nDia 25 - Natal - %s\n" , d_natal);	   	  
}
// função para calcular feriados não fixos
void calcula_dinamico(int ano, int m, int bissexto){
	char datapascoa[15], datapaixao[15];
	// calculando mes e dia da pascoa
	int a = (ano % 19);
	int b = (ano / 100);
	int c = (ano % 100);
	int d = (b / 4);
	int e = (b % 4);
	int f = ((b+8) / 25);
	int g = ((b-f+1) / 3);
	int h = ((19*a+b-d-g+15) % 30);
	int i = (c / 4);
	int k = (c % 4);
	int l = ((32+2*e+2*i-h-k) % 7);
	int M = ((a+11*h+22*l) / 451);
	int m_pascoa = ((h+l-7*M+114) / 31);
	int d_pascoa = ((h+l-7*M+114) % 31)+1;
	// dia da semana da páscoa
	strcpy(datapascoa,diasemana(ano,m_pascoa,d_pascoa)); 
	
	// calculando paixão de cristo
	int d_paixao, m_paixao;
	d_paixao = d_pascoa - 2;
	m_paixao = 4;
	if(d_paixao == (-1)){
		d_paixao = 30;
		m_paixao = 3;}
	else if(d_paixao == 0){
		d_paixao = 31;
		m_paixao = 3;}
	// dia da semana da paixão de cristo
	strcpy(datapaixao,diasemana(ano,m_paixao,d_paixao)); 
	
	// calculando o dia da quarta-feira de cinzas
	int carnaval, resto, mes_c;
	carnaval = 46 - d_pascoa;
	if(m_pascoa == 4 && carnaval < 31){
		carnaval = 31 - carnaval;	
		mes_c = 3;}
    else if(m_pascoa == 4 && carnaval >= 31 && bissexto == 0){
		resto = carnaval - 31;
		carnaval = 28 - resto;
		mes_c = 2; }
	else if(m_pascoa == 4 && carnaval >= 31 && bissexto == 1){
		resto = carnaval - 31;
		carnaval = 29 - resto; 
		mes_c = 2;}
    else if(m_pascoa == 3 && carnaval < 28 && bissexto == 0){
		carnaval = 28 - carnaval; 
		mes_c = 2; }
    else if(m_pascoa == 3 && carnaval < 29 && bissexto == 1){
	    carnaval = 29 - carnaval;
		mes_c = 2; }
		
	// exibindo quarta-feira de cinzas
	if(m == 2 && mes_c == 2 && m_pascoa == 3)
		printf("\nDia %d - Quarta-feira de Cinzas\n", carnaval);
	else if(m == 2 && mes_c == 2 && m_pascoa == 4)
		printf("\nDia %d - Quarta-feira de Cinzas\n", carnaval);
    else if(m == 3 && mes_c == 3 && m_pascoa == 4)
		printf("\nDia %d - Quarta-feira de Cinzas\n", carnaval);
	
	// exibindo paixão de cristo e páscoa
	if(m == 3 && m_paixao == 3 && m_pascoa == 3){
		printf("\nDia %d - Paixão de Cristo - %s", d_paixao,datapaixao);
		printf("\nDia %d - Páscoa - %s\n", d_pascoa,datapascoa);}
    else if(m == 3 && m_paixao == 3 && m_pascoa == 4)
		printf("\nDia %d - Paixão de Cristo - %s\n", d_paixao,datapaixao);
    else if(m == 4 && m_paixao == 3 && m_pascoa == 4)
		printf("\nDia %d - Páscoa - %s\n", d_pascoa,datapascoa);
	else if(m == 4 && m_paixao == 4 && m_pascoa == 4){
		printf("\nDia %d - Paixão de Cristo - %s", d_paixao,datapaixao);
		printf("\nDia %d - Páscoa - %s\n", d_pascoa,datapascoa);}
}

int main(){
	setlocale(LC_ALL,"Portuguese");
	int ano, bissexto = 0, m = 1;
	printf("Insira o ano que deseja ver: ");
	scanf("%d", &ano);
	Data print;
	// ano bissexto se variável for igual a 1 
	if(ano % 400 == 0 || ano % 4 == 0 && ano % 100 != 0)
		bissexto = 1;
	// mostrando calendário
	puts("\n============================================================");
	printf("Calendário do ano %d e seus respectivos feriados:\n",ano);
	printf("\n\tJANEIRO\n");
	imprimemes(m,bissexto,print);
	calcula_fixo(ano,m);
	m += 1;
	if(bissexto == 0){
		printf("\n\tFEVEREIRO\n");
		imprimemes(m,bissexto,print);
		calcula_dinamico(ano,m,bissexto);
		m += 1;}
	else if(bissexto == 1){
		printf("\n\tFEVEREIRO\n");
		imprimemes(m,bissexto,print);
		calcula_dinamico(ano,m,bissexto);
		m += 1;}
	printf("\n\tMARÇO\n");
	imprimemes(m,bissexto,print); 
	calcula_dinamico(ano,m,bissexto);
	m += 1;
	printf("\n\tABRIL\n");
	imprimemes(m,bissexto,print);
	calcula_dinamico(ano,m,bissexto);
	m += 1;
	printf("\n\tMAIO\n");
	imprimemes(m,bissexto,print);
	m += 1;
	printf("\n\tJUNHO\n");
	imprimemes(m,bissexto,print);
	m += 1;
	printf("\n\tJULHO\n");
	imprimemes(m,bissexto,print);
	m += 1;
	printf("\n\tAGOSTO\n");
	imprimemes(m,bissexto,print);
	calcula_fixo(ano,m);
	m += 1;
	printf("\n\tSETEMBRO\n");
	imprimemes(m,bissexto,print);
	m += 1;
	printf("\n\tOUTUBRO\n");
	imprimemes(m,bissexto,print);
	m += 1;
	printf("\n\tNOVEMBRO\n");
	imprimemes(m,bissexto,print);
	m += 1;
	printf("\n\tDEZEMBRO\n");
	imprimemes(m,bissexto,print);
	calcula_fixo(ano,m);
	puts("\n============================================================");
	return 0;
}
