#include <bits/stdc++.h>
#include<iostream>
using namespace std;


//parace q temos uma boa base agr so falta tirar os comentario e pseudocodigos

int viabilidade = 0;	//cotes de viabilidade
int otimalidade = 0;	//corte de otimalidade
int old_func = 0;			//usar a funcao velha



class ator{
	public:
	int preco;						//salario ator
	std::vector<int> inclusao = {};	//vetor de inclusao
};

vector<ator> atores = {}; //vetor de atores
std::vector<int> inclusao_geral = {};
std::vector<int> x = {}; 		//melhor conjunto ate agora
std::vector<int> optx = {}; 	//melhor conjunto ate agora
int optp = 999999999;	//melhor custo ate agora 
int tam_atores;
int tam_inclusao;
int tam_personagens;

void ler_entrada(){
	cin >> tam_inclusao >> tam_atores >> tam_personagens;
	for (int j = 0; j < tam_inclusao; j++){
		inclusao_geral.push_back(0);
	}
	for (int i = 0; i < tam_atores; i++){
		x.push_back(0);
	}
	for (int i = 0; i < tam_atores; i++){
		ator aux; 
		int count;
		cin >> aux.preco >> count;
		for (int j = 0; j < count; j++){
			int aux2;
			cin >> aux2;
			aux.inclusao.push_back(aux2);
		}
		cout << aux.inclusao.size() << "\n";
		atores.push_back(aux);
	}
}

int viavel(std::vector<int> x){
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
		soma += x.at(i);
	}
	if (soma == tam_personagens){
		cout << tam_inclusao << "\n";
		vector<int> inclusao(tam_inclusao,0);
		for (uint i = 0; i < x.size(); i++){
			cout << atores.at(i).preco << atores.at(i).inclusao.size() <<"\n";
			for (uint j = 0; j < atores.at(i).inclusao.size(); j++){
				cout << atores.at(i).inclusao.at(j) << "\n";
				inclusao.at(atores.at(i).inclusao.at(j)-1) = 1;
			}
		}
		for (uint i = 0; i < inclusao.size(); i++){
			if (inclusao.at(i) == 0){
				return 0;
			}
		}
		return 1;	
	}
	return 0;
}

int profit(std::vector<int> x){
	int preco = 0;
	for (uint i = 0; i < x.size(); i++){
		preco += x.at(i) * atores.at(i).preco;
	}
	return preco;
}

std::vector<int> calculaCL(int l){
	std::vector<int> cl = {1,0} ;
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
		soma += x.at(i);
	}
	if (soma > tam_personagens){
		cl = {0};
	} 
	if (l == tam_atores){
		cl = {};
	}
	return cl;
}

int B(std::vector<int> x){
	return 1; 
}
//mais comentado so se eu comentar os comentarios
void branch_and_bound(int l){
	int P = 0; 
	if(viavel(x)){
		P = profit(x); //calcula o custo dessa solucao
		if(P < optp){				//max(P, opt) pra quem eh o novo fodao 
			optp = P;
			optx = x; //optx atualizado de revesgueio na batalha de P e optp 
		}
	}
	printf("aqui\n");
	int nextchoice[tam_atores];
	//int nextbound[tam_atores];
	std::vector<int> cl = calculaCL(l);  // calcula as opcoes viaveis? mas entao pra que serve a linha 12
	int count = 0;
	for (int a : cl){	// essa linha funciona em python (for a in Cl:)
		x.at(l) = a;	// o que eh Xi ?
		nextchoice[count] = a;				// usado pra descidir as proximas chamadas, talvez seja somente uma escolha binaria simples
		//nextbound[count] = B(x); // o que faz B()?
		count++;		//mas por que count
	}
	for (int i = 0; i < count; i++){
		//if (nextbound[i] >= optp) //no caderno ta <= posso estar errado
		//	return;
		x.at(l) = nextchoice[i];	// o que krl eh Xi, n sei nem se eh um i
		branch_and_bound(l+1);	 //recusao 
	}
	return;
}


void imprimesaida(){
	for (uint i = 0; i < optx.size(); ++i){
		if (optx.at(i) == 1){
			cout << i+1 << " ";
		}
	}

	cout << "\n" << optp << "\n";  
}
int main (int argc,char **argv){
	for (int i = 1; i < argc; i++){
		if (!strcmp(argv[i],"-a")){
			old_func = 1;
		}
		else if (!strcmp(argv[i],"-f")){
			otimalidade = 1;
		}
		else if (!strcmp(argv[i],"-o")){
			viabilidade = 1;
		}
		else{
			cout << "argumento invalido: " << argv[i] << "\n";
		}
	}
	ler_entrada(); 	// le a entrada de stdin 
	branch_and_bound(0);	 	// aqui eh onde a magia deve acontecer
	// a saida real eh quase tao avancada quanto o q vc ta vendo
	if (optx.size() == 0){
		cout << "inviavel\n";
		return 1;
	}
	imprimesaida();	
	
	return 1;
}