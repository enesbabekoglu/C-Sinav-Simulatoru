#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int N, S;
double B, D, HBN[100], ortalama, std, T_skoru[100], duzeyler_min[9], duzeyler_max[9];

void sinav_olustur(){

    int dwk; // Hata Yazisini Ekrana Bastirmak Icin Kullaniyoruz

    /* 
    
    Sinava Katilan Ogrenci Sayisini Gerekli Sartlari 
    Do While Dongusu Ile Kontrol Ettirerek Kullanicidan Aliyoruz 
    
    */

    do{

        if(dwk > 0){ // Eger dongu sartlarini sagliyorsa yani hata vermisse hata ciktisi ekrana yazar.
            printf("\nHATA! En az 1 en fazla 100 degeri girilebilir.\n");
        }
        
        printf("Sinava Katilan Ogrenci Sayisi (Max 100): ");
        scanf("%d", &N);

        dwk++;
        
    }while(N < 1 || N > 100);

    dwk = 0; // Her Donguden Sonra Diger Dongude Kullanabilmek Icin Kontrol Degiskenimizi Sifirliyoruz

    /* 
    
    Sinavdaki Soru Sayisini Gerekli Sartlari 
    Do While Dongusu Ile Kontrol Ettirerek Kullanicidan Aliyoruz 
    
    */

    do{

        if(dwk > 0){ // Eger dongu sartlarini sagliyorsa yani hata vermisse hata ciktisi ekrana yazar.
            printf("\nHATA! En az 1 en fazla 100 degeri girilebilir.\n");
        }
        
        printf("Sinavdaki Soru Sayisi (Max 100): ");
        scanf("%d", &S);
        
        dwk++;

    }while(S < 1 || S > 100);

    dwk = 0; // Her Donguden Sonra Diger Dongude Kullanabilmek Icin Kontrol Degiskenimizi Sifirliyoruz

    /* 
    
    Sinavdaki Sorularin Bos Birakilma Ihtimali Icin (0 ile 1 araliginda) Gerekli Sartlari 
    Do While Dongusu Ile Kontrol Ettirerek Kullanicidan Aliyoruz 
    
    */

    do{

        if(dwk > 0){
            printf("\nHATA! En az 0 en fazla 1 degeri girilebilir.\n");
        }
        
        printf("Sorunun Bos Birakilma Ihtimali (0 - 1 Arasi Giriniz): ");
        scanf("%lf", &B);

        dwk++;

    }while(B < 0 || B > 1);

    dwk = 0; // Her Donguden Sonra Diger Dongude Kullanabilmek Icin Kontrol Degiskenimizi Sifirliyoruz

    /* 
    
    Sinavdaki Sorularin Dogru Yapilma Ihtimali Icin (0 ile 1 araliginda) Gerekli Sartlari 
    Do While Dongusu Ile Kontrol Ettirerek Kullanicidan Aliyoruz 
    
    */

    do{

        if(dwk > 0){
            printf("\nHATA! En az 0 en fazla 1 degeri girilebilir.\n");
        }
        
        printf("Sorunun Dogru Yapilma Ihtimali (0 - 1 Arasi Giriniz): ");
        scanf("%lf", &D);

        dwk++;

    }while(D < 0 || D > 1);

    dwk = 0; // Her Donguden Sonra Diger Dongude Kullanabilmek Icin Kontrol Degiskenimizi Sifirliyoruz
    
}

