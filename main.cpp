#include <iostream>
#include <cmath>

using namespace std;

/*void FIFO(int *q, int start, int amount, int trackamount)
{
	cout << "Request | Tracks Traveled\n";
	cout << q[0]<<" | "<< q[0] - start<<endl;
	for (int i = 1; i < amount;i++)
	{
		cout << q[i] << " | " << abs(q[i-1] - q[i])<<endl;
	}
}

void SSTF(int *q, int start)
{
	//int tracks[];

}*/


int main()
{
	int start, trackamount, amount, *q;
	cout << "Enter number of tracks\n";
	cin >> trackamount;
	cout << "Enter starting track\n";
	cin >> start;
	cout << "Enter amount of requests\n";
	cin >> amount;
	q = InitializeArray(amount, trackamount);
	FIFO(q, start, amount, trackamount);
	system("pause");
	return 0;
}
