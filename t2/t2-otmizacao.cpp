#include <bits/stdc++.h>
#include<iostream>
#include <sys/time.h>
using namespace std;

#define INF 99999999 //num grande



int viabilidade = 0;	//cotes de viabilidade
int otimalidade = 0;	//corte de otimalidade
int old_func = 0;		//usar a funcao velha
int nodos = 0;			//contador de nodos
int cortes_viabilidade = 0; //contador de cortes por viabilidade
int cortes_otimalidade = 0; //contador de cortes por otimalidade 
long poda_otm = 0;		//contador de nodos podados por cortes de otimalidade
long poda_via = 0;		//contador de nodos podados por cortes de viabilidade

class ator{
	public:
	int preco;						//salario ator
	std::vector<int> inclusao = {};	//vetor de inclusao
};

vector<ator> atores = {}; //vetor de atores
std::vector<int> x = {}; 		//melhor conjunto ate agora
std::vector<int> optx = {}; 	//melhor conjunto ate agora
long long optp = INF;	//melhor custo ate agora 
int tam_atores;
int tam_inclusao;
int tam_personagens;

void ler_entrada(){

	cin >> tam_inclusao >> tam_atores >> tam_personagens;
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
		atores.push_back(aux);
	}
}

int total_cost(std::vector<int> x){
	int preco = 0;
	for (uint i = 0; i < x.size(); i++){
		preco += x[i] * atores[i].preco;
	}
	return preco;
}

int viavel(std::vector<int> x){
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
		soma += x[i];
	}
	vector<int> inclusao_a(tam_inclusao,0);
	if (soma == tam_personagens){
		for (uint i = 0; i < x.size(); i++){
			if(x[i] == 1){
				for (uint j = 0; j < atores[i].inclusao.size(); j++){
					inclusao_a[atores[i].inclusao[j] - 1] = 1;
				}
			}	
		}
		for (uint k = 0; k < inclusao_a.size(); ++k){
			if (inclusao_a[k] == 0){
				return 0;
			}
		}
		return 1;	
	}
	return 0;
}



std::vector<int> calculaCL(int l){
	std::vector<int> cl = {1,0} ;
	int soma = 0;
	if (l == tam_atores){
		cl = {};
		return cl;	
	}
	if (viabilidade == 0){
		for (uint i = 0; i < x.size(); i++){
			soma += x.at(i);
		}
		if (soma >= tam_personagens){
			cl = {0};
			cortes_viabilidade++;
			poda_via += ((2 <<(tam_atores - l - 1)) - 1);
		} 

	}		
	return cl;
}

int menor_ator(std::vector<int> x,int l){
	long long menor = INF;
	for (uint i = l; i < x.size(); i++){
		if (x[i] == 0 && atores[i].preco < menor){
			menor = atores[i].preco;
		}
	}
	return menor;
}

int B(std::vector<int> x,int l){
	int base = total_cost(x);
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
			soma += x[i];
		}
	if(soma < tam_personagens){
		base += (tam_personagens - soma) * menor_ator(x,l);
	}
	return base;	
}

int total_cost_min_expec(std::vector<int> x, int l, int soma){
	
	//nao ha atores restantes suficientes
	if (((int)x.size() - l) < soma){
		return INF-1;
	}
	std::vector<int> aux(x.size(),0);

	int j = l;
	for (int t = 0; t < soma; t++){
		int menor = INF-1;
		for (uint i = l; i < aux.size(); i++){
			if (aux[i] == 0 && atores[i].preco < menor){
				j = i; 
				menor = atores[i].preco;
			}
		}
		aux[j] = 1;
	}	
	int algo =  total_cost(aux);
	return algo;
}


int B_novo(std::vector<int> x,int l){
	int base = total_cost(x);
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
		soma += x[i];
	}
	if(soma < tam_personagens){
		soma = tam_personagens - soma;	
		base += total_cost_min_expec(x,l,soma);
	}
	return base;	
}



void branch_and_bound(int l){
	int P = 0; 
	if(viavel(x)){
		P = total_cost(x); //calcula o custo dessa solucao
		if(P < optp){  //max(P, opt)
			optp = P;
			optx = x;
		}
	}

	nodos++;
	int nextchoice[tam_atores];
	int nextbound[tam_atores];
	std::vector<int> cl = calculaCL(l);  // calcula as opcoes viaveis
	int count = 0;
	for (int a : cl){	
		x[l] = a;	
		nextchoice[count] = a;				// usado pra decidir as proximas chamadas
		if(old_func == 0)
			nextbound[count] = B_novo(x,l);
		else{
			nextbound[count] = B(x,l);
		}
		count++;
	}
	for (int i = 0; i < count; i++){
		if (nextbound[i] >= optp && otimalidade == 0){
			cortes_otimalidade++;
			poda_otm += ((2 <<(tam_atores - l - 1)) - 1);
		}
		else{
			x[l] = nextchoice[i];	
			branch_and_bound(l+1);	 //recursao
		} 
	}
	return;
}


void imprimesaida(){
	int k = 0;
	
	cerr << "cortes por viabilidade: " << cortes_viabilidade << " (nodos podados: " << poda_via << ")\n";
	cerr << "cortes por otimalidade: " << cortes_otimalidade << " (nodos podados: " << poda_otm << ")\n";

	if (optx.size() == 0){
		cout << "inviavel\n";
		return ;
	}
	for (uint i = 0; i < optx.size(); i++){
		if (optx.at(i) == 1){
			cout << i+1;
			k++;
			if (k != tam_personagens){
				cout <<" ";
			}
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
	struct timeval inicio, fim;
	gettimeofday(&inicio, NULL);
	branch_and_bound(0);	 	// funcao principal
	gettimeofday(&fim, NULL);
	double tempo_exec;
  
    tempo_exec = (fim.tv_sec - inicio.tv_sec) * 1e6;
    tempo_exec = (tempo_exec + (fim.tv_usec - 
                              inicio.tv_usec)) * 1e-6;

	cerr << "tempo de execucao: " << fixed << tempo_exec << setprecision(5) << " sec \n";
	cerr << "nodos explorados: " << nodos << " de " << ((2 << tam_atores) - 1) << "\n";

	imprimesaida();	
	
	return 1;
}