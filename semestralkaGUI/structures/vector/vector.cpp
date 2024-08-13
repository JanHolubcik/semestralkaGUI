#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_);//kam odkial a kolko
		
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other) {
			Vector& otherVector = dynamic_cast<Vector&>(other);//ampersant je referencia
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_);// sluzi but na zvacsenie alebo zmensenie uz existujucej 
			memcpy(memory_, otherVector.memory_, size_);
		}
		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other) { //this pointer na seba samostneho a potrebujem pointer na other
			return true;
		}
		else {
			Vector* otherVector = dynamic_cast<Vector*>(&other);// pretypovat a ak to nepojde tak vratim nullpointer
			if (otherVector != nullptr) { 
				return size_ == otherVector->size_ && memcmp(memory_, otherVector->memory_, size_) == 0;
			}
			else {
				return false;
			}
		}
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		return *getBytePointer(index);// vrati hodnotu ktora je na pointeri
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
	//	Utils::rangeCheckExcept(srcStartIndex, src.size_, "Invalid index of vector(copy)1!");// ci neni mimo range
	//	Utils::rangeCheckExcept(srcStartIndex + length, src.size_+1, 
	//	"Invalid index of vector(copy)2!"+ std::to_string(srcStartIndex + length)+"!!!" + std::to_string(src.size_ + 1));// ci neni mimo range
	//	Utils::rangeCheckExcept(destStartIndex, dest.size_, "Invalid index of vector(copy)3!");// ci neni mimo range
	//	Utils::rangeCheckExcept(destStartIndex, dest.size_+1, "Invalid index of vector(copy)4!");// ci neni mimo range
		if (length > 0) {
		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length) {
			memmove(
				dest.getBytePointer(destStartIndex), 
				src.getBytePointer(srcStartIndex), 
				length
			);
		}
		else {
			memcpy(
				dest.getBytePointer(destStartIndex), 
				src.getBytePointer(srcStartIndex), 
				length
			);
		}
		}

	}

	byte* Vector::getBytePointer(int index)
	{
	//	Utils::rangeCheckExcept(index, size_, "Invalid index of vector (getBytePointer)!");// ci neni mimo range
		return reinterpret_cast<byte*>(memory_) + index;// smernikova aritmetika, memory_ je voidPointer potrebujeme 
														// ho pretypovat na byte*, index preskoci tolko bajtou aka je jeho hodnota
	}
}