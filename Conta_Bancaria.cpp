#include <iostream> // biblioteca de out e in
#include <random> // importa funções de aletoriedade
#include "Cabecalho_CB.hpp" // importa o cabeçalho (hpp)
#include <fstream>  // permite que trabalhe com arquivos
#include <cstdio> // para usar remove e rename

contaBanco::contaBanco() {
    std::random_device rd; // Cria um objeto chamado rd que gera números aleatórios não determinísticos.
    std::mt19937 gen(rd());  // Cria um gerador de números pseudoaleatórios chamado gen.
    std::uniform_int_distribution<> dist(1, 100000000); // Cria uma distribuição uniforme de inteiros
 	// alocação dinâmica
    id = new int(dist(gen));  // inicia valor aleatório a id
    saldo = new float(0.0);  // inicializa saldo
    
    
}

contaBanco::~contaBanco() {
    // salva conta antes de destruir
    salvarConta();
    // deleta dinamicamente id e saldo
	delete id;
    delete saldo;
    
    
}

void contaBanco::deposito(const float& valor) {
    if (valor < 0){ // verifica se é positivo
		std :: cout <<"numero negativo invalido\n";
	 return;
	}
    *saldo += valor; // adiciona valor
}

void contaBanco::saque(const float& valor) {
    if (valor < 0){ // verifica se é positivo
	 std :: cout << "numero negativo invalido\n";
	 return;
	}
	if(valor > *saldo){ // verifica se o usuário possui esse dinheiro
		std :: cout <<" voce não possui esse dinheiro\n";
		return;
	}
    *saldo -= valor; // remove o valor
}

void contaBanco::nomear() {
    std::cout << "Digite seu nome:\n";
    std::cin >> nome; // escreve o nome
}

void contaBanco::informacoesConta() const { // mostra saidas e endereços
    std::cout << "ID: " << *id << "\n";
    std::cout << "Saldo: " << *saldo << "\n";
    std::cout << "Nome: " << *nome << "\n";
     
     
 	 std::cout << "Endereço ID: " << id << "\n";
    std::cout << "Endereço Saldo: " << saldo << "\n";
    std::cout << "Endereço Nome: " << nome << "\n";
}

void contaBanco::salvarConta() const {
	
	if (idExiste(*id)) { // verifica se o id já existe
        std::cout << "Erro: ID ja existe!\n";
        return;
    }
	
    std::ofstream arquivo("contas.txt", std::ios::app); // Abre (ou cria) o arquivo "contas.txt" para escrita, adicionando novos dados no final sem apagar o conteúdo existente.

    if (!arquivo) { // verifica se o arquivo  abriu corretamente.
        std::cout << "Erro ao abrir arquivo!\n";
        return;
    }

    arquivo << *id << ";" << nome << ";" << *saldo << "\n"; //Aqui você grava os dados no arquivo.

    arquivo.close(); //Fecha o arquivo.

    std::cout << "Conta salva com sucesso!\n";
}

void contaBanco::pesquisarConta(int idBusca) const {
    std::ifstream arquivo("contas.txt");

    if (!arquivo) { // verifica se o arquivo não abriu corretamente.
        std::cout << "Erro ao abrir arquivo!\n";
        return;
    }
	// variáveis temporárias para armazenar os dados de uma linha do arquivo.
    int idArquivo; // guarda o ID lido
    std::string nomeArquivo;// guarda o nome
    float saldoArquivo;//guarda o saldo
    char separador;//guarda o caractere ;

    bool encontrada = false; // booleano para verificação

    while (arquivo >> idArquivo >> separador) { // tenta ler um inteiro  idArquivo e um caractere  separador
        std::getline(arquivo, nomeArquivo, ';'); // Lê tudo até encontrar ; gentline serve para o nome poder ter espaço
        arquivo >> saldoArquivo;//Lê o próximo número da linha

        arquivo.ignore(); // pular quebra de linha

        if (idArquivo == idBusca) {//verifica qual se o id existe
        	//mostra os dados
            std::cout << "Conta encontrada:\n";
            std::cout << "ID: " << idArquivo << "\n";
            std::cout << "Nome: " << nomeArquivo << "\n";
            std::cout << "Saldo: " << saldoArquivo << "\n";
            encontrada = true;
            break;
        }
    }

    if (!encontrada)
        std::cout << "Conta nao encontrada.\n";

    arquivo.close();
}

