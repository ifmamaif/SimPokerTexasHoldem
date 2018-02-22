
///	Tema de proiect 5 : Poker Texas Holdem
//	Scrieti un program in C care simuleaza jocul de Poker Texas Holdem :	https://en.wikipedia.org/wiki/Texas_hold_%27em
///	pentru doi jucatori urmand pasii urmatori:
//	1.se genereaza 2 carti pentru fiecare jucator (T0) si apoi 3 carti (T1), o carte (T2) si inca o carte (T3) (in total 5 carti comune). Castiga cel ce are cartile mai mari conform regulilor de aici :	https://ro.wikipedia.org/wiki/Lista_de_m%C3%A2ini_de_poker
///	2.afisati pe ecran cine castiga (J1 sau J2) “mana” la T3;
//	3.estimati dupa fiecare timp T (T0,T1,T2) cine are sanse mai mari sa castige.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <conio.h> // getch
#define NUMBER_CARDS 52
#define NUMBER_HAND_CARDS 2
#define NUMBER_RANK 10
#define NUMBER_COMMUNITY_CARDS 5
#define FILE_NAME_CARDS "cards.txt"
#define FILE_NAME_RANKING "ranking.txt"
#define FILE_NAME_PLAYERS "players.txt"
#define FILE_NAME_INFO "info.txt"
#define FILE_NAME_RULES "rules.txt"
#define Key_Code_Esc 27
#define Key_Code_1 49
#define Key_Code_2 50
#define Key_Code_3 51

typedef struct {
	char * name;
	unsigned char *card;
	
}player;

typedef struct {
	int category;
	char what;
	char what2;
}ranking;


enum cards	{
	AceClubs=0, // as  de trefla
	TwoClubs,
	ThreeClubs,
	FourClubs,
	FiveClubs,
	SixClubs,
	SevenClubs,
	EightClubs,
	NineClubs,
	TenClubs,
	JackClubs,
	QueenClubs,	
	KingClubs,	// 12
	
	AceDiamonds, //13 as de romb
	TwoDiamonds,
	ThreeDiamonds,
	FourDiamonds,
	FiveDiamonds,
	SixDiamonds,
	SevenDiamonds,
	EightDiamonds,
	NineDiamonds,
	TenDiamonds,
	JackDiamonds,
	QueenDiamonds,
	KingDiamonds,	//25
	
	AceHearts, // 26 as de inima rosie
	TwoHearts,
	ThreeHearts,
	FourHearts,
	FiveHearts,
	SixHearts,
	SevenHearts,
	EightHearts,
	NineHearts,
	TenHearts,
	JackHearts,
	QueenHearts,
	KingHearts,	// 38
	
	AceSpades, //	39 as de inima neagra
	TwoSpades,
	ThreeSpades,
	FourSpades,
	FiveSpades,
	SixSpades,
	SevenSpades,
	EightSpades,
	NineSpades,
	TenSpades,
	JackSpades,
	QueenSpades,
	KingSpades 	//	51
};

enum hand_ranking_categories	{
	Five_of_a_kind=0,
	Straight_flush,					// 1
	Four_of_a_kind,					// 2
	Full_house,						// 3
	Flush,							// 4
	Straight,						// 5
	Three_of_a_kind,				// 6
	Two_pair,						// 7
	One_pair,						// 8
	High_card						// 9
};


void clearscreen(){
	system("cls");
}
int random (int,char*);
void press_key();
void intializes_random_number_generator();
void missing_file();
void filenamecards(char**);
void filenamerank(char**);
void filenameplayers(player**,int*);
void isStraight_flush(ranking*,int,int,unsigned char*);
void isFlush(ranking*,int,int,unsigned char*);
void isStraight(ranking*,unsigned char*);
void isFour_of_a_kind(ranking*,unsigned char*);
void isFull_house(ranking*,unsigned char*);
void isThree_of_a_kind(ranking*,unsigned char*);
void isOne_pair(ranking*,unsigned char*);
char isequalcards(char,char);
char compareHighcard(char,char);
char changewhat(char,char);
void compareandchangecategory(int*,int,char*,char);
void systemrank(int,player*,unsigned char*,char,ranking* );
void winner(int,player*,ranking*,char**,char**);
void Info(FILE *,int,player*,unsigned char*,char**,char,unsigned char*,char,ranking*,char**);
void T0(FILE*,int,int,char*,char **,player*);
void T1(FILE*,int,char*,char **,unsigned char*,char*);
void T2(FILE*,int,char*,char **,unsigned char*,char*,unsigned char*,char*);
void T3(FILE*,int,char*,char **,unsigned char*,char*,unsigned char*,char*);

