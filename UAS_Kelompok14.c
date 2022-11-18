//Evelio Excellenta - 2006579705 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct Data { 				//struct data
	int kode; 				//variabel kode barang
	int jumlah; 			//variabel banyak data yang diinput
	char variety[20]; 		//variabel jenis barang
	int berat; 				//variabel berat barang
	int tanggal;			//variabel tanggal masuk/keluar barang
	
	struct Data *next;		//untuk linked list	
	
	struct Data *leftTree;	//untuk binary search tree 
	struct Data *rightTree;	//untuk binary search tree 
	
	int treeData;
	
}* headIn, * headOut, *tempIn, *tempOut;

struct Data urutan[100]; //array untuk sorting
int k=0;

//struct baru untuk melakukan sorting
struct node{
    int kode;           
    char variety[20];   
    int berat;             
    int tanggal;       
    
    struct node* left;
    struct node* right;
};

int menu;						//variabel untuk memilih menu
int i; 							//varibel untuk looping for
int pointIn = 0, pointOut=0;	//variabel untuk urutan data
int jumlah = 0; 				//variabel jumlah data yang diinput
char jenis[5][20] = {"Ikan", "Kepiting", "Cumi-cumi", "Kerang", "Lobster"};

//fungsi dasar
int hitungBerat(int opsi, int kodedicari); 					//fungsi untuk menghitung berat
void insert(int opsi, int kode, char* variety, int berat, int tanggal); //fungsi untuk membuat linked list

//fungsi fungsi menu
void masukan(); 												//fungsi untuk menginput data
void historiMasuk(struct Data * tempIn);  						//fungsi untuk melihat histori barang masuk
void keluaran(); 												//fungsi untuk menginput barang keluar
void historiKeluar(struct Data * tempOut); 						//fungsi untuk melihat histori barang keluar
void cekstock(); 												//fungsi untuk melihat barang secara keseluruhan
void cari(); 													//fungsi untuk mencari barang berdasarkan kode barang
void searchDate(struct Data * tempIn, struct Data * tempOut); 	//fungsi untuk mencari barang berdasarkan tanggal
void panduan(); 												//fungsi untuk menampilkan panduan
void ke_menu(); 												//fungsi untuk kembali ke menu

//fungsi fungsi untuk sorting dengan BST	
struct node* newNodeSort(int data);
struct node* insertSort(struct node* node, int data); //proses melakukan input akar-akar Tree
void urut(struct node* node);

//fungsi fungsi untuk mencari data terkecil dengan BST
struct Data* newNode(int treeData);
struct Data* insertTree(struct Data* Data, int treeData); //proses melakukan input akar-akar Tree
int minValue(struct Data* Data);		
		
int main(){ 			//function main
	headIn=NULL; 		//Inisialisasi nilai headIn
	headOut=NULL; 		//Inisialisasi nilai headOut		
	int menu; 			
	do {
		printf(" ---------------- PROGRAM PENDATAAN STOCK HASIL LAUT ---------------");     
		printf( " \n\nMENU UTAMA :\n");
		printf( "___________________________________________________________________\n\n");
    	printf( " 1. Input Barang Masuk\n\n");
    	printf( " 2. Histori Barang Masuk\n\n");
    	printf( " 3. Input Barang Keluar\n\n");
    	printf( " 4. Histori Barang keluar\n\n");
    	printf( " 5. Cek Seluruh Stock\n\n");
    	printf( " 6. Mencari Stock Barang\n\n");
    	printf( " 7. Mencari Barang Sesuai Tanggal\n\n");
    	printf( " 8. Panduan\n\n");
    	printf( " 9. Keluar\n\n");
    	printf( " _____________________________\n\n");
    	printf( " Masukan Pilihan Anda (1 - 9) : "); 
    	scanf ("%d", &menu); 

	if (menu < 1 || menu > 9) { //error handling sehingga hanya bisa angka sesuai menu
		system("cls");
  		printf ("Input yang anda masukkan tidak tersedia pada menu, silahkan gunakan angka 1-9 untuk memilih\n");
  		ke_menu();
       	}
       	
	switch(menu) { 
		case 1:
			masukan();
			break;
		case 2:
   			historiMasuk(tempIn); 
			break;
		case 3:
			keluaran(); 
			break;
		case 4:
			historiKeluar(tempOut);  
			break;
		case 5:
			cekstock();	
			break;
		case 6:
       		cari();				
			break;
		case 7:
			searchDate(tempIn,tempOut);
			break; 
		case 8:
			panduan();
			break;
		}
	}
	
	while (menu != 9);
	system("cls");
	printf ("============ THANK YOU FOR USING OUR PROGRAM ============");

	return 0;
}