void cevap_anahtari_uret(char cevap_anahtari[], int S){

    int cevap; // Rastgele Üreteceğimiz Cevaplar İçin Tanımladık

    srand(time(0)); // Sistem Saatine Göre Rastgele Sayı Üretmek İçin Kullanacağız

    for(int i = 0; i < S; i++){

        /* Burada Soruların Rastgele Üretilmiş Cevaplarını cevap_anahtari 
        Dizisine Kaydetmemiz İçin Soru Sayısı Kadar Döngü Başlatıyoruz */

        cevap = rand() % 5; // 0 - 4 Aralığında Rastgele Sayı Üretir

        switch(cevap){ // Burada Rastgele Üretilmiş Sayıya Denk Gelen Harfi cevap_anahtari Dizimize Yerleştiriyoruz
            case 0:
                cevap_anahtari[i] = 'A';
                break;
            case 1:
                cevap_anahtari[i] = 'B';
                break;
            case 2:
                cevap_anahtari[i] = 'C';
                break;
            case 3:
                cevap_anahtari[i] = 'D';
                break;
            default:
                cevap_anahtari[i] = 'E';
        }

    }

}

void cevap_anahtari_yazdir(char cevap_anahtari[], int S){ 
    
    /* 
    Bu Fonksiyon Rastgele Üretilmiş cevap_anahtari Dizimizi 
    Bir Döngü Yardımıyla Konsola Bastırır
    */

    printf("\nCEVAP ANAHTARI:\n");

    for(int i = 0; i < S; i++){
        printf("%.3d:%c | ", i+1, cevap_anahtari[i]); // Soruların Numaralarındırmasında Başına 0 Eklenmesi İçin .3d Yazdık
    }

    printf("\n");

}

void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D){

    /* 
    Bu Fonksiyonumuz Boş Bırakma, Doğru Cevap Verme Oranlarını 
    Göz Önünde Bulundurarak Öğrenci Sayısı Kadar Rastgele Bir Sınav 
    Oluşturur ve Öğrencilerin Cevaplarını ogrenci_cevaplari Dizisine Kaydeder
    */

    int cevap, dogruOrani, dogruMu, bosOrani, bosMu; // Bazı Gerekli Değişken Tanımlamalarını Yaptık

    srand(time(0)); // Sistem Saatine Göre Rastgele Sayı Üretmek İçin Kullanacağız

    bosOrani = B*100; // Bu Değişken Double Girdimiz Olan Boş Oranını 100 ile Çarparak Tam Sayı Haline Getiriyor
    dogruOrani = D*100; // Bu Değişken Double Girdimiz Olan Doğru Oranını 100 ile Çarparak Tam Sayı Haline Getiriyor

    for(int i = 0; i < N; i++){ // Öğrenci Sayısı Kadar Dönen Döngü

        for(int j = 0; j < S; j++){ // Soru Sayısı Kadar Dönen Döngü

            bosMu = rand() % 100 + 1; // 1 - 100 Aralığında Rastgele Bir Sayı Döndürür

            if(bosOrani >= bosMu){ // Eğer Rastgele Dönen Sayı bosOrani Değişkeninden Küçük yada Eşitse Soru Boştur

                ogrenci_cevaplari[i][j] = 'X';

            }else{ // Değilse Soru Ya Doğrudur Ya Yanlış

                dogruMu = rand() % 100 + 1; // 1 - 100 Aralığında Rastgele Bir Sayı Döndürür

                if(dogruOrani >= dogruMu){ 
                    
                    /* 
                    Eğer Rastgele Dönen Sayı dogruOrani Değişkeninden Küçük yada Eşitse Soru Doğrudur 
                    Bu Durumda cevap_anahtari Dizisinden Soru Indis Numarasına Denk Gelen Cevabı Öğrenciye Kaydediyoruz
                    */

                    ogrenci_cevaplari[i][j] = cevap_anahtari[j];

                }else{ // Burası Soruya Yanlış Cevap Verilecekse Çalışır

                    for(;;){ // Soruya Doğru Cevap Verilmeyene Kadar Çalışan Döngü

                        cevap = rand() % 5; // 0 - 4 Aralığında Rastgele Sayı Üretir

                        if(cevap == 0 && cevap_anahtari[j] == 'A' || cevap == 1 && cevap_anahtari[j] == 'B' || cevap == 2 && cevap_anahtari[j] == 'C' || cevap == 3 && cevap_anahtari[j] == 'D' || cevap == 4 && cevap_anahtari[j] == 'E'){

                            /* Eğer Cevap Anahtarındaki Cevap ile Rastgele Çıkan 
                            Cevap Aynıysa Döngünün Bir Sonraki Adımına Geçer */

                            cevap = rand() % 5; // 0 - 4 Aralığında Rastgele Sayı Üretir
                            continue; // Sonraki Adıma Geç

                        }else{ // Eğer Doğru Cevap Denk Gelmemişse

                            switch(cevap){ // Çıkan Cevaba Denk Gelen Harfi Öğrencinin Cevap Anahtarı Dizisine Kaydeder
                                case 0:
                                    ogrenci_cevaplari[i][j] = 'A';
                                    break;
                                case 1:
                                    ogrenci_cevaplari[i][j] = 'B';
                                    break;
                                case 2:
                                    ogrenci_cevaplari[i][j] = 'C';
                                    break;
                                case 3:
                                    ogrenci_cevaplari[i][j] = 'D';
                                    break;
                                default:
                                    ogrenci_cevaplari[i][j] = 'E';
                            }

                            break; // Sonsuz For Döngüsünü Sonlandırır

                        }

                    }

                }

            }

        }

    }

}

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S){

    /* Bu Dizi Indis Numarası (ogrenci_ID) Gönderilen 
    Oyuncunun Cevap Anahtarlarını Diziden Alıp Konsola Basar */

    printf("\n%.3d. Ogrencinin Cevaplari:\n", ogrenci_ID+1);

    for(int j = 0; j < S; j++){ // Soru Dongusu

        printf("%.3d:%c | ", j+1, ogrenci_cevaplari[ogrenci_ID][j]);

    }

}

