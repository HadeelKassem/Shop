
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int code;
  char libelle[20];
  float prix;
  int quantite;
} articles;
typedef struct {
  int item_code;
  char item_libelle[20];
  float item_prix;
  int item_quantite;
} items;
int test1(articles **element, int n, int code, int ignore_index) {
  int a = 0;
  for (int i = 0; i < n; i++) {
    if (i == ignore_index) continue;
    if ((*element)[i].code == code) {  a++; }    } 
  if (a >= 1) return 1;
  else return 0;}
int test2(articles **element, int n, char *libelle, int ignore_index) {
  int a = 0;
  for (int i = 0; i < n; i++) {  if (i == ignore_index) continue;
    if (strcmp((*element)[i].libelle, libelle) == 0) {
      a++;
    }
  }
  if (a >= 1)
    return 1;
  else
    return 0;
}
void printarticle(articles *element, int a) {
  for (int i = 0; i < a; i++)
    printf("%s :\n code:%d \n prix:%f \n quantite:%d\n", element[i].libelle,
           element[i].code, element[i].prix, element[i].quantite);}
 void articlestock(articles **element, int *nb_articles) {
  int n, b = 0, a;
 printf("Le stock est vide,Donner le nb d'aricles que vous souhaiter stocker:\n ");
  scanf("%d", &n);
  *element = (articles *)malloc(n * sizeof(articles));
  for (int i = 0; i < n; i++) {
    do {   b = 0;
      a = i + 1;
      printf("Entrez le code de l'article %d :", i + 1);
      scanf("%d", &(*element)[i].code);
      b = test1(element, a, (*element)[i].code, i);
      if (b == 1) {
        printf("Cette code est deja utilise!\n");}            } while (b == 1);
     do {  b = 0;
      a = i + 1;
      printf("Entrez la libelle de l'article %d :", i + 1);
      scanf("%s", (*element)[i].libelle);
      b = test2(element, a, (*element)[i].libelle, i);
      if (b == 1) printf("Cette libelle est deja utilise!!\n");  } while (b == 1);
    printf("Entrez le prix de l'article %d :", i + 1);
    scanf("%f", &(*element)[i].prix);
    do { printf("Donner la quantitee dissponible de  l'article %d :", i + 1);
      scanf("%d", &(*element)[i].quantite);
      if ((*element)[i].quantite <= 0) ("Donner une quantite valide!!");
    } while ((*element)[i].quantite <= 0) ; }
  *nb_articles = n;
  for (int i = 0; i < n; i++)
    printf("%s :\n code:%d \n prix:%f \n quantite:%d\n", (*element)[i].libelle,
           (*element)[i].code, (*element)[i].prix, (*element)[i].quantite);}
 void buyfromstock(articles **element, int *nb_articles, items **it) {
  int b = 0, answer, items_nb = 1,a ;
  *it = (items *)malloc(items_nb * sizeof(items));
  float total_price = 0;
  do {  do {  a = -1;
    printf("Donner le code de l'article que vous voulez acheter:\n");
      scanf("%d", &(*it)[b].item_code);
     for (int i = 0; i < *nb_articles; i++) {
       if ((*it)[b].item_code == (*element)[i].code) {    a = i;
                                                                                            if ((*element)[i].quantite == 0) {
                                                                                             printf("Cette article n'est plus disponible\n");
                                                                                             a = -1; }
 else {strcpy((*it)[b].item_libelle, (*element)[a].libelle);
            (*it)[b].item_prix = (*element)[a].prix ; }break;}}
        if (a == -1) { printf("Ce code n'est pas valide!!\n");}
     } while (a == -1);
     do { printf("Donner la quantite que vous voulez acheter\n");
      scanf("%d", &(*it)[b].item_quantite);
      if ((*it)[b].item_quantite > (*element)[a].quantite ||
          (*it)[b].item_quantite < 0)
        printf("Cette quantite n'est pas valide!!\n");
    } while ((*it)[b].item_quantite > (*element)[a].quantite || (*it)[b].item_quantite < 0);
 
    (*element)[a].quantite = (*element)[a].quantite - (*it)[b].item_quantite;
    total_price = total_price + (*element)[a].prix * (*it)[b].item_quantite;
 
    printf("Voulez-vous acheter un autre article?\n 1.Oui  2.Non\n");
    scanf("%d", &answer);
    if (answer == 2) answer = 0;
    if (answer == 1) {
      int r = 0;
      for (int i = 0; i < *nb_articles; i++) {
        if ((*element)[i].quantite == 0) r++;
      }
      if (r == *nb_articles) {
        printf("Desolee, il n'y a plus d'articles disponibles");
        answer = 0;
      }
    }
 
    b++;
    items_nb++;
    *it = realloc(*it, items_nb * sizeof(items));
 
  } while (answer != 0);
  printf("\n");
  printf(
      "\t Fracture:\n\t==========\nTVA:10%%\n Article  quantite   "
      "prix-par-unite   article-total\n");
 
  printf("\n");
  for (int i = 0; i < b; i++) {
    printf(" \t%s \t%d \t%f \t%f \n ", (*it)[i].item_libelle,
           (*it)[i].item_quantite, (*it)[i].item_prix,
           (*it)[i].item_prix * (*it)[i].item_quantite);
  }
  int sales = 0;
 
  printf("\n");
  printf("* sales 20%% sur une fracture plus que 500$\n");
  if (total_price > 500) {
    sales = total_price * 0.2;
  }
  printf("Prix total:  %f\n", total_price - sales + total_price / 10);
  printf("\n\n");
}
 
