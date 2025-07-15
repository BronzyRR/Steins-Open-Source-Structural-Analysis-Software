#pragma once
#include <string>


//O objeto dessa classe �, simplesmente, armazenar todas as mensagens poss�veis de erro
//Os valores que come�am com 1 s�o referentes a erros na classe de matriz
class Erro
{
private:
	std::string mensagem;
	void setMensagem(std::string mensagem); //definir a mensagem do erro

public:
	Erro(int codigo); 
	std::string texto(); //m�todo que vai retornar a mensagem do erro

};

