#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <regex>
#include "../include/toolbox.h"
#include <stdlib.h>

using namespace std;

/**
* Change l'extension du nom de fichier donné pour .hist
*
* @param fileName A filename containing a '.'
*
* @return The modified extension
*/
string changeExtension(string fileName)
{
	int lastIndex = fileName.find_last_of(".");
	string newFile = fileName.substr(0, lastIndex) + ".hist";
	return newFile;
}

/**
* List all files (not directories) in a directory
*
* @param directory The name of a directory
*
* @return The list of files in directory
*/
vector<string> GetFilesInDirectory(const string &directory)
{
    DIR *dir;
    struct dirent *ent;
    struct stat st;
    vector<string> out;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL)
    {
        const string file_name = ent->d_name;
        const string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    }
    closedir(dir);
}

/**
* Filter the strings of a list which match a regex
*
* @param liste A vector of strings
*
* @param regexpr A regular expression
*
* @return The list of strings for liste which match regexpr
*/
vector<string> filtre(const vector<string>& liste, const string& regexpr)
{
    regex e(regexpr);
    vector<string> out;

    for(string s : liste)
        if(regex_match(s, e))
            out.push_back(s);

    return out;
}

/**
* Compute the set-theoretic difference of two vectors of strings
*
* @param liste A vector of strings
*
* @param done A vector of strings
*
* @return The différent liste \ done
*/
vector<string> difference(const vector<string>& liste, const vector<string>& done)
{
    vector<string> out;

    for(string s : liste)
    {
        bool test = false;
        for(string t : done)
            if(t == s)
            {
                test = true;
                break;
            }
        if(!test)
            out.push_back(s);
    }

    return out;
}

/**
* Read each line of a file and return a vector of strings
*
* @param filename A string containt the filename
*
* @return A vector of strings where each string is a line of the file
*/
vector<string> readFile(string filename)
{
    ifstream infile;
    infile.open(filename);
    string line;
    vector<string> out;

    while (getline(infile, line))
        out.push_back(line);
    infile.close();

    return out;
}

/**
* Extract the image class from a filename
*
* @param filename A string containt the filename of the kind a/unix/path/class-number.pgm
*
* @return A string containing class
*/
string extractClass(string filename)
{
	size_t begin = filename.find_last_of("/");
	size_t end = filename.find_last_of("-");
	size_t length = end - begin-1;
	return filename.substr(begin+1, length);
}

/**
* Extract the path from a complete filename
*
* @param filename A string containt the filename of the kind a/unix/path/file
*
* @return A string containing a/unix/path
*/
string getPath(const string& str)
{
  unsigned found = str.find_last_of("/");
  return str.substr(0,found);
}

/**
* Extract the filename from a complete filename
*
* @param filename A string containt the filename of the kind a/unix/path/file
*
* @return A string containing file
*/
string getFileName(const string& str)
{
  unsigned found = str.find_last_of("/");
  return str.substr(found+1);
}

void modifyImage(string inputFile, string outputFile)
{
	if (!system(NULL))
		exit(EXIT_FAILURE);
	else
	{
		random_device rd;
		mt19937 generator(rd());
		uniform_real_distribution<> distrib(0,1);
		double randomNoise = distrib(generator) * 0.5;
		double randomAngle = distrib(generator) * 3.1415;
		double randomScale = distrib(generator) * 3;
		cout << "noise : " << randomNoise << ", angle : " << randomAngle << ", scale : " << randomScale << endl;
		int i;
		i = system(("./imgRotate -i "+inputFile+" -o tmp.pgm -a "+to_string(randomAngle)+" 2> /dev/null").c_str());
		i = system(("./imgScale -i tmp.pgm -o tmp2.pgm -s "+to_string(randomScale)+" 2> /dev/null").c_str());
		i = system(("./imgAddNoise -i tmp2.pgm -o "+outputFile+" -n "+to_string(randomNoise)+" 2> /dev/null").c_str());
		i = system("rm tmp.pgm tmp2.pgm");
	}
}