int main(int argc,char* argv[]){
	intializes_random_number_generator();
	missing_file();
	char c=1;
	FILE *f;
	int idmenu=0;	
	
	char*check;
	char**name_cards;
	char ** name_rank ;
	
	do{
		switch(idmenu){
			case 1 :
			f=fopen(FILE_NAME_INFO,"r");
			c=1;
			while(fscanf(f,"%c",&c)>0)
				printf("%c",c);			
			fclose(f);
			printf("\n");
			press_key();
			clearscreen();
			idmenu=0;		
			break;
			
			case 2 :
			f=fopen(FILE_NAME_RULES,"r");
			c=1;
			while(fscanf(f,"%c",&c)>0)
				printf("%c",c);
			fclose(f);
			printf("\n");
			press_key();
			clearscreen();
			idmenu=0;
			break;
			
			case 3 :
				check=(char*)calloc(NUMBER_CARDS,sizeof(char)); // unique cards of 52 
								
				name_cards=(char**)malloc(NUMBER_CARDS*sizeof(char*));
				filenamecards(name_cards);
								
				name_rank = (char**)malloc(NUMBER_RANK*sizeof(char*));
				filenamerank(name_rank);
				
				int number_players; 
				player* players=NULL;
				filenameplayers(&players,&number_players);
				
				char public=0;
				unsigned char* publiccommcards=(unsigned char*) malloc (5 * sizeof(unsigned char));
				char nfire=0;
				unsigned char* fired=(unsigned char*) malloc (2 * sizeof(unsigned char));
				
				ranking* rank=(ranking*)malloc(number_players*sizeof(ranking));
				
				T0(stdout,number_players,NUMBER_CARDS,check,name_cards,players); //	Se genereaza 2 carti pentru fiecare jucator
				Info(stdout,number_players,players,publiccommcards,name_cards,public,fired,nfire,rank,name_rank);
				
				T1(stdout,NUMBER_CARDS,check,name_cards,publiccommcards,&public);	//	si apoi 3 carti (T1) , "the flop"
				Info(stdout,number_players,players,publiccommcards,name_cards,public,fired,nfire,rank,name_rank);
				
				T2(stdout,NUMBER_CARDS,check,name_cards,publiccommcards,&public,fired,&nfire);	//	"the turn" or "fourth street" , trebuie arsa o carte
				Info(stdout,number_players,players,publiccommcards,name_cards,public,fired,nfire,rank,name_rank);
				
				T3(stdout,NUMBER_CARDS,check,name_cards,publiccommcards,&public,fired,&nfire);	//	"the river" or "fifth street" , trebuie arsa o carte
				Info(stdout,number_players,players,publiccommcards,name_cards,public,fired,nfire,rank,name_rank);
				
				// 2.afisati pe ecran cine castiga (J1 sau J2) “mana” la T3; https://ro.wikipedia.org/wiki/Lista_de_m%C3%A2ini_de_poker
				// 3.estimati dupa fiecare timp T (T0,T1,T2) cine are sanse mai mari sa castige.
				
				{	// free pointers | free memory
					int i;
					for(i=0;i<NUMBER_CARDS;i++)
						free(name_cards[i]);
					free(name_cards);
					for(i=0;i<number_players;i++){
						free(players[i].name);
						free(players[i].card);
					}
					free(players);
					free(publiccommcards);
					free(fired);
					free(check);
					free(rank);
				}
				clearscreen();
				idmenu=0;	
			break;
			
			default :
				printf("Facultatea de Matematica si Informatica Bucuresti\nProiect : Poker Texas Holdem\nStudent : Ifrim Marius\nMeniu : \n");
				printf("\t1. Informatii Joc\n");
				printf("\t2. Reguli Joc\n");
				printf("\t3. Joaca Jocul\n");
				printf("\tEsc. Iesire\n");
				printf("[Apasati pe tasta corespunzatoare ! ]\n");
				char c=1;
				while(c!=Key_Code_1 && c!=Key_Code_2 && c!=Key_Code_3 && c!=Key_Code_Esc){
					c=getch();
					//printf("%d %c\n",(int)c,c);
				}
				switch(c){
					case Key_Code_1:
						idmenu=1;
						clearscreen();
					break;
					case Key_Code_2:
						idmenu=2;
						clearscreen();
					break;
					case Key_Code_3:
						idmenu=3;
						clearscreen();
					break;
					case Key_Code_Esc:
						idmenu=-1;
						clearscreen();
					break;	
				}
			break;
		}		
	}while(idmenu>=0);	
	return 0;
}

