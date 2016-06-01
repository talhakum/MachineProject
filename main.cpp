#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct orders{
	char ordercode[10];
	char amountofwork[10];
	char operationcode[10];
	char deadline[10];
	struct orders* link;
};
struct operations{
	char operationcode[10];
	char duration[10];
	struct operations *link;
};
struct setupduration{
	char operationcode1[10];
	char operationcode2[10];
	char SetupDuration[10];
	struct setupduration *link;
};
	struct orders *ilk=NULL,*son,*yeni,*liste;
	struct operations *ilk2=NULL,*son2,*yeni2,*liste2,*tutDuration,*tutDuration2;
	struct setupduration *ilk3=NULL,*son3,*yeni3,*liste3,*deneme,*tut;
char* fonksiyon(char * opcode1,char *opcode2);
char* durationAra(char* operationCode);
int main(int argc, char *argv[]) {

	FILE *dosya=fopen("Orders.txt","r");
		FILE *deneme=fopen("Orders.txt","r");

	FILE *dosya2=fopen("Operations.txt","r");
	FILE *dosya3=fopen("SetupDuration.txt","r");
	FILE *dosya4=fopen("Schedule.txt","w+");
	char str[1000];
	while(!feof(dosya)) {

				fgets(str,20,dosya);


		char *pch;
		pch=strtok(str,";");

		if(ilk==NULL) {
			liste=(struct orders*)malloc(sizeof(struct orders)*10);
			strcpy(liste->ordercode,pch);
			pch=strtok(NULL,";");
			strcpy(liste->amountofwork,pch);
			pch=strtok(NULL,";");
			strcpy(liste->operationcode,pch);
			pch=strtok(NULL,";");
			strcpy(liste->deadline,pch);
			ilk=liste;
			son=ilk;
		}
		else {
			yeni=(struct orders*)malloc(sizeof(struct orders)*10);
			strcpy(yeni->ordercode,pch);
			pch=strtok(NULL,";");
			strcpy(yeni->amountofwork,pch);
			pch=strtok(NULL,";");
			strcpy(yeni->operationcode,pch);
			pch=strtok(NULL,";");
			strcpy(yeni->deadline,pch);
			son->link=yeni;
			son=son->link;

		}
		pch=NULL;

	}
	while(!feof(dosya2)) {

				fgets(str,20,dosya2);


		char *pch;
		pch=strtok(str,";");

		if(ilk2==NULL) {
			liste2=(struct operations*)malloc(sizeof(struct operations)*10);
			strcpy(liste2->operationcode,pch);
			pch=strtok(NULL,";");
			strcpy(liste2->duration,pch);

			ilk2=liste2;
			son2=ilk2;
			}
		else {
				yeni2=(struct operations*)malloc(sizeof(struct operations)*10);
			strcpy(yeni2->operationcode,pch);
			pch=strtok(NULL,";");
			strcpy(yeni2->duration,pch);
			son2->link=yeni2;
			son2=son2->link;

		}
		pch=NULL;
	}
		while(!feof(dosya3)) {

				fgets(str,20,dosya3);


		char *pch;
		pch=strtok(str,";");

		if(ilk3==NULL) {
			liste3=(struct setupduration*)malloc(sizeof(struct setupduration)*10);
			strcpy(liste3->operationcode1,pch);
			pch=strtok(NULL,";");
			strcpy(liste3->operationcode2,pch);
			pch=strtok(NULL,";");
			strcpy(liste3->SetupDuration,pch);
			ilk3=liste3;
			son3=ilk3;
		}
		else {
			yeni3=(struct setupduration*)malloc(sizeof(struct setupduration)*10);
			strcpy(yeni3->operationcode1,pch);
			pch=strtok(NULL,";");
			strcpy(yeni3->operationcode2,pch);
			pch=strtok(NULL,";");
			strcpy(yeni3->SetupDuration,pch);

			son3->link=yeni3;
			son3=son3->link;

		}
		pch=NULL;

	}
    rewind(dosya);


	tut=ilk3;
	tutDuration=ilk2;
	int toplam=0;


	fprintf(dosya4,"%d;%s;%s;%s;%d\n\r",0,ilk->operationcode,ilk->ordercode,ilk->amountofwork,0);
int b=0;
    fgets(str,20,dosya);
	while(!feof(dosya)) {
             fgets(str,20,dosya);

	toplam+=(int)(atoi(fonksiyon(ilk->operationcode,ilk->link->operationcode))+ceil(atoi(ilk->amountofwork )/atof(durationAra(ilk->operationcode))));
	fprintf(dosya4,"%d;%s;%s;%s;%d\n\r",toplam, ilk->link->operationcode,ilk->link->ordercode,ilk->link->amountofwork,atoi(fonksiyon(ilk->operationcode,ilk->link->operationcode)));
	ilk=ilk->link;


    b++;



	}
	printf("%d",toplam+(int)ceil(atoi(ilk->amountofwork )/atof(durationAra(ilk->operationcode)))); //Tüm iþlerin verildiði sýrada yapýlarak bittiði süre.



	return 0;
}
char* fonksiyon(char *opcode1,char *opcode2) {
	deneme=NULL;
	deneme=tut;
	if(strcmp(opcode1,opcode2)==0 ) {
		return "0";
	}

	while(1) {

	if( ((strcmp(deneme->operationcode1,opcode1)==0) && (strcmp(deneme->operationcode2,opcode2)==0)) || (((strcmp(deneme->operationcode2,opcode1)==0) && (strcmp(deneme->operationcode1,opcode2)==0))) )
		break;

		deneme=deneme->link;

	}

	return deneme->SetupDuration;

}
char* durationAra(char * operationCode) {
	tutDuration2=NULL;

	tutDuration2=tutDuration;
	while(1) {


	if(strcmp(tutDuration2->operationcode,operationCode)==0) {
		break;
	}
		tutDuration2=tutDuration2->link;
	}
	return tutDuration2->duration;
}
