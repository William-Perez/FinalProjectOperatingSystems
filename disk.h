#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "TextTable.h"
using namespace std;
#ifndef DISK
#define DISK

class Disk{
private:
    int numberOfTracks; // total number of tracks
    int headStart; // position on the track where head started
    int amountOfRequests; // total amount of request
    int *requests; // pointer to array of the request
    int *tracksTraversedBetween; // tracks traversed between request
    bool direction; // direction of the head if true then head is up if false head is down
    int averageSeekTime;
	int *queue; //Ordered list
	bool scan = false;
public:
    Disk();
    Disk(int size);
    void setData(Disk& disk);
    void printTable(string algorithmName); // prints table like in the book
    void addRequests(int requestAmount, int numberOfTracks);
	int* InitializeArray();
	void SSTF();
	void SCAN();
	void CSCAN();
	void LOOK();
	void CLOOK();
	void Disk::calculateTracksTraversed(bool scan);
    string convert_toString(int i);
    void calculateSeekTime();
    ~Disk();
};

Disk::Disk(){ }

Disk::Disk(int size)
{
    requests = new int [size];
    tracksTraversedBetween = new int [size];
}

Disk::~Disk()
{
    delete[] requests;
    delete[] tracksTraversedBetween;
	delete [] queue;
}

void Disk::addRequests(int requestAmount, int numberOfTracks)
{
	int number;
	cout << "Enter requested track(s):\n";
	for (int i = 0; i < requestAmount;)
	{
		cin >> number;
		if (number >= 0 && number < numberOfTracks)
        {
			requests[i] = number;
			i++;
        }
		else if(number < 0)
			cout << "Error invalid input! Keep adding positive integers.\n";
        else
            cout << "Cannot request a track that doesn't exist!\n";
	}
}

void Disk::setData(Disk& disk)
{
    int trackNum; // number of total tracks
    int headPosition; // position of the track number
    int requestNum; // number of request that will be input
    int headMovement; // selection of which way the head will move
    bool upwards;

    do{
        cout << "How many tracks are on the disk? ";
        cin >> trackNum;
        if(trackNum <= 0)
            cout << "Please use a positive non-zero integer for the amount of tracks. Try Again!\n";
    }while(trackNum <= 0);
    cout << endl;

    do{
        cout << "Enter the location of the head: ";
        cin >> headPosition;
        if(headPosition < 0)
            cout << "Please use a non-negative integer for the head position. Try Again!\n";
        else if(headPosition >= trackNum)
            cout << "The position you are looking for does not exist in the disk. Try Again!\n";
    }while(headPosition < 0 && headPosition >= trackNum);
    cout << endl;

    do{
        cout << "Enter the amount of request that will be run: ";
        cin >> requestNum;
        if(requestNum <= 0)
            cout << "Please a positive non-zero integer for the amount of request you will inputing. Try Again!\n";
    }while(requestNum <= 0);
    cout << endl;
    requests = new int[requestNum];
    addRequests(requestNum, trackNum);

    do{
        cout << "In which direction is the head moving? Upwards or Downwards?\n";
        cout << "1.Upwards\n";
        cout << "2.Downwards\n";
        cout << "Enter: ";
        cin >> headMovement;

        if(headMovement == 1)
            upwards = true;
        else if(headMovement == 2)
            upwards = false;
        else
            cout << "Invalid Input! Try Again!\n";
    }while(headMovement!= 1 && headMovement != 2);
    cout << endl;

    numberOfTracks = trackNum;
    headStart = headPosition;
    amountOfRequests = requestNum;
    direction = upwards;
    tracksTraversedBetween = new int [requestNum];
}

void Disk::printTable(string algorithmName)
{
    stringstream track, travel;
    TextTable t('-', '|', '+');
    cout << setw(23) << algorithmName << endl;
    t.add("Next Track Accessed");
    t.add("Number of Tracks Traversed");
    t.endOfRow();

    for(int i = 0; i < amountOfRequests; i++)
    {
        t.add(convert_toString(requests[i]));
        t.add(convert_toString(tracksTraversedBetween[i]));
        t.endOfRow();
    }
    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    cout << t;
    cout << endl;
    calculateSeekTime();
    cout << "Average Seek Time: " << averageSeekTime << endl;
    cout << "Press Enter to Continue!\n";
    cin.get();
    cin.get();
    cout << endl;
}

