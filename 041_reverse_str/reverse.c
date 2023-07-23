#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// first copy to a temp
// reverse temp to the target array

int cal_length(char *array) {
    int n = 0;
    char *ptr = array;
    while (*ptr != '\0')
    {
        n++;
        ptr++;
    }
    return n;
}

void reverse(char * str) {
  if (str == NULL)
    return;
  size_t num = cal_length(str);
  char temp[num];
  for (size_t i = 0; i < num; i++)
  {
    temp[i] = str[i];
  }
  
  for (size_t i = 0; i < num; i++)
  {
    str[i] = temp[num - 1 - i];
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
