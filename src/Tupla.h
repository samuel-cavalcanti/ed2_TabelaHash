//
// Created by samuel on 4/22/21.
//

#ifndef ED2_TABELAHASH_TUPLA_H
#define ED2_TABELAHASH_TUPLA_H

template<typename K, typename V>
class Tupla {
private:

public:
    Tupla(K c, V v) {
        chave = c;
        valor = v;
    }

    K chave;
    V valor;


};


#endif //ED2_TABELAHASH_TUPLA_H
