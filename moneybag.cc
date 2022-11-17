#include "moneybag.h"
#include <iostream>
#include <stdexcept>
#include <compare>
#include <cassert>
// Metody klasy Moneybag.

constexpr Moneybag::Moneybag(coin_number_t ll, coin_number_t ss, coin_number_t dd) : l(ll), s(ss), d(dd) {}

Moneybag::Moneybag(const Moneybag& moneybag) {
    l = moneybag.livre_number();
    s = moneybag.solidus_number();
    d = moneybag.denier_number();
}

Value::Value(const Moneybag& moneybag) {
    __uint128_t result = 0;
    result += ((__uint128_t)240 * moneybag.livre_number());
    result += ((__uint128_t)12 * moneybag.solidus_number());
    result += moneybag.denier_number();

    this->val = result;
}

Value::Value(Moneybag::coin_number_t val) {
    this->val = (__uint128_t)val;
}

Value::Value(const Value& value) {
    val = value.val;
}

Value::Value() {
    val = 0;
}

Moneybag& Moneybag::operator=(const Moneybag &rhs) {
    if (this == &rhs) {
        return *this;
    }

    l = rhs.livre_number();
    s = rhs.solidus_number();
    d = rhs.denier_number();

    return *this;
}

Value& Value::operator=(const Value &rhs) {
    val = rhs.val;
    return *this;
}

constexpr Moneybag::coin_number_t Moneybag::livre_number() const {
    return this->l;
}

constexpr Moneybag::coin_number_t Moneybag::solidus_number() const {
    return this->s;
}

constexpr Moneybag::coin_number_t Moneybag::denier_number() const {
    return this->d;
}

constexpr __uint128_t Value::get_value() const {
    return this->val;
}

std::ostream& operator<< (std::ostream &strm, const Moneybag& rhs) {

    strm << "(" << rhs.livre_number() << (rhs.livre_number() == 1 ? " livre, " : " livres, ") <<
    rhs.solidus_number() << (rhs.solidus_number() == 1 ? " solidus, " : " soliduses, ") <<
    rhs.denier_number() << (rhs.denier_number() == 1 ? " denier" : " deniers") << ")";

    return strm;
}

Moneybag::operator bool() const {
    if ((this->l == 0) && (this->s == 0) && (this->d == 0)) {
        return false;
    }
    return true;
}

Value::operator std::string() const {
    std::string result;
    __int128 help = this->val;

    while(help) {
        result += (char)('0' + (help % 10));
        help /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
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

const Moneybag Moneybag::operator*(coin_number_t rhs) const {
    Moneybag result = *this;
    result *= rhs;
    return result;
}

const Moneybag operator*(const int lhs, const Moneybag &rhs) {
    Moneybag result = rhs;
    result *= lhs;
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

std::partial_ordering Moneybag::operator<=>(const Moneybag &rhs) {
    if (this->livre_number() == rhs.livre_number()
             && this->solidus_number() == rhs.solidus_number()
             && this->denier_number() == rhs.denier_number()) {
        return std::partial_ordering::equivalent;
    }
    else if (this->livre_number() <= rhs.livre_number()
        && this->solidus_number() <= rhs.solidus_number()
        && this->denier_number() <= rhs.denier_number()) {
        return std::partial_ordering::less;
    }
    else if (this->livre_number() >= rhs.livre_number()
             && this->solidus_number() >= rhs.solidus_number()
             && this->denier_number() >= rhs.denier_number()) {
        return std::partial_ordering::greater;
    }
    else {
        return std::partial_ordering::unordered;
    }
}

bool Value::operator==(const Value &rhs) const {
    return (this->val == rhs.get_value());
}

std::strong_ordering Value::operator<=>(const Value &rhs) const {
    if (this->get_value() < rhs.get_value()) {
        return std::strong_ordering::less;
    }
    else if (this->get_value() > rhs.get_value()) {
        return std::strong_ordering::greater;
    }
    else {
        return std::strong_ordering::equal;
    }
}

// ==
bool Value::operator==(const uint64_t rhs) const {
    return (this->val == rhs);
}

// <=>
std::strong_ordering Value::operator<=>(const uint64_t rhs) const {
    if (this->get_value() < rhs) {
        return std::strong_ordering::less;
    }
    else if (this->get_value() > rhs) {
        return std::strong_ordering::greater;
    }
    else {
        return std::strong_ordering::equal;
    }
}

constinit const Moneybag Livre = Moneybag(1, 0, 0);
constinit const Moneybag Solidus = Moneybag(0, 1, 0);
constinit const Moneybag Denier = Moneybag(0, 0, 1);

int main() {
    // Taka konstrukcja nie powinna się kompilować.
    // Moneybag m0;

    Moneybag m1 = Moneybag(1, 10, 19);
    Moneybag m2 = 2 * Solidus + 17 * Denier;
    Moneybag m3(0, 0, 0);
    Moneybag m4(m1);
    m4 = m3;

    std::cout << m3 << std::endl;
    std::cout << m4 + m2 - Solidus << std::endl;

    Moneybag::coin_number_t s = m2.solidus_number();
    assert(s == 2);

    assert(m1);
    assert(!m3);
    assert(m1 >= m2);
    assert(m1 > m2);
    assert(!(m1 < m2));
    assert(m4 == m3);

    assert(Moneybag(2, 2, 1) >= Moneybag(2, 1, 1));
    assert(Moneybag(2, 2, 1) > Moneybag(2, 1, 1));
    assert(!(Moneybag(1, 2, 2) <= Moneybag(2, 2, 1)));
    assert(!(Moneybag(1, 2, 2) < Moneybag(2, 2, 1)));

    m2 += 28 * Solidus + 2 * Denier;

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    assert(!(m1 == m2));
    assert(!(m1 > m2));
    assert(!(m1 < m2));

    //Moneybag nowa = 18000000000000 * Solidus + 17 * Denier;
    //std::cout << nowa;

    Value v1 = Value(m1);
    Value v2(m2);

    std::cout << static_cast<std::string>(v1) << std::endl;
    std::cout << std::string(Value(Livre)) << std::endl;

    assert(v1 == v2);
    assert(!is_neq(v1 <=> v2));
    assert(v1 == 379);
    assert(379 == v2);
    assert(v1 > 350);
    assert(350 < v2);
    assert(0 == Value());

    // Te konstrukcje nie powinny się kompilować.
    //Livre = Denier;
    //Denier = Solidus;
    //Solidus = Livre;
    //int k = Moneybag(1, 2, 3);
    //std::cout << k << "\n";

    return 0;
}