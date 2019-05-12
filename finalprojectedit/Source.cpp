#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>
#include<string>
using namespace std;

class Sort
{
public:
	const int ar_size = 1000000;
	int *dataSet = new int[ar_size];

	int size()
	{
		int size = 0;
		while (dataSet[size] > 0)
			size++;

		return size;
	}

	void insertionSort()
	{
		for (int i = 0; i < size(); i++)
		{
			int tmp = dataSet[i];
			int j;
			for (j = i; i > 0 && tmp < dataSet[j - 1]; j--)
				dataSet[j] = dataSet[j - 1];
			dataSet[j] = tmp;
		}
	}

	void merge(int low, int mid, int high)
	{
		int n1 = mid - low + 1;
		int n2 = high - mid;

		int *L = new int[n1];
		int *R = new int[n2];

		for (int i = 0; i < n1; i++)
			L[i] = dataSet[low + i];
		for (int j = 0; j < n2; j++)
			R[j] = dataSet[mid + 1 + j];

		int i = 0;
		int j = 0;
		int k = low;
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				dataSet[k] = L[i];
				i++;
			}
			else
			{
				dataSet[k] = R[j];
				j++;
			}
			k++;
		}
		while (i < n1)
		{
			dataSet[k] = L[i];
			i++;
			k++;
		}
		while (j < n2)
		{
			dataSet[k] = R[j];
			j++;
			k++;
		}
	}

	void mergesort(int low, int high)
	{
		int pivot;
		if (low < high)
		{
			pivot = (low + high) / 2;
			mergesort(low, pivot);
			mergesort(pivot + 1, high);
			merge(low, pivot, high);
		}
	}

	int partition(int *arr, const int left, const int right)
	{
		const int mid = left + (right - left) / 2;
		const int pivot = arr[mid];

		swap(arr[mid], arr[left]);

		int i = left + 1;
		int j = right;
		while (i <= j)
		{
			while (i <= j && arr[i] <= pivot) { i++; }

			while (i <= j && arr[j] > pivot) { j--; }

			if (i < j) { swap(arr[i], arr[j]); }
		}
		swap(arr[i - 1], arr[left]);
		return i - 1;
	}

	void quicksort(int *arr, const int left, const int right, const int sz)
	{

		if (left >= right)
		{
			return;
		}
		int part = partition(arr, left, right);

		quicksort(arr, left, part - 1, sz);
		quicksort(arr, part + 1, right, sz);
	}


	void bucketSort(int arr[], int size)
	{

		//variables
		int max, divider, i, j, k;
		const int  bucket = 10;

		//buckets
		vector<int> B[bucket];

		//find max and min
		max = getMax(arr, size);

		divider = ceil(float(max + 1) / bucket); //Sets the maximum number in each index/vector/bucket

												 //insert element into bucket
		for (i = 0; i < size; i++) {
			j = floor(dataSet[i] / divider); //Finds the vector index to insert the value being sorted
			B[j].push_back(dataSet[i]); //Inserts the value
		}

		//sort elements in the buckets
		for (int indexbucket = 0; j < bucket; j++) {
			int bucketSize = B[indexbucket].size();

			/*		for (int i = 0; i < bucketSize; i++)
			{
			int tmp = B[indexbucket][i];
			int j;
			for (j = i; i > 0 && tmp < bucketSize-1; j--)
			B[indexbucket][j] = B[indexbucket][j-1];
			B[indexbucket][j] = tmp;
			}*/
			for (int i = 0; i < bucketSize; i++)
			{
				dataSet[i] = B[indexbucket][i];
			}

			mergesort(0, bucketSize); // calls merge sort

			for (int i = 0; i < bucketSize; i++)
			{
				B[indexbucket][i] = dataSet[i];
			}
			
		}

		//append back the elements from the buckets
		k = 0;
		for (i = 0; i < bucket; i++) {
			for (j = 0; j < B[i].size(); j++) {
				dataSet[k++] = B[i][j];
			}
		}
	}

	int getMax(int dataSet[], int size) {
		int i, m = dataSet[0];
		for (i = 1; i < size; i++) {
			if (dataSet[i] > m) {
				m = dataSet[i];
			}
		}
		return m;
	}
	void CountingSort(int arr[], int size)
	{
		int i, j, c;
		int index = 0;
		int min, max;

		min = max = arr[0];
			//find our max/min in array
		for (i = 1; i < size; i++) {
			min = (arr[i] < min) ? arr[i] : min;
			max = (arr[i] > max) ? arr[i] : max;
		}

		c = max - min + 1;

		// dynamically allocate some space
		int *B = new int[c];
		//initalize array to 0
		for (i = 0; i < c; i++) B[i] = 0;
		//keep track of each time a number of the array has been seen
		for (i = 0; i < size; i++) B[arr[i] - min]++;
		 
		for (i = min; i <= max; i++)
			// overwriting array by using count values in the total ordering
			for (j = 0; j < B[i - min]; j++) arr[index++] = i;

		
		//free up used memory
		delete[] B;
	}

	void heapify(int arr[], int size, int i)
	{
		int largest = i;  // largest value = root
		int l = 2 * i + 1;  
		int r = 2 * i + 2; 

			
		if (l < size && arr[l] > arr[largest])//check if child on left is largest
			largest = l;

		
		if (r < size && arr[r] > arr[largest])//check right child if largest
			largest = r;

		// If largest is not root
		if (largest != i)
		{
			swap(arr[i], arr[largest]);

		
			heapify(arr, size, largest);
		}
	}
	
	void heapSort(int arr[], int size)
	{
		
		for (int i = size / 2 - 1; i >= 0; i--)
			heapify(arr, size, i);

		
		for (int i = size - 1; i >= 0; i--) //decrement each element from heap
		{
			
			swap(arr[0], arr[i]); // root goes to the end of array

			
			heapify(arr, i, 0); 
		}
	}

	void read()
	{
		ifstream file_save("dataset.txt");
		if (file_save.is_open())
		{
			int i = 0;
			while (!file_save.eof() && i < ar_size)
			{
				file_save >> dataSet[i];
				i++;
			}
			file_save.close();
		}
		else
			cout << "Error in opening file!" << endl;
	}

	void print() //Print out some of the array to check order
	{
		for (int i = 0; i < 10; i++)
		{
			cout << dataSet[i] << " " << endl;
		}
	}

	void write()
	{
		ofstream file_load("data.txt");
		if (file_load.is_open())
		{
			int i = 0;
			while (i < ar_size)
			{
				file_load << dataSet[i] << endl;
				i++;
				if (dataSet[i] < 0)
					break;
			}
			file_load.close();
		}
		else
			cout << "Error in opening file!" << endl;
	}
};


