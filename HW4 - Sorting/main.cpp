#include <iostream>
#include "Array2D.h"
using namespace std;

// Swap two elements in a generic array
template<typename E>
inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

// For use with min-heap and sorting
class minintCompare {
public:
  static bool prior(int x, int y) { return x < y; }
};

// For use with max-heap and heapsorting
class maxintCompare {
public:
  static bool prior(int x, int y) { return x > y; }
};

/*********************** Insertion Sort ***********************/

// Insertion sort implementation
template <typename E, typename Comp>
void inssort(E A[], int n) { // Insertion Sort
  for (int i=1; i<n; i++)       // Insert i'th record
    for (int j=i; (j>0) && (Comp::prior(A[j], A[j-1])); j--)
      swap(A, j, j-1);
}

/************************* Bubble Sort ************************/

// Bubble sort implementation
template <typename E, typename Comp>
void bubsort(E A[], int n) { // Bubble Sort
  for (int i=0; i<n-1; i++)     // Bubble up i'th record
    for (int j=n-1; j>i; j--)
      if (Comp::prior(A[j], A[j-1]))
        swap(A, j, j-1);
}

/*********************** Selection Sort ***********************/

template <typename E, typename Comp>
void selsort(E A[], int n) { // Selection Sort
  for (int i=0; i<n-1; i++) {   // Select i'th record
    int lowindex = i;           // Remember its index
    for (int j=n-1; j>i; j--)   // Find the least value
      if (Comp::prior(A[j], A[lowindex]))
	lowindex = j;           // Put it in place
    swap(A, i, lowindex);
  }
}

/************************* Shell Sort *************************/

// Modified version of Insertion Sort for varying increments
template <typename E, typename Comp>
void inssort2(E A[], int n, int incr) {
  for (int i=incr; i<n; i+=incr)
    for (int j=i; (j>=incr) &&
                  (Comp::prior(A[j], A[j-incr])); j-=incr)
      swap(A, j, j-incr);
}

template <typename E, typename Comp>
void shellsort(E A[], int n) { // Shellsort
  for (int i=n/2; i>2; i/=2)      // For each increment
    for (int j=0; j<i; j++)       // Sort each sublist
      inssort2<E,Comp>(&A[j], n-j, i);
  inssort2<E,Comp>(A, n, 1);
}

/************************* Merge Sort *************************/

template <typename E, typename Comp>
void mergesort(E A[], E temp[], int left, int right) {
  if (left == right) return;        // List of one element
  int mid = (left+right)/2;
  mergesort<E,Comp>(A, temp, left, mid);
  mergesort<E,Comp>(A, temp, mid+1, right);
  for (int i=left; i<=right; i++)   // Copy subarray to temp
    temp[i] = A[i];
  // Do the merge operation back to A
  int i1 = left; int i2 = mid + 1;
  for (int curr=left; curr<=right; curr++) {
    if (i1 == mid+1)      // Left sublist exhausted
      A[curr] = temp[i2++];
    else if (i2 > right)  // Right sublist exhausted
      A[curr] = temp[i1++];
    else if (Comp::prior(temp[i1], temp[i2]))
      A[curr] = temp[i1++];
    else A[curr] = temp[i2++];
  }
}

template <typename E, typename Comp>
void mergesort(E* array, int n) {
  static E* temp = NULL;
  if (temp == NULL) temp = new E[n];  // Declare temp array
  mergesort<E,Comp>(array, temp, 0, n-1);
}

/************************* Quick Sort *************************/

// Simple findpivot: Pick middle value in array
template <typename E>
inline int findpivot(E A[], int i, int j)
  { return (i+j)/2; }

// Partition the array
template <typename E, typename Comp>
inline int partition(E A[], int l, int r, E& pivot) {
  do {             // Move the bounds inward until they meet
    while (Comp::prior(A[++l], pivot));  // Move l right and
    while ((l < r) && Comp::prior(pivot, A[--r])); // r left
    swap(A, l, r);              // Swap out-of-place values
  } while (l < r);              // Stop when they cross
  return l;      // Return first position in right partition
}

// qsort core function: Basic qsort
template <typename E, typename Comp>
void qsort(E A[], int i, int j) { // Quicksort
  if (j <= i) return; // Don't sort 0 or 1 element
  int pivotindex = findpivot(A, i, j);
  swap(A, pivotindex, j);    // Put pivot at end
  // k will be the first position in the right subarray
  int k = partition<E,Comp>(A, i-1, j, A[j]);
  swap(A, k, j);             // Put pivot in place
  qsort<E,Comp>(A, i, k-1);
  qsort<E,Comp>(A, k+1, j);
}

template <typename E, typename Comp>
void quicksort(E* array, int n) {
  qsort<E,Comp>(array, 0, n-1);
}

/******************** Quick Sort Optimized ********************/

int THRESHOLD = 10;

// qsort2 core function: do not qsort2 lists of length <= THRESHOLD
template <typename E, typename Comp>
void qsort2(E array[], int i, int j) {
  if ((j-i) <= THRESHOLD) return; // Don't sort short list
  int pivotindex = findpivot(array, i, j);
  swap(array, pivotindex, j); // stick pivot at end
  int k = partition<E,Comp>(array, i-1, j, array[j]);
  swap(array, k, j);          // Put pivot value in place
  qsort2<E,Comp>(array, i, k-1);
  qsort2<E,Comp>(array, k+1, j);
}

