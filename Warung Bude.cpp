#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const char* detectOS() { // untuk mendeteksi OS
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}


struct dish { // struct yang disediakan untuk menampung menu makanan
	char nama [255];
	int harga;
	int qty;
	dish *next, *prev;
}*head,*tail;


dish *createNode(char *nama, int harga, int qty){ // fungsi untuk membuat node dish
	dish *temp = (dish*)malloc(sizeof(dish));
	strcpy(temp->nama, nama);
	temp->harga = harga;
	temp->qty = qty;
	temp->next = temp->prev = NULL;
	return temp;
}


void pushHead(char *nama, int harga, int qty){ // fungsi untuk menempatkan node di head (awal)
	dish *temp = createNode(nama, harga, qty);
	if(head == NULL){
		head = tail = temp;
	}
	else{
		head->prev = temp;
		temp->next = head;
		head = temp;
	}
}


void pushTail (char* nama, int harga, int qty){// fungsi untuk menempatkan node di tail (akhir)
	dish *temp = createNode(nama, harga , qty);
	if(head == NULL){
		head = tail = temp;
	}
	else {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
}


void pushMid (char *nama, int harga, int qty){//fungsi untuk menempatkan node sesuai urutan dari harganya (agar tersort)
	if(head == NULL){
		dish *temp = createNode(nama, harga, qty);
		head = tail = temp;
	}
	else if (harga <= head->harga){
		pushHead(nama, harga, qty);
	}
	else if (harga >= tail->harga){
		pushTail(nama, harga, qty);
	}
	else {
		dish *temp = createNode(nama, harga, qty);
		dish *curr = head;
		
		while(curr->harga <= harga){
			curr = curr->next;
		}
		
		curr->prev->next = temp;
		temp->prev = curr->prev;
		curr->prev = temp;
		temp->next = curr;
	}
}

void popHead(){ //fungsi untuk menghapus node head (awal)
	if(head && head == tail){
		head = tail = NULL;
		free(head);
	}
	else {
		dish *newHead = head->next;
		head->next = newHead->prev = NULL;
		free(head);
		head = newHead;
	}
}

void popTail(){//fungsi untuk menghapus node tail (akhir)

	if(head && head == tail){
		head = tail = NULL;
		free(head);
	}
	else {
		dish *newTail = tail->prev;
		tail->prev = newTail ->next = NULL;
		free(tail);
		tail = newTail;
	}

}

int deleteMenu(const char *makananDelete){ //fungsi untuk menghapus node dengan nama yang ditentukan dari inpputan user
	
	dish *curr = head;
	if(!head){
		return -1;
	}
	else if (strcmp(head->nama, makananDelete) == 0){
		popHead();
		return 1;
	}
	else if (strcmp(tail->nama, makananDelete) == 0){
		popTail();
		return 1;
	}else{
		
		while(curr && curr->nama !=makananDelete){
			if(strcmp(curr->nama,makananDelete) == 0){
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				curr->next = curr->prev = NULL;
				free(curr);
				return 1;
			}
			curr = curr->next;
		}
		
	}
	return -1;
	
	
}

int maxMakanan;
int jarakMakanan = 40;
void printKarakter(int banyak, const char *karakter){ //fungsi untuk print suatu karakter berulang kali. Fungsi ini digunakan untuk mempermudah padding pada menu
	for(int i = 0; i < banyak ;i++){
		printf("%s", karakter);
	}
}
void printMenu() {// untuk print menu dengan padding agar tampilan rapi (centre)
	//judul
	printKarakter(89,"=");
	puts("");
	char judul [255] = "Bude's Menu"; 
	printf("%*s\n",50,judul);
	printKarakter(89,"=");
	puts("");
	
	//kategori
	printf(" No |");
	printKarakter(18," ");
	printf("Name");
	printKarakter(18," ");
	printf("|");
	printKarakter(6," ");
	printf("Quantity");
	printKarakter(6," ");
	printf("|");
	printKarakter(8," ");
	printf("Price");
	printKarakter(8," ");
	printf("|");
	puts("");
	
	dish *curr = head;
	//isi
	int nomor = 1;
	while(curr) {
		//nomor
		int nomorTemp;
		if(nomor < 10){
			nomorTemp = 3;
		}
		else if (nomor >= 10 && nomor < 100){
			nomorTemp = 3;
		}
		else{
			nomorTemp = 4;
		}
		printKarakter(4-nomorTemp," ");
		if(nomor >= 10 && nomor < 100){
			printf("%d", nomor);
		}
		else {
			printf("%d.", nomor);
		}
		printKarakter(4-nomorTemp, " ");
		printf("|");
		
		//nama makanan
		int flag = 0;
		int len = (jarakMakanan - strlen(curr->nama));
		if(len%2 == 1)flag = 1;
		len/=2;
		printKarakter(len," ");
		printf("%s", curr->nama);
		if(flag == 1){
			len++;
		}
		printKarakter(len, " ");
		printf("|");
		
		//qty
		printKarakter(8," ");
		printf("%.3d",curr->qty);
		printKarakter(9," ");
		printf("|");
		
		//price
		printKarakter(7, " ");
		printf("Rp.%d", curr->harga);
		if(curr->harga > 10000){
			printKarakter(6, " ");
		}
		else {
			printKarakter(7, " ");	
		}
		
		printf("|");
		
		
		
		
		puts("");
    	curr = curr->next;
    	nomor++;
	}
	printKarakter(89,"=");
	puts("");
}

//hashtable

const int maxElement = 26;

struct order { //struct untuk menampung makanan yang di order oleh customer
	char nama [255];
	int harga;
	int qty;
	order *orderNext, *orderPrev;
};

struct customer{//struct untuk menampung data customer
	char nama[255];
	customer *next;
	order *orderHead, *orderTail, *orderCurr;
}*headCustomer[maxElement], *tailCustomer[maxElement];


customer *createNodeCustomer(char *nama){// fungsi untuk membuat atau menyediakan suatu tempat di memori untuk struct customer
	customer *temp = (customer*)malloc(sizeof(customer));
	strcpy(temp->nama, nama);
	temp->next = NULL;
	temp->orderHead = temp->orderTail = temp->orderCurr = NULL;
	return temp;
}


unsigned long DJB2(char *str) { // fungsi hashing djb2
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % maxElement;
}


void insert(char *nama) { // fungsi untuk memasukkan data customer
	int index = DJB2(nama);
	if(headCustomer[index]){ 
		customer *temp = createNodeCustomer(nama);
		tailCustomer[index]->next = temp;
		tailCustomer[index] = temp;
  	}
	else{
		headCustomer[index] = tailCustomer[index] = createNodeCustomer(nama);
  }
}


void customerWarteg(){ // fungsi untuk melihat daftar nama customer keseluruhan yang datang di warung bude
	system("@cls||clear");
	printf("Customer's List\n");
	int ctr = 0;
	for(int i = 0; i < maxElement; i++){
		if(!headCustomer[i]){
			continue;
		}
		else if(headCustomer[i]){
			ctr++;
			printf("%d ", i);
			customer *curr = headCustomer[i];
			while(curr){
				printf("%s ", curr->nama);
				if(curr->next != NULL){
					printf("-> ");
				}
				curr = curr->next;
			}
		}
		if(ctr > 0){
			puts("");	
		}
	}
	if(ctr == 0){
		printf("None\n");
	}
	printf("Press enter to continue..");
	getchar();
}


int search(char *nama){//fungsi untuk mencari apakah nama yang diinput user terdaftar sebagai customer
	int flag = 0;
	for(int i = 0; i < maxElement; i++){
		if(!headCustomer){
			continue;
		}
		else if(headCustomer[i]){
			customer *curr = headCustomer[i];
			while(curr){
				if(strcmp(nama, curr->nama)==0){
					flag = 1;
					break;
				}
				curr = curr->next;
			}
		}
	}
	return flag;
}

order *createNodeOrder(char *namaMakanan, int harga, int dishQty){ // fungsi untuk membuat node order 
	order *temp = (order*)malloc(sizeof(order));
	strcpy(temp->nama, namaMakanan);
	temp->harga = harga * dishQty;
	temp->qty = dishQty;
	temp->orderNext = temp->orderPrev = NULL;
	return temp;
	
}
void orderCustomer(char *namaCustomer, int dishQty, char *namaMakanan, int harga){ // fungsi push tail pada linked list order
	for(int i = 0; i < maxElement; i++){
		if(!headCustomer){
			continue;
		}
		else if(headCustomer[i]){
			customer *customerCurr = headCustomer[i];
			while(customerCurr){
				if(strcmp(namaCustomer, customerCurr->nama) == 0){
					break;
				}
				customerCurr = customerCurr->next;
			}
			
			customerCurr->orderCurr = createNodeOrder(namaMakanan, harga, dishQty);

			if(customerCurr->orderHead == NULL){
				customerCurr->orderHead = customerCurr->orderTail = customerCurr->orderCurr; 
			}
			else {
				customerCurr->orderTail->orderNext = customerCurr->orderCurr;
				customerCurr->orderCurr->orderPrev = customerCurr->orderTail;
				customerCurr->orderTail = customerCurr->orderCurr;
				
			}
			
			
		}
	}
}

void cariMenu(char *namaMakanan, char *namaCustomer, int dishQty){ //fungsi untuk mencari dan validasi apakah makanan yang dipesan ada
	dish *curr = head;
	while(curr){
		if(strcmp(curr->nama, namaMakanan) == 0){
			curr->qty -= dishQty;
			break;
		}
		curr = curr->next;
	}
	if(curr->qty < 0){
		curr->qty += dishQty;
		printf("Out of Stock\n");
		getchar();
	}
	else if (curr->qty == 0){
		deleteMenu(curr->nama);
		orderCustomer(namaCustomer, dishQty, curr->nama, curr->harga);
	}
	else {
		orderCustomer(namaCustomer, dishQty, curr->nama, curr->harga);
	}
	
	return;

}


void menu1(){ // menampilkan menu - menu yang tersedia ketika user memilih menu 1
	system("@cls||clear");
	char dishName[255];
	int dishPrice = 0;
	int dishQty = 0;
	int dishNameFlag = 1;
	
	do{
		dishNameFlag = 1;
		printf("Insert the name of the dish [LowerCase letters]: ");
		scanf("%[^\n]", dishName);getchar();
		int len = strlen(dishName);
		
		for(int i=0; i < len; i++){
			if(dishName[i] == ' ')continue;
			else if(dishName[i] < 'a' || dishName[i] > 'z' ){
				dishNameFlag = 0;
				break;
			}
		}
		
		dish *curr = head;
		while(curr && curr->nama !=dishName){
			if(strcmp(curr->nama,dishName) == 0){
				dishNameFlag = 0;
				break;
			}
			curr = curr->next;
		}
		
	} while(dishNameFlag == 0);
	
	do{
		printf("Insert the price of the dish[1000..50000]:");
		scanf("%d", &dishPrice); getchar();
	} while(dishPrice < 1000 || dishPrice > 50000);
	
	
	do{
		printf("Insert the quantity of the dish[1..999]:");
		scanf("%d", &dishQty); getchar();
	} while(dishQty < 1 || dishQty > 999);
	
	pushMid(dishName, dishPrice, dishQty);
	printf("\nThe dish has benn added!\n");
	printf("\nPress enter to continue...");
	getchar();
}


void menu2(){// menampilkan menu - menu yang tersedia ketika user memilih menu 2
	char makananDelete[255];
	int flagMakananDelete = 1;
	system("@cls||clear");
	printMenu();
	flagMakananDelete = 1;
	printf("Insert dish's name to be deleted: ");
	scanf("%[^\n]", makananDelete);getchar();
	int len = strlen(makananDelete);
		
	int flagDeleteMenu = deleteMenu(makananDelete);
	if(flagDeleteMenu == 1){
		printf("The dish has been removed\n");
	}
	else {
		printf("Cannot find the dish\n");
	}
	printf("\nPress enter to continue..");
	getchar();
	
}


void menu3(){// menampilkan menu - menu yang tersedia ketika user memilih menu 3
	system("@cls||clear");
	char namaCustomer[255];
	int flag;
	do{
		flag = 1;
		printf("Insert the customer's name [Without Space]:");
		scanf("%[^\n]",namaCustomer);getchar();
		for(int i = 0; i < strlen(namaCustomer); i++){
			if(namaCustomer[i] == ' '){
				flag = 0;
				break;
			}
			if(namaCustomer[i] < 'A'||namaCustomer[i] > 'z'){
				flag = 0;
				break;
			}
		}
	} while(flag == 0);
	
	insert(namaCustomer);
	printf("\nCustomer has been added!\n");
	printf("\nPress enter to continue...");getchar();
	
	
}


void menu4(){// menampilkan menu - menu yang tersedia ketika user memilih menu 4
	system("@cls||clear");
	char namaSearch[255];
	printf("Insert the customer's name to be searched:");
	scanf("%[^\n]", namaSearch); getchar();
	int flag = search(namaSearch);
	puts("");
	if(flag){
		printf("%s is present\n\n", namaSearch);
	}
	else {
		printf("%s is not present\n\n", namaSearch);
	}
	printf("Press enter to continue..");
	getchar();
}

void menu6(){// menampilkan menu - menu yang tersedia ketika user memilih menu 6
	system("@cls||clear");
	char namaCustomer[255];
	int flag;
	do{	
		flag = 1;
		printf("Insert the customer's name:");
		scanf("%[^\n]",namaCustomer); getchar();
		for(int i = 0; i < strlen(namaCustomer); i++){
			if(namaCustomer[i] == ' '){
				flag = 0;
				break;
			}
			if(namaCustomer[i] < 'A' || namaCustomer[i] > 'z'){
				flag = 0;
				break;
			}
		}
		
	}while(flag == 0);
	flag = search(namaCustomer);
	if(flag == 0){
		printf("Customer doesn't exist\n");
		printf("Press enter to continue..");
		getchar();
		return;
	}
	
	int dishQty;
	printMenu();
	printf("insert the amount of dish:");
	scanf("%d", &dishQty);getchar();
	char namaMakanan[255];
	int qty;
	for(int i = 1; i <= dishQty; i++){
		int flag = 0;
		do{
			flag = 0;
			printf("[%d] insert the dish's name and quantity:", i);
			scanf("%[^x]x%d", namaMakanan, &qty); getchar();
			int len = strlen(namaMakanan);
			namaMakanan[len-1]='\0';
			dish *curr = head;
			while(curr){
				if(strcmp(curr->nama,namaMakanan) == 0){
					flag = 1;
					break;
				}
				curr = curr->next;
			}
			
		} while(flag == 0);
		
		
		cariMenu(namaMakanan, namaCustomer, qty);
	}
}

void printData(){//untuk print data order dari masing - masing customer
	system("@cls||clear");
	int index;
	printf("Insert the customer index:");
	scanf("%d", &index);getchar();
	
	customer *customerCurr = headCustomer[index]; 
	while(customerCurr){
		int hargaTot = 0;
		printf("%s\n", customerCurr->nama); 
		customerCurr->orderCurr = customerCurr->orderHead;
		while(customerCurr->orderCurr){
			printf("%s x%d\n",customerCurr->orderCurr->nama, customerCurr->orderCurr->qty);
			hargaTot += customerCurr->orderCurr->harga;
			customerCurr->orderCurr = customerCurr->orderCurr->orderNext;
		}
		printf("Total: %d\n",hargaTot);
		customerCurr = customerCurr->next;
	}	
			
	getchar();		
}
	


void menu(){//berisi tampilan menu awal
	while(1){
		system("@cls||clear");
		printf("%s\n", detectOS()); 
    	time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	printf("%s", asctime(tm));
		int menuChoice;
		printf("1.Add Dish\n");
		printf("2.Remove Dish\n");
		printf("3.Add Customer\n");
		printf("4.Search Customer\n");
		printf("5.View Warteg\n");
		printf("6.Order\n");
		printf("7.Payment\n");
		printf("8.Exit\n");
		
		do{
			printf(">>");
			scanf("%d", &menuChoice);getchar();
		}while(menuChoice < 1 || menuChoice > 8);
		
		switch(menuChoice){
			
			case 1:{
				menu1();
				break;
			}
			case 2:{
				menu2();
				break;
			}
			case 3:{
				menu3();
				break;
			}
			case 4:{
				menu4();
				break;
			}
			case 5:{
				customerWarteg();
				break;
			}
			case 6:{
				menu6();
				break;
			}
			case 7:{
				printData();
				break;
			}
			case 8:{
				return;
			}		
		}
	}
}


int main() {
  	char bootcamp[1000][1000];
  	int ctr = 0;
    menu();
    system("@cls||clear");
    //fungsi untuk membaca file dan print
	FILE *fp = fopen("splash-screen.txt","r"); 
	while(fscanf(fp, "%[^\n]\n", bootcamp[ctr]) != EOF){
		ctr++;
	}
	fclose(fp);
	for(int i = 0;i < ctr; i++){
		printf("%s\n", bootcamp[i]);
	}
    return 0;
}

//kekurangan :  masih menggunakan 1 file saja
