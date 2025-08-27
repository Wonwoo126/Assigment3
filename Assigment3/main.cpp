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
	
	// ���� ������
	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "�κ��丮 ���� �Ϸ�" << endl;
	}
	
	~Inventory() {
		delete[] pItems_;
		pItems_ = nullptr;
		cout << "�κ��丮�� �����Ǿ����ϴ�!" << endl;
	}

	void Assign(const Inventory<T>& other) {
		delete[] pItems_;
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "�κ��丮 ����� �Ϸ�" << endl;
		
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
		cout << "�κ��丮 ũ�� ���� �Ϸ�" << endl;
		
	}

	void RemoveLastItem() {
		if (size_ > 0)	size_--;
		else cout << "�κ��丮�� ����ֽ��ϴ�!" << endl;
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
	inv.AddItem(Item("��", 100));
	inv.AddItem(Item("����", 150));
	inv.AddItem(Item("����1", 30));
	inv.AddItem(Item("����2", 40));
	inv.AddItem(Item("����3", 50));
	inv.PrintAllItems();
	Inventory<Item> inv2 = inv; // ���� ������ ȣ��
	inv2.PrintAllItems();
	Inventory<Item> inv3;
	inv3.Assign(inv); // �Ҵ� ������ ȣ��
	inv3.PrintAllItems();
	inv.RemoveLastItem();
	inv.PrintAllItems();
	inv.Resize(5);
	cout << "������â : " << inv.GetCapacity() << endl;
	inv.SortItems();
	inv.PrintAllItems();
	return 0;
}