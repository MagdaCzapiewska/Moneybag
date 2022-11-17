#ifndef __MONEYBAG_H__
#define __MONEYBAG_H__

#include <initializer_list>
#include <cstdint>
#include <sstream>
#include <compare>

constexpr uint64_t denier_denier = 1;
constexpr uint64_t solid_denier = 12;
constexpr uint64_t livre_denier = 240;

class Moneybag {

private:

    uint64_t l;
    uint64_t s;
    uint64_t d;

    void change_livre_number(uint64_t new_value);
    void change_solidus_number(uint64_t new_value);
    void change_denier_number(uint64_t new_value);

public:
    using coin_number_t = uint64_t;

    //tworzenie sakiewki na podstawie liczby poszczególnych monet, np.
    //Moneybag(1, 2, 3) powinno stworzyć sakiewkę, w której znajdują się 1 liwr,
    //2 solidy i 3 denary; nie powinno być natomiast możliwości utworzenia
    //obiektu bez podania liczby monet;

    constexpr Moneybag(coin_number_t dd, coin_number_t ss, coin_number_t ll);

    Moneybag(const Moneybag& moneybag);

    Moneybag& operator=(const Moneybag &rhs);

    //tworzenie sakiewki przez skopiowanie innej sakiewki;

    // Odczytanie liczby poszczególnych monet za pomocą odpowiednio metod
    //livre_number(), solidus_number() i denier_number();
    coin_number_t livre_number() const;
    coin_number_t solidus_number() const;
    coin_number_t denier_number() const;


    // Wykonywanie operacji dodawania, odejmowania zawartości sakiewek oraz
    //mnożenia zawartości sakiewki przez liczbę całkowitą nieujemną;

    // +
    const Moneybag operator+(const Moneybag &rhs) const;

    // -
    const Moneybag operator-(const Moneybag &rhs) const;

    // *
    const Moneybag operator*(uint64_t rhs) const;

    // +=
    Moneybag& operator+=(const Moneybag &rhs);

    // -=
    Moneybag& operator-=(const Moneybag &rhs);

    // *=
    Moneybag& operator*=(uint64_t rhs);

    // ==
    bool operator==(const Moneybag &rhs) const;

    // !=
    bool operator!=(const Moneybag &rhs) const;

    // <
    bool operator<(const Moneybag &rhs) const;

    // <=
    bool operator<=(const Moneybag &rhs) const;

    // >
    bool operator>(const Moneybag &rhs) const;

    // >=
    bool operator>=(const Moneybag &rhs) const;

    // <=>
    std::partial_ordering operator<=>(const Moneybag &rhs);

    // Wysłanie na strumień wyjściowy napisu reprezentującego zawartość sakiewki;
    //std::ostream& operator<<(std::ostream &strm);

    //porównywanie zawartości sakiewek – na sakiewkach zdefiniowany jest
    //naturalny porządek częściowy;

    // Rzutowanie sakiewki na typ bool, informujące, czy sakiewka jest niepusta
    //(zawiera choć jedną monetę).
    operator bool() const;
};

// *
const Moneybag operator*(const int lhs, const Moneybag &rhs);

class Value {

private:

    __int128 val;

    //utworzenie wartości na podstawie sakiewki lub liczby całkowitej
    //nieujemnej;
public:
    Value(const Moneybag& moneybag);

    Value(Moneybag::coin_number_t val);

    Value();

    Value(const Value& value);

    Value& operator=(const Value &rhs);

    __int128 get_value() const;

    //kopiowanie wartości;

    //porównywanie wartości – na wartościach zdefiniowany jest naturalny
    //porządek liniowy;

    // ==
    bool operator==(const Value &rhs) const;

    // !=
    bool operator!=(const Value &rhs) const;

    // <
    bool operator<(const Value &rhs) const;

    // <=
    bool operator<=(const Value &rhs) const;

    // >
    bool operator>(const Value &rhs) const;

    // >=
    bool operator>=(const Value &rhs) const;

    // <=>
    std::strong_ordering operator<=>(const Value &rhs);

    //porównywanie wartości z liczbami całkowitymi nieujemnymi;

    //rzutowanie wartości na obiekt klasy string reprezentujący wartość
    //w zapisie dziesiętnym.
    operator std::string() const;
};

#endif // __MONEYBAG_H__
