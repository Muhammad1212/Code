
//******************************************************************
//
// CSCI 480 Section 0001
//
// Assignment 1
//
// Author: 
// 
//
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//
//******************************************************************


#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/utsname.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

string getFileData(string); //Get file Data

vector<string> splitPath(string, string); 

int main(int argc, char* argv[])

{

string line;

ifstream inFile;

struct utsname sysinfo; //get file information 

uname(&sysinfo);

string homePath = getenv("HOME"); // Path for directory

string pPath = homePath + "/bin:" + getenv("PATH");

vector<string> paths = splitPath(pPath, ":");

string procfile = "/proc/sys/kernel";


//************PART A ******************


string version = getFileData(procfile + "/version"); 

string unameVersion = sysinfo.version;

cout << "A;" << endl << "/n";


cout << "1. ostype" << setw(21) << getFileData(procfile + "/ostype") << setw(24) << sysinfo.sysname << endl;

cout << "2. hostname" << setw(20) << getFileData(procfile + "/hostname") << setw(24) << sysinfo.nodename << endl;

cout << "3. osrelease" << setw(26) << getFileData(procfile + "/osrelease") << setw(24) << sysinfo.release <<endl;

cout << "4. version" << setw(37) << version.substr(0,version.find_first_of("+")) << setw(24) << unameVersion.substr(0,unameVersion.find("+"))<< endl;

cout << setw(42) << version.substr(version.find_first_of("+")) << setw(24) << unameVersion.substr(unameVersion.find("+")) <<endl;


//******************* PART B/C/D*************************


cout << "\n 1." << endl;


cout << pPath << endl;

cout << pPath.size() - 1 << endl;

cout << "2. "; std::cout.width(30); cout << std::right << "3. " <<

endl << endl;

unsigned totalBytes = -1;

for (unsigned i = 0; i < paths.size(); i++){

totalBytes += paths.at(i).size();

cout << paths.at(i); std::cout.width(30 - paths.at(i).size()); 

cout<< std::right << paths.at(i).size() << " bytes" << endl;

}

cout << "\nTotal:"; std::cout.width(30 - 6); cout << std::right << totalBytes << " bytes\t" << paths.size() << " entries" << endl << endl;

inFile.close();



pid_t w;

pid_t middle = fork();

pid_t child = fork();

if (middle < 0)

{
perror("fork failed"); //fork failed error

exit(-1);

}

if (child < 0)

{

perror ("fork failed");

exit(-1);

}


//if child and middle are both greater than 0, retrieve, parent info

if (child > 0 && middle > 0)

{

cout << "Parent pid: " << getpid() << endl;

 cout << "Parent ppid " << getppid() << endl;

cout << "Parent children: " << middle << " and " << child << endl <<endl;

std::ostringstream oss;

oss << "/bin/ps -f --ppid " << getppid() << "," << getpid() << ","<< middle << "," << child;


std::string s = oss.str();


system(s.c_str());

}


// process, current childs info

if (child == 0)

{

 cout << "Child PID : " << getpid() << endl;

 cout << "Parent ID " << getppid() << endl << endl;

sleep(3);

cout << "\nChild: " << endl << endl;

 exit(0);

 }


//The middle current process info

if (middle == 0)
{
cout << "Middle PID  " << getpid() << endl;

cout << "Parent ID " << getppid() << endl;

cout << "Children " << child << endl << endl;

sleep(3);

cout << "Middle: I am awake." << endl << endl;

exit(0);

}

else

{
while ((w = wait(0)) != -1);  // while wait information at this postion one wait(0)


cout << "Parent: All processes finished." << endl;

}

return 0;

}


string getFileData(string filename)

{

ifstream inFile;

string line;

inFile.open(filename.c_str(), std::ifstream::in);


if (inFile.fail())   //error exception
{

cout << "Error: file does not exist" << endl;

exit(1);

}


getline(inFile, line);

return line;

}


vector<string> splitPath(string path, string delim)

{

size_t index = 0, last;

string str;

vector<string> paths;

while ((index = path.find(delim)) != string::npos)

{


str = path.substr(0, index);

path.erase(0, index + delim.length());

paths.push_back(str);

if ((last = path.find(delim)) == string::npos)

{

paths.push_back(path);

}

}

return paths;

}



