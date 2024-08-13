#pragma once


#include <string>
#include "structures/uzemnaJednotka/uzemnaJednotka.h"
#include "structures/table/table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
#include <fstream>
#include <Windows.h>
#include "loader.h"
#include "sorter.h"
#include "bisectionName.h"

class loader
{
private:
    structures::SortedSequenceTable<wstring, uzemnaJednotka*>* kraje = new structures::SortedSequenceTable<wstring, uzemnaJednotka*>();
    structures::SortedSequenceTable<wstring, uzemnaJednotka*>* okresy = new structures::SortedSequenceTable<wstring, uzemnaJednotka*>();
    structures::SortedSequenceTable<wstring, uzemnaJednotka*>* obce = new structures::SortedSequenceTable<wstring, uzemnaJednotka*>();
    structures::SortedSequenceTable<wstring, uzemnaJednotka*>* krajiny = new structures::SortedSequenceTable<wstring, uzemnaJednotka*>();
public:
    loader() {

    }
    inline structures::SortedSequenceTable<wstring, uzemnaJednotka*>& getKraje() {
        return *kraje;
    }
    inline structures::SortedSequenceTable<wstring, uzemnaJednotka*>& getOkresy() {
        return *okresy;
    }
    inline structures::SortedSequenceTable<wstring, uzemnaJednotka*>& getObce() {
        return *obce;
    }
    inline structures::SortedSequenceTable<wstring, uzemnaJednotka*>& getKrajiny() {
        return *krajiny;
    }
    inline void loadTables() {
     //   SetConsoleCP(1250);
      //  SetConsoleOutputCP(1250);

        std::locale::global(std::locale("sk-SK"));

        wstring line;
        wifstream fileObce("data/obce.csv");
        cout << fileObce.getloc().name();
        fileObce.imbue(std::locale::global(std::locale("sk-SK")));
        wifstream fileOkresy("data/okresy.csv");
        wifstream fileKraje("data/kraje.csv");
        wifstream fileVek("data/vek.csv");
        wifstream fileVzdelanie("data/vzdelanie.csv");
        wstring sortNumber;
        wstring code;
        wstring officialTitle;
        wstring mediumTitle;
        wstring shortTitle;
        wstring note;
        wchar_t delimiter = ';';
  
       
        if (fileObce.is_open())
        {
            wstring dummyLine;
            getline(fileObce, dummyLine);          
            int i = 0;

            while (getline(fileObce, sortNumber, delimiter))
            {
                //if next value is empty we break from while so we dont put empty values to the table
                if (sortNumber.empty()) {
                    break;
                }

                getline(fileObce, code, delimiter);
                getline(fileObce, officialTitle, delimiter);
                getline(fileObce, mediumTitle, delimiter);
                getline(fileObce, shortTitle, delimiter);
                getline(fileObce, note);
                uzemnaJednotka* obec = new uzemnaJednotka(stoi(sortNumber), code, officialTitle, mediumTitle, shortTitle, note,0);
                
                structures::Array<int>* vzdelavanie = new structures::Array<int>(8);
                structures::Array<int>* vekovaSkupina = new structures::Array<int>(6);
                structures::Array<int>* vek = new structures::Array<int>(202);
                    obce->insert(code, obec);
                    obec->getVzdelavanie().assign(*vzdelavanie);
                    obec->getVekovaSkupina().assign(*vekovaSkupina);
                    obec->getVek().assign(*vek);
                    delete vzdelavanie;
                    delete vekovaSkupina;
                    delete vek;

            }
        }
        fileObce.close();
        
        if (fileVzdelanie.is_open()) {
            wstring dummyLine;
            getline(fileVzdelanie, dummyLine);

            while (getline(fileVzdelanie, dummyLine, delimiter)) {
                wstring idOfObec = dummyLine;
                getline(fileVzdelanie, dummyLine, delimiter);

                structures::Array<int>* vzdelavanie = new structures::Array<int>(8);
                
                for (size_t i = 0; i < vzdelavanie->size()-1; i++)
                {
                    getline(fileVzdelanie, dummyLine, delimiter);
                    vzdelavanie->at(i) = stoi(dummyLine);
                }
                getline(fileVzdelanie, dummyLine);
                vzdelavanie->at(vzdelavanie->size() - 1) = stoi(dummyLine);
                obce->find(idOfObec)->getVzdelavanie().assign(*vzdelavanie);
             
                delete vzdelavanie;
     
            }
        }
        fileVzdelanie.close();
        
        
                if (fileVek.is_open()) {
                    wstring dummyLine;
                    getline(fileVek, dummyLine);

                    while (getline(fileVek, dummyLine, delimiter)) {
                        wstring idOfObec = dummyLine;
                        getline(fileVek, dummyLine, delimiter);

                        structures::Array<int>* vekovaSkupina = new structures::Array<int>(6);
                        structures::Array<int>* vek = new structures::Array<int>(202);
                        int id = 0;
                        for (size_t i = 0; i < 201; i++)
                        {
                            getline(fileVek, dummyLine, delimiter);;
                            if (i == 15 || i == 65 || i == 101 || i == 116 || i == 166) {
                                id++;
                            }
                            vek->at(i) = stoi(dummyLine);
                            vekovaSkupina->at(id) = vekovaSkupina->at(id) + stoi(dummyLine);

                        }

                        getline(fileVek, dummyLine);
                        vekovaSkupina->at(5) = vekovaSkupina->at(5) + stoi(dummyLine);
                        obce->find(idOfObec)->getVek().assign(*vek);
                        obce->find(idOfObec)->getVekovaSkupina().assign(*vekovaSkupina);
                        delete vekovaSkupina;
                        delete vek;
                    }
                }
                fileVek.close();
                
     


        if (fileOkresy.is_open()) {
            wstring dummyLine;
            getline(fileOkresy, dummyLine);
            while (getline(fileOkresy, sortNumber, delimiter))
            {
                //if next value is empty we break from while so we dont put empty values to the table
                if (sortNumber.empty()) {
                    break;
                }

                getline(fileOkresy, code, delimiter);
                getline(fileOkresy, officialTitle, delimiter);
                getline(fileOkresy, mediumTitle, delimiter);
                getline(fileOkresy, shortTitle, delimiter);
                getline(fileOkresy, note);

                uzemnaJednotka* okres = new uzemnaJednotka(stoi(sortNumber), code, officialTitle, mediumTitle, shortTitle, note,1);
                
                bool wasMatched = false;
                structures::Array<int>* vzdelavanie = new structures::Array<int>(8);
                structures::Array<int>* vekovaSkupina = new structures::Array<int>(6);
                for (auto obec: *obce)
                {


                    if (SIZE_MAX != obec->getKey().find(okres->getCode())) {
                        obec->accessData()->setBelongsTo(okres);
                        okres->getBelongsToMe().insert(obec->getKey(), obec->accessData());
                        wasMatched = true;
                        for (size_t i = 0; i < 6; i++)
                        {                       
                            vekovaSkupina->at(i) = vekovaSkupina->at(i) + obec->accessData()->getVekovaSkupina().at(i);   
                        }
                        for (size_t i = 0; i < 8; i++)
                        {             
                            vzdelavanie->at(i) = vzdelavanie->at(i) + obec->accessData()->getVzdelavanie().at(i);
                        }
     
                    }

                }
                okres->getVzdelavanie().assign(*vzdelavanie);
                okres->getVekovaSkupina().assign(*vekovaSkupina);
                delete vzdelavanie;
                delete vekovaSkupina;
                okresy->insert(code, okres);

            }

            fileOkresy.close();
           
        }
 
        if (fileKraje.is_open()) {
            wstring dummyLine;
            getline(fileKraje, dummyLine);
            while (getline(fileKraje, sortNumber, delimiter))
            {
                //if next value is empty we break from while so we dont put empty values to the table
                if (sortNumber.empty()) {
                    break;
                }
                getline(fileKraje, code, delimiter);
                getline(fileKraje, officialTitle, delimiter);
                getline(fileKraje, mediumTitle, delimiter);
                getline(fileKraje, shortTitle, delimiter);
                getline(fileKraje, note);

                uzemnaJednotka* kraj = new uzemnaJednotka(stoi(sortNumber), code, officialTitle, mediumTitle, shortTitle, note,2);
                bool wasMatched = false;
                structures::Array<int>* vzdelavanie = new structures::Array<int>(8);
                structures::Array<int>* vekovaSkupina = new structures::Array<int>(6);
                for (auto okres : *okresy)
                {

                    if (SIZE_MAX != kraj->getNote().find(okres->getKey().substr(0, 5))) {                     
                        okres->accessData()->setBelongsTo(kraj);
                        kraj->getBelongsToMe().insert(okres->getKey(), okres->accessData());
                        wasMatched = true;
                        for (size_t i = 0; i < 6; i++)
                        {
                            vekovaSkupina->at(i) = vekovaSkupina->at(i) + okres->accessData()->getVekovaSkupina().at(i);
                        }
                        for (size_t i = 0; i < 8; i++)
                        {
                            vzdelavanie->at(i) = vzdelavanie->at(i) + okres->accessData()->getVzdelavanie().at(i);
                        }

                    }

                }
                kraj->getVzdelavanie().assign(*vzdelavanie);
                kraj->getVekovaSkupina().assign(*vekovaSkupina);
                delete vzdelavanie;
                delete vekovaSkupina;
                kraje->insert(note, kraj);
            }
            fileKraje.close();
        }

        uzemnaJednotka* slovensko = new uzemnaJednotka(0, L"sk", L"sk", L"sk", L"sk", L"sk", 3);
        uzemnaJednotka* zahranicie = new uzemnaJednotka(1, L"zh", L"zh", L"zh", L"zh", L"zh", 3);
        krajiny->insert(L"sk", slovensko);
        krajiny->insert(L"zh", zahranicie);
        structures::Array<int>* vzdelavanie = new structures::Array<int>(8);
        structures::Array<int>* vekovaSkupina = new structures::Array<int>(6);
        for (auto itemKraje : *kraje)
        {
          
            for (size_t i = 0; i < 6; i++)
            {

                vekovaSkupina->at(i) = vekovaSkupina->at(i) + itemKraje->accessData()->getVekovaSkupina().at(i);

            }
            for (size_t i = 0; i < 8; i++)
            {    
                vzdelavanie->at(i) = vzdelavanie->at(i) + itemKraje->accessData()->getVzdelavanie().at(i);
            }

            std::wstring xd = itemKraje->getKey();
            if (itemKraje->getKey() != L"ZZ-9-*****") {

                itemKraje->accessData()->setBelongsTo(slovensko);
                slovensko->getVzdelavanie().assign(*vzdelavanie);
                slovensko->getVekovaSkupina().assign(*vekovaSkupina);
            }else{
                itemKraje->accessData()->setBelongsTo(zahranicie);
                zahranicie->getVzdelavanie().assign(*vzdelavanie);
                zahranicie->getVekovaSkupina().assign(*vekovaSkupina);
            }
          

       
        }
        delete vzdelavanie;
        delete vekovaSkupina;
    }
    ~loader() {
        for (auto itemOkresy : *okresy)
        {
            delete itemOkresy->accessData();
        }

        for (auto itemObce : *obce)
        {
            delete itemObce->accessData();
        }


        for (auto itemKraje : *kraje)
        {
            delete itemKraje->accessData();
        }
        for (auto itemKrajiny : *krajiny)
        {
            delete itemKrajiny->accessData();
        }
        delete obce;
        delete okresy;
        delete kraje;
        delete krajiny;
    }
};

