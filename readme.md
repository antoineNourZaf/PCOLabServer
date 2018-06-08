Description et choix de l’implémentation

Pour implémenter le threadpool, nous avons choisit d'en faire hériter de HoareMonitor.

Ainsi toute les gestions d'attente, de création de nouveau thread et de réveils passent par le threadpool. La classe RunnableLauncher hérite de QThread et sont les threads gérés par le threadpool. Afin que ces threads puisse lancer des Runnable (classe spécifié par les tests) nous avons une méthode assignRunnable ainsi le thread peut lancer une nouvelle gestion de requête. La classe RequestHandlerRunnable hérite de Runnable et est donc la classe concrète que noius utilisons pour gérer une requête.

ses différentes étapes

Pour cette partie nous avons donc dû remplacer la classe RequestHandlerThread par RequestHandlerRunnable puisque les threads devaient pouvoir gérer plusieurs requêtes.
Ensuite, il a fallut ajouter la classe ThreadPool et RunnableLauncher. 

l'implémentation n'a pas été spécialement difficile sauf pour la gestion des réveils et attentes depuis les les threads. car ceux-ci n'avaient pas accès aux méthode du moniteur de Hoare. Il a donc fallut créer des méthode public dans ThreadPool pour cette gestion externe.

la manière dont vous avez vérifié son fonctionnement

Pour vérifier le bon fonctionnement du système, nous avons lancé une quinzaine de fois les tests donné en s'assurant qu'il ne rate pas une seule fois. Nous avons aussi augmenté dans le test le nombre de requête pour voir si avec l'augmentation de la charge des problèmes de concurrence n'apparraissaient pas.

Questions/Réponses :

Quelle est la taille optimale du thread pool pour cette application ? Quels facteurs influencent
ce choix ?

Afin d'optimiser l'utilisation du processeur, le threadpool ne doit pas dépasser le nombre de threads logique du processeur utilisé afin d'éviter des changements de contextes inutiles. On peut donc utiliser la méthode QThread::idealThreadCount() pour connaître ce maximum. Il ne faut pas oublier que le thread principale, le dispatcher de thread ainsi que le dispatcheur de réponse auront aussi du travail pour chaque requête, cependant ce travail sera beaucoup moins conséquent et nous les considérons comme négligeable. 
Il serait intérressant de vérifier si les performances sont meilleurs en laissant un thread de disponible servant aux changement de context pour ces 3 threads "léger".

Que se passe-t-il maintenant lorsque que l’on inonde le serveur de requêtes ? Constatez-vous
une amélioration au niveau de la stabilité du serveur ? et qu’en est-il au niveau de
l’occupation mémoire, par rapport à la version d’un thread par requête ?

Le serveur désormais tiens le coup avec une grande charge de requête ce qui améliore donc sa stabilité. au niveau de la mémoire, nous utilisons beaucoup moins de ressource grâce aux recyclage des threads qui ne prolifèrent donc plus au rythme des requête.