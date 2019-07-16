#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> //abs czyli wartosc bezwzgledna jest tutaj tak?
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Glaz
{
    int klucz;
    int wsp_zbalansowania;
    char Tab_znakow[10];
    struct Glaz* lewy;
    struct Glaz* prawy;
};

struct Stos_wyszukiwania
{
    struct Glaz *AVL_node;
    struct Stos_wyszukiwania *stack_node;
};

int Tablica_losujaca[100000];
int licznik_wystapien;

struct Stos_wyszukiwania* push(struct Glaz *wartosc, struct Stos_wyszukiwania *pierwszy_el);
struct Stos_wyszukiwania* pop(struct Stos_wyszukiwania *pierwszy_el);

int heigth(struct Glaz* wezel);
int obliczbalans(struct Glaz* aktualny);
struct Glaz* leftrotation(struct Glaz *niezbalansowany);
struct Glaz* rightrotation(struct Glaz *niezbalansowany);
struct Glaz* rightleftrotation(struct Glaz *niezbalansowany);
struct Glaz* leftrightrotation(struct Glaz *niezbalansowany);
struct Stos_wyszukiwania *wyszukaj_glaz(struct Glaz* glowa, int szukany);
struct Glaz* usun_glaz(struct Glaz* AVL_korzen, int X);
struct Glaz* dodaj_glaz(struct Glaz* AVL_korzen, int X);
int trawersuj_inorder(struct Glaz* element);
int trawersuj_preorder(struct Glaz* element);
int trawersuj_postorder(struct Glaz* element);
struct Glaz* losowe_el(struct Glaz* glowa, int X);
struct timespec diff(struct timespec start,struct timespec end);
 
