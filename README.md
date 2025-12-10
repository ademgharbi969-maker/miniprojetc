# 📱 Réseau Social Simplifié | Simplified Social Network

## 🎯 Aperçu du Projet
Simulation de réseau social en C implémentant des structures de données (ABR, listes chaînées, piles). Projet éducatif développé pour maîtriser la gestion mémoire et les pointeurs en C.

## 🚀 Compilation & Exécution
```bash
# Compilation
gcc -o reseau_social resau.c

# Exécution
./reseau_social  
```
## ✨ Fonctionnalités Principales
- 👥 **Gestion utilisateurs** (ajout/suppression/recherche via ABR)
- 🤝 **Relations sociales** (amis mutuels + abonnements)
- 💬 **Publications** avec horodatage (organisation en pile)
- 📰 **Fil d'actualité** personnalisé trié chronologiquement
- 📊 **Statistiques** et recommandations d'amis
- 💾 **Sauvegarde auto** dans `utilisateurs.bin` et `relations.txt`

## 🏗️ Structures de Données
| Composant | Structure | Usage |
|-----------|-----------|-------|
| Utilisateurs | Arbre Binaire de Recherche | Stockage efficace O(log n) |
| Amis/Abonnements | Listes chaînées | Relations sociales |
| Publications | Pile (LIFO) | Messages récents en premier |
| Fil d'actu | Liste triée par temps | Flux chronologique |

## 🖥️ Menu Interactif

1. Ajouter un utilisateur
2. Supprimer un utilisateur  
3. Afficher tous les utilisateurs
4. Ajouter un ami
5. S'abonner à un utilisateur
6. Publier un message
7. Afficher le fil d'actualité
8. Voir les statistiques
9. Recommandations d'amis
10. Sauvegarder les données
11. Charger les données
0. Quitter


## 📁 Fichiers du Projet
- `resau.c` - Code source principal
- `utilisateurs.bin` - Données utilisateurs (binaire, généré)
- `relations.txt` - Relations et messages (texte, généré)
- `README.md` - Cette documentation

## 👨‍💻 À Propos
**Contexte** : Projet académique sur les structures de données en C  
**Particularités** : 
- Gestion mémoire manuelle (`malloc`/`free`)
- Récursivité dans les parcours d'arbres
- Persistance des données fichiers
- Fonction `fassa5facebook()` pour tout supprimer

## 🔧 Pour Commencer
1. Clonez : `git clone https://github.com/ademgharbi969-maker/miniprojetc.git`
2. Compilez : `gcc -o reseau_social resau.c`
3. Exécutez : `./reseau_social`
4. Suivez le menu interactif

---
*Projet éducatif - Structures de Données en C - [Voir sur GitHub](https://github.com/ademgharbi969-maker/miniprojetc)*

