/*
 * =====================================================================================
 *
 *       Filename:  myMinuit.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/09/2022 19:10:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */


#ifndef MY_MINUIT_H
#define MY_MINUIT_H
#include "TMinuit.h"
#include "TMath.h"
#include "TRandom.h"
#include <iostream>
using namespace std;

class myMinuit : public TMinuit {

	public:
		myMinuit() : TMinuit(){
		}
		myMinuit(Int_t maxpar): TMinuit(maxpar){
		}
		virtual void   mnprin(Int_t inkode, Double_t fval);
		virtual void   mnprin1(Int_t inkode, Double_t fval);
		virtual void   mnprin2(Int_t inkode, Double_t fval);
		virtual void   setRandomSeed(const int rdmSeed);
	private:
		int m_rdmSeed;
		vector<double> m_rdmVal;
		bool flag_rdm = false;

	public:
		ClassDef(myMinuit, 1)
};
#endif
