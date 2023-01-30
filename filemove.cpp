#include<bits/stdc++.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
using namespace std;
namespace fs = filesystem;
fstream file;
void createRep(string path){
        file.open(path+"\\Report.txt",ios::out);
        if(!file)
        {
             cout<<"Error in creating file!!!"<<endl;
        }
        cout<<"Report File Created"<<endl;
}
void createFolder(string dest){
    fs::create_directories(dest);
}
void moveFilefunc(string dest,string path){
    createFolder(dest);
    char cmd[100];
    strcpy(cmd,"move ");
    strcat(cmd,path.c_str());
    strcat(cmd," ");
    strcat(cmd,dest.c_str());
    system(cmd);     
}

int main()
{
	string path,dest="";
    cin>>path;
    string file_path=path;
	struct stat sb;
    
    createRep(path);
    vector<string> Documents{".txt",".pdf",".xlsx",".xml"};
    vector<string> Music{".mp3",".bit"};
    vector<string> Video{".mp4",".mkv"};
	for (const auto& entry : fs::directory_iterator(path)) {
        filesystem::path outfilename = entry.path();
		string outfilename_str = outfilename.string();
		const char* path = outfilename_str.c_str();
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)){
            filesystem::path p(path);
            if(find(Documents.begin(),Documents.end(),p.extension())!=Documents.end()){
                file<<p.filename()<<" "<<p.extension()<<" "<<"Document"<<endl;
                dest=file_path+"\\Document";
                if(p.stem()=="Report"){
                    continue;
                }else{
                    moveFilefunc(dest,path); 
                }
                   
            }
            else if(find(Music.begin(),Music.end(),p.extension())!=Music.end()){
                file<<p.filename()<<" "<<p.extension()<<" "<<"Music"<<endl;
                dest=file_path+"\\Music";
                moveFilefunc(dest,path);
            }
            else if(find(Video.begin(),Video.end(),p.extension())!=Video.end()){
                file<<p.filename()<<" "<<p.extension()<<" "<<"Video"<<endl;
                dest=file_path+"\\Video";
                moveFilefunc(dest,path);
            }
            else{
                cout<<"This File Extension should not be moved."<<endl;
            }
        }
	}
}