#include <stdio.h>

/* verifică pentru fiecare prizonier dacă și-a
găsit numărul și afișează mesajul corespunzător */
void rezultat(int p, int cutie[])
{
    int nrp, castiga = 1, incercari, nr, gasit;

    // parcurge numerele prizonierilor
    for (nrp = 1; nrp <= p; nrp++)
    {
        incercari = 1;
        nr = nrp;
        gasit = 0;
        // parcurge încercările prizonieriului curent
        while (incercari <= p / 2)
        {
            if (cutie[nr] == nrp)
            {
                gasit = 1;
            }
            nr = cutie[nr];
            incercari++;
        }
        // verifică dacă prizonieriul curent și-a găsit numărul
        if (!gasit)
        {
            castiga = 0;
        }
    }
    // verifică dacă fiecare prizonier și-a găsit numărul
    if (castiga)
    {
        printf("Da\n");
    }
    else
    {
        printf("Nu\n");
    }
}

/* parcurge fiecare secvență de numere din cutii
până se ajunge la numărul inițial și afișeaza ciclul */
void cicluri(int p, int cutie[])
{
    int nrc, nr, nrvechi;

    // parcurge numerele cutiilor
    for (nrc = 1; nrc <= p; nrc++)
    {
        nr = nrc;
        // dacă cutia curentă nu a mai fost găsită deja
        if (cutie[nr])
        {
            printf("%d", nr);
            // cât timp nu s-a găsit numărul inițial într-o cutie
            while (cutie[nr] != nrc)
            {
                printf(" %d", cutie[nr]);
                nrvechi = nr;
                nr = cutie[nr];
                cutie[nrvechi] = 0;
            }
            // golește cutiile găsite pentru a nu mai
            // căuta in ele la următoarea parcurgere
            cutie[nr] = 0;
            printf("\n");
        }
    }
}

int main()
{
    int p, cutie[501], i;

    // citim datele de intrare
    scanf("%d", &p);
    for (i = 1; i <= p; i++)
    {
        scanf("%d", &cutie[i]);
    }

    // apelează funcțiile rezultat și cicluri
    rezultat(p, cutie);
    cicluri(p, cutie);

    return 0;
}