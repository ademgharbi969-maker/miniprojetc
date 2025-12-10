#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOM 50
#define MAX_MSG 200
#define FICHIER_BINAIRE "utilisateurs.bin"
#define FICHIER_TXT "relations.txt"
//njareb f faza 3al github
//commit bl vs code
// Structure pour un message/publication
typedef struct Message {
    int message_id;
    char content[MAX_MSG];
    time_t temps;
    struct Message* next;
} Message;

// Structure pour une liste chaînée d'IDs
typedef struct Listch {
    int user_id;
    struct Listch* next;
} Listch;

// Structure pour un utilisateur
typedef struct User {
    int user_id;
    char name[MAX_NOM];
    Message* publications; // Pile des publications personnelles
    Listch* friends;     
    Listch* subscriptions; 
    struct User* left;
    struct User* right;
} User;

// Structure pour le fil d'actualité
typedef struct filact {
    int user_id;
    char user_name[MAX_NOM];
    Message* message;
    struct filact* next;
} filact;

User* createUser(int user_id, const char* name);
User* ajouterUser(User* root, int user_id, const char* name);
User* searchUser(User* root, int user_id);
User* deleteUser(User* root, int user_id);
User* findMin(User* root);
void freeUserLists(User* user);
void parcoursinfixe(User* root);

Listch* ajouteralist(Listch* head, int user_id);
Listch* removeFromList(Listch* head, int user_id);
int isInList(Listch* head, int user_id);
void afficherlist(Listch* head, const char* listName);
int addFriend(User* root, int user_id1, int user_id2);
int addSubscription(User* root, int subscriber_id, int target_id);

Message* createMessage(const char* content);
int publishMessage(User* root, int user_id, const char* content);
filact* addTofilact(filact* head, int user_id, const char* user_name, Message* message);
filact* createfilact(User* root, int user_id, int max_messages);
void afficherfilact(filact* filact);
void freefilact(filact* filact);

void saveUsersBinary(User* root, FILE* file);
int saveUsersToFile(User* root, const char* filename);
int saveRelationsToFile(User* root, const char* filename);
User* chargerdonnes(const char* users_filename, const char* relations_filename);

void getUserStatistics(User* root, int user_id);
void recommendFriends(User* root, int user_id);
void Menuprincipal();
void fassa5facebook(User* root);


// Créer un nouvel utilisateur
User* createUser(int user_id, const char* name) {
    User* newUser = malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }
    
    newUser->user_id = user_id;
    strncpy(newUser->name, name, MAX_NOM - 1);
    newUser->name[MAX_NOM - 1] = '\0';
    newUser->publications = NULL;
    newUser->friends = NULL;
    newUser->subscriptions = NULL;
    newUser->left = NULL;
    newUser->right = NULL;
    
    return newUser;
}

// Insérer un utilisateur dans l'ABR
User* ajouterUser(User* root, int user_id, const char* name) {
    if (root == NULL) {
        return createUser(user_id, name);
    }
    
    if (user_id < root->user_id) {
        root->left = ajouterUser(root->left, user_id, name);
    } else if (user_id > root->user_id) {
        root->right = ajouterUser(root->right, user_id, name);
    }
    
    return root;
}

// Rechercher un utilisateur par ID
User* searchUser(User* root, int user_id) {
    if (root == NULL || root->user_id == user_id) {
        return root;
    }
    
    if (user_id < root->user_id) {
        return searchUser(root->left, user_id);
    }
    
    return searchUser(root->right, user_id);
}

