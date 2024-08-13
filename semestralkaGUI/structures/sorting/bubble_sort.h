#pragma once



#include "../table/unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Bubble sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BubbleSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Bubble sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void BubbleSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		int size = static_cast<int>(table.size());
		bool wasSwaped = true;
		while (wasSwaped)
		{
			wasSwaped = false;
			for (size_t i = 0; i < size-1; i++)
			{
				if (table->getItemAtIndex(i)->getKey() > table->getItemAtIndex(i + 1)->getKey()) {
					table.swap(table->getItemAtIndex(i), uniform(table->getItemAtIndex(i + 1)));
					wasSwaped = true;

				}
			}
		}
	}

}