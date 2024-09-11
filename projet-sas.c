#include <stdio.h>
#include <string.h>



typedef struct {
    int numero;
    char nom[50];
    char prenom[50];
    char date_naissance[12];
    char departement[50];
    float note_generale;
} Etudiant;

Etudiant etudiants[100];
int nombre_etudiants = 0;


// Liste des d�partements
char departements[10][50];
int nombre_departements = 0;


// Fonction pour v�rifier si un d�partement existe
int trouverDepartement(char *departement) {
    for (int i = 0; i < nombre_departements; i++) {
        if (strcmp(departements[i], departement) == 0) {
            return i;
        }
    }
    return -1;
}


// Fonction pour afficher les �tudiants d'un d�partement sp�cifique
void afficherEtudiantsParDepartement() {
    int trouve = 0;
    char departement[50];

    printf("Donner le nom du departement: \n");
    scanf("%s",&departement);


    printf("\nListe des etudiants dans le departement %s:\n", departement);

    // Parcourir tous les �tudiants
    for (int i = 0; i < nombre_etudiants; i++) {
        // Comparer le d�partement de l'�tudiant avec celui entr� par l'utilisateur
        if (strcmp(etudiants[i].departement, departement) == 0) {
            // Afficher les d�tails de l'�tudiant
            printf("Numero unique: %d\n", etudiants[i].numero);
            printf("Nom: %s\n", etudiants[i].nom);
            printf("Prenom: %s\n", etudiants[i].prenom);
            printf("Date de naissance: %s\n", etudiants[i].date_naissance);
            printf("Note generale: %.2f\n\n", etudiants[i].note_generale);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun etudiant trouve dans ce departement.\n");
    }
}

// Fonction pour calculer et afficher la moyenne g�n�rale de chaque d�partement
void calculerMoyenneParDepartement() {
    if (nombre_etudiants == 0) {
        printf("Aucun etudiant inscrit!\n");
        return;
    }
    // Variables pour stocker la somme des notes et le nombre d'�tudiants par d�partement
    float somme_notes[10] = {0};
    int nombre_etudiants_par_departement[10] = {0};

    // Variable pour la somme des moyennes des d�partements
    float somme_moyennes_departements = 0;
    int departements_comptes = 0; // Nombre de d�partements utilis�s dans la moyenne

    // Parcourir tous les �tudiants et regrouper les notes par d�partement
    for (int i = 0; i < nombre_etudiants; i++) {
        int index_departement = trouverDepartement(etudiants[i].departement);
        somme_notes[index_departement] += etudiants[i].note_generale;
        nombre_etudiants_par_departement[index_departement]++;
    }

    // Afficher la moyenne de chaque d�partement et calculer la somme des moyennes
    printf("\nMoyenne generale par departement:\n");
    for (int i = 0; i < nombre_departements; i++) {
        if (nombre_etudiants_par_departement[i] > 0) {
            float moyenne_departement = somme_notes[i] / nombre_etudiants_par_departement[i];
            printf("Departement %s: Moyenne = %.2f\n", departements[i], moyenne_departement);

            // Ajouter la moyenne de ce d�partement � la somme des moyennes
            somme_moyennes_departements += moyenne_departement;
            departements_comptes++; // Incr�mentation implicite du nombre de d�partements non vides
        }
    }

    // Calculer et afficher la moyenne g�n�rale de l'universit� si au moins un d�partement a �t� compt�
    if (departements_comptes > 0) {
        float moyenne_universite = somme_moyennes_departements / departements_comptes;
        printf("\nMoyenne generale de l'universite (moyenne des departements): %.2f\n", moyenne_universite);
    } else {
        printf("\nAucun etudiant dans les departements.\n");
    }
}

// Fonction pour affichage nombre etudiants par departement
void afficherNombreEtudiantsParDepartement() {
    if (nombre_etudiants == 0) {
        printf("Aucun etudiant inscrit!\n");
        return;
    }

    // Tableau pour stocker le nombre d'�tudiants par d�partement
    int nombre_etudiants_par_departement[10] = {0};

    // Parcourir tous les �tudiants et compter ceux de chaque d�partement
    for (int i = 0; i < nombre_etudiants; i++) {
        int index_departement = trouverDepartement(etudiants[i].departement);
        if (index_departement != -1) {
            nombre_etudiants_par_departement[index_departement]++;
        }
    }

    // Afficher le nombre d'�tudiants par d�partement
    printf("\nNombre d'etudiants par departement:\n");
    for (int i = 0; i < nombre_departements; i++) {
        printf("Departement %s: %d etudiant(s)\n", departements[i], nombre_etudiants_par_departement[i]);
    }
}



// Fonction pour ajouter un �tudiant
void ajouterEtudiant() {
    if (nombre_etudiants >= 100) {
        printf("Nombre maximum atteint!\n");
        return;
    }
     Etudiant e1;
    printf("Entrez le numero de l etudiant: ");
    scanf("%d", &e1.numero);

    // V�rification si le num�ro existe d�j�
    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].numero == e1.numero) {
            printf("Erreur: Un etudiant avec ce numero existe deja!\n");
            return; // Sortir de la fonction si le num�ro existe d�j�
        }
    }
    // Si le num�ro est unique, continuer � collecter les informations de l'�tudiant
    printf("Entrez le nom de l'etudiant: ");
    scanf("%s", e1.nom);
    printf("Entrez le prenom de l'etudiant: ");
    scanf("%s", e1.prenom);
    printf("Entrez la date de naissance (jj/mm/aaaa): ");
    scanf("%s", e1.date_naissance);
    printf("Entrez le departement de l'etudiant: ");
    scanf("%s", e1.departement);
    do {
        printf("Entrez la note generale de l'etudiant (entre 0 et 20): ");
        scanf("%f", &e1.note_generale);

        if (e1.note_generale < 0 || e1.note_generale > 20) {
            printf("Erreur: La note doit etre comprise entre 0 et 20!\n");
        }
    } while (e1.note_generale < 0 || e1.note_generale > 20);

    // Ajouter le d�partement s'il n'existe pas
    if (trouverDepartement(e1.departement) == -1) {
        if (nombre_departements < 10) {
            strcpy(departements[nombre_departements], e1.departement);
            nombre_departements++;
        } else {
            printf("Nombre maximum de d�partements atteint!\n");
        }
    }

    etudiants[nombre_etudiants] = e1;
    nombre_etudiants++;
    printf("Etudiant ajoute avec succes!\n");
}

