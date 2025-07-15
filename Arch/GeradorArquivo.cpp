#include "GeradorArquivo.h"
#include "Erro.h"
#include "Barra.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Criar um arquivo através dos dados obtidos no console
void GeradorArquivo::obterDadosPeloConsole(){
		std::vector<Barra> barrasEstrutura;
		std::vector<Node> nosEstrutura;
		int contadorNo = 0; //número de nós, serve para definir o ID de cada um

		while (true) {
			int resposta;
			std::cout << "Deseja informar uma nova barra? [sim=1; nao=0]" << std::endl;
			std::cin >> resposta;

			if (resposta == 0) { //se a resposta for zero, interromper o loop
				break;
			}
			//se não, pode continuar o código
		
	
			//Variáveis auxiliares
			Node noAuxiliar[2]; //vetor com os nós que irão formar a barra
			double x, y; //posição dos nós
			bool restricaoHorizontal, restricaoVertical, restricaoRotacao; //restrições dos nós

			for (int i = 0; i < 2; i++) {
				std::cout << "\n\n";
				if (i == 0) {
					std::cout << "******************PRIMEIRO NO******************\n\n";
				}
				else {
					std::cout << "******************SEGUNDO NO******************\n\n";
				}

				std::cout << "Posicao X do ponto " << (i+1) << " da barra = ";
				std::cin >> x;

				std::cout << "Posicao Y do ponto " << (i + 1) << " da barra = ";
				std::cin >> y;

				bool jaExiste = false; //se o nó já existe
				for (int n = 0; n < nosEstrutura.size(); n++) {
					if ((nosEstrutura[n].pos.getX() == x) && (nosEstrutura[n].pos.getY() == y)) {
						noAuxiliar[i] = nosEstrutura[n];
						jaExiste = true;
						break;
					}
				}

				if (!jaExiste) {
					std::cout << "\n\n******************RESTRICOES******************\n";
					contadorNo++;
					std::cout << "Restricao horizontal [sim:1, nao:0] = ";
					std::cin >> restricaoHorizontal;
					std::cout << "Restricao vertical [sim:1, nao:0] = ";
					std::cin >> restricaoVertical;
					std::cout << "Restricao rotacao [sim:1, nao:0] = ";
					std::cin >> restricaoRotacao;

					noAuxiliar[i] = Node(contadorNo, x, y, restricaoHorizontal, restricaoVertical, restricaoRotacao);
					
					//carregamento nodais
					
					std::cout << "\n\n******************CARREGAMENTOS******************\n"; 
					double fx, fy, mz;
					std::cout << "Carregamento atuante em x [N] = ";
					std::cin >> fx;

					std::cout << "Carregamento atuante em y [N] = ";
					std::cin >> fy;

					std::cout << "Momento atuante em z [N.m] = ";
					std::cin >> mz;

					noAuxiliar[i].addCarga(fx, fy, mz);

					nosEstrutura.push_back(noAuxiliar[i]);
				}
				else {
					std::cout << "O no ja existe, portanto, nao ha necessidade de adiciona-lo novamente" << std::endl;
				}
			}

			std::cout << "\n\n******************DADOS DA BARRA******************\n";
			double elasticidade, area, inercia;

			std::cout << "Modulo de elasticidade da barra [n/m^2] = ";
			std::cin >> elasticidade;

			std::cout << "Area da barra [m^2] = ";
			std::cin >> area;

			std::cout << "Inercia [m^4] = ";
			std::cin >> inercia;

			std::cout << "\n\n******************ROTULAS DAS BARRAS******************\n";
			bool rotulaN1, rotulaN2;

			std::cout << "Existe rotula em N1 [1: sim; 0: nao] = ";
			std::cin >> rotulaN1;

			std::cout << "Existe rotula em N2 [1: sim; 0: nao] = ";
			std::cin >> rotulaN2;

			Barra barraAuxiliar = Barra(noAuxiliar[0], noAuxiliar[1], elasticidade, area, inercia, rotulaN1, rotulaN2);
			
			std::cout << "\n\n*************CARREGAMENTO NA BARRA****************\n";
			double fxGlobal, fyGlobal;
			std::cout << "Carregamento distribuido global no eixo X [em N/m] = ";
			std::cin >> fxGlobal;

			std::cout << "Carregamento distribuido global no eixo Y [em N/m] = ";
			std::cin >> fyGlobal;

			barraAuxiliar.setCargaDistribuidaGlobal(fxGlobal, fyGlobal);

			std::cout << "\n\n*************MOMENTOS DE FIM DE BARRA****************\n";
			double momentoFimBarraN1, momentoFimBarraN2;
			std::cout << "Momento no fim da barra [N1] = ";
			std::cin >> momentoFimBarraN1;

			std::cout << "Momento no fim da barra [N2] = ";
			std::cin >> momentoFimBarraN2;

			barraAuxiliar.setMomentoFimBarra(momentoFimBarraN1, momentoFimBarraN2);

			barrasEstrutura.push_back(barraAuxiliar);

			std::cout << "\n\n";
		}

		std::cout << "\n\n";
		std::string nomeArquivo;
		std::cout << "Para finalizar, informe o nome do arquivo que deseja salvar: ";
		std::cin >> nomeArquivo;
		
		criarArquivo(nomeArquivo, nosEstrutura, barrasEstrutura);

}

