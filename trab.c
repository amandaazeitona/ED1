/*
Universidade de Brasilia
Instituto de Ciencia Exatas
Departamento de Ciencia da Computacao

Estrutura de Dados - 1/2016

Aluno: Frederico Pinheiro Dib
Matricula: 15/0125925
Aluno: Amanda Oliveira Alves
Matricula: 15/0116276
Turma: A
Versao do compilador: Ubuntu 4.9.2
*/


#include <stdio.h>
#include <stdlib.h>


/*Funçoes de manuseio de pilha e lista de dado float*/
typedef struct elementof{
	float dado;
	struct elementof * proximo;
}t_elementof;


typedef struct listaf{
	t_elementof * primeiro;
	t_elementof * ultimo;
}t_listaf;


typedef struct pilhaf{
	t_listaf * l;
}t_pilhaf;

t_listaf * criaListaf(){
   t_listaf * l = (t_listaf *)malloc(sizeof(t_listaf));
   l->primeiro = NULL;
   l->ultimo = NULL;
   return l;
}


void insereIniciof(float valor, t_listaf * l){
    t_elementof * novoprimeiro = (t_elementof *)malloc(sizeof(t_elementof));
    novoprimeiro->dado = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}


void insereFinalf(float valor, t_listaf * l){
   t_elementof * novoultimo = (t_elementof *)malloc(sizeof(t_elementof));
   novoultimo->dado = valor;
   novoultimo->proximo = NULL; 
   if(l->primeiro == NULL){
      l->primeiro = novoultimo;
   }else{
     l->ultimo->proximo = novoultimo;
   }
   l->ultimo = novoultimo;
}


int estaVaziaf(t_listaf * l){
    if(l->primeiro == NULL){
       return 1;
    }
    return 0;
}


float removeIniciof(t_listaf * l){
    if(estaVaziaf(l)){
        return -1;
    }
    float tmp = l->primeiro->dado;
    t_elementof * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL){
       l->ultimo = NULL;
    }
    return tmp;
}


t_pilhaf * criaPilhaf(){
   t_pilhaf * p =  (t_pilhaf *)malloc(sizeof(t_pilhaf));
   p->l = criaListaf();
   return p;
}


void Empilharf(float valor,t_pilhaf * p){
  insereIniciof(valor, p->l);
}


float Desempilharf(t_pilhaf * p){
  return removeIniciof(p->l);
}


float estaVaziaPilhaf(t_pilhaf * p){
    return estaVaziaf(p->l);
}
/*FIM Float*/

/*Funçoes de manuseio de pilha e lista de dado char*/
typedef struct elemento{
	char dado;
	struct elemento * proximo;
}t_elemento;


typedef struct lista{
	t_elemento * primeiro;
	t_elemento * ultimo;
}t_lista;


typedef struct pilha{
	t_lista * l;
}t_pilha;


t_lista * criaLista(){
   t_lista * l = (t_lista *)malloc(sizeof(t_lista));
   l->primeiro = NULL;
   l->ultimo = NULL;
   return l;
}


void insereInicio(char valor, t_lista * l){
    t_elemento * novoprimeiro = (t_elemento *)malloc(sizeof(t_elemento));
    novoprimeiro->dado = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}


void insereFinal(char valor, t_lista * l){
   t_elemento * novoultimo = (t_elemento *)malloc(sizeof(t_elemento));
   novoultimo->dado = valor;
   novoultimo->proximo = NULL; 
   if(l->primeiro == NULL){
      l->primeiro = novoultimo;
   }else{
     l->ultimo->proximo = novoultimo;
   }
   l->ultimo = novoultimo;
}


int estaVazia(t_lista * l){
    if(l->primeiro == NULL){
       return 1;
    }
    return 0;
}


int removeInicio(t_lista * l){
    if(estaVazia(l)){
        return -1;
    }
    int tmp = l->primeiro->dado;
    t_elemento * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL){
       l->ultimo = NULL;
    }
    return tmp;
}


