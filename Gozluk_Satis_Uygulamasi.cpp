#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

#define MaksUzunluk 50
#define gozlukStoklari 6

int stocks[gozlukStoklari] = {0}; // Stoklarý tutacak dizi
const char *gozlukStok = "stok.txt";

const int ekranGenislik = 1080;  // Örneðin, 1080x720 çözünürlük
const int ekranYukseklik = 720;

// Kullanýcýdan metin giriþi almak için yardýmcý fonksiyon
void girdiAlindi(char *input, int maxLength, int x, int y, int issifre) {
    int i = 0;
    char ch;
    while (1) {
        if (kbhit()) {  // Klavyeden bir tuþ basýldý mý kontrol et
            ch = getch();
            if (ch == 13) { // Enter tuþu
                input[i] = '\0';
                break;
            } else if (ch == 8 && i > 0) { // Backspace tuþu
                i--;
                setcolor(BLACK);
                outtextxy(x + i * 10, y, "_");
                input[i] = '\0';
            } else if (i < maxLength - 1) {
                input[i] = ch;
                input[i + 1] = '\0';
                setcolor(WHITE);
                if (issifre) {
                    outtextxy(x + i * 10, y, "*");
                } else {
                    outtextxy(x + i * 10, y, &ch);
                }
                i++;
            }
        }
        delay(100);  // Kýsa bir süre bekleyerek diðer iþlemlere de fýrsat ver
    }
}

// Kullanýcý adý ve þifreyi dosyaya kaydetme
void kayitOlustur(const char *kullaniciadi, const char *sifre) {
    FILE *file = fopen("gozluk.txt", "a");
    if (file == NULL) {
        printf("Dosya açma hatasý!\n");
        return;
    }
    fprintf(file, "%s %s\n", kullaniciadi, sifre);
    fclose(file);
}

