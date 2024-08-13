#pragma once

#include "../table/unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Select sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SelectSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Select sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void SelectSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		int size = static_cast<int>(table.size());

	
		
			for (size_t i = 0; i < size - 2; i++)
			{
				int min = i;
				for (size_t j = i+1; j < size-1; j++)
				{
					if (table[i] < table[min]) {
						min = j;
						table.swap(table[i], table[min]);
					

					}
				}
			}
		
	

}