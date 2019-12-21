/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
#include "dbLib.h"
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}
void Finalization() {
    // Release your data before exiting
}
bool cityNameTocityId(TCity&City, string cityName) {
	if (City.name == cityName) return true;
	else return false;
}
bool findcityid(TLine& Line, int cityid) {
	if (Line.city_id == cityid) return true;
	return false;
}
bool findstationid(TStation& Station, int cityid) {
	if (Station.city_id == cityid) return true;
	return false;
}
bool findlineid(TLine& Line, int cityid) {
	if (Line.city_id == cityid) return true;
	return false;
}
////////////////
bool findstationid(TStation_Line& Stationline, int lineID) {
	if (Stationline.line_id == lineID) return true; 
	return false; 
}
bool findstationid(TStation& Station, string stationName) {
	if (Station.name == stationName) return true;
	return false;
}

bool findmaxid(TStation& Station, int id_max) {
	if (Station.id > id_max) {
		return true; 
	}
	return false;
}
//Re10 + 
bool findstation_id(TStation& Station, int id){
	if (Station.id == id) return true; 
	return false; 
}
//Re10: 
bool findstationid_STALINE(TStation_Line& T, int station_ID) {
	if (T.station_id == station_ID) return true; 
	return false; 
}
bool findtrackid(TTrack& Track, int trackid) {
	if (Track.id == trackid) return true; 
	return false; 
}
//RE13
bool rmove(TStation_Line&T, int compare1, int compare2) {
	if (T.station_id == compare1 && T.line_id == compare2) return true; 
	return false; 
}
//RE RS 
bool findcity_id(TTrack& Track, int city_ID) {
	if (Track.city_id == city_ID) return true;
	return false;
}




