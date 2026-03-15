#ifndef SEPET_H
#define SEPET_H

#include "Urun.h"
#include <iostream>
using namespace std;

// Sepette urun ve adet tutuyorum.
// Stok dusme / geri verme isi de burada donuyor.

#define MAX_SEPET 200

class Sepet {
    Urun* mUrunler[MAX_SEPET]; // Sepetteki urun pointerlari
    int mAdetler[MAX_SEPET];   // Karsilik gelen adetler
    int mSayi;                 // Sepetteki urun cesidi sayisi

    // Verilen urun ID'sinin sepetteki indeksini bulur
    int indexBul(int urunId) const {
        int i = 0;
        while (i < mSayi) {
            if (mUrunler[i]->getId() == urunId) {
                return i;
            }
            i++;
        }
        return -1; // Bulunamadi
    }

public:
    // Kurucu (Constructor)
    Sepet() {
        mSayi = 0;
    }

    // Sepetin bos olup olmadigini kontrol eder
    int bosMu() const {
        if (mSayi == 0) {
            return 1;
        }
        return 0;
    }

    // Sepete urun ekler, stoktan duser
    int urunEkle(Urun* urun, int adet) {
        // Temel kontroller
        if (!urun || adet <= 0 || urun->getStok() < adet || mSayi >= MAX_SEPET) {
            return 0;
        }

        int idx = indexBul(urun->getId());
        if (idx == -1) {
            // Yeni urun ekle
            mUrunler[mSayi] = urun;
            mAdetler[mSayi] = adet;
            mSayi++;
        }
        else {
            // Var olan urunun adedini artir
            mAdetler[idx] = mAdetler[idx] + adet;
        }

        // sepete girdigi an stoktan dusuyorum
        urun->stokAzalt(adet);
        return 1;
    }

    // Sepetten urun siler, stogu geri iade eder
    int urunSil(int urunId) {
        int idx = indexBul(urunId);
        if (idx == -1) {
            return 0;
        }

        // silince stok geri gelsin diye iade ettim
        mUrunler[idx]->stokArttir(mAdetler[idx]);

        // Dizideki boslugu kapatmak icin kaydirma (shift) islemi
        int i = idx;
        while (i < mSayi - 1) {
            mUrunler[i] = mUrunler[i + 1];
            mAdetler[i] = mAdetler[i + 1];
            i++;
        }

        mSayi--;
        return 1;
    }

    // Urun adedini gunceller, stok farkini ayarlar
    int adetGuncelle(int urunId, int yeniAdet) {
        int idx = indexBul(urunId);
        if (idx == -1 || yeniAdet <= 0) {
            return 0;
        }

        int eski = mAdetler[idx];
        int fark = yeniAdet - eski;

        if (fark > 0) { // Adet artiyorsa stoktan dus
            if (mUrunler[idx]->getStok() < fark) {
                return 0; // Stok yetersiz
            }
            mUrunler[idx]->stokAzalt(fark);
        }
        else if (fark < 0) { // Adet azaliyorsa stogu geri ekle
            mUrunler[idx]->stokArttir(-fark);
        }

        mAdetler[idx] = yeniAdet;
        return 1;
    }

    // Tum sepeti temizler ve stoklari tamamen geri iade eder
    void tamamenTemizle() {
        int i = 0;
        while (i < mSayi) {
            mUrunler[i]->stokArttir(mAdetler[i]); // Stoklari geri ver
            i++;
        }
        mSayi = 0;
    }

    // Sepetteki urunlerin satis fiyatlari uzerinden ara toplami hesaplar
    double araToplam() const {
        double t = 0.0;

        int i = 0;
        while (i < mSayi) {
            // Polimorfizm: Dogru urunun satisFiyati() cagrilir
            t = t + (mUrunler[i]->satisFiyati() * mAdetler[i]);
            i++;
        }

        return t;
    }

    // Sepet icerigini ekrana listeler
    void listele() const {
        if (mSayi == 0) {
            cout << "Sepet bos.\n";
            return;
        }

        cout << "---- SEPET ----\n";

        int i = 0;
        while (i < mSayi) {
            double satir = mUrunler[i]->satisFiyati() * mAdetler[i];

            cout << (i + 1) << ") " << mUrunler[i]->getAd()
                 << " | Kat: " << mUrunler[i]->getKategoriKodu()
                 << " | Adet: " << mAdetler[i]
                 << " | Satir: " << satir << "\n";

            i++;
        }

        cout << "AraToplam: " << araToplam() << "\n";
    }

    // Siparis bitince stok geri vermeden sepeti bosaltmak icin bunu koydum
    void sifirlaStokIadesiz() {
        mSayi = 0;
    }

    // Getter Metotlari
    int getSayi() const {
        return mSayi;
    }

    Urun* getUrun(int i) const {
        return mUrunler[i];
    }

    int getAdet(int i) const {
        return mAdetler[i];
    }
};

#endif