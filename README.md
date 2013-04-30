Réorganisation d’un réseau de fibres optiques
=============================================

## Introduction
Une agglomération désire améliorer le réseau de fibres optiques de ses administrés.

Une première phase de travail va consister à reconstituer le plan du réseau. En effet, plusieurs opérateurs se partagent actuellement ce marché en possédant chacun quelques fibres des câbles du réseau. Le réseau ayant grossi régulièrement, il n'existe pas à ce jour de plan complet de ce réseau. En revanche, chaque opérateur connaît les tronçons de fibres optiques qu'il utilise dans le réseau. En partant de l'hypothèse qu'il y a au moins une fibre utilisée par câble, il est ainsi possible de reconstituer le réseau dans son intégralité.

Une deuxième phase de travail va consister à réorganiser les attributions de fibres de chacun des opérateurs. En effet, la répartition des fibres n'a jamais été remise en cause jusqu'ici : certains câbles sont sous-exploités au détriment d'autres sur-exploités. En fait, chaque opérateur possède une liste de paires de clients qu'il a relié l'un à l'autre par une chaîne de tronçons de fibres optiques. Comme les attributions de fibres optiques n'ont jamais été remises en cause, certaines chaînes sont très longues à cause de cette congestion. Ces problèmes de congestion et de longueurs excessives peuvent être résolus, ou tout du moins améliorés, en attribuant aux opérateurs des chaînes moins longues et mieux réparties dans le réseau.



## Exécution
```
### Phase 1 ###
$ ./main [file.cha/file.res]
$ ./convertres ../res/*.cha
$ ./converthash ../res/*.cha
$ ./convertabr ../res/*.cha
$ ./convertxfig ../*.res
$ ./converttimer  ../res/*.cha
### Phase 2 ###
$ ./convertchaine ../res/*.res
$ ./convertchainecsp ../res/*.res
$ ./chainestat *.cha
```

## Licence

(Licence MIT)

Copyright © David San

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
