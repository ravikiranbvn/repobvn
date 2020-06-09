//File : WorkerThread.h
//Desc : This class creates three worker threads.
//		Thease threads read the queue filled by SearchThread module.
//		these three threads are live untill the search is over
//		Once search is over one flag is set by SearchThread module to stop WorkerThread.
//Date : 10 Jan 2015
//Author : Kripal Thakur

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include "SyncQueue.h"
#include <map>
#include <thread>
#include <mutex>


class WorkerThread{
    public :
        WorkerThread(int WThCount);
        ~WorkerThread();
        
        /*creates three thread*/
        void CreateThreeWorkerThread();
        
        /*filles MTable with words*/
        void FillMTable();
        
        /*return MTable*/
        multimap<int,string,greater<int>> getTableEntry(); /* To get sorted table */

    private:        
        void AddWordtoMTable(string);
        map<string,int> MTable;
        mutex WorkThMutexobj;
        int WorkThreadCount;
        std::thread t[3];
};
#endif /* WORKERTHREAD_H */
