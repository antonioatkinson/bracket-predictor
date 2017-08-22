//
//  Bracket.h
//  March Madness Bracket Predictor
//
//  Created by Antonio Thomas Atkinson on 6/4/17.
//  Copyright © 2017 Antonio Thomas Atkinson. All rights reserved.
//

#ifndef Bracket_h
#define Bracket_h
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

enum Regions{
    East,
    West,
    Midwest,
    South
};
struct TeamInfo{
    string name;
    int seed;
    //string region;//Make enum of regions
    string regionName; //Might not be needed
    Regions region;
    double RPI;
    int RPIRank;
    double BPI;
    int BPIRank;
    double kenpom;
    double kenpomRank;
    double sagarin;
    int sagarinRank;
    string initialOpponent;
    int matchupNumber;//Where matchup is located in bracket 
    //Cacluations
    double avgRankWeight;
    double avgScoreWeight;
    double medianRankWeight;
};

class Bracket{
public:
    Bracket(vector<TeamInfo>&vec_in,unordered_map<string,int> &teamIndex_in):vec(vec_in),teamIndex(teamIndex_in){
        vecRoundof64.resize(32);
        /*for(int i=0;i<32;++i){
            vecRoundof64[i].resize(2);
        }*/
        vecRoundof32.resize(16);
        vecSweetSixteen.resize(16);
        vecEliteEight.resize(8);
        vecFinalFour.resize(4);
        vecNationalChampionship.resize(2);
    }
    void RunFirstRound(){
        for(int i=0;i<(int)vecRoundof64.size()*2;++i){
            vecRoundof64[vec[i].matchupNumber].push_back(&vec[i]);
        }
        printRound(vecRoundof64);
        if(vecRoundof64[8][0]->avgRankWeight<vecRoundof64[8][1]->avgRankWeight){
            cout<<"Winner: "<<vecRoundof64[8][0]->name<<endl;
            cout<<"Winner: "<<vecRoundof64[8][0]->avgRankWeight<<endl;
            cout<<"Winner: "<<vecRoundof64[8][0]->avgScoreWeight<<endl;
            cout<<endl;
            cout<<"Winner: "<<vecRoundof64[8][1]->name<<endl;
            cout<<"Winner: "<<vecRoundof64[8][1]->avgRankWeight<<endl;
            cout<<"Winner: "<<vecRoundof64[8][1]->avgScoreWeight<<endl;
            
            
            cout<<"new round num: "<<vecRoundof64[8][0]->matchupNumber/2<<endl;
            vec[teamIndex[vecRoundof64[8][0]->name]].matchupNumber=vecRoundof64[8][0]->matchupNumber/2;
        }
        else
            cout<<"Winner: "<<vecRoundof64[0][1]->name;
        
        
        cout<<vecRoundof64[0][0]->name<<endl;
        cout<<vecRoundof64[0][1]->name<<endl;
        cout<<vecRoundof64[8][0]->name<<endl;
        cout<<vecRoundof64[8][1]->name<<endl;
        cout<<vecRoundof64[16][0]->name<<endl;
        cout<<vecRoundof64[16][1]->name<<endl;
        cout<<vecRoundof64[24][0]->name<<endl;
        cout<<vecRoundof64[24][1]->name<<endl;
    }
    void RunSecondRound();
    void RunSweetSixteen();
    void RunEliteEight();
    void RunFinalFour();
    void RunNationalChampionship();
private:
    vector<TeamInfo>vec;
    //For later rounds
    vector<vector<TeamInfo*>> vecRoundof64;
    vector<vector<TeamInfo*>> vecRoundof32;
    vector<TeamInfo> vecSweetSixteen;
    vector<TeamInfo> vecEliteEight;
    vector<TeamInfo> vecFinalFour;
    vector<TeamInfo> vecNationalChampionship;
    TeamInfo nationChampion;
    unordered_map<string,int> teamIndex;
    
    //Helper functions
    void calcRound(vector<TeamInfo> &vec){
        for(int i=0;i<(int)vec.size();++i){
            
        }
    }
    void printRound(vector<vector<TeamInfo*>>&vec1){
        for(int i=0;i<(int)vec1.size()*2;++i){
            if(i%8==0&&i!=0){
                cout<<endl<<endl;
            }
            
            if(i==0||i==8||i==16||i==24){
                cout<<vec1[i][0]->name<<endl<<vec1[i][1]->name<<endl<<endl;
            }
            else{
                cout<<"------"<<endl<<"----"<<endl<<endl;
            }
        }
    }
    
};


#endif /* Bracket_h */
