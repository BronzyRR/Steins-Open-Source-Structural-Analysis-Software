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
	/*Cria-se o arquivo com o resultado dos deslocamentos e rea��es nos n�s e esfor�os internos
	nas barras*/
	std::string path = "Arquivos/Resultados/" + nomeArquivo + ".txt";
	std::ofstream resultado(path);

	/*O primeiro passo � definir os n�s que est�o efetivamente conectados, ou seja,
	quais s�o os p�rticos formados pelo conjunto de n�s da estrutura. */

	/*Para isso, deve-se inicializar a lista de adjac�ncia. Cada n� ir� conter uma
	  lista com os demais n�s com quem possui conex�o.*/
	std::vector<std::vector<int>> listaDeAdjacencia;

	//a lista de adjacencia ter� n vectors. Em que n � o n�mero de n�s informados.
	listaDeAdjacencia.resize(nosEstrutura.size());

	/*Logo ap�s, deve-se criar uma estrutura map (que salva os dados em pares: uma chave e seu valor).
	* A chave ser� igual ao id do n�, o valor ser� sua posi��o ordenada de 1 a N. Isto � necess�rio para
	* os casos de descontinuidade entre o ID e a posi��o do N�. Por exemplo, caso o usu�rio apague alguns
	* n�s, o n� de ID=5 pode estar na posi��o 2 do vector, bagun�ando o algoritmo. Para evitar isso, usa-se o
	* map. :) */
	std::map<int, int> posicaoDoNoPeloId;

	//Inicializar o map em quest�o
	for (int i = 0; i < nosEstrutura.size(); i++) {
		posicaoDoNoPeloId.insert(std::make_pair(nosEstrutura[i].getId(), i));
	}

	//Logo ap�s, faz-se necess�rio criar a lista de adjac�ncia, ou seja, inserir os dados.
	for (int i = 0; i < barrasEstrutura.size(); i++) {
		//posi��o no vector do n� 01
		int posicaoNo1 = posicaoDoNoPeloId[barrasEstrutura[i].n1.getId()];

		//posi��o no vector do n� 02
		int posicaoNo2 = posicaoDoNoPeloId[barrasEstrutura[i].n2.getId()];

		//inserir o n� 02 na lista de adjac�ncia do n� 01 da barra
		listaDeAdjacencia[posicaoNo1].push_back(barrasEstrutura[i].n2.getId());

		//inserir o n� 01 na lista de adjac�ncia do n� 02 da barra
		listaDeAdjacencia[posicaoNo2].push_back(barrasEstrutura[i].n1.getId());
	}

	/*Se o n� em quest�o j� foi visitado ou n�o pelo algoritmo de flood fill.No in�cio
	todos s�o inicializados com o valor de -1, ou seja, que ainda n�o foram visitados*/
	std::vector<int> componente;
	componente.resize(nosEstrutura.size());
	for (int i = 0; i < nosEstrutura.size(); i++) {
		componente[i] = -1;
	}
	
	std::vector<Node> nosAnalisados; //nos que formam um grafo especifico
	std::vector<Barra> barrasAnalisadas; //barras que formam um grafo especifico
	std::set<int> nosPortico; //nos que formam um grafo espec�fico

	/*Com todos esses par�metros definidos, pode-se iniciar o flood fill propriamente dito.
	* No caso, optou-se pelo m�todo BFS (breadth-first-search). O objetivo primeiramente �
	  determinar a rela��o dos n�s da estrutura, ou seja, os n�s que formam o grafo. Com isso
	  definido, pode-se determinar - posteriormente - as barras.*/
	int contadorGrafo = 0;
	for (int i = 0; i < nosEstrutura.size(); i++) {

		if (componente[i] == -1) { //se o n� em quest�o ainda n�o foi processado
			contadorGrafo++; //crie mais um grafo, porque se trata de um novo "ramo"
			nosAnalisados.clear(); //limpe o vector dos n�s, porque � um grafo novo
			barrasAnalisadas.clear(); //limpe o vector das barras, porque � um grafo novo
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

				//adicionar esse n� na estrutura do novo grafo/portico
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

			//ap�s obter a rela��o dos n�s, irei salvar tal rela��o em um set para facilitar a busca
			for (int j = 0; j < nosAnalisados.size(); j++) {
				nosPortico.insert(nosAnalisados[j].getId());
			}

			//com a rela��o dos n�s definidas, adiciona-se as barras em que ambos os n�s est�o na rela��o!
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
			resultado << "************DADOS DOS N�S************" << std::endl;
			resultado << std::endl;
			for (int i = 0; i < nosAnalisados.size(); i++) {
				int id = nosAnalisados[i].getId(); //id do n�
				double x = nosAnalisados[i].pos.getX(); //posi��o x do n�
				double y = nosAnalisados[i].pos.getY(); //posi��o y do n�

				double dxGlobal = nosAnalisados[i].getDxGlobal(); //deslocamento em x [refer�ncia global]
				double dyGlobal = nosAnalisados[i].getDyGlobal(); //deslocamento em y [refer�ncia global]
				double rzGlobal = nosAnalisados[i].getRzGlobal(); //rota��o em z [refer�ncia global]

				double reacaoEmX = nosAnalisados[i].getReacaoEmX(); //rea��o em x [refer�ncia global]
				double reacaoEmY = nosAnalisados[i].getReacaoEmY(); //rea��o em y [refer�ncia global]
				double reacaoEmZ = nosAnalisados[i].getReacaoEmZ(); //rea��o em z [refer�ncia global]

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

				bool restricaoEmX = nosAnalisados[i].getRh(); //restri��o em x
				bool restricaoEmY = nosAnalisados[i].getRv(); //restri��o em y
				bool restricaoEmZ = nosAnalisados[i].getRz(); //restri��o em z

				resultado << "N� [ID = " << id << "] [X = "<< x << " ; Y = " << y << " ]: " << std::endl;
				if (restricaoEmX) {
					resultado << "REA��O EM X = " << reacaoEmX << std::endl;
				}
				else {
					resultado << "DESLOCAMENTO EM X = " << dxGlobal << std::endl;
				}

				if (restricaoEmY) {
					resultado << "REA��O EM Y = " << reacaoEmY << std::endl;
				}
				else {
					resultado << "DESLOCAMENTO EM Y = " << dyGlobal << std::endl;
				}

				if (restricaoEmZ) {
					resultado << "REA��O EM Z = " << reacaoEmZ << std::endl;
				}
				else {
					resultado << "ROTA��O EM Z = " << rzGlobal << std::endl;
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
				resultado << "EQUA��O DESLOCAMENTO = " << deslocamento.getString();
				resultado << "EQUA��O ROTA��O = " << rotacao.getString();
				resultado << "EQUA��O MOMENTO FLETOR = " << momentoFletor.getString();
				resultado << "EQUA��O ESFOR�O CORTANTE = " << esforcoCortante.getString();
				resultado << "EQUA��O ESFOR�O NORMAL = " << esforcoNormal.getString();	
				resultado << "EQUA��O DESLOCAMENTO AXIAL = " << deslocamentoAxial.getString();
				resultado << "\n\n";
			}
		}
		else {
			continue;
		}
	}
}

