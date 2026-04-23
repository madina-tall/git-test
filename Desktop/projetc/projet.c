#include <stdio.h>
#include <stdlib.h>

/* Variable globale : le caractere courant */
char calu;

/* Flag d'erreur */
int erreur_trouvee;

/* Prototypes */
int expression();
int terme();
int facteur();
int nombre();
void lire_utile();
void sauter_ligne();

void lire_utile() {
    do {
        calu = getchar();
    } while (calu == ' ' || calu == '\t' || calu == '\n');
}

void sauter_ligne() {
    while (calu != '\n' && (int)calu != EOF) {
        calu = getchar();
    }
}

/* nombre -> chiffre nombre | chiffre */
int nombre() {
    int valeur = 0;

    if (calu < '0' || calu > '9') {
        erreur_trouvee = 1;
        return 0;
    }

    while (calu >= '0' && calu <= '9') {
        valeur = valeur * 10 + (calu - '0');
        calu = getchar();
    }

    /* sauter les blancs */
    while (calu == ' ' || calu == '\t') {
        calu = getchar();
    }

    return valeur;
}

/* facteur -> nombre | '(' expression ')' */
int facteur() {
    int valeur = 0;

    if (erreur_trouvee) return 0;

    if (calu == '(') {
        lire_utile();
        valeur = expression();
        if (!erreur_trouvee) {
            if (calu == ')') {
                lire_utile();
            } else {
                erreur_trouvee = 1;
            }
        }
    } else if (calu >= '0' && calu <= '9') {
        valeur = nombre();
    } else {
        erreur_trouvee = 1;
    }

    return valeur;
}

/* terme -> facteur opérateur-multiplicatif terme | facteur
   Recursif a droite -> evaluation droite->gauche */
int terme() {
    int valeur = facteur();

    if (!erreur_trouvee && (calu == '*' || calu == '/')) {
        char op = calu;
        lire_utile();
        int val2 = terme();   /* recursion a droite */
        if (!erreur_trouvee) {
            if (op == '*') {
                valeur = valeur * val2;
            } else {
                valeur = valeur / val2;
            }
        }
    }

    return valeur;
}

/* expression -> terme opérateur-additif expression | terme
   Recursif a droite -> evaluation droite->gauche */
int expression() {
    int valeur = terme();

    if (!erreur_trouvee && (calu == '+' || calu == '-')) {
        char op = calu;
        lire_utile();
        int val2 = expression();  /* recursion a droite */
        if (!erreur_trouvee) {
            if (op == '+') {
                valeur = valeur + val2;
            } else {
                valeur = valeur - val2;
            }
        }
    }

    return valeur;
}

int main() {
    int valeur;

    while (1) {
        printf("A toi : ");
        lire_utile();

        if ((int)calu == EOF || calu == '.') {
            printf("Au revoir...\n");
            break;
        }

        erreur_trouvee = 0;
        valeur = expression();

        if (!erreur_trouvee && calu == '=') {
            printf("la syntaxe de l'expression est correcte\n");
            printf("sa valeur est %d\n", valeur);
        } else {
            printf("la syntaxe de l'expression est erronee\n");
        }

        sauter_ligne();
    }

    return 0;
}