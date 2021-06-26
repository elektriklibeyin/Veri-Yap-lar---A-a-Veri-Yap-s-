//MÜCAHİT TOKTAŞ 172803036
#include <fstream>
#include <iostream>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

#define Ad_Uzunluk 30        //uzunluk sabitleri
#define Soyad_Uzunluk 30
#define OkulNo_Uzunluk 7

struct Ogrenci_Dugum{        //ogrenci dugumu
char Ad[Ad_Uzunluk];
char Soyad[Soyad_Uzunluk];
char OkulNo[OkulNo_Uzunluk];
Ogrenci_Dugum *sol;
Ogrenci_Dugum *sag;
};

int sayac=0;               //global değişkenler ve menu fonksiyonu
void menuyazdir();
int dosyasecim;
char taramasecim;
string dosyaAdi;
char okulNumara[OkulNo_Uzunluk];

struct Agac{
                              //agac oluşturma fonksiyonları ve değişkenler
    Ogrenci_Dugum *kok;
    int dugumsayisi;
    void olustur();
    void ekle(Ogrenci_Dugum *);
    void dosyadanOku();
                               //tarama kısmı fonksiyonları
    void Tarama_Starter();
    void inorder_tara(Ogrenci_Dugum *);
    void preorder_tara(Ogrenci_Dugum *);
    void postorder_tara(Ogrenci_Dugum *);
                                // kayıt arama kısmı fonksiyonları
    void kayit_ara();
    int ilkDerinlikArama(Ogrenci_Dugum *);
    int ilkGenislikArama(Ogrenci_Dugum *);
                               //dosyaya yazma fonksiyonları
    void dosyaya_yaz();
    void inorder_yaz(Ogrenci_Dugum *);
    void preorder_yaz(Ogrenci_Dugum *);
    void postorder_yaz(Ogrenci_Dugum *);
                               //kayıt silme fonksiyonları
    void kayitsil();
    void sil(char *);
    void sil(Ogrenci_Dugum **);
};

//********************************************* M E N U - S E C I M  *************************************************************

int main(){

  menuyazdir();
}

void menuyazdir(){

    char secim;
    Agac *yeni;             //agac fonksiyonlarına ulaşmak için 'yeni' adında bir nesne yaratıyoruz
    yeni = new Agac;

   cout <<endl;
   cout << "Asagidaki islemlerden birini seciniz ..." << endl << endl;
   cout << "Arama yapmak icin: A" << endl;
   cout << "Listeyi ekrana yazdirmak icin: L" << endl;
   cout << "Ogrenci Silmek icin: S" << endl;
   cout << "Dosyaya yazmak icin: Y" << endl;
   cout << "Cikis icin: C" << endl;
     cin >> secim;

     switch(secim){                     //secime göre gerekli fonksiyona geçisi sağlayan switch yapısı
   case 'A' :
        yeni->kayit_ara();
     break;
   case 'L' :
         yeni->Tarama_Starter();
     break;
   case 'S' :
         yeni->kayitsil();
     break;
   case 'Y' :
         yeni->dosyaya_yaz();
     break;
   case 'C' :
       break;
     }
}

//********************************************* K A Y I T - A R A M A *************************************************************

void Agac::kayit_ara(){                                               //kayıt arama icin bilgi toplanır ve 2-çeşit aramadan biri seçtirilir.
      char arama_turu;
     cout <<endl<< "Hangi Turde tarama yapmak istiyorsunuz? " << endl; //GENİŞLİK VE DERİNLİK ÖNCELİKLİ arama seçimini yaptırıyoruz
           cout << "Derinlik Oncelikli Arama icin: D" << endl;
           cout << "Genislik Oncelikli Arama icin: G" << endl;
            cin >> arama_turu;

  cout <<endl<< "Hangi dosya icinde arama yapmak istiyorsunuz? " << endl;  //dosya seçimi
         cout << "Data1.txt icin: 1" << endl;
         cout << "Data2.txt icin: 2" << endl;
         cout << "Data3.txt icin: 3" << endl;
         cout << "Seciminizi giriniz: " <<endl;
         cin>>dosyasecim;
         olustur();
         sayac=0;
  cout << "Lutfen aramak istediginiz kisinin Okul-Numarasini giriniz : " << endl;   //arama için okul numarası alınır
  cin >> okulNumara;
  switch(arama_turu){                                                               //Genislik ve Derinlik arama turlerine gore secim yapan bir switch yapısı
   case 'D':
      if (ilkDerinlikArama(kok)==0){
      cout <<endl << "!!Aradiginiz kriterlere uygun kayit bulunamadi!!" << endl;
       }
     break;
   case 'G':
      if (ilkGenislikArama(kok)==0){
      cout <<endl << "!!Aradiginiz kriterlere uygun kayit bulunamadi!!" << endl;
       }
     break;
  }

 getchar();
 main();
}

