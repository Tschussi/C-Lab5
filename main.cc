// Kevin Hames Ece 2620
/* The Bubble Sort and Merge Sorts have theoretical runtimes of O(n^2) 
and O(N log N) respectively. This lab is consistent with these theoretical 
run times as the Bubble Sort takes a large amount of time, much longer than 
the Merge Sort (Have not run the bubble sort to completion due to several hour
run time). The merge sort also takes a short amount of time, about .6 seconds.
This is shorter than the theoretical run time but relatively congruent compared
to the bubble sort.
 * 
 */
#include <iostream>
#include<fstream>
#include <ctime>

using namespace std;
#define MAXSIZE 2100000

// sorting in ascending order
void BubbleSort(long int data[], int n)
{
	long int temp; 
	for(int i = 0; i < n-1; i++) {
		for(int j = n-1; j > i; --j) {
			if(data[j] < data[j-1]) // swapping 
			{
				temp = data[j];
				data[j] = data[j-1];
				data[j-1] = temp;
			}
			
		}
	}
}

void Merge(long int numbers[], int i, int j, int k) {
   int mergedSize = k - i + 1;       // Size of merged partition
   long int mergedNumbers[mergedSize];    // Temporary array for merged numbers
   int mergePos = 0;                 // Position to insert merged number
   int leftPos = 0;                  // Position of elements in left partition
   int rightPos = 0;                 // Position of elements in right partition
   
   leftPos = i;                      // Initialize left partition position
   rightPos = j + 1;                 // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] < numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
}

void MergeSort(long int numbers[], int i, int k) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
} 

void printarray( long int *a, int n ) {
	for( int i = 0; i < n; i++ ) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main()
{
	// Declaring Variables
	ifstream  infile;
	ofstream  bubble;
	ofstream  merge;
	infile.open("lab5_input.txt");
	bubble.open("lab5_bubbleout.txt");
	merge.open("lab5_mergeout.txt");
	int i = 0;
	int n = 0; 
	long int x;
	long int *ray = new long int[MAXSIZE];
	int menu;
	double begin_time, end_time, cpu_time_used;

	// Menu
	while(menu!=4) {
	cout << "(1) Read Data from input file" << endl << "(2) Sort Data using Bubble Sort" << endl << "(3) Sort Data using Merge Sort" << endl << "(4) Exit" << endl;	
	cin >> menu;
	switch (menu) {
		case 1 : // Reading in values from text file
		if (infile.is_open())
		{
			 while (infile >> x)   
			{
				ray[i] = x;
				i++;
				n++;
			}
		} 
			break;
		case 2 : // calling and timing the Bubble Sort
			begin_time = clock();
			BubbleSort(ray, MAXSIZE);
			end_time = clock();
			cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
			cout << cpu_time_used << endl;
			// Putting Sorted data in bubbleout.txt
			for(int k = 0; k < n; ++k) 
			{ 
				bubble << ray[k] << endl;
			}
			break;
		case 3 : // Calling and timing the Merge Sort
			begin_time = clock();
			MergeSort(ray,0,MAXSIZE);
			end_time = clock();
			cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
			cout << cpu_time_used << endl;
			// Putting Sorted data in mergeout.txt
			for(int k = 0; k < n; ++k) 
			{ 
				merge << ray[k] << endl;
			}
			break;
		case 4: // Exit
			break;
		default:
			cout << "Invalid option" << endl;
	}
	}
	infile.close();
	bubble.close();
	merge.close();
	delete[] ray;
	return 0;
}

