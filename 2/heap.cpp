#include<iostream>
#include<climits>
#include<vector>
using namespace std;
int arr[1000006];
void swap(pair<int,int> *x, pair<int, int> *y, int i1, int i2);

class MinHeap {

public:
	pair<int, int> *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
	// Constructor
	MinHeap(int capacity);

	// to heapify a subtree with the root at given index
	void MinHeapify(int i);

	int parent(int i) { return (i-1)/2; }

	// to get index of left child of node at index i
	int left(int i) { return (2*i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2*i + 2); }

	// to extract the root which is the minimum element
	pair<int,int> extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap
	int getMin() { return harr[0].first; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k, int index);
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new pair<int, int>[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k, int index)
{
	if (heap_size == capacity)
	{
		//cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i].first = k;
	harr[i].second = index;
	arr[harr[i].second] = i;

	// Fix the min heap property if it is violated
	while (i != 0 && harr[parent(i)].first > harr[i].first) {
        swap(&harr[i], &harr[parent(i)], i, parent(i));
        i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i].first = new_val;
	while (i != 0 && harr[parent(i)].first > harr[i].first) {
        swap(&harr[i], &harr[parent(i)], i, parent(i));
        i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
pair<int,int> MinHeap::extractMin() {
	if (heap_size <= 0)
		return {INT_MAX, INT_MAX};
	if (heap_size == 1) {
		heap_size--;
		return harr[0];
	}
	// Store the minimum value, and remove it from heap
	pair<int,int> root = harr[0];
	harr[0] = harr[heap_size-1];
	arr[harr[0].second] = 0;
	heap_size--;
	MinHeapify(0);
	return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i) {
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l].first < harr[i].first)
		smallest = l;
	if (r < heap_size && harr[r].first < harr[smallest].first)
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest], i, smallest);
		MinHeapify(smallest);
	}
}

// A class for max Heap
class maxHeap
{

public:
	pair<int,int> *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of max heap
	int heap_size; // Current number of elements in max heap
	// Constructor
	maxHeap(int capacity);

	// to heapify a subtree with the root at given index
	void maxHeapify(int i);

	int parent(int i) { return (i-1)/2; }

	// to get index of left child of node at index i
	int left(int i) { return (2*i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2*i + 2); }

	// to extract the root which is the maximum element
	pair<int,int> extractmax();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the maximum key (key at root) from max heap
	int getmax() { return harr[0].first; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k, int index);
};

// Constructor: Builds a heap from a given array a[] of given size
maxHeap::maxHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new pair<int,int>[cap];
}

