
#include <queue>
#include <iostream>

using namespace std;

int getMax(int *arr, int n)
{
	if (n <= 0)
		return 0;

	int max = arr[0];

	for(int i = 1; i < n; i++) {
		if(arr[i] > max)
			max = arr[i];
	}

	return max;
}

void radixAsc(int *arr, int n)
{
	if(n <= 0)
		return;

	int round = 1;
	int max = getMax(arr, n);

	max /= 10;

	while(max > 0) {
		round++;
		max /= 10;
	}

	int factor = 1;

	for(int i = 0; i < round; i++) {
		queue<int> q[10];

		for(int k = 0; k < n; k++) {
			int num = arr[k];
			q[((num / factor) % 10)].push(num);
		}

		int index = 0;

		for(int k = 0; k < 10; k++) {
			while(!q[k].empty()) {
				arr[index] = q[k].front();
				q[k].pop();
				index++;
			}
		}

		factor *= 10;
	}
}

void radixDesc(int *arr, int n)
{
	radixAsc(arr, n);

	for(int i = 0; i < n/2; i++) {
		int t = arr[i];
		arr[i] = arr[n-i-1];
		arr[n-i-1] = t;
	}
}

void radixSort(int *arr, int n)
{
	int index = -1;

	for(int k = 0; k < n; k++) {
		if(arr[k] < 0) {
			index++;
			int t = arr[k];
			arr[k] = arr[index];
			arr[index] = -t;
		}
	}

	radixDesc(arr, index+1);
	radixAsc(arr+index+1, n-index-1);

	for(int k = 0; k < index+1; k++) {
		arr[k] = -arr[k];
	}
}

int main()
{
	int arr[] = {12,2,333,45,55,-35,14,99,1,8,-290, 33,-44,76,25,0};

	radixSort(arr,16);

	for(int i = 0; i < 16; i++) {
		cout << arr[i] << " ";
	}

	cout << endl;
	cin.get();

	return 0;
}
