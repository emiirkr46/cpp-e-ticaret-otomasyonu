#ifndef KATEGORILER_H
#define KATEGORILER_H

#include <string>
#include <iostream>
#include "Urun.h"
using namespace std;

// Burada 5 kategori sinifi yaptim.
// Her birine de en az 3 tane kategoriye ozel alan ekledim.

// Urun: Elektronik Kategorisi
class Elektronik : public Urun {
    string mMarka;
    int mGarantiAy;
    int mGucWatt; // Yeni alanlar
public:
    Elektronik(int id, const string& ad, double fiyat, int stok,
               const string& marka, int garantiAy, int gucWatt)
        : Urun(id, ad, "ELEK", fiyat, stok), // Kategori kodu "ELEK"
          mMarka(marka), mGarantiAy(garantiAy), mGucWatt(gucWatt) {}

    // Elektronige ufak bir artis verdim (%4)
    double satisFiyati() const { return mBirimFiyat * 1.04; }

    void yazdir() const {
        cout << "[" << mId << "] " << mAd << " (Elektronik) "
             << "Satis: " << satisFiyati()
             << " Stok: " << mStok
             << " Marka: " << mMarka
             << " GarantiAy: " << mGarantiAy
             << " Guc: " << mGucWatt << "W";
    }
};

// Urun: Bilgisayar Kategorisi
class Bilgisayar : public Urun {
    string mIslemci;
    int mRamGB;
    int mSsdGB; // Yeni alanlar
public:
    Bilgisayar(int id, const string& ad, double fiyat, int stok,
               const string& islemci, int ramGB, int ssdGB)
        : Urun(id, ad, "PC", fiyat, stok), // Kategori kodu "PC"
          mIslemci(islemci), mRamGB(ramGB), mSsdGB(ssdGB) {}

    // Fiyat artisi %3
    double satisFiyati() const { return mBirimFiyat * 1.03; }

    void yazdir() const {
        cout << "[" << mId << "] " << mAd << " (Bilgisayar) "
             << "Satis: " << satisFiyati()
             << " Stok: " << mStok
             << " CPU: " << mIslemci
             << " RAM: " << mRamGB << "GB"
             << " SSD: " << mSsdGB << "GB";
    }
};

// Urun: Tablet Kategorisi
class Tablet : public Urun {
    double mEkranInch;
    int mKalemVar; // 1/0
    int mPilmAh; // Yeni alanlar
public:
    Tablet(int id, const string& ad, double fiyat, int stok,
           double ekranInch, int kalemVarMi, int pilmAh)
        : Urun(id, ad, "TAB", fiyat, stok), // Kategori kodu "TAB"
          mEkranInch(ekranInch), mKalemVar(kalemVarMi), mPilmAh(pilmAh) {}

    // Fiyat artisi %2
    double satisFiyati() const { return mBirimFiyat * 1.02; }

    void yazdir() const {
        cout << "[" << mId << "] " << mAd << " (Tablet) "
             << "Satis: " << satisFiyati()
             << " Stok: " << mStok
             << " Ekran: " << mEkranInch
             << " Kalem: " << (mKalemVar ? "Var" : "Yok")
             << " Pil: " << mPilmAh;
    }
};

// Urun: Giyim Kategorisi
class Giyim : public Urun {
    string mBeden;
    string mRenk;
    string mKumas; // Yeni alanlar
public:
    Giyim(int id, const string& ad, double fiyat, int stok,
          const string& beden, const string& renk, const string& kumas)
        : Urun(id, ad, "GIY", fiyat, stok), // Kategori kodu "GIY"
          mBeden(beden), mRenk(renk), mKumas(kumas) {}

    // Fiyat artisi %1
    double satisFiyati() const { return mBirimFiyat * 1.01; }

    void yazdir() const {
        cout << "[" << mId << "] " << mAd << " (Giyim) "
             << "Satis: " << satisFiyati()
             << " Stok: " << mStok
             << " Beden: " << mBeden
             << " Renk: " << mRenk
             << " Kumas: " << mKumas;
    }
};

// Urun: Kitap Kategorisi
class Kitap : public Urun {
    string mYazar;
    int mSayfa;
    string mYayinevi; // Yeni alanlar
public:
    Kitap(int id, const string& ad, double fiyat, int stok,
          const string& yazar, int sayfa, const string& yayinevi)
        : Urun(id, ad, "KTP", fiyat, stok), // Kategori kodu "KTP"
          mYazar(yazar), mSayfa(sayfa), mYayinevi(yayinevi) {}

    // Kitapta ekstra artis yapmadim
    double satisFiyati() const { return mBirimFiyat; }

    void yazdir() const {
        cout << "[" << mId << "] " << mAd << " (Kitap) "
             << "Satis: " << satisFiyati()
             << " Stok: " << mStok
             << " Yazar: " << mYazar
             << " Sayfa: " << mSayfa
             << " Yayinevi: " << mYayinevi;
    }
};

#endif