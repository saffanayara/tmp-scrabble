/*
Kelompok B7 - GO Scrabble
Nama	: 211524036 - Amelia Nathasa
          211524052 - Nayara Saffa
          211524053 - Novia Nur Azizah
*/

#include <stdio.h>   //library input output
#include <stdbool.h> //library standar untuk boolean
#include <conio.h>   //library untuk menampilkan hasil antarmuka (tampilan)
#include <stdlib.h>  //library untuk memanggil fungsi-fungsi bawaan dari c
#include <string.h>  //library untuk memanipulasi string
#include <math.h>    //library untuk operasi matematika
#include <windows.h> //library untuk timeout
#include <time.h>    //library untuk timeout
#include <ctype.h>   //library untuk memanipulasi variabel

/*Inisialisasi*/
void inisialisasi();

/*Modul Utama*/
// Modul utama dalam program
int mulaiPermainan();
int tampilBantuan();
int tampilDaftarSkor();

/*Modul mulaiPermainan*/
// Modul-modul untuk memulai permainan
int siapkanDataPemain();
void randomHuruf(char *s);
void tampilPapan();

/*Modul siapkanDataPemain*/
// Modul-modul untuk menyiapkan data pemain
void inputPlayer();
int pilihLevel();

/*Modul tampilPapan*/
// Modul-modul untuk menampilkan papan scrabble
void listHuruf();
void cekKata();
void resetBlokHuruf();
void tempelKata();

/*Modul cekKata*/
// Untuk mengecek apakah kata dapat di tempel di papan atau tidak
void cekBlokHuruf();
void cekSambungKata();
void cekSekitarKata();

/*Modul untuk menghitung waktu input*/
int StartTime();
int EndTime();

/*Modul tampilGiliran*/
// Modul-modul untuk mengatur giliran bermain
void isiPapan();
void cekKamus();
void hitungSkor();

/*Modul untuk Olah Skor*/
// Modul untuk mengolah skor pemain
void tampilPemenang();
int skorAkhir();
void urutkanSkor();
void fileSkor();

/*Modul Gotoxy*/
// Modul untuk menentukan posisi output
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void keteranganPapan();
/*============================================================================================*/
typedef struct // Berisi huruf yang dapat digunakan dan poinnya
{
    char huruf;
    int poin;
} blokHuruf;
blokHuruf daftarHuruf[25];

typedef struct // Berisi data pemain yang memainkan permainan
{
    char nama[10];
    int skor;
    bool giliran;
    char blokHuruf[7];
    char inputKata[7];
    bool cekKata;
} dataPemain;
dataPemain player[2];

typedef struct // Berisi nama pemain dan skor yang didapatkan
{
    char nama[10];
    int skor;
} dataSkor;
dataSkor temp[7];

/*Variabel Global*/
char hurufAcak[100]; // Daftar huruf yang sudah diacak
int idx;             // Indeks huruf acak, agar setiap player mendapatkan huruf acak berbeda
int putaran;		 // Menghitung sudah berapa putaran permainan berlangsung
int waktuGiliran;
char papan[15][15];
int comboKalah;

/*Inisialisasi Bonus Pada Papan*/
int bonus[15][15] = {
    {4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4}, // 1 : Double Letter
    {0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0}, // 2 : Triple Letter
    {0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0}, // 3 : Double Word
    {1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1}, // 4 : Triple Word
    {0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0},
    {0, 0, 1, 0, 0, 0, 2, 0, 2, 0, 0, 0, 1, 0, 0},
    {4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 4},
    {0, 0, 1, 0, 0, 0, 2, 0, 2, 0, 0, 0, 1, 0, 0},
    {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0},
    {0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
    {1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1},
    {0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0},
    {0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0},
    {4, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 4},
};

/*============================================================================================*/
/*Inisialisasi Huruf Yang Dapat Digunakan Beserta Poinnya*/
void inisialisasi()
{
	/*Inisialisasi Skor Awal*/
	player[0].skor = 0;
	player[1].skor = 0;
	
	/*Inisialisasi Poin Huruf*/
    daftarHuruf[0].huruf = 'A';daftarHuruf[0].poin = 1;
    daftarHuruf[1].huruf = 'B';daftarHuruf[1].poin = 5;
    daftarHuruf[2].huruf = 'C';daftarHuruf[2].poin = 8;
    daftarHuruf[3].huruf = 'D';daftarHuruf[3].poin = 3;
    daftarHuruf[4].huruf = 'E';daftarHuruf[4].poin = 1;
    daftarHuruf[5].huruf = 'F';daftarHuruf[5].poin = 5;
    daftarHuruf[6].huruf = 'G';daftarHuruf[6].poin = 3;
    daftarHuruf[7].huruf = 'H';daftarHuruf[7].poin = 4;
    daftarHuruf[8].huruf = 'I';daftarHuruf[8].poin = 1;
    daftarHuruf[9].huruf = 'J';daftarHuruf[9].poin = 10;
    daftarHuruf[10].huruf = 'K';daftarHuruf[10].poin = 2;
    daftarHuruf[11].huruf = 'L';daftarHuruf[11].poin = 4;
    daftarHuruf[12].huruf = 'M';daftarHuruf[12].poin = 2;
    daftarHuruf[13].huruf = 'N';daftarHuruf[13].poin = 1;
    daftarHuruf[14].huruf = 'O';daftarHuruf[14].poin = 1;
    daftarHuruf[15].huruf = 'P';daftarHuruf[15].poin = 4;
    daftarHuruf[16].huruf = 'R';daftarHuruf[16].poin = 1;
    daftarHuruf[17].huruf = 'S';daftarHuruf[17].poin = 1;
    daftarHuruf[18].huruf = 'T';daftarHuruf[18].poin = 1;
    daftarHuruf[19].huruf = 'U';daftarHuruf[19].poin = 1;
    daftarHuruf[20].huruf = 'V';daftarHuruf[20].poin = 5;
    daftarHuruf[21].huruf = 'W';daftarHuruf[21].poin = 8;
    daftarHuruf[22].huruf = 'Y';daftarHuruf[22].poin = 5;
    daftarHuruf[23].huruf = 'Z';daftarHuruf[23].poin = 10;
    daftarHuruf[24].huruf = '!';daftarHuruf[24].poin = 0; // Bisa diisi huruf apa saja
    
    /*Inisialisasi Papan*/
    int i, j;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            papan[i][j] = ' ';
        }
    }
    
    idx = 0;						// Index huruf acak dimulai dari 0
    /*Inisialisasi Blok Huruf*/
    player[0].giliran = true; 		// P1 selalu bermain pertama
    player[1].giliran = false;
    int k=0, l=0;
    for(k=0; k<2; k++){
    	for(l=0; l<7; l++){
    		player[k].blokHuruf[l] = hurufAcak[idx];
    		idx++ ;
		}
	}
}

