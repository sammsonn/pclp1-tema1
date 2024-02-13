#include <stdio.h>
#include <string.h>

/* verifică care șir este mai mare și
returnează 1 dacă e primul și 2 dacă e al doilea*/
int comparatie(char a[], char b[])
{
    int mare = 1;
    char aux[501];

    // dacă primul șir este mai mic le interschimbă
    if (strcmp(a, b) < 0)
    {
        strcpy(aux, a);
        strcpy(a, b);
        strcpy(b, aux);
        mare = 2;
    }
    return mare;
}

/* adună două părți reale sau imaginare, rezultatul fiind introdus în a*/
void adunaremica(char a[], char b[])
{
    // ult ajută în cazul în care suma cifrelor de pe o poziție trece de 10,
    // adăugând 1 la suma cifrelor de pe următoare poziție
    int ult = 0, i;

    // parcurge numerele părții de la coadă la cap
    for (i = strlen(a) - 1; i >= 0; i--)
    {
        // dacă suma cifrelor trece de 10
        if (a[i] + b[i] - 48 + ult > 57)
        {
            a[i] = a[i] + b[i] + ult - 58;
            ult = 1;
        }
        else
        {
            a[i] = a[i] + b[i] + ult - 48;
            ult = 0;
        }
    }
    
    // închide șirul
    a[strlen(a)] = '\0';
}

/* scade două părți reale sau imaginare, rezultatul fiind introdus în a*/
void scaderemica(char a[], char b[])
{
    // ult ajută în cazul în care suma cifrelor de pe o poziție scade sub 0,
    // scăzând 1 din diferența cifrelor de pe următoare poziție
    int ult = 0, i;

    // parcurge numerele părții de la coadă la cap
    for (i = strlen(a) - 1; i >= 0; i--)
    {
        if (a[i] - b[i] + 48 - ult < 48)
        {
            a[i] = a[i] - b[i] - ult + 58;
            ult = 1;
        }
        else
        {
            a[i] = a[i] - b[i] - ult + 48;
            ult = 0;
        }
    }

    // închide șirul
    a[strlen(a)] = '\0';
}

/* adună două numere complexe*/
void adunare(char a[], char b[], int n)
{
    // semnele părților fiecărui număr
    char semnre1 = a[0], semnre2 = b[0],
         semnim1 = a[(n - 1) / 2], semnim2 = b[(n - 1) / 2];

    char re1[501], re2[501], im1[501], im2[501];
    int mare;

    // părțile fiecărui numar
    strncpy(re1, a + 1, (n - 1) / 2 - 1);
    re1[(n - 1) / 2 - 1] = '\0';
    strncpy(re2, b + 1, (n - 1) / 2 - 1);
    re2[(n - 1) / 2 - 1] = '\0';
    strncpy(im1, a + (n - 1) / 2 + 1, (n - 1) / 2 - 1);
    im1[(n - 1) / 2 - 1] = '\0';
    strncpy(im2, b + (n - 1) / 2 + 1, (n - 1) / 2 - 1);
    im2[(n - 1) / 2 - 1] = '\0';

    // dacă părțile reale ale numerelor au același semn
    if ((semnre1 == '0' && semnre2 == '0') ||
    (semnre1 == '1' && semnre2 == '1'))
    {
        adunaremica(re1, re2);
    }

    // dacă partea reală a primului număr este negativă
    // iar cea celui de-al doilea este pozitivă
    if (semnre1 == '1' && semnre2 == '0')
    {
        mare = comparatie(re1, re2);
        scaderemica(re1, re2);
        // se schimbă semnul părții în funcție de care modul era mai mare
        if (mare == 1)
        {
            semnre1 = '1';
        }
        else if (mare == 2)
        {
            semnre1 = '0';
        }
    }

    // dacă partea reală a primului număr este pozitivă
    // iar cea celui de-al doilea este negativă
    if (semnre1 == '0' && semnre2 == '1')
    {
        mare = comparatie(re1, re2);
        scaderemica(re1, re2);
        // se schimbă semnul părții în funcție de care modul era mai mare
        if (mare == 1)
        {
            semnre1 = '0';
        }
        else if (mare == 2)
        {
            semnre1 = '1';
        }
    }

    // se execută aceleași ecuații pentru părțile imaginare
    if ((semnim1 == '0' && semnim2 == '0')
    || (semnim1 == '1' && semnim2 == '1'))
    {
        adunaremica(im1, im2);
    }

    if (semnim1 == '1' && semnim2 == '0')
    {
        mare = comparatie(im1, im2);
        scaderemica(im1, im2);
        if (mare == 1)
        {
            semnim1 = '1';
        }
        else if (mare == 2)
        {
            semnim1 = '0';
        }
    }

    if (semnim1 == '0' && semnim2 == '1')
    {
        mare = comparatie(im1, im2);
        scaderemica(im1, im2);
        if (mare == 1)
        {
            semnim1 = '0';
        }
        else if (mare == 2)
        {
            semnim1 = '1';
        }
    }

    // se golește șirul în care se va introduce noul rezultat
    a[0] = '\0';

    // se alipesc pe rând semnul părții reale, partea reală,
    // semnul părții imaginare și partea imaginară
    strncat(a, &semnre1, 1);
    strcat(a, re1);
    strncat(a, &semnim1, 1);
    strcat(a, im1);

    // se afișează rezultatul obținut
    printf("%s\n", a);
}

