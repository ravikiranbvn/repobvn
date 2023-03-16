#include "WorkerThread.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

WorkerThread::WorkerThread(int WThCount, SyncQueue& Qobject):
              WorkThreadCount(WThCount),
              mQobject(Qobject) {
}

WorkerThread::~WorkerThread(){
 for(auto& t: thCollect) {
    if(t.joinable()) {
      t.join();
    }
  }
}

/*
Name: CreateThreeWorkerThread()
Description: This function creates three worker thread
Parameter: NA
Return Value: NA
*/
void WorkerThread::CreateThreeWorkerThread() {
   /* Create three threads */
   for(int i=0; i< WorkThreadCount; i++) {
      thCollect.push_back(std::thread(&WorkerThread::FillMTable, this));
   }
     
  for(auto& t: thCollect) {
    if(t.joinable()) {
      t.join();
    }
  }
}

/*
Name: AddWordtoMTable()
Description: This function adds words to MTable
Parameter: string str    word read from file
Return Value: NA
*/
void WorkerThread::AddWordtoMTable(std::string str) {
    std::unique_lock<std::mutex> lock(WorkThMutexobj);
    map<string, int>::iterator it = MTable.find(str);
    if (it != MTable.end())
    {
        it->second = it->second+1;
    }

    else{
        MTable.insert(std::make_pair(str, 1));
    } 
}

/*
Name: FillMTable()
Description: This function reads the file and calls AddWordtoMTable() function
Parameter: NA
Return Value: NA
*/
void  WorkerThread::FillMTable() {
       string filename= mQobject.GetFilefrmQ();
       if(!filename.empty()){
           ifstream  file;
           string line;
           
           file.open(filename.c_str());
           if (file.is_open()){
               while (getline (file,line)){
                   std::size_t prev = 0, pos;
                   while ((pos = line.find_first_of("~`=!@#$%^&*)/\?-_|[,. }](_-+{;':""></", prev)) != std::string::npos){
                       if (pos > prev){
                           AddWordtoMTable(line.substr(prev, pos-prev));
                       }
                   prev = pos+1;
                   }
                   if (prev < line.length()){
                       AddWordtoMTable(line.substr(prev, std::string::npos));
                   }
               }
               file.close();
           }
           else
           {
               cout << "-Unable to open file-" << endl;
           }
     }
}


/*
Name: getTableEntry()
Description: This function returns the MTable
Parameter: NA
Return value: multimap<int,string,greater<int>> a sorted multimap
*/
multimap<int,string,greater<int>> WorkerThread::getTableEntry(){   
   std::multimap<int,string,greater<int>> mmtbl;
   std::map<string,int>::iterator iter;
         for(iter=MTable.begin(); iter!=MTable.end(); ++iter){
             mmtbl.insert(make_pair(iter->second,iter->first));
         }
  return mmtbl;
}
