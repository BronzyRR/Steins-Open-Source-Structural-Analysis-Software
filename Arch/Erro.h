#pragma once
#include <string>


//O objeto dessa classe é, simplesmente, armazenar todas as mensagens possíveis de erro
//Os valores que começam com 1 são referentes a erros na classe de matriz
class Erro
{
private:
	std::string mensagem;
	void setMensagem(std::string mensagem); //definir a mensagem do erro

public:
	Erro(int codigo); 
	std::string texto(); //método que vai retornar a mensagem do erro

};

