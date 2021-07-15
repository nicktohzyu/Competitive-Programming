//
// Created by nicktohzyu on 2021-06-18.
//
#ifndef CP_FRACTION_H
#define CP_FRACTION_H
#define ll long long
#include <bits/stdc++.h>

using namespace std;

class Fraction {
public:
    ll num, den;

    ll gcd(ll a, ll b) {
        if (a == 0) {
            return b;
        }
        return gcd(b % a, a);
    }

    Fraction* reduce() {
        int d = gcd(num, den);
        num /= d;
        den /= d;
        return this;
    }

    Fraction(ll a, ll b) {
        num = a;
        den = b;
        reduce();
    }

    string str() {
        return to_string(num) + "/" + to_string(den);
    }
};

//Fraction* operator*(Fraction &l, Fraction &r) {
//    return Fraction(
//            l.num * r.num,
//            l.den * r.den
//    ).reduce();
//}

#endif //CP_FRACTION_H
