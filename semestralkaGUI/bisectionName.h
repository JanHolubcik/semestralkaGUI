#pragma once
#include <string>
#include "structures/table/unsorted_sequence_table.h"
#include "structures/uzemnaJednotka/uzemnaJednotka.h"
#include "criterioName.h"
class bisectionName
{
private:
	structures::UnsortedSequenceTable<int, uzemnaJednotka*>* foundByBisection = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
	uzemnaJednotka* UJ = nullptr;
public:
	bisectionName() {};
	~bisectionName(){
		delete foundByBisection;
	}
	structures::UnsortedSequenceTable<int, uzemnaJednotka*>& getAllFoundByBisection() {
		return *foundByBisection;
	}
	uzemnaJednotka& getFoundByBisection() {
		return *UJ;
	}
	//for obce
	bool findAllUJByBisection(std::wstring key,structures::UnsortedSequenceTable<int, uzemnaJednotka*>& table) {
		foundByBisection->clear();
		bool found = false;
		int index = findByBisection(key,0,table.size(), found, table);
		criterioName *cName = new criterioName();
		if (found) {
			foundByBisection->insert(table.getItemAtIndex(index).getKey(), table.getItemAtIndex(index).accessData());
			//check left
			if (!(index == 0)) {

		
			int findIndex = index-1;

			while (cName->evaluate(table.getItemAtIndex(findIndex).accessData()) == key) {
				foundByBisection->insert(table.getItemAtIndex(findIndex).getKey(),table.getItemAtIndex(findIndex).accessData());
				findIndex--;
			}
			}
			if(!(index==(table.size()-1))){
			int findIndex = index + 1;
			while (cName->evaluate(table.getItemAtIndex(findIndex).accessData()) == key) {
				foundByBisection->insert(table.getItemAtIndex(findIndex).getKey(),table.getItemAtIndex(findIndex).accessData());
				findIndex++;
			}
			}

		}
		delete cName;
		return found;
	}
	// for everyone else
	bool findUJByBisection(std::wstring key, structures::UnsortedSequenceTable<int, uzemnaJednotka*>& table) {
		bool found = false;
		int index = findByBisection(key, 0, table.size(), found, table);
		if (found) {
			UJ = table.getItemAtIndex(index).accessData();
		}
		return found;
	}
private:
	int findByBisection(std::wstring key, int indexStart, int indexEnd, bool& found, structures::UnsortedSequenceTable<int, uzemnaJednotka*>& table) {
		int indexSize = table.size();

		if (indexStart == indexSize) {
			found = false;
			return indexSize;
		}

		int pivot = (indexStart + indexEnd) / 2;
		std::wstring keyAtPivot = table.find(pivot)->getOfficialTitle();

		if (keyAtPivot == key) {
			found = true;
			return pivot;
		}
		else {
			if (indexStart == indexEnd) {
				found = false;
				return key < keyAtPivot ? pivot : pivot + 1;
			}
			else {
				if (keyAtPivot < key) {
					indexStart = pivot + 1;
				}
				else {
					indexEnd = pivot;
				}
				return findByBisection(key, indexStart, indexEnd, found, table);
			}
		}
	}


};

