# SuperMarioPro2

## Les dues noves classes
Per a la tercera entrega les dues classes principals que s'han implementat són 'Block' i 'Interactable'. 

### class Block
Block afegeix alguns dels blocs originals del SMB, com el bloc de totxto, el bloc interrogant, i altres.
El jugador pot interactuar amb aquests (si es compleixen les condicions) saltant i xocant-s'hi des de sota.

### class Interactable
La classe 'Interactable' afegeix objectes diversos que interaccionen amb el jugador. Afegeix les monedes que surten dels blocs, els bolets i els 'goombas' del SMB original, i també la bandera que hi ha al final del mapa.
Alguns d'aquests objectes aparèixen quan s'interactua amb els blocs. Per exemple, del bloc interrogant en poden sortir monedes o bolets. D'altra banda el goomba o la bandera ja es troben al nivell.

## Modificacions adicionals
D'altra banda, també s'ha afegit un menú principal al que es retorna en prèmer 'Escape' des de dins del joc, quan el mario mor o quan s'arriba al final del nivell i es toca la bandera.

A banda d'això s'han fet moltes modificacions a les classes ja existents per tal de crear les noves funcionalitats i també s'ha creat un simple nivell per a mostrar-les.

Dit això, si que vull destacar el mòdul de text 'text.hh' que s'ha creat per al projecte: 

## Libreria nova: text.hh

Aquesta llibreria permet escriure text a la pantalla a partir de fonts ja creades.
Les fonts s'obtenen a partir de fitxers de text, amb una llista de matrius de strings, cada matriu representant el 'sprite' d'un caràcter. Després aquest text es pot pintar amb una paleta (un diccionari que diu a quin color es correspon cada string) i finalment ser dibuixat a la pantalla.

Hi ha dues fonts ja creades dins de la carpeta assets:
    'assets/6x6rounded.txt' i 'assets/6x10rounded.txt'. Al joc s'utilitza la 6x10rounded.

També hi ha la paleta de colors utilitzada i el charset (llista dels caràcters en el mateix ordre en el que apareix a la font)

Cal que per a l'execució del mario estigui present la carpeta "assets" al mateix directori que l'executable, ja que el programa llegeix la font un cop s'executa.

També he inclos un script simple fet amb python que vaig utilitzar per a generar de forma automatitzada la font a partir d'una imatge amb el bitmap dels caràcters.



## Vídeo de demostració
Finalment també he inclòs un petit vídeo mostrant el projecte i les noves mecàniques i objectes que he implemenetat.