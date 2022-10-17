/* find an element in array such that
sum of left array is equal to sum of right
array */

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
 
int findElement(int arr[], int n)
{
  /*  for (int i = 1; i < n; i++) {
        int leftSum = 0;
        for (int j = i - 1; j >= 0; j--) {
            leftSum += arr[j];
        }
 
        int rightSum = 0;
        for (int k = i + 1; k < n; k++) {
            rightSum += arr[k];
        }
 
        if (leftSum == rightSum) {
            return arr[i];
        }
    }
 
    return -1;*/


    // 2nd method (using prefix and suffix array)

    int  prefixSum[n];
    prefixSum[0] = arr[0];
    for (int i = 1; i<n; i++)
    prefixSum[i] = prefixSum[i-1]+arr[i];
    // forming suffix sum array from n-1
    int  suffixSum[n];
    suffixSum[n-1] =arr[n-1];
    for(int i = n-2; i>=0;i--)
      suffixSum[i] = suffixSum[i+1]+arr[i];


      // finding the point where prefix and suffix
      // sum are same 
      for (int i=1; i<n-1;i++)
      if (prefixSum[i]== suffixSum[i])
        return arr[i];
        return -1;
}


 
int main()
{
    // Case 1
    int arr1[] = { 1, 4, 2, 5 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << findElement(arr1, n1) << "\n";
 
    // Case 2
    int arr2[] = { 2, 3, 4, 1, 4, 5 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << findElement(arr2, n2);
    return 0;
}
