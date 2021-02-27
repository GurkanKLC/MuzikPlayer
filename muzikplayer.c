/*
Bu projede komut girdisi içerisindeki komutlarýn sorunsuz uygulanabilmesi için çift yönlü dairesel linkedlist kullanýlmýþtýr.
Insersong komutu uygulanýrken linkedlist kontrol edilmiþ ve ilk kez ekleme yapýlýyor ise ilk düðüm oluþturulmuþ, sonrakiler için düðüm koparýlýp arasýna ekleme yapýlmýþtýr.
PrintPlaylist komutu linkedlist içerisindeki tüm elemanlarý gelen parametreye göre ter herseferinde next'i yada prev'i yazdýrarak listeyi aktarýr.
ReversePlaysong komutu liste yazdýrma komutu ile birlikte çalýþýr ancak liste baþtan sona yazarken reverse yazýlanlarý sondan baþa doðru yeni listeye aktarýr.Eski liste býrakýlýr.
MoveSong komutu ile linkedlist içerisinde liste baþýný kaybetmeden 2 dügüm arasýnda düðüm koparma ve ekleme yaparak yer deðiþtirme yapar.
RemoveSong silinmesi istenilen þarký aktif çalan deðil ise linkedlist içerisinden bularak düðümü koparýp öncesini ve sonrasýný birbirine baðlar ardýndan silinecek olaný serbest býrakýr.
Playsong komutu gelen parametreye baðlý olarak listeden þarký çalmaya baþlar,her parametrede aktif þarký düðümünün next'ine yada prev'ine gider;
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct song
{
    char song[50];
    struct song* next;
    struct song* prev;
} node;
char playingsong[50];
int playkontrol=0;
node* basaekle(node * listebasi,char gelensong[50]);
node* sonaekle(node * listebasi,char gelensong[50]);
node * sonrasinatasi(node * listebasi,char tasinacaksong[50],char capasong[50]);
node * basinatasi(node * listebasi,char tasinacaksong[50],char capasong[50]);
node * silme(node* listebasi,char silineceksong[50]);
node * reverse(node* listebasi);
void playsong(node * listebasi,char komut[5]);
void listele(node* listebasi);
void terslistele(node* listebasi);
int main(int argc, char *argv[])
{
    FILE *f = fopen("output.txt", "w");
    fclose(f);
    node * anadugum;
    anadugum=NULL;
    FILE *input;
    char satir[50],komut[20],komutkodu,sarkiA[50],sarkiB[50];
    input=fopen("input.txt","r");
    while(fscanf(input,"%[^\n]\n",&satir) !=EOF)
    {
        int kbs=0;
        char* komut2[50];
        char* isim;
        isim=strtok(satir,"\t");
        while(isim!=NULL)
        {
            komut2[kbs]=isim;
            isim=strtok(NULL,"\t");
            kbs++;
        }
        if(strcmp("ReversePlaylist",komut2[0]) == 0)
        {
        anadugum=reverse(anadugum);
        }
        else if(strcmp("PrintPlaylist",komut2[0]) == 0)
        {
            if(strcmp("F",komut2[1]) == 0)
            {
                listele(anadugum);
            }
            else if(strcmp("R",komut2[1]) == 0)
            {
                terslistele(anadugum);
            }
        }
        else if(strcmp("PlaySong",komut2[0]) == 0)
        {
            playsong(anadugum,komut2[1]);
        }
        else if(strcmp("InsertSong",komut2[0]) == 0)
        {
            if(strcmp("H",komut2[1]) == 0)
            {
               anadugum=basaekle(anadugum,komut2[2]);
            }
            else if(strcmp("T",komut2[1]) == 0)
            {
                anadugum=sonaekle(anadugum,komut2[2]);
            }
        }
        else if(strcmp("MoveSong",komut2[0]) == 0)
        {
            if(strcmp("A",komut2[1]) == 0)
            {
                anadugum=sonrasinatasi(anadugum,komut2[2],komut2[3]);
            }
            else if(strcmp("B",komut2[1]) == 0)
            {
                anadugum=basinatasi(anadugum,komut2[2],komut2[3]);

            }
        }
        else if(strcmp("RemoveSong",komut2[0]) == 0)
        {
            anadugum=silme(anadugum,komut2[1]);
        }

    }
    return 0;

}
node* basaekle(node * listebasi,char gelensong[50])
{
    if(listebasi==NULL)
    {
        listebasi=(node*)malloc(sizeof(node));
        listebasi-> next=listebasi;
        listebasi-> prev=listebasi;
        strcpy( listebasi-> song,gelensong);
        return listebasi;
    }
    else
    {
        node * adetkontrol;
        adetkontrol=listebasi->next;
        int dugumadet=0;
        while(adetkontrol->song!=listebasi->song)
        {
            dugumadet++;
            adetkontrol=adetkontrol->next;

        }

        if(dugumadet==0)
        {
            node * eklenecek;
            eklenecek=(node*)malloc(sizeof(node));
            strcpy( eklenecek-> song,gelensong);
            eklenecek->next=listebasi;
            eklenecek->prev=listebasi;
            listebasi->next=eklenecek;
            listebasi->prev=eklenecek;
            return eklenecek;
        }
        else
        {
            node * soneleman;
            soneleman=adetkontrol->prev;
            node * eklenecek;
            eklenecek=(node*)malloc(sizeof(node));
            strcpy( eklenecek-> song,gelensong);
            eklenecek->next=listebasi;
            eklenecek->prev=soneleman;
            listebasi->prev=eklenecek;
            soneleman->next=eklenecek;
            return eklenecek;
        }
    }
}
node* sonaekle(node * listebasi,char gelensong[50])
{
    if(listebasi==NULL)
    {
        listebasi=(node*)malloc(sizeof(node));
        listebasi-> next=listebasi;
        listebasi-> prev=listebasi;
        strcpy( listebasi-> song,gelensong);
        return listebasi;
    }
    else
    {
        node * adetkontrol;
        adetkontrol=listebasi->next;
        int dugumadet=0;
        while(adetkontrol->song!=listebasi->song)
        {
            dugumadet++;
            adetkontrol=adetkontrol->next;
        }
        if(dugumadet==0)
        {
            node * eklenecek;
            eklenecek=(node*)malloc(sizeof(node));
            strcpy( eklenecek-> song,gelensong);
            eklenecek->prev=listebasi;
            eklenecek->next=listebasi;
            listebasi->prev=eklenecek;
            listebasi->next=eklenecek;
            return listebasi;
        }
        else
        {
            node * soneleman;
            soneleman=adetkontrol->prev;
            node * eklenecek;
            eklenecek=(node*)malloc(sizeof(node));
            strcpy( eklenecek-> song,gelensong);
            eklenecek->next=listebasi;
            eklenecek->prev=soneleman;
            listebasi->prev=eklenecek;
            soneleman->next=eklenecek;
            return listebasi;
        }
    }

}
void listele(node * listebasi)
{
    if(listebasi!=NULL)
    {
        FILE *f = fopen("output.txt", "a+");
        node * adetkontrol;
        adetkontrol=listebasi;
        fprintf(f, "%s\n", adetkontrol->song);
        listebasi=listebasi->next;
        while(listebasi!=adetkontrol)
        {
            fprintf(f, "%s\n", listebasi->song);
            listebasi=listebasi->next;

        }
        fprintf(f, "%s\n", "*****");
        fclose(f);
    }
    else
    {
        FILE *f = fopen("output.txt", "a+");
        fprintf(f, "%s\n", "No Songs To Print");
        fprintf(f, "%s\n", "*****");
        fclose(f);
    }

}
void terslistele(node * listebasi)
{
    if(listebasi!=NULL)
    {
        FILE *f = fopen("output.txt", "a+");
        node * adetkontrol;
        adetkontrol=listebasi->prev;
        fprintf(f, "%s\n", adetkontrol->song);
        listebasi=adetkontrol->prev;
        while(listebasi!=adetkontrol)
        {
            fprintf(f, "%s\n", listebasi->song);
            listebasi=listebasi->prev;
        }
        fprintf(f, "%s\n", "*****");
        fclose(f);
    }
    else
    {
        FILE *f = fopen("output.txt", "a+");
        fprintf(f, "%s\n", "No Songs To Print");
        fprintf(f, "%s\n", "*****");
        fclose(f);
    }

}
node * sonrasinatasi(node * listebasi,char tasinacaksong[50],char capasong[50])
{
    node * tasinacakdugum;
    tasinacakdugum=NULL;
    node * adetkontrol;
    adetkontrol=listebasi;

    if(strcmp(listebasi->song,tasinacaksong) == 0)
    {
        tasinacakdugum=listebasi;
        node * sondugum;
        sondugum=listebasi->prev;
        node * ilkdugum;
        ilkdugum=listebasi->next;
        sondugum->next=listebasi->next;
        ilkdugum->prev=listebasi->prev;
        node * capadugum;
        while(strcmp(listebasi->song,capasong) != 0)
        {
            if(strcmp(listebasi->next->song,capasong) == 0)
            {
                capadugum=listebasi->next;
            }
            listebasi=listebasi->next;
        }
        tasinacakdugum->prev=capadugum;
        tasinacakdugum->next=capadugum->next;
        capadugum->next->prev=tasinacakdugum;
        capadugum->next=tasinacakdugum;
        return ilkdugum;
    }
    else
    {
        int kontroller=0;
        node * baslangic;
        baslangic=listebasi;


        if(strcmp(baslangic->prev->song,capasong) != 0)
        {
            adetkontrol=listebasi->prev;
            while(listebasi!=adetkontrol)
            {
                if(strcmp(listebasi->next->song,tasinacaksong) == 0)
                {
                    tasinacakdugum=listebasi->next;

                }
                listebasi=listebasi->next;

            }
            listebasi=listebasi->next;
            node * capadugum;
            adetkontrol=listebasi->prev;
            while(listebasi!=adetkontrol)
            {

                if(strcmp(listebasi->song,capasong) == 0)
                {
                    capadugum=listebasi;
                }
                listebasi=listebasi->next;
            }
            listebasi=listebasi->next;
            tasinacakdugum->prev->next=tasinacakdugum->next;
            tasinacakdugum->next->prev=tasinacakdugum->prev;
            node * capasonrasi;
            capasonrasi=capadugum->next;
            tasinacakdugum->next=capasonrasi;
            tasinacakdugum->prev=capadugum;
            capadugum->next=tasinacakdugum;
            capasonrasi->prev=tasinacakdugum;
            return baslangic;
        }
        else
        {
            while(listebasi->next!=adetkontrol)
            {

                if(strcmp(listebasi->song,tasinacaksong) == 0)
                {
                    tasinacakdugum=listebasi;
                }
                listebasi=listebasi->next;
            }
            tasinacakdugum->prev->next=tasinacakdugum->next;
            tasinacakdugum->next->prev=tasinacakdugum->prev;
            node *capadugum;
            capadugum=baslangic->prev;
            tasinacakdugum->next=baslangic;
            tasinacakdugum->prev=capadugum;
            baslangic->prev=tasinacakdugum;
            capadugum->next=tasinacakdugum;
            return baslangic;
        }



    }
}
node * basinatasi(node * listebasi,char tasinacaksong[50],char capasong[50])
{
    node * tasinacakdugum;
    tasinacakdugum=NULL;
    node * adetkontrol;
    adetkontrol=listebasi;

    if(strcmp(listebasi->song,tasinacaksong) == 0)
    {
        tasinacakdugum=listebasi;
        node * baslangic;
        baslangic=listebasi->next;
        node * sondugum;
        sondugum=listebasi->prev;
        sondugum->next=baslangic;
        baslangic->prev=sondugum;
        node * capadugum;

        while(strcmp(listebasi->song,capasong) != 0)
        {
            if(strcmp(listebasi->next->song,capasong) == 0)
            {
                capadugum=listebasi->next;
            }
            listebasi=listebasi->next;
        }
        tasinacakdugum->prev=capadugum->prev;
        tasinacakdugum->next=capadugum;
        capadugum->prev->next=tasinacakdugum;
        capadugum->prev=tasinacakdugum;
        return baslangic;
    }
    else
    {

        if(strcmp(listebasi->song,capasong) == 0)
        {

            node * baslangic;
            baslangic=listebasi;

            while(strcmp(listebasi->song,tasinacaksong) != 0)
            {
                if(strcmp(listebasi->next->song,tasinacaksong) == 0)
                {
                    tasinacakdugum=listebasi->next;

                }
                listebasi=listebasi->next;
            }
            node* sondugum;
            sondugum=baslangic->prev;
            tasinacakdugum->prev->next=tasinacakdugum->next;
            tasinacakdugum->next->prev=tasinacakdugum->prev;
            node* capadugum;
            capadugum=baslangic;
            node *capaoncesi;
            capaoncesi=baslangic->prev;
            tasinacakdugum->prev=capaoncesi;
            tasinacakdugum->next=capadugum;
            capaoncesi->next=tasinacakdugum;
            capadugum->prev=tasinacakdugum;
            return tasinacakdugum;
        }
        else
        {
            node * baslangic;
            baslangic=listebasi;
            adetkontrol=listebasi->prev;
            if(strcmp(adetkontrol->song,tasinacaksong) == 0)
            {
                tasinacakdugum=adetkontrol;
            }
            while(listebasi->next!=adetkontrol)
            {
                if(strcmp(listebasi->next->song,tasinacaksong) == 0)
                {
                    tasinacakdugum=listebasi->next;
                }
                listebasi=listebasi->next;
            }
            listebasi=listebasi->next;
            node * capadugum;
            while(strcmp(listebasi->song,capasong) != 0)
            {
                if(strcmp(listebasi->next->song,capasong) == 0)
                {
                    capadugum=listebasi->next;
                }
                listebasi=listebasi->next;
            }

            tasinacakdugum->prev->next=tasinacakdugum->next;
            tasinacakdugum->next->prev=tasinacakdugum->prev;

            node * capaoncesi;
            capaoncesi=capadugum->prev;
            tasinacakdugum->next=capadugum;
            tasinacakdugum->prev=capaoncesi;
            capadugum->prev=tasinacakdugum;
            capaoncesi->next=tasinacakdugum;
            return baslangic;
        }
    }
}
node * silme(node* listebasi,char silineceksong[50])
{
    if(listebasi!=NULL)
    {
        node * adetkontrol;
        adetkontrol=listebasi->prev;
        node * sarki;
        sarki=NULL;

        if(strcmp(adetkontrol->song,playingsong) == 0)
        {

            sarki=adetkontrol;
        }
        while(listebasi!=adetkontrol)
        {

            if(strcmp(listebasi->song,playingsong) == 0)
            {

                sarki=listebasi;

            }
            listebasi=listebasi->next;
        }
        if(sarki!=NULL)
        {
            if(strcmp(sarki->song,silineceksong) == 0)
            {
                FILE *f = fopen("output.txt", "a+");
                fprintf(f, "%s\n", "Cannot Remove The Playing Song");
                fprintf(f, "%s\n", "*****");
                fclose(f);
                return listebasi;
            }
            else
            {

                if(strcmp(listebasi->song,silineceksong) == 0)
                {
                    node * silinecekdugum;
                    silinecekdugum=listebasi;
                    node * baslangic;
                    baslangic=listebasi->next;
                    node * bitis;
                    bitis=listebasi->prev;
                    bitis->next=baslangic;
                    baslangic->prev=bitis;
                    free(silinecekdugum);
                    return baslangic;


                }
                else
                {
                    node * baslangic;
                    baslangic=listebasi;
                    node * silinecekdugum;

                    while(strcmp(listebasi->song,silineceksong) != 0)
                    {
                        if(strcmp(listebasi->next->song,silineceksong) == 0)
                        {
                            silinecekdugum=listebasi->next;
                        }
                        listebasi=listebasi->next;
                    }
                    node* oncesi;
                    oncesi=silinecekdugum->prev;
                    node* sonrasi;
                    sonrasi=silinecekdugum->next;
                    oncesi->next=sonrasi;
                    sonrasi->prev=oncesi;

                    free(silinecekdugum);

                    return baslangic;
                }
            }
        }
        else
        {
            if(strcmp(listebasi->song,silineceksong) == 0)
            {
                if(listebasi==listebasi->next){
                    listebasi=NULL;
                    return listebasi;
                }
                node * silinecekdugum;
                silinecekdugum=listebasi;
                node * baslangic;
                baslangic=listebasi->next;
                node * bitis;
                bitis=listebasi->prev;
                bitis->next=baslangic;
                baslangic->prev=bitis;
                free(silinecekdugum);
                return baslangic;
            }
            else
            {
                node * baslangic;
                baslangic=listebasi;
                node * silinecekdugum;

                while(strcmp(listebasi->song,silineceksong) != 0)
                {
                    if(strcmp(listebasi->next->song,silineceksong) == 0)
                    {
                        silinecekdugum=listebasi->next;
                    }
                    listebasi=listebasi->next;
                }
                node* oncesi;
                oncesi=silinecekdugum->prev;
                node* sonrasi;
                sonrasi=silinecekdugum->next;
                oncesi->next=sonrasi;
                sonrasi->prev=oncesi;

                free(silinecekdugum);

                return baslangic;
            }
        }

    }
    else
    {
        return listebasi;
    }
}
node * reverse(node* listebasi)
{
    if(listebasi!=NULL)
    {
        node * yenidugum;
        yenidugum=NULL;
        node * adetkontrol;
        adetkontrol=listebasi;
        yenidugum=basaekle(yenidugum,adetkontrol->song);
        listebasi=listebasi->next;
        while(listebasi!=adetkontrol)
        {
            yenidugum=basaekle(yenidugum,listebasi->song);
            listebasi=listebasi->next;

        }
        listebasi=listebasi->next;
        while(listebasi!=adetkontrol)
        {
            listebasi=listebasi->next;
            free(listebasi->prev);

        }
        free(adetkontrol);

        return yenidugum;
    }
    else
    {
        return listebasi;
    }

}
void playsong(node * listebasi,char komut[5])
{
    if(listebasi!=NULL)
    {
        if(playkontrol==0)
        {
            if(strcmp(komut,"N") == 0)
            {
                FILE *f = fopen("output.txt", "a+");
                fprintf(f, "%s\t%s\n","Playing",listebasi->song);
                fprintf(f, "%s\n","*****");
                strcpy( playingsong,listebasi->song);
                playkontrol=1;
                fclose(f);
            }
            else
            {
                FILE *f = fopen("output.txt", "a+");
                fprintf(f, "%s\t%s\n","Playing",listebasi->prev->song);
                strcpy( playingsong,listebasi->prev->song);
                playkontrol=1;
                fprintf(f, "%s\n","*****");
                fclose(f);
            }

        }
        else if(playkontrol==1)
        {

            if(strcmp(komut,"N") == 0)
            {
                FILE *f = fopen("output.txt", "a+");
                node * adetkontrol;
                adetkontrol=listebasi->prev;
                node * sarki;

                if(strcmp(adetkontrol->song,playingsong) == 0)
                {
                    sarki=adetkontrol;
                }
                while(listebasi!=adetkontrol)
                {

                    if(strcmp(listebasi->song,playingsong) == 0)
                    {
                        sarki=listebasi;

                    }
                    listebasi=listebasi->next;
                }
                sarki=sarki->next;
                strcpy( playingsong,sarki->song);
                fprintf(f, "%s\t%s\n","Playing",sarki->song);
                fprintf(f, "%s\n","*****");
                fclose(f);
            }
            else
            {
                FILE *f = fopen("output.txt", "a+");
                node * adetkontrol;
                adetkontrol=listebasi->prev;
                node * sarki;

                if(strcmp(adetkontrol->song,playingsong) == 0)
                {
                    sarki=adetkontrol;
                }
                while(listebasi!=adetkontrol)
                {

                    if(strcmp(listebasi->song,playingsong) == 0)
                    {
                        sarki=listebasi;

                    }
                    listebasi=listebasi->next;
                }
                sarki=sarki->prev;
                strcpy( playingsong,sarki->song);
                fprintf(f, "%s\t%s\n","Playing",sarki->song);
                fprintf(f, "%s\n","*****");
                fclose(f);
            }

        }
    }
    else
    {
        FILE *f = fopen("output.txt", "a+");
        fprintf(f, "%s\n", "No Songs To Play");
        fprintf(f, "%s\n", "*****");
        fclose(f);
    }

}