// Fonction pour modifier un �tudiant
void modifierEtudiant() {
    int numero;
    printf("Entrez le numero de l'etudiant a modifier: ");
    scanf("%d", &numero);

    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].numero == numero) {
            printf("Modification des informations de l'etudiant %d\n", numero);
            printf("Entrez le nouveau nom de l'etudiant: ");
            scanf("%s", etudiants[i].nom);
            printf("Entrez le nouveau prenom de l'etudiant: ");
            scanf("%s", etudiants[i].prenom);
            printf("Entrez la nouvelle date de naissance (jj/mm/aaaa): ");
            scanf("%s", etudiants[i].date_naissance);
            printf("Entrez le nouveau departement: ");
            scanf("%s", etudiants[i].departement);
            printf("Entrez la nouvelle note generale: ");
            scanf("%f", &etudiants[i].note_generale);
            printf("Modification effectuee avec succes!\n");
            return;
        }
    }
    printf("Etudiant non trouve!\n");
}


// Fonction pour supprimer un �tudiant
void supprimerEtudiant() {
    int numero;
    printf("Entrez le numero de l'etudiant a supprimer: ");
    scanf("%d", &numero);

    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].numero == numero) {
            for (int j = i; j < nombre_etudiants - 1; j++) {
                etudiants[j] = etudiants[j + 1];
            }
            nombre_etudiants--;
            printf("Etudiant supprime avec succes!\n");
            return;
        }
    }
    printf("Etudiant non trouve!\n");
}