// Inserts a new key 'k'
void maxHeap::insertKey(int k, int index)
{
	if (heap_size == capacity)
	{
		//cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i].first = k;
	harr[i].second = index;
	arr[harr[i].second] = i;

	// Fix the max heap property if it is violated
	while (i != 0 && harr[parent(i)].first < harr[i].first)
	{
	swap(&harr[i], &harr[parent(i)], i, parent(i));
	i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void maxHeap::decreaseKey(int i, int new_val)
{
	harr[i].first = new_val;
	while (i != 0 && harr[parent(i)].first < harr[i].first)
	{
	swap(&harr[i], &harr[parent(i)], i, parent(i));
	i = parent(i);
	}
}

// Method to remove maximum element (or root) from max heap
pair<int,int> maxHeap::extractmax()
{
	if (heap_size <= 0)
		return {INT_MAX, INT_MAX};
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the maximum value, and remove it from heap
	pair<int,int> root = harr[0];
	harr[0] = harr[heap_size-1];
	arr[harr[0].second] = 0;
	heap_size--;
	maxHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to maxus
// infinite, then calls extractmax()
void maxHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MAX);
	extractmax();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void maxHeap::maxHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int highest = i;
	if (l < heap_size && harr[l] > harr[i])
		highest = l;
	if (r < heap_size && harr[r] > harr[highest])
		highest = r;
	if (highest != i)
	{
		swap(&harr[i], &harr[highest], i, highest);
		maxHeapify(highest);
	}
}

// A utility function to swap two elements
void swap(pair<int,int> *x, pair<int, int> *y, int i1, int i2)
{
    arr[(*x).second] = i2;
    arr[(*y).second] = i1;
	pair<int,int> temp = *x;
	*x = *y;
	*y = temp;
}

// Driver program to test above functions
int main()
{
    int n, k;
    cin >> n;
    cin >> k;
    int median;
    int medianIndex = 0;
    vector<int> numbers(n);
    cin >> median;
    maxHeap mxh(k);
    MinHeap mnh(k);
    long long int max_sum = 0;
    long long int min_sum = 0;
    vector<long long int> result(n - k + 1);
    numbers[0] = median;
    int offset = 0;
    for(int i = 1; i < k; i++) {
        cin >> numbers[i];
        if(numbers[i] <= median) {
            mxh.insertKey(numbers[i], i);
            max_sum += (long long int)numbers[i];
            offset--;
            if(offset == -2) {
                mnh.insertKey(median, medianIndex);
                min_sum += (long long int)median;
                pair<int , int> temp = mxh.extractmax();
                median = temp.first;
                medianIndex = temp.second;
                max_sum -= (long long int)temp.first;
                offset = 0;
            }
        }else {
            mnh.insertKey(numbers[i], i);
            min_sum += (long long int)numbers[i];
            offset++;
            if(offset == 2) {
                mxh.insertKey(median, medianIndex);
                max_sum += (long long int)median;
                pair<int , int> temp = mnh.extractMin();
                median = temp.first;
                medianIndex = temp.second;
                min_sum -= (long long int)temp.first;
                offset = 0;
            }
        }
        }
        if(offset == 1) {
            mxh.insertKey(median, medianIndex);
            max_sum += (long long int)median;
            pair<int, int> temp = mnh.extractMin();
            median = temp.first;
            medianIndex = temp.second;
            min_sum -= (long long int)temp.first;
        }
    if(k % 2 == 1)
        result[0] = min_sum - max_sum;
    else
        result[0] = min_sum - max_sum + median;
    int added, deleted;
    for(int i = 0; i <= n - k - 1; i++) {
        cin >> numbers[i + k];
        deleted = numbers[i];
        added = numbers[i + k];
        if(deleted < median) {
            mxh.deleteKey(arr[i]);
            max_sum -= (long long int)deleted;
            if(added <= median) {
                mxh.insertKey(added, i + k);
                max_sum += (long long int)added;
            }else if(added > median) {
                mnh.insertKey(added, i + k);
                min_sum += (long long int)added;
                mxh.insertKey(median, medianIndex);
                max_sum += (long long int)median;
                pair <int, int> temp = mnh.extractMin();
                min_sum -= (long long int)temp.first;
                median = temp.first;
                medianIndex = temp.second;
            }
        }else if(deleted == median) {
			if(medianIndex != i){
				int inx = arr[i];
				int inx_max = mxh.harr[inx].second;
				int inx_min = mnh.harr[inx].second;
				if(i == inx_max){
					mxh.harr[inx].second = medianIndex;
					arr[medianIndex] = inx;
				}else if (i == inx_min){
					mnh.harr[inx].second = medianIndex;
					arr[medianIndex] = inx;
				}
			}
            if(added < median) {
                mxh.insertKey(added, i + k);
                max_sum += (long long int)added;
                pair <int, int> temp = mxh.extractmax();
                max_sum -= (long long int)temp.first;
                median = temp.first;
                medianIndex = temp.second;
            }else if(added > median) {
                mnh.insertKey(added, i + k);
                min_sum += (long long int)added;
                pair <int, int> temp = mnh.extractMin();
                min_sum -= (long long int)temp.first;
                median = temp.first;
                medianIndex = temp.second;
            }else {
                medianIndex = i + k;
            }
        }else if(deleted > median) {
            mnh.deleteKey(arr[i]);
            min_sum -= (long long int)deleted;
            if(added < median) {
                mxh.insertKey(added, i + k);
                max_sum += (long long int)added;
                mnh.insertKey(median, medianIndex);
                min_sum += (long long int)median;
                pair <int, int> temp = mxh.extractmax();
                max_sum -= (long long int)temp.first;
                median = temp.first;
                medianIndex = temp.second;
            }else if(added >= median) {
                mnh.insertKey(added, i + k);
                min_sum += (long long int)added;
            }
        }
        if(k % 2 == 1)
            result[i + 1] = min_sum - max_sum;
        else
            result[i + 1] = min_sum - max_sum + median;
    }
    for(int i = 0 ; i <= n - k; i++) {
        cout << result[i] << " ";
    }
	return 0;
}