void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
	// TODO: Implement this function for processing a request
	// NOTE: You can add other functions to support this main process.
	//       pData is a pointer to a data structure that manages the dataset
	//       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
	//       N is the size of output, must be a non-negative number
	TDataset* myData = new TDataset();
	myData = (TDataset*)pData;
	string str1, str2, str3;
	stringstream ss;
	ss << pRequest;
	ss >> str1 >> str2 >> str3;
	// Implement Request............................................................................................
	//REQUEST1: CL
	if (str1 == "CL" && str2 == "")
	{
		pOutput = new int*();
		*((int*)pOutput) = myData->get_SizeOFLine();
		N = 1;
	}
	//Request2: CL + cityName
	else if (str1 == "CL" && str2 != "")
	{
		//string cityName = "";
		//if (str3 != "") cityName = str2 + " " + str3;
		//else cityName = str2;
		//int cityid = myData->citiesList->traverse(cityNameTocityId, cityName).id;
		//L1List <TLine> *regLine = new L1List<TLine>;
		//myData->linesList->traverse(findcityid, cityid, regLine); 
		////cout << regLine->at(2).name; 
		//pOutput = new int(regLine->getSize()); 
		//N = 1;
		string cityName = "";
		int count = 0;
		int count_cities = myData->citiesList->getSize();
		int count_lines = myData->linesList->getSize();
		if (str3 != "") cityName = str2 + " " + str3;
		else cityName = str2;
		int saveID = 0; int isFind = 0;
		for (int i = 1; i <= count_cities; i++)
		{
			if (cityName == myData->citiesList->at(i).name)
			{
				isFind = 1;
				saveID = myData->citiesList->at(i).id;
				//break;
			}
		}
		if (isFind == 0) {
			isFind = -1;
		}
		pOutput = new int(isFind);
		if (isFind == 1) {
			for (int i = 1; i <= count_lines; i++)
			{
				if (saveID == myData->linesList->at(i).city_id)count++;
			}
			if (count != 0) {
				pOutput = new int(count);
				N = 1;
			}
			else {
				pOutput = new int(0);
				N = 1;
			}
		}
	}
	//Request3: LSC
	else if (str1 == "LSC")
	{
		string cityName = "";
		///////////////////////////////////////
		if (str3 != "") cityName = str2 + " " + str3;
		else cityName = str2;
		int cityid = myData->citiesList->traverse(cityNameTocityId, cityName).id;
		L1List <TStation> *regStationid = new L1List<TStation>;
		myData->stationList->traverse(findstationid, cityid, regStationid);
		int length = regStationid->getSize();
		int * arr = new int[length];
		for (int i = 0; i < length; i++) {
			arr[i] = regStationid->at(i + 1).id;
		}
		pOutput = arr;
		N = length;
	}
	//Request4: LLC
	else if (str1 == "LLC")
	{
		string cityName = "";
		if (str3 != "") cityName = str2 + " " + str3;
		else cityName = str2;
		int cityid = myData->citiesList->traverse(cityNameTocityId, cityName).id;
		L1List <TLine> *regLineid = new L1List<TLine>;
		myData->linesList->traverse(findlineid, cityid, regLineid);
		int length = regLineid->getSize();
		int * arr = new int[length];
		for (int i = 0; i < length; i++) {
			arr[i] = regLineid->at(i + 1).id;
		}
		pOutput = arr;
		N = length;
	}
	//Request5: LSL
	else if (str1 == "LSL")
	{
		int line_ID = stoi(str2);
		L1List <TStation_Line> *regstationid = new L1List<TStation_Line>;
		myData->station_lineList->traverse(findstationid, line_ID, regstationid);
		int length = regstationid->getSize();
		int * arr = new int[length];
		for (int i = 0; i < length; i++) {
			arr[i] = regstationid->at(i + 1).station_id;
		}
		pOutput = arr;
		N = length;
	}
	//Request6: FC
	else if (str1 == "FC")
	{
		string cityName = ""; 
		if (str3 != "") cityName = str2 + " " + str3;
		else cityName = str2;
		int check = myData->citiesList->traverseR_str(cityNameTocityId, cityName); 
		if (check == 0) {
			int cityid = myData->citiesList->traverse(cityNameTocityId, cityName).id;
			pOutput = new int(cityid);
			N = 1;
		}
		else {
			pOutput = new int(-1); 
			N = 1; 
		}
	}
	//Request7: FS
	else if (str1 == "FS")
	{
		string stationName = "";
		string input = pRequest + 3;
		stringstream stst(input);
		string tmp = "";
		if (stst.peek() == '"') {
			getline(stst, stationName, '"');
			getline(stst, stationName, '"');
			getline(stst, tmp, ',');
		}
		else  getline(stst, stationName, ',');
		int check = myData->stationList->traverseR_str(findstationid, stationName);
		if (check == 0) {
			int stationid = myData->stationList->traverse(findstationid, stationName).id;
			pOutput = new int(stationid);
			N = 1;
		}
		else {
			pOutput = new int(-1); 
			N = 1; 
		}
	}
	//Request8: SLP
	else if (str1 == "SLP")
	{
		//test : SLP 8004 3826
		int index = 0;
		string geoSta = "";
		string geoTra = "";
		int station_id = stoi(str2);
		int track_id = stoi(str3);
		if (myData->stationList->traverseR(findstation_id, station_id) == 0 && myData->tracksList->traverseR(findtrackid, track_id) == 0)
		{
			geoSta = myData->stationList->traverse(findstation_id, station_id).geometry;
			cout << geoSta << endl; cout << endl;
			geoSta = geoSta.substr(6, geoSta.length() - 7);
			
			geoTra = myData->tracksList->traverse(findtrackid, track_id).geometry;
			cout << geoTra << endl;
			geoTra = geoTra.substr(11, geoTra.length() - 12);
			
			string tmp = "";
			stringstream ss(geoTra); //cai linestring 
			getline(ss, tmp, ',');
			bool check = false;
			while (tmp != "")
			{
				if (tmp != geoSta) //cai POINT
				{
					index++;
					if (!(getline(ss, tmp, ','))) break;
				}
				else {
					check = true;
					break;
				}
			}
			if (check = false) { pOutput = new int(-1); N = 1; }
			else { pOutput = new int(index); N = 1; }
		}
		else { pOutput = new int(-1); N = 1;}
		
	}
	//Request9: IS
	else if (str1 == "IS") 
	{
		string inSert = pRequest + 3;
		stringstream stst(inSert);
		string tmp = "";
		TStation stationNode;
		////////////////////////////////////////////
		static int id_max;
		int id_in = myData->stationList->traverse1(findmaxid, id_max).id + 1;
		stationNode.id = id_in; 
		cout << stationNode.id << endl; 
		if (stst.peek() == '"') {
			getline(stst, stationNode.name, '"');
			getline(stst, stationNode.name, '"');
			getline(stst, tmp, ',');
		}
		else getline(stst, stationNode.name, ',');
		cout << stationNode.name << endl;
		getline(stst, tmp, ',');
		if (tmp != "") stationNode.geometry = tmp;
		cout << stationNode.geometry << endl;
		getline(stst, tmp, ',');
		if (tmp != "") stationNode.buildstart = stoi(tmp);
		else stationNode.buildstart = -1;
		cout << stationNode.buildstart << endl;
		getline(stst, tmp, ',');
		if (tmp != "") {
			stationNode.opening = stoi(tmp);
			cout << stationNode.opening << endl;
		}
		else stationNode.opening = -1;
		getline(stst, tmp);
		if (tmp != "") stationNode.closure = stoi(tmp);
		cout << stationNode.closure << endl;
		myData->stationList->push_back(stationNode);
		pOutput = new int(id_in);
		N = 1;
	}
	//Request10: RS 
	else if (str1 == "RS")
	{
		int station_ID = stoi(str2); int id = station_ID;  int index1, index2 = 1;
		string geoSta = ""; string geoTra = "";
		//STATION.CSV: remove station which has id the same id_re
		geoSta = myData->stationList->traverse(findstation_id, id).geometry;
		cout << geoSta <<endl;
		string subgeoSta = geoSta.substr(6, geoSta.length() - 7);
		cout << subgeoSta << endl;
		int track_size = myData->tracksList->getSize(); 
		cout << "tracksize: " << track_size <<endl; 
		for (int i = 1; i <= track_size; i++) {
			string geoTra= myData->tracksList->at(i).geometry;
			string subgeoTra = geoTra.substr(11, geoTra.length() - 12);
			cout << geoTra << endl; 
			int found = subgeoTra.find(subgeoSta);
			cout << found << endl; 
			if (found >= 0) {
				if (found != 0) {
					string in = "LINESTRING(" + subgeoTra.erase(found - 1, (subgeoSta.length())) + ")";
					myData->tracksList->at(i).geometry = in;
					cout << myData->tracksList->at(i).geometry;
					break;
				}
				else
				{
					string in = "LINESTRING(" + subgeoTra.erase(found, (subgeoSta.length()) + 1) + ")";
					myData->tracksList->at(i).geometry = in;
					cout << myData->tracksList->at(i).geometry;
					break;
				}	
			}
		}
		if (myData->stationList->traverseR(findstation_id, id) == 0)
		{
			index1 = myData->stationList->traverseI(findstation_id, id);
			myData->stationList->remove(index1);
			pOutput = new int(0);
			N = 1;
		}

		//STATIONLINE.CSV : remove station which has station_id the same sation_id_request
		if (myData->station_lineList->traverseR(findstationid_STALINE, station_ID) == 0)
		{
			index2 = myData->station_lineList->traverseI(findstationid_STALINE, station_ID);
			//cout << endl; cout << index2; cout << endl;
			myData->station_lineList->remove(index2);
		}
		else
		{
			pOutput = new int(-1);
			N = 1;
		}
	}
	//Request11: US
	else if (pRequest[0] == 'U' && pRequest[1] == 'S')
	{
	//US 7694 "Tuan anh",POINT(2.1 41.41),,0,195
		int station_ID = stoi(str2);
		int len = str2.length();
		string upgrade = pRequest + len + 4;
		TStation stationNode;
		int index = myData->stationList->traverseI(findstation_id, station_ID);
		cout << endl; 
		cout << index; 
		cout << endl; 
		int result = myData->stationList->traverseR(findstation_id, station_ID);
		pOutput = new int(result); 
		N = 1; 
		stringstream stst(upgrade);
		string tmp = "";
		stationNode.id = station_ID;
		if (stst.peek() == '"') {
			getline(stst, stationNode.name, '"');
			getline(stst, stationNode.name, '"');
			getline(stst, tmp, ',');
		}
		else getline(stst, stationNode.name, ',');
		myData->stationList->at(index).name = stationNode.name;
		cout << stationNode.name << endl;
		getline(stst, tmp, ',');
		if (tmp != "") stationNode.geometry = tmp;
		myData->stationList->at(index).geometry = stationNode.geometry;
		cout << stationNode.geometry << endl;
		getline(stst, tmp, ',');
		if (tmp != "") stationNode.buildstart = stoi(tmp); else stationNode.buildstart = -1;
		myData->stationList->at(index).buildstart = stationNode.buildstart;
		cout << stationNode.buildstart << endl;
		getline(stst, tmp, ',');
		if (tmp != "")  stationNode.opening = stoi(tmp);
		myData->stationList->at(index).opening = stationNode.opening;
		cout << stationNode.opening << endl;
		getline(stst, tmp);
		if (tmp != "") stationNode.closure = stoi(tmp);
		myData->stationList->at(index).closure = stationNode.closure;
		cout << stationNode.closure << endl;
	}
	//Request12: ISL
	else if (str1 == "ISL")
	{
	//TEST:  ISL 1604 571 2 
	int station_ID = stoi(str2);
	int line_ID = stoi(str3);
	int count_station_lines = myData->station_lineList->getSize(); 
	int len2 = str2.length();
	int len3 = str3.length();
	bool isFound = false;
	int index = stoi(pRequest + len2 + len3 + 6);
	int count = 0;

	// Duyet de lay phan tu cua mang arrIdx 
	for (int i = 1; i <= count_station_lines; i++)
	{
		if (line_ID == myData->station_lineList->at(i).line_id)
		{
			count++;
			if (station_ID == myData->station_lineList->at(i).station_id) {
				isFound = true;
				pOutput = new int(-1);
				N = 1;
				break;
			}
		}
	}


	//Neu khong tim thay thi insert: 
	if (isFound == false)

	{
		pOutput = new int(0);
		N = 1;
		//station.id == stationid: count ++ ; 
		int *arrIdx = new int[count];
		int p_i = 0;
		for (int i = 0; i < count_station_lines; i++) {
			if (line_ID == myData->station_lineList->at(i + 1).line_id) {
				arrIdx[p_i] = i + 1;
				p_i++;
			}
		}
		TStation_Line stationLineNode;
		stationLineNode.station_id = station_ID;
		stationLineNode.line_id = line_ID;
		stationLineNode.id = -1;
		stationLineNode.city_id = -1;
		stationLineNode.created_at = "";
		stationLineNode.updated_at = "";


		myData->station_lineList->insert(arrIdx[index] - 1, stationLineNode);
	}
	}
	
	//Request13: RSL
	else if (str1 == "RSL") {
		//RSL 7729 571 
		int station_ID = stoi(str2);
		int line_ID = stoi(str3);
		int result = myData->station_lineList->traverseR2(rmove, station_ID, line_ID); 
		pOutput = new int(result); N = 1; 
		int index = myData->station_lineList->traverseI2(rmove, station_ID, line_ID); 
		myData->station_lineList->remove(index); 
	}


	



		
}
	



		


	

	


