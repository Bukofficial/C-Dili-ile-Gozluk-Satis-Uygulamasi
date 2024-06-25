#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

#define MaksUzunluk 50
#define gozlukStoklari 6

int stocks[gozlukStoklari] = {0}; // Stoklar� tutacak dizi
const char *gozlukStok = "stok.txt";

const int ekranGenislik = 1080;  // �rne�in, 1080x720 ��z�n�rl�k
const int ekranYukseklik = 720;

// Kullan�c�dan metin giri�i almak i�in yard�mc� fonksiyon
void girdiAlindi(char *input, int maxLength, int x, int y, int issifre) {
    int i = 0;
    char ch;
    while (1) {
        if (kbhit()) {  // Klavyeden bir tu� bas�ld� m� kontrol et
            ch = getch();
            if (ch == 13) { // Enter tu�u
                input[i] = '\0';
                break;
            } else if (ch == 8 && i > 0) { // Backspace tu�u
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
        delay(100);  // K�sa bir s�re bekleyerek di�er i�lemlere de f�rsat ver
    }
}

// Kullan�c� ad� ve �ifreyi dosyaya kaydetme
void kayitOlustur(const char *kullaniciadi, const char *sifre) {
    FILE *file = fopen("gozluk.txt", "a");
    if (file == NULL) {
        printf("Dosya a�ma hatas�!\n");
        return;
    }
    fprintf(file, "%s %s\n", kullaniciadi, sifre);
    fclose(file);
}

// Kullan�c� ad� ve �ifre do�rulama
int kullaniciDogrula(const char *kullaniciadi, const char *sifre) {
    FILE *file = fopen("gozluk.txt", "r");
    if (file == NULL) {
        printf("Dosya a�ma hatas�!\n");
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

// Stoklar� dosyadan y�kleme
void stokCekme() {
    FILE *file = fopen(gozlukStok, "r");
    if (file == NULL) {
        printf("Stok dosyas� a�ma hatas�!\n");
        return;
    }
    for (int i = 0; i < gozlukStoklari; i++) {
        fscanf(file, "%d", &stocks[i]);
    }
    fclose(file);
}

// Stoklar� dosyaya kaydetme
void stokKaydet() {
    FILE *file = fopen(gozlukStok, "w");
    if (file == NULL) {
        printf("Stok dosyas� a�ma hatas�!\n");
        return;
    }
    for (int i = 0; i < gozlukStoklari; i++) {
        fprintf(file, "%d\n", stocks[i]);
    }
    fclose(file);
}
// G�zl�k stoklar�n� azaltan fonksiyon
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

// G�zl�k se�im men�s� i�lemleri
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
            outtextxy(350, 350, "�ocuk G�zl��� Se�ildi");
            break;
        case 1:
            outtextxy(350, 350, "Erkek G�zl��� Se�ildi");
            break;
        case 2:
            outtextxy(350, 350, "Kad�n G�zl��� Se�ildi");
            break;
        case 3:
            outtextxy(350, 350, "Barbie G�zl��� Sat�n Al�nd�!");
            break;
        case 4:
            outtextxy(350, 350, "McQueen G�zl��� Sat�n Al�nd�!");
            break;
        case 5:
            outtextxy(350, 350, "Ray Ban G�zl��� Sat�n Al�nd�!");
            break;
        case 6:
            outtextxy(350, 350, "Mustang G�zl��� Sat�n Al�nd�!");
            break;
        case 7:
            outtextxy(350, 350, "Osse G�zl��� Sat�n Al�nd�!");
            break;
        case 8:
            outtextxy(350, 350, "Gusto G�zl��� Sat�n Al�nd�!");
            break;
        case 9:
        	outtextxy(350,350, "Geri Tu�una Bas�ld�!");
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

// Ana men� i�lemleri
int main() {
    int gd = DETECT, gm;
    initwindow(ekranGenislik, ekranYukseklik, "Tam Ekran Grafik Penceresi");

    // Stoklar� y�kle
    stokCekme();

    char inputkullaniciadi[MaksUzunluk];
    char inputsifre[MaksUzunluk];

    // Giri� ve kay�t butonlar�
    while (1) {
        cleardevice();
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(200, 100, "Giris ve Kayit");

        // Giri� butonu
        rectangle(150, 200, 350, 250);
        outtextxy(200, 220, "Giris");

        // Kay�t butonu
        rectangle(150, 300, 350, 350);
        outtextxy(200, 320, "Kayit");

        int x, y;
        while (1) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                // Giri� butonuna t�klama
                if (x >= 150 && x <= 350 && y >= 200 && y <= 250) {
                    cleardevice();
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(50, 150, "Kullanici Adi: ");
                    girdiAlindi(inputkullaniciadi, MaksUzunluk, 200, 150, 0);

                    outtextxy(50, 200, "Sifre: ");
                    girdiAlindi(inputsifre, MaksUzunluk, 200, 200, 1);

                    char hosgeldinMesaji[MaksUzunluk + 20] = "Hosgeldiniz, ";

                    // E�er giri� ba�ar�l�ysa kullan�c� ad�n� kar��lama mesaj�na ekleyin
                    if (kullaniciDogrula(inputkullaniciadi, inputsifre)) {
                        strcat(hosgeldinMesaji, inputkullaniciadi);
                        outtextxy(50, 320, hosgeldinMesaji);

                        delay(2000);
                        break;
                    } else {
                        outtextxy(50, 320, "Ge�ersiz kullanici adi veya sifre.");
                        delay(2000);
                        cleardevice();
                        rectangle(150, 200, 350, 250);
                        outtextxy(200, 220, "Giris");
                        rectangle(150, 300, 350, 350);
                        outtextxy(200, 320, "Kayit");
                    }
                }

                // Kay�t butonuna t�klama
                else if (x >= 150 && x <= 350 && y >= 300 && y <= 350) {
                    cleardevice();
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(50, 150, "Kullanici Adi olusturun: ");
                    girdiAlindi(inputkullaniciadi, MaksUzunluk, 250, 150, 0);

                    outtextxy(50, 200, "Sifre olusturun: ");
                    girdiAlindi(inputsifre, MaksUzunluk, 250, 200, 1);

                    // Kullan�c� ad�n� ve �ifreyi dosyaya kaydet
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
            delay(100);  // K�sa bir s�re bekleyerek di�er i�lemlere de f�rsat ver
        }

        // Ana men�
        while (1) {
            cleardevice();
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(200, 50, "Gozluk Secimi");

            // Men� se�enekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // ��k�� butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");

            while (1) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    getmouseclick(WM_LBUTTONDOWN, x, y);

                    // �ocuk G�zl���
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

                                // Barbie G�zl�k
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

                                // McQueen G�zl�k
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

            // Men� se�enekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // ��k�� butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");
                                    break;
                                }
                            }
                            delay(100);  // K�sa bir s�re bekleyerek di�er i�lemlere de f�rsat ver
                        }
                    }

                    // Erkek G�zl���
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

                                // Ray Ban G�zl�k
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

                                // Mustang G�zl�k
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

            // Men� se�enekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // ��k�� butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");
                                    break;
                                }
                            }
                            delay(100);  // K�sa bir s�re bekleyerek di�er i�lemlere de f�rsat ver
                        }
                    }

                    // Kad�n G�zl���
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

                                // Osse G�zl�k
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

                                // Gusto G�zl�k
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

            // Men� se�enekleri
            rectangle(340, 150, 740, 200);
            outtextxy(360, 170, "Cocuk Gozlugu");

            rectangle(340, 250, 740, 300);
            outtextxy(360, 270, "Erkek Gozlugu");

            rectangle(340, 350, 740, 400);
            outtextxy(360, 370, "Kadin Gozlugu");

            // ��k�� butonu
            rectangle(340, 450, 740, 500);
            outtextxy(360, 470, "Cikis");
                                    break;
                                }
                            }
                            delay(100);  // K�sa bir s�re bekleyerek di�er i�lemlere de f�rsat ver
                        }
                    }

                    // ��k��
                    else if (x >= 340 && x <= 740 && y >= 450 && y <= 500) {
                        closegraph();
                        exit(0);
                    }
                }
                delay(100);  // K�sa bir s�re bekleyerek di�er i�lemlere de f�rsat ver
            }
        }
    }

    closegraph();
    return 0;
}

