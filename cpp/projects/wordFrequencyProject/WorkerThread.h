//File : WorkerThread.h

#pragma once

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
