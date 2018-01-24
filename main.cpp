#include <iostream>
#include <cmath>
#include "disk.h"

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

}
*/


int main()
{
    Disk userDisk;
	userDisk.setData(userDisk);
	userDisk.printTable("FIFO");

	return 0;
}
