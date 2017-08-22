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
        vecRoundof32.resize(16);
        resizeVecs(vecRoundof32);
        vecSweetSixteen.resize(8);
        resizeVecs(vecSweetSixteen);
        vecEliteEight.resize(4);
        resizeVecs(vecEliteEight);
        vecFinalFour.resize(2);
        resizeVecs(vecFinalFour);
        vecNationalChampionship.resize(1);
        resizeVecs(vecNationalChampionship);
    }
    void RunFirstRound(){
        for(int i=0;i<(int)vecRoundof64.size()*2;++i){
            vecRoundof64[vec[i].matchupNumber].push_back(&vec[i]);
        }
        printRound(vecRoundof64);
        
        calcRound(vecRoundof64, vecRoundof32);
    }
    void RunSecondRound(){
        cout<<"Second Round\n";
        printRound(vecRoundof32);
        
        calcRound(vecRoundof32, vecSweetSixteen);
    }
    void RunSweetSixteen(){
        cout<<"Sweet Sixteen\n";
        printRound(vecSweetSixteen);
        calcRound(vecSweetSixteen, vecEliteEight);
    }
    void RunEliteEight(){
        cout<<"Elite Eight\n";
        printRound(vecEliteEight);
        calcRound(vecEliteEight, vecFinalFour);
    }
    void RunFinalFour(){
        cout<<"Final Four\n";
        printRound(vecFinalFour);
        calcRound(vecFinalFour, vecNationalChampionship);
    }
    void RunNationalChampionship(){
        cout<<"National Campionship\n";
        printRound(vecNationalChampionship);
        if(vecNationalChampionship[0][0]->avgRankWeight<vecNationalChampionship[0][1]->avgRankWeight){
            cout<<vecNationalChampionship[0][0]->name<<" wins!\n";
        }
        else{
            cout<<vecNationalChampionship[0][1]->name<<" wins!\n";
        }
    }
private:
    vector<TeamInfo>vec;
    //For later rounds
    vector<vector<TeamInfo*>> vecRoundof64;
    vector<vector<TeamInfo*>> vecRoundof32;
    vector<vector<TeamInfo*>> vecSweetSixteen;
    vector<vector<TeamInfo*>> vecEliteEight;
    vector<vector<TeamInfo*>> vecFinalFour;
    vector<vector<TeamInfo*>> vecNationalChampionship;
    TeamInfo nationChampion;
    unordered_map<string,int> teamIndex;
    
    //Helper functions
    void calcRound(vector<vector<TeamInfo*>>&currRound,vector<vector<TeamInfo*>>&nextRound){
        for(int i=0;i<(int)currRound.size();++i){
            if(currRound[i][0]->avgRankWeight<currRound[i][1]->avgRankWeight){
                //nextRound[i/2].push_back(nextRound[i][0]);
                nextRound[i/2][i%2]=currRound[i][0];
            }
            else{
                //nextRound[i/2].push_back(nextRound[i][1]);
                nextRound[i/2][i%2]=currRound[i][1];
            }
        }
    }
    void printRound(vector<vector<TeamInfo*>>&vec1){
        Regions currentRegion= vec1[0][0]->region;
        if((int)vec1.size()>2)
            cout<<vec1[0][0]->regionName<<"\n\n";
        for(int i=0;i<(int)vec1.size();++i){
            //if(i%8==0&&i!=0){
            if(currentRegion!=vec1[i][0]->region&&(int)vec1.size()>2){
                currentRegion=vec1[i][0]->region;
                cout<<vec1[i][0]->regionName<<"\n"<<endl<<endl;
            }
            cout<<vec1[i][0]->name<<endl<<vec1[i][1]->name<<endl<<endl;
        }
        cout<<"----------------------------------\n";
    }
    void resizeVecs(vector<vector<TeamInfo*>>&vec1){
        for(int i=0;i<(int)vec1.size();++i){
            vec1[i].resize(2);
        }
    }
    
};


#endif /* Bracket_h */
