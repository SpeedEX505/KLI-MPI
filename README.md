#Úloha KLI: maximální klika grafu


##Vstupní data:
* G(V,E) = jednoduchý souvislý neorientovaný neohodnocený graf o n uzlech a m hranách
* n = přirozené číslo představující počet uzlů grafu G, n >= 5
* k = přirozené číslo řádu jednotek představující průměrný stupeň uzlu grafu G, n >= k >= 3
* r = kladné reálné číslo, 0 < r < 1


##Doporučení pro algoritmus generování G:
Použijte generátor grafu s volbou typu grafu „-t AD“, který vygeneruje souvislý neorientovaný neohodnocený graf.


##Definice:
Klika grafu G je jeho maximální úplný podgraf, t.j. takovy podgraf, ktery není obsažen v žádném větším podgrafu. Velikost kliky je počet jejich vrcholů.


##Úkol:
Zjistit, zda graf G obsahuje kliku o velikosti alespoň (rovnou nebo větší) r * n a nalézt největší takovou kliku.


##Výstup algoritmu:
Seznam uzlů tvořící kliku, popřípadě konstatování, že klika neexistuje.


##Sekvenční algoritmus:
Sekvenční algoritmus typu BB-DFS s hloubkou stavového stromu omezenou na n. Cena řešení, která se maximalizuje, je velikost kliky vzhledem k zadané podmínce. Horní mez ceny řešení není známa. Algoritmus skončí, až prohledá celý stavový prostor.

##Meze:
* Dolní mez je 2, pokud graf obsahuje aspon 1 hranu.
* Horní mez není známá, ale dá se odhadnout takto: pokud G obsahuje kliku o velikosti x, pak musí obsahovat x vrcholů se stupněm větším nebo rovným x-1.

##Paralelní algoritmus:
Paralelní algoritmus je typu PBB-DFS-V.