User* findMin(User* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

void freeUserLists(User* user) {
    Listch* current = user->friends;
    while (current != NULL) {
        Listch* temp = current;
        current = current->next;
        free(temp);
    }
    
    current = user->subscriptions;
    while (current != NULL) {
        Listch* temp = current;
        current = current->next;
        free(temp);
    }
    
    Message* msgCurrent = user->publications;
    while (msgCurrent != NULL) {
        Message* temp = msgCurrent;
        msgCurrent = msgCurrent->next;
        free(temp);
    }
}

// Supprimer un utilisateur
User* deleteUser(User* root, int user_id) {
    if (root == NULL) return root;
    
    if (user_id < root->user_id) {
        root->left = deleteUser(root->left, user_id);
    } else if (user_id > root->user_id) {
        root->right = deleteUser(root->right, user_id);
    } else {
        // Nœud avec un seul enfant ou sans enfant
        if (root->left == NULL) {
            User* temp = root->right;
            freeUserLists(root);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            User* temp = root->left;
            freeUserLists(root);
            free(root);
            return temp;
        }
        
        // Nœud avec deux enfants
        User* temp = findMin(root->right);
        root->user_id = temp->user_id;
        strcpy(root->name, temp->name);
        root->right = deleteUser(root->right, temp->user_id);
    }
    
    return root;
}

void parcoursinfixe(User* root) {
    if (root != NULL) {
        parcoursinfixe(root->left);
        printf("ID: %d, Nom: %s\n", root->user_id, root->name);
        parcoursinfixe(root->right);
    }
}

// Ajouter un ID à une liste chaînée
Listch* ajouteralist(Listch* head, int user_id) {
    Listch* nouvnoeud = (Listch*)malloc(sizeof(Listch));
    if (nouvnoeud == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }
    nouvnoeud->user_id = user_id;
    nouvnoeud->next = head;
    return nouvnoeud;
}

// Supprimer un ID d'une liste chaînée
Listch* removeFromList(Listch* head, int user_id) {
    if (head == NULL) return NULL;
    
    if (head->user_id == user_id) {
        Listch* temp = head->next;
        free(head);
        return temp;
    }
    
    Listch* current = head;
    while (current->next != NULL && current->next->user_id != user_id) {
        current = current->next;
    }
    
    if (current->next != NULL) {

        Listch* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    
    return head;
}

// Vérifier si un ID est dans une liste
int isInList(Listch* head, int user_id) {
    Listch* current = head;
    while (current != NULL) {
        if (current->user_id == user_id) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Afficher une liste d'IDs
void afficherlist(Listch* head, const char* listName) {
    printf("%s: ", listName);
    Listch* current = head;
    while (current != NULL) {
        printf("%d", current->user_id);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// Ajouter un ami
int addFriend(User* root, int user_id1, int user_id2) {
    User* user1 = searchUser(root, user_id1);
    User* user2 = searchUser(root, user_id2);
    
    if (user1 == NULL || user2 == NULL) {
        return 0; // Utilisateur non trouvé
    }
    
    // Vérifier si l'amitié existe déjà
    if (isInList(user1->friends, user_id2)) {
        printf("Ces utilisateurs sont déjà amis.\n");
        return 1;
    }
    
    // Ajouter user2 à la liste d'amis de user1
    user1->friends = ajouteralist(user1->friends, user_id2);
    // Ajouter user1 à la liste d'amis de user2 (relation symétrique)
    user2->friends = ajouteralist(user2->friends, user_id1);
    
    return 1;
}

// Ajouter un abonnement
int addSubscription(User* root, int subscriber_id, int target_id) {
    User* subscriber = searchUser(root, subscriber_id);
    User* target = searchUser(root, target_id);
    
    if (subscriber == NULL || target == NULL) {
        return 0;
    }
    
    // Vérifier si l'abonnement existe déjà
    if (isInList(subscriber->subscriptions, target_id)) {
        printf("Abonnement déjà existant.\n");
        return 1;
    }
    
    subscriber->subscriptions = ajouteralist(subscriber->subscriptions, target_id);
    return 1;
}

// Créer un nouveau message
Message* createMessage(const char* content) {
    static int message_counter = 1;
    
    Message* newMessage = (Message*)malloc(sizeof(Message));
    if (newMessage == NULL) {
        printf("Erreur d'allocation mémoire pour le message\n");
        return NULL;
    }
    
    newMessage->message_id = message_counter++;
    strncpy(newMessage->content, content, MAX_MSG - 1);
    newMessage->content[MAX_MSG - 1] = '\0';
    newMessage->temps = time(NULL);
    newMessage->next = NULL;
    
    return newMessage;
}

// Publier un message (ajout en tête - pile)
int publishMessage(User* root, int user_id, const char* content) {
    User* user = searchUser(root, user_id);
    if (user == NULL) {
        return 0;
    }
    
    Message* newMessage = createMessage(content);
    if (newMessage == NULL) {
        return 0;
    }
    //empiler
    newMessage->next = user->publications;
    user->publications = newMessage;
    
    return 1;
}

// Ajouter un message au fil d'actualité 
filact* addTofilact(filact* head, int user_id, const char* user_name, Message* message) {
    filact* newItem = (filact*)malloc(sizeof(filact));
    if (newItem == NULL) {
        printf("Erreur d'allocation mémoire pour le filact\n");
        return head;
    }
    
    newItem->user_id = user_id;
    strncpy(newItem->user_name, user_name, MAX_NOM - 1);
    newItem->user_name[MAX_NOM - 1] = '\0';
    newItem->message = message;
    newItem->next = NULL;
    
    if (head == NULL || message->temps > head->message->temps) {
        newItem->next = head;
        return newItem;
    }  
    
    filact* current = head;
    while (current->next != NULL && current->next->message->temps > message->temps) {
        current = current->next;
    }
    
    newItem->next = current->next;
    current->next = newItem;
    
    return head;
}

// Construire le fil d'actualité d'un utilisateur
filact* createfilact(User* root, int user_id, int max_messages) {
    User* user = searchUser(root, user_id);
    if (user == NULL) {
        return NULL;
    }
    
    filact* filact = NULL;
    int message_count = 0;
    
    // Ajouter les publications des amis
    Listch* friend = user->friends;
    while (friend != NULL && message_count < max_messages) {
        User* friendUser = searchUser(root, friend->user_id);
        if (friendUser != NULL) {
            Message* msg = friendUser->publications;
            while (msg != NULL && message_count < max_messages) {
                filact = addTofilact(filact, friend->user_id, friendUser->name, msg);
                msg = msg->next;
                message_count++;
            }
        }
        friend = friend->next;
    }
    
    // Ajouter les publications des abonnements
    Listch* subscription = user->subscriptions;
    while (subscription != NULL && message_count < max_messages) {
        User* subUser = searchUser(root, subscription->user_id);
        if (subUser != NULL && !isInList(user->friends, subscription->user_id)) {
            Message* msg = subUser->publications;
            while (msg != NULL && message_count < max_messages) {
                filact = addTofilact(filact, subscription->user_id, subUser->name, msg);
                msg = msg->next;
                message_count++;
            }
        }
        subscription = subscription->next;
    }
    
    return filact;
}

// Afficher le fil d'actualité
void afficherfilact(filact* fil) {
    if (fil == NULL) {
        printf("Aucune publication dans votre fil d'actualité.\n");
        return;
    }
    
    printf("\n=== FIL D'ACTUALITÉ ===\n");
    filact* current = fil;
    int count = 1;
    
    while (current != NULL) {
        printf("%d. [%s] @%d: %s\n", count++, current->user_name, 
               current->user_id, current->message->content);
        printf("   Publié le: %s", ctime(&current->message->temps));
        current = current->next;
    }
    printf("======================\n");
}

// Libérer le fil d'actualité
void freefilact(filact* fil) {
    while (fil != NULL) {
        filact* temp = fil;
        fil = fil->next;
        free(temp);
    }
}

void saveUsersBinary(User* root, FILE* file) {
    if (root == NULL) return;
    
    // Sauvegarder les données de base de l'utilisateur
    fwrite(&root->user_id, sizeof(int), 1, file);
    fwrite(root->name, sizeof(char), MAX_NOM, file);
    saveUsersBinary(root->left, file);
    saveUsersBinary(root->right, file);
}

int saveUsersToFile(User* root, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erreur: impossible de créer le fichier %s\n", filename);
        return 0;
    }
    
    saveUsersBinary(root, file);
    fclose(file);
    return 1;
}

// Sauvegarder les relations dans un fichier texte
int saveRelationsToFile(User* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur: impossible de créer le fichier %s\n", filename);
        return 0;
    }
    
    void saveUserRelations(User* user) {
        if (user == NULL) return;
        
        fprintf(file, "USER %d %s\n", user->user_id, user->name);
        
        Listch* friend = user->friends;
        while (friend != NULL) {
            fprintf(file, "FRIEND %d %d\n", user->user_id, friend->user_id);
            friend = friend->next;
        }
        
        Listch* subscription = user->subscriptions;
        while (subscription != NULL) {
            fprintf(file, "SUB %d %d\n", user->user_id, subscription->user_id);
            subscription = subscription->next;
        }
        
        Message* msg = user->publications;
        while (msg != NULL) {
            fprintf(file, "MSG %d \"%s\" %ld\n", user->user_id, 
                    msg->content, msg->temps);
            msg = msg->next;
        }
        
        fprintf(file, "END_USER %d\n", user->user_id);
        
        // lhnee recursivité
        saveUserRelations(user->left);
        saveUserRelations(user->right);
    }
    
    saveUserRelations(root);
    fclose(file);
    return 1;
}

// Charger les données
User* chargerdonnes(const char* users_filename, const char* relations_filename) {
    User* root = NULL;
    
    printf("Chargement des données...\n");
    
    // Charger les utilisateurs depuis le fichier binaire
    FILE* users_file = fopen(users_filename, "rb");
    if (users_file != NULL) {
        int user_id;
        char name[MAX_NOM];
        
        while (fread(&user_id, sizeof(int), 1, users_file) == 1) {
            if (fread(name, sizeof(char), MAX_NOM, users_file) == MAX_NOM) {
                root = ajouterUser(root, user_id, name);
            }
        }
        fclose(users_file);
        printf("Utilisateurs chargés depuis %s\n", users_filename);
    } else {
        printf("Aucun fichier d'utilisateurs trouvé. Démarrage avec une base vide.\n");
    }
    
    // Charger les relations depuis le fichier texte
    FILE* relations_file = fopen(relations_filename, "r");
    if (relations_file != NULL) {
        char line[500];
        char name[MAX_NOM];
        //while fgets matreturnich null
        while (fgets(line, sizeof(line), relations_file)) {//ta9ra star ml fichier w t7otou fi line w tzidk /n flekher
            int id1, id2;
            char content[MAX_MSG];
            long temps;
            
            if (sscanf(line, "USER %d %49[^\n]", &id1, name) == 2) {//ta9ra hat lin tal9a \n li zedtha fgets
                // Trouver ou créer l'utilisateur
                User* user = searchUser(root, id1);
                if (user == NULL) {
                    root = ajouterUser(root, id1, name);
                }
            }
            else if (sscanf(line, "FRIEND %d %d", &id1, &id2) == 2) {
                addFriend(root, id1, id2);
            }
            else if (sscanf(line, "SUB %d %d", &id1, &id2) == 2) {
                addSubscription(root, id1, id2);
            }
            else if (sscanf(line, "MSG %d \"%199[^\"]\" %ld", &id1, content, &temps) == 3) {
                User* user = searchUser(root, id1);
                if (user != NULL) {
                    Message* newMessage = malloc(sizeof(Message));
                    if (newMessage != NULL) {
                        static int msg_id = 1;
                        newMessage->message_id = msg_id++;
                        strncpy(newMessage->content, content, MAX_MSG - 1);
                        newMessage->content[MAX_MSG - 1] = '\0';
                        newMessage->temps = temps;
                        newMessage->next = user->publications;
                        user->publications = newMessage;
                    }
                }
            }
        }
        fclose(relations_file);
        printf("Relations chargées depuis %s\n", relations_filename);
    } else {
        printf("Aucun fichier de relations trouvé.\n");
    }
    
    return root;
}

// Statistiques d'un utilisateur
void getUserStatistics(User* root, int user_id) {
    User* user = searchUser(root, user_id);
    if (user == NULL) {
        printf("Utilisateur non trouvé.\n");
        return;
    }
    
    int friend_count = 0;
    Listch* friend = user->friends;
    while (friend != NULL) {
        friend_count++;
        friend = friend->next;
    }
    
    int sub_count = 0;
    Listch* sub = user->subscriptions;
    while (sub != NULL) {
        sub_count++;
        sub = sub->next;
    }
    
    int pub_count = 0;
    Message* msg = user->publications;
    while (msg != NULL) {
        pub_count++;
        msg = msg->next;
    }
    
    printf("\n=== STATISTIQUES de %s (ID: %d) ===\n", user->name, user_id);
    printf("Amis: %d\n", friend_count);
    printf("Abonnements: %d\n", sub_count);
    printf("Publications: %d\n", pub_count);
    printf("==============================\n");
}

// Recommander des amis 

void recommendFriends(User* root, int user_id) {
    User* user = searchUser(root, user_id);
    if (user == NULL) {
        printf("Utilisateur non trouvé\n");
        return;
    }
    
    printf("\n=== RECOMMANDATIONS D'AMIS pour %s ===\n", user->name);
    
    int recommendations[1000] = {0}; 
    
    // chouf tous les amis de l'utilisateur
    Listch* friend = user->friends;
    while (friend != NULL) {
        User* friendUser = searchUser(root, friend->user_id);
        if (friendUser != NULL) {
            // Parcourir les amis de chaque ami
            Listch* friendOfFriend = friendUser->friends;
            while (friendOfFriend != NULL) {
                // ce n'est pas l'utilisateur et pas déjà ami
                if (friendOfFriend->user_id != user_id && 
                    !isInList(user->friends, friendOfFriend->user_id)) {
                    recommendations[friendOfFriend->user_id]++;
                }
                friendOfFriend = friendOfFriend->next;
            }
        }
        friend = friend->next;
    }
    
    // Afficher les recommandations
    int found = 0;
    for (int i = 0; i < 1000; i++) {
        if (recommendations[i] > 0) {
            User* recommended = searchUser(root, i);
            if (recommended != NULL) {
                printf("- %s (ID: %d) - %d ami(s) commun(s)\n", 
                       recommended->name, i, recommendations[i]);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("Aucune recommandation pour le moment.\n");
    }
    printf("===================================\n");
}

// libérer tout l'ABR
void fassa5facebook(User* root) {
    if (root != NULL) {
        fassa5facebook(root->left);
        fassa5facebook(root->right);
        freeUserLists(root);
        free(root);
    }
}

// Menu principal
void Menuprincipal() {
    printf("\n=== RÉSEAU SOCIAL SIMPLIFIÉ ===\n");
    printf("1. Ajouter un utilisateur\n");
    printf("2. Supprimer un utilisateur\n");
    printf("3. Afficher tous les utilisateurs\n");
    printf("4. Ajouter un ami\n");
    printf("5. S'abonner à un utilisateur\n");
    printf("6. Publier un message\n");
    printf("7. Afficher le fil d'actualité\n");
    printf("8. Voir les statistiques\n");
    printf("9. Recommandations d'amis\n");
    printf("10. Sauvegarder les données\n");
    printf("11. Charger les données\n");
    printf("0. Quitter\n");
    printf("Choix: ");
}



int main() {
    User* root = NULL;
    int choice, user_id, user_id2;
    char name[MAX_NOM];
    char content[MAX_MSG];
    
    printf("Bienvenue dans le réseau social simplifié!\n");
    
    // Charger les données au démarrage
    root = chargerdonnes(FICHIER_BINAIRE, FICHIER_TXT);
    
    do {
        Menuprincipal();
        if (scanf("%d", &choice) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // Vider le buffer
            continue;
        }
        getchar(); 
        
        switch (choice) {
            case 1:
                printf("ID de l'utilisateur: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                getchar();
                printf("Nom de l'utilisateur: ");
                if (fgets(name, MAX_NOM, stdin) == NULL) {
                    printf("Erreur de lecture du nom.\n");
                    break;
                }
                name[strcspn(name, "\n")] = 0; 
                
                if (searchUser(root, user_id) != NULL) {
                    printf("Erreur: un utilisateur avec cet ID existe déjà.\n");
                } else {
                    root = ajouterUser(root, user_id, name);
                    printf("Utilisateur ajouté avec succès.\n");
                }
                break;
                
            case 2:
                printf("ID de l'utilisateur à supprimer: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                if (searchUser(root, user_id) == NULL) {
                    printf("Erreur: utilisateur non trouvé.\n");
                } else {
                    root = deleteUser(root, user_id);
                    printf("Utilisateur supprimé.\n");
                }
                break;
                
            case 3:
                printf("\n=== LISTE DES UTILISATEURS ===\n");
                if (root == NULL) {
                    printf("Aucun utilisateur dans le système.\n");
                } else {
                    parcoursinfixe(root);
                }
                printf("=============================\n");
                break;
                
            case 4:
                printf("ID du premier utilisateur: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                printf("ID du deuxième utilisateur: ");
                if (scanf("%d", &user_id2) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                if (addFriend(root, user_id, user_id2)) {
                    printf("Amitié ajoutée avec succès.\n");
                } else {
                    printf("Erreur: utilisateur(s) non trouvé(s).\n");
                }
                break;
                
            case 5:
                printf("ID de l'abonné: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                printf("ID de target: ");
                if (scanf("%d", &user_id2) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                if (addSubscription(root, user_id, user_id2)) {
                    printf("Abonnement ajouté avec succès.\n");
                } else {
                    printf("Erreur: utilisateur(s) non trouvé(s).\n");
                }
                break;
                
            case 6:
                printf("ID de l'utilisateur: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                getchar();
                printf("Contenu du message: ");
                if (fgets(content, MAX_MSG, stdin) == NULL) {
                    printf("Erreur de lecture du message.\n");
                    break;
                }
                content[strcspn(content, "\n")] = 0;
                if (publishMessage(root, user_id, content)) {
                    printf("Message publié avec succès.\n");
                } else {
                    printf("Erreur: utilisateur non trouvé.\n");
                }
                break;
                
            case 7:
                printf("ID de l'utilisateur: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                if (searchUser(root, user_id) == NULL) {
                    printf("Erreur: utilisateur non trouvé.\n");
                } else {
                    filact* filact = createfilact(root, user_id, 10);
                    afficherfilact(filact);
                    freefilact(filact);
                }
                break;
                
            case 8:
                printf("ID de l'utilisateur: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                getUserStatistics(root, user_id);
                break;
                
            case 9:
                printf("ID de l'utilisateur: ");
                if (scanf("%d", &user_id) != 1) {
                    printf("ID invalide.\n");
                    break;
                }
                recommendFriends(root, user_id);
                break;
                
            case 10:
                if (saveUsersToFile(root, FICHIER_BINAIRE) && 
                    saveRelationsToFile(root, FICHIER_TXT)) {
                    printf("Données sauvegardées avec succès.\n");
                } else {
                    printf("Erreur lors de la sauvegarde.\n");
                }
                break;
                
            case 11:
                fassa5facebook(root);
                root = chargerdonnes(FICHIER_BINAIRE, FICHIER_TXT);
                printf("Données chargées.\n");
                break;
                
            case 0:
                printf("Au revoir!\n");
                break;
                
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);
    
    // Sauvegarder les données avant de quitter
    if (saveUsersToFile(root, FICHIER_BINAIRE) && 
        saveRelationsToFile(root, FICHIER_TXT)) {
        printf("Données sauvegardées automatiquement.\n");
    }
    
    fassa5facebook(root);
    return 0;
}