void press_key(){
	fprintf(stdout,"Press any key to continue\n");
	getch();
	system("cls");
}

void intializes_random_number_generator()	{	// Intializes random number generator 
	time_t t;		
	srand((unsigned) time(&t));
}

void missing_file(){
	FILE *f=fopen(FILE_NAME_CARDS,"r");
	if(f==NULL){
		fclose(f);
		f=fopen(FILE_NAME_CARDS,"w");
		fprintf(f,"Ace of clubs\nTwo of clubs\nThree of clubs\nFour of clubs\nFive of clubs\nSix of clubs\nSeven of clubs\nEight of clubs\nNine of clubs\nTen of clubs\nJack of clubs\nQueen of clubs\nKing of clubs\nAce of diamonds\nTwo of diamonds\nThree of diamonds\nFour of diamonds\nFive of diamonds\nSix of diamonds\nSeven of diamonds\nEight of diamonds\nNine of diamonds\nTen of diamonds\nJack of diamonds\nQueen of diamonds\nKing of diamonds\nAce of hearts\nTwo of hearts\nThree of hearts\nFour of hearts\nFive of hearts\nSix of hearts\nSeven of hearts\nEight of hearts\nNine of hearts\nTen of hearts\nJack of hearts\nQueen of hearts\nKing of hearts\nAce of spades\nTwo of spades\nThree of spades\nFour of spades\nFive of spades\nSix of spades\nSeven of spades\nEight of spades\nNine of spades\nTen of spades\nJack of spades\nQueen of spades\nKing of spades");
		fclose(f);
	}
	f=fopen(FILE_NAME_RANKING,"r");
	if(f==NULL){
		fclose(f);
		f=fopen(FILE_NAME_RANKING,"w");
		fprintf(f,"Five_of_a_kind\nStraight_flush\nFour_of_a_kind\nFull_house\nFlush\nStraight\nThree_of_a_kind\nTwo_pair\nOne_pair\nHigh_card"
		);
		fclose(f);
	}
	f=fopen(FILE_NAME_PLAYERS,"r");
	if(f==NULL){
		fclose(f);
		f=fopen(FILE_NAME_PLAYERS,"w");
		fprintf(f,"2\nBob\nJonny");
		fclose(f);
	}
	f=fopen(FILE_NAME_INFO,"r");
	if(f==NULL){
		fclose(f);
		f=fopen(FILE_NAME_INFO,"w");
		fprintf(f,"Texas hold 'em (cunoscut si ca hold 'em sau poker cu 2 carti) este o varianta a jocului standard de poker. Texas hold 'em consta in doua carti date fiecarui jucator (cu fata in jos) si cinci carti comune care sunt date cu fata in sus si implicit sunt vizibile tuturor. Aceste 5 carti se dau in 3 reprize, prima repriza (the flop) contine trei carti, apoi 2 reprize cu cate o carte fiecare (cu numele the turn si the river), jucatorii avand optiunea de a face pas (en: check), de a paria, de a mari pariului pus initial de catre alt jucator, de a plati pariul sec (en: call), sau de a-si arunca cartile.");
		fclose(f);
	}
	f=fopen(FILE_NAME_RULES,"r");
	if(f==NULL){
		fclose(f);
		f=fopen(FILE_NAME_RULES,"w");
		fprintf(f,"in jocul de poker , jucatorii construiesc maini de cate cinci carti in conformitate cu reguli prestabilite ale jocului, care variaza in functie de ce varianta de poker este jucata. Aceste maini sunt comparate folosind un sistem de clasificare, care este standard la toate variantele de poker. jucatorul cu cel mai mare punctaj al mainii, castiga runda in marea majoritate a variantelor de poker. in unele variante, pe de o parte cel mai mic punctaj poate atat castiga cat si pierde.\nDesi utilizate in principal in poker, aceste clasamente de maini sunt, de asemenea, folosite si in alte cateva jocuri de carti , dar si in poker-ul cu zaruri .\nUn anumit clasament de mana de poker, este crescut prin includerea mai multor carti cu acelasi punctaj, toate cele cinci carti fiind de aceeasi culoare , sau toate cele cinci carti fiind de rang consecutiv. Clasamentul relativ a diferitelor categorii de maini de poker se bazeaza pe probabilitatea de a fi la intamplare servita o asa mana dintr-un pachet de carti bine amestecat .\nReguli generale\nUrmatoarele norme se aplica clasamentului tuturor mainilor de poker. in conformitate cu normele tipice exista 7462 de ranguri distincte.\nO mana consta intotdeauna din cinci carti. in jocurile in cazul in care mai mult de cinci carti sunt disponibile pentru fiecare jucator, combinatia celor mai bune cinci carti trebuie sa fi jucata. Oricare carti care nu sunt incluse in mana nu afecteaza rangul. De exemplu: daca jucatorul A detine 3 de inima neagra  Q de romb  si jucatorul B are 3 de trefla  A de trefla  , si cinci carti 4 de trefla  5 de romb  6 de romb  7 de inima neagra  10 de inima rosie  sunt disponibile ambilor jucatori, acestia detin la fel 3-4-5-6-7 chinta, in ciuda faptului ca Asul jucatorului B este mai mare decat Regina jucatorului A.\ncartile individuale sunt clasificate in A (as - cea mai mare) K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2 (cea mai mica). Asii pot aparea ca si carte mica (ca si cum ar avea valoare de 1), atunci cand fac parte din mana de chinta A-2-3-4-5, sau chinta de culoare. in variante de poker de la A la 5 si de la A la 6 ca mana de poker mica, asul joaca numai ca si carte mica si numai ca si carte mare in doi-la-sapte ca mana de poker mica (lowball). Randurile individuale de carti sunt folosite pentru a clasifica mainile, care sunt in categoria aceluiasi rang.\ncartile de aceeasi culoare, suitele , sunt utilizate pentru a determina daca o mana formeaza culoare sau chinta de culoare . in cele mai multe variante, suitele nu au o valoare asociata, si nu joaca niciun rol in determinarea clasamentului la o mana de poker. Uneori, un clasament numit carte mare de culoare este utilizata pentru selectarea la intamplare a unui jucator pentru a servi cartile pentru runda respectiva (dealer) . cartile de culoare mici , de obicei, determina jucatorul sa renunte mai bine la aceastea, sa le arunce inapoi crupierului , in diferitele stiluri de jocuri de poker.\nMainile de poker sunt clasificate in primul rand pe categorii, apoi pe carti individuale; chiar si cea mai mica mana care se califica intr-o anumita categorie invinge toate mainile in toate categoriile inferioare acesteia. De exemplu: 2 de romb  2 de inima neagra  3 de romb  3 de trefla  4 de inima neagra  , mana de doua perechi de carti cu valorile cele mai mici, invinge toate mainile cu doar o singura pereche sau carte mare, (cum ar fi A de inima neagra  A de romb  K de romb  Q de inima rosie  J de trefla  ). Doar intre doua maini din aceeasi categorie sunt randuri de carti utilizate pentru a rupe legaturile.\nO mana de poker are acelasi rang indiferent de ordinea servirii lor de catre crupier. Deci o mana aranjata astfel 10 de inima neagra  8 de romb  10 de romb  6 de trefla  10 de trefla  este acelasi lucru cu o mana aranjata asa 10 de trefla  10 de romb  10 de inima neagra  8 de romb  6 de trefla  , chiar daca in prima mana cele trei carti de acelasi fel nu ies imediat in evidenta.\nDaca exista mai multe maini de acelasi rang la showdown, potul este impartit in mod egal intre jucatorii castigatori. in cazul in care potul de impartit creeaza fractiuni (fise impare), prima mana in sensul acelor de ceasornic de la dealer primeste fisele.\nExista 311 875 200 moduri (5 - permutari) de a fi servite cinci carti dintr-un pachet de 52 de carti de joc, dar pentru ca ordinea cartilor nu conteaza, sunt 5!=120 5-permutari pentru o anumita mana, astfel incat exista doar: 2,598,960 .");
		fclose(f);
	}
}

