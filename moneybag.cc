#include "moneybag.h"
#include <iostream>
#include <stdexcept>
#include <compare>
#include <cassert>

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

constexpr __uint128_t Value::get_value() const {
    return this->val;
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

std::ostream& operator<< (std::ostream &strm, const Moneybag& rhs) {
    strm << "(" << rhs.livre_number() << (rhs.livre_number() == 1 ? " livr, " : " livres, ") <<
    rhs.solidus_number() << (rhs.solidus_number() == 1 ? " solidus, " : " soliduses, ") <<
    rhs.denier_number() << (rhs.denier_number() == 1 ? " denier" : " deniers") << ")";

    return strm;
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

const Moneybag operator*(Moneybag::coin_number_t lhs, const Moneybag &rhs) {
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

bool Value::operator==(const uint64_t rhs) const {
    return (this->val == rhs);
}

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
