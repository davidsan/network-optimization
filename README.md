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
