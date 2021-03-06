#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
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
    int *queue;
    int queueSize;
    bool scan = false;
public:
    Disk();
    Disk(int size);
    void setData();
    void printTable(string algorithmName); // prints table like in the book
    void addRequests(int requestAmount, int numberOfTracks);
    string convert_toString(int i);
    void calculateSeekTime();
    int getAmountOfRequests();
    void setHeadStart();
    int getNumberOfTracks();
    void setDirection();
    void arrivals();
	void FIFO();
    void SSTF();
  	void SCAN();
  	void CSCAN();
  	void LOOK();
  	void CLOOK();
  	void calculateTracksTraversed(bool scan);

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
    delete[] queue;
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

void Disk::setData()
{
    int trackNum; // number of total tracks
    int requestNum; // number of request that will be input
    do{
        cout << "How many tracks are on the disk? ";
        cin >> trackNum;
        if(trackNum <= 0)
            cout << "Please use a positive non-zero integer for the amount of tracks. Try Again!\n";
    }while(trackNum <= 0);
    cout << endl;
    numberOfTracks = trackNum;

    setHeadStart();
    cout << endl;

    do{
        cout << "Enter the amount of request that will be run: ";
        cin >> requestNum;
        if(requestNum <= 0)
            cout << "Please a positive non-zero integer for the amount of request you will inputing. Try Again!\n";
    }while(requestNum <= 0);
    cout << endl;
    amountOfRequests = requestNum;
    requests = new int[requestNum];
    addRequests(requestNum, trackNum);

    setDirection();
    cout << endl;
    queueSize = requestNum;
}

void Disk::printTable(string algorithmName)
{
    stringstream track, travel;
    TextTable t('-', '|', '+');
    cout << setw(23) << algorithmName << endl;
    t.add("Next Track Accessed");
    t.add("Number of Tracks Traversed");
    t.endOfRow();

    for(int i = 0; i < queueSize; i++)
    {
        t.add(convert_toString(queue[i]));
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

int Disk::getAmountOfRequests()
{
    return amountOfRequests;
}

void Disk::setHeadStart()
{
    int headPosition; // position of the track number

    do{
        cout << "Enter the location of the head: ";
        cin >> headPosition;
        if(headPosition < 0)
            cout << "Please use a non-negative integer for the head position. Try Again!\n";
        else if(headPosition >= numberOfTracks)
            cout << "The position you are looking for does not exist in the disk. Try Again!\n";
    }while(headPosition < 0 && headPosition >= numberOfTracks);

    headStart = headPosition;
}

int Disk::getNumberOfTracks()
{
    return numberOfTracks;
}

void Disk::setDirection()
{
    int headMovement;
    bool upwards;
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

    direction = upwards;
}

void Disk::FIFO()
{
	for (int i = 0; i < amountOfRequests;i++)
	{
		queue[i] = requests[i];
	}
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
	delete[] queue;
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
	delete[] queue;
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
	delete[] queue;
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
	delete[] queue;
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
	tracksTraversedBetween = new int[queueSize];
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
						tracksTraversedBetween[i] += (2 * abs(headStart - requests[i - 1]));
					}
				}
				else
				{
					if (requests[i - 1] < requests[i])
					{
						tracksTraversedBetween[i] += (2 * abs(headStart - requests[i - 1]));
					}
				}
			}
		}
	}
}

void Disk::arrivals()
{
	int arrivalAmount = numgen(20);
	int *temp;
	queueSize = amountOfRequests + arrivalAmount;
	temp = new int[queueSize];
	for (int i = 0; i < amountOfRequests; i++)
	{
		temp[i] = queue[i];
	}
	for (int i = amountOfRequests; i < queueSize; i++)
	{
		temp[i] = numgen(numberOfTracks);
	}
	delete[] queue;
	queue = new int[queueSize];
	for (int i = 0; i < queueSize; i++)
	{
		queue[i] = temp[i];
	}
	delete[] temp;
}

#endif // DISK

