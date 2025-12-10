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
# Compilation
gcc -o reseau_social main.c

# Exécution
./reseau_social