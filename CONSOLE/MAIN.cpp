#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <direct.h>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#define _WIN32_DCOM
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <winternl.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma warning(suppress : 4996)

using namespace std;

using std::cout; using std::cin; using std::endl; 
using std::string; using std::error_code;
using std::istringstream; using std::cerr; 
using std::filesystem::directory_iterator;

string findSubstr(std::string str, int n) {        // no-ref, no-const
    str.resize(n);
    return str;
}

char keypress() {
    system("/bin/stty raw");
    char c;
    system("/bin/stty -echo");
    c = getc(stdin);
    system("/bin/stty echo");
    system("/bin/stty cooked");
    return c;
}

void editfile(string filename) {
    std::cout << "\033[2J\033[1;1H";
    ofstream file(filename);
    string text = "";
    bool saved = true;
    string save;
    do {
        std::cout << "\033[2J\033[1;1H"; //clear

        if (saved) {
            save = "  |  File is saved";
        }
        else {
            save = "  |  File has unsaved changes";
        }
        std::cout << filename << "  |  Press ~ to save file and ` to exit" << save << "\n____________________________________________________________________________\n" << text; //display text and header

        system("/bin/stty -raw");
        system("/bin/stty raw"); //change input
        char key = keypress(); //take input
        if (key == 127) { //backspace
            text = text.substr(0, text.length() - 1);
            saved = false;
        }
        else if (key == 126) { //~ to save
            ofstream file(filename);
            file << text;
            file.close();
            saved = true;
        }
        else if (key == 13) {
            text += "\n"; //for newlines
            saved = false;
        }
        else if (key == 96) {
            std::cout << "\033[2J\033[1;1H";
            break;
        }
        else { //add char
            text += key;
            saved = false;
        }
    } while (true);
}

