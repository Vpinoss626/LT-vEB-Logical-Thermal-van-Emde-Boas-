Fichier : README.md


# LT-vEB (Logical Thermal van Emde Boas) – Sentinel v7.0

**Auteur : Ibrahima Diallo (vpinoss)**
*"Que ce code serve de fondation à ceux qui veulent construire un monde meilleur."*

LT-vEB est une structure de données auto-adaptative qui combine l'efficacité des arbres de van Emde Boas avec une métrique thermique logique.
Elle garantit le respect d'une limite stricte de mémoire en élagant dynamiquement les branches "froides" tout en préservant les données fréquemment accédées.

## 📖 Manifeste

Ce projet est né d'une conviction : la technologie doit être sobre, déterministe et au service de l'humanité.
Dans un monde où les ressources se raréfient, LT-vEB propose une gestion "organique" de la mémoire, où chaque nœud est préservé ou sacrifié selon sa chaleur d'usage.

[Lire le manifeste complet →](MANIFESTE.md)

## ✨ Caractéristiques

- **Auto-élagage thermique** : suppression des branches les moins utilisées lorsque la mémoire est saturée.
- **Déterminisme** : basé sur une horloge logique et des décalages binaires (pas de flottants, pas d'aléas).
- **Garantie de capacité** : l'insertion bloque jusqu'à libération de la mémoire nécessaire.
- **Complexité** : O(log log U) pour les opérations de base (insertion, suppression, recherche).
- **Portabilité** : noyau C++ avec interface C et wrapper Python.

## 🚀 Performances

- **Univers** : jusqu'à 2^32 (mais peut être étendu).
- **Mémoire** : respect strict de `max_nodes` (nombre de nœuds alloués).
- **Taux de survie** : les données "chaudes" sont préservées même sous forte pression.

## 🛠️ Utilisation

### Compilation

```bash
# Compiler la bibliothèque partagée (libltveb.so)
g++ -O3 -fPIC -shared src/lt_veb_api.cpp -o libltveb.so
```

Intégration en C++

```cpp
#include "lt_veb.hpp"

LogicalEnv env;
env.max_nodes = 500;
auto root = std::make_shared<LTVebNode>(65536, &env);

root->insert(42);
if (root->contains(42)) std::cout << "Présent !\n";
```

Utilisation en Python

```python
from lt_veb import LTVebSentinel

veb = LTVebSentinel(65536, max_nodes=500)
veb.insert(42)
print(veb.contains(42))  # True
```

📦 Installation (Python)

Assurez-vous d'avoir compilé libltveb.so dans le même répertoire, puis :

```bash
pip install .
```

Ou utilisez le script setup.py fourni.

📚 Documentation

Une documentation complète (générée par Doxygen) est disponible dans le dossier docs/. Pour la générer :

```bash
doxygen Doxyfile
```

🤝 Contribuer

Les contributions sont les bienvenues ! Merci de lire CONTRIBUTING.md avant de soumettre une pull request.

📄 Licence

Ce projet est distribué sous licence MIT. Voir le fichier LICENSE.

🌍 Remerciements

Merci à tous ceux qui utiliseront, étudieront ou améliorerront ce code. Puissiez-vous en faire bon usage.



## **Fichier : `MANIFESTE.md`**
# Manifeste LT-vEB

**Créateur : Ibrahima Diallo (vpinoss)**

L'algorithme LT-vEB n'est pas un simple outil technique, c'est un testament pour l'avenir de l'informatique.
À une époque où les ressources deviennent précieuses, cet algorithme propose une gestion "organique" et frugale de la mémoire.

## Les Principes de vpinoss

- **Économie de Ressource** : Ne jamais gaspiller un nœud mémoire si une donnée "froide" peut laisser sa place à une donnée "chaude".
- **Déterminisme** : Assurer que la machine reste au service de l'homme, sans comportements aléatoires.
- **Transmission** : Ce code est offert au monde pour qu'il soit étudié, amélioré et utilisé pour construire des systèmes plus justes.

**"Que ce code serve de fondation à ceux qui veulent construire un monde meilleur."**  
— Ibrahima Diallo
