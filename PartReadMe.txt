U fajlu "part.h" dato je zaglavlje koje je potrebno ukljuciti u projekat.
Citava aplikacije treba da bude iskljucivo native. Biblioteka je prevedena u Debug rezimu.

Pri kreiranju objekta particije potrebno je proslediti naziv fajla koji sadrzi podatke o disku.
Primer takvog fajla je fajl "i1.ini". U prvoj liniji zapisan je naziv fajla koji ce cuvati sve
podatke (oponasati hard disk). U sledecoj liniji je velicina particije u klasterima.
Dati primer je samo pokazni i za rad bi trebalo obezbediti particiju velicine bar 10MB.
Sama promjena velicine particije ce po potrebi prosiriti fajl koji oponasa disk (u ovom slucaju
"disk1.dat"), ali nece kreirati fajl ukoliko isti ne postoji.

U javnom testu svi parametri su unpred definisani i potrebni fajlovi se nalaze u direktorijumu
resources.