void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S){

    double soruPuan = 100/S, ogrenciPuan; // Soru Başına Düşen Puanı Belirliyoruz
    int dogruSayisi = 0, yanlisSayisi = 0, bosSayisi = 0; // Öğrencinin D/Y/B Değerlerini Saydıracağız

    for(int ogrenci_ID = 0; ogrenci_ID < N; ogrenci_ID++){ // Öğrenci Sayısı Kadar Dönen Döngü

        for(int soru_ID = 0; soru_ID < S; soru_ID++){ // Soru Sayısı Kadar Dönen Döngü

            if(ogrenci_cevaplari[ogrenci_ID][soru_ID] == cevap_anahtari[soru_ID]){ // Eğer Cevap Anahtarıyla Aynıysa
                dogruSayisi++; // Doğru Sayısını 1 Arttır
            }else if(ogrenci_cevaplari[ogrenci_ID][soru_ID] == 'X'){ // Eğer Cevabı Boşsa
                bosSayisi++; // Boş Sayısını 1 Arttır
            }else{ // Eğer Cevabı Yanlışsa
                yanlisSayisi++; // Yanlış Sayısını 1 Arttır
            }

        }

        /* 
        Öğrenci Puanı Hesaplaması Yapıyoruz
        4 Yanlış 1 Doğruyu Götürmesi Gerektiğinden Yanlış Sayımızı 
        4'e Bölüyoruz ve Doğru Sayımızdan Çıkartıyoruz Çıkan Sonucu
        Soru Başına Düşen Puan İle Çarpıyoruz
        */
        
        ogrenciPuan = (dogruSayisi-(yanlisSayisi/4))*soruPuan;

        if(ogrenciPuan > 0){ // Eğer Öğrenci Puanı 0'dan Büyük Çıkarsa Aynen HBN Dizisinde Kaydediyoruz
            HBN[ogrenci_ID] = ogrenciPuan;
        }else{ // Değilse En Az 0 Olması Gerektiğinden 0 Olarak Kaydediyoruz
            HBN[ogrenci_ID] = 0;
        }

        /* Tüm Değerleri Bir Sonraki Öğrencide Kullanabilmek İçin Sıfırlıyoruz */

        dogruSayisi = 0;
        yanlisSayisi = 0;
        bosSayisi = 0;

    }

}

