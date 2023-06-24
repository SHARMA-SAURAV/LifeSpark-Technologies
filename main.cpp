#include <iostream>
#include <vector>

using namespace std;

vector<int> findLongestSubarray(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> longestSubarray;
    int longestLength = 0;
    int start = 0;
    int end = 0;
    int sum = 0;

    while (end < n) {
        sum += arr[end];

        if (end - start + 1 >= longestLength && sum / (end - start + 1) >= k) {
            longestLength = end - start + 1;
            longestSubarray = vector<int>(arr.begin() + start, arr.begin() + end + 1);
        }

        if (sum / (end - start + 1) < k) {
            sum = 0;
            start = end + 1;
        }

        end++;
    }

    return longestSubarray;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int k = 4;
    int x=5;

    vector<int> result = findLongestSubarray(arr, k);
    cout << "A subarray greater than or equal to k: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    vector <int> answer=findLongestSubarray(result,x);
    cout<<"A subarray from the array is greater than or equal to x:  ";
    for(int num : answer){
        cout<<num<<" ";
    }
    cout<<endl;

    return 0;
}