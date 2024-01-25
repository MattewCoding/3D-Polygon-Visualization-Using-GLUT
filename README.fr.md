# 3D Polygon Visualization Using GLUT
[![fr](https://img.shields.io/badge/lang-en-en)](https://github.com/MattewCoding/3D-Polygon-Visualization-Using-GLUT/blob/main/README.md)

En utilisant GLUT (basé sur C++), j'ai créé un programme qui permet de visualiser quatre types de polygones différents.

## Table des matières

- [3D Polygon Visualization Using GLUT](#project-name)
  - [Table des matières](#table-des-matières)
  - [Description](#description)
  - [Caractéristiques](#caractéristiques)
  - [Démarrage](#démarrage)
    - [Prérequis](#prérequis)
    - [Installation](#installation)
  - [Utilisation](#utilisation)
  - [Licence](#licence)
  - [Remerciements](#remerciements)

## Description

Dans le cadre de mes cours à l'université, on m'a demandé d'utiliser GLUT pour visualiser une sphère, et de pouvoir la modifier selon les 3 axes. Au fur et à mesure que le projet avançait, on m'a demandé de faire la même chose pour une superquadrique, un tore et un cylindre. C'est ce que j'ai fait.

## Caractéristiques

- Visualisation de 4 polygones différents
  - Une sphère
  - Une superquadrique
  - Un tore
  - Un cylindre
- Modifier les différents polygones
  - Avec l'étirement
  - Avec le déplacement
  - En le faisant pivoter
- Passer d'un maillage en triangle à un maillage en rectangle

## Démarrage

Pour démarrer ce projet, suivez les étapes suivantes :

### Prérequis

Avant d'exécuter le projet, assurez-vous que les prérequis suivants sont installés :

- [Compilateur C++](https://isocpp.org/get-started) : Installez un compilateur C++ compatible avec votre plate-forme.
- [Bibliothèque GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php) : Téléchargez et installez la bibliothèque GLUT pour votre système d'exploitation.

Alternativement, installez un IDE capable de compiler des projets C++/GLUT. J'ai utilisé CodeBlocks, je le recommande donc.
- [CodeBlocks](https://www.codeblocks.org/downloads/) : Un IDE

### Installation
Vous pourriez probablement utiliser git clone mais je ne l'ai jamais utilisé, donc si vous savez comment faire, allez-y, mais sinon je recommande de télécharger le fichier zip en cliquant sur le bouton "Code" et ensuite sur le bouton "Download ZIP".

## Utilisation
Instructions are explained in the console, but for completeness sake:
- Generale
  - P: Forme suivante
  - O: Forme precedente
  - M: Basculer entre la maille carree et la maille triangulaire
  - L: Des/activer la rotation
- Deplacements
  - Z: Vers le haut
  - Q: Vers la gauche
  - S: Vers le bas
  - D: Vers la droite
  - A: Dans axe Z vers l'avant
  - E: Dans axe Z vers l'arriere
- Rotation
  - W: Rotation vers la gauche sur le plan XY
  - X: Rotation vers la droite sur le plan XY
  - C: Rotation vers l'avant sur le plan YZ
  - V: Rotation vers l'arriere sur le plan YZ
  - B: Rotation vers la gauche sur le plan XZ
  - N: Rotation vers la droite sur le plan XZ
- Mise a l'echelle (ou, pour la superquadrique, modification des exposants de son equation)
  - R : Augmenter l'echelle du polygone sur l'axe X
  - F : Diminuer l'echelle du polygone sur l'axe X
  - T : Augmenter l'echelle des polygones sur l'axe des Y
  - G : Diminuer l'echelle des polygones sur l'axe des Y
  - Y : Augmenter l'echelle des polygones sur l'axe Z
  - H : Diminuer l'echelle du polygone sur l'axe Z
- Tore
  - U: Augmenter le rapport
  - J: Diminuer le rapport

## Licence

La licence de ce projet est distribuée sous la [Licence MIT](LICENSE). 

## Remerciements

Merci aux pages Wikipedia, pour avoir fourni les équations paramétriques des formes, à mon professeur, pour m'avoir suggéré ce sujet de projet, et naturellement, à la bibliothèque GLUT, pour avoir rendu cette visualisation possible.
