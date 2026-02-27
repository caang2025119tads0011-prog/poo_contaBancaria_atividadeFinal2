#ifndef CONTA_BANCARIA_HPP // condicional para definir
#define CONTA_BANCARIA_HPP // define

// evita incluir duas vezes ou mais



class contaBanco {// classe
private: // atributos privados
    int* id; // ponteiro de indentificados
    float* saldo; // ponteiro de saldo
    char nome [50]; // array de nome

public:
    contaBanco(); // construtor
    ~contaBanco();  // destrutor

    void deposito(const float& valor); 
    void saque(const float& valor);
    void nomear();
    void informacoesConta() const;
    void salvarConta() const; // salva conta em arquivo txt
    void pesquisarConta(int idBusca) const; // procura no arquivo txt
    bool idExiste(int idBusca) const; // verifica se id já existe no arquivo txt
    void apagarConta(int idBusca); // permite apagar contas salvas no txt
};

#endif