double sinif_ortalamasi_hesapla(double HBN[], int N){

    /* Bu Fonksiyonda Sınıf Ortalamasını Ortalama Formülünü Kullanarak Hesaplıyoruz ve Döndürüyoruz */
    
    double toplamPuan = 0;

    for(int ogrenci_ID = 0; ogrenci_ID < N; ogrenci_ID++){

        toplamPuan += HBN[ogrenci_ID];

    }

    return toplamPuan/N;

}

double standart_sapma_hesapla(double ortalama, double HBN[], int N){

    /* Bu Fonksiyonda Sınıfın Standart Sapmasını Standart Sapma Formülünü Kullanarak Hesaplıyoruz ve Döndürüyoruz */

    double standartSapma = 0, toplam = 0;

    for(int ogrenci_ID = 0; ogrenci_ID < N; ogrenci_ID++){

        toplam += pow((HBN[ogrenci_ID]-ortalama), 2);

    }

    standartSapma = sqrt(toplam / (N-1));

    return standartSapma;

}

void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]){

    /* Öğrenci Sayısı Kadar Bir Dizi Döndürüp T_skoru Formülünü Uyguluyoruz ve T_skoru Dizisine Tek Tek Kaydediyoruz */

    printf("\n");

    for(int ogrenci_ID = 0; ogrenci_ID < N; ogrenci_ID++){
        T_skoru[ogrenci_ID] = 60 + 10 * (HBN[ogrenci_ID] - ortalama) / std;
    }

}

void sinif_duzeyi(double ortalama){

    /* Bu Fonksiyonumuz Sınıfımızın Düzeyini Verilen Tabloya Göre Ortalama Bilgisini Kullanarak Kontrol Ediyor */

    int ekstra; // Tablodaki Aralıklara Göre Artış Yapmak İçin ekstra Değişkenini Tanımladık

    if(ortalama > 80 && ortalama <= 100){
        printf("\nSinif Duzeyi: Ustun Basari\n\n");
        ekstra = 0;
    }else if(ortalama > 70 && ortalama <= 80){
        printf("\nSinif Duzeyi: Mukemmel\n\n");
        ekstra = 2;
    }else if(ortalama > 62.5 && ortalama <= 70){
        printf("\nSinif Duzeyi: Cok Iyi\n\n");
        ekstra = 4;
    }else if(ortalama > 57.5 && ortalama <= 62.5){
        printf("\nSinif Duzeyi: Iyi\n\n");
        ekstra = 6;
    }else if(ortalama > 52.5 && ortalama <= 57.5){
        printf("\nSinif Duzeyi: Ortanin Ustu\n\n");
        ekstra = 8;
    }else if(ortalama > 47.5 && ortalama <= 52.5){
        printf("\nSinif Duzeyi: Orta\n\n");
        ekstra = 10;
    }else if(ortalama > 42.5 && ortalama <= 47.5){
        printf("\nSinif Duzeyi: Zayif\n\n");
        ekstra = 12;
    }else{
        printf("\nSinif Duzeyi: Kotu\n\n");
        ekstra = 14;
    }

    for(int harf_id = 0; harf_id < 9; harf_id++){ // Harf Sayısı Kadar Döndürüyoruz

        duzeyler_min[harf_id] = 27+(harf_id*5)+ekstra; // Bu Harfe Denk Gelen Minimum Puan Değerini duzeyler_min Dizimize Kaydediyoruz
        duzeyler_max[harf_id] = 32+(harf_id*5)+ekstra; // Bu Harfe Denk Gelen Maksimum Puan Değerini duzeyler_max Dizimize Kaydediyoruz

        if(harf_id == 0){ // Eğer Harf FF ise Minimum Değerini 0 Olarak Güncelliyoruz
            duzeyler_min[harf_id] = 0;
        }

        if(harf_id == 8){ // Eğer Harf AA ise Maksimum Değerini 100 Olarak Güncelliyoruz
            duzeyler_max[harf_id] = 100;
        }

    }

}

