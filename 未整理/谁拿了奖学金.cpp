#include <iostream>
#include <string>
using namespace std;
string name;
int score = 0, sum = 0;
int main()
{
	int n = 0;
	cin >> n;
	string na;
	int qm = 0, bj = 0, art = 0;
	char gb = 0, west = 0;
	for (int i = 1; i <= n; ++i)
	{
		cin >> na >> qm >> bj >> gb >> west >> art;
		int get = 0;
		if (qm > 80 && art >= 1)
			get += 8000;
		if (qm > 85 && bj > 80)
			get += 4000;
		if (qm > 90)
			get += 2000;
		if (west == 'Y' && qm > 85)
			get += 1000;
		if (gb == 'Y' && bj > 80)
			get += 850;
		sum += get;
		if (get > score)
		{
			score = get;
			name = na;
		}
	}
	cout << name << endl
		 << score << endl
		 << sum;
	return 0;
}