void reset(articles **element, int *nb_articles) {
  free(*element);
  *nb_articles = 0;
}
void removefct(articles **element, int *nb_articles) {
  int index, i = 0, a = 0;
  printf("Donner le code de l'element que vous voulez annuler\n");
  scanf("%d", &index);
  for (i = 0; i < *nb_articles; i++) {
    if ((*element)[i].code == index) {
      for (int j = i; j < *nb_articles - 1; j++) {
        (*element)[j] = (*element)[j + 1];
      }
      a++;
      break;
    }
  }
  if (a > 0) {
    *nb_articles = *nb_articles - 1;
    *element = realloc(*element, (*nb_articles) * sizeof(articles));
  }
}
void add(articles **element, int *nb_articles) {
  int a, c, b;
  int i = *nb_articles;
  do {
    *nb_articles += 1;
    *element = realloc(*element, (*nb_articles) * sizeof(articles));
    do {
      b = 0;
      c = i + 1;
      printf("Entrez le code de l'article %d :", i + 1);
      scanf("%d", &(*element)[i].code);
      ;
      b = test1(element, c, (*element)[i].code, i);
      if (b == 1) printf("Cette code est deja utilise!\n");
 
    } while (b == 1);
 
    do {
      b = 0;
      c = i + 1;
      printf("Entrez la libelle de l'article %d :", i + 1);
      scanf("%s", (*element)[i].libelle);
      b = test2(element, c, (*element)[i].libelle, i);
      if (b == 1) printf("Cette libelle est deja utiliser!!");
    } while (b == 1);
    printf("Entrez le prix de l'article:\n");
    scanf("%f", &(*element)[i].prix);
    do {
      printf("Donner la quantitee dissponible de  l'article %d :", i + 1);
      scanf("%d", &(*element)[i].quantite);
      if ((*element)[i].quantite <= 0) printf("Donner une quantite valide!!");
    } while ((*element)[i].quantite <= 0);
    printf("Voulez-vous en stocker un autre?\n 1. Oui 2. Non \n");
    scanf("%d", &a);
    i++;
 
  } while (a == 1);
}
 