void harflendir(int harf_id){

    /* Bu Fonksiyon Ekrana Gelen Harf ID Değerine Göre Harfi Çıktı Olarak Konsola Yazar */

    if(harf_id == 0){
        printf("FF");
    }else if(harf_id == 1){
        printf("FD");
    }else if(harf_id == 2){
        printf("DD");
    }else if(harf_id == 3){
        printf("DC");
    }else if(harf_id == 4){
        printf("CC");
    }else if(harf_id == 5){
        printf("CB");
    }else if(harf_id == 6){
        printf("BB");
    }else if(harf_id == 7){
        printf("BA");
    }else{
        printf("AA");
    }

}

void ogrenci_notlari(double HBN[], int N, double T_skoru[]){

    /* Öğrencilerin HBN, T-Skoru ve Harf Notlarını Ekrana Yazdırıyoruz */

    int harf_id = 0;

    for(int ogrenci_ID = 0; ogrenci_ID < N; ogrenci_ID++){

        printf("\n%.3d. Ogrencinin HBN: %.2lf, T-Skoru: %.2lf, Harf Notu: ", ogrenci_ID+1, HBN[ogrenci_ID], T_skoru[ogrenci_ID]);

        while(harf_id < 9){ // Harf Sayımız Kadar Dönen Bir Döngü Oluşturuyoruz

            if(T_skoru[ogrenci_ID] >= duzeyler_min[harf_id] && T_skoru[ogrenci_ID] < duzeyler_max[harf_id]){
                /* Eğer Öğrencinin T-Skoru Harf Min ve Harf Max Arasındaysa harflendir Fonksiyonunun İçine Bu Harfi Gönderiyoruz*/
                harflendir(harf_id);
                break; // Şart Sağlandığı İçin Döngüden Çıkıyoruz
            }

            harf_id++;

        }

        harf_id = 0; // Her Öğrenci İçin Kontrol Yapacağımızdan Sıfırlıyoruz

    }

}

void main(){
    
    char cevap_anahtari[100], ogrenci_cevaplari[100][100];

    sinav_olustur(); // Sınav Girdilerini Alıyoruz
    cevap_anahtari_uret(cevap_anahtari, S); // Cevap Anahtarı Üretiyoruz
    cevap_anahtari_yazdir(cevap_anahtari, S); // Cevap Anahtarını Konsola Bastırıyoruz
    sinavi_uygula(ogrenci_cevaplari, cevap_anahtari, N, S, B, D); // Sınavı Öğrencilere Uyguluyoruz

    for(int ogrenci_ID = 0; ogrenci_ID < N; ogrenci_ID++){ // Öğrenci Sayısı Kadar Döner
        ogrenci_cevabini_yazdir(ogrenci_cevaplari, ogrenci_ID, S); // Öğrencinin Cevabını Konsola Yazdıran Fonksiyon
    }

    ogrencileri_puanla(ogrenci_cevaplari, cevap_anahtari, HBN, N, S); // Öğrencilerin Puanlarını Hesaplatıyoruz

    ortalama = sinif_ortalamasi_hesapla(HBN, N); // Sınıf Ortalamasını Çekiyoruz
    std = standart_sapma_hesapla(ortalama, HBN, N); // Sınıfın Standart Sapmasını Çekiyoruz
    T_skoru_hesapla(ortalama, HBN, N, std, T_skoru); // Her Öğrenci İçin T-Skoru Hesaplatan Fonksiyonu Çalıştırıyoruz

    printf("\n\nSinif Ortalamasi: %.2lf, Standart Sapma: %.2lf", ortalama, std); // Sınıfın Bilgilerini Yazıyoruz
    
    sinif_duzeyi(ortalama); // Sınıf Düzeyini Ortalama Bilgisini Göndererek Ekrana Yazdırıyoruz

    ogrenci_notlari(HBN, N, T_skoru); // Öğrencilerin Puan Tablosunu Konsole Yazdırıyoruz

}

