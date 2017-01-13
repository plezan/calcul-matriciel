#include <stdio.h>
#include <stdlib.h>

#define SAVE_PATH ".\\"
#define EXT ".matrice"

typedef struct matrices{
  unsigned int nb_ligne;
  unsigned int nb_colonne;
  int **data;
} matrice;

matrice newMat(unsigned int nb_ligne0,unsigned int nb_colonne0){
    unsigned int i,j;
    matrice m;
    m.nb_ligne = nb_ligne0;
    m.nb_colonne = nb_colonne0;
    m.data = (int**)malloc(m.nb_ligne*sizeof(int *));//aloue le nombre de lignes
    for(i=0;i<m.nb_ligne;++i){
        m.data[i] = (int *)malloc(m.nb_colonne*sizeof(int));//aloue le nombre de colones
        for(j=0;j<m.nb_colonne;++j){
            m.data[i][j]=m.nb_colonne*i+j+1;
            //printf("%d\n",m.data[i][j]);
        }
    }
    return m;
}

void initMat(matrice *m){
    int i,j;
    for(i=0;i<(*m).nb_ligne;i++){
        for(j=0;j<(*m).nb_colonne;j++){
            printf("Entrer la valeur en %d;%d : ",i,j);
            fflush(stdin);
            scanf("%d",&(*m).data[i][j]);
        }
    }
}

matrice loadMat(char name){

    FILE* sauvegarde = NULL;
    char path[255];
    sprintf(&path,"%s%c%s",SAVE_PATH,name,EXT);
    int i,j,l,c;

    sauvegarde = fopen(path,"r");

    fscanf(sauvegarde,"%d,%d\n",&l,&c);

    matrice m = newMat(l,c);

    for(i=0;i<m.nb_ligne;i++){
        for(j=0;j<m.nb_colonne;j++){
            fscanf(sauvegarde,"%d",&m.data[i][j]);
        }
    }
    fclose(sauvegarde);
    return m;
}

void printMat(matrice m){
    int i,j;
    for(i=0;i<m.nb_ligne;i++){
        for(j=0;j<m.nb_colonne;j++){
            printf(" %d ",m.data[i][j]);
        }
        printf("\n");
    }
}

void saveMat(matrice m,char name){
    FILE* sauvegarde = NULL;
    char path[255];
    sprintf(&path,"%s%c%s",SAVE_PATH,name,EXT);
    int i,j;
    sauvegarde = fopen(path,"w");
    fprintf(sauvegarde,"%d,%d\n",m.nb_ligne,m.nb_colonne);
    for(i=0;i<m.nb_ligne;i++){
        for(j=0;j<m.nb_colonne;j++){
            fprintf(sauvegarde,"%d\n",m.data[i][j]);
        }
    }
    fclose(sauvegarde);
}

matrice addMat(matrice a,matrice b){
    if(a.nb_colonne == b.nb_colonne && a.nb_ligne == b.nb_ligne){
        matrice m = newMat(a.nb_ligne,a.nb_colonne);
        int i,j;
        for(i=0;i<m.nb_ligne;i++){
            for(j=0;j<m.nb_colonne;j++){
                m.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return m;

    }
}

void scalMat(int scalaire,matrice *a){
    int i,j;
    for(i=0;i<(*a).nb_ligne;i++){
        for(j=0;j<(*a).nb_colonne;j++){
            (*a).data[i][j]=scalaire*(*a).data[i][j];
        }
    }
}

matrice multMat(matrice a,matrice b){
    if(a.nb_colonne == b.nb_ligne){
        matrice m = newMat(a.nb_ligne,b.nb_colonne);
        int i,j,k;
        for(i=0;i<m.nb_ligne;i++){
            for(j=0;j<m.nb_colonne;j++){
                m.data[i][j]=0;
                for (k=0;k<a.nb_colonne;k++)
                {
                    m.data[i][j]+=b.data[k][j]*a.data[i][k];
                }
            }
        }
        return m;

    }
}

int ask(char question[255]){
    int choix;
    printf("%s",question);
    scanf("%d",&choix);

    return choix;
}

int main()
{
    matrice a,b;
    int choix = 0;
    if(ask("Voulez vous charger une matrice 'A' existante ? 1 = Oui\n")==1){
         a=loadMat('a');
         printf("chargement de la matrice A\n");
    }else{
        a=newMat(3,3);
        printf("Creation de la matrice A\n");
        initMat(&a);
    }

    if(ask("Voulez vous charger une matrice 'B' existante ? 1 = Oui\n")==1){
         b=loadMat('b');
         printf("chargement de la matrice B\n");
    }else{
        b=newMat(3,3);
        printf("Creation de la matrice B\n");
        initMat(&b);
    }

    /*matrice b=newMat(3,3);
    initMat(&b);
    matrice a=loadMat('a');
    printf("Matrice A :\n");
    printMat(a);

    printf("Matrice B:\n");
    printMat(b);*/
    //saveMat(a,'a');
    matrice m = multMat(a,b);
    printf("A x B =\n");
    printMat(m);

    m = addMat(a,b);
    printf("A + B =\n");
    printMat(m);

    scalMat(2,&m);
    printf("2 * A =\n");
    printMat(m);


    return 0;
}