int Agac::ilkDerinlikArama(Ogrenci_Dugum *p){                           //derinlik öncelikli arama YIGIN yapısı kullanılarak gerçeklenmiştir.

   stack<Ogrenci_Dugum*>yigin;                                     //yıgın veri yapısı olusturulur ve kok dugumu yığına atılır
   yigin.push(kok);
   while(!yigin.empty()){
     sayac++;
     p=yigin.top();
    yigin.top();
    if(strcmp(okulNumara,p->OkulNo)==0){                   //strcmp fonksiyonu ile bilgiler karşılaştırılır
        cout<<endl<<"Aradiginiz Kayit ---> "<<p->OkulNo<<" "<<p->Ad<<" "<<p->Soyad<<endl;
        cout<<"Total islem sayisi : "<<sayac<<endl;
          return 1;
    }
    if(p->sag)
        yigin.push(p->sag);
    if(p->sol)
     yigin.push(p->sol);
   }
  return 0;
}

int Agac::ilkGenislikArama(Ogrenci_Dugum *p){                            //Genislik öncelikli arama KUYRUK yapısı kullanılarak gerçeklenmiştir.

   queue <Ogrenci_Dugum*> kuyruk;                                   //kuyruk veri yapısı olusturulur ve kok dugumu kuyruğa atılır
   kuyruk.push(kok);
   while(!kuyruk.empty()){
     sayac++;
     p=kuyruk.front();
     kuyruk.pop();
    if(strcmp(okulNumara,p->OkulNo)==0){
        cout<<endl<<"Aradiginiz Kayit ---> "<<p->OkulNo<<" "<<p->Ad<<" "<<p->Soyad<<endl;
            cout<<"Total islem sayisi : "<<sayac<<endl;
             return 1;
    }
    if(p->sag)
        kuyruk.push(p->sag);
    if(p->sol)
     kuyruk.push(p->sol);
   }
  return 0;
}

//********************************************* K A Y I T - T A R A M A  *************************************************************

void Agac::Tarama_Starter(){                     //kayıt tarama için bilgi toplanır ve pre-in-post taramalara burdan erişilir.

   cout <<endl<< "Preorder listeleme icin: R" << endl;    //tarama çeşitlerinden biri seçilir
         cout << "Inorder listeleme icin: I" << endl;
         cout << "Postorder listeleme icin: O" << endl <<endl;
         cout << "Seciminizi giriniz: " <<endl;
         cin >> taramasecim;
         string  taramatipi;
            if(taramasecim =='R')               taramatipi = "Preorder";
            if(taramasecim =='I')               taramatipi = "Inorder";
            if(taramasecim == 'O')              taramatipi = "Postorder";
         cout <<endl<< "Hangi dosya icin "<< taramatipi <<" listeleme yapmak istiyorsunuz?" << endl;
         cout << "Data1.txt icin: 1" << endl;
         cout << "Data2.txt icin: 2" << endl;
         cout << "Data3.txt icin: 3" << endl;
         cout << "Seciminizi giriniz: " <<endl;       //dosya seçimi yapılır
         cin >> dosyasecim;
         olustur();

    switch(taramasecim){                //pre-in-post taramalara bu switch yapısından erişilir.
    case 'R':
    preorder_tara(kok); break;
    case 'I':
    inorder_tara(kok); break;
    case 'O':
    postorder_tara(kok); break;
    }
    main();
}

void Agac::preorder_tara(Ogrenci_Dugum *p){         //console'a preorder tarama sonuçları yazdırılır
  if(p){
    cout<<p->OkulNo<<" "<<p->Ad<<" "<<p->Soyad<<endl;
    preorder_tara(p->sol);
    preorder_tara(p->sag);
 }
}

void Agac::inorder_tara(Ogrenci_Dugum *p){
  if(p){
    inorder_tara(p->sol);
    cout<<p->OkulNo<<" "<<p->Ad<<" "<<p->Soyad<<endl;
    inorder_tara(p->sag);
 }
}

void Agac::postorder_tara(Ogrenci_Dugum *p){
  if(p){
    postorder_tara(p->sol);
    postorder_tara(p->sag);
    cout<<p->OkulNo<<" "<<p->Ad<<" "<<p->Soyad<<endl;
 }
}

//********************************************* A G A C   Y A P I S I   K U R M A *************************************************************

void Agac::olustur(){
kok = NULL;
dugumsayisi = 0;
dosyadanOku();
}

