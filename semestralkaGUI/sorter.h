#pragma once
#include "structures/table/unsorted_sequence_table.h"
#include "structures/uzemnaJednotka/uzemnaJednotka.h"
#include "criterio.h"
#include "criterioUJ.h"
//sorter is using quicksort
template<typename K, typename T, typename V>
class sorter
{
public:
	sorter() {};

	~sorter() {};
	void sortByName(structures::UnsortedSequenceTable<K, uzemnaJednotka*>& table, criterioUJ<V>* sortKriterio, int typeOfSorting) {
		if (typeOfSorting == 0) {
			quickAsc(0, table.size() - 1, table, sortKriterio);
		}
		else {
			quickDesc(0, table.size() - 1, table, sortKriterio);
		}


	};
private:

	void quickAsc(size_t min, size_t max, structures::UnsortedSequenceTable<K, T*>& table, criterioUJ<V>* sortKriterio) {
		V pivot = sortKriterio->evaluate(table.getItemAtIndex((min + max) / 2).accessData());
		int left = min;
		int right = max;

		do {
			while (sortKriterio->evaluate(table.getItemAtIndex(left).accessData()) < pivot) {

				left++;
			}
			while (sortKriterio->evaluate(table.getItemAtIndex(right).accessData()) > pivot) {
				right--;
			}
			if (left <= right) {
				table.swap(left, right);
				left++;
				right--;
			}


		} while (left <= right);
		if (min < right && right != -1) {
			quickAsc(min, right, table, sortKriterio);
		}
		if (left < max) {
			quickAsc(left, max, table, sortKriterio);
		}
	}

	void quickDesc(size_t min, size_t max, structures::UnsortedSequenceTable<int, uzemnaJednotka*>& table, criterioUJ<V>* sortKriterio) {
		V pivot = sortKriterio->evaluate(table.getItemAtIndex((min + max) / 2).accessData());
		int left = min;
		int right = max;

		do {
			while (sortKriterio->evaluate(table.getItemAtIndex(left).accessData()) > pivot) {

				left++;
			}
			while (sortKriterio->evaluate(table.getItemAtIndex(right).accessData()) < pivot) {
				right--;
			}
			if (left <= right) {
				table.swap(left, right);
				left++;
				right--;
			}


		} while (left <= right);
		if (min < right && right != -1) {
			quickDesc(min, right, table, sortKriterio);
		}
		if (left < max) {
			quickDesc(left, max, table, sortKriterio);
		}
	}

};