// Fonction pour afficher les d�tails d'un �tudiant
void afficherEtudiant() {
    int numero;
    printf("Entrez le numero de l'etudiant: ");
    scanf("%d", &numero);

    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].numero == numero) {
            printf("Numero: %d\n", etudiants[i].numero);
            printf("Nom: %s\n", etudiants[i].nom);
            printf("Prenom: %s\n", etudiants[i].prenom);
            printf("Date de naissance: %s\n", etudiants[i].date_naissance);
            printf("Departement: %s\n", etudiants[i].departement);
            printf("Note generale: %.2f\n", etudiants[i].note_generale);
            return;
        }
    }
    printf("Etudiant non trouve!\n");
}

// Fonction pour afficher les etudiants
void afficherEtudiants() {
    if(nombre_etudiants == 0) printf("Liste vide! \n");
    for (int i = 0; i < nombre_etudiants; i++) {
            printf("Etudiant %d :\n",i+1);
            printf("Numero: %d\n", etudiants[i].numero);
            printf("Nom: %s\n", etudiants[i].nom);
            printf("Prenom: %s\n", etudiants[i].prenom);
            printf("Date de naissance: %s\n", etudiants[i].date_naissance);
            printf("Departement: %s\n", etudiants[i].departement);
            printf("Note generale: %.2f\n", etudiants[i].note_generale);
    }

}


// Fonction pour calculer et afficher le nombre d'etudiants > seuil

void superieureSeuil() {
    float seuil;
    printf("Entrez le seuil de note generale pour filtrer les etudiants: \n");
    scanf("%f", &seuil);

    int nb_etudiants_reussi = 0;

    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].note_generale > seuil) {
            nb_etudiants_reussi++;
        }

    }
    printf("Nombre d'etudiants ayant note > %.2f est: %d\n",seuil, nb_etudiants_reussi);
}

// Fonction pour trier les �tudiants par nom (ordre alphab�tique)
void trierEtudiantsParNom() {
    Etudiant temp;
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = i + 1; j < nombre_etudiants; j++) {
            if (strcmp(etudiants[i].nom, etudiants[j].nom) > 0) {
                temp = etudiants[i];
                etudiants[i] = etudiants[j];
                etudiants[j] = temp;
            }
        }
    }
    printf("Etudiants tries par nom.\n");
    for (int i = 0; i < nombre_etudiants; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants[i].prenom, etudiants[i].nom, etudiants[i].note_generale, etudiants[i].departement);
    }
}

// Fonction pour trier les �tudiants par nom (ordre alphab�tique) INVERSE
void trierEtudiantsParNomInverse() {
    Etudiant temp;
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = i + 1; j < nombre_etudiants; j++) {
            // Inverser la condition pour un tri inverse
            if (strcmp(etudiants[i].nom, etudiants[j].nom) < 0) {
                temp = etudiants[i];
                etudiants[i] = etudiants[j];
                etudiants[j] = temp;
            }
        }
    }
    printf("Etudiants tries par nom (ordre inverse).\n");
    for (int i = 0; i < nombre_etudiants; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants[i].prenom, etudiants[i].nom, etudiants[i].note_generale, etudiants[i].departement);
    }
}


// Fonction pour rechercher un �tudiant par nom
void rechercherEtudiant() {
    char nom[50];
    printf("Entrez le nom de l'etudiant a rechercher: ");
    scanf("%s", nom);

    for (int i = 0; i < nombre_etudiants; i++) {
        if (strcmp(etudiants[i].nom, nom) == 0) {
            printf("Etudiant trouve: Nom: %s, Prenom: %s, Departement: %s, Note: %.2f\n", etudiants[i].nom, etudiants[i].prenom, etudiants[i].departement, etudiants[i].note_generale);
            return;
        }
    }
    printf("Etudiant non trouve!\n");
}


// Fonction pour afficher le total inscrit dans l universite
void totalInscrit(){
    printf("le nombre total des etudiants inscrits dans l universite est : %d",nombre_etudiants);
    return;
}