/*Esse método irá analisar os dados brutos obtidos através do console ou da interface gráfica do programa e filtrá-los
  de maneira a tornar a implementação do MEF mais simples. */
void GeradorArquivo::criarArquivo(std::string nomeArquivo, std::vector<Node> nosEstrutura, std::vector<Barra> barrasEstrutura) {

	//O primeiro passo é criar o arquivo propriamente dito. Para isso, utiliza-se a classe ofstream.

	try {

		//**************************CRIAR O ARQUIVO**************************
		//Criar o endereço para o arquivo, no caso é na pasta "Arquivos"
		std::string path = "Arquivos/DadosEntrada/" + nomeArquivo + ".txt";

		//Criar o arquivo propriamente dito
		std::ofstream arquivo(path);

		//Se der algum erro na inicialização/abertura do arquivo, emitir um ERRO
		if (!arquivo.is_open()) {
			throw Erro(501);
		}

		//**************************GRAVAR OS DADOS NO ARQUIVO**************************

		//As duas primeiras linhas serão referentes ao número de nós e ao número de barras da estrutura
		arquivo << nosEstrutura.size() << std::endl;
		arquivo << barrasEstrutura.size() << std::endl;

		//Logo após, adiciona-se os dados dos nós da estrutura
		for (int i = 0; i < nosEstrutura.size(); i++){
			arquivo << nosEstrutura[i].getId() << std::endl;
			arquivo << nosEstrutura[i].pos.getX() << std::endl;
			arquivo << nosEstrutura[i].pos.getY() << std::endl;
			arquivo << nosEstrutura[i].getFx() << std::endl;
			arquivo << nosEstrutura[i].getFy() << std::endl;
			arquivo << nosEstrutura[i].getMz() << std::endl;
			arquivo << nosEstrutura[i].getRh() << std::endl;
			arquivo << nosEstrutura[i].getRv() << std::endl;
			arquivo << nosEstrutura[i].getRz() << std::endl; 
		}

		//Logo após, adiciona-se os dados das barras da estrutura
		for (int i = 0; i < barrasEstrutura.size(); i++) {
			arquivo << barrasEstrutura[i].n1.getId() << std::endl;
			arquivo << barrasEstrutura[i].n2.getId() << std::endl;
			arquivo << barrasEstrutura[i].getElasticidade() << std::endl;
			arquivo << barrasEstrutura[i].getArea() << std::endl;
			arquivo << barrasEstrutura[i].getInercia() << std::endl;
			arquivo << barrasEstrutura[i].getFxGlobal() << std::endl;
			arquivo << barrasEstrutura[i].getFyGlobal() << std::endl;
			arquivo << barrasEstrutura[i].getRotulaN1() << std::endl;
			arquivo << barrasEstrutura[i].getRotulaN2() << std::endl;
			arquivo << barrasEstrutura[i].getMomentoFimBarraN1() << std::endl;
			arquivo << barrasEstrutura[i].getMomentoFimBarraN2() << std::endl;
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}