void filenamecards(char** name_cards){
	FILE* f=fopen(FILE_NAME_CARDS,"r");
	int i;
	for(i=0;i<NUMBER_CARDS;i++){
		char c='a';
		int number=0;
		fpos_t setposition=ftell(f);
		while(fscanf(f,"%c",&c)>0 && c!='\r' && c!='\n'){
			number++;
		}
		fsetpos(f,&setposition);
		name_cards[i]=(char*)malloc((number+1)*sizeof(char));
		fread(name_cards[i],sizeof(char),number,f);
		name_cards[i][number]=0;
		fscanf(f,"%c",&c);
	}
	fclose(f);
}

void filenamerank(char** name_rank){
	FILE* f=fopen(FILE_NAME_RANKING,"r");
	int i;
	for(i=0;i<NUMBER_RANK;i++){
		char c='a';
		int number=0;
		fpos_t setposition=ftell(f);
		while(fscanf(f,"%c",&c)>0 && c!='\r' && c!='\n'){
			number++;
		}
		fsetpos(f,&setposition);
		name_rank[i]=(char*)malloc((number+1)*sizeof(char));
		fread(name_rank[i],sizeof(char),number,f);
		name_rank[i][number]=0;
		fscanf(f,"%c",&c);
	}
	fclose(f);	
}

