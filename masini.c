#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* citește brand-ul mașinii și îl introduce într-o matrice*/
void citestebrand(char *brand[], int i)
{
    char aux[21];

    scanf("%s", aux);
    brand[i] = malloc(strlen(aux) + 1);
    strcpy(brand[i], aux);
}

/* citește numărul mașinii și îl introduce într-o matrice*/
void citestenumar(char *numar[], int i)
{
    char aux[21];

    scanf("%s", aux);
    numar[i] = malloc(strlen(aux) + 1);
    strcpy(numar[i], aux);
}

/* citește combustibilul mașinii și îl introduce într-o matrice*/
void citestecombustibil(char *combustibil[], int i)
{
    char aux[21];

    scanf("%s", aux);
    combustibil[i] = malloc(strlen(aux) + 1);
    strcpy(combustibil[i], aux);
}

/* calculează câte mașini de fiecare tip (după combustibil) sunt*/
void nrcombustibili(char *combustibil[], int n,
int *nrb, int *nrm, int *nrh, int *nre)
{
    int i;
    *nrb = 0, *nrm = 0, *nrh = 0, *nre = 0;

    // parcurge matricea de combustibili
    for (i = 0; i < n; i++)
    {
        // când intâlnește un anumit tip de combustibil
        // crește contorul pentru combustibilul respectiv
        if (!strcmp(combustibil[i], "benzina"))
        {
            *nrb = *nrb + 1;
        }
        if (!strcmp(combustibil[i], "motorina"))
        {
            *nrm = *nrm + 1;
        }
        if (!strcmp(combustibil[i], "hibrid"))
        {
            *nrh = *nrh + 1;
        }
        if (!strcmp(combustibil[i], "electric"))
        {
            *nre = *nre + 1;
        }
    }
}

/* calculează consumul total de combustibil
și suma totală plătita pentru fiecare marcă*/
int brandconsum(char *brand[], char *combustibil[], double consum[],
int km[], int n, char *brandunic[], double consumtotal[], double costtotal[])
{
    int i, j, este, cate = 0;
    brandunic[0] = malloc(strlen(brand[0]) + 1);

    // introduce in matricea de brand-uri unice primul brand
    strcpy(brandunic[0], brand[0]);
    cate = 1;

    // parcurge matricea de brand-uri
    for (i = 1; i < n; i++)
    {
        este = 0;
        // parcurge matricea de brand-uri unice
        for (j = 0; j < cate; j++)
        {
            // dacă brand-ul curent a fost deja 
            // introdus în matricea de brand-uri unice
            if (!strcmp(brand[i], brandunic[j]))
            {
                este = 1;
            }
        }
        // dacă nu a mai fost introdus
        if (este == 0)
        {
            brandunic[cate] = malloc(strlen(brand[i]) + 1);

            // introduce brand-ul curent în matricea de brand-uri unice
            strcpy(brandunic[cate], brand[i]);
            cate++;
        }
    }

    brandunic = realloc(brandunic, cate * sizeof(char *));
    consumtotal = realloc(consumtotal, cate * sizeof(double));

    // parcurge matricea de brand-uri
    for (i = 0; i < n; i++)
    {
        // parcurge matricea de brand-uri unice
        for (j = 0; j < cate; j++)
        {
            // dacă brand-ul curent a fost găsit in matricea de brand-uri unice
            if (!strcmp(brand[i], brandunic[j]))
            {
                // adaugă la consumul total al brand-ului 
                // unic consumul mașinii cu brand-ul curent
                consumtotal[j] = (double)(consumtotal[j]
                + (consum[i] * km[i]) / 100);

                // adaugă la costul total al brand-ului 
                // unic costul de deplasare al mașinii cu brand-ul 
                // curent în funcție de ce combustibil folosește
                if (!strcmp(combustibil[i], "benzina")
                || !strcmp(combustibil[i], "hibrid"))
                {
                    costtotal[j] = (double)((costtotal[j]
                    + ((consum[i] * km[i]) / 100) * 8.02));
                }
                if (!strcmp(combustibil[i], "motorina"))
                {
                    costtotal[j] = (double)((costtotal[j]
                    + ((consum[i] * km[i]) / 100) * 9.29));
                }
            }
        }
    }

    // returnează câte brand-uri unice sunt în matricea de brand-uri
    return cate;
}

