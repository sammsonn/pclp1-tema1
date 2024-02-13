#include <stdio.h>
#include <string.h>

/* face codificarea A*/
void CodificareA(char text[], char cheieA[])
{
    char matrice[501][501], aux;
    int i = 0, j = 0, k = 0, linii, coloane, ordine[51], lungime;

    // introduce textul in matricea cu numarul
    // de coloane egal cu lungimea cheii
    for (k = 0; k < strlen(text); k++)
    {
        if (j < strlen(cheieA))
        {
            matrice[i][j] = text[k];
        }
        else
        {
            i++;
            j = 0;
            matrice[i][j] = text[k];
        }
        j++;
    }
    // completează elementele necompletate din matrice cu spații
    while (j < strlen(cheieA))
    {
        matrice[i][j] = ' ';
        j++;
    }

    linii = i;
    coloane = strlen(cheieA) - 1;

    // inițializează un vector pentru ordinea literelor
    for (i = 0; i < strlen(cheieA); i++)
    {
        ordine[i] = i;
    }
    
    // sortează lexicografic cheia, memorând și ordinea nouă a literelor
    for (i = 0; i < strlen(cheieA) - 1; i++)
    {
        for (j = i + 1; j <= strlen(cheieA) - 1; j++)
        {
            if (cheieA[j] < cheieA[i])
            {
                aux = cheieA[j];
                cheieA[j] = cheieA[i];
                cheieA[i] = aux;

                aux = ordine[j];
                ordine[j] = ordine[i];
                ordine[i] = aux;
            }
        }
    }

    // golește șirul inițial
    text[0] = '\0';

    // alipește elementele de pe coloane în ordinea nouă a coloanelor
    for (j = 0; j <= coloane; j++)
    {
        for (i = 0; i <= linii; i++)
        {
            strncat(text, &matrice[i][ordine[j]], 1);
        }
    }

    // calculează lungimea textului nou
    lungime = (coloane + 1) * (linii + 1);
    // închide textul nou
    text[lungime + 1] = '\0';
   
    // se afișează textul codificat
    puts(text);
}

void CodificareB(char text[], int cheieB)
{
    int i, j, aux;

    // permută circular la dreapta de câte ori indică cheia
    for (i = 1; i <= cheieB; i++)
    {
        aux = text[strlen(text) - 1];
        for (j = strlen(text) - 1; j > 0; j--)
        {
            text[j] = text[j - 1];
        }
        text[0] = aux;
    }

    // adună la literele permutate pe cheieB
    for (i = 0; i < cheieB; i++)
    {
        // verifică dacă nu este spațiu
        if (text[i] != ' ')
        {
            // dacă este literă mică
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                // dacă după adunare iese din alfabetul literelor mici
                if (text[i] + cheieB > 122)
                {
                    text[i] = text[i] + cheieB - 58;
                }
                else
                {
                    text[i] = text[i] + cheieB;
                }
            }
            // dacă este literă mare
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                // dacă după adunare iese din alfabetul literelor mari
                if (text[i] + cheieB > 90)
                {
                    text[i] = text[i] + cheieB + 6;
                }
                else
                {
                    text[i] = text[i] + cheieB;
                }
            }
        }
    }

    // afișează textul codificat
    puts(text);
}

