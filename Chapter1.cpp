#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

// Answer 1
bool isUnique(string s) {
  bool counting_table[256] = {false, };
  for (int i = 0; i < s.length(); i++) {
    int val = s[i];
    if (counting_table[val] == true)
      return false;
    counting_table[val] = true;
  }
  return true;
}

// Answer 2
void reverseString(char* s) {
  int len = strlen(s);
  char temp;
  for (int i = 0; i < len / 2; i++) {
    temp = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = temp;
  }
  return;
}

// Answer 3
void removeDuplicate(char* s) {
  if (!s)
    return;
  int tail = 1;
  for (int i = 1; i < strlen(s); i++) {
    int j;
    for (j = 0; j < tail; j++) {
      if (s[i] == s[j]) {
	break;
      }
    }
    if (j == tail) {
      s[tail] = s[i];
      tail++;
    }
  }
  s[tail] = 0;
}

// Answer 4
bool isAnagram(string s1, string s2) {
  if (s1.length() != s2.length())
    return false;
  int table[256] = {0, };
  int totalChar = 0;
  int completeChar = 0;

  for (int i = 0; i < s1.length(); i++) {
    if (table[s1[i]] == 0)
      totalChar++;
    table[s1[i]]++;
  }

  for (int i = 0; i < s2.length(); i++) {
    if (table[s2[i]] == 0)
      return false;
    table[s2[i]]--;
    if (table[s2[i]] == 0)
      completeChar++;
  }
  if (totalChar != completeChar)
    return false;
  return true;
}

// Answer 5
void replaceSpace(char *str) {
  int numSpace = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == ' ')
      numSpace++;
  }

  int newLength = strlen(str) + numSpace * 2;
  str[newLength] = 0;
  newLength--;

  for (int i = strlen(str) - 1; i >=0; i--) {
    if (str[i] == ' ') {
      str[newLength] = '0';
      str[newLength - 1] = '2';
      str[newLength - 2] = '%';
      newLength = newLength - 3;

    } else {
      str[newLength] = str[i];
      newLength--;
    }
  }
  return;
}

// Answer 6
void rotateImage(int *image, int size) {
  int row, column;
  if (size % 2) {
    row = size / 2;
    column = size / 2 + 1;
  } else {
    row = column = size / 2;
  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      int temp = image[i * size + j];
      image[i * size + j] = image[(size - 1 - j) * size + i];
      image[(size - 1 - j) * size + i] = image[(size - 1 - i) * size + (size - 1 - j)];
      image[(size - 1 - i) * size + (size - 1 - j)] = image[j * size + (size - 1 - i)];
      image[j * size + (size - 1 - i)] = temp;
    }
  }
}

// Answer 7
void clearRowCol(int *array, int r, int c) {
  bool* row = (bool *)calloc(0, sizeof(bool) * r);
  bool* col = (bool *)calloc(0, sizeof(bool) * c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (array[i * r + j] == 0) {
	row[i] = true;
	col[j] = true;
      }
    }
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (row[i] || col[j]) {
	array[i * r + j] = 0;
      }
    }
  }

}

// Answer 8
bool isRotation(char* s1, char* s2) {
  if (strlen(s1) != strlen(s2))
    return false;

  char* newStr = (char *)malloc(sizeof(char) * (strlen(s1) * 2 + 1));
  strcpy(newStr, s1);
  strcat(newStr, s1);

  char* p = strstr(newStr, s2);
  free(newStr);
  return p;
}

int main() {
  // Question 1
  cout << isUnique("abcd") << endl;
  cout << isUnique("aaa") << endl;
  cout << isUnique("baa") << endl;
  cout << isUnique("") << endl;
  cout << isUnique("ababa") << endl << endl;

  // Question 2
  char s[6] = "abcde";
  cout << "Before " << s << endl;
  reverseString(s);
  cout << "After " << s << endl << endl;
  
  // Question 3
  char a[] = "";
  removeDuplicate(a);
  cout << a << endl;

  char b[] = "abcd";
  removeDuplicate(b);
  cout << b << endl;

  char c[] = "aabb";
  removeDuplicate(c);
  cout << c << endl;

  char d[] = "abab";
  removeDuplicate(d);
  cout << d << endl;

  char e[] = "aaaa";
  removeDuplicate(e);
  cout << e << endl << endl;

  // Question 4
  cout << isAnagram("", "") << endl;
  cout << isAnagram("abc", "ab") << endl;
  cout << isAnagram("aabcc", "acbca") << endl;
  cout << isAnagram("abcd", "aabc") << endl;
  cout << isAnagram("abccba", "aabbcc") << endl << endl;

  // Question 5
  char f[] = "";
  replaceSpace(f);
  cout << "After " << f << endl;
  
  char g[] = " ";
  replaceSpace(g);
  cout << "After " << g << endl;

  char h[] = "a b c ";
  replaceSpace(h);
  cout << "After " << h << endl << endl;

  // Question 6
  int array[8 * 8];
  int array2[9 * 9];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      array[i * 8 + j] = i * 10 + j;
    }
  }

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      array2[i * 9 + j] = i * 10 + j;
    }
  }
  
  rotateImage(array, 8);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << array[i * 8 + j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  rotateImage(array2, 9);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << array2[i * 9 + j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  // Question 7
  array[0] = 0;
  array[4 * 8 + 5] = 0;
  array2[4 * 9 + 4] = 0;
  array2[4 * 9 + 5] = 0;
  clearRowCol(array, 8, 8);
  clearRowCol(array2, 9, 9);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << array[i * 8 + j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << array2[i * 9 + j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  

  // Question 8
  char i[] = "waterflower", j[] = "terflowerwa", k[] = "water"; 
  cout << isRotation(k, f) << endl;
  cout << isRotation(i, j) << endl;
  cout << isRotation(f, f) << endl << endl;

  return 0;
}