void filenameplayers(player** players,int* nr){
	FILE* f=fopen(FILE_NAME_PLAYERS,"r");
	int i;
	fscanf(f,"%d",nr);
	char c;
	fscanf(f,"%c",&c); // "eliminim"=trec=sar-peste terminatorul de linie 
	(*players)=(player*)malloc((*nr)*sizeof(player));
	for(i=0;i<(*nr);i++){
		c='a';
		int number=0;
		fpos_t setposition=ftell(f);
		while(fscanf(f,"%c",&c)>0 && c!='\r' && c!='\n'){
			number++;
		}
		fsetpos(f,&setposition);		
		(*players)[i].name =(char*)malloc((number+1)*sizeof(char));
		fread((*players)[i].name ,sizeof(char),number,f);
		(*players)[i].name[number]=0;		
		(*players)[i].card=(unsigned char*)calloc(NUMBER_HAND_CARDS,sizeof(unsigned char));
		fscanf(f,"%c",&c);
	}
	fclose(f);
}

char isequalcards(char a,char b){
	char c1=a,c2=b;
	while(c1>(KingClubs+1))
		c1-=(KingClubs+1);
	while(c2>(KingClubs+1))
		c2-=(KingClubs+1);
	return c1==c2;
}

char compareHighcard(char a,char b){
	char c1=a,c2=b;
	if(c2 >= AceSpades)
		c2-= AceSpades;
	if(c2 >= AceHearts)
		c2-= AceHearts;
	if(c2 >= AceDiamonds)
		c2-= AceDiamonds;
	if(c1 >= AceSpades)
		c1-= AceSpades;
	if(c1 >= AceHearts)
		c1-= AceHearts;
	if(c1 >= AceDiamonds)
		c1-= AceDiamonds;
	if(c1 == AceClubs)
		return a;
	if(c2 == AceClubs)
		return b;
	if( c1 < c2)
		return b;
	return a;
}

char changewhat(char first ,char second) {
	if( second==AceClubs || second==AceDiamonds || second==AceHearts || second==AceSpades ){
		return second;
	}
	else if(first!=AceClubs && first!=AceDiamonds && first!=AceHearts && first!=AceSpades ){
		return compareHighcard(first,second);	
	}
	return first;
}

void compareandchangecategory(int* firstcategory , int secondcategory , char* firstcard , char secondcard){
	if( (*firstcategory) > secondcategory){
		(*firstcategory) = secondcategory;
		(*firstcard) = secondcard;
	}
	else if( (*firstcategory) == secondcategory){
		(*firstcard) = changewhat((*firstcard),secondcard);
	}
}

int random (int modulo,char* check){
	if(check == NULL){
		return rand() % modulo;	// un numar aleator intre 0 si modulo(=52)-1 <=> [0,51];
	}
	int var = rand() % modulo;	// un numar aleator intre 0 si modulo(=52)-1 <=> [0,51];
	while(check[var]!=0)	//	cat timp exista acea carte , check[var]==0 => nu exista ,check[var]!=0 (adica 1) => cartea exista deja
		var = rand() % modulo; // schimb cartea
	check[var]++; // cartea devine unica , check[var]=1 <=> cartea exista;
	return var;
}

