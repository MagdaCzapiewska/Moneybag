#include "moneybag.h"
#include <iostream>
#include <stdexcept>
#include <compare>
#include <cassert>
// Metody klasy Moneybag.

constexpr Moneybag::Moneybag(coin_number_t ll, coin_number_t ss, coin_number_t dd) : l(ll), s(ss), d(dd) {}

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

void Moneybag::change_livre_number(uint64_t new_value) {
    this->l = new_value;
}
void Moneybag::change_solidus_number(uint64_t new_value) {
    this->s = new_value;
}
void Moneybag::change_denier_number(uint64_t new_value) {
    this->d = new_value;
}

Moneybag& Moneybag::operator+=(const Moneybag &rhs) {

    unsigned long long result_l = 0;
    unsigned long long result_s = 0;
    unsigned long long result_d = 0;

    if (__builtin_uaddll_overflow (this->livre_number(), rhs.livre_number(), &result_l)
    || __builtin_uaddll_overflow (this->solidus_number(), rhs.solidus_number(), &result_s)
    || __builtin_uaddll_overflow (this->denier_number(), rhs.denier_number(), &result_d)) {
        throw std::out_of_range("Result out of range\n");
    }
    else {
        this->change_livre_number(result_l);
        this->change_solidus_number(result_s);
        this->change_denier_number(result_d);
    }

    return *this;
}

Moneybag& Moneybag::operator-=(const Moneybag &rhs) {
    if (this->livre_number() < rhs.livre_number()
    || this->solidus_number() < rhs.solidus_number()
    || this->denier_number() < rhs.denier_number()) {
        throw std::out_of_range("Result out of range\n");
    }
    else {
        this->change_livre_number(this->livre_number() - rhs.livre_number());
        this->change_solidus_number(this->solidus_number() - rhs.solidus_number());
        this->change_denier_number(this->denier_number() - rhs.denier_number());
    }
    return *this;
}

Moneybag& Moneybag::operator*=(const uint64_t rhs) {
    unsigned long long result_l = 0;
    unsigned long long result_s = 0;
    unsigned long long result_d = 0;

    if (__builtin_umulll_overflow (this->livre_number(), rhs, &result_l)
        || __builtin_umulll_overflow (this->solidus_number(), rhs, &result_s)
        || __builtin_umulll_overflow (this->denier_number(), rhs, &result_d)) {
        throw std::out_of_range("Result out of range\n");
    }
    else {
        this->change_livre_number(result_l);
        this->change_solidus_number(result_s);
        this->change_denier_number(result_d);
    }

    return *this;
}

const Moneybag Moneybag::operator+(const Moneybag &rhs) const {
    Moneybag result = *this;
    result += rhs;
    return result;
}

const Moneybag Moneybag::operator-(const Moneybag &rhs) const {
    Moneybag result = *this;
    result -= rhs;
    return result;
}

const Moneybag Moneybag::operator*(uint64_t rhs) const {
    Moneybag result = *this;
    result *= rhs;
    return result;
}

bool Moneybag::operator==(const Moneybag &rhs) const {
    if (this->livre_number() != rhs.livre_number()
        || this->solidus_number() != rhs.solidus_number()
        || this->denier_number() != rhs.denier_number()) {
        return false;
    }
    else {
        return true;
    }
}

bool Moneybag::operator!=(const Moneybag &rhs) const {
    return !(this->operator==(rhs));
}


bool Moneybag::operator<(const Moneybag &rhs) const {
    if (this->livre_number() < rhs.livre_number()
    && this->solidus_number() < rhs.solidus_number()
    && this->denier_number() < rhs.denier_number()) {
        return true;
    }
    else {
        return false;
    }
}

bool Moneybag::operator<=(const Moneybag &rhs) const {
    if (this->livre_number() <= rhs.livre_number()
        && this->solidus_number() <= rhs.solidus_number()
        && this->denier_number() <= rhs.denier_number()) {
        return true;
    }
    else {
        return false;
    }
}

bool Moneybag::operator>(const Moneybag &rhs) const {
    if (this->livre_number() > rhs.livre_number()
        && this->solidus_number() > rhs.solidus_number()
        && this->denier_number() > rhs.denier_number()) {
        return true;
    }
    else {
        return false;
    }
}

bool Moneybag::operator>=(const Moneybag &rhs) const {
    if (this->livre_number() >= rhs.livre_number()
        && this->solidus_number() >= rhs.solidus_number()
        && this->denier_number() >= rhs.denier_number()) {
        return true;
    }
    else {
        return false;
    }
}

std::partial_ordering Moneybag::operator<=>(const Moneybag &rhs) {
    if (*this < rhs) {
        return std::partial_ordering::less;
    }
    else if (*this > rhs) {
        return std::partial_ordering::greater;
    }
    else if (*this == rhs) {
        return std::partial_ordering::equivalent;
    }
    else {
        return std::partial_ordering::unordered;
    }
}

constinit Moneybag Livre = Moneybag(1, 0, 0);
constinit Moneybag Solidus = Moneybag(0, 1, 0);
constinit Moneybag Denier = Moneybag(0, 0, 1);

int main() {
    Moneybag m1 = Moneybag(1, 10, 19);
    Moneybag m2 = Moneybag(0, 2, 17);
    std::cout << m1;
    //m1.operator<<(std::cout);
    Moneybag m3(0, 0, 0);
    std::cout << m3;
    Moneybag m4(m1);
    std::cout << m1;
    std::cout << m4;

    Moneybag::coin_number_t s = m2.solidus_number();
    assert(s == 2);

    assert(m1);
    assert(!m3);
    Moneybag m5 = m1 + m2;
    std::cout << m5;
    //assert(m1 >= m2);
    //assert(m1 > m2);
    //assert(!(m1 < m2));
    assert(m4 == m3);

    //assert(Moneybag(2, 2, 1) >= Moneybag(2, 1, 1));
    //assert(Moneybag(2, 2, 1) > Moneybag(2, 1, 1));
    //assert(!(Moneybag(1, 2, 2) <= Moneybag(2, 2, 1)));
    //assert(!(Moneybag(1, 2, 2) < Moneybag(2, 2, 1)));

    return 0;
}