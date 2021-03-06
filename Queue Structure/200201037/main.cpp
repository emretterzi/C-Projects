#include <graphics.h>
#include <stdlib.h>
#include <String.h>
#define sinir_belirleme 80
#include <stdio.h>

char katar[sinir_belirleme];
typedef struct n{
    struct n *child[sinir_belirleme];
    int strtindx;
    int indxend;
    int indx;
}node;

void edge_Yapma(node *n){
    int say1= strlen(katar);
    for(int a = 0; a < say1; a++){
        n->child[a] = (node *) malloc(sizeof(node));
        n->child[a]->strtindx = -1;
        n->child[a]->indxend = -2;
        n->child[a]->indx =  0;
    }
}


int node_Sorgulama(int x, int y, int z);



void node_Alt(node *root, int i){
    int t = 0;
    int say2 = strlen(katar);
    int son[10];
    int basla[10];
    int bas[10];

    for(int k = i+1; k < say2; k++){
        if(katar[i] == katar[k]){
            int x = i+1;
            int y = k+1;
            bas[t] = node_Sorgulama(x, y, k);
            son[t] = k + node_Sorgulama(x, y, k) - i;
            basla[t] = k;
            t++;
        }
    }

    for(int j = 0; j < t; j++){
        if(bas[0] - i > son[j] - basla[j]){
            root->child[i]->strtindx = i;
            root->child[i]->indxend = i + son[j] - basla[j];
            root->child[i]->indx =  -1;
            break;
        }
        else{
            root->child[i]->strtindx = i;
            root->child[i]->indxend = bas[0];
            root->child[i]->indx =  -1;
        }
    }

    for(int k = 0; k != i && k < say2; k++){
        if(root->child[k]->indx == -1){
            if(katar[root->child[k]->strtindx] == katar[root->child[i]->strtindx]){
                root->child[i]->strtindx = -1;
                root->child[i]->indxend = -2;
                root->child[i]->indx =  0;
            }
        }
    }
}
void node_Alt2(node *root);
void node_ic(node *root);

void node_ic2(node *root, node *n);

void graph(node *n);