int main(int ac, char **at)
{
    struct timespec start,end;
    
    clock_gettime(CLOCK_MONOTONIC,&start);
    printf("Czas poczatek: %d\n",start.tv_nsec);

    ///////////////////////////
    srand(time(NULL));
    struct Glaz* korzen = NULL;
    struct Stos_wyszukiwania *sciezka_poszukiwan;
    
    int X, k1, k2, k3, k4;

    FILE * fp = fopen("inlab04.txt", "r");
    if(fp == NULL )
        return -1;
    
    fscanf(fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
    fclose(fp);
    
    korzen = usun_glaz(korzen,k1);
    korzen = dodaj_glaz(korzen,k1);
    korzen = losowe_el(korzen,X);
    printf("\nLiczba elementow: %d\n ",trawersuj_inorder(korzen));
    printf("\n--------------\n");
    printf("\nLiczba elementow: %d\n ",trawersuj_preorder(korzen));
    printf("\n--------------\n");
    korzen = dodaj_glaz(korzen,k2);
    printf("\nLiczba elementow: %d\n ",trawersuj_inorder(korzen));
    printf("\n--------------\n");
    korzen = dodaj_glaz(korzen,k3);
    korzen = dodaj_glaz(korzen,k4);
    korzen = usun_glaz(korzen,k1);
    printf("\nLiczba elementow: %d\n ",trawersuj_preorder(korzen));
    printf("\n--------------\n");
    sciezka_poszukiwan = wyszukaj_glaz(korzen,k1);
   // if(sciezka_poszukiwan!=NULL) printf("\nZnaleziono wezel o podanym kluczu: %d. Sciezka ktora do niego prowadzi: ",k1); do{printf(" %d ",sciezka_poszukiwan->AVL_node->klucz); sciezka_poszukiwan = pop(sciezka_poszukiwan); }while(sciezka_poszukiwan!=NULL);
    korzen = usun_glaz(korzen,k2);
    printf("\nLiczba elementow: %d\n ",trawersuj_inorder(korzen));
    printf("\n--------------\n");
    korzen = usun_glaz(korzen,k3);
    korzen = usun_glaz(korzen,k4);
    ///////////////
    
    
    clock_gettime(CLOCK_MONOTONIC,&end);
    printf("Elapsed time equals %.4f seconds\n", diff(start,end).tv_sec + diff(start,end).tv_nsec/1e9);
    
    //time_t end;
    //time(&end);
    //time_t program = end - begin;
    //struct tm tm = *localtime (&program);
    //printf("\nCzas wykonania: %d\n",tm.tm_sec);
    //printf("Czas koniec: %d\n",end);
    
    // korzen = dodaj_glaz(korzen,10);
   // korzen = dodaj_glaz(korzen,14);
   // korzen = dodaj_glaz(korzen,13);
   // printf("Root: %d \n",korzen->klucz);
    //printf("%c   <-\n\n\n ",*at[0]);
    //Mogę tak odczytywać argumenty przy wywołaniu programu
    // Pierwszy argument to start, kolejne będą przekazanymi
    //Mogę je przekonwertować na inta z pomocą atoi lub sscanf
    //Jak przekazać parametry przez konsolę?
    //timespec start, end
    //clock gettime (CLOCK_MONOTONIC &start);
    
    /*
    korzen = dodaj_glaz(korzen,3);
    korzen = dodaj_glaz(korzen,10);
    korzen = dodaj_glaz(korzen,2);
    korzen = dodaj_glaz(korzen,8);
    korzen = dodaj_glaz(korzen,7);
    korzen = dodaj_glaz(korzen,6);
    korzen = dodaj_glaz(korzen,13);
    korzen = dodaj_glaz(korzen,0);
    korzen = dodaj_glaz(korzen,14);
    korzen = dodaj_glaz(korzen,12);

    korzen = dodaj_glaz(korzen,3);
    korzen = dodaj_glaz(korzen,4);
    korzen = dodaj_glaz(korzen,1);
    korzen = dodaj_glaz(korzen,9);
    korzen = dodaj_glaz(korzen,12);
    korzen = dodaj_glaz(korzen,13);
    korzen = dodaj_glaz(korzen,10);
    korzen = dodaj_glaz(korzen,14);
    korzen = dodaj_glaz(korzen,8);
    korzen = dodaj_glaz(korzen,0);
     
    korzen = dodaj_glaz(korzen,10);
    korzen = dodaj_glaz(korzen,8);
    korzen = dodaj_glaz(korzen,7);
    korzen = dodaj_glaz(korzen,0);
    korzen = dodaj_glaz(korzen,6);
    korzen = dodaj_glaz(korzen,9);
    korzen = dodaj_glaz(korzen,14);
    korzen = dodaj_glaz(korzen,13);
    korzen = dodaj_glaz(korzen,2);
    korzen = dodaj_glaz(korzen,5);
    */
    return 0;
}

struct Stos_wyszukiwania* push(struct Glaz *wartosc, struct Stos_wyszukiwania *pierwszy_el)
{
    struct Stos_wyszukiwania *tymcz;
    tymcz = (struct Stos_wyszukiwania *)malloc(sizeof(struct Stos_wyszukiwania));
    
    tymcz->AVL_node = wartosc;
    tymcz->stack_node = pierwszy_el;
    pierwszy_el = tymcz;
    pierwszy_el->stack_node==NULL;
    return pierwszy_el;
} 

struct Stos_wyszukiwania* pop(struct Stos_wyszukiwania *pierwszy_el)
{
    struct Stos_wyszukiwania *tymczasowy=pierwszy_el;
    
    if(tymczasowy->stack_node!=NULL)
    {
        pierwszy_el = pierwszy_el->stack_node;
        free(tymczasowy);
        return pierwszy_el;
    }
    else
    return NULL;
    

}

int heigth(struct Glaz* wezel)
{
int lh,rh;
if(wezel==NULL)
return 0;
lh = heigth(wezel->lewy);
rh = heigth(wezel->prawy);
return (1+MAX(lh,rh)); 
}

int obliczbalans(struct Glaz* aktualny)
{
    return (heigth(aktualny->prawy) - heigth(aktualny->lewy)); 
}
    
struct Glaz* leftrotation(struct Glaz *niezbalansowany)
{
    
    struct Glaz *unbalanced_pd=niezbalansowany->prawy; //Prawe-Dziecko
    
    niezbalansowany->prawy=unbalanced_pd->lewy;  
    unbalanced_pd->lewy = niezbalansowany;
    
    niezbalansowany->wsp_zbalansowania = (unbalanced_pd->wsp_zbalansowania==1) ? 0 : 1;
    unbalanced_pd->wsp_zbalansowania = (unbalanced_pd->wsp_zbalansowania==0) ? 1 : 0;

    return unbalanced_pd;
    
}

struct Glaz* rightrotation(struct Glaz *niezbalansowany)
{
    struct Glaz *unbalanced_ld=niezbalansowany->lewy; //Lewe-Dziecko
    
    niezbalansowany->lewy=unbalanced_ld->prawy;  
    unbalanced_ld->prawy = niezbalansowany;
    
    niezbalansowany->wsp_zbalansowania = (unbalanced_ld->wsp_zbalansowania==-1) ? 0 : -1;
    unbalanced_ld->wsp_zbalansowania = (unbalanced_ld->wsp_zbalansowania==0) ? 1 : 0;
    return unbalanced_ld;
}

struct Glaz* rightleftrotation(struct Glaz *niezbalansowany)
{
    struct Glaz *unbalanced_pd=niezbalansowany->prawy; //Prawe-Dziecko
    struct Glaz *unbalanced_pd_lewy = unbalanced_pd->lewy;
    
    //printf("niezbalansowany: %d\n",niezbalansowany->klucz);
    //printf("niezbalansowany: %d\n",niezbalansowany->prawy->klucz);
    //printf("niezbalansowany: %d\n",niezbalansowany->prawy->lewy->klucz);
    
    struct Glaz *tymczasowy = unbalanced_pd_lewy->prawy;
    //right
    unbalanced_pd->lewy = tymczasowy;
    unbalanced_pd_lewy->prawy = unbalanced_pd;
    niezbalansowany->prawy = unbalanced_pd_lewy;
    
    //left
   // printf("%%niezbalansowany: %d\n",niezbalansowany->klucz);
   // printf("%%niezbalansowany: %d\n",unbalanced_pd_lewy->lewy); 
   // printf("%%niezbalansowany: %d\n",niezbalansowany->prawy->klucz);
      
    niezbalansowany->prawy = unbalanced_pd_lewy->lewy;
    unbalanced_pd_lewy->lewy = niezbalansowany;
    
    //printf("%%niezbalansowany: %d\n",unbalanced_pd_lewy->klucz);
    //printf("%%niezbalansowany: %d\n",unbalanced_pd_lewy->lewy->klucz);
    //printf("%%niezbalansowany: %d\n",unbalanced_pd_lewy->prawy->klucz);
    
    niezbalansowany->wsp_zbalansowania = (unbalanced_pd_lewy->wsp_zbalansowania==-1) ? 1:0;
    unbalanced_pd->wsp_zbalansowania = (unbalanced_pd_lewy->wsp_zbalansowania==1) ? -1:0;
    unbalanced_pd_lewy->wsp_zbalansowania=0;
    
    return unbalanced_pd_lewy;
}

 struct Glaz* leftrightrotation(struct Glaz *niezbalansowany)
{
    struct Glaz *unbalanced_pd=niezbalansowany->lewy; //Prawe-Dziecko
    struct Glaz *unbalanced_pd_prawy = unbalanced_pd->prawy;
    
    //left
    unbalanced_pd->prawy = unbalanced_pd_prawy->lewy;
    unbalanced_pd_prawy->lewy = unbalanced_pd;
    niezbalansowany->lewy = unbalanced_pd_prawy;
    
    //right
    niezbalansowany->lewy = unbalanced_pd_prawy->prawy;
    unbalanced_pd_prawy->prawy = niezbalansowany;
    
    niezbalansowany->wsp_zbalansowania = (unbalanced_pd_prawy->wsp_zbalansowania==1) ? -1:0;
    unbalanced_pd->wsp_zbalansowania = (unbalanced_pd_prawy->wsp_zbalansowania==-1) ? 1:0;
    unbalanced_pd_prawy->wsp_zbalansowania=0; 
    
    return unbalanced_pd_prawy;
}
    
struct Stos_wyszukiwania *wyszukaj_glaz(struct Glaz* glowa, int szukany)
{
    struct Glaz *tymcz = glowa;
    struct Stos_wyszukiwania *sciezka_poszukiwan=NULL;
    while(tymcz!=NULL)
    {
        if(tymcz->klucz == szukany)
        break;
        
        if(szukany > tymcz->klucz)
        {sciezka_poszukiwan = push(tymcz,sciezka_poszukiwan); tymcz=tymcz->prawy;}
        else
        {sciezka_poszukiwan = push(tymcz,sciezka_poszukiwan); tymcz=tymcz->lewy;}
    }
    
    if(tymcz==NULL) {printf("\nWyszukiwanie: nie znaleziono elementu o takim kluczu. \n\n"); return 0;}
    
    return sciezka_poszukiwan;
}

struct Glaz* usun_glaz(struct Glaz* AVL_korzen, int X)
{
    if(AVL_korzen == NULL) {printf("\nUsuwanie elementow: lista jest pusta \n\n"); return AVL_korzen;}

    struct Glaz *tymcz = AVL_korzen, *rodzic = NULL, *potomek;
    int czy_lewy = 0;
    struct Stos_wyszukiwania *odkorzenia = NULL;
    
    
    while(tymcz!=NULL)
    {
        
        if(X == tymcz->klucz)
        break;
        else if(X >tymcz->klucz)
        {
        odkorzenia = push(tymcz,odkorzenia); 
        rodzic = tymcz; tymcz = tymcz->prawy; czy_lewy = 0;}
        else 
        {
        odkorzenia = push(tymcz,odkorzenia); 
        rodzic = tymcz; tymcz = tymcz->lewy; czy_lewy = 1;}
    
    }
    
    if(tymcz == NULL) //Nie  udalo sie znalezc podanej wartosci
    {printf("Element nie istnieje, nie mozna usunac. "); return AVL_korzen;}
    
    //Tymcz wskazuje na wezel do usuniecia. Mozliwosci:
    // 1) Jest lisciem
    // 2) Ma jednego potomka
    // 3) Ma dwoch potomkow
    
    if(tymcz->prawy == NULL&&tymcz->lewy==NULL) //Jezeli wyszukany wezel jest lisciem
    {
        //Znaleziony wezel jest korzeniem drzewa
        if(rodzic == NULL)
        AVL_korzen=NULL;
        else 
        {
            if(rodzic->lewy==tymcz) //Jezeli znaleziony byl lewym, ustawiam wskaznik jego rodzica->lewy na null
            rodzic->lewy=NULL;
            else
            rodzic->prawy=NULL;
        }
        free(tymcz);
    }
    else
    if(tymcz->lewy == NULL || tymcz->prawy == NULL)
    {
        // Szukany element ma tylko jednego potomka
        if(tymcz->prawy==NULL)
            potomek = tymcz->lewy;
        else
            potomek= tymcz->prawy;
            
        if(rodzic == NULL) //jezeli brak rodzica usuwamy korzen
        AVL_korzen = potomek;
        else
        {
            //usuwamy galaz posiadajaca potomka i nie bedaca korzeniem
            if(czy_lewy)
            rodzic->lewy = potomek;
            else
            rodzic->prawy = potomek;
        }
        free(tymcz);
    }
    else
    {
        // Trzecia opcja: wyszukany wezel ma dwoje potomkow

        //Znajduje nastepnika: 
        
        //Tutaj musze przekonfigurowac liste. Musi ona wyszukiwac od miejsca gdzie usunieto nastepnika
        struct Glaz *nastepnik;
        struct Glaz *tymcz_nastepnik=tymcz->prawy;
        odkorzenia = push(tymcz,odkorzenia);
        //Jezeli tymczasowy nastepnik ma przynajmniej jednego lewego potomka, moge dodac tymczasowy nastepnik do listy
        //Wtedy od niego rozpoczna sie poszukiwania (W domysle szukam miejsca nastepnika)
    
    
        while(tymcz_nastepnik->lewy!=NULL)
        {
            nastepnik = tymcz_nastepnik;
            odkorzenia = push(nastepnik,odkorzenia);
            
            tymcz_nastepnik = tymcz_nastepnik->lewy;
        }
        
        nastepnik = tymcz_nastepnik;
        
        int klucz_nastepnika = nastepnik->klucz;
        struct Glaz *rodzic_nastepnika = odkorzenia->AVL_node;
        //Proces usuwania nastepnika. Bedzie on mial prawego lub 0 potomkow
        
        //Jezeli nastepnikiem jest pierwszy po prawej usuwanego wezla
        //if(tymcz_nastepnik->lewy==NULL)
        //rodzic_nastepnika = odkorzenia->stack_node->AVL_node;
        
        //printf("rodzic nastepnika: %d\n\n",rodzic_nastepnika->klucz);
        
      //  printf("raz: %d",tymcz->prawy->klucz);
      //  printf("raz: %d",nastepnik->prawy);
        
        if(tymcz->prawy == nastepnik) //Jezeli nie musialem dlugo szukac nastepnika
        {
            if(nastepnik->prawy == NULL) //Nastepnik nie ma zadnych potomkow
            {free(nastepnik); rodzic_nastepnika->prawy = NULL;}
            else       // Szukany element ma tylko jednego potomka
            {rodzic_nastepnika->prawy = nastepnik->prawy; free(nastepnik);}}
        else //Jezeli nastepnik nie byl prawym dzieckiem usuwanego (czyli prawe dziecko usuwanego mialo jakies mniejsze dzieci)
        {
            if(nastepnik->prawy == NULL) //Nastepnik nie ma zadnych potomkow
            {free(nastepnik); rodzic_nastepnika->lewy = NULL;}
            else       // Szukany element ma tylko jednego potomka
            {rodzic_nastepnika->lewy = nastepnik->prawy; free(nastepnik);}}
        
        
        tymcz->klucz = klucz_nastepnika;
        
       // printf("^^ tTYMCZ: %d\n",tymcz->klucz);
       // tymcz->wsp_zbalansowania = obliczbalans(tymcz);
       // printf("^^ tTYMCZ: %d\n",tymcz->wsp_zbalansowania);
       // printf("STOS: %d\n",odkorzenia->stack_node->AVL_node->klucz);
        
    }
    //rebalancing
    int poprzedni_wsp = 0;
    int obecny_wsp = 0;
    int zbalansowane = 0;
    
        //poprzedni_wsp = odkorzenia->AVL_node->wsp_zbalansowania;
        //odkorzenia->AVL_node->wsp_zbalansowania = obliczbalans(odkorzenia->AVL_node);
        //obecny_wsp = odkorzenia->AVL_node->wsp_zbalansowania;
         
        while(odkorzenia&&!zbalansowane)
        {
       
        odkorzenia->AVL_node->wsp_zbalansowania = obliczbalans(odkorzenia->AVL_node);
        obecny_wsp = odkorzenia->AVL_node->wsp_zbalansowania;
        
        if(abs(obecny_wsp)==1)    //W drodze do korzenia napotkalismy wezel, w ktorym nastapila zmiana wspolcznynnika z 0 na +/- 1
        {zbalansowane=1; break;}
        
        //Przy zmianie z +/- 1 na 0 podrozujemy dalej
        
        if(abs(obecny_wsp)==2) //Napotkano niezbalansowany wezel - rebalancing
        {
            
            
            struct Glaz *niezbalansowany = odkorzenia->AVL_node;
            if(odkorzenia->stack_node!=NULL) odkorzenia=odkorzenia->stack_node;
            struct Glaz *rodzic_niezbalansowanego = odkorzenia->AVL_node;
            struct Glaz *tymczasowy_pivot;
            int wykonalem_rotacje = 0;
            
            if(obecny_wsp == 2)
            {
                
             //   printf("\n\n Wewnatrz funkcji: %d \n",trawersuj_inorder(AVL_korzen));
                
                
                    struct Glaz *wsk_prawy = niezbalansowany->prawy; 
                    poprzedni_wsp = wsk_prawy->wsp_zbalansowania;
                    struct Glaz *tymczasowy_pivot_dwa;
                    
                    struct Glaz *wsp_dopoprawy = niezbalansowany->prawy;
                    
                    if(wsk_prawy->wsp_zbalansowania == 1)
                    {tymczasowy_pivot = leftrotation(niezbalansowany); wykonalem_rotacje = 1;}
                    
                    if(wsk_prawy->wsp_zbalansowania == -1&&!wykonalem_rotacje)
                    //tymczasowy_pivot_dwa = rightrotation(niezbalansowany->prawy); 
                    //niezbalansowany->prawy = tymczasowy_pivot_dwa;
                    {tymczasowy_pivot = rightleftrotation(niezbalansowany);wykonalem_rotacje = 1;}               
                    
                    
                    if(wsk_prawy->wsp_zbalansowania == 0&&!wykonalem_rotacje)
                    {tymczasowy_pivot = leftrotation(niezbalansowany); zbalansowane = 1; wykonalem_rotacje = 1;}
                    
                    //Tu jest blad korzen(9) -> ma wskazywac na? (13)? 
                    if(rodzic_niezbalansowanego == niezbalansowany)
                    AVL_korzen = tymczasowy_pivot;
                    else
                    {
                    if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                    rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                    else
                    rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                    wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
            }
            else
            {
               // printf("Niezbalansowany: %d\n",niezbalansowany->klucz);
                
                struct Glaz *lewy_niezbalansowanego = niezbalansowany->lewy;
                lewy_niezbalansowanego->wsp_zbalansowania = obliczbalans(lewy_niezbalansowanego);
                struct Glaz *wsp_dopoprawy = niezbalansowany->lewy;
                
                if(lewy_niezbalansowanego->wsp_zbalansowania == 1)
                {tymczasowy_pivot = leftrightrotation(niezbalansowany); wykonalem_rotacje = 1;}
                
                if(lewy_niezbalansowanego->wsp_zbalansowania == -1&&!wykonalem_rotacje)
                {tymczasowy_pivot = rightrotation(niezbalansowany); wykonalem_rotacje = 1;}
                
                if(lewy_niezbalansowanego->wsp_zbalansowania == 0&&!wykonalem_rotacje)
                {tymczasowy_pivot = rightrotation(niezbalansowany); zbalansowane = 1; wykonalem_rotacje = 1;}
                
                if(rodzic_niezbalansowanego == niezbalansowany)
                AVL_korzen = tymczasowy_pivot;
                else
                {
                if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                else
                rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
            }
            
        } 
        
        odkorzenia = odkorzenia->stack_node;
        }
        /*                    
printf("## %d \n\n",tymczasowy_pivot->klucz);
printf("## %d \n\n",tymczasowy_pivot->prawy->klucz);
printf("## %d \n\n",tymczasowy_pivot->lewy->klucz);

printf("##(AVL) %d \n\n",AVL_korzen);
printf("##(AVL) %d \n\n",rodzic_niezbalansowanego);
                
                    printf("##(AVL) %d \n\n",AVL_korzen->prawy->klucz);
                    
//printf("\n\n 2Wewnatrz funkcji: %d \n",trawersuj_inorder(AVL_korzen));    
        */
    return AVL_korzen;
    
}

struct Glaz* dodaj_glaz(struct Glaz* AVL_korzen, int X)
{
    struct Glaz *AVL_temporary=AVL_korzen, *AVL_nowy, *AVL_rodzic_nowy;
    AVL_nowy = (struct Glaz*) malloc(sizeof(struct Glaz));
    if(AVL_nowy==NULL){printf("Blad przydzielenia pamieci."); return 0;}
    
    /////////////////
    AVL_nowy->klucz=X;
    sprintf(AVL_nowy->Tab_znakow, "%d", X);
    AVL_nowy->wsp_zbalansowania = 0;
    AVL_nowy->lewy=NULL;
    AVL_nowy->prawy=NULL;
    /////////////////
   struct Stos_wyszukiwania *stos_odkorzenia = NULL;
    
    if(AVL_temporary!=NULL) //Jezeli drzewo nie jest puste
    {
        while(AVL_temporary!=NULL) //Szuka wlasciwego miejsca dla nowego elementu
        {
        if(X == AVL_temporary->klucz) {printf("Element o podanym kluczu juz znajduje sie w BST."); return 0;}
        
        else if(X >AVL_temporary->klucz)
        {stos_odkorzenia = push(AVL_temporary,stos_odkorzenia); 
        AVL_rodzic_nowy = AVL_temporary; AVL_temporary = AVL_temporary->prawy;}
        else 
        {stos_odkorzenia = push(AVL_temporary,stos_odkorzenia);
        AVL_rodzic_nowy = AVL_temporary; AVL_temporary = AVL_temporary->lewy;}
        }
        
    if(AVL_rodzic_nowy->klucz > X)
    AVL_rodzic_nowy->lewy = AVL_nowy;
    else
    AVL_rodzic_nowy->prawy = AVL_nowy;
    
    int poprzedni_wsp = 0;
    int obecny_wsp = 0;
    int zbalansowane = 0;
    while(stos_odkorzenia&&!zbalansowane)
    {
        
        stos_odkorzenia->AVL_node->wsp_zbalansowania = obliczbalans(stos_odkorzenia->AVL_node);
        obecny_wsp = stos_odkorzenia->AVL_node->wsp_zbalansowania;
        
        if(obecny_wsp==0) //Napotkalem w drodze od wstawionego liscia wsp = 0, drzewo jest zbalansowane
        {zbalansowane = 1; break;}
        
        //printf("<< %d >>",obecny_wsp);
        if(abs(obecny_wsp)==2) //Napotkano niezbalansowany wezel - rebalancing
        {
            
            
            struct Glaz *niezbalansowany = stos_odkorzenia->AVL_node;
            if(stos_odkorzenia->stack_node!=NULL) stos_odkorzenia=stos_odkorzenia->stack_node;
            struct Glaz *rodzic_niezbalansowanego = stos_odkorzenia->AVL_node;
            struct Glaz *tymczasowy_pivot;
        
            if(obecny_wsp==2)
            {
                    struct Glaz *wsk_prawy = niezbalansowany->prawy; 
                    poprzedni_wsp = wsk_prawy->wsp_zbalansowania;
                    
                    struct Glaz *wsp_dopoprawy = niezbalansowany->prawy;
                    
                    if(obecny_wsp*poprzedni_wsp > 0) //Przypadek jednorodny PP
                    tymczasowy_pivot = leftrotation(niezbalansowany);
                    else //Przypadek niejednorodny PL
                    tymczasowy_pivot = rightleftrotation(niezbalansowany);
                    
                    if(rodzic_niezbalansowanego == niezbalansowany)
                    AVL_korzen = tymczasowy_pivot;
                    else
                    {
                    if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                    rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                    else
                    rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                    wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
            }       
            else
            {
                    
                    struct Glaz *wsk_lewy = niezbalansowany->lewy; 
                    poprzedni_wsp = wsk_lewy->wsp_zbalansowania;
        
                    struct Glaz *wsp_dopoprawy = niezbalansowany->lewy;
                    
                    if(obecny_wsp*poprzedni_wsp > 0) //Przypadek jednorodny LL
                    tymczasowy_pivot= rightrotation(niezbalansowany);
                    else //Przypadek niejednorodny LP
                    {
                    tymczasowy_pivot = leftrightrotation(niezbalansowany);
                    }

                    if(rodzic_niezbalansowanego == niezbalansowany)
                    AVL_korzen = tymczasowy_pivot;
                    else
                    {
                    if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                    rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                    else
                    rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                    wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
            }
            zbalansowane = 1; break;
        }
        
        stos_odkorzenia = stos_odkorzenia->stack_node;
    }

    
    }else AVL_korzen = AVL_nowy;
    
    return AVL_korzen;
}

int trawersuj_inorder(struct Glaz* element)
{
    int licznik = 0; int i=0;
    if(element!=NULL){
        licznik++;
        licznik += trawersuj_inorder(element->lewy);
        printf("( K: %d ", element->klucz);
        while(element->Tab_znakow[i])
        {printf("%c",element->Tab_znakow[i]); i++;}
        printf(")");
        licznik += trawersuj_inorder(element->prawy);
    }
    return licznik;
}

int trawersuj_preorder(struct Glaz* element)
{
    int licznik = 0; int i=0;
    if(element!=NULL){
        licznik++;
        printf("( K: %d ", element->klucz);
        printf("C: ");
        while(element->Tab_znakow[i])
        {printf("%c",element->Tab_znakow[i]); i++;}
        printf(")");
        licznik += trawersuj_preorder(element->lewy);
        licznik += trawersuj_preorder(element->prawy);
    }
    return licznik;
}

int trawersuj_postorder(struct Glaz* element)
{
    int licznik=0; int i=0;
    if(element!=NULL){
        licznik++;
        licznik+= trawersuj_postorder(element->lewy);
        licznik+= trawersuj_postorder(element->prawy);
        printf("( K: %d ", element->klucz);
        printf("C: ");
        while(element->Tab_znakow[i])
        {printf("%c",element->Tab_znakow[i]); i++;}
        printf(")");
    }
    return licznik;
}

struct Glaz* losowe_el(struct Glaz* glowa, int X)
{
    // W poprzednim programie nie losowales dokladnie X elementow
    // Inkrementujesz i tylko kiedy dodaj poprawnie element
    struct Glaz *tymcz = glowa;
    int a;
    int i = 0;
    while(i < X)
    {
    a = (rand()%100000);
       if(!Tablica_losujaca[a])
       {tymcz = dodaj_glaz(tymcz,(a));
        i++; Tablica_losujaca[a]=1;} 
    }
    
    return tymcz;
}

struct timespec diff(struct timespec start,struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

/*
 * 

 * 
 * 
 * 
    while(stos_odkorzenia&&!zbalansowane)
    {
        /*
        Założenia: 
        1. Od wstawionego liscia podrozuje przez stos
        2. Obliczam wspolczynniki dla kazdego napotkanego wezla, zachowujac stare wersje (moze na tej samej stercie w innej zmiennej?)
        3. Jezeli wspolczynnik wyniesie 2: 
        - sprawdz, czy wspolczynnik prawego wezla wynosil 0 przed usunieciem
        - sprawdz, czy wspolczynnik prawego dziecka wonosil 1 przed usunieciem. Jesli tak, wykonaj rotacje w lewo wokol wezla 2
        - nastepnie idz dalej do korzenia sprawdzajac wspolczynniki (zbalansowano lokalnie)
        - sprawdz, czy wspolczynnik lewego dziecka wynosi -1. Jesli tak, wykonaj balansowanie w lewo wokol jego prawego dziecka, 
        - a nastepnie w prawo wokol wezla 2(czy -1)? i podrozuj dalej w celu znalezienia wezla
        4. Analogicznie dla wspolczynnika -2: 
        

        poprzedni_wsp = stos_odkorzenia->AVL_node->wsp_zbalansowania;
        stos_odkorzenia->AVL_node->wsp_zbalansowania = obliczbalans(stos_odkorzenia->AVL_node);
        obecny_wsp = stos_odkorzenia->AVL_node->wsp_zbalansowania;
        if(abs(obecny_wsp)!=2) poprzedni_wsp = poprzedni_wsp_tymczasowy;
        
        if(abs(obecny_wsp)==2) //Napotkano niezbalansowany wezel - rebalancing
        {
            
            struct Glaz *niezbalansowany = stos_odkorzenia->AVL_node;
            if(stos_odkorzenia->stack_node!=NULL) stos_odkorzenia=stos_odkorzenia->stack_node;
            struct Glaz *rodzic_niezbalansowanego = stos_odkorzenia->AVL_node;
            struct Glaz *tymczasowy_pivot;
        
            if(obecny_wsp==2)
            {
                
            if(AVL_korzen->prawy==niezbalansowany) czy_korzen = 1;
                
            if(poprzedni_wsp_tymczasowy==0)                         // Prawy potomek niezbalansowanego jest rowny 0, jedna rotacja w lewo
            {tymczasowy_pivot = leftrotation(niezbalansowany);      //Przywraca porzadek globalny
            zbalansowane = 1; break;}
                
            struct Glaz *wsk_prawy =stos_odkorzenia->AVL_node->prawy; 
            poprzedni_wsp = wsk_prawy->wsp_zbalansowania;
                    
            if(obecny_wsp*poprzedni_wsp > 0) //Przypadek jednorodny PP
            tymczasowy_pivot = leftrotation(niezbalansowany);
            else //Przypadek niejednorodny PL
            tymczasowy_pivot = rightleftrotation(niezbalansowany,rodzic_niezbalansowanego,AVL_korzen,5);
            
            } //Obecny_wsp == -2       
            else
            {
            if(AVL_korzen->lewy==niezbalansowany) czy_korzen = 1;    
                
            if(poprzedni_wsp_tymczasowy==0)                                         // Lewy potomek niezbalansowanego jest rowny 0, jedna rotacja w prawo
            {tymczasowy_pivot = rightrotation(niezbalansowany);                     //Przywraca porzadek globalny
            zbalansowane = 1; break;}
                
            struct Glaz *wsk_lewy =stos_odkorzenia->AVL_node->lewy; 
            poprzedni_wsp = wsk_lewy->wsp_zbalansowania;
                    
            if(obecny_wsp*poprzedni_wsp > 0) //Przypadek jednorodny LL
            tymczasowy_pivot= rightrotation(niezbalansowany);
            else //Przypadek niejednorodny LP
            tymczasowy_pivot = leftrightrotation(niezbalansowany,rodzic_niezbalansowanego,AVL_korzen,5);                                                        
            }
            
            //Przypisuje rodzica niezbalansowanego 
            if(rodzic_niezbalansowanego==AVL_korzen&&!czy_korzen) {AVL_korzen = tymczasowy_pivot;}
            else if (rodzic_niezbalansowanego == AVL_korzen&&czy_korzen&& X > AVL_korzen->klucz) AVL_korzen->prawy = tymczasowy_pivot;
            else if (rodzic_niezbalansowanego == AVL_korzen&&czy_korzen&& X < AVL_korzen->klucz) AVL_korzen->lewy = tymczasowy_pivot;
            else if (X > rodzic_niezbalansowanego->klucz) {rodzic_niezbalansowanego->prawy = tymczasowy_pivot;}
            else if (X < rodzic_niezbalansowanego->klucz) {rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
        }
        
        stos_odkorzenia = stos_odkorzenia->stack_node;
    }
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     *         // Trzecia opcja: wyszukany wezel ma dwoje potomkow

        //Znajduje nastepnika: 
        
        //Tutaj musze przekonfigurowac liste. Musi ona wyszukiwac od miejsca gdzie usunieto nastepnika
        
        struct Glaz *nastepnik;
        struct Glaz *tymcz_nastepnik=tymcz->prawy;
        odkorzenia = push(tymcz,odkorzenia);
        //Jezeli tymczasowy nastepnik ma przynajmniej jednego lewego potomka, moge dodac tymczasowy nastepnik do listy
        //Wtedy od niego rozpoczna sie poszukiwania (W domysle szukam miejsca nastepnika)
        
        
        
        while(tymcz_nastepnik->lewy!=NULL)
        {
            nastepnik = tymcz_nastepnik;
            odkorzenia = push(nastepnik,odkorzenia);
            
            tymcz_nastepnik = tymcz_nastepnik->lewy;
        }
        
        nastepnik = tymcz_nastepnik;
        
        int klucz_nastepnika = nastepnik->klucz;
        struct Glaz *rodzic_nastepnika = odkorzenia->AVL_node;
        //Proces usuwania nastepnika. Bedzie on mial prawego lub 0 potomkow
        
        //Jezeli nastepnikiem jest pierwszy po prawej usuwanego wezla
        //if(tymcz_nastepnik->lewy==NULL)
        //rodzic_nastepnika = odkorzenia->stack_node->AVL_node;
        
        printf("rodzic: %d\n",rodzic_nastepnika->klucz);
        printf("rodzic: %d\n",nastepnik->klucz);
        printf("Dziesiatka: %d\n",odkorzenia->stack_node->AVL_node->klucz); 
        
        //printf("rodzic nastepnika: %d\n\n",rodzic_nastepnika->klucz);
        
        if(nastepnik->prawy == NULL) //Nastepnik nie ma zadnych potomkow
        {free(nastepnik); rodzic_nastepnika->lewy = NULL;}
        else       // Szukany element ma tylko jednego potomka
        {rodzic_nastepnika->lewy = nastepnik->prawy; free(nastepnik);}

        tymcz->klucz = klucz_nastepnika;
        
        printf("rodzic: %d\n",tymcz->klucz);
         * 
         * 
         * 
         * 
         * 
         * 
         *                 /*
                printf("Napotkano wezel: %d\n",niezbalansowany->klucz);
                
                struct Glaz *wsk_prawy = niezbalansowany->prawy; 
                poprzedni_wsp = wsk_prawy->wsp_zbalansowania;
                struct Glaz *wsp_dopoprawy = niezbalansowany->prawy;
              
                if(wsk_prawy->wsp_zbalansowania == 1)
                tymczasowy_pivot = rightleftrotation(niezbalansowany);
                
                if(wsk_prawy->wsp_zbalansowania == -1)
                {   
                    tymczasowy_pivot = rightleftrotation(niezbalansowany);  
                    
                    printf("Tymczasowypivot: %d\n",tymczasowy_pivot->klucz);
                    printf("Tymczasowypivot: %d\n",tymczasowy_pivot->lewy->klucz);
                    printf("Tymczasowypivot: %d\n",tymczasowy_pivot->prawy->klucz);
                    
                }
                
                if(wsk_prawy->wsp_zbalansowania == 0)
                {tymczasowy_pivot = leftrotation(niezbalansowany); zbalansowane = 1;}
                
                
                if(rodzic_niezbalansowanego == niezbalansowany)
                AVL_korzen = tymczasowy_pivot;
                
                else
                {
                if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                else
                rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                    
                //printf("Rodzic niezbalansowanego: %d\n",rodzic_niezbalansowanego->prawy->klucz);
                    
                printf("Tymczasowypivot: %d\n", rodzic_niezbalansowanego->prawy->klucz);
                printf("Tymczasowypivot: %d\n", rodzic_niezbalansowanego->prawy->lewy->klucz);
                printf("Tymczasowypivot: %d\n", rodzic_niezbalansowanego->prawy->prawy->klucz);
                wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * 
                 * Poprzednia wersja usunglaz: 
                 * 
                 * struct Glaz* usun_glaz(struct Glaz* AVL_korzen, int X)
{
    if(AVL_korzen == NULL) {printf("\nUsuwanie elementow: lista jest pusta \n\n"); return AVL_korzen;}

    struct Glaz *tymcz = AVL_korzen, *rodzic = NULL, *potomek;
    int czy_lewy = 0;
    struct Stos_wyszukiwania *odkorzenia = NULL;
    
    
    while(tymcz!=NULL)
    {
        
        if(X == tymcz->klucz)
        break;
        else if(X >tymcz->klucz)
        {
        odkorzenia = push(tymcz,odkorzenia); 
        rodzic = tymcz; tymcz = tymcz->prawy; czy_lewy = 0;}
        else 
        {
        odkorzenia = push(tymcz,odkorzenia); 
        rodzic = tymcz; tymcz = tymcz->lewy; czy_lewy = 1;}

    }
    
    if(tymcz == NULL) //Nie  udalo sie znalezc podanej wartosci
    {printf("Element nie istnieje, nie mozna usunac. "); return AVL_korzen;}
    
    //Tymcz wskazuje na wezel do usuniecia. Mozliwosci:
    // 1) Jest lisciem
    // 2) Ma jednego potomka
    // 3) Ma dwoch potomkow
    
    if(tymcz->prawy == NULL&&tymcz->lewy==NULL) //Jezeli wyszukany wezel jest lisciem
    {
        //Znaleziony wezel jest korzeniem drzewa
        if(rodzic == NULL)
        AVL_korzen=NULL;
        else 
        {
            if(rodzic->lewy==tymcz) //Jezeli znaleziony byl lewym, ustawiam wskaznik jego rodzica->lewy na null
            rodzic->lewy=NULL;
            else
            rodzic->prawy=NULL;
        }
        free(tymcz);
    }
    else
    if(tymcz->lewy == NULL || tymcz->prawy == NULL)
    {
        // Szukany element ma tylko jednego potomka
        if(tymcz->prawy==NULL)
            potomek = tymcz->lewy;
        else
            potomek= tymcz->prawy;
            
        if(rodzic == NULL) //jezeli brak rodzica usuwamy korzen
        AVL_korzen = potomek;
        else
        {
            //usuwamy galaz posiadajaca potomka i nie bedaca korzeniem
            if(czy_lewy)
            rodzic->lewy = potomek;
            else
            rodzic->prawy = potomek;
        }
        free(tymcz);
    }
    else
    {
        // Trzecia opcja: wyszukany wezel ma dwoje potomkow

        //Znajduje nastepnika: 
        
        //Tutaj musze przekonfigurowac liste. Musi ona wyszukiwac od miejsca gdzie usunieto nastepnika
        
        struct Glaz *nastepnik;
        struct Glaz *tymcz_nastepnik=tymcz->prawy;
        odkorzenia = push(tymcz,odkorzenia);
        //Jezeli tymczasowy nastepnik ma przynajmniej jednego lewego potomka, moge dodac tymczasowy nastepnik do listy
        //Wtedy od niego rozpoczna sie poszukiwania (W domysle szukam miejsca nastepnika)
        
        while(tymcz_nastepnik->lewy!=NULL)
        {
            nastepnik = tymcz_nastepnik;
            odkorzenia = push(nastepnik,odkorzenia);
            
            tymcz_nastepnik = tymcz_nastepnik->lewy;
        }
        
        
        nastepnik = tymcz_nastepnik;
        
        int klucz_nastepnika = nastepnik->klucz;
        struct Glaz *rodzic_nastepnika = odkorzenia->AVL_node;
        //Proces usuwania nastepnika. Bedzie on mial prawego lub 0 potomkow
        
        //Jezeli nastepnikiem jest pierwszy po prawej usuwanego wezla
        //if(tymcz_nastepnik->lewy==NULL)
        //rodzic_nastepnika = odkorzenia->stack_node->AVL_node;
        
        //printf("rodzic nastepnika: %d\n\n",rodzic_nastepnika->klucz);
        
        if(tymcz->prawy == nastepnik) //Jezeli nie musialem dlugo szukac nastepnika
        {
            if(nastepnik->prawy == NULL) //Nastepnik nie ma zadnych potomkow
            {free(nastepnik); rodzic_nastepnika->prawy = NULL;}
            else       // Szukany element ma tylko jednego potomka
            {rodzic_nastepnika->prawy = nastepnik->prawy; free(nastepnik);}}
        else //Jezeli nastepnik nie byl prawym dzieckiem usuwanego (czyli prawe dziecko usuwanego mialo jakies mniejsze dzieci)
            {
            if(nastepnik->prawy == NULL) //Nastepnik nie ma zadnych potomkow
            {free(nastepnik); rodzic_nastepnika->lewy = NULL;}
            else       // Szukany element ma tylko jednego potomka
            {rodzic_nastepnika->lewy = nastepnik->prawy; free(nastepnik);}}


        tymcz->klucz = klucz_nastepnika;
    }
      
    //rebalancing
    int poprzedni_wsp = 0;
    int obecny_wsp = 0;
    int zbalansowane = 0;
    
        //poprzedni_wsp = odkorzenia->AVL_node->wsp_zbalansowania;
        //odkorzenia->AVL_node->wsp_zbalansowania = obliczbalans(odkorzenia->AVL_node);
        //obecny_wsp = odkorzenia->AVL_node->wsp_zbalansowania;
         
        while(odkorzenia&&!zbalansowane)
        {
        
        odkorzenia->AVL_node->wsp_zbalansowania = obliczbalans(odkorzenia->AVL_node);
        obecny_wsp = odkorzenia->AVL_node->wsp_zbalansowania;
        
        if(abs(obecny_wsp)==1)    //W drodze do korzenia napotkalismy wezel, w ktorym nastapila zmiana wspolcznynnika z 0 na +/- 1
        {zbalansowane=1; break;}
        
        //Przy zmianie z +/- 1 na 0 podrozujemy dalej
        
        if(abs(obecny_wsp)==2) //Napotkano niezbalansowany wezel - rebalancing
        {
            
            struct Glaz *niezbalansowany = odkorzenia->AVL_node;
            if(odkorzenia->stack_node!=NULL) odkorzenia=odkorzenia->stack_node;
            struct Glaz *rodzic_niezbalansowanego = odkorzenia->AVL_node;
            struct Glaz *tymczasowy_pivot;
            
            
            if(obecny_wsp == 2)
            {
                    struct Glaz *wsk_prawy = niezbalansowany->prawy; 
                    poprzedni_wsp = wsk_prawy->wsp_zbalansowania;
                    
                    struct Glaz *wsp_dopoprawy = niezbalansowany->prawy;
                    
                    
                    if(wsk_prawy->wsp_zbalansowania == 1)
                    tymczasowy_pivot = rightleftrotation(niezbalansowany);
                    
                    if(wsk_prawy->wsp_zbalansowania == -1)
                    tymczasowy_pivot = leftrotation(niezbalansowany);  
                    
                    if(wsk_prawy->wsp_zbalansowania == 0)
                    {tymczasowy_pivot = leftrotation(niezbalansowany); zbalansowane = 1;}
                    
                    if(rodzic_niezbalansowanego == niezbalansowany)
                    AVL_korzen = tymczasowy_pivot;
                    else
                    {
                    if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                    rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                    else
                    rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                    wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
            }
            else
            {
                
                struct Glaz *lewy_niezbalansowanego = niezbalansowany->lewy;
                lewy_niezbalansowanego->wsp_zbalansowania = obliczbalans(lewy_niezbalansowanego);
                struct Glaz *wsp_dopoprawy = niezbalansowany->lewy;
                
                if(lewy_niezbalansowanego->wsp_zbalansowania == 1)
                tymczasowy_pivot = leftrightrotation(niezbalansowany);
                
                if(lewy_niezbalansowanego->wsp_zbalansowania == -1)
                tymczasowy_pivot = rightrotation(niezbalansowany);
                
                if(lewy_niezbalansowanego->wsp_zbalansowania == 0)
                {tymczasowy_pivot = rightrotation(niezbalansowany); zbalansowane = 1;}
                
                if(rodzic_niezbalansowanego == niezbalansowany)
                AVL_korzen = tymczasowy_pivot;
                else
                {
                if(tymczasowy_pivot->klucz > rodzic_niezbalansowanego->klucz)
                rodzic_niezbalansowanego->prawy = tymczasowy_pivot;
                else
                rodzic_niezbalansowanego->lewy = tymczasowy_pivot;}
                    
                wsp_dopoprawy->wsp_zbalansowania = obliczbalans(wsp_dopoprawy);
            }
        } 
        
        odkorzenia = odkorzenia->stack_node;
        }
    
    return AVL_korzen;
    
}
                */
    
