#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <string.h>

struct alignement
{
  char * x;
  char * y;
};


/* =============================================================== */
char * readtextfile(char * filename)
  /* Retourne le contenu du fichier texte filename */
/* =============================================================== */
{
  struct stat monstat;
  int N;
  char * text = NULL;
  FILE *fd = NULL;

  N = stat(filename, &monstat);
  if (N == -1)
  {
    fprintf(stderr, "error : bad file %s\n", filename);
    exit(0);
  }
  N = monstat.st_size;
  text = (char *)malloc(N+1);
  if (text == NULL)
  {   fprintf(stderr,"readtextfile() : malloc failed for text\n");
      exit(0);
  }
  fd = fopen(filename,"r");
  if (!fd)
  {
    fprintf(stderr, "readtextfile: can't open file %s\n", filename);
    exit(0);
  }
  
  fread(text, sizeof(char), N, fd);
  if((N>0) && (text[N-1] == '\n') ) text[N-1] = '\0';
  else text[N-1] = '\0';
  fclose(fd);
  return text;
}

/* =============================================================== */
int Imax(int a, int b)
/* Retourne  le maximum de a et b                                  */
/* =============================================================== */
{
  if (a < b) return b;
  else return a;	       
}

/* =============================================================== */
int Imin2(int a, int b)
/* Retourne  le minimum de a et b                                  */
/* =============================================================== */
{
  if (a < b) return a;
  else return b;	       
}

/* =============================================================== */
int Imin3(int a, int b, int c)
/* Retourne  le minimum de a, b et c                               */
/* =============================================================== */
{
  return Imin2(Imin2(a,b),c);
}

/* =============================================================== */
void retourne(char *c)
/* Retourner la chaîne de caractère c                              */
/* =============================================================== */
{
  char tmp;
  int m, j, i;
  m = strlen(c);
  j = m/2;
  for(i = 0; i < j; i++ ){
    tmp = c[i];
    c[i] = c[m-i-1];
    c[m-i-1] = tmp;
  }
}
/* =============================================================== */
void afficheSeparateurHorizontal(int nbcar)
/* =============================================================== */
{
  int i;
  printf("|-");
  for(i=0; i < nbcar; i++)
    printf("-");
  printf("-|-");
  for(i=0; i < nbcar; i++)
    printf("-");
  printf("-|\n");
}


/* =============================================================== */
void affiche(char* texte1, char* texte2, int nbcar)
  /* Affiche simultanément texte1 et texte 2 en positionnnant nbcar  
     caractères sur chaque ligne. */
/* =============================================================== */
{
  int i, l1, l2, l;
  
  char *t1,*t2;
  
  char out[512];
  
  l1 = strlen(texte1);
  l2 = strlen(texte2);

  t1 = (char*) malloc(sizeof(char) * (nbcar + 1));
  t2 = (char*)malloc(sizeof(char) * (nbcar + 1));

  l = Imax(l1, l2);
  afficheSeparateurHorizontal(nbcar);
  for(i = 0; i < l; i+= nbcar){
    if (i < l1) {
      strncpy(t1, &(texte1[i]), nbcar);
      t1[nbcar] = '\0';
    } else t1[0] = '\0';
    if (i < l2) {
      strncpy(t2, &(texte2[i]),nbcar);
      t2[nbcar] = '\0';
    } else t2[0] = '\0';
    
    sprintf(out, "| %c-%ds | %c-%ds |\n",'%', nbcar, '%', nbcar);
    printf(out, t1,t2);
  }
  afficheSeparateurHorizontal(nbcar);
  free(t1);
  free(t2);
}

/* =============================================================== */
void affiche2(char* texte1, char* texte2, int nbcar)
  /* idem affiche, mais avec un formattage différent
/* =============================================================== */
{

  int i, l1, l2, l;
  
  char *t1,*t2;
  
  char out[512];
  
  l1 = strlen(texte1);
  l2 = strlen(texte2);

  t1 = (char*) malloc(sizeof(char) * (nbcar + 1));
  t2 = (char*)malloc(sizeof(char) * (nbcar + 1));

  l = Imax(l1, l2);

  for(i = 0; i < l; i+= nbcar){
    if (i < l1) {
      strncpy(t1, &(texte1[i]), nbcar);
      t1[nbcar] = '\0';
    } else t1[0] = '\0';
    if (i < l2) {
      strncpy(t2, &(texte2[i]),nbcar);
      t2[nbcar] = '\0';
    } else t2[0] = '\0';
    
    sprintf(out, "x: %c-%ds \ny: %c-%ds\n",'%', nbcar, '%', nbcar);
    printf(out, t1,t2);

  }
  free(t1);
  free(t2);
}

