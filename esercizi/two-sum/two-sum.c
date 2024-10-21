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

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  *returnSize = 2;

  int *result = (int *)malloc(*returnSize * sizeof(int));

  for (int i = 0; i < numsSize; i++) {
    for (int j = i + 1; j < numsSize; j++) {
      if (nums[i] + nums[j] == target) {
        result[0] = i;
        result[1] = j;
        return result;
      }
    }
  }

  return NULL;
}
