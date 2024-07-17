## 2. Experiences

On a récupèré les mêmes fichiers que ceux du TP2. Pour compresser les fichiers, nous avons utilisé la commande :
./huffman -c fichierOriginal fichierOriginal.huf

Après avoir compressé les fichiers du TP précédent, nous avons eu deux options pour obtenir la taille en octets ou en (bits/octet) :

Avec la commande :
ls -l tests/fichierOriginal tests/fichierCompressé : Cette commande donne seulement la taille en octets.

./filentropy lib/fichierCompressé : Pour utiliser cette commande, nous avons de nouveau utilisé le TP précédent en faisant appel au fichier filentropy, tout en copiant les fichiers compressés dans le TP précédent.

Enfin, nous avons supprimé les fichiers utilisés, tout en vous laissant les liens pour le téléchargement.

## Fichiers récupérés en ligne

- **GitLab :** [https://gitlab.com/gitlab-org/gitlab/-/raw/master/doc/user/img/markdown_video.mp4]
- **GitLab :** [https://gitlab.com/gitlab-org/gitlab/-/raw/master/doc/user/img/markdown_audio.mp3]
- **GitLab :** [https://gitlab.com/gitlab-org/gitlab/-/blob/master/doc/user/markdown.md#inline-html]

- **GitLab :** [https://gitlab.com/gitlab-org/gitlab/-/raw/master/doc/user/img/markdown_logo.png]

## Informations sur les fichiers

| Nom du fichier           | Taille (octets) | Entropie (bits/octet) |
|--------------------------|-----------------|-----------------------|
| markdown_video.mp4       | 383631          | 7.96                  |
| markdown_audio.mp3       | 68064           | 7.96                  |
| markdown.html            | 46045           | 5.31                  |
| markdown_logo.png        | 8692            | 7.89                  |

## Informations sur les fichiers

| Nom du fichierCompréssé           | Taille (octets) | Entropie (bits/octet) |
|-----------------------------------|-----------------|-----------------------|
| markdown_video.huf                | 384252          |  7.99                 |
| markdown_audio.huf                | 69139           |  7.98                 |
| markdown.huf                      | 31290           |  7.84                 |
| markdown_logo.huf                 | 9882            |  7.72                 |

Dans l'analyse du tableau fourni, on constate que la taille des fichiers compressés diffère de la taille des fichiers d'origine. Voici quelques observations basées sur les résultats :

markdown_video.mp4 :
Taille d'origine : 383631 octets
Taille compressée : 384252 octets
L'augmentation de la taille après compression peut être due à plusieurs facteurs, tels que la complexité des données vidéo, la présence de données déjà compressées dans le fichier vidéo, ou même des limitations dans l'algorithme de compression utilisé.
markdown_audio.mp3 :
Taille d'origine : 68064 octets
Taille compressée : 69139 octets
La compression de fichiers audio peut être moins efficace que celle des fichiers texte en raison de la complexité des données audio et de la présence de données déjà compressées dans le fichier MP3.
markdown.html :
Taille d'origine : 46045 octets
Taille compressée : 31290 octets
Dans ce cas, la compression semble avoir été plus efficace, ce qui est cohérent avec le fait que les fichiers texte peuvent souvent être compressés de manière plus efficace en raison de leur nature répétitive et prévisible.
markdown_logo.png :
Taille d'origine : 8692 octets
Taille compressée : 9882 octets
Bien que PNG soit un format compressé, la taille peut parfois augmenter après la compression, surtout si le fichier contient déjà des données compressées ou si le contenu ne se prête pas bien à la compression.
En conclusion, les différences observées dans la taille des fichiers compressés par rapport à la taille d'origine peuvent être dues à la nature inhérente des données, à la complexité des fichiers, ainsi qu'à l'efficacité de l'algorithme de compression appliqué.
