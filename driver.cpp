/*****************************************************************
	Title:  	driver.cpp
	Date:  		10-10-2022
	Author: 	Robert Angel
	Purpose:	Doubly linked list of counties to use merge sort on them. The list is also a template so it can be used with anything.
******************************************************************/
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include "County.h"
#include "List.h"
using namespace std;

int main()
{
	ifstream file;
	stringstream temp;
	string line, county, state;
	int index, pop;
	file.open("counties_list.csv", ios::in);
	//file.open("counties_ten.csv", ios::in);

	//create a new list of county pointers ------------------------------------------------------------------
	List<County*> countyList;
	County* newCounty;

	if(file.good()) {
	while(getline(file, line, ','))
	{
		temp.clear();
		temp.str(line);
		temp >> index;

		getline(file, line, ',');
		county = line;

		getline(file, line, ',');
		state = line;

		getline(file, line, '\n');
		temp.clear();
		temp.str(line);
		temp >> pop;

		newCounty = new County(index, county, state, pop);
		//append newCounty to your list-----------------------------------------------------------------------------------
		countyList.appendNode(newCounty);
	}}

	file.close();
	
	//call mergesort---------------------------------------------------------------------------------------------
	countyList.mergeSort();
	//print the list-----------------------------------------------------------------------------------------------------
	countyList.print();

	return 0;
}