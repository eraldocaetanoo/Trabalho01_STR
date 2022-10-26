#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <math.h>

//
int maior(int v[], int tam){
	int i, maior = 0;
	for(i = 0;i < tam; i++){
        if(v[i] > maior){
            maior = v[i];
        }
    }
    return maior;
}

int menor(int v[], int tam){
	int i, menor = 10000;
	for(i = 0;i < tam; i++){
        if(v[i] < menor){
            menor = v[i];
        }
    }    
    return menor;
}

int main(){
	
	FILE *fp;
	char ch;
	char nomeArq[] = {"sistema1.txt"};
	
	fp = fopen(nomeArq,"r");
	
	int qtLinhas=0;
	while(fread (&ch, sizeof(char), 1, fp)) {
            if(ch == '\n') {
                qtLinhas++;
            }
    } 
    printf("%d\n\n",qtLinhas);
	fclose(fp);
	
	fp = fopen(nomeArq,"r");
	
	fscanf(fp,"%c", &ch);
      	
	while((ch = fgetc(fp)) != EOF){
    	if(ch == '\n') /* esse  \n  eh o final da linha, aqui pula uma linha */		
			break; 	   /* para pular outra linha precisa ir at� encontrar outro  \n */
	}
	
	int linhas = qtLinhas, colunas = 3;
	int matriz[linhas][colunas];
	
	int p[linhas];
	int c[linhas];
	int d[linhas];
	
	for (int i = 0; i < linhas; i++){
		for (int j = 0; j < colunas; j++){
				//fscanf(fp,"%d",&matriz[i][j]);
				if (j == 0){
					fscanf(fp,"%d",&p[i]);
				}
				if (j == 1){
					fscanf(fp,"%d",&c[i]);
				}
				if (j == 2){
					fscanf(fp,"%d",&d[i]);
				}	
		}	
	}

	fclose(fp);

	
	/*
	for (int j = 0; j < colunas; j++){
		for (int i = 0; i < linhas; i++){
			if (j == 0){
				p[i] = matriz[i][j];
			}
			if (j == 1){
				c[i] = matriz[i][j];
			}
			if (j == 2){
				d[i] = matriz[i][j];
			}
		}
	}
	*/
	for (int i = 0; i < linhas;i++){
		printf("T%d\tP= %d\tC= %d\tD= %d\n",i+1,p[i],c[i],d[i]);
	}
	/*
	for (int i = 0; i<12;i++){
		
		printf("%d\n",p[i]);
	}
	for (int i = 0; i<12;i++){
		
		printf("%d\n",c[i]);
	}
	*/
	
	//int tamP = sizeof(p)/sizeof(p[0]);
	//int tamC = sizeof(c)/sizeof(c[0]);
	//int tamD = sizeof(d)/sizeof(d[0]);
	//printf("%d\n", maior(p,linhas));
	//printf("%d\n", menor(p,linhas));
	//printf("%d\n", maior(c,linhas));
	//printf("%d\n", menor(c,linhas));
	//printf("%d\n", maior(d,linhas));
	//printf("%d\n", menor(d,linhas));
	
	
	/*
	for (int i = 0; i < linhas;i++){
		printf("%d\n",p[i]);
	}
	for (int i = 0; i < linhas;i++){
		printf("%d\n",c[i]);
	}
	for (int i = 0; i < linhas;i++){
		printf("%d\n",d[i]);
	}
	*/
	
	int N = qtLinhas;
	
	
	double somac = 0;
	double somap = 0;
	double somad = 0;
	
	
	for (int i = 0; i < N; i++){
		somac = c[i] + somac;
		somap = p[i] + somap;
		somad = d[i] + somad;
	}
	// RM (Rate Monotonic)
	
	double limiarUtilizacaoRM = 0.0;
	double utilizacao = 0.0;
	//printf("%d\n",N);
	//printf("%f\n",pow(2,(1.0/N)));
	
	utilizacao = somac/somap;
	
	limiarUtilizacaoRM = N*(pow(2,(1.0/N))-1);
	
	printf("%lf\n",utilizacao);
	printf("%lf\n",limiarUtilizacaoRM);
	
	int escRM = 0;
	
	
	for (int i = 0; i < linhas;i++){
		if (utilizacao <= limiarUtilizacaoRM || maior(p,linhas) % (p[i]) == 0){
			escRM = 1;	// escalonavel
		}
		else{
			escRM = 0;	// nao escalonavel
		}
	}
	
	
	if (escRM == 1){
		printf("Escalonavel por RM!\n");
		
		
				
	}
	else{
		printf("Nao escalonavel por RM!\n");
		//exit(0);
	}
	
	int escEDF = 0;
	
	for (int i = 0; i < linhas;i++){
		if (p[i] == d[i] && (utilizacao <= 1.0)){
			escEDF = 1;	// escalonavel
		}
		else if (d[i] < p[i] && (somac/somad) <= 1.0){
			escEDF = 1;	// escalonavel
		}
		else{
			escEDF = 0;	// nao escalonavel
			//exit(0);
		}
	}
	
	if (escEDF == 1){
		printf("Escalonavel por EDF!\n");
		
		
				
	}
	else{
		printf("Nao escalonavel por EDF!\n");
		//exit(0);
	}
	
	
	fflush(stdin);
//	getchar();
//	getch();
	return 0;
	
}
