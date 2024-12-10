#ifndef CONTATO_HPP
#define CONTATO_HPP

#include <string>

class Contato
{
private:
    std::string nome;
    std::string id;
    std::string endereco;
    std::string payload;

public:
    std::string getNome() const { return nome; }
    std::string getId() const { return id; }
    std::string getEndereco() const { return endereco; }
    std::string getPayload() const { return payload; }

    void setNome(const std::string &nome) { this->nome = nome; }
    void setId(const std::string &id) { this->id = id; }
    void setEndereco(const std::string &endereco) { this->endereco = endereco; }
    void setPayload(const std::string &payload) { this->payload = payload; }

    Contato() = default;
};

#endif