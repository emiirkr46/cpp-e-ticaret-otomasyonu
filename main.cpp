#include <iostream>
#include <string>

#include "Kategoriler.h"
#include "MusteriOkuma.h"
#include "Sepet.h"

using namespace std;

// Ana dosyada menuleri, login'i ve odeme akisini topladim.
// Urunleri burada elle ekledim (odev oyle istiyor).

#define MAX_URUN 300

// Odeme tipleri sabitleri
#define ODEME_KK   1
#define ODEME_EFT  2
#define ODEME_KAP  3

// Gecersiz girdiden sonra cin buffer'ini temizler
static void cinTemizle() {
    cin.clear();

    // ignore kullanmadim, elle newline'a kadar yuttum
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') {
            break;
        }
    }
}

// ID'ye gore urunu bulur
static Urun* urunBul(Urun* urunler[], int urunSayi, int id) {
    int i = 0;
    while (i < urunSayi) {
        if (urunler[i]->getId() == id) {
            return urunler[i];
        }
        i++;
    }
    return 0; // Bulunamadi
}

// Kategori seceneklerini ekrana yazar
static void kategorileriYaz() {
    cout << "\nKategoriler:\n";
    cout << "1) ELEK (Elektronik)\n";
    cout << "2) PC   (Bilgisayar)\n";
    cout << "3) TAB  (Tablet)\n";
    cout << "4) GIY  (Giyim)\n";
    cout << "5) KTP  (Kitap)\n";
}

// Kullanicidan kategori secimi alir ve kategori kodunu dondurur
static string kategoriSec() {
    kategorileriYaz();
    cout << "Kategori sec (1-5): ";

    int s;
    if (!(cin >> s)) {
        cinTemizle();
        return "";
    }

    if (s == 1) { return "ELEK"; }
    if (s == 2) { return "PC"; }
    if (s == 3) { return "TAB"; }
    if (s == 4) { return "GIY"; }
    if (s == 5) { return "KTP"; }

    return "";
}

// Belirli bir kategoriye ait urunleri listeler
static void kategoriyeGoreListele(Urun* urunler[], int urunSayi, const string& kat) {
    cout << "\n--- URUN LISTESI (" << kat << ") ---\n";

    int i = 0;
    while (i < urunSayi) {
        if (urunler[i]->getKategoriKodu() == kat) {
            urunler[i]->yazdir(); // Polimorfizm
            cout << "\n";
        }
        i++;
    }
}

// Tum urunleri listeler
static void tumUrunleriListele(Urun* urunler[], int urunSayi) {
    cout << "\n--- TUM URUNLER ---\n";

    int i = 0;
    while (i < urunSayi) {
        urunler[i]->yazdir(); // Polimorfizm
        cout << "\n";
        i++;
    }
}

// Odeme tipine gore nihai tutar uzerindeki farki hesaplar
static double odemeFarki(int odemeTipi, double tutar) {
    if (odemeTipi == ODEME_KK) {
        return tutar * 0.02; // +%2
    }
    if (odemeTipi == ODEME_EFT) {
        return -(tutar * 0.03); // -%3
    }
    if (odemeTipi == ODEME_KAP) {
        return 30.0; // Sabit 30 TL
    }
    return 0.0;
}

// Odeme tipi numarasina karsilik gelen ismi dondurur
static string odemeAdi(int odemeTipi) {
    if (odemeTipi == ODEME_KK) { return "Kredi Karti"; }
    if (odemeTipi == ODEME_EFT) { return "Havale/EFT"; }
    if (odemeTipi == ODEME_KAP) { return "Kapida Odeme"; }
    return "Bilinmiyor";
}

