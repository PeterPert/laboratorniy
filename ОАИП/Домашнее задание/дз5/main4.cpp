#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int> numbers;
	for (int i = 0; i < n; i++) {
		int h;
		cin >> h;
		numbers.push_back(h);
	}
	numbers.erase(remove_if(numbers.begin(), numbers.end(), [](int n) { return n < 0; }), numbers.end());
	for (int x : numbers) {
		cout << x << " ";
	}
	return 0;
}