string Disk::convert_toString(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

void Disk::calculateSeekTime()
{
    int avg = 0;

    for(int i = 0; i < amountOfRequests; i++)
    {
        avg += tracksTraversedBetween[i];
    }

    avg /= amountOfRequests;
    averageSeekTime = avg;
}

void Disk::SSTF()
{
	int current = headStart, temp;
	bool *used;
	
	queue = new int[amountOfRequests];
	used = new bool[amountOfRequests];
	for (int i = 0; i < amountOfRequests; i++)
		used[i] = false;

	for (int j = 0; j < amountOfRequests; j++)
	{
		int seektime = 1000000;
		for (int i = 0; i < amountOfRequests;i++)
		{

			if ((abs(requests[i] - current) < seektime) && !(used[i]))
			{
				temp = i;
				seektime = abs(requests[i] - current);

			}
			if (i == amountOfRequests - 1)
			{
				queue[j] = temp;
				used[temp] = true;
			}
		}
		current = requests[queue[j]];

	}
	/*cout << requests[queue[0]] << " | " << abs(headStart - requests[queue[0]]) << endl;
	for (int i = 1; i < amountOfRequests;i++)
	{
		cout << requests[queue[i]] << " | " << abs(requests[queue[i - 1]] - requests[queue[i]]) << endl;
	}*/
}

void Disk::SCAN()
{
	delete [] queue;
	queue = new int[amountOfRequests];
	for (int i = 0; i < amountOfRequests; i++)
	{
		queue[i] = requests[i];
	}
	int temp;
	for (int i = 0;i<amountOfRequests;i++)
	{
		for (int j = 0;j<amountOfRequests;j++)
		{
			if (queue[i] > queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	for (int i = 0; queue[i] > headStart;i++)
	{
		for (int j = 0; j<amountOfRequests;j++)
		{
			if (queue[i] < queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	if (!direction)
	{
		for (; queue[0] > headStart;)
		{
			temp = queue[0];
			for (int i = 0; i < amountOfRequests - 1; i++)
			{
				queue[i] = queue[i + 1];
			}
			queue[amountOfRequests - 1] = temp;
		}
	}
	for (int i = 0; i < amountOfRequests; i++)
	{
		cout << queue[i] << endl;
	}
}

void Disk::CSCAN()
{
	delete [] queue;
	queue = new int[amountOfRequests];
	for (int i = 0; i < amountOfRequests; i++)
	{
		queue[i] = requests[i];
	}
	int temp;
	for (int i = 0;i<amountOfRequests;i++)
	{
		for (int j = 0;j<amountOfRequests;j++)
		{
			if (queue[i] > queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	for (int i = 0; queue[i] > headStart;i++)
	{
		for (int j = 0; j<amountOfRequests;j++)
		{
			if (queue[i] < queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	for (int i = 0;i<amountOfRequests;i++)
	{
		for (int j = 0;j<amountOfRequests;j++)
		{
			if (queue[i] < queue[j] && queue[j] < headStart)
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	if (!direction)
	{
		if (amountOfRequests % 2)
		{
			for (int i = 0; i != (amountOfRequests / 2);i++)
			{
				temp = queue[i];
				queue[i] = queue[amountOfRequests - (1 + i)];
				queue[amountOfRequests - (1 + i)] = temp;
				temp = i;
			}
			int i = temp + 1;
			temp = queue[i];
			queue[i] = queue[amountOfRequests - (1 + i)];
			queue[amountOfRequests - (1 + i)] = temp;
		}
		else
		{
			for (int i = 0; (queue[i + 1] != queue[amountOfRequests - (1 + i)]);i++)
			{
				temp = queue[i];
				queue[i] = queue[amountOfRequests - (1 + i)];
				queue[amountOfRequests - (1 + i)] = temp;
				temp = i;
			}
			int i = temp + 1;
			temp = queue[i];
			queue[i] = queue[amountOfRequests - (1 + i)];
			queue[amountOfRequests - (1 + i)] = temp;
		}
	}
	for (int i = 0; i < amountOfRequests; i++)
	{
		cout << queue[i] << endl;
	}

}

void Disk::CLOOK()
{
	delete [] queue;
	queue = new int[amountOfRequests];
	for (int i = 0; i < amountOfRequests; i++)
	{
		queue[i] = requests[i];
	}
	int temp;
	for (int i = 0;i<amountOfRequests;i++)
	{
		for (int j = 0;j<amountOfRequests;j++)
		{
			if (queue[i] > queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	for (int i = 0; queue[i] > headStart;i++)
	{
		for (int j = 0; j<amountOfRequests;j++)
		{
			if (queue[i] < queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	for (int i = 0;i<amountOfRequests;i++)
	{
		for (int j = 0;j<amountOfRequests;j++)
		{
			if (queue[i] < queue[j] && queue[j] < headStart)
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	if (!direction)
	{
		if (amountOfRequests % 2)
		{
			for (int i = 0; i != (amountOfRequests / 2);i++)
			{
				temp = queue[i];
				queue[i] = queue[amountOfRequests - (1 + i)];
				queue[amountOfRequests - (1 + i)] = temp;
				temp = i;
			}
			int i = temp + 1;
			temp = queue[i];
			queue[i] = queue[amountOfRequests - (1 + i)];
			queue[amountOfRequests - (1 + i)] = temp;
		}
		else
		{
			for (int i = 0; (queue[i + 1] != queue[amountOfRequests - (1 + i)]);i++)
			{
				temp = queue[i];
				queue[i] = queue[amountOfRequests - (1 + i)];
				queue[amountOfRequests - (1 + i)] = temp;
				temp = i;
			}
			int i = temp + 1;
			temp = queue[i];
			queue[i] = queue[amountOfRequests - (1 + i)];
			queue[amountOfRequests - (1 + i)] = temp;
		}
	}
	for (int i = 0; i < amountOfRequests; i++)
	{
		cout << queue[i] << endl;
	}
}

void Disk::LOOK()
{
	delete [] queue;
	queue = new int[amountOfRequests];
	for (int i = 0; i < amountOfRequests; i++)
	{
		queue[i] = requests[i];
	}
	int temp;
	for (int i = 0;i<amountOfRequests;i++)
	{
		for (int j = 0;j<amountOfRequests;j++)
		{
			if (queue[i] > queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	for (int i = 0; queue[i] > headStart;i++)
	{
		for (int j = 0; j<amountOfRequests;j++)
		{
			if (queue[i] < queue[j])
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}
	if (!direction)
	{
		for (; queue[0] > headStart;)
		{
			temp = queue[0];
			for (int i = 0; i < amountOfRequests - 1; i++)
			{
				queue[i] = queue[i + 1];
			}
			queue[amountOfRequests - 1] = temp;
		}
	}
	for (int i = 0; i < amountOfRequests; i++)
	{
		cout << queue[i] << endl;
	}
}

int numgen(int trackamount)
{
	int random_integer;
	random_integer = (rand() % trackamount) + 1;
	//cout << random_integer << endl;
	return random_integer;
}

void Disk::calculateTracksTraversed(bool scan)
{
	for (int i = 0; i < amountOfRequests; i++)
	{
		if (i == 0)
		{
			tracksTraversedBetween[0] = abs(headStart - requests[0]);
		}
		else
		{
			tracksTraversedBetween[i] = abs(requests[i - 1] - requests[i]);
			if (scan)
			{
				if (direction)
				{
					if (requests[i - 1] > requests[i])
					{
						tracksTraversedBetween[i] += (2 * (headStart - requests[i - 1]));
					}
				}
				else
				{
					if (requests[i - 1] < requests[i])
					{
						tracksTraversedBetween[i] += (2 * (headStart - requests[i - 1]));
					}
				}
			}
		}
	}
}

#endif // DISK



#endif // DISK
