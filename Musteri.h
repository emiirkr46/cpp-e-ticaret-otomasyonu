#ifndef MUSTERI_H
#define MUSTERI_H

#include <string>
#include <iostream>

using namespace std;

// enum kullanma dedigin icin sabit yaptim
// Musteri tipleri icin sabitler
#define TIP_STANDART 1
#define TIP_PREMIUM  2
#define TIP_KURUMSAL 3

// Soyut (Abstract) Musteri Sinifi
class Musteri {
protected:
    int mNo;
    string mAd;
    string mSoyad;
    string mKullaniciAdi;
    string mSifre;

public:
    // Kurucu (Constructor)
    Musteri(int no, const string& ad, const string& soyad, const string& k, const string& s)
        : mNo(no), mAd(ad), mSoyad(soyad), mKullaniciAdi(k), mSifre(s) {}

    // Sanal Yikici (Virtual Destructor)
    virtual ~Musteri() {}

    string getKullaniciAdi() const { return mKullaniciAdi; }

    // Sifre dogrulama
    int sifreDogruMu(const string& girilen) const {
        if (mSifre == girilen) {
            return 1;
        }
        return 0;
    }

    // Saf Sanal Metotlar - Her alt sinif bu metotlari uygulamak zorunda
    virtual int tip() const = 0;
    virtual double indirimOrani() const = 0;
    virtual double kargoUcreti(double araToplam) const = 0;

    // Temel yazdırma metodu, alt siniflar override edebilir.
    virtual void yazdir() const {
        cout << mAd << " " << mSoyad;
    }
};

// Standart Musteri Tipi
class StandartMusteri : public Musteri {
public:
    StandartMusteri(int no, const string& ad, const string& soyad, const string& k, const string& s)
        : Musteri(no, ad, soyad, k, s) {}

    int tip() const { return TIP_STANDART; }
    double indirimOrani() const { return 0.0; } // %0 indirim
    double kargoUcreti(double) const { return 30.0; } // Sabit 30.0 kargo

    void yazdir() const {
        cout << mAd << " " << mSoyad << " (Standart)";
    }
};

// Premium Musteri Tipi
class PremiumMusteri : public Musteri {
public:
    PremiumMusteri(int no, const string& ad, const string& soyad, const string& k, const string& s)
        : Musteri(no, ad, soyad, k, s) {}

    int tip() const { return TIP_PREMIUM; }
    double indirimOrani() const { return 0.10; } // %10 indirim

    double kargoUcreti(double araToplam) const {
        // kendim 450 yaptim, premium'a kucuk avantaj olsun
        if (araToplam >= 450.0) { // 450 TL ve uzeri ucretsiz kargo
            return 0.0;
        }
        return 30.0;
    }

    void yazdir() const {
        cout << mAd << " " << mSoyad << " (Premium)";
    }
};

// Kurumsal Musteri Tipi
class KurumsalMusteri : public Musteri {
    string mSirketAdi;
    string mVergiNo; // Kurumsal musteriye ozel ek alanlar
public:
    KurumsalMusteri(int no, const string& ad, const string& soyad, const string& k, const string& s,
                    const string& sirket, const string& vergi)
        : Musteri(no, ad, soyad, k, s), mSirketAdi(sirket), mVergiNo(vergi) {}

    int tip() const { return TIP_KURUMSAL; }
    double indirimOrani() const { return 0.15; } // %15 indirim
    double kargoUcreti(double) const { return 0.0; } // Her zaman ucretsiz kargo

    void yazdir() const {
        cout << mAd << " " << mSoyad << " (Kurumsal)"
             << " Sirket: " << mSirketAdi
             << " VergiNo: " << mVergiNo;
    }
};

#endif