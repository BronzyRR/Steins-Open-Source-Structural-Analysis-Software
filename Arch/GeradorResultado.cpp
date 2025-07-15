#include "GeradorResultado.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include "Node.h"
#include "Barra.h"
#include "Estrutura.h"

#define THRESHOLD 0.0000000001

void GeradorResultado::calcularResultado(std::string nomeArquivo, std::vector<Node>& nosEstrutura, std::vector<Barra>& barrasEstrutura) {
	/*Cria-se o arquivo com o resultado dos deslocamentos e reações nos nós e esforços internos
	nas barras*/
	std::string path = "Arquivos/Resultados/" + nomeArquivo + ".txt";
	std::ofstream resultado(path);

	/*O primeiro passo é definir os nós que estão efetivamente conectados, ou seja,
	quais são os pórticos formados pelo conjunto de nós da estrutura. */

	/*Para isso, deve-se inicializar a lista de adjacência. Cada nó irá conter uma
	  lista com os demais nós com quem possui conexão.*/
	std::vector<std::vector<int>> listaDeAdjacencia;

	//a lista de adjacencia terá n vectors. Em que n é o número de nós informados.
	listaDeAdjacencia.resize(nosEstrutura.size());

	/*Logo após, deve-se criar uma estrutura map (que salva os dados em pares: uma chave e seu valor).
	* A chave será igual ao id do nó, o valor será sua posição ordenada de 1 a N. Isto é necessário para
	* os casos de descontinuidade entre o ID e a posição do Nó. Por exemplo, caso o usuário apague alguns
	* nós, o nó de ID=5 pode estar na posição 2 do vector, bagunçando o algoritmo. Para evitar isso, usa-se o
	* map. :) */
	std::map<int, int> posicaoDoNoPeloId;

	//Inicializar o map em questão
	for (int i = 0; i < nosEstrutura.size(); i++) {
		posicaoDoNoPeloId.insert(std::make_pair(nosEstrutura[i].getId(), i));
	}

	//Logo após, faz-se necessário criar a lista de adjacência, ou seja, inserir os dados.
	for (int i = 0; i < barrasEstrutura.size(); i++) {
		//posição no vector do nó 01
		int posicaoNo1 = posicaoDoNoPeloId[barrasEstrutura[i].n1.getId()];

		//posição no vector do nó 02
		int posicaoNo2 = posicaoDoNoPeloId[barrasEstrutura[i].n2.getId()];

		//inserir o nó 02 na lista de adjacência do nó 01 da barra
		listaDeAdjacencia[posicaoNo1].push_back(barrasEstrutura[i].n2.getId());

		//inserir o nó 01 na lista de adjacência do nó 02 da barra
		listaDeAdjacencia[posicaoNo2].push_back(barrasEstrutura[i].n1.getId());
	}

	/*Se o nó em questão já foi visitado ou não pelo algoritmo de flood fill.No início
	todos são inicializados com o valor de -1, ou seja, que ainda não foram visitados*/
	std::vector<int> componente;
	componente.resize(nosEstrutura.size());
	for (int i = 0; i < nosEstrutura.size(); i++) {
		componente[i] = -1;
	}
	
	std::vector<Node> nosAnalisados; //nos que formam um grafo especifico
	std::vector<Barra> barrasAnalisadas; //barras que formam um grafo especifico
	std::set<int> nosPortico; //nos que formam um grafo específico

	/*Com todos esses parâmetros definidos, pode-se iniciar o flood fill propriamente dito.
	* No caso, optou-se pelo método BFS (breadth-first-search). O objetivo primeiramente é
	  determinar a relação dos nós da estrutura, ou seja, os nós que formam o grafo. Com isso
	  definido, pode-se determinar - posteriormente - as barras.*/
	int contadorGrafo = 0;
	for (int i = 0; i < nosEstrutura.size(); i++) {

		if (componente[i] == -1) { //se o nó em questão ainda não foi processado
			contadorGrafo++; //crie mais um grafo, porque se trata de um novo "ramo"
			nosAnalisados.clear(); //limpe o vector dos nós, porque é um grafo novo
			barrasAnalisadas.clear(); //limpe o vector das barras, porque é um grafo novo
			nosPortico.clear();

			//realizar a BFS
			std::queue<int> filaGrafo; 
			filaGrafo.push(nosEstrutura[i].getId());
			componente[i] = 1;

			int idNoAtual, posNoAtual;
			while (!filaGrafo.empty()) {
				idNoAtual = filaGrafo.front();
				posNoAtual = posicaoDoNoPeloId[idNoAtual];
				filaGrafo.pop();

				//adicionar esse nó na estrutura do novo grafo/portico
				nosAnalisados.push_back(nosEstrutura[posNoAtual]);

				for (int j = 0; j < listaDeAdjacencia[posNoAtual].size(); j++) {
					int idNoSecundario = listaDeAdjacencia[posNoAtual][j];
					int posNoSecundario = posicaoDoNoPeloId[idNoSecundario];

					if (componente[posNoSecundario] == -1) {
						componente[posNoSecundario] = 1;
						filaGrafo.push(listaDeAdjacencia[posNoAtual][j]);
					}
					else {
						continue;
					}
				}
			}

			//após obter a relação dos nós, irei salvar tal relação em um set para facilitar a busca
			for (int j = 0; j < nosAnalisados.size(); j++) {
				nosPortico.insert(nosAnalisados[j].getId());
			}

			//com a relação dos nós definidas, adiciona-se as barras em que ambos os nós estão na relação!
			for (int j = 0; j < barrasEstrutura.size(); j++) {
				int idNo1 = barrasEstrutura[j].n1.getId();
				int idNo2 = barrasEstrutura[j].n2.getId();

				if ((nosPortico.find(idNo1) != nosPortico.end()) && (nosPortico.find(idNo2) != nosPortico.end())) {
					barrasAnalisadas.push_back(barrasEstrutura[j]);
				}
			}

			Estrutura::calcular(nosAnalisados, barrasAnalisadas);
			
			//Agora deve-se escrever os resultados num arquivo .txt
			resultado << "*************************************************RESULTADOS PORTICO " << contadorGrafo << "*************************************************" << std::endl;
			resultado << "************DADOS DOS NÓS************" << std::endl;
			resultado << std::endl;
			for (int i = 0; i < nosAnalisados.size(); i++) {
				int id = nosAnalisados[i].getId(); //id do nó
				double x = nosAnalisados[i].pos.getX(); //posição x do nó
				double y = nosAnalisados[i].pos.getY(); //posição y do nó

				double dxGlobal = nosAnalisados[i].getDxGlobal(); //deslocamento em x [referência global]
				double dyGlobal = nosAnalisados[i].getDyGlobal(); //deslocamento em y [referência global]
				double rzGlobal = nosAnalisados[i].getRzGlobal(); //rotação em z [referência global]

				double reacaoEmX = nosAnalisados[i].getReacaoEmX(); //reação em x [referência global]
				double reacaoEmY = nosAnalisados[i].getReacaoEmY(); //reação em y [referência global]
				double reacaoEmZ = nosAnalisados[i].getReacaoEmZ(); //reação em z [referência global]

				if (abs(dxGlobal) < THRESHOLD) {
					dxGlobal = 0.0;
				}

				if (abs(dyGlobal) < THRESHOLD) {
					dyGlobal = 0.0;
				}

				if (abs(rzGlobal) < THRESHOLD) {
					rzGlobal = 0.0;
				}

				if (abs(reacaoEmX) < THRESHOLD) {
					reacaoEmX = 0.0;
				}

				if (abs(reacaoEmY) < THRESHOLD) {
					reacaoEmY = 0.0;
				}

				if (abs(reacaoEmZ) < THRESHOLD) {
					reacaoEmZ = 0.0;
				}

				bool restricaoEmX = nosAnalisados[i].getRh(); //restrição em x
				bool restricaoEmY = nosAnalisados[i].getRv(); //restrição em y
				bool restricaoEmZ = nosAnalisados[i].getRz(); //restrição em z

				resultado << "NÓ [ID = " << id << "] [X = "<< x << " ; Y = " << y << " ]: " << std::endl;
				if (restricaoEmX) {
					resultado << "REAÇÃO EM X = " << reacaoEmX << std::endl;
				}
				else {
					resultado << "DESLOCAMENTO EM X = " << dxGlobal << std::endl;
				}

				if (restricaoEmY) {
					resultado << "REAÇÃO EM Y = " << reacaoEmY << std::endl;
				}
				else {
					resultado << "DESLOCAMENTO EM Y = " << dyGlobal << std::endl;
				}

				if (restricaoEmZ) {
					resultado << "REAÇÃO EM Z = " << reacaoEmZ << std::endl;
				}
				else {
					resultado << "ROTAÇÃO EM Z = " << rzGlobal << std::endl;
				}
				resultado << std::endl;
			}

			resultado << std::endl;
			resultado << "************DADOS DAS BARRAS************" << std::endl;
			resultado << std::endl;
			for (int i = 0; i < barrasAnalisadas.size(); i++) {
				int id1 = barrasAnalisadas[i].n1.getId();
				int id2 = barrasAnalisadas[i].n2.getId();

				EquacaoPolinomial deslocamento = barrasAnalisadas[i].getEquacaoDeslocamento();
				EquacaoPolinomial rotacao = barrasAnalisadas[i].getEquacaoRotacao();
				EquacaoPolinomial momentoFletor = barrasAnalisadas[i].getEquacaoMomentoFletor();
				EquacaoPolinomial esforcoCortante = barrasAnalisadas[i].getEquacaoEsforcoCortante();
				EquacaoPolinomial esforcoNormal = barrasAnalisadas[i].getEquacaoEsforcoNormal();
				EquacaoPolinomial deslocamentoAxial = barrasAnalisadas[i].getEquacaoDeslocamentoAxial();

				resultado << "BARRA [ID1 = " << id1 << "; ID2 = " << id2 << "]: \n";
				resultado << "EQUAÇÃO DESLOCAMENTO = " << deslocamento.getString();
				resultado << "EQUAÇÃO ROTAÇÃO = " << rotacao.getString();
				resultado << "EQUAÇÃO MOMENTO FLETOR = " << momentoFletor.getString();
				resultado << "EQUAÇÃO ESFORÇO CORTANTE = " << esforcoCortante.getString();
				resultado << "EQUAÇÃO ESFORÇO NORMAL = " << esforcoNormal.getString();	
				resultado << "EQUAÇÃO DESLOCAMENTO AXIAL = " << deslocamentoAxial.getString();
				resultado << "\n\n";
			}
		}
		else {
			continue;
		}
	}
}