void insert(int opsi, int kode, char* variety, int berat, int tanggal){
	if (opsi==0){ //untuk data masuk
		struct Data * dataIn = (struct Data *) malloc(sizeof(struct Data));
    	
		dataIn->kode = kode;
    	strcpy(dataIn->variety, variety);
   		dataIn->berat = berat;
    	dataIn->tanggal = tanggal;
    	dataIn->next = NULL;    	

   		//men-set dataIn sebagai head baru saat headIn = NULL
    	if(headIn==NULL){
    	    headIn = dataIn;
    	}

   	 	else{
   	     	//memasukkan data saat list tidak kosong
    		dataIn->next = headIn;
  	    	headIn = dataIn;
 	   }
	}

    if (opsi==1){ //untuk data keluar
 		struct Data * dataOut = (struct Data *) malloc(sizeof(struct Data));
 		
 		dataOut->kode = kode;
 		strcpy(dataOut->variety, variety);
 	  	dataOut->berat = berat;
 		dataOut->tanggal = tanggal;
 		dataOut->next = NULL;
    
  		if(headOut==NULL){
        	//men-set dataOut sebagai head baru saat headIn = NULL
    	    headOut = dataOut;
    	}

    	else{
    	    //memasukkan data saat list tidak kosong
    	    dataOut->next = headOut;
     		headOut = dataOut;
    	}
	}
}


//proses sorting mulai di sini
struct node* newNodeSort(int data){	//untuk head pada tree untuk sorting
  struct node* node = (struct node*) malloc(sizeof(struct node));
  node->tanggal  = data;
  node->left  = NULL;
  node->right = NULL;
   
  return(node);
}

struct node* insertSort(struct node* node, int data){  //proses melakukan input akar-akar Tree

  if (node == NULL)
    return(newNodeSort(data)); 
  
  else
  {
    if (data <= node->tanggal)
        node->left  = insertSort(node->left, data);
  
    else
        node->right = insertSort(node->right, data);
    return node;
  }
}	

void urut(struct node* node) { //untuk melakukan sorting
  struct node* current = node;

  if (node != NULL) {
    urut (current->left);
    urutan[k++].tanggal =node->tanggal ; 
    urut (current->right);  
  }
}
//proses sorting berhenti disini


void masukan(){ //variabel untuk menambahkan data barang yang masuk
	int code; //variabel untuk error handling sehingga hanya bisa menginput nilai kode tertentu
	int berat;
	int tanggal;
	
	system ("cls");
	printf("================= MENU INPUT BARANG MASUK =================\n\n");
	printf("Masukkan Jumlah Barang Yang Akan Didata : "); scanf("%d", &jumlah); //jumlah data yang diinput
	printf( "_________________________________________________________________\n");
			
	printf("\n Kode 0 = Ikan \n kode 1 = Kepiting \n kode 2 = Cumi-cumi \n kode 3 = Kerang \n kode 4 = Lobster\n\t\t\t   "); //keterangan kode yang sesuai dengan barang
		
	for(i = 0; i < jumlah; i++){  //loop input data
		printf("\n\nDATA BARANG KE-%d",pointIn + 1);
		printf("\n\tMasukkan Kode\t : "); scanf(" %d", &code); //kode yang ingin di gunakan dimasukkan ke variabel code
				
		if(code < 0 || code > 4){ //error handling
			printf ("Barang dengan kode yang anda masukkan tidak tersedia, silahkan kembali ke menu\n");
			i--;
		}
		else {
			printf("\tJenis\t\t : %s\n", jenis[code]); //print jenisnya secara otomatis
			printf("\tMasukkan Berat\t : "); scanf(" %d", &berat ); //memasukkan berat
			printf("\tMasukkan Tanggal masuk (YYYYMMDD)\t : ");scanf(" %d", &tanggal); //memasukkan tanggal
			pointIn++;
			insert(0, code, jenis[code], berat, tanggal);
		}				
	}
	ke_menu(); //back to menu
}

