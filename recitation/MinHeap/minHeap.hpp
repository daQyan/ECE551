#pragma once
#include <iostream>
#include <algorithm>

using namespace std;
template <typename Item>

class minHeap {
private:
	Item* data;							
	int count;
	int capacity;

	shifDown(int k) {
		while (2 * k <= count) {
			int j = 2 * k;
			if (j + 1 <= count && data[j + 1] <= data[j])
				j++;
			if (data[k] <= data[j])
				break;
			swap(data[k], data[j]);
			k = j;
		}
	}

	shiftUp(int k) {
		while (k > 1 && data[k / 2] > data[k]) {
			swap(data[k], data[k / 2]);
			k /= 2;
		}
	}

public:
	minHeap(int capacity) {
		data = new Item[capacity + 1];
		this->capacity = capacity;
		count = 0;
	}
	// minHeap(Item arr[], int n) {
	// 	data = new Item[n + 1];
	// 	capacity = n;
	// 	for (int i = 0; i < n; ++i) {
	// 		data[i + 1] = arr[i];					
	// 	}
	// 	count = n;

	// 	for (int i = count / 2; i >= 1; --i) {
	// 		shiftDown(i);
	// 	}
	// }

	~minHeap() { delete[] data; }

	int size() { return count; }

	bool isEmpty() { return count == 0; }

	void insert(Item k) {
		assert(count + 1 <= capacity);
		data[count + 1] = k;
		shiftUp(count + 1);
		count++;
		
	}

	Item removeMin() {
		assert(count > 0);
		Item ret = data[1];
		swap(data[1], data[count]);
		count --;
		shifDown(1);
		return ret;
	}

	Item getRoot() {
		assert(count > 0);
		return data[1];
	}

};
