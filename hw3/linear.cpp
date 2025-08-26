
// Return false if the somePredicate function returns false for at
    // least one of the array elements; return true otherwise.
  bool allTrue(const std::string a[], int n){
      if (n <= 0) return true;
      else if (n == 1) return somePredicate(a[0]);
      else {
          return allTrue(a+1, n-1) && somePredicate(a[0]);
      }
  }

    // Return the number of elements in the array for which the
    // somePredicate function returns true.
  int countTrue(const std::string a[], int n)
  {
      if (n <= 0) return 0;
      else if (n == 1){
          if (somePredicate(a[0])){
              return 1;
          }
          else return 0;

      }
      else {
          return (countTrue(a+1, n-1) + somePredicate(a[0]));
      }
  }

    // Return the subscript of the first element in the array for which
    // the somePredicate function returns true.  If there is no such
    // element, return -1.
  int firstTrue(const std::string a[], int n)
{
      if (n <= 0) return -1;
      
      if (somePredicate(a[0])) return 0;
      
      int result = firstTrue(a + 1, n - 1);
      if (result == -1) return -1;
      return result + 1;
  }

    // Return the subscript of the first string in the array that is >= all
    // strings in the array (i.e., return the smallest subscript m such
    // that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
    // that no strings are to be considered to be in the array, return -1.
  int locateMax(const std::string a[], int n){
      if (n <= 0) return -1;
      
      if (n == 1) return 0;
      
      else{
          int currentMax = locateMax(a+1, n-1) + 1;
          if (a[0] >= a[currentMax]) return 0;
          else return currentMax;
      }
  }

    // If all n2 elements of a2 appear in the n1 element array a1, in
    // the same order (though not necessarily consecutively), then
    // return true; otherwise (i.e., if the array a1 does not include
    // a2 as a not-necessarily-contiguous subsequence), return false.
    // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
    // For example, if a1 is the 7 element array
    //    "donald" "keir" "claudia" "jinping" "keir" "claudia" "narendra"
    // then the function should return true if a2 is
    //    "keir" "jinping" "narendra"
    // or
    //    "keir" "claudia" "claudia"
    // and it should return false if a2 is
    //    "keir" "narendra" "jinping"
    // or
    //    "donald" "jinping" "jinping"
  bool contains(const std::string a1[], int n1, const std::string a2[], int n2){
      if (n2 <= 0) return true;
      if (n2 > n1 || n1 <= 0) return false;
      
      if (a1[0] == a2[0]){
          return contains(a1+1, n1-1, a2+1, n2-1);
      }
      
      return contains(a1+1, n1-1, a2, n2);
  }

