#include <stdio.h>
#include <stdlib.h>

void printArray(int* array, int size){
  for(int i = 0; i < size; i++){
    printf("%d ", array[i]);
  }
}

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  int totalSize = nums1Size + nums2Size;
  int array[totalSize], indexCounter = 0;

  for(int i = 0; i < nums1Size; i++){
    array[indexCounter++] = nums1[i];
  }

  for(int i = 0; i < nums2Size; i++){
    array[indexCounter++] = nums2[i];
  }

  qsort(array, totalSize, sizeof(int), compare);

  int middle = totalSize / 2;

  printArray(array, totalSize);

  if(totalSize % 2 == 0)
    return (double)(array[middle] + array[middle - 1]) / 2.0;
  else
    return array[middle];
}

int main(){
  int num1[] = {1, 3};
  int num2[] = {2};

  int num1Size = sizeof(num1) / sizeof(num1[0]);
  int num2Size = sizeof(num2) / sizeof(num2[0]);

  findMedianSortedArrays(num1, num1Size, num2, num2Size);
  return 0;
}