void Agac::dosyadanOku(){

   string dosyaAdi;

     switch(dosyasecim){           //yapılmış olan dosya seçimine göre datası çekilecek dosyanın adını dosyaAdi'na veriyoruz
    case 1:
    dosyaAdi="data1.txt";  break;
    case 2:
    dosyaAdi="data2.txt";  break;
    case 3:
    dosyaAdi="data3.txt";  break;
     }

	char ogrno[15],ad[30],soyad[30],satirAl[75];
	char *ptr;
	ifstream dosya1(dosyaAdi);			//ifstream ile "data?.txt" dosyasını okumak için dosyayı açma
	dosya1.getline(satirAl,75);
	for(int i=0;i<75;i++){				//satır sonundaki '\r' karakterini, '\0' karakteri ile değiştirme
		if(satirAl[i]=='\r')
			satirAl[i]='\0';
		}

	while(dosya1){					//while döngüsü içinde dosyayı sonuna kadar satır satır okuma ve okunan satırları boşluklara göre parçalayıp,
		ptr=strtok(satirAl,"\t");		//	j sayacının değerine göre değişkenlere atama
		int j=0;
		while(ptr!=NULL){
			if(j==0)
				strcpy(ogrno,ptr);
			if(j==1)
				strcpy(ad,ptr);
			if(j==2)
				strcpy(soyad,ptr);
			if(j==3){			    //bir ad ve bir soyad okunmasına rağmen satır sonu gelmedi ise öğrencinin iki adı var demektir,
				strcat(ad," ");		//	bu iki ad arada bir boşluk bırakılarak öğrenci değişkenine atanır ve soyadı tekrar okunur
				strcat(ad,soyad);
				strcpy(soyad,ptr);
				}
			ptr=strtok(NULL," ");
			j++;
			}

        Ogrenci_Dugum *yeni;
        yeni = new Ogrenci_Dugum;
        strcpy(yeni->Ad,ad);
        strcpy(yeni->Soyad,soyad);
        strcpy(yeni->OkulNo,ogrno);
        yeni->sol = yeni->sag =NULL;
		ekle(yeni);

	    dosya1.getline(satirAl,75);
		for(int i=0;i<75;i++){
			if(satirAl[i]=='\r')
				satirAl[i]='\0';
			}
		}
	dosya1.close();
}

void Agac::ekle(Ogrenci_Dugum *eklenecek){            //.txt den çekilen veri burada agaç yapısına yerleştirilir.

 Ogrenci_Dugum *tara, *yeni;
 tara = kok;
 int karsilas;
 bool eklendi = false;
 yeni = new Ogrenci_Dugum;
 strcpy(yeni->Ad, eklenecek->Ad);
 strcpy(yeni->Soyad, eklenecek->Soyad);
 strcpy(yeni->OkulNo, eklenecek->OkulNo);
 yeni->sol=NULL;
 yeni->sag=NULL;
 if(kok==NULL){
    kok=yeni;
    dugumsayisi++;
    return;
 }
 while((tara != NULL)&&(!eklendi)){
    karsilas = strcmp(yeni->OkulNo,tara->OkulNo);
    if(karsilas<0){
        if(tara->sol != NULL)
            tara=tara->sol;
        else{
            tara->sol = yeni;
            eklendi= true;
        }
    }
    else if(karsilas >0){
        if(tara->sag !=NULL)
            tara=tara->sag;
        else{
            tara->sag=yeni;
            eklendi = true;
        }
    }
    else
        cout<<"veri tekrari olamaz.\n";
  }
    if(eklendi)
    dugumsayisi++;
}

//*********************************************  D O S Y A Y A - Y A Z M A   *************************************************************
void Agac::dosyaya_yaz(){

   cout <<endl<< "Hangi dosyayi yazdirmak istiyorsunuz? " << endl;        //yazılacak dosya için verinin hangi dosyadan çekileceği yani hangi agacın yazdırılacağı sorulur
         cout << "Data1.txt icin: 1" << endl;
         cout << "Data2.txt icin: 2" << endl;
         cout << "Data3.txt icin: 3" << endl;
         cout << "Seciminizi giriniz: " <<endl;
           cin>>dosyasecim;
         cout <<endl<< "Preorder yazdirmak icin: R" << endl;           //yazdırma tipi seçtirilir.
               cout << "Inorder yazdirmak icin: I" << endl;
               cout << "Postorder yazdirmak icin: O" <<endl;
               cout << "Seciminizi giriniz: " <<endl;
                cin >> taramasecim;
               cout <<"Yeni kayit icin dosya adi giriniz: "<<endl;      //oluşturulacak dosya için kullanıcıdan bir dosya adı yazması istenir.
                cin >> dosyaAdi;

    olustur();
  switch(taramasecim){                            //seçilen yazdırma tipine göre pre-in-post yazma fonksiyonlarına erişim sağlayan switch yapısı
    case 'R':
    preorder_yaz(kok); break;
    case 'I':
    inorder_yaz(kok); break;
    case 'O':
    postorder_yaz(kok); break;
    }
    cout<<" ** Dosyaniz olusturuldu **"<<endl;
    main();
}

