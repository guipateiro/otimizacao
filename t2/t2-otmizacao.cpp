#include <bits/stdc++.h>
using namespace std;


//parace q temos uma boa base agr so falta tirar os comentario e pseudocodigos


//oi Joao


int x[];  //conjunto atual
int optx; //melhor conjunto ate agora
int optp; //melhor custo ate agora 
int cl[]; //eu juro q nao entendi ate agr


//mais comentado so se eu comentar os comentarios
void branch_and_bound(int l){
	if([x0, ... , xn] eh solucao viavel){
		P = profit([x0, ... , xn]); //calcula o custo dessa solucao
		if(P < optp){				//max(P, opt) pra quem eh o novo fodao 
			optp = P;
			optx = [x0, ... , xn]; //optx atualizado de revesgueio na batalha de P e optp 
		}
	}
	cl = calculaCL();  // calcula as opcoes viaveis? mas entao pra que serve a linha 12
	int count = 0;
	for (cada a em Cl){	// essa linha funciona em python (for a in Cl:)
		Xi = a;	// o que eh Xi ?
		nextchoice[count] = a;				// usado pra descidir as proximas chamadas, talvez seja somente uma escolha binaria simples
		nextbound[count] = B([x0, ... , xn]); // o que faz B()?
		count++;		//mas por que count
	}
	qsort(nextchoice); 	// ordena , mas n sei se é descescente ou cescente
	qsort(nextbound);	// ordena , mas n sei se é descescente ou cescente
	for (int i = 0; i < count-1; i++){
		if nextbound[i] >= optp; //no caderno ta <= posso estar errado
			return;
		Xi = nextchoice[i];	// o que krl eh Xi, n sei nem se eh um i
		branch_and_bound(l+1);	 //recusao 
	}
}
int main () {
	entrada = ler_entrada(); 	// le a entrada de stdin 
	verificaopcoes(); 			// -o, -a , -f vindo diretamente de argc e argv[]
	branch_and_bound(l);	 	// aqui eh onde a magia deve acontecer
	qsort(optx); 				// o vetor de atores deve estar ordenado
	// a saida real eh quase tao avancada quanto o q vc ta vendo
	cout << optx << "\n" << optp << "\n";  
}