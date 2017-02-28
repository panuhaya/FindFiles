//============================================================================
// Name        : FindFiles.cpp
// Author      : panuhaya
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/range/adaptor/reversed.hpp>

using std::cout;
using namespace boost::filesystem;

struct fileStruct {
	std::set<std::string> namefile;
	std::set<std::string> dirs;
};

int main(int argc, char* argv[]) {

	std::set<std::string> mysetFile;
	std::set<std::string> mysetDir;
	std::set<std::string> endSet;
	ofstream myfile;
	std::string ruta=current_path().string();
	char *cadena1;

	cadena1=argv[1];
	//------taking current directory
	  if (argc < 2)
	  {
			cadena1 = new char [ruta.length()+1];
			std::strcpy (cadena1, ruta.c_str());
	  }

	  path p(cadena1);
	  try
	  {
	    if (exists(p))
	    {
	    	if (is_directory(p))
	      {
	    		std::vector<fileStruct> filesv;
	    		recursive_directory_iterator dirA(p), end;
	    		while(dirA != end){
	        		recursive_directory_iterator dirB(p), end;
	        		while(dirB != end){
	        		if(is_regular_file(dirA->path()) && is_regular_file(dirB->path())){
	        			if(dirA->path().branch_path()!=dirB->path().branch_path()){
	        				if(dirA->path().filename()==dirB->path().filename()){
	        					if(file_size(dirA->path())==file_size(dirB->path())){
	        						// -------file repeated, and its directory
	        						mysetFile.insert(dirA->path().filename().string());
	        						mysetDir.insert(dirB->path().branch_path().string());
	        					}
	        				}
	        			}
	        		}
	        		dirB++;
	        	}
	        		dirA++;
	        }
	    		for(auto&& ia: mysetFile){
	    			fileStruct myStruct;
	    			myStruct.namefile.insert(ia);
	    			for(auto&& ie: mysetDir){
	    				if(exists(ie +"/"+ ia)){
	    					myStruct.dirs.insert(ie);
	    				}
	    			}
	    			filesv.push_back(myStruct);
	    		}
	    		cout<<filesv.size()<<std::endl;

	    		for(int tr=0;tr<filesv.size();tr++){
	    		for(auto&& tt:filesv){
	    			if(filesv[tr].dirs==tt.dirs){
	    				for(auto&& yy: tt.namefile){
	    					filesv[tr].namefile.insert(yy);
	    				}
	    			}
	    		}
	    	}
	    		/*fileStruct minstruct;
				for(auto&& mjk:filesv){
					if(minstruct.dirs==mjk.dirs)
						for(auto&& yy: minstruct.namefile){
							mjk.namefile.insert(yy);
						}
					else{
						minstruct=mjk;
					}
				}*/

	    		myfile.open("filesRepited.txt");
	    		fileStruct minstructu;
	    		for(auto&& mnm:filesv){
	    			if(minstructu.dirs!=mnm.dirs)
	    				if(minstructu.namefile!=mnm.namefile){
			    		minstructu=mnm;
		    		for(auto&& ttr: minstructu.dirs)
		    			myfile<<"Directory " <<ttr<<std::endl;
		    		for(auto&& trr: minstructu.namefile)
		    			myfile<<"	File " <<trr<<std::endl;
	    			}
	    		}


	    	myfile.close();
	      }
	      else
	        cout << p << " exists, but is not a regular file or directory\n";
	    }
	    else
	      cout << p << " does not exist\n";
	  }

	  catch (const filesystem_error& ex)
	  {
	    cout << ex.what() << '\n';
	  }
	  return 0;
}
