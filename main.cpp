/*
CS 251 - Project 1 Gerrymandering
CS 251-Fall 2020 
instructions copyrightes to Professor-Dr Shanon Reckinger 
Author: Huma Tejaswi Akkem
*/
#include "ourvector.h"
#include<fstream>
#include<string>
#include <sstream>
#include<iostream>
#include <cmath>
using namespace std;
// creating a class for the whole project and Created two main vars to track
// the states names and distNo till end of the Program
class Program {
 public:
        string state;
        int distNo;
};
// to convert the string to lower case letters for it to be easier to skim
// through the given text file
string toLowerWord(string j) {
    for (char & i : j) {      // loop to convert all letters into lower case
        i = tolower(i);
    }
    return j;     // returning the output of the function
}
// These Function is used to extrcat the inputs (names) line by line from
// the file
string getfile(string &input) {
    size_t decom = input.find(",");
    string nameFile = input.substr(0, decom);
    input = input.substr(decom + 1, input.size() - nameFile.size() - 1);
    return nameFile;
}
// These function loads the data of rupblic votes,StateName,distNumber......
// Democrats votes and eligble Vote numbers from the file and stores int....
// main.cpp.................................................................
string readAndFind(string &input) {
    Program program;
    string distNom;
    while (!input.empty()) {
        size_t decom = input.find(",");
        string TheNum = input.substr(0, decom);
        input = input.substr(decom + 1, input.size() - TheNum.size() - 1);
        decom = input.find(",");
        string dVotes;
    if (decom != string::npos) {
        dVotes = input.substr(0, decom);
        input = input.substr(decom + 1, input.size() - dVotes.size() - 1);
    }   else if (int(decom) == -1)  {
        dVotes = input;
        input = "";
    }
        decom = input.find(",");
        string rVotes;
    if (decom == string::npos) {
        rVotes = input;
        input = "";
    }  else  {
        rVotes = input.substr(0, decom);
        input = input.substr(decom + 1, input.size() - rVotes.size() - 1);
        }
        distNom = TheNum;
    }
    if (distNom == "AL") {
        distNom = "1";
    }
    return distNom;
}
// These Function is used the read the districts.txt file and stores the...
// data if the file is wrong then it gives invalid output( errors statement)
bool readAndStoreFile(string fileName, ourvector<int> &distNumb,
ourvector<string> &stateName, 
int &loadCounter, ourvector<string> &lineData) {
    cout << endl;
    ifstream infile(fileName);
    string input;
    getline(infile, input, '\n');
    if (!infile.is_open())  {
        cout << "Invalid first file, try again."<< endl;
    }   else if (infile.is_open())  {
        cout << "Reading: " << fileName << endl;
    while (!infile.eof()) {
        lineData.push_back(input);
        string StateName = getfile(input);
        Program program;
        stateName.push_back(StateName);
        program.state = StateName;
        cout << "..." << StateName << "...";
        string distNoum = readAndFind(input);
        cout << distNoum << " districts total" << endl;
        distNumb.push_back(stoi(distNoum));
        getline(infile, input, '\n');
        }
        return true;
    }
    return false;;
}
// These Extracts the votes in data-----------------------------------------
string getEligibleVoters(string &input) {
    string num;
    size_t pos = input.find(",");
    num = input.substr(0, pos);
    return num;
}
// These function is used to read and stores the eligible_voters.txt file
// and if the file is incoorect it prints the error statements
bool readAndPrintEligibleVoters(string fileName2, ourvector<string>
&stateName, int &loadCounter,
ourvector<string> &eligibleLine,
    ourvector<int> &eligNumber) {
    cout << endl;
    ifstream infile(fileName2);
    string input;
// getline(infile,input,'\n');
    if (!infile.is_open())  {
      cout << "Invalid second file, try again."<< endl;
    }  else if (infile.is_open())  {
      cout << "Reading: "<< fileName2 << endl;
    while (getline(infile, input, '\n'))  {
            string nameOfState = getfile(input);
            eligibleLine.push_back(nameOfState);
            int x = stoi(getEligibleVoters(input));
            eligNumber.push_back(x);
    for (int i = 0; i < stateName.size(); ++i)  {
    if (nameOfState == stateName[i])  {
            cout << "..." << nameOfState << "...";
            cout << x << " eligible voters" << endl;
              }
            }
       }
        return true;
    }
    return false;
}
// These function is used to search the state from the file, we input the
// statename and it search state stats and prints out 
string searchState(string &stateToFind, int &searchCounter,
ourvector<string> &stateName, ourvector<int> &distNumb, int &stateNumm) {
    int i = 0;
    for (i = 0; i < stateName.size(); i++) {
        string str = stateToFind;
        string string1 = "";
        string str1 = stateName[i];
        string string2 = "";
    for (int i = 0; i < str.length(); ++i) {
        string1 = string1 + toLowerWord(str);
        } for (int i = 0; i < str1.length(); ++i) {
            string2 = string2 + toLowerWord(str1);
        } 
        if (string2 == string1) {
        searchCounter++;
        string s = stateName[i];
        stateNumm = i;
        return s;
        break;
  }
}
  return "";
}
// These function is determine the state is gerrymandered or not for exampl
// if userinput is illinois, systems gives its not a gerrymandered and if 
// the
// states is gerrymandered " it says YES"
void isItGerrymandered(ourvector<string> &lineData,
int stateNumm, ourvector<string> &eligibleLine, 
ourvector<string> &tokens, ourvector<int> &eligNumber) {
    string str = lineData[stateNumm];
    istringstream ss(str);
    string token;
while (getline(ss, token, ',')) {
       tokens.push_back(token);
    }
    int totalDemVotes = 0;
    int eligible_voters = 0;
    int totalRepVotes = 0;
    int wastedDem = 0;
    int wastedRep = 0;
    int total = 0;
    int overHalf = 0;
    int wasteddemo = 0;
    int wastedrepo = 0;
    for (int i = 0; i < eligNumber.size(); i++) {
    if (eligibleLine[i] == tokens[0]) {
         eligible_voters = eligNumber[i];
        }
    } for (int i = 1; i < tokens.size(); i+=3) {
        totalDemVotes += stoi(tokens[i+1]);
        totalRepVotes += stoi(tokens[i+2]);
        total = stoi(tokens[i+1]) + stoi(tokens[i+2]);
        overHalf = int(total/2) + 1;
    if (overHalf < stoi(tokens[i+1])) {
        wastedRep = stoi(tokens[i+1]) - overHalf;
        wastedDem = stoi(tokens[i+2]);
        wasteddemo += wastedDem;
        wastedrepo += wastedRep;
    } else if (overHalf < stoi(tokens[i+2])) {
        wastedDem = stoi(tokens[i+2]) - overHalf;
        wastedRep = stoi(tokens[i+1]);
        wasteddemo += wastedDem;
        wastedrepo += wastedRep; }
    }
// determines the Efficiency Gap of the states         
double EG;
    if (wastedrepo > wasteddemo) {
        EG = wastedrepo - wasteddemo;
    } else {
        EG = wasteddemo - wastedrepo;
    }
        EG = EG/(totalDemVotes+totalRepVotes);
        EG = EG * 100;
    if (EG >= 7 && ((tokens.size()-1)/3) >= 3) {
        cout <<"Gerrymandered: Yes"<< endl;
    if (wasteddemo > wastedrepo) {
        cout << "Gerrymandered against: Republicans"<< endl;
    } else if (wasteddemo < wastedrepo) {
        cout << "Gerrymandered against: Democrats"<< endl;
    }
        cout <<"Efficiency Factor: "<< EG <<"%"<< endl;
        cout <<"Wasted Democratic votes: "<< wastedrepo << endl;
        cout <<"Wasted Republican votes: "<< wasteddemo << endl;
        cout <<"Eligible voters: "<< eligible_voters<< endl;
    } else {
        cout <<"Gerrymandered: No"<< endl;
        cout <<"Wasted Democratic votes: "<< wastedrepo << endl;
        cout <<"Wasted Republican votes: "<< wasteddemo << endl;
        cout <<"Eligible voters: "<< eligible_voters << endl;
    }
    tokens.clear();
}
// These function is used for plotting the domcractic votes and republic
// votes, tokens2 is a substring in my project i created two tokens.
void plotting(ourvector<string> &lineData, int stateNumm, 
ourvector<string> &v, ourvector<string> &tokens2) {
    string str = lineData[stateNumm];
    istringstream ss(str);
    string token;
  while (getline(ss, token, ','))  {
         tokens2.push_back(token);
       }
    for (int i = 1; i < tokens2.size(); i+=3) {
        double z = stoi(tokens2[i+1]);
        double x = stoi(tokens2[i+2]);
        double demsToPrint = 0;
        demsToPrint = (z/(x+z));
        demsToPrint = demsToPrint * 100;
        int demsToPri = int(demsToPrint);
        int repsToPrint = 0;
        repsToPrint = 100 - demsToPri;
        if (tokens2[i] == "AL") {
            tokens2[i] = "1";
        }
        cout <<"District: " << tokens2[i] << endl;

        if (repsToPrint > 0 && demsToPrint > 0) {
            for (int j = 0; j < demsToPri; j++) {
                cout << "D";
            } for (int s = 0; s < repsToPrint; s++) {
                cout << "R";
            }
            cout << endl;
        }  else if (demsToPri == 100) {
            for (int i = 0; i < 100; i++) {
                cout << "D";
            }
            cout << endl;
        } else if (repsToPrint == 100) {
        for (int i = 0; i < 100; i++) {
              cout << "R";
            } cout << endl;
        }
    }
    cout << endl;
    tokens2.clear();
}
// creativeComponent, what it does: its deterination scale a ascii codes when it demo 
// votes are more then its goes up.
// to use the creative compont load the data->enter search state->enterstats
// ->enter plot->enter scale
void creativeComponent(ourvector<string> &lineData, int stateNumm, 
ourvector<string> &v, ourvector<string> &tokens22) {
    string str = lineData[stateNumm];
    istringstream ss(str);
    int totalDemVotes;
    int totalRepVotes;
    string token;
    while (getline(ss, token, ',')) {
        tokens22.push_back(token);
    }
    for (int i = 1; i < tokens22.size(); i+=3) {
        totalDemVotes += stoi(tokens22[i+1]);
        totalRepVotes += stoi(tokens22[i+2]);
    }
    if (totalDemVotes > totalRepVotes) {
        cout << "   +--------[XX]-------+\n"
         <<"    |        ||        | \n"
         <<"    |        ||        | \n"
         <<"    |        ||       /|\\\n"
         <<"   /^\\       || (Republican)\n"
         <<"(Democrat)   ||       \n"
         <<"             ||\n"
         <<"             ||\n"
         <<"            /uu\\ \n";
         cout << endl;
    }
    if (totalDemVotes < totalRepVotes) {
        cout << "    +--------[XX]-------+\n"
         <<"    |         ||        | \n"
         <<"    |         ||        | \n"
         <<"    |         ||       /|\\\n"
         <<"   /^\\        ||   (Democrat)\n"
         <<"(Republican)  ||       \n"
         <<"              ||\n"
         <<"              ||\n"
         <<"             /uu\\ \n";
         cout << endl;
    } else if(totalRepVotes == totalDemVotes) {
        cout << "  +--------[XX]-------+\n"
         <<"    |         ||        | \n"
         <<"    |         ||        | \n"
         <<"   /|\\       ||      /|\\\n"
         <<" (Republican) ||    (Democrat)\n"
         <<"              ||     \n"
         <<"              ||\n"
         <<"              ||\n"
         <<"             /uu\\ \n";
         cout << endl;
    }
}
    
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------
// Here I call the all functions from above the class, I used 8 vectors I 
// limited the useage of vector as much i can
int main() {
    Program program;
    string input;
    string TheNum;
    string stateToFind;
    ourvector<string>v;
    ourvector<int> distNumb;
    ourvector<int> republicHolder;
    ourvector<int> democratHolder;
    ourvector<int> eligNumber;
    ourvector<string>stateName;
    ourvector<string>lineData;
    ourvector<string>eligibleLine;
    ourvector<string>tokens;
    ourvector<string>tokens22;
    int stateNumm = 0;
    string command;
    string firstFile;
    string secondFile;
    string nameToSearch;
    string name1;
    string name2;
    string name3;
    string validState = "N/A";
    string dataLoaded = "No";
    int loadCounter = 0;
    int searchNum = 0;
    int searchCounter = 1;
    int plotCount = 0;
    cout <<"Welcome to the Gerrymandering App!" << endl;
    while (command != "exit") {
    if (loadCounter != 0 && searchCounter == 0) {
            cout << endl <<"State does not exist, search again." << endl;
            searchCounter++;
        }
        cout << endl;
        cout << "Data loaded? " << dataLoaded << endl;
        cout << "State: " << validState << endl;
        cout << endl;
        cout << "Enter command: ";
        cin >> command;
        cout << endl;
        cout <<"-----------------------------";
        cout << endl;
    if (command == "load") {
    if (loadCounter == 0) {
        cin >> firstFile;
        cin >> secondFile;
    if (readAndStoreFile(firstFile, distNumb, stateName, loadCounter,
lineData) && readAndPrintEligibleVoters(secondFile, stateName, loadCounter,
eligibleLine, eligNumber)) {
            dataLoaded = "Yes";
            loadCounter = 1;
            loadCounter++;} else {
            dataLoaded = "No";
         }
         } else {
         cout << endl << "Already read data in, exit and start over."
         <<endl;
            }
        }
    if (command == "search") {
    if (loadCounter <= 0) {
        cout << endl <<"No data loaded, please load data first."
        << endl;
    } else {
         getline(cin, stateToFind);
         stringstream ss(stateToFind);
         name1 = "";
         name2 = "";
         name3 = "";
         ss >> name1 >> name2 >> name3;
         if (name2.size() == 0) {
         nameToSearch = name1; } else if (name3.size() == 0) {
         nameToSearch = name1 + " " + name2; } else {
         nameToSearch = name1 + " " + name2 + " " + name3;
    }
         searchCounter = 0;
         string ValidStName = searchState(nameToSearch, searchCounter,
stateName, distNumb, stateNumm);
    if ( searchCounter > 0 ) {
         validState = ValidStName;
         searchNum++;
    } else {
         validState = validState;  }
    }
}
    if (command == "stats") {
    if (loadCounter <= 0)  {
    cout <<endl <<"No data loaded, please load data first."<< endl;
    } else if (searchNum == 0) {
        cout << endl << "No state indicated, please search for state first."<< endl;
    }  else  {
    isItGerrymandered(lineData, stateNumm, eligibleLine, tokens,
eligNumber);}}  
    if (command == "plot") {
    if (searchNum >= 1) {
        plotting(lineData, stateNumm, v, tokens);
        plotCount = plotCount + 1;
    } else if (loadCounter <= 0) {
       cout <<endl <<"No data loaded, please load data first."<< endl;
    } else if (plotCount <= 0)  {
      cout << "No state indicated, please search for state first." << endl;
            }
        }
    if (command == "scale") {
    if (searchNum >= 1) {
        creativeComponent(lineData, stateNumm, v, tokens22);
    } else if (loadCounter <= 0) {
       cout <<endl <<"No data loaded, please load data first."<< endl;
    } else if (plotCount <= 0)  {
      cout << "No state indicated, please search for state first." << endl;
            }
        }
    }
    return 0;
}