/* calculează câte numere de înmatriculare nu sunt corecte*/
void nrgresite(char *brand[], char *numar[], int n, int gresit[])
{
    int i;

    // parcurge matricea de numere de înmatriculare
    for (i = 0; i < n; i++)
    {
        // dacă numărul curent nu are o lungime
        // valabilă este marcat ca și greșit
        if (strlen(numar[i]) < 6 || strlen(numar[i]) > 8)
        {
            gresit[i] = 1;
        }
        // dacă are lungimea 6, poate fi numai de forma A12ABC
        else if (strlen(numar[i]) == 6)
        {
            // în cazul în care nu e de forma A12ABC, este marcat ca și greșit
            if (numar[i][0] < 'A' || numar[i][0] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][1] < '0' || numar[i][1] > '9')
            {
                gresit[i] = 1;
            }
            if (numar[i][2] < '0' || numar[i][2] > '9')
            {
                gresit[i] = 1;
            }
            if (numar[i][3] < 'A' || numar[i][3] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][4] < 'A' || numar[i][4] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][5] < 'A' || numar[i][5] > 'Z')
            {
                gresit[i] = 1;
            }
        }
        // dacă are lungimea 7, poate fi de forma A123ABC sau AB12ABC
        else if (strlen(numar[i]) == 7)
        {
            // se verifică mai întâi prima literă
            if (numar[i][0] < 'A' || numar[i][0] > 'Z')
            {
                gresit[i] = 1;
            }
            // dacă prima literă este corectă
            else
            {
                // se verifică dacă a doua este
                // cifră pentru a intra pe primul caz
                if (numar[i][1] >= '0' && numar[i][1] <= '9')
                {
                    // dacă nu respectă formatul impus
                    if (numar[i][2] < '0' || numar[i][2] > '9')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][3] < '0' || numar[i][3] > '9')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][4] < 'A' || numar[i][4] > 'Z')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][5] < 'A' || numar[i][5] > 'Z')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][6] < 'A' || numar[i][6] > 'Z')
                    {
                        gresit[i] = 1;
                    }
                }
                // sau se verifică daca a doua este
                // literă pentru a intra pe al doilea caz
                else if (numar[i][1] >= 'A' && numar[i][1] <= 'Z')
                {
                    // dacă nu respectă formatul impus
                    if (numar[i][2] < '0' || numar[i][2] > '9')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][3] < '0' || numar[i][3] > '9')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][4] < 'A' || numar[i][4] > 'Z')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][5] < 'A' || numar[i][5] > 'Z')
                    {
                        gresit[i] = 1;
                    }
                    if (numar[i][6] < 'A' || numar[i][6] > 'Z')
                    {
                        gresit[i] = 1;
                    }
                }
            }
        }
        // dacă are lungimea 8, poate fi numai de forma AB123ABC
        else if (strlen(numar[i]) == 8)
        {
            // în cazul în care nu este de forma 
            // AB123ABC, este marcat ca și greșit
            if (numar[i][0] < 'A' || numar[i][0] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][1] < 'A' || numar[i][1] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][2] < '0' || numar[i][2] > '9')
            {
                gresit[i] = 1;
            }
            if (numar[i][3] < '0' || numar[i][3] > '9')
            {
                gresit[i] = 1;
            }
            if (numar[i][4] < '0' || numar[i][4] > '9')
            {
                gresit[i] = 1;
            }
            if (numar[i][5] < 'A' || numar[i][5] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][6] < 'A' || numar[i][6] > 'Z')
            {
                gresit[i] = 1;
            }
            if (numar[i][7] < 'A' || numar[i][7] > 'Z')
            {
                gresit[i] = 1;
            }
        }
    }
}

int main()
{
    char **brand, **numar, **combustibil, c, **brandunic;
    double *consum, *consumtotal, *costtotal;
    int *km, n, i, nrb, nrm, nrh, nre, *gresit, existagresit = 0, cate;

    // se citeșe numărul de mașini
    scanf("%d", &n);

    consum = malloc(n * sizeof(double));
    km = malloc(n * sizeof(int));
    brand = malloc(n * sizeof(char *));
    numar = malloc(n * sizeof(char *));
    combustibil = malloc(n * sizeof(char *));

    // se citesc pe rând datele pentru fiecare mașină
    for (i = 0; i < n; i++)
    {
        citestebrand(brand, i);
        getchar();
        citestenumar(numar, i);
        getchar();
        citestecombustibil(combustibil, i);
        getchar();
        scanf("%lf%d", &consum[i], &km[i]);
        getchar();
    }
    // se citește cerința
    scanf("%c", &c);

    // în funcție de cerință se intră pe cazul respectiv
    if (c == 'a')
    {
        nrcombustibili(combustibil, n, &nrb, &nrm, &nrh, &nre);

        // se afișează statistica
        printf("benzina - %d\n", nrb);
        printf("motorina - %d\n", nrm);
        printf("hibrid - %d\n", nrh);
        printf("electric - %d\n", nre);
    }

    if (c == 'b')
    {
        brandunic = malloc(n * sizeof(char *));
        consumtotal = calloc(n, sizeof(double));
        costtotal = calloc(n, sizeof(double));
        cate = brandconsum(brand, combustibil, consum,
        km, n, brandunic, consumtotal, costtotal);

        // pentru fiecare brand unic
        for (i = 0; i < cate; i++)
        {
            // se afișează cât a consumat și cât a costat consumul
            printf("%s a consumat %.2lf - %.2lf lei\n",
            brandunic[i], consumtotal[i], costtotal[i]);
        }
    }

    if (c == 'c')
    {
        gresit = calloc(n, sizeof(int));
        nrgresite(brand, numar, n, gresit);

        // parcurge numerele de înmatriculare
        for (i = 0; i < n; i++)
        {
            // dacă un număr este greșit
            if (gresit[i])
            {
                // afișează care mașină are numărul greșit
                printf("%s cu numarul %s: numar invalid\n",
                brand[i], numar[i]);

                // marchează ca există măcar o mașină cu număr greșit
                existagresit = 1;
            }
        }

        // dacă nu exista nicio mașină cu număr greșit
        if (!existagresit)
        {
            printf("Numere corecte!\n");
        }
    }

    return 0;
}