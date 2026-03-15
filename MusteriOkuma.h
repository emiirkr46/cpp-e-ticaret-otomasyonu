#ifndef MUSTERI_OKUMA_H
#define MUSTERI_OKUMA_H

#include <string>
#include <fstream>
#include <iostream>
#include "Musteri.h"

using namespace std;

// Burada musterileri dosyadan okuyorum.
// Hazir cevirme fonksiyonlari kullanmadan kendim parcaladim.

#define MAX_MUSTERI 200

// String'i Integer'a cevirme fonksiyonu (Manuel uygulama)
inline int benimIntCevir(const string& s) {
    int i = 0;
    int isaret = 1;
    long sonuc = 0;

    // Baslangictaki bosluklari yut
    while (i < (int)s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')) {
        i++;
    }

    // Isareti kontrol et
    if (i < (int)s.size() && s[i] == '-') {
        isaret = -1;
        i++;
    }
    else if (i < (int)s.size() && s[i] == '+') {
        i++;
    }

    // Rakamlari cevir
    while (i < (int)s.size()) {
        char c = s[i];
        if (c < '0' || c > '9') {
            break; // Rakam degilse dur
        }
        sonuc = sonuc * 10 + (c - '0');
        i++;
    }

    return (int)(sonuc * isaret);
}

// CSV satirindan istenen alani (parcayi) cikarir
inline string csvAlanGetir(const string& satir, int hedefIndex) {
    int idx = 0;
    int bas = 0;
    int i = 0;

    if (hedefIndex < 0) {
        return "";
    }

    // Satir sonuna veya virgul gorene kadar ilerle
    while (i <= (int)satir.size()) {
        if (i == (int)satir.size() || satir[i] == ',') {
            if (idx == hedefIndex) {
                int son = i;
                string parca = "";

                // Alanı parcala
                int k = bas;
                while (k < son) {
                    parca += satir[k];
                    k++;
                }
                return parca;
            }
            idx++;
            bas = i + 1; // Bir sonraki alanin baslangici
        }
        i++;
    }

    return "";
}

// CSV satirindaki alan (virgul sayisi + 1) sayisini hesaplar
inline int csvAlanSayisi(const string& satir) {
    int say = 1;

    int i = 0;
    while (i < (int)satir.size()) {
        if (satir[i] == ',') {
            say++;
        }
        i++;
    }

    return say;
}

// musteri.txt dosyasindan musteri verilerini okur ve Musteri nesneleri olusturur
inline int musterileriOku(Musteri* dizi[], int& sayi) {
    ifstream fin("musteri.txt");
    if (!fin) {
        return 0; // Dosya acilamazsa 0 dondur
    }

    sayi = 0;
    string satir;

    // baslik satirini geciyorum
    getline(fin, satir);

    while (getline(fin, satir)) {
        if (satir.size() == 0) {
            continue;
        }

        if (sayi >= MAX_MUSTERI) {
            break;
        }

        int alanSay = csvAlanSayisi(satir);
        if (alanSay < 6) { // En az 6 alan olmali
            continue;
        }

        // CSV alanlarini cikar
        string sNo    = csvAlanGetir(satir, 0);
        string ad     = csvAlanGetir(satir, 1);
        string soyad  = csvAlanGetir(satir, 2);
        string kAdi   = csvAlanGetir(satir, 3);
        string sifre  = csvAlanGetir(satir, 4);
        string tip    = csvAlanGetir(satir, 5);

        string sirket = "";
        string vergi  = "";

        // Kurumsal musteriler icin opsiyonel alanlari kontrol et
        if (alanSay >= 7) {
            sirket = csvAlanGetir(satir, 6);
        }
        if (alanSay >= 8) {
            vergi = csvAlanGetir(satir, 7);
        }

        int no = benimIntCevir(sNo);

        // Tipine gore farkli sinif (polimorfizm) olusturuyorum
        if (tip == "Kurumsal") {
            dizi[sayi] = new KurumsalMusteri(no, ad, soyad, kAdi, sifre, sirket, vergi);
        }
        else if (tip == "Premium") {
            dizi[sayi] = new PremiumMusteri(no, ad, soyad, kAdi, sifre);
        }
        else { // Diger tum tipler Standart olarak kabul edilir (Bireysel)
            dizi[sayi] = new StandartMusteri(no, ad, soyad, kAdi, sifre);
        }

        sayi++;
    }

    fin.close();
    return 1;
}

#endif