void T0(FILE *flow,int number_players,int number_cards,char * check,char ** name_cards,player * players){
	int i;
	for(i=0;i<number_players;i++){
		int j;
		for(j=0;j<NUMBER_HAND_CARDS;j++){
			players[i].card[j]=random(number_cards,check);
		}
	}
}

void T1(FILE *flow,int number_cards,char * check,char ** name_cards,unsigned char* publiccommcards,char* public){
	publiccommcards[0]=random(number_cards,check);
	publiccommcards[1]=random(number_cards,check);
	publiccommcards[2]=random(number_cards,check);
	(*public)=3;
}

void T2(FILE *flow,int number_cards,char * check,char ** name_cards,unsigned char* publiccommcards,char* public,unsigned char*fired,char *nfire)	{
	fired[0]=random(number_cards,check);
	publiccommcards[3]=random(number_cards,check);
	(*public)=4;
	(*nfire)=1;
}

void T3(FILE *flow,int number_cards,char * check,char ** name_cards,unsigned char* publiccommcards,char* public,unsigned char*fired,char *nfire)	{
	fired[1]=random(number_cards,check);
	publiccommcards[4]=random(number_cards,check);
	(*public)=5;
	(*nfire)=2;
}

void Info(FILE *flow,int number_players,player* players,unsigned char* publiccommcards,char ** name_cards,char public,unsigned char*fired,char nfire,ranking* rank,char**name_rank){
	int i;
	for(i=0;i<number_players;i++){		
		fprintf(flow,"Player %d %s : ",i+1,players[i].name);
		int j;
		for(j=0;j<NUMBER_HAND_CARDS;j++){
			fprintf(flow,"%s , ",name_cards[players[i].card[j]]);			
		}
		fprintf(flow,"\b\b  \n");
	}
	if(nfire > 0 ){
		fprintf(flow,"Fired Cards:  ");
		for(i=0;i<nfire;i++){
			fprintf(flow,"%s , ",name_cards[fired[i]]);
		}
		fprintf(flow,"\b\b  \n");
	}
	if(public > 0 ){
		fprintf(flow,"Community Cards:  ");
		for(i=0;i<public;i++){
			fprintf(flow,"%s , ",name_cards[publiccommcards[i]]);
		}
		fprintf(flow,"\b\b  \n");
	}
	systemrank(number_players,players,publiccommcards,public,rank);
	winner(number_players,players,rank,name_cards,name_rank);
	if(nfire == 2)
		printf("\nEND GAME !\n");
	press_key();
}

void isStraight_flush(ranking* rank,int Ace,int King,unsigned char* cards){
	int seek=cards[Ace]>0?(King+1):-1;
	int ok=seek>0?1:0;
	int j;
	for(j=King;j>=Ace;j--){
		if(cards[j]>0){		
			if(j==(seek-ok)){
				ok++;
			}
			else {
				ok=1;
				seek=j;
			}
		}
		if(ok>=5){										
			if(seek>King)
				seek=Ace;
			compareandchangecategory(&((rank)->category) , Straight_flush , &((rank)->what) , seek);						
		}
	}
}
	
void isFlush(ranking* rank,int Ace,int King,unsigned char* cards){
	int seek=cards[Ace]>0?Ace:-1;
	int ok=seek>0?1:0;
	int j;
	for(j=Ace+1;j<=King;j++){
		if(cards[j]>0){
			ok++;
			if(seek!=Ace)
				seek=j;
			}
		}
	if(ok>=5){
		compareandchangecategory(&(rank->category) , Flush , &(rank->what) , seek);
	}
}