t_pilha * criaPilha(){
   t_pilha * p =  (t_pilha *)malloc(sizeof(t_pilha));
   p->l = criaLista();
   return p;
}


void Empilhar(char valor,t_pilha * p){
  insereInicio(valor, p->l);
}


char Desempilhar(t_pilha * p){
  return removeInicio(p->l);
}


int estaVaziaPilha(t_pilha * p){
    return estaVazia(p->l);
}
/*FIM char*/

/*Função que indica se o termo eh um operador, (ou um espaço para facilitar a identificação de um numero na função Conta)*/
int testeOperador(char *exp, int indice) {
	int i = indice;

	if(exp[i] == ' ') {
		return 1;
	}
	if(exp[i] == '+') {
		return 1;
	}
	else {
		if (exp[i] == '*') {
			return 1;
		}
		if (exp[i] == '-') {
			return 1;
		}
		if (exp[i] == '/') {
			return 1;
		}
		if (exp[i] == '(') {
			return 1;
		}
		if (exp[i] == ')') {
			return 1;
		}
	}
	return 0;
}

/*Funcão que retorna 1 caso na pilha tenha um operador de prioridade maior ou igual ao da string, e retorna 0 se nao houver, se for farenteses ou se a pilha tiver vazia*/
int Prioridade(char *exp, t_pilha *p, int indice) {
	int i = indice;
	
	if((exp[i] == '(') || (exp[i] == ')')) {
		return 0;
	}
	if(p->l->primeiro == NULL) {
		return 0;
	}
	else {
		if (((exp[i] == '*') && (p->l->primeiro->dado == '+')) || ((exp[i] == '*') && (p->l->primeiro->dado == '-'))){
			return 0;
		}
		else {
			if (((exp[i] == '/') && (p->l->primeiro->dado == '+')) || ((exp[i] == '/') && (p->l->primeiro->dado == '-'))){
				return 0;
			}
		}
	}
	return 1;
}

/*funcao que tranforma a string exp na forma infixa para a string posf na forma posfixa*/
void Posfixa(char *exp, char *posf) {
	int i=0, j=0;
	t_pilha *p = criaPilha();

	while(exp[i] != '\0') {  /*ate pecorrer toda a string exp, executa os comandos abaixo*/
		int indice = i;
		if(exp[i] == ' ') { /*se for espaço apenas incrementa o i*/
			i++;
		}
		else {
			if(testeOperador(exp, indice) == 0) { /*se for um numero é simplesmente passado para a nova string. e sera adicionado um espaço apos*/
				while((testeOperador(exp, i) == 0) && (exp[i] != '\0')) {
					posf[j] = exp[i];
					i++;
					j++;
				}
				posf[j] = ' ';
				j++;
			}
			else {
				if(Prioridade(exp, p, indice) == 1) { /*se for um operador que satisfaz a prioridade ele desempilha a pilha e grava o operado nela depois*/
					while((estaVaziaPilha(p) != 1) && (p->l->primeiro->dado != '(')) { /*so para ao chegar n final da pilha ou encontrar um parenteses aberto*/
						posf[j] = Desempilhar(p);
						j++;
					}
					Empilhar(exp[i], p); 
					i++;
				}
				else {
					if(exp[i] != ')') { /*se for diferente de parenteses fechado, empilha*/
						Empilhar(exp[i], p);
						i++;
					}
					else {
						while(p->l->primeiro->dado != '(') { /* se houver um parenteses fechado, desempilha ate encontrar o aberto*/
							posf[j] = Desempilhar(p);
							j++;		
						}
						Desempilhar(p); /*desempilha o aberto sem gravar na string*/
						i++;
					}
				}
			}
		}
	}
	while(estaVaziaPilha(p) != 1) { /*caso apos tudo a pilha ainda n esteja vazia, despilha o resto*/
		posf[j] = Desempilhar(p);
		j++;
	}
	posf[j] = '\0';
}