bool contaBanco::idExiste(int idBusca) const {
	
    std::ifstream arquivo("contas.txt"); // le os dados do arquivo

    if (!arquivo) {
        return false; // se não existe arquivo, não existe ID
    }
	// variáveis temporárias para armazenar os dados de uma linha do arquivo.
    int idArquivo; // guarda o ID lido
    std::string nomeArquivo; // guarda o nome
    float saldoArquivo; //guarda o saldo
    char separador; //guarda o caractere ;

    while (arquivo >> idArquivo >> separador) { // tenta ler um inteiro  idArquivo e um caractere  separador
        std::getline(arquivo, nomeArquivo, ';'); // Lê tudo até encontrar ; gentline serve para o nome poder ter espaço
        arquivo >> saldoArquivo; //Lê o próximo número da linha
        arquivo.ignore(); //Isso ignora o caractere de quebra de linha \n.

        if (idArquivo == idBusca) { // verifica se o ID lido for igual ao ID que o usuário quer buscar
            arquivo.close();
            return true;
        }
    }

    arquivo.close();
    return false;
}


void contaBanco::apagarConta(int idBusca) {

    // Abre o arquivo original para leitura
    std::ifstream arquivo("contas.txt");

    // Verifica se conseguiu abrir
    if (!arquivo) {
        std::cout << "Erro ao abrir arquivo!\n";
        return;
    }

    // Cria um arquivo temporário para reescrever os dados
    std::ofstream temp("temp.txt");

    // Variáveis auxiliares para armazenar dados lidos
    int idArquivo;
    std::string nomeArquivo;
    float saldoArquivo;
    char separador;

    bool encontrada = false; // controla se encontrou o ID

    // Loop que percorre todas as contas do arquivo
    while (arquivo >> idArquivo >> separador) {

        // Lê o nome até encontrar ';'
        std::getline(arquivo, nomeArquivo, ';');

        // Lê o saldo
        arquivo >> saldoArquivo;

        // Ignora a quebra de linha
        arquivo.ignore();

        // Se o ID for diferente do que queremos apagar
        if (idArquivo != idBusca) {

            // Copia a linha para o arquivo temporário
            temp << idArquivo << ";" 
                 << nomeArquivo << ";" 
                 << saldoArquivo << "\n";
        }
        else {
            // Se for o ID procurado, marcamos como encontrado
            encontrada = true;
        }
    }

    // Fecha os dois arquivos
    arquivo.close();
    temp.close();

    // Apaga o arquivo original
    std::remove("contas.txt");

    // Renomeia o temporário para o nome original
    std::rename("temp.txt", "contas.txt");

    // Mensagem final
    if (encontrada)
        std::cout << "Conta apagada com sucesso!\n";
    else
        std::cout << "ID nao encontrado.\n";
}



int main()
{
	contaBanco cb; //chama o construtor
	int valor; // cria valor e lhe da referência
	int&  v = valor;
	while(true)
	{	
		int opcao;// cria valor e lhe da referência
		int&  z = opcao;
		std :: cout <<"____Menu___\n";
		std :: cout <<"1-nomear\n" << "2-deposito\n" << "3-saque\n"<<"4-Informações da conta\n"<< "5-pesquisar\n" << "6-deletar conta\n" << "7-sair\n";
		std :: cin >> z; //menu de escolhas
		
		switch(z) // condicional switch case
		{
		case 1:
			cb.nomear(); // chama nomear
			break;
		case 2:
			std :: cout <<"Digite seu valor\n";
			std :: cin >> v;
			cb.deposito(v); // chama depósito
			break;
		case 3:
			std :: cout <<"Digite seu valor\n";
			std :: cin >> v; // chama saque
			cb.saque(v);
			break;
		case 4:
			cb.informacoesConta(); // chama as informações da conta
			break;
		case 5:
			int busca;
    		std::cout << "Digite o ID para buscar: ";
    		std::cin >> busca;
    		cb.pesquisarConta(busca); // chama a pesquisa
    		break;
    	case 6:
    		int busca2;
    		std::cout << "Digite o ID para buscar: ";
    		std::cin >> busca2;
    		cb.apagarConta(busca); // chama função
    		break;
		case 7:
    		return 0; // finaliza
        	break;
		default:
			
			break;
			return 0;
		}
		
		
		
		
		
		
		
	}
	return 0;
}
	
	