void isStraight(ranking* rank,unsigned char* cards){
	unsigned char *same=(unsigned char*)calloc(KingClubs+1,sizeof(unsigned char));
	int j;
	for(j=AceClubs;j<=KingSpades;j++){
		same[j%(KingClubs+1)]+=cards[j];
	}
	int seek=same[AceClubs]>0?(KingClubs+1):-1;
	int ok=seek>0?1:0;
	for(j=KingClubs;j>=AceClubs;j--){						
		if(same[j]>0){
			if(j==(seek-ok)){
				ok++;
			}
			else {
				ok=1;
				seek=j;
			}
		}				
		if(ok>=5){											
			if(cards[seek+KingHearts+1]>0)
				seek+=KingHearts+1;
			else if(cards[seek+KingDiamonds+1]>0)
				seek+=KingDiamonds+1;
			else if(cards[seek+KingClubs+1]>0)
				seek+=KingClubs+1;
			compareandchangecategory(&(rank->category) , Straight , &(rank->what) , seek);					
		}
	}
	free(same);
}

void isFour_of_a_kind(ranking* rank,unsigned char* cards){
	unsigned char *same=(unsigned char*)calloc(KingClubs+1,sizeof(unsigned char));
	int j;
	for(j=AceClubs;j<=KingSpades;j++){
		same[j%(KingClubs+1)]+=cards[j];
	}
	for(j=KingClubs;j>=AceClubs;j--){						
		if(same[j]==4){		
			compareandchangecategory(&(rank->category) , Four_of_a_kind , &(rank->what) , j);			
			free(same);
			return;
		}
	}
	free(same);
}
	
void isThree_of_a_kind(ranking* rank,unsigned char* cards){	
	unsigned char *same=(unsigned char*)calloc(KingClubs+1,sizeof(unsigned char));
	int j;
	for(j=AceClubs;j<=KingSpades;j++){
		same[j%(KingClubs+1)]+=cards[j];
	}
	for(j=KingClubs;j>=AceClubs;j--){						
		if(same[j]==3){
			int seek=j;
			if(cards[seek+KingHearts+1]>0)
				seek+=KingHearts+1;
			else if(cards[seek+KingDiamonds+1]>0)
				seek+=KingDiamonds+1;
			else if(cards[seek+KingClubs+1]>0)
				seek+=KingClubs+1;
			if(rank->category == Full_house){				//	Full_house
				char aux=changewhat(rank->what,seek);
				if(aux==seek){
					rank->what2=changewhat(rank->what2,rank->what);
					rank->what=seek;
				}
				else {
					rank->what2=changewhat(rank->what2,seek);							
				}
			}
			else if(rank->category == Two_pair)	{		//	Two_pair	=>	Full_house
				rank->category=Full_house;
				rank->what2=rank->what;
				rank->what=seek;
			}
			else if(rank->category == One_pair)	{		//	One_pair	=>	Full_house
				rank->category=Full_house;
				rank->what2=rank->what;
				rank->what=seek;
			}
			else {											//	Three_of_a_kind
				compareandchangecategory(&(rank->category) , Three_of_a_kind , &(rank->what) , seek);						
			}	
		}
	}
	free(same);	
}
	
void isOne_pair(ranking* rank,unsigned char* cards){	
	unsigned char *same=(unsigned char*)calloc(KingClubs+1,sizeof(unsigned char));
	int j;
	for(j=AceClubs;j<=KingSpades;j++){
		same[j%(KingClubs+1)]+=cards[j];
	}
	for(j=KingClubs;j>=AceClubs;j--){						
		if(same[j]==2){
			int seek=j;
			if(cards[seek+KingHearts+1]>0)
				seek+=KingHearts+1;
			else if(cards[seek+KingDiamonds+1]>0)
				seek+=KingDiamonds+1;
			else if(cards[seek+KingClubs+1]>0)
				seek+=KingClubs+1;
			if(rank->category == Full_house){						//	Full_house
				rank->what2=changewhat(rank->what2,seek);						
			}
			else if(rank->category==Three_of_a_kind){				//	Three_of_a_kind	=>	Full_house
				rank->category=Full_house;
				rank->what2=seek;
			}
			else if(rank->category==One_pair){				//	One_pair	=>	Two_pair
				char aux=changewhat(rank->what,seek);
				if(aux==seek){
					rank->what2=changewhat(rank->what2,rank->what);
					rank->what=seek;
				}
				else {
					rank->what2=changewhat(rank->what2,seek);							
				}
				rank->category=Two_pair;
			}
			else {													//	One_pair
				compareandchangecategory(&(rank->category) , One_pair , &(rank->what) , seek);						
			}	
		}
	}
	free(same);	
}
	
