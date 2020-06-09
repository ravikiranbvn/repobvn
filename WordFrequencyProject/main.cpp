//File : main.cpp

#include "SyncQueue.h"
#include "WorkerThread.h"
#include "SearchThread.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <ftw.h>
#include <fnmatch.h>
#include <signal.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <utility>
#include <iterator>
#include <map>
#include <iomanip>
using namespace std;

//max 3 worker thread
const unsigned int WThreadCount = 3;

//Queue object
SyncQueue Qobject;

int main(int argc, char * argv[]){

	string path;
	bool searchStatus = false;
	cout<<"Please specify the directory path: "<<endl;
	cin>>path;

	DIR *pDir;
	pDir = opendir(path.c_str());

	if(pDir==NULL){
		cout << endl << "Directory doesn't exists" << endl;
		return -1;
	}

	closedir(pDir);

	cout << endl <<"Please wait while processing...." <<  endl;

	//Creating Search thread to add .txt file in Queue
	SearchThread STobject;
	searchStatus = STobject.StartSearchTxtFiles(path);

	//Creating worker threads
	WorkerThread WThread(WThreadCount);
	WThread.CreateThreeWorkerThread();

	while(1){
		if(searchStatus && !(Qobject.GetCount()))
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