void GeradorResultado::lerArquivo(std::string nomeArquivo) {

	/* O primeiro passo � ler o arquivo .txt que contem os dados dos nos e barras da estrutura. 
	Um adendo importante, � de que os carregamentos j� foram compatibilizados na classe GeradorArquivo.
	Portanto, n�o h� necessidade de se repetir tal procedimento. */

	std::string path = "Arquivos/DadosEntrada/" + nomeArquivo + ".txt";
	std::ifstream arquivo(path);

	//Os primeiros dados s�o, respectivamente, o n�mero de n�s e o n�mero de barras
	int numeroDeNos, numeroDeBarras;

	arquivo >> numeroDeNos;
	arquivo >> numeroDeBarras;

	//Logo ap�s, deve-se ler a quantidade especificada de n�s e barras
	std::vector<Node> nosEstrutura;
	std::vector<Barra> barrasEstrutura;

	//Primeiramente, deve-se ler os n�s.
	//VARI�VEIS AUXILIARES
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

	//Em seguida, cria-se um map relacionando o id do n� com sua posi��o no vetor
	std::map<int, int> posicaoDoNoPeloId;
	for (int i = 0; i < nosEstrutura.size(); i++) {
		posicaoDoNoPeloId.insert(std::make_pair(nosEstrutura[i].getId(), i));
	}

	//Logo ap�s, pode-se obter os dados das barras
	int id1, id2; //id dos n�s que formam a barra
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

	//**************************COMPATIBILIZA��O DOS CARREGAMENTOS*********************
	/*� necess�rio compatibilizar os carregamentos atuantes no n�s, ou seja, adicionar(aos n�s) os carregamentos
	equivalentes das barras.*/

	bool n1; //se o n� 1 da barra i j� foi processado
	bool n2; //se o n� 2 da barra i j� foi processado

	for (int i = 0; i < barrasEstrutura.size(); i++) { //percorrer todas as barras da estrutura

		//as flags s�o falsas no in�cio para cada barra
		n1 = false;
		n2 = false;

		for (int j = 0; j < nosEstrutura.size(); j++) { //percorrer todos os n�s da estrutura
			if (n1 && n2) { //se ambas as flags forem true, a compatibiliza��o j� foi feita para a barra i. Portanto, pode-se passar para a pr�xima barra.
				break;
			}

			if (barrasEstrutura[i].n1.getId() == nosEstrutura[j].getId()) { //se o n� em quest�o for igual ao n1 da barra, realizar a compatibiliza��o
				n1 = true;

				//Checar se a barra � rotulada em rela��o ao n� N1
				if (barrasEstrutura[i].getRotulaN1()) {
					//Se a barra for rotulada em rela��o a esse n�, n�o se deve adicionar o momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N1(), barrasEstrutura[i].getFyEquivalenteGlobal_N1(), 0.0);
				}
				else {
					//Se a barra n�o for rotulada, o procedimento � o padr�o, ou seja, adiciona-se a parcela do momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N1(), barrasEstrutura[i].getFyEquivalenteGlobal_N1(),
						barrasEstrutura[i].getMzEquivalenteGlobal_N1());
				}

			}
			else if (barrasEstrutura[i].n2.getId() == nosEstrutura[j].getId()) { //se o n� em quest�o for igual ao n2 da barra, realizar a compatiliza��o
				n2 = true;

				//Checar se a barra � rotulada em rela��o ao n� N2
				if (barrasEstrutura[i].getRotulaN2()) {
					//Se a barra for rotulada em rela��o a esse n�, n�o se deve adicionar o momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N2(), barrasEstrutura[i].getFyEquivalenteGlobal_N2(), 0.0);
				}
				else {
					//Se a barra n�o for rotulada, o procedimento � o padr�o, ou seja, adiciona-se a parcela do momento
					nosEstrutura[j].addCarga(barrasEstrutura[i].getFxEquivalenteGlobal_N2(), barrasEstrutura[i].getFyEquivalenteGlobal_N2(),
						barrasEstrutura[i].getMzEquivalenteGlobal_N2());
				}
			}
			else { //caso n�o seja igual nem a n1 e nem a n2, continuar para a pr�xima itera��o do loop
				continue;
			}
		}
	}

	//enviar o vetores contendo os dados dos n�s e das barras da estrutura para serem processados
	calcularResultado(nomeArquivo, nosEstrutura, barrasEstrutura);

}