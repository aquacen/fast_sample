/* 
 * File:   main.cpp
 * Author: fpereira
 *
 * Created on December 4, 2014, 4:31 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>

#include "AquaHelp.h"
#include "AquaParam.h"
#include "AquaException.h"
#include "AquaParamFeature.h"
#include "AquaFile.h"
#include "AquaUtils.h"

using namespace std;

#include <unordered_map>
#include <algorithm>

std::vector<AquaParamFeature *> AquaParam::features;
std::string AquaHelp::name = "Fasta(q) MC Sample";
std::string AquaHelp::version = "2.0.0";

class Tpair{
public:
    string dna1;
    string qual1;
    
    string dna2;
    string qual2;
};

std::string revcom(std::string data) {
    std::string rew = std::string(data.rbegin(), data.rend());
    const char * newdna = rew.c_str();
    char * newdna2 = new char[strlen(newdna)+1];
    for (int i=0; i<rew.size(); i++){
        if (newdna[i]=='A') newdna2[i]='T';
        else if (newdna[i]=='C') newdna2[i]='G';
        else if (newdna[i]=='G') newdna2[i]='C';
        else if (newdna[i]=='T') newdna2[i]='A';
        else if (newdna[i]=='a') newdna2[i]='t';
        else if (newdna[i]=='c') newdna2[i]='g';
        else if (newdna[i]=='g') newdna2[i]='c';
        else if (newdna[i]=='t') newdna2[i]='a';
    }
    newdna2[strlen(newdna)]='\0';
    return std::string(newdna2);
}

std::string rev(std::string data) {
    return std::string(data.rbegin(), data.rend());
}

void sampleFastq(FILE * pt, FILE * &ptOut, int percentClip, int leftClip, int rightClip, int minClip, int maxClip){
    int numReads = 0;
    int numReadsTotal = 0;
    int numBases = 0;
    while ( !feof(pt) ){
        char *name = new char[2048];
	fgets(name, 2048, pt);
	string sname = std::string(name);
        if (sname.size()<3){ continue; }
        sname = sname.substr(1, sname.size()-2);
        
        numReadsTotal++;
        
        char *seq = new char[2048];
	fgets(seq, 2048, pt);
	string sseq = std::string(seq);
        if (sseq.find("\n")!=std::string::npos){
            sseq = sseq.substr(0, sseq.size()-1);
        }
        
        char *mais = new char[2048];
	fgets(mais, 2048, pt);
        
        char *qual = new char[2048];
	fgets(qual, 2048, pt);
	string squal = std::string(qual);
        if (squal.find("\n")!=std::string::npos){
            squal = squal.substr(0, squal.size()-1);
        }
        
        int mc = rand() % 100 + 1;
        if (mc > percentClip){ continue; }
        
        if (sseq.size() > leftClip){
            sseq = sseq.substr(leftClip);
            squal = squal.substr(leftClip);
        } else {
            continue;
        }
        
        if (rightClip > 0){
            int newSize = sseq.size() - rightClip;
            if (newSize > 0){
                sseq = sseq.substr(0, newSize);
                squal = squal.substr(0, newSize);
            } else {
                continue;
            }
        }
        
        if (sseq.size() > maxClip){
            sseq = sseq.substr(0, maxClip);
            squal = squal.substr(0, maxClip);
        }
        
        if (sseq.size() < minClip){
            continue;
        }        
        
        numReads++;
        numBases += sseq.size();
        
        fprintf(ptOut, "@%s\n%s\n+\n%s\n", sname.c_str(), sseq.c_str(), squal.c_str());
    }
    
    cout << "# reads in: " << numReadsTotal << endl;
    cout << "# reads out: " << numReads << endl;
    cout << "# bases: " << numBases << endl;
}

int main(int argc, char** argv) {
    try{
        bool rev2 = false;
        
        AquaParamFeature * pFSA        = new AquaParamFeature(string("-f"), true,  "*Fasta or Fastq file");
        AquaParamFeature * pSampleSize = new AquaParamFeature(string("-n"), true,  " Percent sample size (default: 50)");
        
        AquaParamFeature * pLeft       = new AquaParamFeature(string("-l"), true, " Left clip (default: 17)");
        AquaParamFeature * pRight      = new AquaParamFeature(string("-r"), true, " Right clip (default: 0)");
        AquaParamFeature * pMin        = new AquaParamFeature(string("-s"), true, " Min read size (default: 50)");
        AquaParamFeature * pMax        = new AquaParamFeature(string("-b"), true, " Max read size (default: 9999), cut bp after this number");
        
        AquaParamFeature * pHelp       = new AquaParamFeature(string("-h"), false, " Show this help");
        AquaParamFeature * pVersion    = new AquaParamFeature(string("-v"), false, " Show version");
        AquaParam::startArgs(argc, argv);
        if (pHelp->value=="T") AquaHelp::show(argv);
        if (pVersion->value=="T") AquaHelp::showVersion(argv);
        if (pSampleSize->value == "") pSampleSize->value = "50";
        if (pLeft->value == "") pLeft->value = "17";
        if (pRight->value == "") pRight->value = "0";
        if (pMin->value == "") pMin->value = "50";
        if (pMax->value == "") pMax->value = "9999";
        AquaParam::checkRequireds();
        
        //AquaUtils::mkDir(pOut->value);
        
        AquaFile * fHandler = new AquaFile();
        FILE * pt = fHandler->open(pFSA->value, "r");
        vector<string> paths = AquaUtils::explode("/", pFSA->value);
        string last = paths[paths.size()-1];
        
        stringstream ss;
        ss.str("");
        ss << last << "_sample_n_" << pSampleSize->value ;
        if (pLeft->value != "17") ss << "_l_" << pLeft->value ;
        if (pRight->value != "0") ss << "_r_" << pRight->value;
        if (pMin->value != "50") ss << "_min_" << pMin->value;
        if (pMax->value != "9999") ss << "_max_" << pMax->value;
        
        char *a = new char[2];
	fgets(a, 2, pt);
	string b = string(a);
        int tipo = 1;
	if (b == ">"){
            cout << "FASTA: [" << a << "]\n";
            ss << ".fasta";
	} else if (b == "@"){
            cout << "FASTQ: [" << a << "]\n";
            ss << ".fastq";
            tipo = 2;
	} else {
            AquaException e;
            e.msg = "Doesn't appear be a fasta or fastq file.";
            throw e;
        }
        fseek ( pt , 0 , SEEK_SET );
        srand (time(NULL));
        
        cout << "File out: " << ss.str() << endl;
        
        int leftClip = atoi(pLeft->value.c_str());
        int rightClip = atoi(pRight->value.c_str());
        int minClip = atoi(pMin->value.c_str());
        int maxClip = atoi(pMax->value.c_str());
        int percentClip = atoi(pSampleSize->value.c_str());
        FILE * ptOut = fHandler->open(ss.str().c_str(), "w+");
        if (tipo == 1){
            //no implemented yet
        } else {
            sampleFastq(pt, ptOut, percentClip, leftClip, rightClip, minClip, maxClip);
        }
                
    } catch (AquaException e){
        if (e.msg != "clean"){
            fprintf(stderr,e.msg.c_str());
            cout << endl;
            return 1;
        }
    }
    cout << endl;
    return 0;
}