/* =============================================================== */
int **lev(char *X, char *Y)
/* Retourne une matrice T de taille (|X|+1)*(|Y|+1) telle que T[i][j]
   d¨¦signe le score d¡¯un alignement optimal entre Xi et Yj. 
   C'est ¨¤ dire le dernier ¨¦l¨¦ment de la matrice donne le score 
   d'un alignement optimal entre X et Y
   R¨¦ponse de la question 1                                        */
/* =============================================================== */
{
    int m = strlen(X), n = strlen(Y);
    int **T = NULL;
	int i, j;
	int sub;
    T = (int **)malloc((m + 1) * sizeof(int *));
    
    T[0] = (int *)malloc((n + 1) * sizeof(int));
    T[0][0] = 0;
    for(i = 1; i <= m; i++)
    {
		T[i] = (int *)malloc((n + 1) * sizeof(int));
		T[i][0] = 1 + T[i - 1][0];
    }
    for(j = 1; j <= n; j++)
		T[0][j] = 1 + T[0][j - 1];
    for(i = 1; i <= m; i++)
    {
		for(j = 1; j <= n; j++)
		{
			if(X[i - 1] == Y[j - 1])
				sub = 0;
			else sub = 1;
			T[i][j] = Imin3(T[i][j - 1] + 1, T[i - 1][j - 1] + sub, T[i - 1][j] + 1);
		}
    }
    return T;
}

/* =============================================================== */
char **findAlignOpt(int **T, char *text1, char *text2)
/* Retourne un alignement optimal de text1 et text2 en donnant la 
   matrice T obtenue par la fonction lev()
   R¨¦ponse da la question 2                                        */
/* =============================================================== */
{
	int i, j, len1, len2, index;
	char *align[2];
	char **alignReal;
	len1 = strlen(text1);
	len2 = strlen(text2);
	
	align[0] = (char *)malloc((len1 + len2) * sizeof(char));
	align[1] = (char *)malloc((len1 + len2) * sizeof(char));
	
	alignReal = (char **)malloc(2 * sizeof(char *));

	i = len1;
	j = len2;
	index = len1 + len2 - 1;
	align[0][index] = '\0';
	align[1][index] = '\0';
	
	while(i > 0 || j > 0)
	{
		index--;
		
		if(i > 0 && T[i][j] == T[i - 1][j] + 1)
		{
			align[0][index] = text1[i - 1];
			align[1][index] = '_';
			i--;
		}
		else if(j > 0 && T[i][j] == T[i][j - 1] + 1)
		{
			align[0][index] = '_';
			align[1][index] = text2[j - 1];
			j--;
		}
		else
		{
			align[0][index] = text1[i - 1];
			align[1][index] = text2[j - 1];
			i--;
			j--;
		}
	}
	
	alignReal[0] = (char *)malloc((len1 + len2 - index) * sizeof(char));
	alignReal[1] = (char *)malloc((len1 + len2 - index) * sizeof(char));
	strncpy(alignReal[0], align[0] + index, len1 + len2 - index);
	strncpy(alignReal[1], align[1] + index, len1 + len2 - index);
	free(align[0]);
	free(align[1]);
	return alignReal;
}

/* =============================================================== */
char **separeParas(char *text, int *nbPara)
/* Etant donn¨¦ un texte avec n paragraphes, separe ces n paragraphes
   et sauvegarde chaque paragraphe dans chaque ligne d'un tableau. 
   Notant que l'on agnore des symbols "\n" au debut du texte
   Une fonction interm¨¦diaire pour la question 4                   */
