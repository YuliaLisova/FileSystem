#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <iomanip> 
#include <io.h> 
#include <string>
using namespace std;

void RussianMessage(const char * str)
{
	char * p = new char[strlen(str) + 1];
	CharToOemA(str, p);
	cout << setw(30) << p;
	delete[] p;
}

const int MAXX_PATH = 260;  
const char * MASK = "*.txt";  
void findFiles(char path[], int & count)           
{
	_finddata_t * fd= new _finddata_t;  
											  
	char findFilePath[MAX_PATH];  
	char  findDirPath[MAX_PATH]; 
 	strcpy(findFilePath, path);   
	strcat(findFilePath, MASK);	 
	long OK = _findfirst(findFilePath,fd);   
   
	int result = OK;   
	while (result!=-1)
	{    
		if(fd->attrib & 32)       
		{
			 RussianMessage(path); RussianMessage(fd->name); cout << endl;
			 count++; 
		}
		result = _findnext(OK, fd);     
	}
	strcpy(findDirPath, path);       
	strcat(findDirPath, "*.*");
	OK = _findfirst(findDirPath, fd);
	result = OK;
	while(result != -1)
	{
		
		if(fd->attrib & _A_SUBDIR && strcmp(fd->name, ".") && strcmp(fd->name, ".."))
		{
			char newPath[MAX_PATH];  
			strcpy(newPath, path);   
			strcat(newPath, fd->name); 
			strcat(newPath, "\\");		
			findFiles(newPath, count);      
		}
		result = _findnext(OK, fd);
	}
	delete fd;  
}

int main(int argc, char **argv)
{   int count_of_files=0;
	cout << "Drives list:\n";
	int drivesBitMask = GetLogicalDrives();
	char drive = 'A';
	char root[4] = {};
	int type = 0;

	while (drivesBitMask)
	{
		if (drivesBitMask & 1) {
			cout << "Drive " << drive << ": is present. ";
			sprintf(root, "%c:\\", drive);
			type = GetDriveTypeA(root);
			switch (type)
			{
			case DRIVE_UNKNOWN:
				cout << "Drive type is unknown!";
				break;
			case DRIVE_CDROM:
				cout << "Drive is CD-ROM";
				break;
			case DRIVE_REMOTE:
				cout << "Drive is Remote disk";
				break;
			case DRIVE_REMOVABLE:
				cout << "Drive is Removable";
				break;
			case DRIVE_NO_ROOT_DIR:
				cout << "Root path to drive is invalid";
				break;
			case DRIVE_FIXED:
				cout << "Drive is fixed. HDD, for example";
				break;
			case DRIVE_RAMDISK:
				cout << "Drive is a RAM disk";
				break;
			}

			cout << endl;
			char disc[2]={drive};
			char new_disc[10];
			strcpy(new_disc, disc);
			strcat (new_disc, ":");
			strcat (new_disc, "\\");
			findFiles(new_disc, count_of_files);

		}

		drive++;
		drivesBitMask >>= 1;
	}
	cout<<"\n-------------------------\n";
	cout<<"count of "<<MASK<<" files is "<<count_of_files<<endl;
}

