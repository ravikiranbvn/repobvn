/*
 * Psavesearch.cpp
 *
 *  Created on: 10.06.2020
 *      Author: bulusur
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

void saveToFile(vector<tuple<int, string, string, bool>> const & data){

	ofstream myFile;
	myFile.open("filepath", std::ios_base::app);
	if(myFile.is_open())
	{
		for (const auto &e : data)
			myFile << get<0>(e) <<" "<< get<1>(e) <<" " << get<2>(e) <<" "<< get<3>(e) << "\n";

		cout << "***PATTERNS SAVED***" << endl;
	}
	else
		cout << "Unable to open file while saving" <<endl;

	myFile.close();
}

void searchPattern(){

	typedef tuple<int,string,string,bool>pData;
	vector<pData>data;

	int id;
	string name, filePath;
	bool flag = false;

	ifstream readFile("filepath");
	if(readFile.is_open())
	{
		while(readFile >> id >>name>>filePath>>flag){
			data.push_back(make_tuple(id,name,filePath,flag));
		}
		readFile.close();
	}
	else
	{
		cout << "Unable to open file while searching" << endl;
	}

	int i, SEL;
	string nameFile;
	bool flagValue;

	cout << "SEARCH BY (1)ID (2)NAME (3)PATH (4)FLAG :" << endl;
	cin >> SEL;

	switch(SEL){
	case 1:
		cout <<"\nEnter ID : ";
		cin >> i;
		for(auto row : data){
			if(get<0>(row) == i){
				cout << get<0>(row)<<", " << get<1>(row)<<", "  << get<2>(row)<<", "<< get<3>(row)<<endl;
			}
		}
		break;
	case 2:
		cout <<"\nENTER NAME : ";
		cin >> nameFile;
		for(auto row : data){
			if(get<1>(row) == nameFile){
				cout << get<0>(row)<<", " << get<1>(row)<<", "  << get<2>(row)<<", "<< get<3>(row)<<endl;
			}
		}
		break;
	case 3:
		cout <<"\nENTER FILE PATH : ";
		cin >> nameFile;
		for(auto row : data){
			if(get<2>(row) == nameFile){
				cout << get<0>(row)<<", " << get<1>(row)<<", "  << get<2>(row)<<", "<< get<3>(row)<<endl;
			}
		}
		break;
	case 4:
		cout <<"\nENTER FLAG VALUE : ";
		cin >> flagValue;
		for(auto row : data){
			if(get<3>(row) == flagValue){
				cout << get<0>(row)<<", " << get<1>(row)<<", "  << get<2>(row)<<", "<< get<3>(row)<<endl;
			}
		}
		break;
	}


}

int main()
{
	int inputSel;
	cout << "***Selection Menu****" << endl;
	cout << "Input: (1) Enter a new pattern call (2) Search the previous pattern calls : " << endl;
	cin  >> inputSel;

	int id;
	string name, filePath;
	bool flag = false;
	typedef tuple<int,string,string,bool>pData;
	vector<pData>pList;

	switch(inputSel)
	{
	case 1:
		cout << "Enter id, name, filepath, status" << endl;
		cin >> id >> name >> filePath >> flag;
		pList.push_back(make_tuple(id, name, filePath, flag));

		// Save new pattern
	    saveToFile(pList);
		break;

	case 2:
	    // search pattern
		searchPattern();
		break;

	default:
		break;
	}

	return 0;
}


