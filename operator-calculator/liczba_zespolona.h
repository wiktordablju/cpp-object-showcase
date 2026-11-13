#ifndef LICZBA_ZESPOLONA_H
#define LICZBA_ZESPOLONA_H

#include <iostream>

class LiczbaZespolona {

private:
    double im, re;
    static int licznik;

public:
    void setRe(double rea) { re = rea; }
    double getRe() const { return re; }
    void setIm(double ima) { im = ima; }
    double getIm() const { return im; }


    LiczbaZespolona() : re(0), im(0) {
        ++licznik;
    }

    LiczbaZespolona(double rea) : re(rea), im(0) {
        ++licznik;
    }

    LiczbaZespolona(double rea, double ima) : re(rea), im(ima) {
        ++licznik;
    }

    LiczbaZespolona(const LiczbaZespolona& lz) : re(lz.re), im(lz.im) {
        ++licznik;    
    }

    ~LiczbaZespolona() {
        --licznik;
    }
    
    LiczbaZespolona& operator+=(const LiczbaZespolona& lz) {
        re += lz.re;
        im += lz.im;
        return *this;
    }

    LiczbaZespolona operator+(const LiczbaZespolona &lz) const;

    LiczbaZespolona operator-(const LiczbaZespolona &lz) const;

    double& operator[](int indeks) {
        if (indeks == 0) return im;
        else if (indeks == 1) return re;
        else {
            std::cout << "Indeks poza zakresem ";
            return re;  
        }
    }

     bool operator!=(const LiczbaZespolona& lz) const {
        return (re != lz.re) || (im != lz.im);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const LiczbaZespolona& lz);
    friend std::istream& operator>>(std::istream& is, LiczbaZespolona& lz);

     LiczbaZespolona& operator=(const LiczbaZespolona& lz) {
        std::cout << "Wywołano operator przypisania" << std::endl;
        if (this != &lz) {
            re = lz.re;
            im = lz.im;
        }
        return *this;
    }

    bool operator==(const LiczbaZespolona& lz) const {
        return (re == lz.re) && (im == lz.im);
    }

    LiczbaZespolona& operator++() {
        ++re;
        return *this;
    }

    LiczbaZespolona& operator+=(double f) {
        re += f;
        return *this;
    }


    void operator()(double rea, double ima) {
        re = rea;
        im = ima;
    }
};
    // LiczbaZespolona operator+(const LiczbaZespolona& lz1, const LiczbaZespolona& lz2) {
    //     return LiczbaZespolona(lz1.getRe() + lz2.getRe(), lz1.getIm() + lz2.getIm());
    // }
    inline LiczbaZespolona LiczbaZespolona::operator+(const LiczbaZespolona &lz) const {
    return LiczbaZespolona(re + lz.re, im + lz.im);
    }

    inline LiczbaZespolona LiczbaZespolona::operator-(const LiczbaZespolona &lz) const {
    return LiczbaZespolona(re - lz.re, im - lz.im);
    }

    inline std::ostream& operator<<(std::ostream& os, const LiczbaZespolona& lz) {
    os << "(" << lz.re << ", " << lz.im << "i)";
    return os;
    }

    inline std::istream& operator>>(std::istream& is, LiczbaZespolona& lz) {
    double re, im;
    if (is >> re >> im) {
        lz.setRe(re);
        lz.setIm(im);
    }
    return is;
}
#endif // LICZBA_ZESPOLONA_H