// Kullanýcý adý ve þifre doðrulama
int kullaniciDogrula(const char *kullaniciadi, const char *sifre) {
    FILE *file = fopen("gozluk.txt", "r");
    if (file == NULL) {
        printf("Dosya açma hatasý!\n");
        return 0;
    }
    char storedkullaniciadi[MaksUzunluk];
    char storedsifre[MaksUzunluk];
    while (fscanf(file, "%s %s", storedkullaniciadi, storedsifre) != EOF) {
        if (strcmp(kullaniciadi, storedkullaniciadi) == 0 && strcmp(sifre, storedsifre) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Stoklarý dosyadan yükleme
void stokCekme() {
    FILE *file = fopen(gozlukStok, "r");
    if (file == NULL) {
        printf("Stok dosyasý açma hatasý!\n");
        return;
    }
    for (int i = 0; i < gozlukStoklari; i++) {
        fscanf(file, "%d", &stocks[i]);
    }
    fclose(file);
}

// Stoklarý dosyaya kaydetme
void stokKaydet() {
    FILE *file = fopen(gozlukStok, "w");
    if (file == NULL) {
        printf("Stok dosyasý açma hatasý!\n");
        return;
    }
    for (int i = 0; i < gozlukStoklari; i++) {
        fprintf(file, "%d\n", stocks[i]);
    }
    fclose(file);
}
// Gözlük stoklarýný azaltan fonksiyon
void stoktanDus(int index) {
    if (stocks[index] > 0) {
        stocks[index]--;
        stokKaydet();
    } else {
        cleardevice();
		outtextxy(100, 200, "Elimizde Yok!");
        delay(1500);
    }
}

// Gözlük seçim menüsü iþlemleri
void gozlukMenuleri( char *category) {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(200, 50, category);
    // Geri butonu
    rectangle(100, 360, 400, 410);
    outtextxy(200, 380, "Geri");
}

void animasyonMenu(int type) {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    rectangle(340, 250, 740, 450);
    switch(type) {
        case 0:
            outtextxy(350, 350, "Çocuk Gözlüðü Seçildi");
            break;
        case 1:
            outtextxy(350, 350, "Erkek Gözlüðü Seçildi");
            break;
        case 2:
            outtextxy(350, 350, "Kadýn Gözlüðü Seçildi");
            break;
        case 3:
            outtextxy(350, 350, "Barbie Gözlüðü Satýn Alýndý!");
            break;
        case 4:
            outtextxy(350, 350, "McQueen Gözlüðü Satýn Alýndý!");
            break;
        case 5:
            outtextxy(350, 350, "Ray Ban Gözlüðü Satýn Alýndý!");
            break;
        case 6:
            outtextxy(350, 350, "Mustang Gözlüðü Satýn Alýndý!");
            break;
        case 7:
            outtextxy(350, 350, "Osse Gözlüðü Satýn Alýndý!");
            break;
        case 8:
            outtextxy(350, 350, "Gusto Gözlüðü Satýn Alýndý!");
            break;
        case 9:
        	outtextxy(350,350, "Geri Tuþuna Basýldý!");
        	break;
    }
    int c,v,b;
    while (!kbhit()) {
        for (b=0; b<=500; b++) {
            c = rand() % getmaxx();
            v = rand() % getmaxy();
            putpixel(c,v,3);
        }
        delay(750);
        cleardevice();
        break;
    }
}

// Ana menü iþlemleri
int main() {
    int gd = DETECT, gm;
    initwindow(ekranGenislik, ekranYukseklik, "Tam Ekran Grafik Penceresi");

    // Stoklarý yükle
    stokCekme();

    char inputkullaniciadi[MaksUzunluk];
    char inputsifre[MaksUzunluk];

    // Giriþ ve kayýt butonlarý
    while (1) {
        cleardevice();
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(200, 100, "Giris ve Kayit");

        // Giriþ butonu
        rectangle(150, 200, 350, 250);
        outtextxy(200, 220, "Giris");

        // Kayýt butonu
        rectangle(150, 300, 350, 350);
        outtextxy(200, 320, "Kayit");

        int x, y;
        while (1) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                // Giriþ butonuna týklama
                if (x >= 150 && x <= 350 && y >= 200 && y <= 250) {
                    cleardevice();
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(50, 150, "Kullanici Adi: ");
                    girdiAlindi(inputkullaniciadi, MaksUzunluk, 200, 150, 0);

                    outtextxy(50, 200, "Sifre: ");
                    girdiAlindi(inputsifre, MaksUzunluk, 200, 200, 1);

                    char hosgeldinMesaji[MaksUzunluk + 20] = "Hosgeldiniz, ";

                    // Eðer giriþ baþarýlýysa kullanýcý adýný karþýlama mesajýna ekleyin
                    if (kullaniciDogrula(inputkullaniciadi, inputsifre)) {
                        strcat(hosgeldinMesaji, inputkullaniciadi);
                        outtextxy(50, 320, hosgeldinMesaji);

                        delay(2000);
                        break;
                    } else {
                        outtextxy(50, 320, "Geçersiz kullanici adi veya sifre.");
                        delay(2000);
                        cleardevice();
                        rectangle(150, 200, 350, 250);
                        outtextxy(200, 220, "Giris");
                        rectangle(150, 300, 350, 350);
                        outtextxy(200, 320, "Kayit");
                    }
                }

                // Kayýt butonuna týklama
                else if (x >= 150 && x <= 350 && y >= 300 && y <= 350) {
                    cleardevice();
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(50, 150, "Kullanici Adi olusturun: ");
                    girdiAlindi(inputkullaniciadi, MaksUzunluk, 250, 150, 0);

                    outtextxy(50, 200, "Sifre olusturun: ");
                    girdiAlindi(inputsifre, MaksUzunluk, 250, 200, 1);

                    // Kullanýcý adýný ve þifreyi dosyaya kaydet
                    kayitOlustur(inputkullaniciadi, inputsifre);

                    outtextxy(50, 320, "Kayit basarili! Lutfen giris yapin.");
                    delay(2000);
                    cleardevice();
                    rectangle(150, 200, 350, 250);
                    outtextxy(200, 220, "Giris");
                    rectangle(150, 300, 350, 350);
                    outtextxy(200, 320, "Kayit");
                }
            }
            delay(100);  // Kýsa bir süre bekleyerek diðer iþlemlere de fýrsat ver
        }

        // Ana menü
        while (1) {
            cleardevice();
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(200, 50, "Gozluk Secimi");

            // Menü seçenekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // Çýkýþ butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");

            while (1) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    getmouseclick(WM_LBUTTONDOWN, x, y);

                    // Çocuk Gözlüðü
                    if (x >= 340 && x <= 740 && y >= 150 && y <= 200) {
                        animasyonMenu(0);
                        gozlukMenuleri("Cocuk Gozlugu");
                        rectangle(100, 150, 400, 200);
                        outtextxy(110, 170, "Barbie Gozluk");
                        rectangle(100, 210, 400, 260);
                        outtextxy(110, 230, "McQueen Gozluk");

                        while (1) {
                            if (ismouseclick(WM_LBUTTONDOWN)) {
                                getmouseclick(WM_LBUTTONDOWN, x, y);

                                // Barbie Gözlük
                                if (x >= 100 && x <= 400 && y >= 150 && y <= 200) {
                                    stoktanDus(0);
                                    animasyonMenu(3);
                                    delay(750);
                                    gozlukMenuleri("Cocuk Gozlugu");
                                    rectangle(100, 150, 400, 200);
                                    outtextxy(110, 170, "Barbie Gozluk");
                                    rectangle(100, 210, 400, 260);
                                    outtextxy(110, 230, "McQueen Gozluk");
                                }

                                // McQueen Gözlük
                                else if (x >= 100 && x <= 400 && y >= 210 && y <= 260) {
                                    stoktanDus(1);
                                    animasyonMenu(4);
                                    delay(750);
                                    gozlukMenuleri("Cocuk Gozlugu");
                                    rectangle(100, 150, 400, 200);
                                    outtextxy(110, 170, "Barbie Gozluk");
                                    rectangle(100, 210, 400, 260);
                                    outtextxy(110, 230, "McQueen Gozluk");
                                }

                                // Geri butonu
                                else if (x >= 100 && x <= 400 && y >= 360 && y <= 410) {
                                	animasyonMenu(9);
                                	cleardevice();
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(200, 50, "Gozluk Secimi");

            // Menü seçenekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // Çýkýþ butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");
                                    break;
                                }
                            }
                            delay(100);  // Kýsa bir süre bekleyerek diðer iþlemlere de fýrsat ver
                        }
                    }

                    // Erkek Gözlüðü
                    else if (x >= 340 && x <= 740 && y >= 250 && y <= 300) {
                        animasyonMenu(1);
                        gozlukMenuleri("Erkek Gozlugu");
                        rectangle(100, 150, 400, 200);
                        outtextxy(110, 170, "Ray Ban Gozluk");
                        rectangle(100, 210, 400, 260);
                        outtextxy(110, 230, "Mustang Gozluk");

                        while (1) {
                            if (ismouseclick(WM_LBUTTONDOWN)) {
                                getmouseclick(WM_LBUTTONDOWN, x, y);

                                // Ray Ban Gözlük
                                if (x >= 100 && x <= 400 && y >= 150 && y <= 200) {
                                    stoktanDus(2);
                                    animasyonMenu(5);
                                    delay(750);
                                    gozlukMenuleri("Erkek Gozlugu");
                                    rectangle(100, 150, 400, 200);
                                    outtextxy(110, 170, "Ray Ban Gozluk");
                                    rectangle(100, 210, 400, 260);
                                    outtextxy(110, 230, "Mustang Gozluk");
                                }

                                // Mustang Gözlük
                                else if (x >= 100 && x <= 400 && y >= 210 && y <= 260) {
                                    stoktanDus(3);
                                    animasyonMenu(6);
                                    delay(750);
                                    gozlukMenuleri("Erkek Gozlugu");
                                    rectangle(100, 150, 400, 200);
                                    outtextxy(110, 170, "Ray Ban Gozluk");
                                    rectangle(100, 210, 400, 260);
                                    outtextxy(110, 230, "Mustang Gozluk");
                                }

                                // Geri butonu
                                else if (x >= 100 && x <= 400 && y >= 360 && y <= 410) {
                                	cleardevice();
                                	animasyonMenu(9);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(200, 50, "Gozluk Secimi");

            // Menü seçenekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // Çýkýþ butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");
                                    break;
                                }
                            }
                            delay(100);  // Kýsa bir süre bekleyerek diðer iþlemlere de fýrsat ver
                        }
                    }

                    // Kadýn Gözlüðü
                    else if (x >= 340 && x <= 740 && y >= 350 && y <= 400) {
                        animasyonMenu(2);
                        gozlukMenuleri("Kadin Gozlugu");
                        rectangle(100, 150, 400, 200);
                        outtextxy(110, 170, "Osse Gozluk");
                        rectangle(100, 210, 400, 260);
                        outtextxy(110, 230, "Gusto Gozluk");

                        while (1) {
                            if (ismouseclick(WM_LBUTTONDOWN)) {
                                getmouseclick(WM_LBUTTONDOWN, x, y);

                                // Osse Gözlük
                                if (x >= 100 && x <= 400 && y >= 150 && y <= 200) {
                                    stoktanDus(4);
                                    animasyonMenu(7);
                                    delay(750);
                                    gozlukMenuleri("Kadin Gozlugu");
                                    rectangle(100, 150, 400, 200);
                                    outtextxy(110, 170, "Osse Gozluk");
                                    rectangle(100, 210, 400, 260);
                                    outtextxy(110, 230, "Gusto Gozluk");
                                }

                                // Gusto Gözlük
                                else if (x >= 100 && x <= 400 && y >= 210 && y <= 260) {
                                    stoktanDus(5);
                                    animasyonMenu(8);
                                    delay(750);
                                    gozlukMenuleri("Kadin Gozlugu");
                                    rectangle(100, 150, 400, 200);
                                    outtextxy(110, 170, "Osse Gozluk");
                                    rectangle(100, 210, 400, 260);
                                    outtextxy(110, 230, "Gusto Gozluk");
                                }

                                // Geri butonu
                                else if (x >= 100 && x <= 400 && y >= 360 && y <= 410) {
                                	cleardevice();
                                	animasyonMenu(9);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(200, 50, "Gozluk Secimi");

            // Menü seçenekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // Çýkýþ butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");
                                    break;
                                }
                            }
                            delay(100);  // Kýsa bir süre bekleyerek diðer iþlemlere de fýrsat ver
                        }
                    }

                    // Çýkýþ
                    else if (x >= 340 && x <= 740 && y >= 450 && y <= 500) {
                        closegraph();
                        exit(0);
                    }
                }
                delay(100);  // Kýsa bir süre bekleyerek diðer iþlemlere de fýrsat ver
            }
        }
    }

    closegraph();
    return 0;
}

