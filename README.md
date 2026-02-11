# MiniRT, un projet 42 de raytracer 
- MiniRT est un mini moteur de raytracing écrit en C. Le programme génère une image 3D à partir d’une description de scène (.rt) en utilisant les principes fondamentaux du ray tracing : rayons, intersections, éclairage et ombres.
- Ce miniRT apporte des fonctionnalites non demandees dans le sujet 42 mais qui rendent le programme plus agreable a manipuler, implementent des effets de lumiere supplementaires (cf. bonus perso).
- Ameliorations a notre initiative (projet realise en binome) qui ont permis d'explorer et d'approfondir des concepts mathematiques/physiques (quaternions, phenomene de refraction) et de prorgammation (buffer d'accumulation, threads pool, interface utilisateur).

# Fonctionnalites

- Objets supportés :
Sphère, Plan, Cylindre, Cône (bonus 42)

- Effets de lumiere :
Ombres portées, Reflets, Anti auto-intersection via un offset (EPS), Eclairage de Phong, lumiere diffuse / speculaire (bonus 42), Plusieurs lumières ponctuelles (bonus 42), Transparence / verre (bonus perso), Degrade de couleurs (bonus perso)

- Effets des materiaux
Reflexion, Rugosite, Gestion des normales pour bump maps (bonus 42), Textures (bonus 42), Effet checkerboard (bonus 42)

- Gestion de l'affichage
Affichage en temps réel via MiniLibX, Accumulation des pixels pour amelioration de la qualite image en continu (bonus perso), Interface utilisateur permettant de modifier camera et objets en temps reel (bonus perso), Gestion de la rotation des objets avec quaternions (bonus perso)

# COMPILATION

Version "Standard 42" (avec bonus 42 + Interface utilisateur)
- telecharger la Minilibx (https://github.com/42paris/minilibx-linux) dans le repertoire lib/mlx
- make
- ./miniRT "nom du fichier de scene a afficher"

Version multithread
- make bonus
- - ./miniRT "nom du fichier de scene a afficher"
- La version multithread necessite encore quelques ameliorations notamment pour regler les pb persistants d'acces concurrents a la scene (necessite que chaque thread ait sa propre copie de la scene),
mais aussi pour optimiser la coordination des threads entre les phases d'accumulation d'image et les phases de mise a jour de la scene apres modification.
Ce pb genere des artefacts au deplacement de la camera ou lors de la modification de la scene.
- On note une amelioration sensible de la fluidite de manipulation de la scene en temps reel.

# UI
//en mode "CAMERA" :
- rotation camera = click gauche + deplacement souris;
- translation camera :
              avant/arriere = scroll avant/arriere (axe z);
              haut/bas = w_key/s_key (axe y);
              camera gauche/droite = a_key/d_key (axe x);

//en mode "EDIT":
- selection objet = click gauche souris;
- resize objet = scroll avant/arriere souris;
- translation objets:
                haut/bas = w_key/s_key (axe y);
                gauche/droite = a_key/d_key (axe x);
                avant/arriere = fleche haut / fleche bas
- rotation objets: maintenir click gauche souris +
                axe x = q_KEY / e_KEY;
                axe y = a_KEY / d_KEY;
                axe z = z_KEY / c_KEY;
  
bascule mode "camera" <--> "edit" = m_key;
retour camera position initiale = r_key.

# Sources:
//Principes du ratracing:
 - https://euler.ac-versailles.fr/IMG/pdf/raytracing.pdf (francais);
 - https://raytracing.github.io/books/RayTracingInOneWeekend.html (english);
 - https://www.youtube.com/playlist?list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl
 - https://www.youtube.com/watch?v=gsZiJeaMO48
   
//Bases mathematiques:
- rappels trigonometriques : https://perso.liris.cnrs.fr/gilles.gesquiere/Teaching/Imagina/Cours05.pdf, https://perso.univ-rennes1.fr/sean.mcnamara/AppMath2/2.4_cylindriques_spheriques.pdf;
- calcul vectoriel (https://www.youtube.com/watch?v=4uuQh-J0D2c) (francais);
- produit vectoriel, produit mixte et interpretation geometrique (https://www.youtube.com/watch?v=Qi1stedji44) (francais);
- https://docs.gl/sl4/refract
- https://docs.gl/sl4/reflect
- https://fr.wikipedia.org/wiki/Ombrage_de_Phong
  
//Texture:
- https://anirudh-s-kumar.github.io/CG-Notes/texture_mapping/
- https://dogukannn.github.io/2024/12/12/ray-tracing-four.html
