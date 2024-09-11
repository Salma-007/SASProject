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


// Liste des départements
char departements[10][50];
int nombre_departements = 0;


// Fonction pour vérifier si un département existe
int trouverDepartement(char *departement) {
    for (int i = 0; i < nombre_departements; i++) {
        if (strcmp(departements[i], departement) == 0) {
            return i;
        }
    }
    return -1;
}


// Fonction pour afficher les étudiants d'un département spécifique
void afficherEtudiantsParDepartement() {
    int trouve = 0;
    char departement[50];

    printf("Donner le nom du departement: \n");
    scanf("%s",&departement);


    printf("\nListe des etudiants dans le departement %s:\n", departement);

    // Parcourir tous les étudiants
    for (int i = 0; i < nombre_etudiants; i++) {
        // Comparer le département de l'étudiant avec celui entré par l'utilisateur
        if (strcmp(etudiants[i].departement, departement) == 0) {
            // Afficher les détails de l'étudiant
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

// Fonction pour calculer et afficher la moyenne générale de chaque département
void calculerMoyenneParDepartement() {
    if (nombre_etudiants == 0) {
        printf("Aucun etudiant inscrit!\n");
        return;
    }

    // Variables pour stocker la somme des notes et le nombre d'étudiants par département
    float somme_notes[10] = {0};
    int nombre_etudiants_par_departement[10] = {0};

    // Variable pour la somme des moyennes des départements
    float somme_moyennes_departements = 0;
    int departements_comptes = 0; // Nombre de départements utilisés dans la moyenne

    // Parcourir tous les étudiants et regrouper les notes par département
    for (int i = 0; i < nombre_etudiants; i++) {
        int index_departement = trouverDepartement(etudiants[i].departement);
        if (index_departement != -1) {
            somme_notes[index_departement] += etudiants[i].note_generale;
            nombre_etudiants_par_departement[index_departement]++;
        }
    }

    // Afficher la moyenne de chaque département et calculer la somme des moyennes
    printf("\nMoyenne generale par departement:\n");
    for (int i = 0; i < nombre_departements; i++) {
        if (nombre_etudiants_par_departement[i] > 0) {
            float moyenne_departement = somme_notes[i] / nombre_etudiants_par_departement[i];
            printf("Departement %s: Moyenne = %.2f\n", departements[i], moyenne_departement);

            // Ajouter la moyenne de ce département à la somme des moyennes
            somme_moyennes_departements += moyenne_departement;
            departements_comptes++; // Incrémentation implicite du nombre de départements non vides
        }
    }

    // Calculer et afficher la moyenne générale de l'université si au moins un département a été compté
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

    // Tableau pour stocker le nombre d'étudiants par département
    int nombre_etudiants_par_departement[10] = {0};

    // Parcourir tous les étudiants et compter ceux de chaque département
    for (int i = 0; i < nombre_etudiants; i++) {
        int index_departement = trouverDepartement(etudiants[i].departement);
        if (index_departement != -1) {
            nombre_etudiants_par_departement[index_departement]++;
        }
    }

    // Afficher le nombre d'étudiants par département
    printf("\nNombre d'etudiants par departement:\n");
    for (int i = 0; i < nombre_departements; i++) {
        printf("Departement %s: %d etudiant(s)\n", departements[i], nombre_etudiants_par_departement[i]);
    }
}



// Fonction pour ajouter un étudiant
void ajouterEtudiant() {
    if (nombre_etudiants >= 100) {
        printf("Nombre maximum atteint!\n");
        return;
    }
    Etudiant e1;
    printf("Entrez le numero de l'etudiant: ");
    scanf("%d", &e1.numero);
    printf("Entrez le nom de l'etudiant: ");
    scanf("%s", e1.nom);
    printf("Entrez le prenom de l'etudiant: ");
    scanf("%s", e1.prenom);
    printf("Entrez la date de naissance (jj/mm/aaaa): ");
    scanf("%s", e1.date_naissance);
    printf("Entrez le departement de l'etudiant: ");
    scanf("%s", e1.departement);
    printf("Entrez la note generale de l'etudiant: ");
    scanf("%f", &e1.note_generale);

    // Ajouter le département s'il n'existe pas
    if (trouverDepartement(e1.departement) == -1) {
        if (nombre_departements < 10) {
            strcpy(departements[nombre_departements], e1.departement);
            nombre_departements++;
        } else {
            printf("Nombre maximum de départements atteint!\n");
        }
    }

    etudiants[nombre_etudiants] = e1;
    nombre_etudiants++;
    printf("Etudiant ajoute avec succes!\n");
}

// Fonction pour modifier un étudiant
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


// Fonction pour supprimer un étudiant
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

// Fonction pour afficher les détails d'un étudiant
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

// // Fonction pour calculer et afficher la moyenne générale
// void calculerMoyenneGenerale() {
//     if (nombre_etudiants == 0) {
//         printf("Aucun etudiant inscrit!\n");
//         return;
//     }

//     float somme = 0;
//     for (int i = 0; i < nombre_etudiants; i++) {
//         somme += etudiants[i].note_generale;
//     }

//     printf("Moyenne generale de l'universite: %.2f\n", somme / nombre_etudiants);
// }

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

// Fonction pour trier les étudiants par nom (ordre alphabétique)
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

// Fonction pour trier les étudiants par nom (ordre alphabétique) INVERSE
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


/*// Fonction pour trier les étudiants par moyenne générale (ordre décroissant)
void trierEtudiantsParMoyenne() {
    Etudiant temp;
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = i + 1; j < nombre_etudiants; j++) {
            if (etudiants[i].note_generale < etudiants[j].note_generale) {
                temp = etudiants[i];
                etudiants[i] = etudiants[j];
                etudiants[j] = temp;
            }
        }
    }

    printf("Etudiants tries par moyenne generale (ordre decroissant).\n");
}*/

// Fonction pour rechercher un étudiant par nom
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


// Fonction pour trier les étudiants par note générale (ordre décroissant)
void trierEtudiantsParNote() {
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = 0; j < nombre_etudiants - i - 1; j++) {
            if (etudiants[j].note_generale < etudiants[j + 1].note_generale) {
                // Échange des étudiants
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


// Fonction pour trier les étudiants par note générale (ordre croissant)
void trierEtudiantsParNoteInverse() {
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = 0; j < nombre_etudiants - i - 1; j++) {
            if (etudiants[j].note_generale < etudiants[j + 1].note_generale) {
                // Échange des étudiants
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

// Fonction pour afficher les 3 étudiants ayant les meilleures notes
void afficherTop3Etudiants() {
    if (nombre_etudiants == 0) {
        printf("Aucun etudiant inscrit!\n");
        return;
    }

    // Trier les étudiants par note
    for (int i = 0; i < nombre_etudiants - 1; i++) {
        for (int j = 0; j < nombre_etudiants - i - 1; j++) {
            if (etudiants[j].note_generale < etudiants[j + 1].note_generale) {
                // Échange des étudiants
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }

    // Afficher les 3 étudiants avec les meilleures notes
    printf("\nLes 3 etudiants ayant les meilleures notes:\n");
    for (int i = 0; i < 3 && i < nombre_etudiants; i++) {
        printf("%d. %s %s, Note: %.2f, Departement: %s\n",
               i + 1, etudiants[i].prenom, etudiants[i].nom, etudiants[i].note_generale, etudiants[i].departement);
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
        printf("6. Rechercher un étudiant \n");
        printf("7. Trier les étudiants  \n");

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
                    scanf(" %d",&a);

            switch(a){
                case 1:
                    supprimerEtudiant();
                    break;
                case 2:
                    modifierEtudiant();
                break;
                default:
                printf("Retour au menu!\n");
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
                    printf(" 1- Afficher le nombre total des etudiants inscrits.\n ");
                    printf("2- Afficher le nombre des etudiants dans chaque departement.\n ");
                    printf("3- Afficher les etudiants ayant une moyenne generale supérieure à un certain seuil.\n ");
                    printf("4- Afficher les 3 etudiants ayant les meilleures notes.\n ");
                    printf("5- Afficher le nombre des etudiants ayant reussi dans chaque departement. \n ");
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
                default:
                printf("Retour au menu!\n");
            }

                }while(b!=0);
            break;

            case 6:
                do {
                    printf(" 1- Rechercher un étudiant par son nom\n ");
                    printf("2- Afficher la liste des étudiants inscrits dans un département spécifique\n ");
                    scanf(" %d",&c);

            switch(c){
                case 1:
                    rechercherEtudiant();
                    break;
                case 2:
                    afficherEtudiantsParDepartement();
                break;
                default:
                printf("Retour au menu!\n");
            }
                }while(c!=0);
                break;
            case 7:
                do {
                    printf(" 1- Tri alphabétique des étudiants en fonction de leur nom de A à Z \n ");
                    printf("2- Tri alphabétique des étudiants en fonction de leur nom de Z à A\n ");
                    printf("3- Tri des étudiants par moyenne générale, du plus élevé au plus faible \n ");
                    printf("4- Tri des étudiants par moyenne générale, du plus faible au plus élevé \n ");
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
                default:
                printf("Retour au menu!\n");
            }
                }while(d!=0);
                break;

            case 0:
                printf("Vous avez quitte le programme!\n");
                break;
            default:
                printf("Retour au menu!\n");
        }
    } while (choix != 0);

    return 0;
}
