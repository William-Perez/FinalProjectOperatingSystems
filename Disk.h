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
public:
    Disk(int size);
    void setData(int trackNum, int head, int requestAmount, int direction)
    void printTable(); // prints table like in the book
    void addRequests();
    ~Disk();
};

Disk::Disk(int size)
{
    requests = int new [size];
    tracksTraversedBetween = int new [size];
}

Disk::~Disk()
{
    delete[] requests;
    delete[] tracksTraversedBetween;
}

void Disk::addRequests(int requestAmount, int numberOfTracks)
{
	int number;
	cout << "Enter requested track(s):\n";
	for (int i = 0; i < amount;i++)
	{
		cin >> number;
		if (number >= 0 && number < trackamount)
			requests[i] = number;
		else
			cout << "Error: invalid input\n";
	}
}

#endif // DISK
