#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kitap struct yapýsý
typedef struct {
    int kitap_numarasi;
    char isim[450];
    char yazar[450];
    int sayfa_sayisi;
} Kitap;

// Kullanici struct yapýsý
typedef struct {
    int kullanici_numarasi;
    char isim[150];
    char soyisim[150]; 
} Kullanici;

// Odunc struct yapýsý
typedef struct {
    int kullanici_numarasi;
    int kitap_numarasi;
    char baslangic_tarihi[11]; 
    char bitis_tarihi[11];     
} Odunc;

void menu();
void kitapIslemleri();
void kullaniciIslemleri();
void oduncIslemleri();

void kitapEkle();
void kitapListele();
void kitapGuncelle();
void kitapSil();
void kitapAra();

void kullaniciEkle();
void kullaniciListele();
void kullaniciGuncelle();
void kullaniciSil();
void kullaniciAra();

void oduncAl();
void kitabiGeriGetir();
void oduncListele();

int main() {
    menu();
    return 0;
}

int otomatikNumaraAta(const char *file, int hangi) {
    FILE *dosya = fopen(file, "r");

    if (dosya == NULL) {
        return 1; 
    }

    int enYuksekNumara = 0;

    switch (hangi) {
        case 1: {
            Kitap kontrolKitap;
            while (fscanf(dosya, "%d %[^\n]s %[^\n]s %d", &kontrolKitap.kitap_numarasi, kontrolKitap.isim, kontrolKitap.yazar, &kontrolKitap.sayfa_sayisi) == 4) {
                if (kontrolKitap.kitap_numarasi > enYuksekNumara) {
                    enYuksekNumara = kontrolKitap.kitap_numarasi;
                }
            }
            break;
        }
        case 2: {
            Kullanici kontrolKullanici;
            while (fscanf(dosya, "%d %[^\n]s %[^\n]s", &kontrolKullanici.kullanici_numarasi, kontrolKullanici.isim, kontrolKullanici.soyisim) == 3) {
                if (kontrolKullanici.kullanici_numarasi > enYuksekNumara) {
                    enYuksekNumara = kontrolKullanici.kullanici_numarasi;
                }
            }
            break;
        }
        default:
            printf("HATALI GÝRÝS!");
            break;
    }

    fclose(dosya);

    // Dosyanýn sonuna gelindiðinde ve bir sonraki okuma iþlemi baþarýsýz olduðunda
    // enYuksekNumara 0 olacaktýr. Bu durumda, 1 ekleyerek yeni bir numara oluþturulur.
    return enYuksekNumara + 1;
}

void menu() {
    int secim;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Kitap Islemleri\n");
        printf("2. Kullanici Islemleri\n");
        printf("3. Odunc Alma Islemleri\n");
        printf("0. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kitapIslemleri();
                break;
            case 2:
                kullaniciIslemleri();
                break;
            case 3:
                oduncIslemleri();
                break;
            case 0:
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
    } while (secim != 0);
}