void GeradorResultado::lerArquivo(std::string nomeArquivo) {

	/* O primeiro passo é ler o arquivo .txt que contem os dados dos nos e barras da estrutura. 
	Um adendo importante, é de que os carregamentos já foram compatibilizados na classe GeradorArquivo.
	Portanto, não há necessidade de se repetir tal procedimento. */

	std::string path = "Arquivos/DadosEntrada/" + nomeArquivo + ".txt";
	std::ifstream arquivo(path);

	//Os primeiros dados são, respectivamente, o número de nós e o número de barras
	int numeroDeNos, numeroDeBarras;

	arquivo >> numeroDeNos;
	arquivo >> numeroDeBarras;

	//Logo após, deve-se ler a quantidade especificada de nós e barras
	std::vector<Node> nosEstrutura;
	std::vector<Barra> barrasEstrutura;

	//Primeiramente, deve-se ler os nós.
	//VARIÁVEIS AUXILIARES
	int id;
	double x, y;
	double fx, fy, mz;
	bool restricaoHorizontal, restricaoVertical, restricaoRotacao;

	for (int i = 0; i < numeroDeNos; i++) {
		arquivo >> id;
		arquivo >> x;
		arquivo >> y;
		arquivo >> fx;
		arquivo >> fy;
		arquivo >> mz;
		arquivo >> restricaoHorizontal;
		arquivo >> restricaoVertical;
		arquivo >> restricaoRotacao;
		
		Node noAuxiliar(id, x, y, restricaoHorizontal, restricaoVertical, restricaoRotacao);
		noAuxiliar.setFx(fx);
		noAuxiliar.setFy(fy);
		noAuxiliar.setMz(mz);
		nosEstrutura.push_back(noAuxiliar);
	}

	//Em seguida, cria-se um map relacionando o id do nó com sua posição no vetor
	std::map<int, int> posicaoDoNoPeloId;
	for (int i = 0; i < nosEstrutura.size(); i++) {
		posicaoDoNoPeloId.insert(std::make_pair(nosEstrutura[i].getId(), i));
	}

	//Logo após, pode-se obter os dados das barras
	int id1, id2; //id dos nós que formam a barra
	double elasticidade, area, inercia;
	double fxGlobal, fyGlobal;
	bool rotulaN1, rotulaN2;
	double momentoFimBarraN1, momentoFimBarraN2;

	for (int i = 0; i < numeroDeBarras; i++) {
		arquivo >> id1;
		arquivo >> id2;
		arquivo >> elasticidade;
		arquivo >> area;
		arquivo >> inercia;
		arquivo >> fxGlobal;
		arquivo >> fyGlobal;
		arquivo >> rotulaN1;
		arquivo >> rotulaN2;
		arquivo >> momentoFimBarraN1;
		arquivo >> momentoFimBarraN2;

		Barra barraAuxiliar(nosEstrutura[posicaoDoNoPeloId[id1]], nosEstrutura[posicaoDoNoPeloId[id2]], elasticidade,
			area, inercia, rotulaN1, rotulaN2);

		barraAuxiliar.setMomentoFimBarra(momentoFimBarraN1, momentoFimBarraN2);
		barraAuxiliar.setCargaDistribuidaGlobal(fxGlobal, fyGlobal);
			
		barrasEstrutura.push_back(barraAuxiliar);
	}

	//**************************COMPATIBILIZAÇÃO DOS CARREGAMENTOS*********************
	/*É necessário compatibilizar os carregamentos atuantes no nós, ou seja, adicionar(aos nós) os carregamentos
	equivalentes das barras.*/

	bool n1; //se o nó 1 da barra i já foi processado
	bool n2; //se o nó 2 da barra i já foi processado

	for (int i = 0; i < barrasEstrutura.size(); i++) { //percorrer todas as barras da estrutura

		//as flags são falsas no início para cada barra
		n1 = false;
		n2 = false;

		for (int j = 0; j < nosEstrutura.size(); j++) { //percorrer todos os nós da estrutura
			if (n1 && n2) { //se ambas as flags forem true, a compatibilização já foi feita para a barra i. Portanto, pode-se passar para a próxima barra.
				break;
			}

			if (barrasEstrutura[i].n1.getId() == nosEstrutura[j].getId()) { //se o nó em questão for igual ao n1 da barra, realizar a compatibilização
				n1 = true;

				//Checar se a barra é rotulada em relação ao nó N1
				if (barrasEstrutura[i].getRotulaN1()) {
					//Se a barra for rotulada em relação a esse nó, não se deve adicionar o momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N1(), barrasEstrutura[i].getFyEquivalenteGlobal_N1(), 0.0);
				}
				else {
					//Se a barra não for rotulada, o procedimento é o padrão, ou seja, adiciona-se a parcela do momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N1(), barrasEstrutura[i].getFyEquivalenteGlobal_N1(),
						barrasEstrutura[i].getMzEquivalenteGlobal_N1());
				}

			}
			else if (barrasEstrutura[i].n2.getId() == nosEstrutura[j].getId()) { //se o nó em questão for igual ao n2 da barra, realizar a compatilização
				n2 = true;

				//Checar se a barra é rotulada em relação ao nó N2
				if (barrasEstrutura[i].getRotulaN2()) {
					//Se a barra for rotulada em relação a esse nó, não se deve adicionar o momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N2(), barrasEstrutura[i].getFyEquivalenteGlobal_N2(), 0.0);
				}
				else {
					//Se a barra não for rotulada, o procedimento é o padrão, ou seja, adiciona-se a parcela do momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N2(), barrasEstrutura[i].getFyEquivalenteGlobal_N2(),
						barrasEstrutura[i].getMzEquivalenteGlobal_N2());
				}
			}
			else { //caso não seja igual nem a n1 e nem a n2, continuar para a próxima iteração do loop
				continue;
			}
		}
	}

	//enviar o vetores contendo os dados dos nós e das barras da estrutura para serem processados
	calcularResultado(nomeArquivo, nosEstrutura, barrasEstrutura);

}