template <typename E, typename Comp>
void quicksort2(E* array, int n) {
   qsort2<E,Comp>(array, 0, n-1);
  inssort<E,Comp>(array, n); // Cleanup sort
}

/************************* Heap Sort **************************/

// Include the heap implementation
#include "heap.h"

// Standard heapsort implementation
template <typename E, typename Comp>
void heapsort(E A[], int n) { // Heapsort
  E maxval;
  heap<E,Comp> H(A, n, n);    // Build the heap
  for (int i=0; i<n; i++)        // Now sort
    maxval = H.removefirst();    // Place maxval at end
}

int main(int argc, char const *argv[])
{
  // Allocating memory space
  Array2D<int> num10    = Array2D<int>(1000000, 10);  // 1M sets
  Array2D<int> num100   = Array2D<int>(1000000, 100); // 1M sets
  Array2D<int> num100K  = Array2D<int>(10, 100000);
  Array2D<int> num1M    = Array2D<int>(10, 1000000);

  FILE* fp = fopen("results.csv", "w");
  if (fp == NULL){
    printf("Cannot open the file for writing!");
    exit(1);
  }

  fprintf(fp, "Sort, 10, 100, 100K, 1M, Up100K, Down100K\n");

  fprintf(fp, "Insertion, %f, %f, %f, NaN, %f, %f\n",
            num10.getRandomTime(&inssort<int, minintCompare>),
           num100.getRandomTime(&inssort<int, minintCompare>),
          num100K.getRandomTime(&inssort<int, minintCompare>),
          //num1M.getRandomTime(&inssort<int, minintCompare>),
          num100K.getSortedTime(&inssort<int, minintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&inssort<int, minintCompare>, quicksort<int, maxintCompare>)
          );

  fprintf(fp, "Bubble, %f, %f, %f, NaN, %f, %f\n",
            num10.getRandomTime(&bubsort<int, minintCompare>),
           num100.getRandomTime(&bubsort<int, minintCompare>),
          num100K.getRandomTime(&bubsort<int, minintCompare>),
          //num1M.getRandomTime(&bubsort<int, minintCompare>),
          num100K.getSortedTime(&bubsort<int, minintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&bubsort<int, minintCompare>, quicksort<int, maxintCompare>)
          );

  fprintf(fp, "Selection, %f, %f, %f, NaN, %f, %f\n",
            num10.getRandomTime(&selsort<int, minintCompare>),
           num100.getRandomTime(&selsort<int, minintCompare>),
          num100K.getRandomTime(&selsort<int, minintCompare>),
          //num1M.getRandomTime(&selsort<int, minintCompare>),
          num100K.getSortedTime(&selsort<int, minintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&selsort<int, minintCompare>, quicksort<int, maxintCompare>)
          );

  fprintf(fp, "Shell, %f, %f, %f, %f, %f, %f\n",
            num10.getRandomTime(&shellsort<int, minintCompare>),
           num100.getRandomTime(&shellsort<int, minintCompare>),
          num100K.getRandomTime(&shellsort<int, minintCompare>),
            num1M.getRandomTime(&shellsort<int, minintCompare>),
          num100K.getSortedTime(&shellsort<int, minintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&shellsort<int, minintCompare>, quicksort<int, maxintCompare>)
          );

  // For some reason merge sort does not work.
  // fprintf(fp, "Merge, %f, %f, %f, %f, %f, %f\n",
  //           num10.getRandomTime(&mergesort<int, minintCompare>),
  //          num100.getRandomTime(&mergesort<int, minintCompare>),
  //         num100K.getRandomTime(&mergesort<int, minintCompare>),
  //           num1M.getRandomTime(&mergesort<int, minintCompare>),
  //         num100K.getSortedTime(&mergesort<int, minintCompare>, quicksort<int, minintCompare>),
  //         num100K.getSortedTime(&mergesort<int, minintCompare>, quicksort<int, maxintCompare>)
  //         );

  fprintf(fp, "Quick, %f, %f, %f, %f, %f, %f\n",
            num10.getRandomTime(&quicksort<int, minintCompare>),
           num100.getRandomTime(&quicksort<int, minintCompare>),
          num100K.getRandomTime(&quicksort<int, minintCompare>),
            num1M.getRandomTime(&quicksort<int, minintCompare>),
          num100K.getSortedTime(&quicksort<int, minintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&quicksort<int, minintCompare>, quicksort<int, maxintCompare>)
          );

  fprintf(fp, "Quick/O, %f, %f, %f, %f, %f, %f\n",
            num10.getRandomTime(&quicksort2<int, minintCompare>),
           num100.getRandomTime(&quicksort2<int, minintCompare>),
          num100K.getRandomTime(&quicksort2<int, minintCompare>),
            num1M.getRandomTime(&quicksort2<int, minintCompare>),
          num100K.getSortedTime(&quicksort2<int, minintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&quicksort2<int, minintCompare>, quicksort<int, maxintCompare>)
          );

  fprintf(fp, "Heap, %f, %f, %f, %f, %f, %f\n",
            num10.getRandomTime(&heapsort<int, maxintCompare>),
           num100.getRandomTime(&heapsort<int, maxintCompare>),
          num100K.getRandomTime(&heapsort<int, maxintCompare>),
            num1M.getRandomTime(&heapsort<int, maxintCompare>),
          num100K.getSortedTime(&heapsort<int, maxintCompare>, quicksort<int, minintCompare>),
          num100K.getSortedTime(&heapsort<int, maxintCompare>, quicksort<int, maxintCompare>)
          );


  fclose(fp);

  return 0;
}
