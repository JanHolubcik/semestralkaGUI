#pragma once

#include "list.h"
#include "linked_list.h"
namespace structures
{
	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.
	
    template<typename T>
    class DoubleLinkedListItem : public LinkedListItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DoubleLinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getPrv();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setPrv(DoubleLinkedListItem<T>* prv);

    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* prv_;
    };

    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public LinkedList<T> 
	{
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;
    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        DoubleLinkedListItem<T>* getItemAtIndex(int index);

	};


    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data)
        :LinkedListItem<T>(data),
        prv_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other):
        : LinkedListItem<T>(*other),
        prv_(other.prv_)
    {
    }

  
   

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        prv_ = nullptr;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrv()
    {
        return prv_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrv(DoubleLinkedListItem<T>* prv)
    {
        prv_ = prv;
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList():
        LinkedList<T>()
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other):
        LinkedList<T>(other)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        return LinkedList<T>::size();
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
        if (this != &other) {
            DoubleLinkedList<T>& otherDLL = dynamic_cast<DoubleLinkedList<T>&>(other);
            clear();

            for (T item : otherDLL)
            {

                add(item);
            }
        }
        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        //otestuj
        //ide
       return LinkedList<T>::equals(other);
    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
    
        return getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
        if (size_ == 0) {
     
            first_ = newItem;
            last_ = newItem;
            newItem->setPrv(nullptr);
            newItem->setNext(nullptr);
            
           /* LinkedList<T>::first_ = newItem;
            LinkedList<T>::first_->setPrv(nullptr);
            LinkedList<T>::first_->setNext(nullptr);
            LinkedList<T>::last_ = newItem;
            */
        }
        else {
 


            newItem->setPrv(dynamic_cast<DoubleLinkedListItem<T>*>(last_));
            last_->setNext(newItem);
            LinkedList<T>::last_ = newItem;
            newItem->setNext(nullptr);


        }

       
        size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        if (index == size_) {
            add(data);
        }
        else
        {
  //          Utils::rangeCheckExcept(index, size_, "Invalid index LInkedList (insert).");
            if (index == 0) {
                DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
                (dynamic_cast<DoubleLinkedListItem<T>*>(first_))->setPrv(newItem);
                newItem->DoubleLinkedListItem<T>::setNext(first_);
                newItem->setPrv(nullptr);
                first_ = newItem;
            }
            else
            {

                DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
                DoubleLinkedListItem<T>* nextItem = getItemAtIndex(index);
                DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);

                newItem->setNext(prevItem->getNext());
                newItem->setPrv(prevItem);
                prevItem->setNext(newItem);
                nextItem->setPrv(newItem);

            }
        }
        size_++;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        int index = getIndexOf(data);
        if (index != -1) {
            removeAt(index);
            return true;
        }
        return false;
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        if (size_ == 0) {
            throw std::runtime_error("There are no variables in DoubleLinkedList to be deleted.");
        }
        else {
         //   Utils::rangeCheckExcept(index, size_, "Invalid index DoubleLinkedList (removeAt).");
            DoubleLinkedListItem<T>* removed = getItemAtIndex(index);
            if (first_ == last_) {
                delete removed;
            }
            else if (first_ == removed && first_ != last_) {
                first_ = first_->getNext();
                (dynamic_cast<DoubleLinkedListItem<T>*>(first_))->setPrv(nullptr);
            
                delete removed;
            }
            else if (last_ == removed && first_ != last_) {
                
                last_ = dynamic_cast<DoubleLinkedListItem<T>*>(last_)->getPrv();
                last_->setNext(nullptr);
                delete removed;
            }
            else {
                DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
                DoubleLinkedListItem<T>* nextItem = getItemAtIndex(index + 1);
                prevItem->setNext(nextItem);
                nextItem->setPrv(prevItem);
                delete removed;

            }
            size_--;
        };
    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
       return (LinkedList<T>::getIndexOf(data));
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        if (index == -1) {
            return dynamic_cast<DoubleLinkedListItem<T>*>(last_);
        }
        else {

            if(size()!=0){
                if(size()/2>index){
                    DoubleLinkedListItem<T>* current = dynamic_cast<DoubleLinkedListItem<T>*>(first_);
                  for (size_t i = 0; i < index; i++)
                    {
                      current = dynamic_cast<DoubleLinkedListItem<T>*>(current->getNext());
                    }
                  return current;
                }
                else 
                {
                    DoubleLinkedListItem<T>* current = dynamic_cast<DoubleLinkedListItem<T>*>(last_);
                    for (size_t i = 0; i < size()-index-1; i++)
                    {
                        current = current->getPrv();
                    }
                    return current;
                }
             }
             
        }
    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        LinkedList<T>::clear();
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
       return LinkedList<T>::getBeginIterator();
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        return LinkedList<T>::getEndIterator();
    }






}