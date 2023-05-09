//File : main.cpp

#include "SyncQueue.h"
#include "WorkerThread.h"
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

//max 3 worker thread
const unsigned int WThreadCount = 3;

int main(int argc, char * argv[]){

       //Queue object
       SyncQueue Qobject;

	string path;
	cout<<"Please specify the directory path: "<<endl;
	cin>>path;
	
	for(const auto& entry: fs::recursive_directory_iterator(path)) {
           if(entry.is_regular_file()) {
             if(entry.path().extension().string() == ".txt") {
                Qobject.AddFileNametoQ(entry.path());
           }
	  }
        }
	cout << endl <<"Please wait while processing...." <<  endl;
	
	//Creating worker threads
	WorkerThread WThread(WThreadCount, Qobject);
	WThread.CreateThreeWorkerThread();

	while(1) {
	   if(!Qobject.GetCount())
	   {
	     break;
	   }
	}

	multimap<int,string,greater<int>> MMtable;
	MMtable = WThread.getTableEntry();

	cout << endl <<"Total files Processed "<< Qobject.GetFileCount() << endl;

	cout << "***********************************************"<<endl;
	cout << "count" << "---------" << "Words" <<endl;
	cout << "***********************************************"<<endl;

	int i=0;
	for(auto iter=MMtable.begin(); iter!=MMtable.end(); ++iter){
		std::cout << iter->first << "-------------" << iter->second << std::endl;
		i++;
		if(i==10) //To get only top 10 words.
			break;
	}
	cout << "***********************************************"<<endl;

	return 0;
}
