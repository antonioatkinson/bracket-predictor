//
//  main.cpp
//  March Madness Bracket Predictor
//
//  Created by Antonio Thomas Atkinson on 6/3/17.
//  Copyright © 2017 Antonio Thomas Atkinson. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include "Bracket.h"
#include <vector>
#include <string>
#include <getopt.h>
using namespace std;

void readData(vector<TeamInfo> &vec,unordered_map<string,int> &teamIndex);
void calcInitialData(vector<TeamInfo> &vec,unordered_map<string, int> &teamIndex);
void determineRegion(vector<TeamInfo> &vec,char region,int i);
void runProgram(vector<TeamInfo> &vec,unordered_map<string, int> &teamIndex);
void testPrint(vector<TeamInfo> &vec,unordered_map<string,int> &teamIndex);

int main(int argc, char * argv[]) {
    ios_base::sync_with_stdio(false);
    if (getenv("INPUT")) {         freopen(getenv("INPUT"), "r", stdin);   freopen(getenv("OUTPUT"), "w", stdout);     }
    
    /*opterr = true; // Give us help with errors
    
    static struct option longOpts[] =
    {
        {"stack",no_argument,nullptr,'s'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}
    };
    
    int idx = 0; // getopt_long stores the option index here
    int c;       // The single character for the option, but stored as int
    //string dArg;
    while ((c = getopt_long(argc, argv, "sqcplo:b:e:h", longOpts, &idx))!=-1)
    {
        switch (c) {
            case 's':
                break;
            
            case 'h':
                cout << "-s --stack: Stack based routing scheme\n";
                cout << "-q --queue: Queue based routing scheme\n";
                cout << "-c --change: Letterman Allowed to change one letter to another\n";
                cout << "-p --swap: Letterman allowed to swap two adjacent characters\n";
                cout << "-l --length: Allowed to modify length of word by adding or deleting a letter\n";
                cout << "-o(W|M) --output(W|M): Specifies output\n";
                cout << "-b --begin: Beginning word\n";
                cout << "-e --end: Ending word\n";
                cout << "-h --help: Help\n";
                c1.help = true;
                exit(0);
            default:
                cerr << "Unknown option " << c << endl;
                exit(1);
        }
    }*/
    
    int numOfTeams=0;
    cin>>numOfTeams;
    vector<TeamInfo> vec;
    vec.resize(numOfTeams);
    
    unordered_map<string, int> teamIndex;
    
    string input;
    cin>>input>>input>>input>>input>>input>>input>>input>>input>>input>>input>>input>>input>>input;
    
    readData(vec, teamIndex);
    calcInitialData(vec, teamIndex); 
    runProgram(vec, teamIndex);
    //testPrint(vec, teamIndex);
    
    return 0;
}
void readData(vector<TeamInfo> &vec,unordered_map<string, int> &teamIndex){
    string region;
    for(int i=0;i<(int)vec.size();++i){
        cin>>vec[i].name>>vec[i].seed>>region;//Could make more efficient or remove completly 
        vec[i].regionName=region;
        
        determineRegion(vec, region[0],i);
        
        cin>>vec[i].RPI>>vec[i].RPIRank>>vec[i].BPI>>vec[i].BPIRank>>vec[i].kenpom>>vec[i].kenpomRank>>vec[i].sagarin>>vec[i].sagarinRank>>vec[i].initialOpponent>>vec[i].matchupNumber;
        
        teamIndex[vec[i].name] = i;
    }
}
void calcInitialData(vector<TeamInfo> &vec,unordered_map<string, int> &teamIndex){
    for(int i=0;i<(int)vec.size();++i){
        vec[i].avgRankWeight = (1*vec[i].sagarinRank+2*vec[i].kenpomRank+3*vec[i].BPIRank+4*vec[i].RPIRank)/10;
        vec[i].avgScoreWeight = (4*vec[i].sagarin+3*vec[i].kenpom+2*vec[i].BPI+1*vec[i].RPI)/10;
    }
}
void runProgram(vector<TeamInfo> &vec,unordered_map<string, int> &teamIndex){
    Bracket bracket(vec,teamIndex);
    bracket.RunFirstRound();
}
void determineRegion(vector<TeamInfo> &vec,char region,int i){
    switch (region) {
        case 'W':
            vec[i].region=West;
            break;
        case 'E':
            vec[i].region=East;
            break;
        case 'M':
            vec[i].region=Midwest;
            break;
        case 'S':
            vec[i].region=South;
            break;
        default:
            break;
    }
}
void testPrint(vector<TeamInfo> &vec,unordered_map<string,int> &teamIndex){
    for(int i=0;i<(int)vec.size();++i){
        cout<<vec[i].name<<" "<<vec[i].seed<<" "<<vec[i].region<<" "<<vec[i].RPI<<" "<<vec[i].RPIRank<<" "<<vec[i].BPI<<" "<<
        vec[i].BPIRank<<" "<<vec[i].kenpom<<" "<<vec[i].kenpomRank<<" "<<vec[i].sagarin<<" "<<vec[i].sagarinRank<<" "<<vec[i].initialOpponent<<" "<<vec[i].matchupNumber<<"\n";
    }
}
