#ifndef __MONEYBAG_H__
#define __MONEYBAG_H__

#include <initializer_list>
#include <cstdint>
#include <sstream>

constexpr uint64_t denier_denier = 1;
constexpr uint64_t solid_denier = 12;
constexpr uint64_t livre_denier = 240;

class Denier {
public:
    Denier();
};

class Livre {

public:
    Livre();
};

class Solidus {

public:
    Solidus();
};

class Moneybag {

private:
    //constinit static Livre l;
    //constinit static Solidus s;
    //constinit static Denier d;

    uint64_t l;
    uint64_t s;
    uint64_t d;

public:
    using coin_number_t = uint64_t;

    //tworzenie sakiewki na podstawie liczby poszczególnych monet, np.
    //Moneybag(1, 2, 3) powinno stworzyć sakiewkę, w której znajdują się 1 liwr,
    //2 solidy i 3 denary; nie powinno być natomiast możliwości utworzenia
    //obiektu bez podania liczby monet;

    Moneybag(coin_number_t dd, coin_number_t ss, coin_number_t ll);

    Moneybag(const Moneybag& moneybag);

    //tworzenie sakiewki przez skopiowanie innej sakiewki;

    // Odczytanie liczby poszczególnych monet za pomocą odpowiednio metod
    //livre_number(), solidus_number() i denier_number();
    coin_number_t livre_number() const;
    coin_number_t solidus_number() const;
    coin_number_t denier_number() const;


    // Wykonywanie operacji dodawania, odejmowania zawartości sakiewek oraz
    //mnożenia zawartości sakiewki przez liczbę całkowitą nieujemną;

    // Wysłanie na strumień wyjściowy napisu reprezentującego zawartość sakiewki;
    //std::ostream& operator<<(std::ostream &strm);

    //porównywanie zawartości sakiewek – na sakiewkach zdefiniowany jest
    //naturalny porządek częściowy;

    // Rzutowanie sakiewki na typ bool, informujące, czy sakiewka jest niepusta
    //(zawiera choć jedną monetę).
    operator bool() const;
};

class Value {

    //utworzenie wartości na podstawie sakiewki lub liczby całkowitej
    //nieujemnej;

    //kopiowanie wartości;

    //porównywanie wartości – na wartościach zdefiniowany jest naturalny
    //porządek liniowy;

    //porównywanie wartości z liczbami całkowitymi nieujemnymi;

    //rzutowanie wartości na obiekt klasy string reprezentujący wartość
    //w zapisie dziesiętnym.
};

#endif // __MONEYBAG_H__