/* =============================================================== */
{
	char **paras;
	int nbParaTempo = 0;
	int i;
	int k, m = 0;
	int espConse = 0;
	for(i = 0; text[i] != '\0'; i++)
	{
		if(i == 0)
		{
			while(text[i] == '\n')
				i++;
		}
		if(text[i] == '\n' || text[i + 1] == '\0')
		{
			nbParaTempo++;
			while(text[i + 1] == '\n')
			{
				i++;
			}
		}
	}

	*nbPara = nbParaTempo;
	paras = (char **)malloc(nbParaTempo * sizeof(char *));
	
	k = 0;
	for(i = 0; text[i] != '\0'; i++)
	{
		if(text[i] == '\t')
			text[i] = ' ';
		/*N¨¦glige des symbols '\n' au d¨¦but du texte*/
		if(i == 0)
		{
			while(text[i] == '\n')
			{
				i++;
			}
			m = i;
		}
		espConse = 0;
		if(text[i] == '\n' || text[i + 1] == '\0')
		{
			if(k == *nbPara - 1)
			{
				if(text[i] != '\n')
					i++;
				paras[k] = (char *)malloc((i + 1 - m));
				strncpy(paras[k], text + m, i - m);
				paras[k][i - m] = '\0';
				return paras;
			}
			/*S'il y a plusieur symbols '\n' cons¨¦cutivement, on les traite comme un seul symbol*/
			while(text[i + 1] == '\n')
			{
				i++;
				espConse++;
			}
			paras[k] = (char *)malloc((i + 1 - m - espConse));
			strncpy(paras[k], text + m, i - m - espConse);
			paras[k][i - m - espConse] = '\0';
			k++;
			m = i + 1;
		}
	}
	return paras;
}

/* =============================================================== */
int **scoreEntreParas(char **paras1, char **paras2, int nbPara1, int nbPara2)
/* Retourne une matrice "alignParas" telle que alignParas[i][j] est
   le score d'un alignement optimal entre le (i+1)¨¨me paragraphe 
   de text1 et le (j+1)¨¨me paragraphe de text2
   Une fonction interm¨¦diaire pour la question 4                   */
/* =============================================================== */
{
	int **scoreParas;
	int i, j;
	
	scoreParas = (int **)malloc(nbPara1 * sizeof(int *));
	
	for(i = 0; i < nbPara1; i++)
	{
		scoreParas[i] = (int *)malloc(nbPara2 * sizeof(int));
		for(j = 0; j < nbPara2; j++)
		{
			scoreParas[i][j] = lev(paras1[i], paras2[j])[strlen(paras1[i])][strlen(paras2[j])];
		}
	}
	return scoreParas;
}

/* =============================================================== */
int **levParas(int **scoreParas, char **paras1, char **paras2, int nbPara1, int nbPara2)
/* Retourne une matrice TParas dont TParas[i][j] est le score d'un
   alignement optimal entre les premiers i+1 paragraphes de text1 et
   les premiers j+1 paragraphes de text2 en mettant en correspondance
   les diff¨¦rentes paragraphes mais non pas les caract¨¨res
   Une fonction interm¨¦diaire pour la question 4                   */
/* =============================================================== */
{
	int **TParas = NULL;
	int i, j;
	TParas = (int **)malloc((nbPara1 + 1) * sizeof(int *));

	TParas[0] = (int *)malloc((nbPara2 + 1) * sizeof(int));
	TParas[0][0] = 0;

	for(i = 1; i <= nbPara1; i++)
	{
		TParas[i] = (int *)malloc((nbPara2 + 1) * sizeof(int));
		TParas[i][0] = strlen(paras1[i - 1]) + TParas[i - 1][0];
	}
	for(j = 1; j <= nbPara2; j++)
	{
		TParas[0][j] = strlen(paras2[j - 1]) + TParas[0][j - 1];
	}
	for(i = 1; i <= nbPara1; i++)
	{
		for(j = 1; j <= nbPara2; j++)
		{
			TParas[i][j] = Imin3(TParas[i][j - 1] + strlen(paras2[j - 1]), TParas[i - 1][j - 1] + scoreParas[i - 1][j - 1], TParas[i - 1][j] + strlen(paras1[i - 1]));
		}
	}
	return TParas;
}