int main(){


		char str[sinir_belirleme];
		printf("suffix tree olusturulmasi istenen kelimeyi giriniz: ");
		scanf("%s",str);
		int  uzunluk= strlen(str);
		char Suff[uzunluk][uzunluk+1];
		char prestr[uzunluk][uzunluk+1];

		for(int i = 0; i < uzunluk; i++){
			int a = 0;
			for(int j = i; j < uzunluk; j++){
				Suff[i][a] = str[j];
				a++;
			}
			Suff[i][a] = '\0';
		}

		for(int i = 0; i < uzunluk; i++){
			int a = 0;
			for(int j = 0; j <= i; j++){
				prestr[i][a] = str[j];
				a++;
			}
			prestr[i][a] = '\0';
		}

		int sonuc = 0;

		for(int i = 1; i < uzunluk; i++){
			for(int j = 0; j < uzunluk-1; j++){
				if(strcmp(Suff[i],prestr[j]) == 0){
					sonuc = 1;
					break;
				}
			}
		}
		if(sonuc == 0)
			printf("%s katari icin Suffix agaci olusturulabilir.\n\n",str);
		else
			printf("%s katari icin Suffix agaci olusturulamaz.\n\n",str);



	if(sonuc == 0){

    int length = strlen(str);
    FILE *file = fopen("katar.txt", "w");
    fprintf(file,"%s",str);
    fclose(file);

    for(int i = 0; i < length; i++)
        katar[i] = str[i];

    node *root = (node *) malloc(sizeof(node));

    edge_Yapma(root);

    for(int i = 0; i < length; i++){
        int a = 0;
        for(int j = 0; j < length; j++){
            if(i == j)
                continue;
            if(str[i] == str[j])
                a = 1;
        }
        if(a == 0){
            root->child[i]->strtindx = i;
            root->child[i]->indxend = length-1;
            root->child[i]->indx = i;
            root->child[i]->child[0] = NULL;
            continue;
        }

        node_Alt(root,i);

        if(root->child[i]->indx == -1)
            node_ic(root->child[i]);

        if(root->child[i]->indx == -1){
            node_Alt2(root->child[i]);
            node *n = root->child[i];
            while(1){
                for(int j = 0; j < length; j++){
                    if(n->child[j]->indx == -1){
                        node_ic2(n->child[j],root->child[i]);
                        node_Alt2(n);
                    }
                }
            break;
            }
        }
    }

    int tut = 0;
    int durum = 0;
    int strtindx = 0;
    int indxend = 0;
    int durum2 = 0;
    int sayac = 0;
    for(int i = 0; i < length; i++){
        sayac = 0;
        if(root->child[i]->indx == -1){
            durum = 1;
            node *n = root->child[i];
            for(int j = 0; j < length; j++){
                if(n->child[j]->indx == -1){
                    durum2 = 1;
                    if(n->child[j]->indxend - root->child[i]->strtindx + 1 > indxend-strtindx){
                    	sayac = 0;
                        strtindx = n->child[j]->strtindx - (root->child[i]->indxend - root->child[i]->strtindx + 1);
                        indxend = n->child[j]->indxend;
                        for(int k = 0; k < length; k++){
                            if(n->child[j]->child[k]->indxend != -2){
                                sayac++;
                            }
                        }
                        tut = sayac;
                    }
                }
            }
            if(durum2 == 0){
            	sayac = 0;
                if(n->indxend - n->strtindx + 1 > indxend - strtindx){
                    strtindx = n->strtindx;
                    indxend= n->indxend;
                    for(int j = 0; j < length; j++){
                        if(n->child[j]->indxend != -2){
                            sayac++;
                        }
                    }
                    tut = sayac;
                }
            }
        }
    }

    if(durum == 0)
        printf("tekrar eden alt katar yok\n\n");
    else{
        printf("En uzun tekrar eden alt katar: ");
        for(int i = strtindx; i <= indxend; i++)
            printf("%c",str[i]);
        printf("\n%d kere tekrar eder.\n\n",tut);


        strtindx = 0;
        indxend = 0;
        sayac = 0;
        int indiz[10];
        int indiz1[10];
        int adet = 0;
        int indiz2[10];
        int sayac2 = 0;
        for(int i = 0; i < length; i++){
            sayac = 0;
            if(root->child[i]->indx == -1){
                node *tekrar = root->child[i];
                for(int j = 0; j < length; j++){
                    if(tekrar->child[j]->indxend != -2){
                        if(tekrar->child[j]->indx == -1){
                            for(int k = 0; k < length; k++){
                                if(tekrar->child[j]->child[k]->indxend != -2)
                                    sayac++;
                            }
                        }
                        else
                            sayac++;
                    }
                    if(sayac > sayac2){
                        sayac2 = sayac;
                        strtindx = root->child[i]->strtindx;
                        indxend = root->child[i]->indxend;
                    }

                }
                sayac = 0;
                for(int j = 0; j < length; j++){

                    if(tekrar->child[j]->indxend != -2){
                        if(tekrar->child[j]->indx == -1){
                            for(int k = 0; k < length; k++){
                                if(tekrar->child[j]->child[k]->indxend != -2)
                                    sayac++;
                            }
                        }
                        else
                            sayac++;
                    }
                    if(sayac == sayac2 && sayac2 > 0 && sayac > 0){
                        indiz[adet] = root->child[i]->strtindx;
                        indiz1[adet] = root->child[i]->indxend;
                        indiz2[adet] = sayac;
                        adet++;
                        break;
                    }
                }
            }
        }

        printf("En cok tekrar eden alt katar: ");

        for(int i = 0; i < adet; i++){
            if(indiz2[i] == sayac2){
                for(int j = indiz[i]; j <= indiz1[i]; j++)
                    printf("%c",str[j]);
                printf(", ");
            }
        }
        printf("\n%d kere tekrar eder.\n",sayac2);

    }

    char aranan[sinir_belirleme];
    printf("Aramak isteginiz alt katari giriniz: ");
    scanf("%s",aranan);
    char cdiz[strlen(aranan)];
    int sorgu = 0;
    int sayac3 = 0;
    int dint[length];
    int ara1= 0;
    for(int i = 0; i <= length - strlen(aranan); i++){
        int ara2 = 0;
        for(int j = i; j < i + strlen(aranan); j++){
            cdiz[ara2] = str[j];
            ara2++;
        }
        cdiz[ara2] = '\0';
        if(strcmp(aranan,cdiz) == 0){
            sorgu = 1;
            sayac3++;
            dint[ara1] = i;
            ara1++;
        }
    }

    if(sorgu == 0)
        printf("%s suffix tree de bulunmamaktadir.\n\n",aranan);
    else{
        printf("%s in ilk gectigi yer: %d\n",aranan,dint[0]);
        printf("%d kere tekrar eder.\n\n",sayac3);
    }
    graph(root);

}
	remove("katar.txt");
    return 0;
}

int node_Sorgulama(int x, int y, int z){
    if(x == z)
        return x-1;
    if(katar[x] == katar[y])
        return node_Sorgulama(x+1, y+1, z);
    else
        return x-1;
}

