#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char nama[255];
	char bulan[255];
	int tanggal;
	int tahun;
	int total;
	node *next,*prev;
} *head,*tail,*curr;

node *createNode(char *nama,long long int tanggal,char *bulan,int tahun,int total) {
  node *temp = (node*)malloc(sizeof(node));
  strcpy(temp->nama,nama);
  temp->tanggal=tanggal;
  strcpy(temp->bulan,bulan);
  temp->tahun=tahun;
  temp->total=total;
  temp->next = temp->prev = NULL;
  return temp;
}

 void pushPQ(char *nama,long long int tanggal,char *bulan,int tahun,int total) {
    node *temp = createNode(nama, tanggal, bulan, tahun, total);

    if(!head) { 
      head = tail = temp;
    } else if(total < head->total) { 
      temp->next = head;
      head->prev = temp;
      head = temp; 
    } else if(total > tail->total) { 
      temp->prev = tail;
      tail->next = temp;
      tail = temp; 
    } else { 
      node *curr = head;
      
      while(curr && curr->next->total < temp->total) {
        curr = curr->next;
      }

      curr->next->prev = temp; 
      temp->next = curr->next; 
      curr->next = temp; 
      temp->prev = curr; 
    }
  }
  

int cekBulan (char*bulan){
  	int index;
  	char namaBulan[20][255]={"january","february","march","april","may","june","july","august","september","october","november", "december"};
  	for(int i=0;i<12;i++){
  		if(strcmp(bulan,namaBulan[i])==0){
  			index=i;
  			break;
		  }
	  }
  	index++;
  	return index*30;
}
  
  
void printLinkedList() {
  curr = head;

  while(curr) {
    printf("%d %s %d - %s", curr->tanggal,curr->bulan, curr->tahun, curr->nama);
    puts("");
    curr = curr->next;
  }
  
}

void popHead() {
  if(head && head == tail) { // jika hanya 1 node
    head = tail = NULL;
    free(head);
  } else { // jika > 1 node // A (head) -><- B -><- C
    node *newHead = head->next; // A (head) -><- B (newHead) -><- C
    head->next = newHead->prev = NULL; // A (head) B (newHead) -><- C
    free(head); // B (newHead) -><- C
    head = newHead; // B (head) -><- C
  }
}

int main (){
	char nama[255];long long int tanggal;char bulan[255];int tahun;int total;
	int banyakPasien,obat;
	scanf("%d %d",&banyakPasien,&obat);getchar();
	int ctr= banyakPasien;
	for(int i=0;i<banyakPasien;i++){
	
	scanf("%d %s %d - %[^\n]",&tanggal,bulan,&tahun,nama);getchar();
//	printf("%s",bulan);
	total = cekBulan(bulan);
	tahun*=300;
	total+= (tanggal+tahun);
//	int cek = cekBulan(bulan);
//	printf("%d",cek);
	pushPQ(nama,tanggal,bulan,tahun,total);
	
}
	while(obat--){
		ctr--;
		popHead();
	}
	printf("Needed %d more cure\n",ctr);
	printLinkedList();
	return 0;
}