int main()
{
	char repeat = 'n';
	do {
		Sort ins;
		int userinput = 0;

		ins.read();

		clock_t tStart;

		do {
			cout << "Which sort would you like to run?" << endl;
			cout << "0. Exit Program" << endl << "1. Insertion Sort" << endl << "2. Heap Sort" << endl << "3. Merge Sort" <<
				endl << "4. Quick Sort" << endl << "5. Counting Sort" << endl << "6. Bucket Sort" << endl;

			cin >> userinput;

			cout << "First 10 numbers before sorting" << endl;
			//ins.print();
			tStart = clock();
			if (userinput == 1)
			{
				cout << "Performing Insertion Sort" << endl;
				ins.insertionSort();
			}
			else if (userinput == 2)
			{
				cout << "Performing Heap Sort" << endl;
				ins.heapSort(ins.dataSet, ins.size() - 1);
			}
			else if (userinput == 3)
			{
				cout << "Performing Merge Sort" << endl;
				ins.mergesort(0, ins.size() - 1);
			}
			else if (userinput == 4)
			{
				cout << "Performing Quick Sort" << endl;
				ins.quicksort(ins.dataSet, 0, ins.size() - 1, ins.size()); //quicksort array
			}
			else if (userinput == 5)
			{
				cout << "Performing Counting Sort" << endl;
				ins.CountingSort(ins.dataSet, ins.size() - 1);
			}
			else if (userinput == 6)
			{
				cout << "Performing Bucket Sort" << endl;
				ins.bucketSort(ins.dataSet, ins.size() - 1);
			}
			else if (userinput == 0)
			{
				cout << "Thank you for using the search program" << endl;
				break;
			}
			else
			{
				cout << "There is no command for that number" << endl;
			}
		} while (userinput < 1 || userinput > 6);

		//ins.write();

		if (userinput >= 1 || userinput <= 6)
		{
			double time = (double)(clock() - tStart) / CLOCKS_PER_SEC;

			//if (time < 60)
			cout << "Time elapsed: " << time << " Seconds" << endl;
			//else if (time > 60)
			//	cout << "Time elapsed: " << time / 60 << " minutes" << endl;
			cout << "Size of the data set: " << ins.size() << endl; //<< "First 10 numbers after sorting" << endl;

																	//	ins.print();
			ins.read();
		}
		if (userinput >= 1 || userinput <= 6)
		{
			cout << "Do you want to try out a different sort? Y/N" << endl;
			cin >> repeat;
		}
	} while (repeat == 'y' || repeat == 'Y');

	system("PAUSE");
	//cin.get();
	return 0;
}