void node_Alt2(node *root){
    int say3 = strlen(katar);
    int son[10];
    int basla[10];
    int bas[10];

    for(int i = 0; i < say3; i++){
        int say4 = 0;
        if(root->child[i]->indxend != -2){
            for(int j = i+1; j < say3; j++){
                if(root->child[j]->indxend != -2){
                    if(katar[i] == katar[j]){
                        int x = i+1;
                        int y = j+1;
                        bas[say4] = node_Sorgulama(x, y, j);
                        son[say4] = j + node_Sorgulama(x, y, j) - i;
                        basla[say4] = j;
                        say4++;
                    }
                }
            }
        }

        for(int j = 0; j < say4; j++){
        if(bas[0] - i > son[j] - basla[j]){
            root->child[i]->strtindx = i;
            root->child[i]->indxend = i + son[j] - basla[j];
            root->child[i]->indx =  -1;
            break;
        }
        else{
            root->child[i]->strtindx = i;
            root->child[i]->indxend = bas[0];
            root->child[i]->indx =  -1;
        }
    }
        for(int k = 0; k != i && k < say3; k++){
            if(root->child[k]->indx == -1){
                if(katar[root->child[k]->strtindx] == katar[root->child[i]->strtindx]){
                    root->child[i]->strtindx = -1;
                    root->child[i]->indxend = -2;
                    root->child[i]->indx =  0;
                }
            }
        }
    }
}

void node_ic(node *root){
    int say5 = strlen(katar);
    edge_Yapma(root);
    node *tekrar = root;
    for(int j = root->strtindx; j < say5; j++){
        if(katar[tekrar->strtindx] == katar[j]){
            int a = j + tekrar->indxend - tekrar->strtindx + 1;
            tekrar->child[a]->strtindx = j + tekrar->indxend - tekrar->strtindx +1;
            tekrar->child[a]->indxend = say5-1;
            tekrar->child[a]->indx =  j;
        }
    }
}

void node_ic2(node *root, node *n){
    int say6 = strlen(katar);
    int yer = n->indxend - n->strtindx + 1;
    edge_Yapma(root);
    node *tekrar = root;
    for(int j = root->strtindx; j < say6; j++){
        if(katar[tekrar->strtindx] == katar[j]){
            if(katar[tekrar->indxend] == katar[j + tekrar->indxend-tekrar->strtindx]
			&& katar[tekrar->strtindx - 1] == katar[j - 1]){
                int yer2 = j + tekrar->indxend - tekrar->strtindx + 1;
                tekrar->child[yer2]->strtindx = j + tekrar->indxend - tekrar->strtindx +1;
                tekrar->child[yer2]->indxend = say6-1;
                tekrar->child[yer2]->indx =  j - yer;
            }
        }
    }
}




void graph(node *n){

	initwindow(1550,1000);

	setbkcolor(3);
	 cleardevice();



	int say7 = strlen(katar);
	int kor = 1100;
	pieslice(800,20,0,0,10);
	int k = 0;
	for(int i = 0; i < say7; i++){
		if(n->child[i]->indxend != -2){
			line(800,20,kor-250*k,200);
			pieslice(kor-250*k,200,0,0,10);
			int y = (kor-250*k - 800)/4;
			setcolor(0);
			char z[say7+1];
			int p = 0;
			for(int t = n->child[i]->strtindx; t <= n->child[i]->indxend; t++){
				z[p] = katar[t];
				p++;
			}
			z[p] = '\0';

			outtextxy(kor-260*k-y,150,z);
			setcolor(15);
			if(n->child[i]->indx == -1){
				node *tekrar = n->child[i];

				pieslice(kor-250*k,200,0,0,10);

				int m = 0;
				for(int j = 0; j < say7; j++){
					if(tekrar->child[j]->indxend != -2){
						line(kor-250*k,200,kor+50-250*k-100*m,400);
						pieslice(kor+50-250*k-100*m,400,0,0,10);

						int y = (kor+50-250*k-100*m - (kor-250*k))/2;
						setcolor(0);
						char z[2];
						int p = 0;
						for(int t = tekrar->child[j]->strtindx; t <= tekrar->child[j]->indxend; t++){
							z[0] = katar[t];
							z[1] = '\0';

							outtextxy(kor+50-250*k-100*m-y,275+20*p,z);
							p++;
						}
						setcolor(15);
						if(tekrar->child[j]->indx == -1){
							pieslice(kor+50-250*k-100*m,400,0,0,10);
							node *root = tekrar->child[j];
							int a = 0;
							for(int l = 0; l < say7; l++){
								if(root->child[l]->indxend != -2){
									line(kor+50-250*k-100*m,400,1200-250*k-100*m-70*a,600);


									int y = (1200-250*k-100*m-70*a - (kor+50-250*k-100*m))/2;
									setcolor(0);

									int p = 0;
									for(int t = root->child[l]->strtindx; t <= root->child[l]->indxend; t++){


										p++;
									}
									setcolor(15);



									setcolor(15);
									pieslice(1200-250*k-100*m-70*a,600,0,0,5);
									a++;

								}
							}
						}
						else{
							char r[say7];





							setcolor(15);
						}
						m++;
					}
				}
			}
			else{
				char z[say7];



				setcolor(15);
			}
			k++;
		}
	}


	getch();
	closegraph();
}