int main() {
    cout << "E_TICARET sistemine hos geldin.\n";

    // 1) Musterileri dosyadan aliyorum
    Musteri* musteriler[MAX_MUSTERI];
    int musteriSayi = 0;

    // musteri.txt okuma islemi
    if (!musterileriOku(musteriler, musteriSayi)) {
        cout << "musteri.txt okunamadi.\n";
        return 0;
    }

    // 2) Urunleri elle ekledim (25 tane)
    Urun* urunler[MAX_URUN];
    int urunSayi = 0;
    int id = 1001; // Urun ID baslangici

    // Elektronik Urunleri (ELEK)
    urunler[urunSayi] = new Elektronik(id++, "Bluetooth Kulaklik", 899.90, 30, "Sonic", 24, 15); urunSayi++;
    urunler[urunSayi] = new Elektronik(id++, "Akilli Saat", 1499.00, 20, "TimeX", 24, 5); urunSayi++;
    urunler[urunSayi] = new Elektronik(id++, "Oyun Konsolu", 15999.00, 10, "PlayNova", 24, 120); urunSayi++;
    urunler[urunSayi] = new Elektronik(id++, "Kablosuz Mouse", 399.90, 50, "ClickPro", 12, 2); urunSayi++;
    urunler[urunSayi] = new Elektronik(id++, "Router", 1299.00, 25, "NetFast", 24, 18); urunSayi++;

    // Bilgisayar Urunleri (PC)
    urunler[urunSayi] = new Bilgisayar(id++, "Laptop 14", 25999.00, 8, "i5", 16, 512); urunSayi++;
    urunler[urunSayi] = new Bilgisayar(id++, "Laptop 16", 33999.00, 6, "i7", 32, 1024); urunSayi++;
    urunler[urunSayi] = new Bilgisayar(id++, "Masaustu", 28999.00, 5, "Ryzen7", 32, 1024); urunSayi++;
    urunler[urunSayi] = new Bilgisayar(id++, "Mini PC", 9999.00, 12, "i3", 8, 256); urunSayi++;
    urunler[urunSayi] = new Bilgisayar(id++, "Workstation", 74999.00, 2, "Xeon", 64, 2048); urunSayi++;

    // Tablet Urunleri (TAB)
    urunler[urunSayi] = new Tablet(id++, "Tablet 10", 7999.00, 15, 10.1, 1, 8000); urunSayi++;
    urunler[urunSayi] = new Tablet(id++, "Tablet 11", 9999.00, 12, 11.0, 1, 9000); urunSayi++;
    urunler[urunSayi] = new Tablet(id++, "Tablet Mini", 5499.00, 20, 8.3, 0, 6000); urunSayi++;
    urunler[urunSayi] = new Tablet(id++, "Tablet Pro", 15999.00, 7, 12.9, 1, 11000); urunSayi++;
    urunler[urunSayi] = new Tablet(id++, "Cocuk Tablet", 3999.00, 18, 8.0, 0, 5000); urunSayi++;

    // Giyim Urunleri (GIY)
    urunler[urunSayi] = new Giyim(id++, "Tisort", 299.90, 80, "M", "Siyah", "Pamuk"); urunSayi++;
    urunler[urunSayi] = new Giyim(id++, "Hoodie", 899.90, 40, "L", "Gri", "Polar"); urunSayi++;
    urunler[urunSayi] = new Giyim(id++, "Kot Pantolon", 1299.00, 35, "32", "Mavi", "Denim"); urunSayi++;
    urunler[urunSayi] = new Giyim(id++, "Mont", 2499.00, 20, "XL", "Lacivert", "Kanvas"); urunSayi++;
    urunler[urunSayi] = new Giyim(id++, "Spor Ayakkabi", 2199.00, 25, "42", "Beyaz", "Sentetik"); urunSayi++;

    // Kitap Urunleri (KTP)
    urunler[urunSayi] = new Kitap(id++, "C++ Temelleri", 450.00, 40, "A. Yazar", 520, "KodYayin"); urunSayi++;
    urunler[urunSayi] = new Kitap(id++, "Algoritmalar", 520.00, 35, "B. Yazar", 610, "Bilisim"); urunSayi++;
    urunler[urunSayi] = new Kitap(id++, "Veritabani", 390.00, 30, "C. Yazar", 480, "Akademi"); urunSayi++;
    urunler[urunSayi] = new Kitap(id++, "OOP Pratik", 410.00, 25, "D. Yazar", 450, "Teknik"); urunSayi++;
    urunler[urunSayi] = new Kitap(id++, "Linux Notlari", 360.00, 50, "E. Yazar", 400, "Sistem"); urunSayi++;

    // 3) Login akisi
    Musteri* aktif = 0;

    int deneme = 0;
    while (deneme < 3 && !aktif) {
        string k;
        string s;

        cout << "\nKullanici adi: ";
        cin >> k;
        cout << "Sifre: ";
        cin >> s;

        // Musteri listesinde dogrulama yap
        int i = 0;
        while (i < musteriSayi) {
            if (musteriler[i]->getKullaniciAdi() == k && musteriler[i]->sifreDogruMu(s)) {
                aktif = musteriler[i];
                break;
            }
            i++;
        }

        if (!aktif) {
            cout << "Giris basarisiz.\n";
        }

        deneme++;
    }

    // Login basarisizsa programdan cik
    if (!aktif) {
        cout << "Cikis.\n";

        // Bellek temizligi
        int i = 0;
        while (i < urunSayi) {
            delete urunler[i];
            i++;
        }

        i = 0;
        while (i < musteriSayi) {
            delete musteriler[i];
            i++;
        }

        return 0;
    }

    cout << "\nHos geldin: ";
    aktif->yazdir(); // Polimorfizm ile dogru musteri tipi yazdirilir
    cout << "\n";

    // Adresleri basit tuttum (diziyle)
    string adresler[20];
    int adresSayi = 0;

    Sepet sepet;

    // 4) Ana Menuler
    while (true) {
        cout << "\n==== ANA MENU ====\n";
        cout << "1) Adres ekle/listele\n";
        cout << "2) Kategori secip urun listele\n";
        cout << "3) Tum urunleri listele\n";
        cout << "4) Sepete urun ekle\n";
        cout << "5) Sepet islemleri\n";
        cout << "0) Cikis\n";
        cout << "Secim: ";

        int secim;
        if (!(cin >> secim)) {
            cinTemizle();
            continue;
        }

        if (secim == 0) {
            break; // Cikis
        }

        if (secim == 1) {
            // Adres Ekle/Listele
            cout << "\nAdresler:\n";

            if (adresSayi == 0) {
                cout << "Adres yok.\n";
            }

            int i = 0;
            while (i < adresSayi) {
                cout << (i + 1) << ") " << adresler[i] << "\n";
                i++;
            }

            cout << "Yeni adres ekle? (1=Evet, 0=Hayir): ";
            int evet;

            if (!(cin >> evet)) {
                cinTemizle();
                continue;
            }

            if (evet == 1) {
                if (adresSayi >= 20) {
                    cout << "Adres limiti dolu.\n";
                }
                else {
                    cout << "Adres gir: ";
                    cinTemizle();
                    getline(cin, adresler[adresSayi]);

                    if (adresler[adresSayi].size() > 0) {
                        adresSayi++;
                    }
                }
            }
        }
        else if (secim == 2) {
            // Kategoriye gore urun listele
            string kat = kategoriSec();

            if (kat == "") {
                cout << "Gecersiz.\n";
            }
            else {
                kategoriyeGoreListele(urunler, urunSayi, kat);
            }
        }
        else if (secim == 3) {
            // Tum urunleri listele
            tumUrunleriListele(urunler, urunSayi);
        }
        else if (secim == 4) {
            // Sepete urun ekle
            int uid;
            int adet;

            cout << "Urun ID: ";
            if (!(cin >> uid)) { cinTemizle(); continue; }

            cout << "Adet: ";
            if (!(cin >> adet)) { cinTemizle(); continue; }

            Urun* u = urunBul(urunler, urunSayi, uid);

            if (!u) {
                cout << "Urun yok.\n";
            }
            else {
                int ok = sepet.urunEkle(u, adet);

                if (!ok) {
                    cout << "Eklenemedi (stok/adet).\n";
                }
                else {
                    cout << "Eklendi.\n";
                }
            }
        }
        else if (secim == 5) {
            // Sepet Islemleri Menusu
            while (true) {
                cout << "\n==== SEPET ====\n";
                sepet.listele();

                cout << "1) Urun sil\n";
                cout << "2) Adet guncelle\n";
                cout << "3) Sepeti temizle\n";
                cout << "4) Odeme yap\n";
                cout << "0) Geri\n";
                cout << "Secim: ";

                int s2;
                if (!(cin >> s2)) {
                    cinTemizle();
                    continue;
                }

                if (s2 == 0) {
                    break;
                }

                if (s2 == 1) {
                    // Urun sil
                    int uid;
                    cout << "Silinecek urun ID: ";
                    if (!(cin >> uid)) { cinTemizle(); continue; }

                    if (!sepet.urunSil(uid)) {
                        cout << "Silinemedi.\n";
                    }
                    else {
                        cout << "Silindi.\n";
                    }
                }
                else if (s2 == 2) {
                    // Adet guncelle
                    int uid;
                    int yeni;

                    cout << "Urun ID: ";
                    if (!(cin >> uid)) { cinTemizle(); continue; }

                    cout << "Yeni adet: ";
                    if (!(cin >> yeni)) { cinTemizle(); continue; }

                    if (!sepet.adetGuncelle(uid, yeni)) {
                        cout << "Guncellenemedi.\n";
                    }
                    else {
                        cout << "Guncellendi.\n";
                    }
                }
                else if (s2 == 3) {
                    // Sepeti temizle (Stoklar iade edilir)
                    sepet.tamamenTemizle();
                    cout << "Sepet temizlendi.\n";
                }
                else if (s2 == 4) {
                    // Odeme akisi baslangici
                    if (sepet.bosMu()) {
                        cout << "Sepet bos.\n";
                        continue;
                    }

                    // Teslimat adresi aliyorum
                    string teslimat;

                    if (adresSayi == 0) {
                        cout << "Teslimat adresi gir: ";
                        cinTemizle();
                        getline(cin, teslimat);
                    }
                    else {
                        // Var olan adreslerden secim yap veya yeni gir
                        cout << "Adres sec (1-" << adresSayi << "), 0=Yeni gir: ";
                        int asec;

                        if (!(cin >> asec)) { cinTemizle(); continue; }

                        if (asec == 0) {
                            cout << "Yeni adres: ";
                            cinTemizle();
                            getline(cin, teslimat);

                            if (teslimat.size() > 0 && adresSayi < 20) {
                                adresler[adresSayi] = teslimat;
                                adresSayi++;
                            }
                        }
                        else if (asec >= 1 && asec <= adresSayi) {
                            teslimat = adresler[asec - 1];
                        }
                        else {
                            cout << "Gecersiz.\n";
                            continue;
                        }
                    }

                    // Hesaplamalar
                    double ara = sepet.araToplam();
                    // Polimorfizm ile aktif musterinin indirim orani alinir
                    double indirim = ara * aktif->indirimOrani();
                    double indirimli = ara - indirim;
                    // Polimorfizm ile aktif musterinin kargo ucreti alinir
                    double kargo = aktif->kargoUcreti(ara);

                    // Odeme tipi secimi
                    cout << "\nOdeme tipi:\n";
                    cout << "1) Kredi Karti (+%2)\n";
                    cout << "2) Havale/EFT (-%3)\n";
                    cout << "3) Kapida Odeme (+30)\n";
                    cout << "Secim: ";

                    int ot;
                    if (!(cin >> ot)) { cinTemizle(); continue; }

                    if (ot < 1 || ot > 3) {
                        cout << "Gecersiz.\n";
                        continue;
                    }

                    double baz = indirimli + kargo;
                    double fark = odemeFarki(ot, baz);
                    double nihai = baz + fark;

                    // Siparis ozeti
                    cout << "\n========== SIPARIS OZETI ==========\n";
                    cout << "Musteri: ";
                    aktif->yazdir(); // Polimorfizm
                    cout << "\n";

                    cout << "Adres: " << teslimat << "\n\n";
                    cout << "Sepet:\n";

                    // Sepet icerigini detayli listele
                    int i = 0;
                    while (i < sepet.getSayi()) {
                        Urun* uu = sepet.getUrun(i);
                        int adt = sepet.getAdet(i);
                        double satir = uu->satisFiyati() * adt;

                        cout << "- " << uu->getAd()
                             << " | Kat: " << uu->getKategoriKodu()
                             << " | Adet: " << adt
                             << " | Satir: " << satir << "\n";

                        i++;
                    }

                    // Nihai hesaplamalari yazdir
                    cout << "\nAra toplam: " << ara << "\n";
                    cout << "Indirim: -" << indirim << "\n";
                    cout << "Indirim sonrasi: " << indirimli << "\n";
                    cout << "Kargo: " << kargo << "\n";
                    cout << "Odeme: " << odemeAdi(ot) << "\n";
                    cout << "Odeme farki: " << fark << "\n";
                    cout << "NIHAI: " << nihai << "\n";
                    cout << "==================================\n";

                    // Siparis tamam, sepeti stok iadesiz sifirliyorum
                    sepet.sifirlaStokIadesiz();
                    break;
                }
            }
        }
    }

    // Program kapanirken new ile actiklarimi siliyorum (Bellek temizligi)
    int i = 0;
    while (i < urunSayi) {
        delete urunler[i];
        i++;
    }

    i = 0;
    while (i < musteriSayi) {
        delete musteriler[i];
        i++;
    }

    cout << "Cikis yapildi.\n";
    return 0;
}