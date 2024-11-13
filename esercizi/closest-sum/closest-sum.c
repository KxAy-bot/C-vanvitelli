#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int threeSumClosest(int *nums, int numsSize, int target);

int main() {
  int array[] = {-1, 2, 1, -4};
  int dim = sizeof(array) / sizeof(array[0]);
  int target = 1;

  printf("%d", threeSumClosest(array, dim, target));
  return 0;
}

int threeSumClosest(int *nums, int numsSize, int target) {
  int closestSum = INT_MAX;
  int minDiff = INT_MAX;

  for (int i = 0; i < numsSize - 2; i++) {
    for (int j = i + 1; j < numsSize - 1; j++) {
      for (int k = j + 1; k < numsSize; k++) {
        int sum = nums[i] + nums[j] + nums[k];
        int diff = abs(sum - target);

        if (diff < minDiff) {
          minDiff = diff;
          closestSum = sum;
        }
      }
    }
  }

  return closestSum;
}