void modify(articles **element, int *nb_articles) {
  int index, i = 0, a = 0, reponse = 0, code, quantity, b, c, t;
  char libelle[20];
  do {
    t = 0;
    printf("Donner le  code de l'element que vous voulez changer\n");
    scanf("%d", &index);
 
    for (i = 0; i < *nb_articles; i++) {
      if ((*element)[i].code == index) {
        t++;
      }
    }
 
    if (t == 0) {
      printf("Donner un code valid!\n");
    }
  } while (t == 0);
 
  for (i = 0; i < *nb_articles; i++) {
    do {
      if ((*element)[i].code == index) {
        printf(
            "Que voulez -vous changer?\n 1.code 2.prix 3.quantite 4.libelle");
        scanf("%d", &a);
        switch (a) {
          case 1:
            do {
              printf("Donner le nouveau code:");
              scanf("%d", &code);
              b = test1(element, *nb_articles, code, i);
 
              if (b == 1) printf("Ce code est deja utiliser!!");
            } while (b == 1);
            (*element)[i].code = code;
            break;
          case 2:
            printf("Donner le nouveau prix:");
            float price;
            scanf("%f", &price);
            (*element)[i].prix = price;
            break;
          case 3:
            do {
              printf("Donner la nouvelle quantite:");
              scanf("%d", &quantity);
 
              if (quantity <= 0) printf("Cette quantity n'est pas valide!!\n");
            } while (quantity <= 0);
            (*element)[i].quantite = quantity;
            break;
          case 4:
            do {
              printf("Donner la nouvelle libelle:");
 
              scanf("%s", libelle);
              c = test2(element, *nb_articles, libelle, i);
              if (c == 1) printf("Cette libelle est deja utiliser!!");
            } while (c == 1);
            strcpy((*element)[i].libelle, libelle);
 
            break;
          default:
            printf("Ce n'est pas  un choix possible!!\n");
            reponse = 1;
            break;
        }
      }
    } while (reponse == 1);
  }
}
 
void owner_mode_page(articles **element, int *nb_articles) {
  int i, options, a, r = 0;
  a = *nb_articles;
  printarticle(*element, a);
  printf(
      "Que faire?\n 1.Stocker un nouveau article\n 2.Annuler un article\n "
      "3.Changer les info d'un article\n 4.Formatter \n");
  scanf("%d", &options);
  switch (options) {
    case 1:
      add(element, nb_articles);
      break;
    case 2:
      removefct(element, nb_articles);
      break;
    case 3:
      modify(element, nb_articles);
      break;
    case 4:
      reset(element, nb_articles);
      break;
    default:
      printf("Ce n'est pas une operation valide!!\n");
      break;
  }
}
 
int main() {
  int home_page = 0;
  int r = 0, n = 0, t = 0, nb_articles = 0, f = 0;
  articles *element = NULL;
  items *it = NULL;
  do {
    if (nb_articles != 0) {
      f = 0; 
      for (int i = 0; i < nb_articles; i++) {
        if (element[i].quantite == 0) f++;
      }
    }
 
    do {
      printf("CLIENT ou COMMERCANT??\n 1.Client    2.Commercant\n");
      scanf("%d", &n);
      if (n == 1) {
        printf("Bienvenue au HK-MARKETS!!\n");
        if (nb_articles == 0 || f == nb_articles)
          printf("Desole pas des articles disponibles dans le stock!\n");
        else {
          printarticle(element, nb_articles);
          buyfromstock(&element, &nb_articles, &it);
        }
      } else if (n == 2) {
        if (nb_articles == 0)
          articlestock(&element, &nb_articles);
        else
          owner_mode_page(&element, &nb_articles);
      } else {
        r = 1;
        printf("Veuillex choisir un mode valid!\n");
      }
    } while (r == 1);
    printf("Retourner a la page d'accueil?\n  1.Oui 2.Non\n");
    scanf("%d", &t);
  } while (t == 1);
  return 0;
}


