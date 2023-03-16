#include "SyncQueue.h"
using namespace std;

SyncQueue::SyncQueue()
{
	CountFileSize = 0;
}

SyncQueue::~SyncQueue()
{
}


/*
Name: AddFileNameinQ()
Description: This function add filepath to synchornized queue
Parameter: string filepath
Return value: NA
 */
void SyncQueue::AddFileNametoQ(string filepath)
{
	std::unique_lock<std::mutex> lock(MutexObject);
	Queue.push(filepath);
	CountFileSize++;
}

/*
Name: GetFilefrmQ()
Description: This function read the filepath from synchronized queue
Parameter: NA
Return value : string    filepath
 */
string SyncQueue::GetFilefrmQ(){
        std::unique_lock<std::mutex> lock(MutexObject);
	string filename="";
	if(!Queue.empty()){
		filename = Queue.front();
		Queue.pop();
	}
	
	return filename;
}

/*
Name: GetCount()
Description: This function returns the size of synchronized queue
             This check is required before fetching filepath from queue
Parameter: NA
Return value: int
 */
int SyncQueue::GetCount() {
	int CountSize = 0;
	CountSize=Queue.size();
	return CountSize;
}

/*
Name: GetFileCount()
Description: This function returns the total number of file processed by synchornized queue
Parameter: NA
Return value: int
 */
int SyncQueue::GetFileCount() {
	return CountFileSize;
}