int main()
{
    /*Untuk Memilih Menu*/
    int pilihMenu;
    do
    {
        system("cls");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ			\n\n");
        printf("\t\t\t          GO SCRABBLE               				");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ			\n");
        printf("\t\t\t          MENU UTAMA    						\n");
        printf("\t\t\t                       						\n");
        printf("\t\t\t           1. MULAI       					\n");
        printf("\t\t\t          2. BANTUAN       					\n");
        printf("\t\t\t         3. DAFTAR SKOR      				\n");
        printf("\t\t\t          4. KELUAR       					\n");
        printf("\t\t\t                         						\n");
        printf("\t\t\t                          					\n");
        printf("\t\t\t     PILIH MENU [1/2/3/4]: ");
        scanf("%d", &pilihMenu);
        printf("\n\n\n");

        if (pilihMenu == 1)
        {
            mulaiPermainan();
        }
        if (pilihMenu == 2)
        {
            tampilBantuan();
        }
        if (pilihMenu == 3)
        {
            tampilDaftarSkor();
        }
    } while (pilihMenu != 4);

    exit(0);
}

/*Untuk Memulai Permainan*/
int mulaiPermainan()
{
    /*Menyiapkan Data Pemain*/
    siapkanDataPemain();
    putaran = 0;	// Sebelum permainan dimulai, maka nilai putaran adalah 0
    comboKalah = 0; // Sebelum permainan dimulai, maka nilai comboKalah adalah 0

    /*Untuk random huruf. Sumber internet*/
    srand(time(NULL));
    // daftarHuruf merupakan daftar huruf yang masih berurutan
    char daftarHuruf[100] = "AAAAAAAAAAAAAAAAAAABBBBCCCDDDDEEEEEEEEFGGGHHIIIIIIIIJKKKLLLMMMNNNNNNNNNOOOPPRRRRSSSTTTTTUUUUUVWYYZ!!";
    strcpy(hurufAcak, daftarHuruf);
    randomHuruf(hurufAcak);
    idx = 0; // Index huruf acak dimulai dari 0

    /*Inisialisasi*/
    inisialisasi();

    /*Menampilkan Papan Permainan*/
    tampilPapan();

    return 0;
}

/*Menampilkan File Bantuan*/
int tampilBantuan()
{
    FILE *tutorial;
    char help;
    int back;
    tutorial = fopen("bantuan.TXT", "r");
    if (tutorial == NULL)
    {
        printf("File tidak dapat dibuka\n\r");
        exit(0);
    }
    system("cls");
    while ((help = getc(tutorial)) != EOF)
    {
        putch(help);
    }
    system("\n\n\n");
    system("pause");
}

void fileSkor()
{
	/*Menampilkan Tanggal*/
	time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    int m;
    m = tm.tm_mon+1;
    
	int i;
    FILE *f;
	f = fopen("skor.txt", "a+");
	
	if(f!=NULL){
		if(player[0].skor != player[1].skor){
			if(player[0].skor > player[1].skor){
				fprintf(f,"\t|%d/%d/%d %d:%d:%d \t|%s \t\t|%d \t|MENANG \t|\n", tm.tm_mday, m, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player[0].nama, player[0].skor);
				fprintf(f,"\t+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n"); 
				fprintf(f,"\t|%d/%d/%d %d:%d:%d \t|%s \t\t|%d \t|KALAH  \t|\n", tm.tm_mday, m, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player[1].nama, player[1].skor);
				fprintf(f,"\t+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n"); 
			}
			if(player[1].skor > player[0].skor){
				fprintf(f,"\t|%d/%d/%d %d:%d:%d \t|%s \t\t|%d \t|MENANG \t|\n", tm.tm_mday, m, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player[1].nama, player[1].skor);
				fprintf(f,"\t+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n"); 
				fprintf(f,"\t|%d/%d/%d %d:%d:%d \t|%s \t\t|%d \t|KALAH  \t|\n", tm.tm_mday, m, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player[0].nama, player[0].skor);
				fprintf(f,"\t+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n"); 
			}
		}else{
			for(i=0; i < 2; i++){ 
        		fprintf(f,"\t|%d/%d/%d %d:%d:%d \t|%s \t\t|%d \t|SERI \t\t|\n", tm.tm_mday, m, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, player[i].nama, player[i].skor); 
				fprintf(f,"\t+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");    
    		}
		}
	}
	
	fclose(f);
}

/*Menampilkan Skor Tertinggi*/
int tampilDaftarSkor()
{
    FILE *fileSkor;
    char skor;
    int back;
    fileSkor = fopen("skor.txt", "r");
    if (fileSkor == NULL)
    {
        printf("File tidak dapat dibuka\n\r");
        exit(0);
    }
    system("cls");
    while ((skor = getc(fileSkor)) != EOF)
    {
        putch(skor);
    }
    
    printf("\n\n\n\n\n");
    system("pause");
}