void historiMasuk(struct Data * tempIn){
	system ("cls");
    tempIn = headIn;
  	struct node* root = NULL;

	while(tempIn!=NULL){
	
  		if(root==NULL){
   			root = insertSort(root, tempIn->tanggal);
  		}
  		else {
 	 		insertSort(root, tempIn->tanggal);
		}
		tempIn = tempIn->next;
	}
	tempIn = headIn;
	
	printf("*****  DATA BARANG MASUK ***** \n" );
	printf("------------------------------------------------------------------\n");
    printf("|  TANGGAL  |  CODE  |      NAME      |  WEIGHT | \n");
    printf("------------------------------------------------------------------\n");
    
   	k=0;
 	urut(root);

	for(int i=0;i<100;i++){
		tempIn = headIn;	
    	while (tempIn != NULL) {
    		if(urutan[i].tanggal==tempIn->tanggal){
    		printf("    %d        %-5d     %-10s          %d        \n", tempIn->tanggal, tempIn->kode, tempIn->variety, tempIn->berat);
		}
        tempIn = tempIn->next;
    	}
	}
    ke_menu();
}

void keluaran(){ //variabel untuk menambahkan data barang yang masuk
	int code; //variabel untuk error handling sehingga hanya bisa menginput nilai kode tertentu
	int berat;
	int tanggal;

	system ("cls");
	printf("================= MENU INPUT BARANG KELUAR =================\n\n");
	printf("Masukkan Jumlah Barang Yang Akan Didata : "); scanf("%d", &jumlah); //jumlah data yang diinput
	printf( "_________________________________________________________________\n");
			
	printf("\n Kode 0 = Ikan \n kode 1 = Kepiting \n kode 2 = Cumi-cumi \n kode 3 = Kerang \n kode 4 = Lobster\n\t\t\t   "); //keterangan kode yang sesuai dengan barang
		
	for(i = 0; i < jumlah; i++){  //loop input data
		printf("\n\nDATA BARANG KE-%d",pointOut + 1);
		printf("\n\tMasukkan Kode\t : "); scanf(" %d", &code); //kode yang ingin di gunakan dimasukkan ke variabel code
				
		if(code < 0 || code > 4){ //error handling
			printf ("Barang dengan kode yang anda masukkan tidak tersedia, silahkan kembali ke menu\n");
			i--;
		}
				
		else {
			printf("\tJenis\t\t : %s\n", jenis[code]); //print jenisnya secara otomatis
			printf("\tMasukkan Berat\t : "); scanf(" %d", &berat ); //memasukkan berat
			printf("\tMasukkan Tanggal masuk (YYYYMMDD)\t : ");scanf(" %d", &tanggal); //memasukkan tanggal
			pointOut++;
			insert(1, code, jenis[code], berat, tanggal);
		}				
	}
	ke_menu(); //back to menu
}

void historiKeluar(struct Data * tempOut)
{
	system ("cls");
    tempOut = headOut;

  	struct node* root = NULL;

	while(tempOut!=NULL){
	
  		if(root==NULL){
   			root = insertSort(root, tempOut->tanggal);
  		}
  		else {
 	 		insertSort(root, tempOut->tanggal);
		}
		tempOut = tempOut->next;
	}

	tempOut = headOut;
	
	printf("*****  DATA BARANG KELUAR ***** \n" );
	printf("------------------------------------------------------------------\n");
    printf("|  TANGGAL  |  CODE  |      NAME      |  WEIGHT | \n");
    printf("------------------------------------------------------------------\n");
    
   	k=0;
 	urut(root);

	for(int i=0;i<100;i++){
		tempOut = headOut;	
	    while (tempOut != NULL) {
	    	if(urutan[i].tanggal==tempOut->tanggal){
	    	printf("    %d        %-5d     %-10s          %d        \n", tempOut->tanggal, tempOut->kode, tempOut->variety, tempOut->berat);
			}
	        tempOut = tempOut->next;
	    }
	}
    ke_menu();
}

