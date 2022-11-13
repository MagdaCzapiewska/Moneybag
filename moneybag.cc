#include "moneybag.h"
#include <iostream>

// Metody klasy Moneybag.

Moneybag::Moneybag(coin_number_t ll, coin_number_t ss, coin_number_t dd) : l(ll), s(ss), d(dd) {}

Moneybag::Moneybag(const Moneybag& moneybag) {
    std::cout << moneybag.livre_number() << " " << moneybag.solidus_number() << " " << moneybag.denier_number() << "\n";
    //Moneybag(moneybag.livre_number(), moneybag.solidus_number(), moneybag.denier_number());
    l = moneybag.livre_number();
    s = moneybag.solidus_number();
    d = moneybag.denier_number();
}

Moneybag::coin_number_t Moneybag::livre_number() const {
    return this->l;
}

Moneybag::coin_number_t Moneybag::solidus_number() const {
    return this->s;
}

Moneybag::coin_number_t Moneybag::denier_number() const {
    return this->d;
}

std::ostream& operator<< (std::ostream &strm, const Moneybag& rhs) {

    strm << "(" << rhs.livre_number() << (rhs.livre_number() == 1 ? " livre, " : " livres, ") <<
    rhs.solidus_number() << (rhs.solidus_number() == 1 ? " solidus, " : " soliduses, ") <<
    rhs.denier_number() << (rhs.denier_number() == 1 ? " denier" : " deniers") << ")\n";

    return strm;
}

Moneybag::operator bool() const {
    if ((this->l == 0) && (this->s == 0) && (this->d == 0)) {
        return false;
    }
    return true;
}

int main() {
    Moneybag m1 = Moneybag(1, 10, 19);
    std::cout << m1;
    //m1.operator<<(std::cout);
    Moneybag m3(0, 0, 0);
    std::cout << m3;
    Moneybag m4(m1);
    std::cout << m1;
    std::cout << m4;

    return 0;
}