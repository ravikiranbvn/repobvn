//File : WorkerThread.h

#pragma once

#include "SyncQueue.h"
#include <map>
#include <thread>
#include <mutex>

class WorkerThread{
    public :
        WorkerThread(int WThCount, SyncQueue& Qobject);
        ~WorkerThread();
        
        /*creates three thread*/
        void CreateThreeWorkerThread();
        
        /*filles MTable with words*/
        void FillMTable();
        
        /*return MTable*/
        std::multimap<int, std::string, std::greater<int>> getTableEntry(); /* To get sorted table */

    private:        
        void AddWordtoMTable(std::string);
        std::map<std::string,int> MTable;
        std::mutex WorkThMutexobj;
        int WorkThreadCount;
        std::vector<std::thread> thCollect;
        SyncQueue& mQobject;
};