void isHigh_card(ranking* rank,unsigned char* cards){
	unsigned char *same=(unsigned char*)calloc(KingClubs+1,sizeof(unsigned char));
	int j;
	for(j=AceClubs;j<=KingSpades;j++){
		same[j%(KingClubs+1)]+=cards[j];
	}
	for(j=KingClubs;j>=AceClubs;j--){						
		if(same[j]==1){
			int seek=j;
			if(cards[seek+KingHearts+1]>0)
				seek+=KingHearts+1;
			else if(cards[seek+KingDiamonds+1]>0)
				seek+=KingDiamonds+1;
			else if(cards[seek+KingClubs+1]>0)
				seek+=KingClubs+1;
			compareandchangecategory(&(rank->category) , High_card , &(rank->what) , seek);
		}
	}
	free(same);	
}
	
void systemrank(int number_players,player* players,unsigned char* publiccommcards,char public,ranking* rank){	// BUGG LA CARTI , AFISARE
	int i;
	for(i=0;i<number_players;i++){
		rank[i].category=High_card+1;
		rank[i].what=TwoClubs;	
	}
	unsigned char* cards=(unsigned char*)calloc(NUMBER_CARDS,sizeof(unsigned char));
	for(i=0;i<public;i++){
			cards[publiccommcards[i]]++;
		}
	for(i=0;i<number_players;i++){
		int j;
		for(j=0;j<NUMBER_HAND_CARDS;j++){
			cards[players[i].card[j]]++;
		}
		
		if(rank[i].category>=Straight_flush){						//	Straight_flush
			isStraight_flush(&(rank[i]),AceClubs,KingClubs,cards);
			isStraight_flush(&(rank[i]),AceDiamonds,KingDiamonds,cards);;
			isStraight_flush(&(rank[i]),AceHearts,KingHearts,cards);
			isStraight_flush(&(rank[i]),AceSpades,KingSpades,cards);
		}				
		if(rank[i].category>=Flush){								//	Flush
			isFlush(&(rank[i]),AceClubs,KingClubs,cards);
			isFlush(&(rank[i]),AceDiamonds,KingDiamonds,cards);;
			isFlush(&(rank[i]),AceHearts,KingHearts,cards);
			isFlush(&(rank[i]),AceSpades,KingSpades,cards);
		}
		if(rank[i].category>=Flush){								//	Straight
			isStraight(&(rank[i]),cards);
		}
		if(rank[i].category>=Four_of_a_kind){						//	Four_of_a_kind
			isFour_of_a_kind(&(rank[i]),cards);
		}		
		if(rank[i].category>=Full_house){							//	Full_house	||	Three_of_a_kind	||	Two_pair || One_pair
			isOne_pair(&(rank[i]),cards);									//	Full_house	||	Two_pair		||	One_pair
			isThree_of_a_kind(&(rank[i]),cards);							//	Full_house	||	Three_of_a_kind	
		}		
		if(rank[i].category>=High_card){							//	High_card
			isHigh_card(&(rank[i]),cards);
		}		
		for(j=0;j<NUMBER_HAND_CARDS;j++){
			cards[players[i].card[j]]--;
		}
	}
	free(cards);
}

void winner(int number_players,player* players,ranking* rank,char ** name_cards,char ** name_rank){
	int category=High_card;
	char whatcard=TwoClubs;
	int i;
	for(i=0;i<number_players;i++){		
		compareandchangecategory(&category , rank[i].category , &whatcard , rank[i].what);
	}
	int number_winners=0;
	char *winners=(char*)calloc(number_players,sizeof(char));
	for(i=0;i<number_players;i++){
		if(category == rank[i].category && isequalcards(rank[i].what,whatcard)==1){
			winners[i]=1;
			number_winners++;
		}
	}
	if(number_winners==1){
			int who=0;
			for(i=0;i<number_players;i++){		
				if(winners[i]==1)
					who=i;
			}
			printf("The winner is the player %d %s with :  %s  (  %s  ).\n",who+1,players[who].name,
			name_rank[category],
			name_cards[(int)whatcard]);
	}
	else {
		printf("Draw with : %s  (  %s  ) for : ",
			name_rank[category],
			name_cards[(int)whatcard]);
		for(i=0;i<number_players;i++){		
			if(winners[i]==1){
				printf("player %d %s , ",i+1,players[i].name);
			}
		}
		printf("\b\b .\n");
	}
	free(winners);
}