int hitungBerat(int opsi, int kodedicari){ //fungsi untuk proses perhitungan berat,
	int sum = 0; //variabel untuk hasil penjumlahan
		
	struct Data * temp;
	if (opsi==0){
   		temp = headIn;
   	}
 
    else {
    	temp = headOut;
	}
	
	while(temp!=NULL){
        if (temp->kode == kodedicari){
        	sum=sum+temp->berat;
    	}	
    	temp=temp->next;
    }
    
	return sum; //return hasil dari penjumlahan di sum  
}

//proses mencari minimum value
struct Data* newNode(int treeData){
  struct Data* Data = (struct Data*) malloc(sizeof(struct Data));
  Data->treeData  = treeData;
  Data->leftTree  = NULL;
  Data->rightTree = NULL;
   
  return(Data);
}

struct Data* insertTree(struct Data* Data, int treeData){ //proses melakukan input akar-akar Tree
  if (Data == NULL)
    return(newNode(treeData)); 
 
  else{
    if (treeData <= Data->treeData)
        Data->leftTree  = insertTree(Data->leftTree, treeData);
 
    else
        Data->rightTree = insertTree(Data->rightTree, treeData);
        
    return Data;
  }
}

int minValue(struct Data* Data) { //proses pencarian minimum
  struct Data* current = Data;
 
  while (current->leftTree != NULL){
    current = current->leftTree;
  }
 
  return(current->treeData);
}
////////////////////////////////////////////////////////////////////////

void cekstock(){ //function untuk cek stock barang keseluruhan
	int beratTotal=0;
	struct Data* root = NULL;
	system("cls");
	printf("*****  INVENTORY ***** \n" );
	printf("------------------------------------------------------------------\n");
    printf("|  CODE  |      NAME      |  WEIGHT IN | WEIGHT OUT | STOCK | \n"); //stock adalah barang masuk dikurang barang keluar
    printf("------------------------------------------------------------------\n");
 
    for (i = 0; i < 5; i++){
    	printf("    %d        %-15s     %d          %-5d      %-5d      \n", i, jenis[i], hitungBerat(0, i), hitungBerat(1, i), hitungBerat(0, i) - hitungBerat(1, i)); //menggunakan function hitungBerat untuk melakukan perhitungan
  		beratTotal=hitungBerat(0, i) - hitungBerat(1, i);		  
 
  		if(root==NULL){root = insertTree(root, beratTotal);}
 
  		else {insertTree(root, beratTotal);}
	}
	
	printf("\n Stock barang paling sedikit di gudang adalah sebesar %d \n barang tersebut adalah :\n", minValue(root));
	
	for (i = 0; i < 5; i++){
		if ((hitungBerat(0, i) - hitungBerat(1, i)) == minValue(root)){
			printf ("~%s \n", jenis[i]);
		}
	}
	
	if(minValue(root)<50){
		printf("Barang yang beratnya dibawah 50kg harap di-stock kembali\n");
	}
	
    printf("------------------------------------------------------------------\n");
	
	ke_menu();
}

void cari(){ //function untuk mencari barang dengan memasukkan kode
	int find; 
	system("cls");
	printf ("Masukkan kode barang yang ingin anda cari : \n >");scanf("%d", &find);
	
	if (find < 0 || find > 4){ //error handling
	  	printf ("\nBarang dengan kode yang anda masukkan tidak tersedia, silahkan kembali ke menu\n");
	}
	
	else{
		printf("\nKode Barang : %d\n", find);
		printf("Jenis Barang : %s\n", jenis[find]);
		printf("Berat Barang : %d\n", hitungBerat(0, find) - hitungBerat(1, find));		
	}
	ke_menu();
}

