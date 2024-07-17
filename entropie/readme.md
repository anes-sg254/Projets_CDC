## 1. Notion d'entropie

1.1) L'entropie maximal est 8 dans le cas ou tout les symboles ont la même probabilitée 
Cette entropie est atteinte pour un fichier qui liste les caractères par exemple, ou un fichier ou les caractères sont totalement aléatoires 
Dans un fichier composé de texte certains symboles auront une probablité plus elevée que d'autres, l'entropie max n'est pas atteinte.

## 2. Mise en oeuvre du calcul de l'entropie 

2.7) L'entropie est le nombre de bits requis pour coder chaque symboles de S dans le meilleur cas.
Dans le cas d'un codage optimal le fichier est donc de longueur : Entropy(S) x nb(s) 
(Entropie fois le nombre de symboles)

## Question 2.8:
Pour calculer le pourcentage de réduction de la taille du fichier initial que permettrait un codage optimal, nous pouvons utiliser la formule suivante :

Pourcentage de réduction = (1 - (Taille minimale du fichier / Taille du fichier initial)) * 100

Dans notre cas, la taille minimale du fichier correspond à l'entropie multipliée par le nombre de symboles, et la taille du fichier initial est donnée par la variable file_size.

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

## Explication: 
Les différences observées entre les différents types de fichiers sont principalement dues à leur contenu intrinsèque et à leur format de stockage.

Vidéo (MP4) : La vidéo markdown_video.mp4 a une taille relativement importante de 383631 octets, ce qui est typique des fichiers vidéo. Elle présente une entropie de 7.96 bits/octet, ce qui suggère une certaine complexité dans les données vidéo, mais avec une certaine redondance permettant une compression efficace.

Audio (MP3) : L'audio markdown_audio.mp3 a une taille plus petite de 68064 octets par rapport à la vidéo, mais une entropie similaire de 7.96 bits/octet. Cela peut être dû à la compression efficace des données audio dans le format MP3 tout en préservant la qualité audio.

Fichier HTML : Le fichier markdown.html a une taille de 46045 octets avec une entropie de 5.31 bits/octet. Les fichiers HTML contiennent généralement du texte, des balises et des métadonnées, ce qui explique une entropie relativement plus faible par rapport aux médias audiovisuels.

Image (PNG) : L'image markdown_logo.png est relativement petite avec 8692 octets mais présente une entropie élevée de 7.89 bits/octet. Cela peut être dû à la complexité des détails dans l'image ou à la présence de certaines zones de couleur qui ne sont pas facilement compressibles.

En résumé, les différences entre les types de fichiers résident dans la nature de leur contenu (texte, audio, vidéo, image) ainsi que dans les algorithmes de compression spécifiques utilisés pour chaque format. Les médias audiovisuels ont tendance à avoir une entropie plus élevée en raison de leur contenu multimédia complexe, tandis que les fichiers texte peuvent avoir une entropie plus faible en raison de la structure régulière du texte. Les formats de compression spécifiques jouent également un rôle crucial dans la taille finale des fichiers.