// Fonction pour trier les �tudiants par note g�n�rale (ordre d�croissant)
void trierEtudiantsParNote() {
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = 0; j < nombre_etudiants - i - 1; j++) {
            if (etudiants[j].note_generale < etudiants[j + 1].note_generale) {
                // �change des �tudiants
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
     printf("\n Liste des etudiants tries par note generale (du plus eleve au plus faible):\n");
    for (int i = 0; i < nombre_etudiants; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants[i].prenom, etudiants[i].nom, etudiants[i].note_generale, etudiants[i].departement);
    }
}


// Fonction pour trier les �tudiants par note g�n�rale (ordre croissant)
void trierEtudiantsParNoteInverse() {
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = 0; j < nombre_etudiants - i - 1; j++) {
            if (etudiants[j].note_generale < etudiants[j + 1].note_generale) {
                // �change des �tudiants
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
     printf("\n Liste des etudiants tries par note generale (du plus faible au plus eleve):\n");
    for (int i = 0; i < nombre_etudiants; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants[i].prenom, etudiants[i].nom, etudiants[i].note_generale, etudiants[i].departement);
    }
}

// Fonction pour afficher les 3 �tudiants ayant les meilleures notes
void afficherTop3Etudiants() {
    if (nombre_etudiants == 0) {
        printf("Aucun etudiant inscrit!\n");
        return;
    }

    // Trier les �tudiants par note
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = 0; j < nombre_etudiants - i - 1; j++) {
            if (etudiants[j].note_generale < etudiants[j + 1].note_generale) {
                // �change des �tudiants
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }

    // Afficher les 3 �tudiants avec les meilleures notes
    printf("\nLes 3 etudiants ayant les meilleures notes:\n");
    for (int i = 0; i < 3 && i < nombre_etudiants; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants[i].prenom, etudiants[i].nom, etudiants[i].note_generale, etudiants[i].departement);
    }
}

// Fonction pour afficher le nombre d'�tudiants ayant r�ussi dans chaque d�partement
void afficherNombreReussitesParDepartement() {
    // Tableau pour compter les r�ussites par d�partement
    int reussites_par_departement[10] = {0};

    // Parcourir tous les �tudiants et compter les r�ussites dans chaque d�partement
    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].note_generale >= 10.0) { // V�rifier si l'�tudiant a r�ussi
            int index_departement = trouverDepartement(etudiants[i].departement);
            if (index_departement != -1) {
                reussites_par_departement[index_departement]++;
            }
        }
    }

    // Afficher le nombre d'�tudiants ayant r�ussi dans chaque d�partement
    printf("\nNombre d'etudiants ayant reussi dans chaque departement:\n");
    for (int i = 0; i < nombre_departements; i++) {
        printf("Departement %s: %d reussite(s)\n", departements[i], reussites_par_departement[i]);
    }
}


// Afficher le nombre d'�tudiants ayant r�ussi tries
void trierEtudiantsReussis() {
    // Compter le nombre d'�tudiants qui ont r�ussi
    int nombre_reussis = 0;
    Etudiant etudiants_reussis[100]; // Tableau temporaire pour les �tudiants qui ont r�ussi

    for (int i = 0; i < nombre_etudiants; i++) {
        if (etudiants[i].note_generale >= 10) {
            etudiants_reussis[nombre_reussis++] = etudiants[i];
        }
    }

    // Appliquer le tri sur les �tudiants qui ont r�ussi
    for (int i = 0; i < nombre_reussis - 1; i++) {
        for (int j = 0; j < nombre_reussis - i - 1; j++) {
            if (etudiants_reussis[j].note_generale > etudiants_reussis[j + 1].note_generale) {
                // �changer les �tudiants
                Etudiant temp = etudiants_reussis[j];
                etudiants_reussis[j] = etudiants_reussis[j + 1];
                etudiants_reussis[j + 1] = temp;
            }
        }
    }

    // Afficher la liste tri�e des �tudiants qui ont r�ussi
    printf("\nListe des etudiants qui ont reussi (note >= 10) tries par note (du plus faible au plus eleve):\n");
    for (int i = 0; i < nombre_reussis; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants_reussis[i].prenom, etudiants_reussis[i].nom, etudiants_reussis[i].note_generale, etudiants_reussis[i].departement);
    }
}





