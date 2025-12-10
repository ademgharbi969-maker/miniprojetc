# 📱 Réseau Social Simplifié | Simplified Social Network

[![Langage: C](https://img.shields.io/badge/langage-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Sujet: Structures de Données](https://img.shields.io/badge/sujet-Structures%20de%20Données-orange.svg)](https://fr.wikipedia.org/wiki/Structure_de_donn%C3%A9es)

## 📖 Table des Matières | Table of Contents
- [Aperçu](#-aperçu-du-projet--project-overview)
- [Fonctionnalités](#-fonctionnalités--features)
- [Structure des Données](#️-structure-des-données--data-structures)
- [Exécution](#-comment-exécuter--how-to-run)
- [Menu](#️-menu-principal--main-menu)

## 🎯 Aperçu du Projet | Project Overview
Simulation de réseau social en C implémentant plusieurs structures de données (ABR, listes chaînées, piles). Projet éducatif développé pour maîtriser la gestion mémoire et les pointeurs.

**Fichier source principal :** `resau.c`

## ✨ Fonctionnalités | Features
- 👥 **Gestion des utilisateurs** (ajout, suppression, recherche)
- 🤝 **Relations sociales** (amis, abonnements)
- 💬 **Publications** avec horodatage
- 📰 **Fil d'actualité** personnalisé
- 📊 **Statistiques** et recommandations d'amis
- 💾 **Sauvegarde automatique** (fichiers binaires et texte)

## 🏗️ Structure des Données | Data Structures
| Structure | Implémentation | Usage |
|-----------|----------------|-------|
| Utilisateurs | ABR (Arbre Binaire de Recherche) | Stockage efficace |
| Amis/Abonnements | Listes chaînées | Relations sociales |
| Publications | Pile (LIFO) | Messages récents en premier |
| Fil d'actualité | Liste triée par temps | Flux chronologique |

## 🚀 Comment Exécuter | How to Run
```bash
# Compilation (notez le nom de fichier : resau.c)
gcc -o reseau_social resau.c

# Exécution
./reseau_social
=== RÉSEAU SOCIAL SIMPLIFIÉ ===
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
miniprojetc/
├── resau.c                    # Code source principal
├── README.md                 # Ce fichier (documentation)
├── .gitignore               # Configuration Git
├── utilisateurs.bin         # Fichier binaire généré
└── relations.txt            # Fichier texte généré
# Avec tous les avertissements
gcc -Wall -o reseau_social resau.c

# Ou avec support C99
gcc -std=c99 -o reseau_social resau.c