/*Menyiapkan Data Pemain*/
int siapkanDataPemain()
{
    inputPlayer();
    pilihLevel();
}

/*Input Nama Player*/
void inputPlayer()
{
	int length1=0, length2=0;
	do{
	do{
		system("cls");
    	printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ			\n\n");
    	printf("\t\t\t          GO SCRABBLE               				");
    	printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ			\n");
    	printf("\t\t\t       INPUT NAMA PLAYER   					\n");
    	printf("\t\t\t      [MAKSIMAL 10 HURUF]                		\n");
    	printf("\t\t\t      				                		\n");
    	printf("\t\t\t    Player 1 : ");
    	scanf("\t\t\t     %[^\n]", player[0].nama);
    	printf("\n\t\t\t    Player 2 : ");
    	scanf("\t\t\t     %[^\n]", player[1].nama);
    	length1 = strlen(player[0].nama);
    	length2 = strlen(player[1].nama);
	} while(length1 >= 10);
	} while (length2 >= 10);
}

int pilihLevel()
{
    // Kamus Data
    int pilihLevel;
    do
    {
        system("cls");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ\n\n");
        printf("\t\t\t          GO SCRABBLE               	   ");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ	 \n");
        printf("\t\t\t             	         				 \n");
        printf("\t\t\t             LEVEL       				 \n");
        printf("\t\t\t    		    	                     \n");
        printf("\t\t\t           1. Mudah                    \n");
        printf("\t\t\t           2. Sedang                    \n");
        printf("\t\t\t           3. Sulit                     \n");
        printf("\t\t\t                         				 \n");
        printf("\t\t\t                          			 \n");
        printf("\t\t\t       PILIH MENU [1/2/3]: ");
        scanf("%d", &pilihLevel);
        printf("\n\n\n");

        if (pilihLevel == 1)
        {
            waktuGiliran = 75;
        }
        if (pilihLevel == 2)
        {
            waktuGiliran = 60;
        }
        if (pilihLevel == 3)
        {
            waktuGiliran = 45;
        }
    } while (pilihLevel != 1 && pilihLevel != 2 && pilihLevel != 3);
    return pilihLevel;
}

/*Random Huruf (Referensi Googling)*/
void randomHuruf(char *s)
{
    int i, j;
    int length = strlen(s);
    char daftarHuruf[length + 1];
    strcpy(daftarHuruf, s);
    // variabel untuk membantu menentukan kapan harus mengakhiri loop di bawah
    double diff = 0;
    bool same_start = false;
    bool same_end = false;
    int times_stuck = 0;
    // Terus mencoba mengacak kata sampai cukup
    do
    {
        // Acak kata dengan mengemukan dua indeks secara acak dalam string dan menukan karakter pada indeks tersebut (asalkan bukan indeks yang sama) dan lakukan sebanyak karakter yang ada
        int i = 0;
        while (i < length)
        {
            // menemukan dua posisi acak dalam string
            int pos1 = rand() % length;
            int pos2 = rand() % length;
            // tukar karakter pada posisi ini asalkan tidak sama
            if (pos1 != pos2)
            {
                char temp = s[pos1];
                s[pos1] = s[pos2];
                s[pos2] = temp;
                i++;
            }
        }
        // hitung berapa banyak karakter yang berbeda saat membandingkan string daftarHuruf dengan string acakHuruf
        int differences = 0;
        for (j = 0; j < length; j++)
            if (daftarHuruf[j] != s[j])
                differences++;
        // menghitung pecahan dari berapa banyak karakter yang berbeda (yaitu 0,5 berarti setengah karakter berbeda)
        diff = (double)differences / length;
        // periksa apakah string acakHuruf memiliki karakter awal dan akhir yang sama dengan string aslinya
        same_start = s[0] == daftarHuruf[0];
        same_end = s[length - 1] == daftarHuruf[length - 1];
        // kenaikan times_stuck jadi kita tahu berapa kali kita menjalankan loop
        times_stuck++;
    } while (((same_start && same_end) ||
              (diff < 0.5)) &&
             (times_stuck < 100));
}