void DecodificareA(char text[], char cheieA[])
{
    char matrice[501][501], aux;
    int i = 0, j = 0, k = 0, linii, coloane,
    ordine[51], lungime, ordinebun[51];
    
    // matricea are numarul de linii egal cu lungimea cheii
    linii = strlen(cheieA);

    // calculează câte coloane are matricea
    if (strlen(text) % strlen(cheieA) == 0)
    {
        coloane = strlen(text) / strlen(cheieA);
    }
    else
    {
        coloane = strlen(text) / strlen(cheieA) + 1;
    }

    // completează matricea pe linii cu textul de decodificat
    for (k = 0; k < strlen(text); k++)
    {
        if (j < coloane)
        {
            matrice[i][j] = text[k];
        }
        else
        {
            i++;
            j = 0;
            matrice[i][j] = text[k];
        }
        j++;
    }

    // daca mai rămân elemente de completat în matrice se completează cu spații
    while (i < linii)
    {
        if (j < coloane)
        {
            matrice[i][j] = ' ';
        }
        else
        {
            i++;
            j = 0;
            matrice[i][j] = ' ';
        }
        j++;
    }
    while (j < coloane)
    {
        matrice[i][j] = ' ';
        j++;
    }

    // inițializează un vector pentru ordinea literelor
    for (i = 0; i < strlen(cheieA); i++)
    {
        ordine[i] = i;
    }

    // sortează lexicografic cheia, memorând și ordinea nouă a literelor
    for (i = 0; i < strlen(cheieA) - 1; i++)
    {
        for (j = i + 1; j <= strlen(cheieA) - 1; j++)
        {
            if (cheieA[j] < cheieA[i])
            {
                aux = cheieA[j];
                cheieA[j] = cheieA[i];
                cheieA[i] = aux;

                aux = ordine[j];
                ordine[j] = ordine[i];
                ordine[i] = aux;
            }
        }
    }

    // inițializează un vector pentru a vedea în ce ordine
    // sunt plasate liniile în matrice în funcție
    // de textul la care trebuie să se ajungă
    for (i = 0; i < strlen(cheieA); i++)
    {
        for (j = 0; j < strlen(cheieA); j++)
        {
            if (ordine[j] == i)
            {
                ordinebun[i] = j;
            }
        }
    }

    // goleșe șirul de completat
    text[0] = '\0';

    // alipește la text elementele matricii pe coloane,
    // liniile fiind luate în ordinea bună calculată anterior
    for (j = 0; j < coloane; j++)
    {
        for (i = 0; i < linii; i++)
        {
            strncat(text, &matrice[ordinebun[i]][j], 1);
        }
    }

    // calculează lungimea textului și îl închide
    lungime = (coloane + 1) * (linii + 1);
    text[lungime + 1] = '\0';

    // afișează textul decodificat
    puts(text);
}

void DecodificareB(char text[], int cheieB)
{
    int i, j, aux;

    // scade din literele permutate pe cheieB
    for (i = 0; i < cheieB; i++)
    {
        // verifică dacă nu este spațiu
        if (text[i] != ' ')
        {
            // dacă este literă mică
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                // daca iese din alfabetul literelor mici
                if (text[i] - cheieB < 97)
                {
                    text[i] = text[i] - cheieB - 6;
                }
                else
                {
                    text[i] = text[i] - cheieB;
                }
            }
            // dacă este literă mare
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                // dacă iese din alfabetul literelor mari
                if (text[i] - cheieB < 65)
                {
                    text[i] = text[i] - cheieB + 58;
                }
                else
                {
                    text[i] = text[i] - cheieB;
                }
            }
        }
    }

    // permută circular la stânga de câte ori indică cheia
    for (i = 1; i <= cheieB; i++)
    {
        aux = text[0];
        for (j = 0; j < strlen(text) - 1; j++)
        {
            text[j] = text[j + 1];
        }
        text[strlen(text) - 1] = aux;
    }

    // afișează textul decodificat
    puts(text);
}

int main()
{
    char text[501], cheieA[51], codificare[21];
    int cheieB;

    // se citește textul inițial
    fgets(text, 501, stdin);
    text[strlen(text) - 1] = '\0';

    // se citesc codificările și decodificările până se citește STOP
    while (1)
    {
        scanf("%s", codificare);

        // verifică dacă s-a citit STOP
        if (!strcmp(codificare, "STOP"))
        {
            break;
        }

        getchar();

        // verifică ce codificare sau decodificare s-a citit
        if (!strcmp(codificare, "CodificareA"))
        {
            fgets(cheieA, 51, stdin);
            cheieA[strlen(cheieA) - 1] = '\0';
            CodificareA(text, cheieA);
        }

        if (!strcmp(codificare, "CodificareB"))
        {
            scanf("%d", &cheieB);
            CodificareB(text, cheieB);
        }

        if (!strcmp(codificare, "DecodificareA"))
        {
            fgets(cheieA, 51, stdin);
            cheieA[strlen(cheieA) - 1] = '\0';
            DecodificareA(text, cheieA);
        }

        if (!strcmp(codificare, "DecodificareB"))
        {
            scanf("%d", &cheieB);
            DecodificareB(text, cheieB);
        }
    }

    return 0;
}