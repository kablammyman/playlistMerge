#pragma once

#include "resource.h"
#include <hash_map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string masterFilePath = "";
string addFilePath = "";
int numDupes = 0;

hash_map<string, string>  masterPlayListEntry;
typedef pair <string, string> dataPair;


int addEntries(string playListPath)
{
	ifstream m3uFile(playListPath);
	string line;
	string title;
	string path;

	if (!m3uFile.is_open())
		return -1;


	while ( getline (m3uFile,line) )
	{
		if(line == "#EXTM3U")
			continue;

		unsigned pos = line.find("#EXTINF");  
		if(pos == string::npos) //we have the path
		{
			path = line;
			if(masterPlayListEntry.count( path ) == false)
				masterPlayListEntry.insert ( dataPair ( path, title ) );
			else
				numDupes++;
				
		}
		else
			title = line;
		
	}
	m3uFile.close();

}


void updatePlaylist(string masterPlaylistPath)
{
	ofstream m3uFile;
	m3uFile.open (masterPlaylistPath);

	if(!m3uFile.is_open())
		return;

	m3uFile << "#EXTM3U\n";

	for(hash_map<string, string>::const_iterator i = masterPlayListEntry.begin(); i != masterPlayListEntry.end(); ++i)
	{
		//string title = i->second;
		//string path = i->first;
		m3uFile << i->second << "\n";
		m3uFile << i->first << "\n";
	}

	m3uFile.close();
}