/*funcao que testa se o numero de parenteses aberto é igual ao numero de parenteses aberto. retorna 1 caso seja igual, e 0 caso nao*/
int Validez(char *exp) {
	int i = 0;
	t_pilha *p = criaPilha();
	
	while(exp[i] != '\0') { /*ate pecorrer toda a string exp, executa os comandos abaixo*/
		if (exp[i] == '(') {
			Empilhar('(', p);
		}
		else {
			if (exp[i] == ')') {
				if((p->l->primeiro != NULL) && (p->l->primeiro->dado != ')')) {
					Desempilhar(p);
				}
				else {
					return 0; /*se encontrar um parenteses fechado e a pilha estiver vazia, ou o dado ser um parenteses fechaddo, expreção invalida*/
				}
			}
		}
		i++;
	}
	if (estaVaziaPilha(p) == 1) { /*se apos tudo a pilha estiver vazia, expreção valida, se nao, expreção invalida*/
		return 1;
	}
	else {
		return 0;
	}
}

/*funcao com a finalidade de tranformar um char em um innteiro de mesma equivalencia*/
int Tranformar(char n) {
	if(n == '1') {
		return 1;
	}
	if(n == '2') {
		return 2;
	}
	if(n == '3') {
		return 3;
	}
	if(n == '4') {
		return 4;
	}
	if(n == '5') {
		return 5;
	}
	if(n == '6') {
		return 6;
	}
	if(n == '7') {
		return 7;
	}
	if(n == '8') {
		return 8;
	}
	if(n == '9') {
		return 9;
	}
	if(n == '0') {
		return 0;
	}
	return -10;
}

/*junto da  funcao "Tranforma", essa função tranforma multiplos algarismos numericos seguidos, em um so numero de mesma equivalencia*/
int contaNumero(int cont, char *posf, int k) {
	int valor, retorno = 0, i;
	while(cont > 0) {
		for(i=0;i<cont;i++) {
			if(i == 0) {
				valor = Tranformar(posf[k]);
			}
			else {
				valor = valor * 10;
			}

		}
		retorno = retorno + valor;
		cont--;
		k++;
	}
	return retorno;
}

/*efetua o calculo e retorna o resultado final*/
float Conta(char *posf) {
	int j = 0, cont, k;
	t_pilhaf *p = criaPilhaf();
	float primeiro, segundo, valor;

	while(posf[j] != '\0') { /*ate pecorrer toda a string exp, executa os comandos abaixo*/
		if(testeOperador(posf, j) != 1) { /*se for um numero executa as operações e transforma o numero em umm numero inteiro*/
			cont = 0;
			k = j;
			while(posf[j] != ' ') {
				cont++;
				j++;
			}
			Empilharf(contaNumero(cont, posf, k), p);
			j++;
		}
		else { /*ao encontrar um operador, desempilha 2 numeros e faz o calculo correspondente*/
			segundo = Desempilharf(p);
			primeiro = Desempilharf(p);
			if(posf[j] == '*') {
				valor = primeiro * segundo;
			}
			if(posf[j] == '+') {
				valor = primeiro + segundo;
			}
			if(posf[j] == '/') {
				valor = primeiro / segundo;
			}
			if(posf[j] == '-') {
				valor = primeiro - segundo;
			}
			Empilharf(valor, p); /*empilha o resultado*/
			j++;
		}
	}
	valor = Desempilharf(p); /*retorna o valor final*/
	return valor;
}


int main() {
	char exp[41];
	char posf[41];	
	printf("Digite a expressao\n");
	scanf("%[^\n]s", exp);
	getchar();
	if (Validez(exp) == 1) { /*se for valida: transforma a expreção na posfixa e calcula o resultado*/
		Posfixa(exp, posf);
		printf("%.2f\n", Conta(posf));
	}
	else {
		printf("A expressao nao eh valida!\n");
	}
	return 0;
}