/*Tampilan Papan Scrabble**/
void tampilPapan()
{
	putaran++ ;	// Putaran selalu bertambah
    system("cls");
    printf("\n\n");
    printf("อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ  \n");
    printf("                                            GO SCRABBLE                                                      \n");
    printf("อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n\n");
    printf("	  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15	\n");
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("1	|@%c | %c | %c |$%c | %c | %c | %c |@%c | %c | %c | %c |$%c | %c | %c |@%c |\n", papan[0][0], papan[0][1], papan[0][2], papan[0][3], papan[0][4], papan[0][5], papan[0][6], papan[0][7], papan[0][8], papan[0][9], papan[0][10], papan[0][11], papan[0][12], papan[0][13], papan[0][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("2	| %c |~%c | %c | %c | %c |#%c | %c | %c | %c |#%c | %c | %c | %c |~%c | %c |\n", papan[1][0], papan[1][1], papan[0][2], papan[1][3], papan[1][4], papan[1][5], papan[1][6], papan[1][7], papan[1][8], papan[1][9], papan[1][10], papan[1][11], papan[1][12], papan[1][13], papan[1][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("3	| %c | %c |~%c | %c | %c | %c |$%c | %c |$%c | %c | %c | %c |~%c | %c | %c |\n", papan[2][0], papan[2][1], papan[2][2], papan[2][3], papan[2][4], papan[2][5], papan[2][6], papan[2][7], papan[2][8], papan[2][9], papan[2][10], papan[2][11], papan[2][12], papan[2][13], papan[2][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("4	|$%c | %c | %c |~%c | %c | %c | %c |$%c | %c | %c | %c |~%c | %c | %c |$%c |\n", papan[3][0], papan[3][1], papan[3][2], papan[3][3], papan[3][4], papan[3][5], papan[3][6], papan[3][7], papan[3][8], papan[3][9], papan[3][10], papan[3][11], papan[3][12], papan[3][13], papan[3][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("5	| %c | %c | %c | %c |~%c | %c | %c | %c | %c | %c |~%c | %c | %c | %c | %c |\n", papan[4][0], papan[4][1], papan[4][2], papan[4][3], papan[4][4], papan[4][5], papan[4][6], papan[4][7], papan[4][8], papan[4][9], papan[4][10], papan[4][11], papan[4][12], papan[4][13], papan[4][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("6	| %c |#%c | %c | %c | %c |#%c | %c | %c | %c |#%c | %c | %c | %c |#%c | %c |\n", papan[5][0], papan[5][1], papan[5][2], papan[5][3], papan[5][4], papan[5][5], papan[5][6], papan[5][7], papan[5][8], papan[5][9], papan[5][10], papan[5][11], papan[5][12], papan[5][13], papan[5][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("7	| %c | %c |$%c | %c | %c | %c |#%c | %c |#%c | %c | %c | %c |$%c | %c | %c |\n", papan[6][0], papan[6][1], papan[6][2], papan[6][3], papan[6][4], papan[6][5], papan[6][6], papan[6][7], papan[6][8], papan[6][9], papan[6][10], papan[6][11], papan[6][12], papan[6][13], papan[6][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("8	|@%c | %c | %c |$%c | %c | %c | %c |*%c | %c | %c | %c |$%c | %c | %c |@%c |\n", papan[7][0], papan[7][1], papan[7][2], papan[7][3], papan[7][4], papan[7][5], papan[7][6], papan[7][7], papan[7][8], papan[7][9], papan[7][10], papan[7][11], papan[7][12], papan[7][13], papan[7][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("9	| %c | %c |$%c | %c | %c | %c |#%c | %c |#%c | %c | %c | %c |$%c | %c | %c |\n", papan[8][0], papan[8][1], papan[8][2], papan[8][3], papan[8][4], papan[8][5], papan[8][6], papan[8][7], papan[8][8], papan[8][9], papan[8][10], papan[8][11], papan[8][12], papan[8][13], papan[8][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("10	| %c |#%c | %c | %c | %c |#%c | %c | %c | %c |#%c | %c | %c | %c |#%c | %c |\n", papan[9][0], papan[9][1], papan[9][2], papan[9][3], papan[9][4], papan[9][5], papan[9][6], papan[9][7], papan[9][8], papan[9][9], papan[9][10], papan[9][11], papan[9][12], papan[9][13], papan[9][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("11	| %c | %c | %c | %c |~%c | %c | %c | %c | %c | %c |~%c | %c | %c | %c | %c |\n", papan[10][0], papan[10][1], papan[10][2], papan[10][3], papan[10][4], papan[10][5], papan[10][6], papan[10][7], papan[10][8], papan[10][9], papan[10][10], papan[10][11], papan[10][12], papan[10][13], papan[10][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("12	|$%c | %c | %c |~%c | %c | %c | %c |$%c | %c | %c | %c |~%c | %c | %c |$%c |\n", papan[11][0], papan[11][1], papan[11][2], papan[11][3], papan[11][4], papan[11][5], papan[11][6], papan[11][7], papan[11][8], papan[11][9], papan[11][10], papan[11][11], papan[11][12], papan[11][13], papan[11][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("13	| %c | %c |~%c | %c | %c | %c |$%c | %c |$%c | %c | %c | %c |~%c | %c | %c |\n", papan[12][0], papan[12][1], papan[12][2], papan[12][3], papan[12][4], papan[12][5], papan[12][6], papan[12][7], papan[12][8], papan[12][9], papan[12][10], papan[12][11], papan[12][12], papan[12][13], papan[12][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("14	| %c |~%c | %c | %c | %c |#%c | %c | %c | %c |#%c | %c | %c | %c |~%c | %c |\n", papan[13][0], papan[13][1], papan[13][2], papan[13][3], papan[13][4], papan[13][5], papan[13][6], papan[13][7], papan[13][8], papan[13][9], papan[13][10], papan[13][11], papan[13][12], papan[13][13], papan[13][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    printf("15	|@%c | %c | %c |$%c | %c |%c  | %c |@%c | %c | %c | %c |$%c | %c | %c |@%c |\n", papan[14][0], papan[14][1], papan[14][2], papan[14][3], papan[14][4], papan[14][5], papan[14][6], papan[14][7], papan[14][8], papan[14][9], papan[14][10], papan[14][11], papan[14][12], papan[14][13], papan[14][14]);
    printf("	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    keteranganPapan();
    listHuruf();
    isiPapan();
}
/*Menampilkan Keterangan Pada Papan*/
void keteranganPapan()
{
	/*Tampil Skor Pemain*/
	gotoxy(78, 10);
    printf("SKOR");
    gotoxy(78, 11);
    printf("_________________________");
    gotoxy(78, 12);
    printf("%s : %d", player[0].nama, player[0].skor);
    gotoxy(78, 13);
    printf("%s : %d", player[1].nama, player[1].skor);
    
    /*Tampil Giliran Pemain*/
    int i;
    if (player[0].giliran == true)
    {
        i = 0;
    }
    else
    {
        i = 1;
    }
    gotoxy(78, 15);
    printf("Giliran %s !", player[i].nama);
    gotoxy(78, 16);
    printf("Waktu %d detik", waktuGiliran);
	
	/*Tampil Keterangan Pada Papan*/
	gotoxy(78,8);
	printf("Sisa blok huruf : %d", 100-idx);
    gotoxy(78, 33);
    printf("Keterangan:");
    gotoxy(78, 34);
    printf("@ : Triple Word");
    gotoxy(78, 35);
    printf("# : Triple Letter");
    gotoxy(78, 36);
    printf("~ : Double Word");
    gotoxy(78, 37);
    printf("$ : Double Letter");
}

/*Blok huruf masing-masing player dan tempat input huruf pada blok ke papan*/
void listHuruf()
{
    int i, j;
    if (player[0].giliran == true)
    {
        i = 0; // Player 1
    }
    else
    {
        i = 1; // Player 2
    }
    
    gotoxy(78, 18);
    printf("BLOK HURUF");
    gotoxy(78, 19);
    printf("+---+---+---+---+---+---+---+");
    gotoxy(78, 20);
    printf("| %c | %c | %c | %c | %c | %c | %c |", player[i].blokHuruf[0], player[i].blokHuruf[1], player[i].blokHuruf[2], player[i].blokHuruf[3], player[i].blokHuruf[4], player[i].blokHuruf[5], player[i].blokHuruf[6]);
    gotoxy(78, 21);
    printf("+---+---+---+---+---+---+---+");
    gotoxy(78, 22);
    printf("  1   2   3   4   5   6   7");

    // Ketika pemain menggunakan huruf untuk menyusun kata, maka mereka mendapat huruf baru
    for (i = 0; i < 2; i++)
    {
        if (player[i].giliran == false)
        {
            for (j = 0; j < 7; j++)
            {
                if (hurufAcak[idx] < 100)
                {
                    if (player[i].blokHuruf[j] == ' ')
                    {
                        player[i].blokHuruf[j] = hurufAcak[idx];
                        idx++;
                    }
                }
                else
                {
                    tampilPemenang();
                }
            }
        }
    }
}

/*Mengisi papan*/
void isiPapan()
{
    int baris1, kolom1, baris2, kolom2, posisiKata, length, i, t, j;
    double waktuInput = 0;
    if (player[0].giliran == true)
    { // Cek sekarang giliran siapa
        i = 0;
    }
    else
    {
        i = 1;
    }

    /*Mulai Waktu Berpikir*/
    t = StartTime();

    gotoxy(78, 24);
    printf("Pilih Posisi Kata");
    gotoxy(78, 25);
    printf("Posisi Kata 1.Horizontal 2.Vertikal [1/2] : ");
    scanf("%d", &posisiKata);
    gotoxy(78, 26);
    printf("[Awal] Baris Kolom : ");
    scanf("%d %d", &baris1, &kolom1);
    gotoxy(78, 27);
    printf("[Akhir] Baris Kolom : ");
    scanf("%d %d", &baris2, &kolom2);
    gotoxy(78, 28);
    printf("Input Kata : ");
    memset(player[i].inputKata, 0, strlen(player[i].inputKata)); //Mengosongkan string
    scanf("%s", &player[i].inputKata);
    fflush(stdin);

    t = EndTime() - t;
    waktuInput = ((double)t) / CLOCKS_PER_SEC; // hitung waktu menjadi detik

    if (waktuInput > waktuGiliran)
    {
        gotoxy(78, 30);
        printf("Kamu melebihi batas waktu lebih dari %d detik", waktuGiliran);
        gotoxy(78, 31);
        printf("Waktu kamu adalah %2.f detik", waktuInput);
        Sleep(3000);

        // Jika waktu habis, giliran ganti, skor player tidak bertambah
        if (i == 0)
        {
            player[0].giliran = false;
            player[1].giliran = true; // Jika salah ganti giliran
        }
        else
        {
            player[0].giliran = true;
            player[1].giliran = false;
        }
        comboKalah++ ;
        if(comboKalah == 3){
        	tampilPemenang();
		}else{
			tampilPapan();	
		}
    }
    cekKata(posisiKata, baris1, kolom1, baris2, kolom2);
}

void cekKata(int posisiKata, int baris1, int kolom1, int baris2, int kolom2)
{
    int i, j, k=0, l, m, count, length;
    char bacaKata[15], huruf[2];
    memset(bacaKata, 0, strlen(bacaKata)); // Mengosongkan string
    if (player[0].giliran == true)
    { // Cek sekarang giliran siapa
        i = 0;
    }
    else
    {
        i = 1;
    }
    player[i].cekKata = false;
    
    // Untuk menginput simbol yang bisa diisi semua huruf
    for(j=0; j<7; j++){
    	if(player[i].inputKata[j] == '!'){
    		gotoxy(78, 29);printf("Pilih Huruf Untuk '!' : ");
    		scanf("%s", &huruf[k]);
    		k++ ;
		}
	}
    
	cekSambungKata(i, posisiKata, baris1, kolom1, baris2, kolom2, bacaKata, huruf);
    if(player[i].cekKata == true){
    	cekBlokHuruf(i);
    	if(player[i].cekKata == true){
    		cekKamus(bacaKata);
    		if(player[i].cekKata == true){
    			cekSekitarKata(i, posisiKata, baris1, kolom1, baris2, kolom2, huruf);
    			if(player[i].cekKata == true){
    				tempelKata(posisiKata, baris1, kolom1, huruf);
    				hitungSkor(posisiKata, baris1, kolom1, bacaKata);
    				comboKalah = 0;
				}
			}
		}
	}
	if(player[i].cekKata == false){
		gotoxy(78,31);printf("Input Gagal!");
		Sleep(3000);
		if(putaran == 1){
			putaran = 0;	// Jika player pertama tidak membentuk kata di tengah, player selanjutnya harus membentuk kata di tengah
		}
		comboKalah++ ;
		resetBlokHuruf();
	}
	// Setlah selesai cek kata, ganti giliran
	if (i == 0)
    {
        player[0].giliran = false;
        player[1].giliran = true;
    }
    else
    {
        player[0].giliran = true;
        player[1].giliran = false;
    }
    if(comboKalah == 3){
        tampilPemenang();
	}else{
		tampilPapan();	
	}
}

void cekSambungKata(int i, int posisiKata, int baris1, int kolom1, int baris2, int kolom2, char *bacaKata, char *huruf){
	int x = baris1 - 1, y = kolom1 - 1, length, l=0, k=0, m=0;
	int o = baris2 - 1, p = kolom2 - 1;
	int count=0; // Untuk mengecek huruf yang di input player menyambung dengan kata yang ada di papan
    length = strlen(player[i].inputKata);
    if (posisiKata == 1) // Horizontal (kolom bertambah)
	{
	    for (y = kolom1 - 1; y < kolom2; y++)
	    {
	        if (papan[x][y] == ' ')
	        {
	            if (l < length)
	            {
	            	if(player[i].inputKata[l] == '!'){
	            		bacaKata[k] = tolower(huruf[m]);
	            		k++; m++; l++;
					}else{
						bacaKata[k] = toupper(player[i].inputKata[l]);
						k++; l++;
					}
	            }else{
	                break;
				}
	            if(putaran == 1){				// Khusus putaran 1, salah satu huruf harus menyentuh kotak bintang
	            	if(x == 7 && y == 7){
	            		player[i].cekKata = true;
					}
				}
	    	}
	        else
	        {
	            bacaKata[k] = papan[x][y];
	            k++ ;
	            count++ ;
	        }
	    }
	}else{
	    for (x = baris1 - 1; x < baris2; x++)
	    {
	        if (papan[x][y] == ' ')
	        {
	            if (l < length)
	            {
	            	if(player[i].inputKata[l] == '!'){
	            		bacaKata[k] = tolower(huruf[m]);
	            		k++ ;
	            		m++ ;
					}else{
						bacaKata[k] = toupper(player[i].inputKata[l]);
						k++; l++;
					}
	            }
	            else
	            {
	                break;
	            }
	            if(putaran == 1){				// Khusus putaran 1, salah satu huruf harus menyentuh kotak bintang
	            	if(x == 7 && y == 7){
	            		player[i].cekKata = true;
					}
				}
	        }
	        else
	        {
	            bacaKata[k] = papan[x][y];
	            k++ ;
	            count++ ;
	        }
	    }
	}
	length = strlen(player[i].inputKata);
	if(putaran == 1){
		if(player[i].cekKata == false){
			putaran = 0;					// Jika player pertama tidak membentuk kata di tengah, player selanjutnya harus membentuk kata di tengah
		}else{
			if(posisiKata == 1){
				if(kolom1-1+length+count > kolom2){
					player[i].cekKata = false;
					putaran = 0;
				}
			}else{
				if(baris1-1+length+count > baris2){
					player[i].cekKata = false;
					putaran = 0;
				}
			}
		}
	}
	if(putaran != 1){
		if(count > 0){
			if(baris1 <= 15 && kolom1 <= 15 && baris2 <= 15 && kolom2 <= 15){	// Kata tidak boleh melewati papan
				if(posisiKata == 1){
					if(papan[baris1-1][kolom1-2] == ' ' && papan[baris2-1][kolom2] == ' ' && kolom1-1+length+count <= kolom2){		// Pada kolom sebelum dan sesudah inputan, harus kosong tidak boleh berisi huruf
	    				player[i].cekKata = true;
					}
					// Bila input kata di ujung kotak, maka tidak perlu di cek kotak sebelumnya kosong atau tidak
					if(kolom1 == 1){
						if(papan[baris2-1][kolom2] == ' ' && kolom1-1+length+count <= kolom2){
							player[i].cekKata = true;
						}
					}
					if(kolom2 == 15){
						if(papan[baris1-1][kolom1-2] == ' ' && kolom1-1+length+count <= kolom2){
							player[i].cekKata = true;
						}
					}
				}else{
					if(papan[baris1-2][kolom1-1] == ' ' && papan[baris2][kolom2-1] == ' ' && baris1-1+length+count <= baris2){		// Pada baris sebelum dan sesudah inputan, harus kosong tidak boleh berisi huruf
	    				player[i].cekKata = true;
					}
					// Bila input kata di ujung kotak, maka tidak perlu di cek kotak sebelumnya kosong atau tidak
					if(baris1 == 1){
						if(papan[baris2][kolom2-1] == ' ' && baris1-1+length+count <= baris2);
							player[i].cekKata = true;
					}
					if(baris2 == 15){
						if(papan[baris1-2][kolom1-1] == ' ' && baris1-1+length+count <= baris2);
							player[i].cekKata = true;
					}
				}
			}
		}
	}
	if(posisiKata == 1){
		if(baris1 != baris2){
			player[i].cekKata = false;
		}
	}else{
		if(kolom1 != kolom2){
			player[i].cekKata = false;
		}
	}
}

// Untuk mengecek apakah kata yang diinput player sesuai dengan huruf yang dimiliki
void cekBlokHuruf(int i){
	int j, k, count;
	int length;
	length = strlen(player[i].inputKata);
	for (j = 0; j < length; j++)
        {
            count = 0;
            for (k = 0; k < 7; k++)
            {
                if (toupper(player[i].inputKata[j]) == player[i].blokHuruf[k])
                {
                    player[i].blokHuruf[k] = ' ';
                    count++; // Bila ada huruf yang sama maka dihitung
                    break;
                }
            }
            if (count < 1)
            { // Bila tidak ada huruf yang sama maka input kata salah
                player[i].cekKata = false;
                break;
            }else{
            	player[i].cekKata = true;
			}
        }
}

// Untuk mengecek, apakah di sekitar inputan player terbentuk kata lain
void cekSekitarKata(int i, int posisiKata, int baris1, int kolom1, int baris2, int kolom2, char *huruf){
	int x = baris1 - 1, y = kolom1 - 1;
	int o = baris2 - 1, p = kolom2 - 1;
	int h=0, j=0, k=0, l=0, m=0, n=0, q=0, tampungSkor, length;
	int awal, akhir;
	char bacaKata[15];
	tampungSkor = player[i].skor;
	if(posisiKata == 1){
		for(y = kolom1-1; y < kolom2; y++){
			h=0, j=0, k=0, l=0, m=0, n=0;
			if(papan[x][y] == ' '){					// Proses pengecekan hanya dilakukan di sekitar huruf yang diinpput user
				memset(bacaKata, 0, strlen(bacaKata)); 	// Mengosongkan string
				awal=0; akhir=0;
				for(k = baris1-2; k >= 0; k--){				// Cek apakah di atas input ada huruf lain
					if(papan[k][y] != ' '){
						awal = k;
					}else{
						break;
					}
				}
				for(l = baris1; l < 15; l++){				// Cek apakah di bawah input ada huruf lain
					if(papan[l][y] != ' '){
						akhir = l;
					}else{
						break;
					}
				}
				if(awal > 0){
					if(akhir == 0){
						akhir = baris1 - 1;
					}
				}
				if(akhir > 0){
					if(awal == 0){
						awal = baris1-1;
					}
				}
				for(m = awal; m <= akhir; m++){
					if(m > 0){
						if(papan[m][y] != ' '){
							bacaKata[n] = papan[m][y];
							n++ ;
						}else{
							if(player[i].inputKata[q] == '!'){
								bacaKata[n] = tolower(huruf[h]);
								n++; h++ ;
							}else{
								bacaKata[n] = toupper(player[i].inputKata[q]);
								n++ ;
							}
						}
					}
				}
				length = strlen(bacaKata);
				if(length > 0){
					cekKamus(bacaKata);
					if(player[i].cekKata == true){
						hitungSkor(2,awal+1,y+1,bacaKata);
					}else{
						if(player[i].skor != tampungSkor){
							player[i].skor =  tampungSkor;
							break;
						}else{
							break;
						}
					}
				}
				q++ ;
			}
		}
	}else{
		for(x = baris1-1; x < baris2; x++){
			h=0, j=0, k=0, l=0, m=0, n=0;
			if(papan[x][y] == ' '){					// Proses pengecekan hanya dilakukan di sekitar huruf yang diinpput user
				memset(bacaKata, 0, strlen(bacaKata)); 	// Mengosongkan string
				awal=0; akhir=0;
				for(k = kolom1-2; k >= 0; k--){				// Cek apakah di kiri input ada huruf lain
					if(papan[x][k] != ' '){
						awal = k;
					}else{
						break;
					}
				}
				for(l = kolom1; l < 15; l++){				// Cek apakah di kanan input ada huruf lain
					if(papan[x][l] != ' '){
						akhir = l;
					}else{
						break;
					}
				}
				if(awal > 0){
					if(akhir == 0){
						akhir = kolom1-1;
					}
				}
				if(akhir > 0){
					if(awal == 0){
						awal = kolom1-1;
					}
				}
				for(m = awal; m <= akhir; m++){
					if(m > 0){
						if(papan[x][m] != ' '){
							bacaKata[n] = papan[x][m];
							n++ ;
						}else{
							if(player[i].inputKata[q] == '!'){
								bacaKata[n] = tolower(huruf[h]);
								n++; h++ ;
							}else{
								bacaKata[n] = toupper(player[i].inputKata[q]);
								n++ ;
							}
						}
					}
				}
				length = strlen(bacaKata);
				if(length > 0){
					cekKamus(bacaKata);
					if(player[i].cekKata == true){
						hitungSkor(1,x+1,awal+1,bacaKata);
					}else{
						if(player[i].skor != tampungSkor){
							player[i].skor = tampungSkor;
							break;
						}else{
							break;
						}
					}	
				}
				q++ ;	
			}
		}
	}
}

void cekKamus(char *bacaKata)
{

#define BUFFER_SIZE 1000 // Definisikan penyimpanan sementara
    int indexOf(FILE * fptr, const char *word, int *ine, int *col);

    FILE *fptr;
    char path[100];
    char word[50];
    char tampung[17];
    memset(tampung, 0, strlen(tampung)); // Mengosongkan string
    int line, col, i, j, k=1, length;
    int pilihLevel;

    if (player[0].giliran == true)
    { // Cek sekarang giliran siapa
        i = 0;
    }
    else
    {
        i = 1;
    }
    length = strlen(bacaKata);
    tampung[0] = ' ';
    for(j=0; j<length; j++){
    	tampung[k] = tolower(bacaKata[j]);
    	k++ ;
	}
	tampung[k] = ' ';
	strncpy(word, tampung, 50);
    // Menentukan Kamus yang akan digunakan berdasarkan level

    fptr = fopen("kamusSulit.txt", "r");

    if (fptr == NULL)
    {
        gotoxy(78, 30);
        printf("Kamus Tidak Dapat Dibuka");

        exit(EXIT_FAILURE);
    }

    // Cari indeks kata di fptr
    indexOf(fptr, word, &line, &col);

    if (line != -1)
    {
        gotoxy(78, 30);
        printf("Kata %s ada di dalam kamus ", word);
        Sleep(3000);
        player[i].cekKata = true;
    }
    else
    {
        gotoxy(78, 30);
        printf("Kata %s tidak ada di dalam Kamus ", word);
        Sleep(3000);
        player[i].cekKata = false;
    }
    // tutup file
    fclose(fptr);
}

int indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;
    *line = -1;
    *col = -1;
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;
        // Cari kata
        pos = strstr(str, word);
        if (pos != NULL)
        {
            // Ini untuk nampilin indeks kaya baris dan kolomnya, tp ga dimunculin di atas nya heheh
            *col = (pos - str);
            break;
        }
    }
    // Kalo katanya ga ketemu, return -1
    if (*col == -1)
        *line = -1;
    return *col;
}

/*Jika inputan kata salah blok huruf tidak akan berkurang*/
void resetBlokHuruf()
{
    int i, j=0, k=0, length;

    if (player[0].giliran == true)
    { // Cek sekarang giliran siapa
        i = 0;
    }
    else
    {
        i = 1;
    }
    length = strlen(player[i].inputKata);
    for(k = 0; k < 7; k++){
    	if(player[i].blokHuruf[k] == ' '){
    		player[i].blokHuruf[k] = toupper(player[i].inputKata[j]);
    		j++ ;
		}
	}
}

/*Tempel kata yang diinput user ke papan*/
void tempelKata(int posisiKata, int baris1, int kolom1, char *huruf)
{
    int k = kolom1 - 1, l = baris1 - 1, j = 0, length, m=0;
    int i;
    if (player[0].giliran == true)
    { // Cek sekarang giliran siapa
        i = 0;
    }
    else
    {
        i = 1;
    }
    length = strlen(player[i].inputKata);
    while (j < length)
    {
        if (posisiKata == 1)
        {
            if (papan[l][k] == ' ')
            {
            	if(player[i].inputKata[j] == '!'){
            		papan[l][k] = tolower(huruf[m]);
            		m++ ;
				}else{
					papan[l][k] = toupper(player[i].inputKata[j]);	
				}
                k++;
                j++;
            }
            else
            {
                k++;
            }
        }
        else
        {
            if (papan[l][k] == ' ')
            {
            	if(player[i].inputKata[j] == '!'){
            		papan[l][k] = tolower(huruf[m]);
            		m++ ;
				}else{
					papan[l][k] = toupper(player[i].inputKata[j]);
				}
                l++;
                j++;
            }
            else
            {
                l++;
            }
        }
    }
}

/*Menghitung Skor Pemain*/
void hitungSkor(int posisiKata, int baris1, int kolom1, char *bacaKata)
{
    int i, j, k, length, tampungSkor = 0;
    bool doubleWord = false, tripleWord = false;
    if (player[0].giliran == true)
    { // Cek sekarang giliran siapa
        k = 0;
    }
    else
    {
        k = 1;
    }
    length = strlen(bacaKata);
    int m = baris1 - 1, n = kolom1 - 1;
    for (i = 0; i < length; i++)
    {
        tampungSkor = 0; // Untuk nampung skor per huruf
        // Cek poin per huruf
        for (j = 0; j < 25; j++)
        {
            if (bacaKata[i] == daftarHuruf[j].huruf)
            {
                tampungSkor = tampungSkor + daftarHuruf[j].poin;
                break;
            }
        }
        // Cek bonus pada papan
        switch (bonus[m][n])
        {
        case 1:
            tampungSkor = tampungSkor * 2;
            break;
        case 2:
            tampungSkor = tampungSkor * 3;
            break;
        case 3:
            doubleWord = true;
            break;
        case 4:
            tripleWord = true;
            break;
        }
        if (posisiKata == 1)
        {
            n++;
        }
        else
        {
            m++;
        }
        player[k].skor = player[k].skor + tampungSkor;
    }
    if (doubleWord == true)
    {
        player[k].skor = player[k].skor * 2;
    }
    if (tripleWord == true)
    {
        player[k].skor = player[k].skor * 3;
    }
}

/*Mencatat waktu pertama dihitung*/
int StartTime()
{
    clock_t startInput;
    startInput = clock();
    return startInput;
}
/*Mencatat waktu terakhir dihitung*/
int EndTime()
{
    clock_t endInput;
    endInput = clock();
    return endInput;
}

/*Menampilkan status akhir pemain*/
void tampilPemenang()
{
    int input;
    	system("cls");
        printf("\n\n");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ    \n\n");
        printf("\t\t\t           GO SCRABBLE                       ");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ     \n");
        if (player[0].skor != player[1].skor)
        {
            printf("\t\t\t             SELAMAT                    	\n");
            printf("\t\t\t                                          \n");
            printf("\t\t\t                        					\n");
            if (player[0].skor > player[1].skor)
            {
                printf("\t\t\t             %s        		     	\n", player[0].nama);
            }
            if (player[0].skor < player[1].skor)
            {
                printf("\t\t\t             %s        		     	\n", player[1].nama);
            }
            printf("\t\t\t             MENANG                	    \n");
        }
        else
        {
            printf("\t\t\t                                   		 \n");
            printf("\t\t\t                                           \n");
            printf("\t\t\t                        					 \n");
            printf("\t\t\t            PERMAINAN         		     \n");
            printf("\t\t\t             SERI !!                	     \n");
        }
        printf("\t\t\t                                 		     \n");
        Sleep(3000);
	
	fileSkor();
    skorAkhir();
}

int skorAkhir()
{
    int input;
    system("cls");
    do
    {
        printf("\n\n");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ    \n\n");
        printf("\t\t\t           GO SCRABBLE                       ");
        printf("\n\n\t\t\tอออออออออออออออออออออออออออออออออ      \n");
        printf("\t\t\t              SKOR                         \n");
        printf("\t\t\t                                           \n");
        printf("\t\t\t             %s : %d                 \n", player[0].nama, player[0].skor);
        printf("\t\t\t             %s : %d                 \n", player[1].nama, player[1].skor);
        printf("\t\t\t                                           \n");
        printf("\t\t\t             1. Ulang                         \n");
        printf("\t\t\t         2. Kembali ke Menu                   \n");
        printf("\t\t\t      Input Pilihan [1/2]: ");
        scanf("%d", &input);
    } while (input != 1 && input != 2); // Player hanya dapat input huruf 1 atau 2

    if (input == 1)
    {
        mulaiPermainan();
    }
    if (input == 2)
    {
        main();
    }
    return input;
}