void kitapIslemleri() {
	char kitap[]="kitaplar.txt";
    int secim;
    do {
        printf("\n--- KITAP ISLEMLERI ---\n");
        printf("1. Kitap Ekleme\n");
        printf("2. Kitap Listeleme\n");
        printf("3. Kitap Guncelleme\n");
        printf("4. Kitap Silme\n");
        printf("5. Kitap Arama\n");
        printf("0. Ana Menu\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kitapEkle();
                break;
            case 2:
                kitapListele();
                break;
            case 3:
                kitapGuncelle();
                break;
            case 4:
                kitapSil();
                break;
            case 5:
                kitapAra();
                break;
            case 0:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
    } while (secim != 0);
}

void kitapEkle() {
    Kitap yeniKitap;
    char kitap[] = "kitaplar.txt";
    int hangi = 1;

    // Otomatik kitap numarasý atama
    yeniKitap.kitap_numarasi = otomatikNumaraAta(kitap, hangi);
    FILE *dosya = fopen(kitap, "a+");

    Kitap kontrolKitap;
    int enYuksekNumara = 0;

    while (fscanf(dosya, "%d %s %s %d", &kontrolKitap.kitap_numarasi, kontrolKitap.isim, kontrolKitap.yazar, &kontrolKitap.sayfa_sayisi) != EOF) {
        if (kontrolKitap.kitap_numarasi > enYuksekNumara) {
            enYuksekNumara = kontrolKitap.kitap_numarasi;
        }
    }

    fclose(dosya);

    // Yeni kitap numarasýný sýraya göre atama
    yeniKitap.kitap_numarasi = enYuksekNumara + 1;
	printf("Kitap eklerken bosluk yerine _ koynuz.");

    printf("Kitap Adi: ");
    scanf(" %[^\n]s", yeniKitap.isim);

    printf("Yazar: ");
    scanf(" %[^\n]s", yeniKitap.yazar);

    printf("Sayfa Sayisi: ");
    scanf("%d", &yeniKitap.sayfa_sayisi);

    dosya = fopen("kitaplar.txt", "a");

    // Yeni kitabý dosyaya yazma
    fprintf(dosya, "%d %s %s %d\n", yeniKitap.kitap_numarasi, yeniKitap.isim, yeniKitap.yazar, yeniKitap.sayfa_sayisi);

    fclose(dosya);

    printf("Kitap basariyla eklendi!\n");
    printf("Kitap numarasi: %d\n", yeniKitap.kitap_numarasi);
}

void kitapListele() {
    int kitapVarMi = 0;
    Kitap okunanKitap;

    FILE *dosya = fopen("kitaplar.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    printf("\n--- KITAPLAR ---\n");
    printf("%-10s%-20s%-20s%-15s\n", "Kitap No", "Isim", "Yazar", "Sayfa Sayisi");

    while (fscanf(dosya, "%d %s %s %d", &okunanKitap.kitap_numarasi, okunanKitap.isim, okunanKitap.yazar, &okunanKitap.sayfa_sayisi) != EOF) {
        kitapVarMi = 1;
        printf("%-10d%-20s%-20s%-15d\n", okunanKitap.kitap_numarasi, okunanKitap.isim, okunanKitap.yazar, okunanKitap.sayfa_sayisi);
    }

    if (kitapVarMi == 0) {
        printf("Listelenecek kitap bulunamamistir.\n");
    }

    fclose(dosya);
}

void kitapGuncelle() {
    int arananKitapNo;
    printf("Guncellenecek Kitap Numarasi: ");
    scanf("%d", &arananKitapNo);

    FILE *dosya = fopen("kitaplar.txt", "r");
    FILE *geciciDosya = fopen("gecici_kitaplar.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    Kitap guncelKitap;
    int bulundu = 0;
    
    while (fscanf(dosya, "%d %s %s %d", &guncelKitap.kitap_numarasi, guncelKitap.isim, guncelKitap.yazar, &guncelKitap.sayfa_sayisi) != EOF) {
        if (guncelKitap.kitap_numarasi == arananKitapNo) {
            printf("Yeni Bilgileri Girin:\n");

            printf("Yeni Kitap Adi: ");
            scanf(" %[^\n]s", guncelKitap.isim);

            printf("Yeni Yazar: ");
            scanf(" %[^\n]s", guncelKitap.yazar);

            printf("Yeni Sayfa Sayisi: ");
            scanf("%d", &guncelKitap.sayfa_sayisi);

            bulundu = 1;
        }

        fprintf(geciciDosya, "%d %s %s %d\n", guncelKitap.kitap_numarasi, guncelKitap.isim, guncelKitap.yazar, guncelKitap.sayfa_sayisi);
    }

    fclose(dosya);
    fclose(geciciDosya);

    if (!bulundu) {
        remove("gecici_kitaplar.txt"); // Geçici dosyayý sil
        printf("Belirtilen kitap numarasi bulunamadi.\n");
        return;
    }

    remove("kitaplar.txt");
    rename("gecici_kitaplar.txt", "kitaplar.txt");

    printf("Kitap basariyla guncellendi!\n");
}

void kitapSil() {
    FILE *dosya = fopen("kitaplar.txt", "r");
    FILE *geciciDosya = fopen("gecici_kitaplar.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilirken hata olustu\n");
        return;
    }

    Kitap silinecekKitap;
    char satir[500];
    int bulundu = 0;

    printf("Silinecek Kitap Numarasi: ");
    int silinecekKitapNo;
    scanf("%d", &silinecekKitapNo);

    rewind(dosya);  

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        sscanf(satir, "%d %s %s %d", &silinecekKitap.kitap_numarasi, silinecekKitap.isim, silinecekKitap.yazar, &silinecekKitap.sayfa_sayisi);

        if (silinecekKitap.kitap_numarasi == silinecekKitapNo) {
            bulundu = 1;
            
            printf("Kitap basariyla silindi!\n");
        } else {
            
            fprintf(geciciDosya, "%d %s %s %d\n", silinecekKitap.kitap_numarasi, silinecekKitap.isim, silinecekKitap.yazar, silinecekKitap.sayfa_sayisi);
        }
    }

    fclose(dosya);
    fclose(geciciDosya);

    remove("kitaplar.txt");
    rename("gecici_kitaplar.txt", "kitaplar.txt");

    if (!bulundu) {
        printf("Belirtilen numarada bir kitap bulunamadý.\n");
        return;
    }
}

void kitapAra() {
    char arananKelime[100];
    printf("Arama yapmak istediginiz kelimeyi girin: ");
    scanf(" %[^\n]s", arananKelime);

    FILE *dosya = fopen("kitaplar.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    Kitap arananKitap;
    int bulundu = 0;

printf("\n--- ARAMA SONUCU ---\n");
printf("%-15s%-20s%-20s%-15s\n", "Kitap Numarasi", "Isim", "Yazar", "Sayfa Sayisi");

// Dosyadan kitaplarý oku ve arama iþlemini yap
while (fscanf(dosya, "%d %s %s %d", &arananKitap.kitap_numarasi, arananKitap.isim, arananKitap.yazar, &arananKitap.sayfa_sayisi) != EOF) {
    // Kitabýn ismi veya yazarýnda aranan kelime varsa ekrana yazdýr
    if (strstr(arananKitap.isim, arananKelime) || strstr(arananKitap.yazar, arananKelime)) {
        printf("%-15d%-20s%-20s%-15d\n", arananKitap.kitap_numarasi, arananKitap.isim, arananKitap.yazar, arananKitap.sayfa_sayisi);
        bulundu = 1;
    }
}

fclose(dosya);

if (!bulundu) {
    printf("Aranan kelimeye uygun kitap bulunamadi.\n");
}
}

void kullaniciIslemleri() {
    int secim;
    char kullanici[]="kullanicilar.txt";
    do {
        printf("\n--- KULLANICI ISLEMLERI ---\n");
        printf("1. Kullanici Ekleme\n");
        printf("2. Kullanici Listeleme\n");
        printf("3. Kullanici Guncelleme\n");
        printf("4. Kullanici Silme\n");
        printf("5. Kullanici Arama\n");
        printf("0. Ana Menu\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kullaniciEkle();
                break;
            case 2:
                kullaniciListele();
                break;
            case 3:
                kullaniciGuncelle();
                break;
            case 4:
                kullaniciSil();
                break;
            case 5:
                kullaniciAra();
                break;
            case 0:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
    } while (secim != 0);
}

void kullaniciEkle() {
    Kullanici yeniKullanici;
    char kullanici[] = "kullanicilar.txt";
    int hangi = 2;

    yeniKullanici.kullanici_numarasi = otomatikNumaraAta(kullanici, hangi);

    FILE *dosya = fopen(kullanici, "a+");
    
    Kullanici kontrolKullanici;
    
    int enYuksekNumara = 0;
    
    while (fscanf(dosya, "%d %[^\n]s %[^\n]s", &kontrolKullanici.kullanici_numarasi, kontrolKullanici.isim, kontrolKullanici.soyisim) != EOF) {
        if (kontrolKullanici.kullanici_numarasi > enYuksekNumara) {
            enYuksekNumara = kontrolKullanici.kullanici_numarasi;
        }
    }
    fclose(dosya);

    
    yeniKullanici.kullanici_numarasi = enYuksekNumara + 1;

    printf("Isim: ");
    scanf(" %[^\n]s", yeniKullanici.isim);

    printf("Soyisim: ");
    scanf(" %[^\n]s", yeniKullanici.soyisim);
    
    dosya = fopen("kullanicilar.txt", "a");
    
    fprintf(dosya, "%d %s %s\n", yeniKullanici.kullanici_numarasi, yeniKullanici.isim, yeniKullanici.soyisim);

    fclose(dosya);

    printf("Kullanici %d basariyla eklendi!\n", yeniKullanici.kullanici_numarasi);
}

void kullaniciListele() {
    int kullaniciVarMi = 0;
    Kullanici okunanKullanici;

    FILE *dosya = fopen("kullanicilar.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    printf("\n--- KULLANICILAR ---\n");
    printf("%-20s%-20s%-20s\n", "Kullanici Numarasi", "Isim", "Soyisim");

    while (fscanf(dosya, "%d %s %s", &okunanKullanici.kullanici_numarasi, okunanKullanici.isim, okunanKullanici.soyisim) != EOF) {
        kullaniciVarMi = 1;
        printf("%-20d%-20s%-20s\n", okunanKullanici.kullanici_numarasi, okunanKullanici.isim, okunanKullanici.soyisim);
    }

    if (kullaniciVarMi == 0) {
        printf("Listelenecek kullanici bulunamamistir.\n");
    }

    fclose(dosya);
}


void kullaniciGuncelle() {
    int hedefKullaniciNo;
    printf("Guncellenecek Kullanici Numarasi: ");
    scanf("%d", &hedefKullaniciNo);

    FILE *dosya = fopen("kullanicilar.txt", "r");
    FILE *geciciDosya = fopen("gecici_kullanicilar.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    Kullanici okunanKullanici;
    int bulundu = 0;

    
    while (fscanf(dosya, "%d %s %s", &okunanKullanici.kullanici_numarasi, okunanKullanici.isim, okunanKullanici.soyisim) != EOF) {
        if (okunanKullanici.kullanici_numarasi == hedefKullaniciNo) {
            printf("Yeni Isim: ");
            scanf(" %[^\n]s", okunanKullanici.isim);

            printf("Yeni Soyisim: ");
            scanf(" %[^\n]s", okunanKullanici.soyisim);

            bulundu = 1;
        }

        fprintf(geciciDosya, "%d %s %s\n", okunanKullanici.kullanici_numarasi, okunanKullanici.isim, okunanKullanici.soyisim);
    }

    fclose(dosya);
    fclose(geciciDosya);

    if (!bulundu) {
        remove("gecici_kullanicilar.txt");
        printf("Belirtilen kullanici bulunamadi.\n");
        return;
    }

    remove("kullanicilar.txt");
    rename("gecici_kullanicilar.txt", "kullanicilar.txt");

    printf("Kullanici basariyla guncellendi.\n");
}

void kullaniciSil() {
    FILE *dosya = fopen("kullanicilar.txt", "r");
    FILE *geciciDosya = fopen("gecici_kullanicilar.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilirken hata olustu\n");
        return;
    }

    Kullanici silinecekKullanici;
    char satir[500];
    int bulundu = 0;

    printf("Silinecek Kullanici Numarasi: ");
    int silinecekKullaniciNo;
    scanf("%d", &silinecekKullaniciNo);

    rewind(dosya); 


    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        sscanf(satir, "%d %s %s", &silinecekKullanici.kullanici_numarasi, silinecekKullanici.isim, silinecekKullanici.soyisim);

        if (silinecekKullanici.kullanici_numarasi == silinecekKullaniciNo) {
            bulundu = 1;

            printf("Kullanici basariyla silindi!\n");
        } else {

            fprintf(geciciDosya, "%d %s %s\n", silinecekKullanici.kullanici_numarasi, silinecekKullanici.isim, silinecekKullanici.soyisim);
        }
    }

    fclose(dosya);
    fclose(geciciDosya);


    remove("kullanicilar.txt");
    rename("gecici_kullanicilar.txt", "kullanicilar.txt");

    if (!bulundu) {
        printf("Belirtilen numarada bir kullanici bulunamadi.\n");
        return;
    }
}

void kullaniciAra() {
    char arananKelime[100];
    printf("Arama yapmak istediginiz kelimeyi girin: ");
    scanf(" %[^\n]s", arananKelime);

    FILE *dosya = fopen("kullanicilar.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    Kullanici arananKullanici;
    int bulundu = 0;

printf("\n--- ARAMA SONUCU ---\n");
printf("%-20s%-20s%-20s\n", "Kullanici Numarasi", "Isim", "Soyisim");

while (fscanf(dosya, "%d %s %s", &arananKullanici.kullanici_numarasi, arananKullanici.isim, arananKullanici.soyisim) != EOF) {

    if (strstr(arananKullanici.isim, arananKelime) || strstr(arananKullanici.soyisim, arananKelime)) {
        printf("%-20d%-20s%-20s\n", arananKullanici.kullanici_numarasi, arananKullanici.isim, arananKullanici.soyisim);
        bulundu = 1;
    }
}

fclose(dosya);


if (!bulundu) {
    printf("Aranan kelimeye uygun kullanici bulunamadi.\n");
}
}

void oduncIslemleri() {
    int secim;
    do {
        printf("\n--- ODUNC ALMA ISLEMLERI ---\n");
        printf("1. Odunc Alma\n");
        printf("2. Kitabi Geri Getirme\n");
        printf("3. Odunc Listeleme\n");
        printf("0. Ana Menu\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                oduncAl();
                break;
            case 2:
                kitabiGeriGetir();
                break;
            case 3:
                oduncListele();
                break;
            case 0:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
    } while (secim != 0);
}

void oduncAl() {
    Odunc yeniOdunc;

    printf("Kullanici Numarasi: ");
    scanf("%d", &yeniOdunc.kullanici_numarasi);

    printf("Kitap Numarasi: ");
    scanf("%d", &yeniOdunc.kitap_numarasi);

    if (kitapOduncAlindiMi(yeniOdunc.kitap_numarasi)) {
        printf("Bu kitap zaten odunc alinmis.\n");
        return;
    }

    printf("Baslangic Tarihi (Ör: 01/01/2024): ");
    scanf("%s", yeniOdunc.baslangic_tarihi);

    printf("Bitis Tarihi (Ör: 15/01/2024): ");
    scanf("%s", yeniOdunc.bitis_tarihi);

    FILE *dosya = fopen("odunc_alinan_kitaplar.txt", "a");
    if (dosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    fprintf(dosya, "%d %d %s %s\n", yeniOdunc.kullanici_numarasi, yeniOdunc.kitap_numarasi, yeniOdunc.baslangic_tarihi, yeniOdunc.bitis_tarihi);

    fclose(dosya);

    printf("Kitap basariyla odunc alindi!\n");
}

int kitapOduncAlindiMi(int kitapNumarasi) {
    FILE *dosya = fopen("odunc_alinan_kitaplar.txt", "r");
    if (dosya == NULL) {
        return 0;
    }

    Odunc oduncKontrol;
    while (fscanf(dosya, "%*d %d %s %s", &oduncKontrol.kitap_numarasi, oduncKontrol.baslangic_tarihi, oduncKontrol.bitis_tarihi) != EOF) {
        if (oduncKontrol.kitap_numarasi == kitapNumarasi) {
            fclose(dosya);
            return 1;
        }
    }

    fclose(dosya);
    return 0;
}

void kitabiGeriGetir() {
    int kullaniciNo, kitapNo;
    printf("Kullanici Numarasi: ");
    scanf("%d", &kullaniciNo);

    printf("Kitap Numarasi: ");
    scanf("%d", &kitapNo);

    FILE *dosya = fopen("odunc_alinan_kitaplar.txt", "r");
    FILE *geciciDosya = fopen("gecici_odunc_alinan_kitaplar.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    Odunc oduncBilgisi;
    int bulundu = 0;

    while (fscanf(dosya, "%d %d %s %s", &oduncBilgisi.kullanici_numarasi, &oduncBilgisi.kitap_numarasi, oduncBilgisi.baslangic_tarihi, oduncBilgisi.bitis_tarihi) != EOF) {
        if (oduncBilgisi.kullanici_numarasi == kullaniciNo && oduncBilgisi.kitap_numarasi == kitapNo) {
            bulundu = 1;
            printf("Kitap geri getiriliyor...\n");
        } else {
        
            fprintf(geciciDosya, "%d %d %s %s\n", oduncBilgisi.kullanici_numarasi, oduncBilgisi.kitap_numarasi, oduncBilgisi.baslangic_tarihi, oduncBilgisi.bitis_tarihi);
        }
    }

    fclose(dosya);
    fclose(geciciDosya);

    if (!bulundu) {
        remove("gecici_odunc_alinan_kitaplar.txt"); 
        printf("Belirtilen kullanici veya kitap numarasina sahip odunc kitap bulunamadi.\n");
        return;
    }

    remove("odunc_alinan_kitaplar.txt");
    rename("gecici_odunc_alinan_kitaplar.txt", "odunc_alinan_kitaplar.txt");

    printf("Kitap basariyla geri getirildi!\n");
}

void oduncListele() {

    FILE *dosya = fopen("odunc_alinan_kitaplar.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        return;
    }

    Odunc oduncBilgisi;
    printf("\n--- ODUNC KITAPLAR ---\n");
    printf("%-15s%-15s%-20s%-20s\n", "Kullanici No", "Kitap No", "Baslangic Tarihi", "Bitis Tarihi");

    while (fscanf(dosya, "%d %d %s %s", &oduncBilgisi.kullanici_numarasi, &oduncBilgisi.kitap_numarasi, oduncBilgisi.baslangic_tarihi, oduncBilgisi.bitis_tarihi) != EOF) {
        printf("%-15d%-15d%-20s%-20s\n", oduncBilgisi.kullanici_numarasi, oduncBilgisi.kitap_numarasi, oduncBilgisi.baslangic_tarihi, oduncBilgisi.bitis_tarihi);
    }

    fclose(dosya);
}
