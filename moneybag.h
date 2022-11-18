#ifndef __MONEYBAG_H__
#define __MONEYBAG_H__

#include <cstdint>
#include <sstream>
#include <compare>

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

    explicit constexpr Moneybag(coin_number_t ll, coin_number_t ss, coin_number_t dd) : l(ll), s(ss), d(dd) {}

    Moneybag(const Moneybag& moneybag);

    Moneybag& operator=(const Moneybag &rhs);

	constexpr coin_number_t livre_number() const {
		return this->l;
	}

	constexpr coin_number_t solidus_number() const {
		return this->s;
	}

	constexpr coin_number_t denier_number() const {
		return this->d;
	}

    const Moneybag operator+(const Moneybag &rhs) const;

    const Moneybag operator-(const Moneybag &rhs) const;

    const Moneybag operator*(uint64_t rhs) const;

    Moneybag& operator+=(const Moneybag &rhs);

    Moneybag& operator-=(const Moneybag &rhs);

    Moneybag& operator*=(uint64_t rhs);

    bool operator==(const Moneybag &rhs) const;

    std::partial_ordering operator<=>(const Moneybag &rhs);

    explicit operator bool() const;
};

std::ostream& operator<< (std::ostream &strm, const Moneybag& rhs);

const Moneybag operator*(Moneybag::coin_number_t lhs, const Moneybag &rhs);

constinit const Moneybag Livre = Moneybag(1, 0, 0);
constinit const Moneybag Solidus = Moneybag(0, 1, 0);
constinit const Moneybag Denier = Moneybag(0, 0, 1);

class Value {

private:

    __uint128_t val;

public:

    explicit Value(const Moneybag& moneybag);

    explicit Value(Moneybag::coin_number_t val);

    explicit Value();

    explicit Value(const Value& value);

    Value& operator=(const Value &rhs);

    constexpr __uint128_t get_value() const;

    bool operator==(const Value &rhs) const;

    std::strong_ordering operator<=>(const Value &rhs) const;

    bool operator==(const uint64_t rhs) const;

    std::strong_ordering operator<=>(const uint64_t rhs) const;

    explicit operator std::string() const;
};

#endif // __MONEYBAG_H__
