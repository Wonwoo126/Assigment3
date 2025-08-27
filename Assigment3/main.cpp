#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


class Item {
private:
	string name_;
	int price_;
public:
	Item(string name = "Unknown", int price = 0) : name_(name), price_(price) {}
	void PrintInfo() const {
		cout << "Item Name: " << name_ << ", Price: " << price_ << endl;
	}
	int GetPrice() const { return price_; }
};

bool compareItemsByPrice(const Item& a, const Item& b) {
	return a.GetPrice() < b.GetPrice();
}

template <typename T> 

class Inventory {
private:
	T* pItems_ = nullptr;
	int capacity_ = 0;
	int size_ = 0;
public:
	Inventory(int capacity_ = 10) {
		if (capacity_ <= 0) {
			this->capacity_ = 1;
		}
		else this->capacity_ = capacity_;
		pItems_ = new T[this->capacity_];
	}
	
	// 복사 생성자
	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "인벤토리 복사 완료" << endl;
	}
	
	~Inventory() {
		delete[] pItems_;
		pItems_ = nullptr;
		cout << "인벤토리가 삭제되었습니다!" << endl;
	}

	void Assign(const Inventory<T>& other) {
		delete[] pItems_;
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "인벤토리 덮어쓰기 완료" << endl;
		
	}

	void AddItem(const T& item) {
		if(size_ >= capacity_) {
			capacity_ *= 2;
			T* newItems = new T[capacity_];
			for (int i = 0; i < size_; i++) {
				newItems[i] = pItems_[i];
			}
			delete[] pItems_;
			pItems_ = newItems;
			size_++;
			pItems_[size_ - 1] = item;
		}
		else {
			size_++;
			pItems_[size_ - 1] = item;
		}
		
	}

	void Resize(int newCapacity) {
		
		T* newItems = new T[newCapacity];
		int newSize = (newCapacity < size_) ? newCapacity : size_;
		for (int i = 0; i < newSize; i++) {
			newItems[i] = pItems_[i];
		}
		delete[] pItems_;
		pItems_ = newItems;
		capacity_ = newCapacity;
        size_ = newSize;
		cout << "인벤토리 크기 조정 완료" << endl;
		
	}

	void RemoveLastItem() {
		if (size_ > 0)	size_--;
		else cout << "인벤토리가 비어있습니다!" << endl;
	}

    int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }

	void PrintAllItems() const {
		for (int i = 0; i < size_; i++) {
			pItems_[i].PrintInfo();
		}
		cout << endl;
	}

	void SortItems() {
		sort(pItems_, pItems_ + size_, compareItemsByPrice);
	}
};




int main() {
	Inventory<Item> inv(2);
	inv.AddItem(Item("검", 100));
	inv.AddItem(Item("방패", 150));
	inv.AddItem(Item("포션1", 30));
	inv.AddItem(Item("포션2", 40));
	inv.AddItem(Item("포션3", 50));
	inv.PrintAllItems();
	Inventory<Item> inv2 = inv; // 복사 생성자 호출
	inv2.PrintAllItems();
	Inventory<Item> inv3;
	inv3.Assign(inv); // 할당 연산자 호출
	inv3.PrintAllItems();
	inv.RemoveLastItem();
	inv.PrintAllItems();
	inv.Resize(5);
	cout << "아이템창 : " << inv.GetCapacity() << endl;
	inv.SortItems();
	inv.PrintAllItems();
	return 0;
}