/* scade două numere*/
void scadere(char a[], char b[], int n)
{
    // semnele părților fiecărui număr
    char semnre1 = a[0], semnre2 = b[0],
         semnim1 = a[(n - 1) / 2], semnim2 = b[(n - 1) / 2];

    char re1[501], re2[501], im1[501], im2[501];
    int mare;

    // părțile fiecărui numar
    strncpy(re1, a + 1, (n - 1) / 2 - 1);
    re1[(n - 1) / 2 - 1] = '\0';
    strncpy(re2, b + 1, (n - 1) / 2 - 1);
    re2[(n - 1) / 2 - 1] = '\0';
    strncpy(im1, a + (n - 1) / 2 + 1, (n - 1) / 2 - 1);
    im1[(n - 1) / 2 - 1] = '\0';
    strncpy(im2, b + (n - 1) / 2 + 1, (n - 1) / 2 - 1);
    im2[(n - 1) / 2 - 1] = '\0';

    // dacă părțile reale ale numerelor au semne opuse
    if ((semnre1 == '1' && semnre2 == '0')
    || (semnre1 == '0' && semnre2 == '1'))
    {
        adunaremica(re1, re2);
    }

    // dacă părțile reale ale numerelor sunt pozitive
    if (semnre1 == '0' && semnre2 == '0')
    {
        mare = comparatie(re1, re2);
        scaderemica(re1, re2);
        if (mare == 1)
        {
            semnre1 = '0';
        }
        else if (mare == 2)
        {
            semnre1 = '1';
        }
    }

    // dacă părțile reale ale numerelor sunt negative
    if (semnre1 == '1' && semnre2 == '1')
    {
        mare = comparatie(re1, re2);
        scaderemica(re1, re2);
        if (mare == 1)
        {
            semnre1 = '1';
        }
        else if (mare == 2)
        {
            semnre1 = '0';
        }
    }

    // se execută aceleași ecuații pentru părțile imaginare
    if ((semnim1 == '1' && semnim2 == '0')
    || (semnim1 == '0' && semnim2 == '1'))
    {
        adunaremica(im1, im2);
    }

    if (semnim1 == '0' && semnim2 == '0')
    {
        mare = comparatie(im1, im2);
        scaderemica(im1, im2);
        if (mare == 1)
        {
            semnim1 = '0';
        }
        else if (mare == 2)
        {
            semnim1 = '1';
        }
    }

    if (semnim1 == '1' && semnim2 == '1')
    {
        mare = comparatie(im1, im2);
        scaderemica(im1, im2);
        if (mare == 1)
        {
            semnim1 = '1';
        }
        else if (mare == 2)
        {
            semnim1 = '0';
        }
    }

    // se golește șirul în care se va introduce noul rezultat
    a[0] = '\0';

    // se alipesc pe rând semnul părții reale, partea reală,
    // semnul părții imaginare și partea imaginară
    strncat(a, &semnre1, 1);
    strcat(a, re1);
    strncat(a, &semnim1, 1);
    strcat(a, im1);

    // se afișează rezultatul obținut
    printf("%s\n", a);
}

int main()
{
    int n;
    char semn;
    char a[1001], b[1001];

    // citește datele de intrare până când se întâlnește 0
    scanf("%d", &n);
    getchar();
    fgets(a, n, stdin);
    getchar();

    while (1)
    {
        // în funcție de semnul citit se oprește programul
        // sau se apelează funcția corespunzătoare
        semn = getchar();

        if (semn == '0')
        {
            break;
        }

        getchar();
        fgets(b, n, stdin);
        getchar();

        if (semn == '+')
        {
            adunare(a, b, n);
        }

        if (semn == '-')
        {
            scadere(a, b, n);
        }
    }

    return 0;
}