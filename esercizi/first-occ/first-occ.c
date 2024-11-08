#include <stdio.h>
#include <string.h>

int strStr(char *haystack, char *needle);

int main() {
  char haystack[] = "sadbutsad";
  char needle[] = "but";

  printf("output: %d\n", strStr(haystack, needle));
  return 0;
}

int strStr(char *haystack, char *needle) {
  int haystackLen = strlen(haystack), needleLen = strlen(needle);

  int left = 0, right = needleLen - 1;

  while (right < haystackLen) {
    if (strncmp(haystack + left, needle, needleLen) == 0) {
      return left;
    }

    left++;
    right++;
  }
  return -1;
}
