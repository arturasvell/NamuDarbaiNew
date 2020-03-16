# Namų darbų sistema
Ši programa saugo duomenis apie mokinius:
1. Jų vardą;
2. Jų pavardę;
3. Jų namų darbų rezultatus
4. Jų egzamino rezultatus
Iš šių duomenų programa apskaičiuoja **medianą** arba **vidurkį** (*pasirinktinai*) bei išveda duomenis į ekraną
# Releasai
- **v0.1** Pirmoji programos versija, yra dvi implementacijos: naudojant *C masyvus* ir *std::vector*. Realizuotas paprastas *exception handling*
- **v0.1.1** Pataisytas *medianos/vidurkio* pasirinkimas, sutvarkytas formatavimas
- **v0.1.2** Pridėtas atsitiktinis skaičių generavimas
- **v0.2** Pridėta galimybė nuskaityti duomenis iš failo, duomenys rūšiuojami pagal studentų vardą ir pavardę, kodas išskaidytas į tris failus (*logic.cpp, logic.h ir main.cpp*), pridėtas paprastas *exception handling*
- **v0.3** Pridėtas failų generavimas, rezultatų rikiavimas į "galvočius" ir "nuskriaustuosius" pagal galutinį balą, failo pavadinimo pasirinkimas, kelių failų nuskaitymas
- **v0.4.1** Pridėtas benchmarking - kiekvieno failo generavimas, rūšiavimas, spausdinimas ir kiekvieno šio proceso trukmės skaičiavimas
- **0.5** Ištestuota programos sparta su vektoriais

# Kaip naudotis programa
- Pasirinkti, ar generuoti failus, ar skaityti esamus failus
- Pasirinkti, kiek failų skaityti
- Laukti

# Programos kompiliavimo gidas (LINUX)
- Paleisti makefile su komanda **make**
- Enjoy
# Programos kompiliavimo gidas (WINDOWS - CODEBLOCKS)
- Sukompiliuoti programą, paleidus CBP failą (su c++14 standartu)
-Enjoy
