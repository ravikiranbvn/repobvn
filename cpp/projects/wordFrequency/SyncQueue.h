//File : Queue.h
//Desc : This creates queue to to store .txt files. SearchThread fill this queue untill the searching is over.

#pragma once 

#include <string>
#include <mutex>
#include <queue>
#include <iostream>

class SyncQueue{
public:
     SyncQueue();
    ~SyncQueue();

     /*writes filename in Queue */
     void AddFileNametoQ(std::string filename);

     /*reads the filename from Queue and returns the filename */
     std::string GetFilefrmQ(void);
                       
     /*returns nubmer of files present queue*/
     int GetCount();
                
     /*returns number of files processed by queue*/
     int GetFileCount();
                                
private :
     //mutext object for synchronization on queue
     std::mutex MutexObject;
 
     //synchronized queue to save filename. This queue is processed by Searchthread and Workerthread  
     std::queue<std::string> Queue;
                
     //store number of files processed by queue       
     int CountFileSize; 
};
