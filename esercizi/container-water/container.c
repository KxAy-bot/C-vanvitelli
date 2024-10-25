#include <stdio.h>

int maxArea(int *height, int heightSize);

int main() {
  int height[] = {1,8,6,2,5,4,8,3,7};
  int size = sizeof(height) / sizeof(height[0]);

  printf("%d", maxArea(height, size));

  return 0;
}

int maxArea(int *height, int heightSize){
  int left = 0, right = heightSize - 1, max = 0;

  while (left < right) {
    int base = right - left;
    int h = (height[left] < height[right]) ? height[left] : height[right];
    int area = base * h;

    if (area > max) {
      max = area;
    }

    if (height[left] <= height[right]) {
      left++;
    } else {
      right--;
    }
  }
  
  return max;
}

