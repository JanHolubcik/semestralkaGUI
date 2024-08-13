#pragma once
#include <string>
#include "../array/array.h";
#include "structures/table/sorted_sequence_table.h";

using namespace std;
enum vzdelavanie { bezUkoncenieho, zakladneVzdelanie, stredneOdborne,uplneStredneVzdelanie,vyssieOdborneVzdelanie,vysokoskolseVzdelanie,bezSkoslkehoVzdelanie,nezistene };
class uzemnaJednotka
{
public:
	uzemnaJednotka(int sortNumber, wstring code, wstring officialTitle, wstring mediumTitle, wstring shortTitle, wstring note,int type);
	~uzemnaJednotka();
	inline int getSortNumber() {
		return sortNumber;
	}
	inline int getType() {
		return type;
	}
	inline wstring getNote() {
		return note;
	}
	inline wstring getCode() {
		return code;
	}
	inline wstring getOfficialTitle() {
		return officialTitle;
	}
	inline wstring getMediumTitle() {
		return mediumTitle;
	}
	inline wstring getShortTitle() {
		return shortTitle;
	}
	
	inline structures::Array<int>& getVzdelavanie() {
		return *vzdelavanie;
	}
	inline structures::Array<int>& getVekovaSkupina() {
		return *vekovaSkupina;
	}
	inline structures::Array<int>& getVek() {
		return *vek;
	}
	inline void setBelongsTo(uzemnaJednotka* uj) {
		belongsTo = uj;
	}
	inline uzemnaJednotka* getBelongsTo() {
		if (belongsTo== nullptr) {
			return nullptr;
		}
		return belongsTo;
	}
	inline uzemnaJednotka& getBelongsToAdress() {
		return *belongsTo;
	}

	inline structures::SortedSequenceTable<wstring, uzemnaJednotka*>& getBelongsToMe() {
		return *belongsToMe;
	}
private:

	int sortNumber;
	wstring code;	
	wstring officialTitle;
	wstring mediumTitle;
	wstring shortTitle;
	wstring note;
	int type;
	uzemnaJednotka* belongsTo = nullptr;
	structures::Array<int> *vzdelavanie = new structures::Array<int>(8);
	structures::Array<int>* vekovaSkupina = new structures::Array<int>(6);
	structures::Array<int>* vek = new structures::Array<int>(202);
	structures::SortedSequenceTable<wstring, uzemnaJednotka*>* belongsToMe = new structures::SortedSequenceTable<wstring, uzemnaJednotka*>();
};

uzemnaJednotka::~uzemnaJednotka() {
	delete vzdelavanie;
	delete vekovaSkupina;
	delete belongsToMe;
	delete vek;
};

inline uzemnaJednotka::uzemnaJednotka(int sortNumber, wstring code, wstring officialTitle, wstring mediumTitle, wstring shortTitle, wstring note,int type):
sortNumber(sortNumber),
code(code),
officialTitle(officialTitle),
mediumTitle(mediumTitle),
shortTitle(shortTitle),
note(note),
type(type)
{

}

