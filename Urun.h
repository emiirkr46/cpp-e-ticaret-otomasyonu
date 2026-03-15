#ifndef URUN_H
#define URUN_H

#include <string>
#include <iostream>

using namespace std;

// Urunun ortak yerlerini buraya topladim.
// Kategoriler bu siniftan tureyecek.
// Bu sinif, urunler icin bir temel (base class) gorevi gorur.
class Urun {
protected:
    int mId;
    string mAd;
    string mKategoriKodu;
    double mBirimFiyat;
    int mStok;

public:
    // Kurucu (Constructor)
    Urun(int id, const string& ad, const string& kat, double fiyat, int stok)
        : mId(id), mAd(ad), mKategoriKodu(kat), mBirimFiyat(fiyat), mStok(stok) {}

    // Sanal Yikici (Virtual Destructor) - Kalitimin (Inheritance) dogru calismasi icin
    virtual ~Urun() {}

    // Getter Metotlari
    int getId() const { return mId; }
    string getAd() const { return mAd; }
    string getKategoriKodu() const { return mKategoriKodu; }
    double getBirimFiyat() const { return mBirimFiyat; }
    int getStok() const { return mStok; }

    // Stok islemleri
    void stokAzalt(int adet) { mStok -= adet; }
    void stokArttir(int adet) { mStok += adet; }

    // Kategoriye gore satis fiyati degisebilsin diye virtual yaptim.
    // Saf Sanal Fonksiyon (Pure Virtual Function) - Urun sinifini soyut (abstract) yapar.
    virtual double satisFiyati() const = 0;

    // Ekrana yazdirmayi da her sinif kendi yapsin (Polimorfizm)
    // Saf Sanal Fonksiyon (Pure Virtual Function)
    virtual void yazdir() const = 0;
};

#endif