int main() {
    int choix=-1;
    int a,b,c,d;

    do {
        printf("\n---------------------\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Modifier/ supprimer un etudiant\n");
        printf("3. Afficher les etudiants de l universite\n");
        printf("4. Afficher les moyennes par departements et de l universite\n");
        printf("5. Afficher les statistiques \n");
        printf("6. Rechercher un etudiant \n");
        printf("7. Trier les etudiants  \n");

        printf("0. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        getchar();

        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                do {
                    printf(" 1- supprimer\n ");
                    printf("2- modifier\n ");
                    printf("0- Retour au menu \n ");
                    scanf(" %d",&a);

            switch(a){
                case 1:
                    supprimerEtudiant();
                    break;
                case 2:
                    modifierEtudiant();
                break;
                default:
                printf("Menu: \n");
            }

                }while(a!=0);
            break;
            case 3:
                afficherEtudiants();
                break;
            case 4:
                calculerMoyenneParDepartement();
                break;
            case 5:
                do {
                    printf(" 1- Afficher le nombre total d'etudiants inscrits.\n ");
                    printf("2- Afficher le nombre d'etudiants dans chaque departement.\n ");
                    printf("3- Afficher les etudiants ayant une moyenne generale superieure � un certain seuil.\n ");
                    printf("4- Afficher les 3 etudiants ayant les meilleures notes.\n ");
                    printf("5- Afficher le nombre d'etudiants ayant r�ussi dans chaque departement. \n ");
                    printf("0- Retour au menu \n ");
                    scanf(" %d",&b);
                    getchar();

            switch(b){
                case 1:
                    totalInscrit();
                    break;
                case 2:
                    afficherNombreEtudiantsParDepartement();
                    break;
                case 3:
                    superieureSeuil();
                    break;
                case 4:
                    afficherTop3Etudiants();
                    break;
                case 5:
                    afficherNombreReussitesParDepartement();
                    break;
                default:
                printf("Menu: \n");
            }

                }while(b!=0);
            break;

            case 6:
                do {
                    printf(" 1- Rechercher un etudiant par son nom\n ");
                    printf("2- Afficher la liste des etudiants inscrits dans un departement specifique\n ");
                    printf("0- Retour au menu \n ");
                    scanf(" %d",&c);

            switch(c){
                case 1:
                    rechercherEtudiant();
                    break;
                case 2:
                    afficherEtudiantsParDepartement();
                break;
                default:
                printf("Menu: \n");
            }
                }while(c!=0);
                break;
            case 7:
                do {
                    printf(" 1- Tri alphabetique des etudiants en fonction de leur nom de A � Z \n ");
                    printf("2- Tri alphabetique des etudiants en fonction de leur nom de Z � A\n ");
                    printf("3- Tri des etudiants par moyenne generale, du plus eleve au plus faible \n ");
                    printf("4- Tri des etudiants par moyenne generale, du plus faible au plus eleve \n ");
                    printf("0- Retour au menu \n ");
                    scanf(" %d",&c);

            switch(d){
                case 1:
                    trierEtudiantsParNom();
                    break;
                case 2:
                    trierEtudiantsParNomInverse();
                break;
                case 3:
                    trierEtudiantsParNote();
                break;
                case 4:
                    trierEtudiantsParNoteInverse();
                break;
                case 5:
                    trierEtudiantsReussis();
                break;

                default:
                printf("Menu: \n");
            }
                }while(d!=0);
                break;

            case 0:
                printf("Vous avez quitte le programme!\n");
                break;
            default:
                printf("Tapez un nombre depuis le menu svp!\n");
        }
    } while (choix != 0);

    return 0;
}
