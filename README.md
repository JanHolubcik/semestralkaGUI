# Territorial Data Analyzer / Analyzátor územných jednotiek (Data Structures)

This repository contains an academic project focused on the design, implementation, and analysis of custom data structures and algorithms. The application processes and analyzes demographic data of territorial units (municipalities, districts, regions) using a Windows Forms GUI.

---

## 🌐 Language / Jazyk
- [English Version](#english-version)
- [Slovenská Verzia](#slovenská-verzia)

---

## English Version

### 📝 Project Overview & Data Structures
The core of this application revolves around custom data structures, specifically **Sequence Tables**:
* **Sorted Sequence Table:** Used during the data loading phase. Since raw file data is not perfectly sorted, this structure allows fast lookups using binary search (Bisection) in `O(log n)` time to find parent territorial units (districts/regions).
* **Unsorted Sequence Table:** Used post-loading for processing. Data from the sorted table is transferred here to allow dynamic sorting using the internal `swap` method.

The graphical user interface (GUI) was built using **Windows Forms**.

### 🏗️ Architecture & UML Overview
* `Loader`: Handles data loading. Contains 4 Sorted Sequence Tables (one for each type of territorial unit) and the `loader()` method for parsing files.
* `Sorter`: Manages sorting operations. Uses a strategy pattern via methods like `sortByName()`.
* `Bisection`: Performs binary search to find a Territorial Unit (TU) by name. Can return a single match or multiple matches.
* `UzemnaJednotka` (Territorial Unit - TU): Holds all parsed attributes (education, age, age groups). Contains references to its parent TU and child TUs.
* `Criteria` (`Kritéria`): Evaluates specific attributes of TUs. `criterioUJ` inherits from base `criterio`. Used extensively during sorting and filtering.
* `Filters` (`Filtre`): Includes `fUJByValue`, `filterByInterval`, and `universalFilter` (which uses a virtual constructor for memory-safe criteria deletion). Uses a composite pattern (`compositeFilter`) to chain multiple filters together.

### ⏱️ Computational Complexity & Algorithms

#### Data Loading Hierarchy
1. **Municipalities (`obce.csv`):** Loaded first. Complexity: `O(N)`.
2. **Education/Age Data:** Loaded by code to match with the corresponding municipality. Complexity: `O(N log N)` (Binary search for the municipality).
3. **Districts:** Aggregates education and age data from its child municipalities. Complexity: `O(N^2)`.
4. **Regions:** Aggregates data from its child districts. Complexity: `O(N^2)`.

#### Core Algorithms
* **Point Search (Bisection):** Loads a specific TU type into an unsorted table, sorts it, and performs binary search by name. Complexity: `O(log N)`.
* **Partial Search:** Fallback string matching if point search fails. Scans all TUs. Complexity: `O(N * K)` (where K is string length).
* **Filtering:** Linear scan of all TUs based on composite filters. Complexity: `O(N)`.
* **Sorting (Quicksort):** Used for sorting data tables. Complexity: `O(N log N)` (average case).
* **Min/Max Selection:** Linear scan to find the best/worst values. Complexity: `O(N)`.

### 📊 Applied Criteria & Queries
The application supports complex composite queries (Level 4 requirements), extracting data with specific complexities based on attributes like:
* Name (`O(1)`), Type (`O(1)`), Hierarchy Belonging
* Education count/share (`O(1)` to `O(N)`)
* Age intervals & demographic shares

**Example Complex Queries Supported:**
* Sort all districts in the Žilina region in ascending order by the share of men aged 20-40, filtered to show only those between 20-30%.
* Display the municipality in the Trenčín region with the lowest pre-productive age population.

### 📖 User Guide
* **Search Panel (Fig. 1 & 2):** Point and partial search inputs. Leaving it empty displays all records.
* **Sorting & Max/Min Panel (Fig. 3):** Used to sort the table (by name, education, age groups) or find extreme values. Works on both raw and filtered tables.
* **Filter Management (Fig. 4 & 5):** Interface to define and add filters. Includes validation alerts. Users can apply chained filters (`Filtruj tabuľku`) or reset them (`Resetuj filtre`).

---

## Slovenská Verzia

### 📝 Návrh aplikácie a použité údajové štruktúry
Základom aplikácie je práca s vlastnými implementáciami údajových štruktúr pre efektívne spracovanie demografických údajov:
* **Utriedená sekvenčná tabuľka (Sorted Sequence Table):** Využíva sa primárne pri načítaní dát. Keďže dáta v súboroch nie sú zoradené, tabuľka umožňuje rýchle vyhľadávanie pomocou bisekcie s časovou zložitosťou `O(log n)`. To je kľúčové pre rýchle priradenie obcí ku krajom a okresom.
* **Neutriedená sekvenčná tabuľka (Unsorted Sequence Table):** Používa sa po načítaní. Prvky z utriedenej tabuľky sa do nej prekopírujú, čo umožňuje dynamické triedenie tabuľky pomocou metódy `swap`.

Na grafické spracovanie platformy bol použitý framework **Windows Forms**.

### 🏗️ Architektúra a UML
* `Loader`: Slúži na načítanie dát zo súborov. Obsahuje 4 utriedené sekvenčné tabuľky pre každý typ územnej jednotky (ÚJ) a metódu `loader()`.
* `Sorter`: Zabezpečuje triedenie dát na základe zvolenej metódy (napr. `sortByName()`).
* `Bisection`: Vykonáva binárne vyhľadávanie podľa názvu. Vracia buď všetky nájdené ÚJ, alebo len jednu.
* `UzemnaJednotka`: Obsahuje atribúty zo súborov (vzdelanie, vek, vekové skupiny). Uchováva referencie na nadradenú ÚJ aj na podradené ÚJ.
* `Kritéria`: Obsahuje hierarchiu kritérií (`criterioUJ` dedí z `criterio`). Používajú sa pri vyhodnocovaní prvkov počas triedenia.
* `Filtre`: Zahŕňa `fUJByValue`, `filterByInterval` a `universalFilter`. Využíva návrhový vzor Composite (`compositeFilter`) na ukladanie viacerých filtrov. `universalFilter` využíva virtuálny konštruktor na bezpečné vymazanie kritérií z pamäte.

### ⏱️ Hierarchia načítania a výpočtová zložitosť

#### Proces načítania
1. **Obce (`obce.csv`):** Zložitosť `O(N)`.
2. **Vzdelanie a vek:** Načítava sa kód, podľa ktorého sa bisekciou hľadá príslušná obec. Zložitosť `O(N log N)`.
3. **Okresy:** Načítajú sa kódy a prechádzajú sa obce na sčítanie dát pod daný okres. Zložitosť `O(N^2)`.
4. **Kraje:** Načítajú sa kódy a sčítavajú sa dáta z príslušných okresov. Zložitosť `O(N^2)`.

#### Algoritmy a operácie
* **Bodové vyhľadávanie (Bisekcia):** Tabuľka sa utriedi a aplikuje sa bisekcia podľa názvu. Zložitosť `O(log N)`.
* **Čiastočné vyhľadávanie:** Aktivuje sa pri nenájdení exaktnej zhody. Prehľadáva výskyty podreťazcov v názvoch. Zložitosť `O(N * K)` (kde K je dĺžka hľadaného reťazca).
* **Filtrovanie:** Prechádzanie všetkých ÚJ. Zložitosť `O(N)`. Podporuje viacnásobné zreťazené filtre.
* **Triedenie (Quicksort):** Časová zložitosť pri ideálnom pivotovi je `O(N log N)`. Umožňuje triediť surové aj vyfiltrované dáta.
* **Výber maxima/minima (Najlepšie/Najhoršie):** Prechod cez celú tabuľku. Zložitosť `O(N)`.

### 📊 Použité kritéria a zložité dopyty (4. úroveň)
Aplikácia dokáže vyhodnocovať komplexné dopyty s parametrami ako typ ÚJ, príslušnosť k vyššiemu celku (`O(1)`), počet/podiel vzdelania a počet/podiel vekových intervalov (`O(N)`).

**Príklady implementovaných dopytov:**
* Zoraďte vzostupne všetky okresy Žilinského kraja podľa podielu mužov vo veku od 20 do 40 rokov, kde je ich podiel medzi 20 – 30 %.
* Vypíšte informácie o okrese v Trnavskom kraji, ktorý má najviac obyvateľov v produktívnom veku.
* Vypíšte informácie o obci v Trenčianskom kraji, ktorá má najmenej obyvateľov v predproduktívnom veku.

### 📖 Používateľská príručka (UI)
* **Obr. 1 a Obr. 2 (Vyhľadávanie):** Slúži na bodové a čiastočné vyhľadávanie. Prázdne pole vypíše všetky ÚJ.
* **Obr. 3 (Triedenie a Extrémy):** Pred triedením je nutné načítať tabuľku. Umožňuje triedenie podľa názvu, vzdelania či veku a hľadanie maxima. Pracuje aj s aktívnymi filtrami.
* **Obr. 4 a Obr. 5 (Filtrovanie):** Zadávanie hodnôt pre nové filtre. Tlačidlo *Pridaj filter* vyhodnotí platnosť a aplikuje zmeny. Používateľ môže aplikovať zreťazené filtre (*Filtruj tabuľku*) alebo ich zmazať (*Resetuj filtre*).
