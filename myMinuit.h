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
#include <iostream>
using namespace std;

class myMinuit : public TMinuit {

	public:
		myMinuit() : TMinuit(){
		}
		myMinuit(Int_t maxpar): TMinuit(maxpar){
		}
   		virtual void   mnexcm(const char *comand, Double_t *plist, Int_t llist, Int_t &ierflg) ;
		ClassDef(myMinuit, 1)
};
#endif
