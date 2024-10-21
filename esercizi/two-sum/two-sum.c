#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize);

void print_array(int *array, int size) {
  printf("[");
  for (int i = 0; i < size; i++) {
    if (i == size - 1) {
      printf(" %d", i);
    } else {
      printf(" %d,", i);
    }
  }
  printf("]");
}

int main() {
  int nums[] = {2, 7, 11, 15};
  int target = 9;
  int numsSize = sizeof(nums) / sizeof(nums[0]);
  int returnSize;

  int *indexes = twoSum(nums, numsSize, target, &returnSize);
  print_array(indexes, returnSize);

  return 0;
}

typedef struct {
  int key;
  int value;
} HashTable;

int hash(int key, int size) { return abs(key) % size; }

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  *returnSize = 2;
  int hashTableSize = numsSize * 2;
  HashTable *hashTable = (HashTable *)calloc(hashTableSize, sizeof(HashTable));

  for (int i = 0; i < numsSize; i++) {
    int complement = target - nums[i];
    int hashIndex = hash(complement, hashTableSize);

    if (hashTable[hashIndex].key == complement) {
      int *result = (int *)malloc(*returnSize * sizeof(int));
      result[0] = hashTable[hashIndex].value;
      result[1] = i;
      free(hashTable);
      return result;
    }

    hashIndex = hash(nums[i], hashTableSize);
    hashTable[hashIndex].key = nums[i];
    hashTable[hashIndex].value = i;
  }

  free(hashTable);
  return NULL;
}