/* =============================================================== */
void findAlignParasOpt(int **TParas, char **paras1, char **paras2, int nbPara1, int nbPara2)
/* Reponse finale de la question 4                                 */
/* =============================================================== */
{
	int i, j, k, index;
	char **alignParasOpt1, **alignParasOpt2;
	int nbParaTotal = nbPara1 + nbPara2 - 1;
	
	alignParasOpt1 = (char **)malloc(nbParaTotal * sizeof(char *));
	alignParasOpt2 = (char **)malloc(nbParaTotal * sizeof(char *));

	i = nbPara1;
	j = nbPara2;
	index = nbParaTotal;
	
	while(i > 0 || j > 0)
	{
		index--;
		
		if(i > 0 && TParas[i][j] == TParas[i - 1][j] + (int)strlen(paras1[i - 1]))
		{
			alignParasOpt1[index] = (char *)malloc((int)strlen(paras1[i - 1]) + 1);
			alignParasOpt2[index] = (char *)malloc((int)strlen(paras1[i - 1]) + 1);
			strcpy(alignParasOpt1[index], paras1[i - 1]);
			for(k = 0; k < (int)strlen(paras1[i - 1]); k++)
			{
				alignParasOpt2[index][k] = '_';
			}
			alignParasOpt2[index][k] = '\0';
			i--;
		}
		else if(j > 0 && TParas[i][j] == TParas[i][j - 1] + (int)strlen(paras2[j - 1]))
		{
			alignParasOpt1[index] = (char *)malloc((int)strlen(paras2[j - 1]) + 1);
			alignParasOpt2[index] = (char *)malloc((int)strlen(paras2[j - 1]) + 1);
			for(k = 0; k < (int)strlen(paras2[j - 1]); k++)
			{
				alignParasOpt1[index][k] = '_';
			}
			alignParasOpt1[index][k] = '\0';
			strcpy(alignParasOpt2[index], paras2[j - 1]);
			j--;
		}
		else
		{
			alignParasOpt1[index] = findAlignOpt(lev(paras1[i - 1], paras2[j - 1]), paras1[i - 1], paras2[j - 1])[0];
			alignParasOpt2[index] = findAlignOpt(lev(paras1[i - 1], paras2[j - 1]), paras1[i - 1], paras2[j - 1])[1];
			i--;
			j--;
		}
	}
	for(i = index; i < nbParaTotal; i++)
	{
		affiche(alignParasOpt1[i], alignParasOpt2[i], 50);
	}
	for(i = index; i < nbParaTotal; i++)
	{
		free(alignParasOpt1[i]);
		free(alignParasOpt2[i]);
	}
	free(alignParasOpt1);
	free(alignParasOpt2);
	
}

/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
	char *x, *y, *tmp;
	int score;
	char **align;
	char **paras1, **paras2;
	int **scoreParas;
	int **TParas;
	int nbPara1 = 0, nbPara2 = 0;
	int i;
	int flag = 0;

	if(argc != 3){
		printf("usage: %s text1 text2\n", argv[0]);
		exit(0);
	}  

	x = readtextfile(argv[1]);
	y = readtextfile(argv[2]);

	tmp = x;
	if(strlen(x) > strlen(y))
	{
		tmp = y;
	}
	for(i = 0; i < (int)strlen(tmp); i++)
	{
		if(x[i] == '\n') 
		{
			flag = 4;
			break;
		}
	}

	printf("Affichage des textes originaux : \n\n");

	if(flag == 0)
	{
		affiche(x, y, 50);
		printf("Test de question 3 : \n\n");
		score = lev(x, y)[strlen(x)][strlen(y)];
		printf("le score de l'alignement optimal est: %d\n", score);

		align = findAlignOpt(lev(x, y), x, y);
		printf("\nUn alignement optimal des 2 textes : \n");
		affiche(align[0], align[1], 50);
		free(align);
	}

	else
	{
		printf("\t\t=======%s=======\n%s\n\n\t\t=======%s=======\n%s\n\n", argv[1], x, argv[2], y);
		printf("Test de question 4 : \n\n");
		paras1 = separeParas(x, &nbPara1);
		paras2 = separeParas(y, &nbPara2);
		scoreParas = scoreEntreParas(paras1, paras2, nbPara1, nbPara2);

		TParas = levParas(scoreParas, paras1, paras2, nbPara1, nbPara2);

		printf("La distance entre textes : %d; longueur de %s : %d, longueur de %s : %d\nScore de similarite en %% : %.6f\n", TParas[nbPara1][nbPara2], argv[1], TParas[nbPara1][0], argv[2], TParas[0][nbPara2], (float)100 * (TParas[nbPara1][0] + TParas[0][nbPara2] - TParas[nbPara1][nbPara2]) / (TParas[nbPara1][0] + TParas[0][nbPara2]));

		findAlignParasOpt(TParas, paras1, paras2, nbPara1, nbPara2);

		free(paras1);
		free(paras2);
		free(TParas);
		free(scoreParas);
	}
	free(x);
	free(y);

}
