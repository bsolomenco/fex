(A) Prima problema cu care m-am confruntat a fost modificarea in timp real a designului aplicatiei.

    - ABORDARE
    1) Initial am implementat partea de QT StyleSheet in fisierul style.qss iar ulterior am incarcat in resource file(.qrc).

    - EFECT
    2) Problema a aparut pentru ca chiar daca am integrat corect, modificarile se actualizau tot dupa restartarea aplicatiei.

    - SURSA PROBLEMEI
    3) Sursa problemei provenea de la locul in care executabilul citea fisierul .qss. El nu citea fisierul propriu-zis de pe disk si cel incarcat in momentul compilarii;

    - SOLUTIE
    4) Am folosit QFileSystemWatcher, care urmarea fisierul style.qss de pe disk. In momentul in care fisierul era modificat(iar modificarile erau salvate). Observatorul comunica cu aplicatia pentru a reincarca noul continut al fisierului .qss.

(B) Compararea fisierelor ascunse. Fisierele ascunse nu apareau in rezultatul comparatiei

- CAUZA - 
    1) Folosind QDir::entryInfoList(), implicit QDir este echivalentul cu "ls" fara "-a"
- SOLUTIE -
    2) Am folosit flagul QDir::Hidden 
    const auto flags = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden;

(C) Folosind VS code si CMake mi-a fost destul de dificil sa urmaresc procesul de debugg, callstack si call hierarchy


(D) Implementarea SearchDialog 

    - PROBLEMA
    1) UI-ul ingetat
        In momentul in care cautam in fisire mare interfata se bloca complet. 
    - CAUZA -
    2) QDirInterator rula sincron pe main thread. 

    -SOLUTIE-
    3) Am incarcat initial o abordare multi-threading insa am obtinut un undefined behavior in Qt deoarece widget-urile nu sunt thread-safe.
    Am renuntat la aceasta abordare si am mers pe o solutie single-thread insa cu un mic "arificiu":

        if (found % 50 == 0)
            QApplication::processEvents();
    La fiecare 50 de rezultate Qt proceseaza evenimentele aflate in panding astfel UI este responsive si am evitate probmela generate de multi-threading.

     PS: o sa mai caut imbunatatiri la aceasta solutie.