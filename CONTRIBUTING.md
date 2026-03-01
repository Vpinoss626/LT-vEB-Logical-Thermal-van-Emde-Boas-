Contribuer à LT‑vEB

Nous sommes ravis que vous souhaitiez contribuer à LT‑vEB ! Ce projet est né d'une vision : une informatique plus sobre, déterministe et humaine. Chaque contribution – qu'il s'agisse d'un rapport de bug, d'une suggestion, d'une amélioration du code ou de la documentation – est précieuse et participe à faire rayonner cette philosophie.

Merci de prendre le temps de lire ces quelques lignes avant de commencer.

---

🌟 Notre philosophie

Avant toute chose, nous vous invitons à lire le manifeste du projet. Il résume les valeurs qui animent LT‑vEB : économie de ressource, déterminisme et transmission. Dans vos contributions, nous vous encourageons à garder ces principes à l'esprit.

---

🐛 Signaler un bug

Si vous rencontrez un comportement inattendu ou une erreur :

1. Vérifiez que le problème n'a pas déjà été signalé dans les issues.
2. Ouvrez une nouvelle issue en utilisant le modèle prévu (si disponible) ou en décrivant clairement :
   · Le contexte (système, version du compilateur, étapes pour reproduire).
   · Le comportement observé et le comportement attendu.
   · Si possible, un extrait de code ou une trace d'exécution.
3. Soyez bienveillant : derrière chaque bug, il y a des humains qui cherchent à améliorer le projet.

---

💡 Proposer une amélioration

Vous avez une idée pour rendre LT‑vEB plus performant, plus simple à utiliser, ou plus robuste ? Génial !

1. Ouvrez d'abord une discussion : avant de coder, partagez votre idée dans une issue avec le label enhancement ou discussion. Expliquez le problème que vous souhaitez résoudre et comment vous envisagez de le faire.
2. Recueillez les retours : les mainteneurs et la communauté pourront vous aider à affiner votre proposition.
3. Codez en suivant les recommandations ci-dessous.

---

🛠️ Guide de soumission de code (Pull Request)

Vous souhaitez soumettre du code ? Suivez ces étapes :

1. Préparation

· Fork le dépôt et créez une branche dédiée à votre contribution (par exemple feature/amelioration-elagage ou fix/issue-42).
· Assurez-vous que votre code compile sans erreur avec les options -Wall -Wextra -Werror (ou l'équivalent pour votre environnement).
· Ajoutez des tests pour valider votre modification (voir la section « Tests » ci-dessous).
· Mettez à jour la documentation si nécessaire (commentaires Doxygen, README, etc.).

2. Normes de code

· Style : respectez le style existant (indentation 4 espaces, accolades sur la même ligne, etc.). Nous utilisons clang-format avec une configuration proche du style LLVM. Vous pouvez formater automatiquement avec :
  ```bash
  clang-format -i src/*.cpp include/*.hpp
  ```
· Nommage : variables et fonctions en snake_case, classes en PascalCase, constantes en UPPER_CASE.
· Commentaires : privilégiez un code auto-documenté, mais n'hésitez pas à ajouter des commentaires pour expliquer les parties délicates. Utilisez Doxygen pour les entêtes de fonctions publiques.
· Pas de régression : assurez-vous que tous les tests existants passent.

3. Tests

· C++ : les tests unitaires se trouvent dans tests/. Nous utilisons Google Test. Ajoutez vos tests dans un fichier existant ou créez-en un nouveau.
· Python : les tests sont dans tests/test_lt_veb.py et utilisent unittest. Lancez-les avec python -m unittest discover tests.

4. Soumettre la Pull Request

· Poussez votre branche sur votre fork.
· Ouvrez une Pull Request vers la branche main du dépôt principal.
· Décrivez clairement vos modifications : quel problème résolvent-elles, comment avez-vous testé, y a-t-il des points d'attention ?
· Référencez l'issue associée si elle existe (par exemple Closes #42).
· Restez disponible pour d'éventuelles questions ou demandes de modification.

---

📋 Code de conduite

Nous nous engageons à offrir un environnement respectueux et inclusif pour tous. En participant à ce projet, vous acceptez de respecter notre Code de Conduite (à rédiger si ce n'est pas déjà fait). En résumé : soyez courtois, évitez les attaques personnelles, et accueillez les différences d'opinion avec bienveillance.

---

❤️ Remerciements

Chaque contributeur, quelle que soit la taille de sa contribution, fait avancer LT‑vEB vers un monde numérique plus sobre et plus juste. Nous vous en remercions chaleureusement.

Que ce code serve de fondation à ceux qui veulent construire un monde meilleur.
– Ibrahima Diallo (vpinoss)