void readfile(string filename) {
    std::cout << "\033[2J\033[1;1H"; //clear
    ifstream file(filename); //open file to read
    string text;
    std::cout << filename << "  |  Read only mode  |  Press enter to exit \n___________________________________________________\n"; //header
    while (getline(file, text)) {
        cout << text << "\n"; //display
    }
    std::cin.ignore();
    std::cin.ignore(); //wait for keypress
    std::cout << "\033[2J\033[1;1H"; // clear
}
int main(int argc, char** argv) {
    string filename;
    string text;
    string entry;
    string middlethingy = ":/";
    system("cls");
    string choice;
    
    cout << "What command would you like to perform?" << endl;
    /* COMMAND INDEX
    *1 afile
    *2 cd
    *3 cfile
    *4 chdir
    *5 clear
    *6 cpyfile
    *7 datafile
    *8 dfile
    *9 efile
    *10 help
    *11 ls
    *12 mkdir
    *13 quit
    *14 rfile
    */
    while (true)
    {
        cout << entry + " " + "INPUT: -> ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "help") {
            cout << "[START OF HELP INDEX]\n";
            cout << "help - to bring up this\n";
            cout << "afile - add to file\n";
            cout << "cfile - create files\n";
            cout << "chdir - to change directories\n";
            cout << "clear - clears console\n";
            cout << "cpyfile - copy file\n";
            cout << "datafile - shows file in bytes\n";
            cout << "dfile - delete file\n";
            cout << "efile - empty file\n";
            cout << "ls - views directories\n";
            cout << "mkdir - creates directories\n";
            cout << "quit - ends program (this one)\n";
            cout << "rfile - read from file\n";
            cout << "ver - shows the version of this (and the os you are using\n";
            cout << "[END ON HELP INDEX]\n";
        }
        else if (choice == "afile") {
            system("cls");
            text = "";
            cout << endl << "Enter name of file: ";
            cin >> filename;
            cout << endl << "Enter text to write to file: (Enter END to complete)" << endl;
            ofstream myfile;
            myfile.open(entry + (filename).c_str(), ios::app);
            string line;
            cin.ignore();	 // (Ignore the Buffer(Temperory contents)	
            while (getline(cin, line))
            {
                if (line.size() >= 3)
                {
                    if (line.substr(line.size() - 3) == "END") //Specifying that whenever END is typed stop reading data eof//
                    {
                        text += line.substr(0, line.size() - 3);// o is position of 1st chracter ,line.size is the total length, t is size of END//
                        break;
                    }
                    else {
                        text += line + "\n";
                    }
                }
                else {
                    text += line + "\n";
                }
            }
            myfile << text;
            myfile.close();
            cout << "File Updated Successfully" << endl << endl;
        }
        else if (choice == "cfile") {
            system("cls");
            cout << endl << "Enter name of file: ";
            cin.ignore();
            getline(cin, filename);
            ofstream myfile(entry + (filename).c_str());//.c_str() is used when you want to pass the contents of string to function//
            myfile.close();
            cout << "File Created Successfully" << endl << endl;
        }
        else if (choice == "chdir") {
            if (choice.find(middlethingy) != string::npos) {
                cout << "Successfully changed to " << entry << endl;
            }
            else {
                cout << "Enter FULL PATH to DIR : ";
                cin >> entry;
                cout << "\n";
                cout << "Successfully changed to " << entry << endl;
            }
            
            
            _chdir(entry.c_str());
        }
        else if (choice == "clear") {
            system("cls");
            cout << "What command would you like to perform?" << endl;
        }
        else if (choice == "cpyfile") {
            system("cls");
            text = "";
            cout << endl << "Enter name of file to copy from: ";
            cin.ignore();
            getline(cin, filename);
            fstream myfile(entry + (filename).c_str());
            string line;
            while (getline(myfile, line)) {
                text += line + "\n";
            }
            myfile.close();
            cout << endl << "Enter name of file to copy to: ";
            string second;
            getline(cin, second);
            ofstream myfile2;
            myfile2.open(entry + (second).c_str(), ios::app);
            myfile2 << text;
            myfile2.close();
            cout << "File Copied Successfully" << endl << endl;
        }
        else if (choice == "datafile") {
            string path;
            error_code ec{};

            cout << "Enter path to file e.g 'C:/folder/to/file.txt' or 'file.txt' -> ";
            cin >> path;

            auto size = std::filesystem::file_size(path, ec);
            if (ec == error_code{})
                cout << "size of file '" << path << "' = " << size << " bytes" << endl;
            else
                cout << "Error accessing file '" << path
                << "' message: " << ec.message() << endl;
            }
        else if (choice == "deldir") {
            string folder;
            cout << "Name of directory you want to delete? : ";
            cin >> folder;
            string ayyo = entry + folder;
            _rmdir(ayyo.c_str());
        }
        else if (choice == "dfile") 
        {
            system("cls");
            cout << endl << "Enter name of file: ";
            cin >> filename;
            if (remove((entry + filename).c_str()) == 0)
            {
                cout << "File Deleted Successfully" << endl << endl;
            }
            else
            {
                cout << "File Not Found" << endl << endl;
            }
        }
        else if (choice == "efile") 
        {
            system("cls");
            cout << endl << "Enter name of file: ";
            cin >> filename;
            ofstream myfile;
            myfile.open(entry + (filename).c_str());
            myfile << "";
            myfile.close();
            cout << "File Emptied Successfully" << endl << endl;
        }
        else if (choice == "ls") {
            //cout << "Directory you want to see? e.g D:/, D:/directory\n(also dont mistype or you have to restart console :/)\n-> ";
            //cin.ignore() >> path;
            for (const auto& file : directory_iterator(entry))
                cout << file.path() << endl;
                
        }
        else if (choice == "mkdir")
        {
            bool isFull = false;
            string uinput;
            cout << "Do you want to make a DIR in fullpath or just here?\n (btw you can do /folder/folder/ if you choose just here)\n also you can only respond in 'fullpath' or 'here'";
            cin >> uinput;
            std::for_each(uinput.begin(), uinput.end(), [](char& c) {c = ::tolower(c); });
            if (uinput == "fullpath") {
                isFull = true;
            }
            else if (uinput == "fullpath") {
                isFull = false;
            }
            if (isFull == false) {
                string folder;
                cout << "what do you want your folder to be named / be?: -> ";
                cin >> folder;
                string fullmkdir = entry + "/" + folder;
                if (_mkdir(fullmkdir.c_str()) == -1)
                    cerr << " Error : " << strerror(errno) << endl;

                else
                    cout << "Folder Created\n";
            }
            else if (isFull == true) {
                string fullpath;
                cout << "what do you want your folder to be named / be?: -> ";
                cin >> fullpath;
                if (_mkdir(fullpath.c_str()) == -1)
                    cerr << " Error : " << strerror(errno) << endl;

                else
                    cout << "Folder Created!\n";
                }
        }  
        else if (choice == "quit")
        {
            break;
        }
        else if (choice == "rfile") 
        {
            system("cls");
            text = "";
            cout << endl << "Enter name of file: ";
            cin >> filename;
            fstream myfile;
            myfile.open(entry + (filename).c_str());
            while (getline(myfile, text)) {
                cout << text << "\n";
            }
            myfile.close();
            char now;
            cout << endl << "End of File. Press any key to end : ";
            cin >> now;
            cout << "File Created Successfully" << endl << endl;
        }
        else if (choice == "ver") 
        {
            
            cout << "CONSOLE : DEV-VER\n BY MANIATICDEVS©\n";

            OSVERSIONINFOEX info;
            ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
            info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
            GetVersionEx((LPOSVERSIONINFO)&info);//info requires typecasting

            printf("Windows version: %u.%u\n", info.dwMajorVersion, info.dwMinorVersion);

            
        }
        
        else {
            cout << "COMMAND NOT FOUND\n";
        }
    }
}
