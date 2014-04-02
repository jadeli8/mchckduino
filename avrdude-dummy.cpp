#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
using namespace std;


int main(int argc,char* argv[])
{
    std::string hexPrefix("-Uflash:w:");
    std::string platformPrefix("-c");
    std::string configPrefix("-C");
    std::string argument;
    std::string hexValue; 
    std::string platformValue; 
    std::string original = argv[0];
    size_t found;
    found=original.find_last_of("/\\");
    std::string command = "\""+original.substr(0,found+1) + "avrdude" + "\"";



    // args start at 1 (0 is program name)
    for(int i = 1; i < argc; ++i) // index every arg in argv[]
    {
         argument = argv[i];
        //if(std::string(argv[i]) == "-U") // test each arg against our switch

        if(argument.substr(0, hexPrefix.size()) == hexPrefix) { // test each arg against our switch
        
            // found hex file ... 
            hexValue = argument.substr(hexPrefix.size());
            hexValue = hexValue.substr(0, hexValue.size()-2);
            //cout << hexValue << endl;
        }
        if(argument.substr(0, platformPrefix.size()) == platformPrefix) { 
            // found platform ... 
            platformValue = argument.substr(platformPrefix.size(),9);
            //cout << platformValue << endl;
        }


        if(argument.substr(0, configPrefix.size()) == configPrefix) { 
            // found platform ... 

            command += " -C\""+argument.substr(configPrefix.size())+"\"";
            //cout << platformValue << endl;
        }
        else{
            command += " "+argument;
        }

    }


    if (platformValue == "swd"){
        //run digispark
        cout << "Running McHck Uploader..." << endl;

        //replace the rest of this with the uploader
        std::string uploader = "\""+original.substr(0,found+1)+"mchck_upload\" "+hexValue; 

        //cout << uploader << endl;
        cout << "Plug in device now... (will timeout in 60 seconds)" << endl;
        system(uploader.c_str());
    }
    else{
        cout << "Running AVRDUDE..." << endl;
        

        #ifdef _WIN32
        command = "\""+command+"\"";
        #endif
        //cout << command << endl;
        system(command.c_str());
    }
}