void searchDate(struct Data * tempIn, struct Data * tempOut){ 	//function untuk melakukan pencarian barang yang masuk/keluar pada tanggal tertentu
	int searchDate, masuk_or_keluar; 							//searchDate untuk variabel tanggal yang ingin dicari, masuk_or_keluar untuk variabel memilih untuk melihat barang masuk/keluar
	tempIn=headIn;
	tempOut=headOut;											
	int markIn=0, markOut=0; 									//untuk error handling, apa bila tidak ada barang yang masuk/keluar di tanggal tersebut
	
	system("cls");
	printf("Data tanggal barang masuk & keluar\n");
	printf("Tanggal masuk/keluar? (Tekan 1 untuk tanggal masuk | tekan 2 untuk tanggal keluar)\n"); scanf("%d", &masuk_or_keluar);
	
	if(masuk_or_keluar == 1){
		printf("Input tanggal : (YYYYMMDD)\n");	scanf("%d", &searchDate); //memasukkan tanggal
		printf("\nBarang masuk pada tanggal %d : ", searchDate);
		
		printf("\n*****  DATA BARANG  ***** \n" );
		printf("------------------------------------------------------------------\n");
		printf("|  CODE  |      NAME      |  WEIGHT | STOCK | \n"); //stock adalah barang masuk dikurang barang keluar
		printf("------------------------------------------------------------------\n");
				    
		while(tempIn!=NULL){
			if ((tempIn)->tanggal == searchDate){
        			printf("    %d        %-15s     %d          %-5d        \n", tempIn->kode, tempIn->variety, tempIn->berat, tempIn->tanggal);
					markIn++;
			}
			tempIn = tempIn->next;
			}
			printf("------------------------------------------------------------------\n");

			if (markIn==0)	{  //bila tidak ada barang yang masuk
				printf("\n\nTidak ada barang yang masuk pada tanggal %d \n", searchDate);
			}
	}
	
	else if(masuk_or_keluar == 2){
		printf("Input tanggal : (YYYYMMDD)\n");	scanf("%d", &searchDate);//memasukkan tanggal
		printf("\nBarang keluar pada tanggal %d : ", searchDate);
		
		printf("\n*****  DATA BARANG  ***** \n" );
		printf("------------------------------------------------------------------\n");
		printf("|  CODE  |      NAME      |  WEIGHT | STOCK | \n"); //stock adalah barang masuk dikurang barang keluar
		printf("------------------------------------------------------------------\n");
				    
		while(tempOut!=NULL){
			if ((tempOut)->tanggal == searchDate){
        			printf("    %d        %-15s     %d          %-5d        \n", tempOut->kode, tempOut->variety, tempOut->berat, tempOut->tanggal);
					markOut++;
			}		
			tempOut = tempOut->next;
			}
			printf("------------------------------------------------------------------\n");
		
		if (markOut==0)	{ //bila tidak ada barang yang keluar
			printf("\n\nTidak ada barang yang keluar pada tanggal %d \n", searchDate);
		}
	}
	
	else{
		printf("Kembali ke menu, lalu tekan 7 untuk melanjutkan pencarian\n");
	}
	ke_menu();
}

void panduan(){ //function untuk menampilkan panduan
	system("cls");
	printf("\n***PANDUAN***\n");

	printf("1. Pada menu Input Barang Masuk, pengguna dapat memasukkan data hasil tangkapan laut berdasarkan tanggal masuk, kode, jenis, dan berat;\n");

	printf("2. Pada menu Histori Barang Masuk, pengguna dapat melihat data barang yang masuk. Data yang ditampilkan pada menu ini disortir berdasarkan tanggal masuknya;\n"); 
	
	printf("3. Pada menu Input Barang Keluar, pengguna dapat memasukkan data hasil tangkapan laut berdasarkan tanggal keluar, kode, jenis, dan berat;\n");

	printf("4. Pada menu Histori Barang keluar, pengguna dapat melihat data barang yang masuk. Data yang ditampilkan pada menu ini disortir berdasarkan tanggal keluarnya;\n");
	
	printf("5. Pada menu Cek Seluruh Stock, pengguna dapat melihat seluruh stock berdasarkan kode yang disortir / diurutkan;\n");
	
	printf("6. Pada menu Mencari Stock Barang, pengguna dapat melihat informasi barang secara spesifik dengan memasukkan kode uniknya;\n");
	
	printf("7. Pada menu Mencari Barang Sesuai Tanggal, pengguna dapat melihat barang apa saja yang masuk atau keluar pada tanggal yang ingin di cari;\n");
	
	printf("8. Pada menu Panduan, pengguna mendapat panduan mengenai cara kerja program serta kode unik masing-masing jenis;\n");
	
	printf("9. Pada menu Keluar, pengguna akan keluar dari program.\n");
	ke_menu(); 
}

void ke_menu(){ //function untuk kembali ke menu
	printf("\n\n\t\t\tPress any key to continue.....");
	getch();
	system("cls");
}
