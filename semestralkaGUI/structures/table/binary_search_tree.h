#pragma once

#include "table.h"
#include "../list/list.h"
#include "../tree/binary_tree.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Binarny vyhladavaci strom. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T>
	{
	public:
		typedef typename BinaryTreeNode<TableItem<K, T>*> BSTTreeNode;
	public:
		/// <summary> Konstruktor. </summary>
		BinarySearchTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BinarySearchTree, z ktoreho sa prevezmu vlastnosti. </param>
		BinarySearchTree(BinarySearchTree<K, T>& other);

		/// <summary> Destruktor. </summary>
		~BinarySearchTree();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Najde vrchol binarneho vyhladavacieho stromu s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Vrchol binarneho vyhladavacieho stromu s danym klucom. Ak sa kluc v tabulke nenachadza, vrati otca, ktoreho by mal mat vrchol s takym klucom. </returns>
		typename BSTTreeNode* findBSTNode(K key, bool& found);

	protected:
		/// <summary> Binarny strom s datami. </summary>
		BinaryTree<TableItem<K, T>*>* binaryTree_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

		/// <summary> Vlozi vrchol do stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vlozeny. </param>
		/// <returns> true, ak sa podarilo vrchol vlozit (teda v strome nie je vrchol s rovnakym klucom), false inak. </returns>
		bool tryToInsertNode(BSTTreeNode* node);

		/// <summary> Bezpecne vyjme zo stromu vrchol stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vyjmuty. </param>
		/// <remarks> Vrchol nebude zruseny, iba odstraneny zo stromu a ziadne vrcholy nebudu ukazovat na neho a ani on nebude ukazovat na ziadne ine vrcholy. </remarks>
		void extractNode(BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree() :
		Table<K, T>(),
		binaryTree_(new BinaryTree<TableItem<K, T>*>()),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(BinarySearchTree<K, T>& other) :
		BinarySearchTree()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree()
	{
		clear();
		delete binaryTree_;
		binaryTree_ = nullptr;
		
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size()
	{
		return size_;
	}

	template<typename K, typename T>
	inline Structure& BinarySearchTree<K, T>::assign(Structure& other)
	{
		if (this != &other) {
			BinarySearchTree<K, T>& BST = dynamic_cast<BinarySearchTree<K, T>&>(other);
			clear();
			/*
			for (auto item : BST) {
				this->insert(item->getKey(), item->accessData());
			}*/
			//pouzit preorder alebo levelorder
			//keby ze ich vytvaram cez new na halde treba ich vymazat takto nemusim viacej nic riesit(dereferencovanie)
			Tree<TableItem<K, T>*>::PreOrderTreeIterator start(BST.binaryTree_->getRoot());
			Tree<TableItem<K, T>*>::PreOrderTreeIterator end(nullptr);
			while (start != end) {
				TableItem<K, T>* item = *start;
				++start;
				insert(item->getKey(), item->accessData());
			}

		}
		return *this;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<BinarySearchTree<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline T& BinarySearchTree<K, T>::find(const K& key)
	{
		bool found = false;
		BSTTreeNode* item = findBSTNode(key, found);
		if (found) {
			return item->accessData()->accessData();
		}
		else {
			throw std::out_of_range("find binary search tree");
		}
		
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K& key, const T& data)
	{
		BSTTreeNode* item = new BSTTreeNode(new TableItem<K, T>(key, data));
		if (tryToInsertNode(item)) {
			size_++;
		}
		else {
			delete item->accessData();
			delete item;
			throw std::logic_error("Key aleary in tree. insert binary tree");
		}
	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K& key)
	{
		bool found = false;

		BSTTreeNode* item = findBSTNode(key, found);

		if (found) {
			extractNode(item);

			T data = item->accessData()->accessData();
			delete item->accessData();
			delete item;
			size_--;
			return data;
		}
		else {
			
			throw std::logic_error("Key not found. binary search tree remove");
		}
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K& key, T& data)
	{
		bool found = false;
		BSTTreeNode* item = findBSTNode(key, found);
		if (found) {
			data = item->accessData()->accessData();
			return true;
		}
		else {
			return false;
		}
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K& key)
	{
		bool found = false;
		findBSTNode(key, found);
		return found;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear()
	{
	
		for (auto node : (*binaryTree_)) {
			delete node;
		}
		binaryTree_->clear();
		size_ = 0;


	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator()
	{
		//return BinaryTree<TableItem<K, T>*> BinarySearchTree<K, T>::InOrder
		return binaryTree_->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator()
	{
		return binaryTree_->getEndIterator();
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K, T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(K key, bool& found)
	{
		found = false;
		if (binaryTree_->getRoot() == nullptr) {
			return nullptr;
		}
		else {
			BSTTreeNode* node = dynamic_cast<BSTTreeNode*>(binaryTree_->getRoot());
			
			
			while (node->accessData()->getKey() != key) {
				K data = node->accessData()->getKey();
				if (key < node->accessData()->getKey()) {
					if (node->hasLeftSon()) {
						node = node->getLeftSon();
					}
					else {
						return node;
					}
				}
				else {
					if (node->hasRightSon()) {
						node = node->getRightSon();
					}
					else {
						return node;
					}
				}
			}
			found = true;
			return node;
		}
	
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node)
	{
		if (binaryTree_->getRoot() == nullptr) {

			binaryTree_->replaceRoot(node);
			return true;
		}

		K key = node->accessData()->getKey();
		bool found = false;
		BSTTreeNode* item = findBSTNode(key,found);
		T x = item->accessData()->getKey();
		if (!found) {

			if (item == nullptr) {
				binaryTree_->replaceRoot(node);
			}
			else {
				if (key < item->accessData()->getKey()) {
					item->setLeftSon(node);
				}
				else {
					item->setRightSon(node);
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node)
	{
		BSTTreeNode* parent = node->getParent();
		BSTTreeNode* replaceNode = nullptr;
		bool haveTwoSon = false;
		bool haveRightSon = node->hasRightSon();
		bool haveLeftSon = node->hasLeftSon();
		if (node->hasLeftSon() && node->hasRightSon()) {

			replaceNode = node->getRightSon();
			while (replaceNode->hasLeftSon())
			{
				replaceNode = replaceNode->getLeftSon();
			}

			extractNode(replaceNode);

			replaceNode->setLeftSon(node->changeLeftSon(nullptr));
			replaceNode->setRightSon(node->changeRightSon(nullptr));
			haveTwoSon = true;
		}
	
		if(!haveTwoSon && (node->hasLeftSon() || node->hasRightSon())){
			replaceNode = node->hasLeftSon() ?
				node->changeLeftSon(nullptr) :
				node->changeRightSon(nullptr);
		}
				if (parent == nullptr)
				{
					binaryTree_->replaceRoot(replaceNode);
				}
				else
				{
					if (node->isLeftSon())
					{
						parent->setLeftSon(replaceNode);
					}
					else
					{
						parent->setRightSon(replaceNode);
					}
				}

			if (replaceNode != nullptr)
			{
				replaceNode->setParent(parent);
			}

	}

}