void Agac::preorder_yaz(Ogrenci_Dugum *p){     //dosyaya preorder yazma
  struct Dosya_Kayit{
   char ad[Ad_Uzunluk];
   char soyad[Soyad_Uzunluk];
   char okulNo[OkulNo_Uzunluk];
  }kayit;
    ofstream dosyayaz(dosyaAdi,ios::app);
 if(p){
    strcpy(kayit.ad,p->Ad);
    strcpy(kayit.soyad,p->Soyad);
    strcpy(kayit.okulNo,p->OkulNo);
    dosyayaz<<kayit.okulNo<<" "<<kayit.ad<<" "<<kayit.soyad<<endl;
    preorder_yaz(p->sol);
    preorder_yaz(p->sag);
 }
 dosyayaz.close();
}

void Agac::inorder_yaz(Ogrenci_Dugum *p){    //dosyaya inorder yazma
  struct Dosya_Kayit{
   char ad[Ad_Uzunluk];
   char soyad[Soyad_Uzunluk];
   char okulNo[OkulNo_Uzunluk];
  }kayit;

    ofstream dosyayaz(dosyaAdi,ios::app);
 if(p){
    inorder_yaz(p->sol);
    strcpy(kayit.ad,p->Ad);
    strcpy(kayit.soyad,p->Soyad);
    strcpy(kayit.okulNo,p->OkulNo);
    dosyayaz<<kayit.okulNo<<" "<<kayit.ad<<" "<<kayit.soyad<<endl;
    inorder_yaz(p->sag);
 }
 dosyayaz.close();
}

void Agac::postorder_yaz(Ogrenci_Dugum *p){     //dosyaya postorder yazma
  struct Dosya_Kayit{
   char ad[Ad_Uzunluk];
   char soyad[Soyad_Uzunluk];
   char okulNo[OkulNo_Uzunluk];
  }kayit;
    ofstream dosyayaz(dosyaAdi,ios::app);
 if(p){
    postorder_yaz(p->sol);
    postorder_yaz(p->sag);
    strcpy(kayit.ad,p->Ad);
    strcpy(kayit.soyad,p->Soyad);
    strcpy(kayit.okulNo,p->OkulNo);
    dosyayaz<<kayit.okulNo<<" "<<kayit.ad<<" "<<kayit.soyad<<endl;
 }
 dosyayaz.close();
}

//*********************************************  A G A C T A N - D U G U M - S İ L M E   *************************************************************

void Agac::kayitsil(){

     cout <<endl<< "Hangi dosyadan ogrenci silmek istiyorsunuz? " << endl;   //burda dosya seçimi yani AĞAÇ seçimi yaptırıyoruz
           cout << "Data1.txt icin: 1" << endl;
           cout << "Data2.txt icin: 2" << endl;
           cout << "Data3.txt icin: 3" << endl;
           cout << "Seciminizi giriniz: " <<endl;
             cin>>dosyasecim;
         olustur();
  char no[OkulNo_Uzunluk];
  cout<<"Lutfen kaydini silmek istediginiz kisinin Okul Numarasini giriniz: "  << endl;   //silinecek Öğrencinin okul numarası istenir.
  cin.ignore(1000,'\n');
  cin.getline(no,OkulNo_Uzunluk);
   sil(no);                           //okul numarası sil fonksiyonuna gönderilir.
}

void Agac::sil(char *sil_no){           //silinecek düğüm tespit edilir.
  Ogrenci_Dugum *tara, *ust;
  tara=kok;
  bool bulundu = false;
  char yon='k';
  while(tara&&!bulundu){
    int karsilas = strcmp(sil_no,tara->OkulNo);
    if(karsilas<0){
      ust= tara;
      yon ='l';
      tara = tara->sol;
    }
    else if(karsilas>0){
        ust = tara;
        yon = 'r';
        tara= tara->sag;
    }
    else
        cout<<"silinecek kayit bulundu.\n"<<endl;
        bulundu=true;
  }
  if(bulundu){

    if(yon=='l')
        sil(&ust->sol);
    else if(yon=='r')
        sil(&ust->sag);
    else
        sil(&kok);
  }
  else
    cout<<"silinecek kayit bulunamadi.\n"<<endl;
}

void Agac::sil(Ogrenci_Dugum **p){    //düğüm silme işlemi gerçekleştirilir.
  Ogrenci_Dugum *r,*q;
  r=*p;
  if(r==NULL)
    return;
  else if (r->sag==NULL){
     *p = r->sol;
     delete r;
  }
  else if(r->sol==NULL){
    *p = r->sag;
    delete r;
  }
  else{
    for(q = r->sag; q->sol; q=q->sol);
    q->sol= r->sol;
    *p=r->sag;
    delete r;
  }
  cout<<"Ogrenci Agactan Silindi"<<endl;
  main();

}


























