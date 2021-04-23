//
// Created by samuel on 4/22/21.
//

#ifndef ED2_TABELAHASH_TABELAHASH_H
#define ED2_TABELAHASH_TABELAHASH_H


#include <vector>
#include <list>
#include <string>
#include "Tupla.h"


template<typename Chave, typename Valor>
class TabelaHash {

    typedef std::list<Tupla<Chave, Valor> > Bucket;

public:

    /**
    * Inicializar o array de tuplas com capacidade = qtde_buckets.
    * Lembrar de setar todas as posições do array inicializado
    * para NULL.
    **/

    /**
     * Por padrão irei utilizar um fator de carga 0.75 e uma capacidade
     * inicial igual 16 elementos.
     */
    TabelaHash() {
        quantidadeDeElementosInseridos = 0;
        buckets = new std::vector<Bucket *>(8);

    }

    ~TabelaHash() {
        delete buckets;
    }


/**
    * Essa é a função pública que nos permite inserir
    * uma tupla <c,v> na buckets. Nessa função nós
    * verificamos se é preciso aumentar o array de acordo
    * com o load factor. Essa função pode reusar sua versão
    * sobrecarregada para inserir a tupla na buckets.
    * Essa função também incrementa a quantidade de elementos
    * na buckets (variável quantidadeDeElementosInseridos).
    **/

    std::size_t getPos(Chave chave) {
        auto currentSize = buckets->size();

        return std::hash<Chave>{}(chave) % currentSize;
    }

    Bucket *getBucket(Chave chave) {
        auto pos = getPos(chave);
        return buckets->at(pos);
    }

    void inserir(Chave c, Valor v) {

        auto pos = getPos(c);

        if (buckets->at(pos) == nullptr)
            buckets->at(pos) = new Bucket;


        buckets->at(pos)->push_back(Tupla<Chave, Valor>(c, v));

        quantidadeDeElementosInseridos++;
        if (quantidadeDeElementosInseridos == buckets->size())
            resizeBuckets();

    }

    /**
    * Essa função retorna o fator de carga da Tabela Hash.
    **/
    double load_factor() {
        double bucketsSize{buckets->size()};
        double quantidadeDeElementos{this->quantidadeDeElementosInseridos};
        return quantidadeDeElementos / bucketsSize;
    }

    /**
    * Há apenas um valor associado a uma chave.
    * Essa função retorna esse valor, caso a chave exista.
    * Se a chave não existir a função retorna NULL.
    * Lembre-se: em caso de colisão, é preciso navegar
    * no Bucket (lista ligada) para ter certeza se a chave
    * existe ou não.
    **/
    Valor getValor(Chave chave) {


        auto bucket = getBucket(chave);

        if (bucket == nullptr)
            return NULL;

        for (auto &tupla : *bucket)
            if (tupla.chave == chave)
                return tupla.valor;


        return NULL;
    }

    /**
    * Essa função retorna true caso a chave exista,
    * false caso contrário.
    * Lembre-se: em caso de colisão, é preciso navegar
    * no Bucket (lista ligada) para ter certeza se a chave
    * existe ou não.
    **/
    bool contemChave(Chave chave) {
        auto bucket = getBucket(chave);


        if (bucket == nullptr)
            return false;

        for (auto &tupla : *bucket)
            if (tupla.chave == chave)
                return true;


        return false;
    }


    /**
    * Essa função retorna um vetor com todas as chaves
    * já inseridas na buckets.
    **/
    std::vector<Chave> getChaves() {
        std::vector<Chave> chaves;

        for (auto &bucket : *buckets)
            if (bucket != nullptr)
                for (auto &tupla : *bucket)
                    chaves.push_back(tupla.chave);


        return chaves;
    };

    /**
    * Essa função desaloca os nós previamente alocados, e muda
    * o quantidadeDeElementosInseridos do array de tuplas para 8.
    **/
    void clear() {

        delete buckets;

        quantidadeDeElementosInseridos = 0;
        buckets = new std::vector<Bucket *>(8);

    };

    /**
    * Há apenas um nó associado com uma mesma chave.
    * Essa função remove esse nó da buckets, caso a chave exista.
    * Se a chave não existir a função não faz nada.
    * Lembre-se: em caso de colisão, é preciso navegar
    * no Bucket (lista ligada) para ter certeza se a chave
    * existe ou não.
    * Dica: olhar algoritmo de remoção em lista ligada, pois
    * após a remoção de um nó a lista precisa permanecer íntegra,
    * ou seja, navegável.
    **/
    void remover(Chave chave) {

        auto pos = getPos(chave);
        auto bucket = buckets->at(pos);

        if (bucket == nullptr)
            return;

        for (auto it = bucket->begin(); it != bucket->end(); it++) {
            if (it->chave == chave) {
                bucket->remove(*it);
                break;
            }
        }


        quantidadeDeElementosInseridos--;
    }


    /**
    * Essa função retorna a quantidade de pares
    * que já foram inseridos na Tabela Hash.
    **/
    int size() {
        return quantidadeDeElementosInseridos;
    }

    /**
    * Essa função retorna o quantidadeDeElementosInseridos atual do
    * array usado para armazenar a Tabela Hash.
    **/
    int bucket_count() {

        return buckets->size();

    }


    void resizeBuckets() {

        auto currentSize = this->buckets->size();
        auto newSize = currentSize * 8;
        auto newBuckets = new std::vector<Bucket *>(newSize);

        for (auto &bucket: *buckets) {
            if (bucket == nullptr)
                continue;

            for (auto &tupla : *bucket) {
                auto newPos = std::hash<Chave>{}(tupla.chave) % newSize;
                if (newBuckets->at(newPos) == nullptr)
                    newBuckets->at(newPos) = new Bucket;

                newBuckets->at(newPos)->push_back(tupla);
            }
        }

        delete buckets;

        buckets = newBuckets;


    }

private:
    std::vector<Bucket *> *buckets;

    //quantidade de elementos  já inseridos na buckets hash
    std::size_t quantidadeDeElementosInseridos;

};


#endif //ED2_TABELAHASH_TABELAHASH_H
