#include <iostream>

using namespace std;


const int MOD = 1e9 + 7;

int arr[1000000];

/*         n --> No. of elements present in input array.
    BITree[0..n] --> Array that represents Binary Indexed Tree.
    arr[0..n-1] --> Input array for which prefix sum is evaluated. */

// Returns sum of arr[0..index]. This function assumes
// that the array is preprocessed and partial sums of
// array elements are stored in BITree[].
long long int getSum(long long int BITree[], long long int index)
{
    long long int sum = 0; // Initialize result

    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse ancestors of BITree[index]
    while (index>0)
    {
        // Add current element of BITree to sum
        sum += BITree[index];
        sum %= MOD;

        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return sum;
}

// Updates a node in Binary Index Tree (BITree) at given index
// in BITree. The given value 'val' is added to BITree[i] and
// all of its ancestors in tree.
void updateBIT(long long int BITree[], long long int n, long long int index, long long int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse all ancestors and add 'val'
    while (index <= n)
    {
    // Add 'val' to current node of BI Tree
    BITree[index] += val;
    BITree[index] %= MOD;

    // Update index to that of parent in update View
    index += index & (-index);
    }
}

// Constructs and returns a Binary Indexed Tree for given
// array of size n.
long long int *constructBITree(long long int n)
{
    // Create and initialize BITree[] as 0
    long long int *BITree = new long long int[n+1];
    for (long long int i=1; i<=n; i++)
        BITree[i] = 0;

    // Store the actual values in BITree[] using update()

    // Uncomment below lines to see contents of BITree[]
    //for (long long int i=1; i<=n; i++)
    //     cout << BITree[i] << " ";

    return BITree;
}

long long int combinaiton(long long int n) {
    return (n * (n - 1)) / 2;
}

int main() {
    long long int n;
    long long int result = 0;
    cin >> n;
    long long int* indicator = constructBITree(n);
    long long int* left = constructBITree(n);
    long long int* right = constructBITree(n);
    for(long long int i = 0; i < n ; i++) {
        int inp;
        cin >> inp;
        arr[inp] = i;
    }
    for(int i = n; i >= 1; i--) {

        long long int left_getSum = getSum(indicator, arr[i]);
        long long int right_getSum = getSum(indicator, n - 1) - getSum(indicator, arr[i]);
        long long int right_sum = getSum(right, n - 1) - getSum(right, arr[i]);
        long long int left_Sum = getSum(left, arr[i]);

        updateBIT(left, n, arr[i], left_getSum);
        updateBIT(right, n, arr[i], right_getSum);
        updateBIT(indicator, n, arr[i], 1);
        long long int left_result = (combinaiton(left_getSum) - left_Sum) % MOD;
        long long int right_result = (combinaiton(right_getSum) - right_sum) % MOD;
        result = (result + (left_result * right_result) % MOD) % MOD;
    }
    cout << result << "\n";
    return 0;
}
