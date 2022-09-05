#include <bits/stdc++.h>
#include<iostream>
#include <sys/time.h>
using namespace std;


//parace q temos uma boa base agr so falta tirar os comentario e pseudocodigos

int viabilidade = 0;	//cotes de viabilidade
int otimalidade = 0;	//corte de otimalidade
int old_func = 0;		//usar a funcao velha
int nodos = 0;			//contador de nodos


class ator{
	public:
	int preco;						//salario ator
	std::vector<int> inclusao = {};	//vetor de inclusao
};

vector<ator> atores = {}; //vetor de atores
std::vector<int> x = {}; 		//melhor conjunto ate agora
std::vector<int> optx = {}; 	//melhor conjunto ate agora
int optp = 99999999;	//melhor custo ate agora 
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
		//cout << aux.preco << " " <<count << "\n";
		for (int j = 0; j < count; j++){
			int aux2;
			cin >> aux2;
			//cout << aux2<< "\n";
			aux.inclusao.push_back(aux2);
		}
		//cout << aux.inclusao.size() << "\n";
		atores.push_back(aux);
	}
}

int profit(std::vector<int> x){
	int preco = 0;
	for (uint i = 0; i < x.size(); i++){
		preco += x.at(i) * atores.at(i).preco;
	}
	return preco;
}

int viavel(std::vector<int> x){
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
		soma += x.at(i);
	}
	vector<int> inclusao_a(tam_inclusao,0);
	if (soma == tam_personagens){
		//cout << tam_inclusao << "\n";
		for (uint i = 0; i < x.size(); i++){
			if(x.at(i) == 1){
				//cout << atores.at(i).preco << atores.at(i).inclusao.size() <<"\n";
				for (uint j = 0; j < atores.at(i).inclusao.size(); j++){
					//cout << atores.at(i).inclusao.at(j) << "\n";
					inclusao_a.at(atores.at(i).inclusao.at(j) - 1) = 1;
				}
			}	
		}
		/*cout << "entrada = " ;
		for (uint k = 0; k < x.size(); ++k){
			cout << x.at(k) << " ";
		}
		cout << "\n";
		cout << "profit = " << profit(x) << "\n" << "inclusao = ";
		for (uint k = 0; k < inclusao_a.size(); ++k){
			cout << inclusao_a.at(k) << " ";
		}
		cout << "\n";*/
		for (uint k = 0; k < inclusao_a.size(); ++k){
			if (inclusao_a.at(k) == 0){
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
	if (viabilidade == 0){
		for (uint i = 0; i < x.size(); i++){
			soma += x.at(i);
		}
		if (soma >= tam_personagens){
			cl = {0};
		} 
	}	
	if (l == tam_atores){
		cl = {};
	}	
	return cl;
}

int menor_ator(std::vector<int> x,int l){
	int menor = 99999999;
	for (uint i = l; i < x.size(); i++){
		if (x.at(i) == 0 && atores.at(i).preco < menor){
			//cout << "menor = " << atores.at(i).preco << "\n";
			menor = atores.at(i).preco;
		}
	}
	return menor;
}

int B(std::vector<int> x,int l){
	int base = profit(x);
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
			soma += x.at(i);
		}
	if(soma < tam_personagens){
		base += (tam_personagens - soma) * menor_ator(x,l);
	}
	//cout << "B = " << base << "\n";
	return base;	
}

int profit_min_expec(std::vector<int> x, int l, int soma){
	
	//nao ha atores restantes suficientes
	if (((int)x.size() - l) < soma){
		//cout << "FALHA\n" ; 
		return 99999999;
	}
	std::vector<int> aux(x.size(),0);
	//copy(x.begin(), x.end(), back_inserter(aux));  
	int j = l;
	for (int t = 0; t < soma; t++){
		int menor = 99999999;
		for (uint i = l; i < aux.size(); i++){
			if (aux.at(i) == 0 && atores.at(i).preco < menor){
				//cout << "menor = " << atores.at(i).preco << "\n";
				j = i; 
				menor = atores.at(i).preco;
			}
		}
		//cout << "\n";
		aux.at(j) = 1;
	}	
	int algo =  profit(aux);
	//cout << "L = " << l << "\n";
	//cout << "algo = "  << algo << "\n";
	return algo;
}


int B_novo(std::vector<int> x,int l){
	int base = profit(x);
	int soma = 0;
	for (uint i = 0; i < x.size(); i++){
		soma += x.at(i);
	}
	//cout << "personagens: "<< soma << " / " << tam_personagens <<  " espaco" << x.size() - l << " - " << tam_personagens - soma << " = " << int(x.size() - l - (tam_personagens - soma))<<  "\n"; 
	if(soma < tam_personagens){
		soma = tam_personagens - soma;	
		base += profit_min_expec(x,l,soma);
	}
	//cout << "B = " << base << "\n";
	return base;	
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
	/*else{
		cout << "entrada = " ;
		for (uint k = 0; k < x.size(); ++k){
			cout << x.at(k) << " ";
		}
		cout << "\n";
		cout <<"INVIAVEL \n";
	}*/
	nodos++;
	int nextchoice[tam_atores];
	int nextbound[tam_atores];
	std::vector<int> cl = calculaCL(l);  // calcula as opcoes viaveis? mas entao pra que serve a linha 12
	int count = 0;
	for (int a : cl){	// essa linha funciona em python (for a in Cl:)
		x.at(l) = a;	// o que eh Xi ?
		nextchoice[count] = a;				// usado pra descidir as proximas chamadas, talvez seja somente uma escolha binaria simples
		if(old_func == 0)
			nextbound[count] = B_novo(x,l); // o que faz B()?
		else{
			nextbound[count] = B(x,l);
		}
		//cout << B(x) << "\n";
		count++;		//mas por que count
	}
	for (int i = 0; i < count; i++){
		if (nextbound[i] >= optp && otimalidade == 0); //no caderno ta <= posso estar errado
		else{
			x.at(l) = nextchoice[i];	// o que krl eh Xi, n sei nem se eh um i
			branch_and_bound(l+1);	 //recusao
		} 
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
	struct timeval inicio, fim;
	gettimeofday(&inicio, NULL);
	branch_and_bound(0);	 	// aqui eh onde a magia deve acontecer
	gettimeofday(&fim, NULL);
	double tempo_exec;
  
    tempo_exec = (fim.tv_sec - inicio.tv_sec) * 1e6;
    tempo_exec = (tempo_exec + (fim.tv_usec - 
                              inicio.tv_usec)) * 1e-6;
	//double tempo_exec = double(fim - inicio) / double(CLOCKS_PER_SEC);
	cerr << "tempo de execusao: " << fixed << tempo_exec << setprecision(5) << " sec \n";
	cerr << "nodos explorados: " << nodos << " de " << ((2 << tam_atores) - 1) << "\n";
	// a saida real eh quase tao avancada quanto o q vc ta vendo
	if (optx.size() == 0){
		cout << "inviavel\n";
		return 1;
	}
	imprimesaida();	
	
	return 1;
}