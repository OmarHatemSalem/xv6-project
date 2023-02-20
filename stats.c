#include "types.h"
#include "stat.h"
#include "user.h" 
#include "float.h"

#define INT_MAX 2147483647

void merge(int arr[], int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        // if (!isdigit(number[i]))
        if (number[i] > '9' || number[i] < '0')
            return 0;
    }
    return 1;
}

float sqrt(float x, int precision)
{
    int start = 1, end = x;
    int mid;
    float ans = 0;
    
    while (start <= end) {
           //calculating mid value
        mid = (start + end) / 2;
        //if square of mid is equal to x then we return mid value
        if (mid * mid == x) {

            ans = mid;

            break;

        }
        //if square of mid is less than x then we search in only right half of array
        if (mid * mid < x) {

            start = mid + 1;

            ans = mid;

        }
        ////if square of mid is greater than x then we search in only left half of array
        else {

            end = mid - 1;

        }   

    }
    float increment = 0.1;
 //caluculating precision and this loop ends if ans square is greater than x
    for (int i = 0; i < precision; i++) {

        while (ans * ans <= x) {
             
            ans += increment;

        }
        ans = ans - increment;

        increment = increment / 10;

    }

    return ans;
}

void calc_stats(int arr[], int n) 
{
    float sum = 0, minScore=INT_MAX, maxScore=-1*INT_MAX, sumSq = 0, count=0;

    for (int i=0; i<n; i++) {
        float arri = (float)arr[i];
        sum += arri;
        minScore = (minScore > arri) ? arri : minScore;
        maxScore = (maxScore > arri) ? maxScore : arri;
        sumSq += arri*arri;
        count++;

    }

    sum /= count;
    sumSq = sumSq/count - (sum*sum);
   
    // printf(1, "printf: %f\n", (sum));
    // printf(1, "printf: %f\n", 1.34);
    // printf(1, "printf: %f\n", 0.344);

    printf(1, "Average: ");
    printfloat(1, sum);
    printf(1, "\nSTDEV: ");
    printfloat(1,  sqrt(sumSq, 10));
    printf(1, "\nMin: ");
    printfloat(1, minScore);
    printf(1, "\nMax: ");
    printfloat(1, maxScore);
    printf(1, "\n");

    mergeSort(arr, 0, n-1);
    printf(1, "Median: %d\n", arr[n/2]);

}

int main(int argc, char *argv[])
{
    int n = argc - 1;
    int* arr = (int*) malloc(n*sizeof(int));

    for (int i=0; i<n; i++) {
      // printf(1, "%c\n", argv);
      if (!isNumber(argv[i+1])) {
        printf(2, "Entires must be an integer\n");
        exit();
      } else if(argv[i+1][0] == '-') {
        arr[i] = -1*atoi(argv[i+1]+1);
      } else {
        arr[i] = atoi(argv[i+1]);
      }
    }

    calc_stats(arr, n);
    exit();


}