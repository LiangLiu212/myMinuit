/*
 * =====================================================================================
 *
 *       Filename:  blindMinuit.h
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

class blindMinuit : public TMinuit {

	public:
		blindMinuit() : TMinuit(){
				m_Offset = 10.0;
		}
		blindMinuit(Int_t maxpar): TMinuit(maxpar){
				m_Offset = 10.0;
		}
		virtual void   mnprin(Int_t inkode, Double_t fval);
		virtual void   mnprin1(Int_t inkode, Double_t fval);
		virtual void   mnprin2(Int_t inkode, Double_t fval);
		
		virtual void   mnpout(Int_t iuext1, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const;
		virtual void   mnpout1(Int_t iuext1, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const;
		virtual void   mnpout2(Int_t iuext1, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const;

		// Blind analysis
		virtual void   blindParameter(const int n);
		virtual void   unblindParameter(const int n);
		virtual void   blindParameter(bool okblind = true);
		virtual void   unblindParameter(bool okunblind = true);
		virtual void   setRandomSeed(const int rdmSeed);
		virtual void   setOffsetRange(const double offset = 10.0){
				m_Offset = offset;
		}
	private:
		int m_rdmSeed;
		double m_Offset;
		vector<double> m_rdmVal;
		vector<double> m_signVal;
		vector<double> m_tmpsignVal;
		vector<double> m_tmprdmVal;
		bool flag_rdm = false;
		bool fblind;
		bool funblind;

};
#endif
