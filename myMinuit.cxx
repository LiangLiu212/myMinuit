/*
 * =====================================================================================
 *
 *       Filename:  myTMinuit.cxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/09/2022 19:50:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */


#include "myMinuit.h"


ClassImp(myMinuit);

////////////////////////////////////////////////////////////////////////////////
/// Prints the values of the parameters at the time of the call
///
/// also prints other relevant information such as function value,
/// estimated distance to minimum, parameter errors, step sizes.
///
/// According to the value of IKODE, the printout is:
/// IKODE=INKODE=
///                -  0    only info about function value
///                -  1    parameter values, errors, limits
///                -  2    values, errors, step sizes, internal values
///                -  3    values, errors, step sizes, first derivs.
///                -  4    values, parabolic errors, MINOS errors
///
///    when INKODE=5, MNPRIN chooses IKODE=1,2, or 3, according to fISW[1]



void myMinuit::setRandomSeed(const int rdmSeed){
	flag_rdm = true;
	m_rdmVal.clear();
	TRandom *rdm = new TRandom();
	rdm->SetSeed(rdmSeed);
	for(int i =0; i < fMaxpar; i++){
		m_rdmVal.push_back(rdm->Rndm());
	//	cout << "m_rdmVal = " << m_rdmVal[i] << endl;
	}
}

void myMinuit::mnprin(Int_t inkode, Double_t fval){
	if(flag_rdm){
		mnprin2(inkode, fval);
	}
	else {
		mnprin1(inkode, fval);
	}
}



void myMinuit::mnprin1(Int_t inkode, Double_t fval)
{
   /* Initialized data */

   static const TString cblank = "           ";
   TString cnambf = "           ";

   /* Local variables */
   Double_t dcmax, x1, x2, x3, dc;
   x2 = x3 = 0;
   Int_t nadd, i, k, l, m, ikode, ic, nc, ntrail, lbl;
   TString chedm;
   TString colhdl[6], colhdu[6], cx2, cx3, cheval;

   if (fNu == 0) {
      Printf(" THERE ARE CURRENTLY NO PARAMETERS DEFINED");
      return;
   }
//                 get value of IKODE based in INKODE, fISW[1]
   ikode = inkode;
   if (inkode == 5) {
      ikode = fISW[1] + 1;
      if (ikode > 3) ikode = 3;
   }
//                 set 'default' column headings
   for (k = 1; k <= 6; ++k) {
      colhdu[k-1] = "UNDEFINED";
      colhdl[k-1] = "COLUMN HEAD";
   }
//             print title if Minos errors, and title exists.
   if (ikode == 4 && fCtitl != fCundef) {
      Printf(" MINUIT TASK: %s",(const char*)fCtitl);
   }
//             report function value and status
   if (fval == fUndefi) cheval = " unknown       ";
   else                 cheval.Form("%g",fval);

   if (fEDM == fBigedm) chedm = " unknown  ";
   else                 chedm.Form("%g",fEDM);

   nc = fNfcn - fNfcnfr;
   Printf(" FCN=%s FROM %8s  STATUS=%10s %6d CALLS   %9d TOTAL"
               ,(const char*)cheval
               ,(const char*)fCfrom
               ,(const char*)fCstatu,nc,fNfcn);
   m = fISW[1];
   if (m == 0 || m == 2 || fDcovar == 0) {
      Printf("                     EDM=%s    STRATEGY=%2d      %s"
                      ,(const char*)chedm,fIstrat
                      ,(const char*)fCovmes[m]);
   } else {
      dcmax = 1;
      dc    = TMath::Min(fDcovar,dcmax)*100;
      Printf("                     EDM=%s    STRATEGY=%2d  ERROR MATRIX UNCERTAINTY %5.1f per cent"
                      ,(const char*)chedm,fIstrat,dc);
   }

   if (ikode == 0) return;
//              find longest name (for Rene!)
   ntrail = 10;
   for (i = 1; i <= fNu; ++i) {
      if (fNvarl[i-1] < 0) continue;
      for (ic = 10; ic >= 1; --ic) {
         if (fCpnam[i-1](ic-1,1) != " ") goto L16;
      }
      ic = 1;
L16:
      lbl = 10 - ic;
      if (lbl < ntrail) ntrail = lbl;
   }
   nadd = ntrail / 2 + 1;
   if (ikode == 1) {
      colhdu[0] = "              ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "      PHYSICAL";
      colhdu[2] = " LIMITS       ";
      colhdl[1] = "    NEGATIVE  ";
      colhdl[2] = "    POSITIVE  ";
   }
   if (ikode == 2) {
      colhdu[0] = "              ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "    INTERNAL  ";
      colhdl[1] = "    STEP SIZE ";
      colhdu[2] = "    INTERNAL  ";
      colhdl[2] = "      VALUE   ";
   }
   if (ikode == 3) {
      colhdu[0] = "              ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "       STEP   ";
      colhdl[1] = "       SIZE   ";
      colhdu[2] = "      FIRST   ";
      colhdl[2] = "   DERIVATIVE ";
   }
   if (ikode == 4) {
      colhdu[0] = "    PARABOLIC ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "        MINOS ";
      colhdu[2] = "ERRORS        ";
      colhdl[1] = "   NEGATIVE   ";
      colhdl[2] = "   POSITIVE   ";
   }

   if (ikode != 4) {
      if (fISW[1] < 3) colhdu[0] = "  APPROXIMATE ";
      if (fISW[1] < 1) colhdu[0] = " CURRENT GUESS";
   }
   Printf("  EXT PARAMETER              %-14s%-14s%-14s",(const char*)colhdu[0]
                                                    ,(const char*)colhdu[1]
                                                    ,(const char*)colhdu[2]);
   Printf("  NO.   NAME      VALUE       %-14s%-14s%-14s",(const char*)colhdl[0]
                                                    ,(const char*)colhdl[1]
                                                    ,(const char*)colhdl[2]);
//                                             loop over parameters
   for (i = 1; i <= fNu; ++i) {
      if (fNvarl[i-1] < 0) continue;
      l = fNiofex[i-1];
      cnambf = cblank(0,nadd) + fCpnam[i-1];
      if (l == 0) goto L55;
//             variable parameter.
      x1  = fWerr[l-1];
      cx2 = "PLEASE GET X..";
      cx3 = "PLEASE GET X..";
      if (ikode == 1) {
         if (fNvarl[i-1] <= 1) {
            Printf(" %4d %-11s%14.5e%14.5e",i,(const char*)cnambf,fU[i-1],x1);
            continue;
         } else {
            x2 = fAlim[i-1];
            x3 = fBlim[i-1];
         }
      }
      if (ikode == 2) {
         x2 = fDirin[l-1];
         x3 = fX[l-1];
      }
      if (ikode == 3) {
         x2 = fDirin[l-1];
         x3 = fGrd[l-1];
         if (fNvarl[i-1] > 1 && TMath::Abs(TMath::Cos(fX[l-1])) < .001) {
            cx3 = "** at limit **";
         }
      }
      if (ikode == 4) {
         x2 = fErn[l-1];
         if (x2 == 0)        cx2 = " ";
         if (x2 == fUndefi)  cx2 = "   at limit   ";
         x3 = fErp[l-1];
         if (x3 == 0)        cx3 = " ";
         if (x3 == fUndefi)         cx3 = "   at limit   ";
      }
      if (cx2 == "PLEASE GET X..")  cx2.Form("%14.5e",x2);
      if (cx3 == "PLEASE GET X..")  cx3.Form("%14.5e",x3);
      Printf(" %4d %-11s%14.5e %14.5e%-14s%-14s",i
                   ,(const char*)cnambf,fU[i-1],  x1
                   ,(const char*)cx2,(const char*)cx3);

//              check if parameter is at limit
      if (fNvarl[i-1] <= 1 || ikode == 3) continue;
      if (TMath::Abs(TMath::Cos(fX[l-1])) < .001) {
         Printf("                                 WARNING -   - ABOVE PARAMETER IS AT LIMIT.");
      }
      continue;

//                               print constant or fixed parameter.
L55:
      colhdu[0] = "   constant   ";
      if (fNvarl[i-1] > 0)  colhdu[0] = "     fixed    ";
      if (fNvarl[i-1] == 4 && ikode == 1) {
         Printf(" %4d %-11s%14.5e%-14s%14.5e%14.5e",i
              ,(const char*)cnambf,fU[i-1]
              ,(const char*)colhdu[0],fAlim[i-1],fBlim[i-1]);
      } else {
         Printf(" %4d %-11s%14.5e%s",i
                   ,(const char*)cnambf,fU[i-1],(const char*)colhdu[0]);
      }
   }

   if (fUp != fUpdflt) {
      Printf("                               ERR DEF= %g",fUp);
   }
   return;
}




void myMinuit::mnprin2(Int_t inkode, Double_t fval)
{
   /* Initialized data */

   static const TString cblank = "           ";
   TString cnambf = "           ";

   /* Local variables */
   Double_t dcmax, x1, x2, x3, dc;
   x2 = x3 = 0;
   Int_t nadd, i, k, l, m, ikode, ic, nc, ntrail, lbl;
   TString chedm;
   TString colhdl[6], colhdu[6], cx2, cx3, cheval;

   if (fNu == 0) {
      Printf(" THERE ARE CURRENTLY NO PARAMETERS DEFINED");
      return;
   }
//                 get value of IKODE based in INKODE, fISW[1]
   ikode = inkode;
   if (inkode == 5) {
      ikode = fISW[1] + 1;
      if (ikode > 3) ikode = 3;
   }
//                 set 'default' column headings
   for (k = 1; k <= 6; ++k) {
      colhdu[k-1] = "UNDEFINED";
      colhdl[k-1] = "COLUMN HEAD";
   }
//             print title if Minos errors, and title exists.
   if (ikode == 4 && fCtitl != fCundef) {
      Printf(" MINUIT TASK: %s",(const char*)fCtitl);
   }
//             report function value and status
   if (fval == fUndefi) cheval = " unknown       ";
   else                 cheval.Form("%g",fval);

   if (fEDM == fBigedm) chedm = " unknown  ";
   else                 chedm.Form("%g",fEDM);

   nc = fNfcn - fNfcnfr;
   Printf(" FCN=%s FROM %8s  STATUS=%10s %6d CALLS   %9d TOTAL"
               ,(const char*)cheval
               ,(const char*)fCfrom
               ,(const char*)fCstatu,nc,fNfcn);
   m = fISW[1];
   if (m == 0 || m == 2 || fDcovar == 0) {
      Printf("                     EDM=%s    STRATEGY=%2d      %s"
                      ,(const char*)chedm,fIstrat
                      ,(const char*)fCovmes[m]);
   } else {
      dcmax = 1;
      dc    = TMath::Min(fDcovar,dcmax)*100;
      Printf("                     EDM=%s    STRATEGY=%2d  ERROR MATRIX UNCERTAINTY %5.1f per cent"
                      ,(const char*)chedm,fIstrat,dc);
   }

   if (ikode == 0) return;
//              find longest name (for Rene!)
   ntrail = 10;
   for (i = 1; i <= fNu; ++i) {
      if (fNvarl[i-1] < 0) continue;
      for (ic = 10; ic >= 1; --ic) {
         if (fCpnam[i-1](ic-1,1) != " ") goto L16;
      }
      ic = 1;
L16:
      lbl = 10 - ic;
      if (lbl < ntrail) ntrail = lbl;
   }
   nadd = ntrail / 2 + 1;
   if (ikode == 1) {
      colhdu[0] = "              ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "      PHYSICAL";
      colhdu[2] = " LIMITS       ";
      colhdl[1] = "    NEGATIVE  ";
      colhdl[2] = "    POSITIVE  ";
   }
   if (ikode == 2) {
      colhdu[0] = "              ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "    INTERNAL  ";
      colhdl[1] = "    STEP SIZE ";
      colhdu[2] = "    INTERNAL  ";
      colhdl[2] = "      VALUE   ";
   }
   if (ikode == 3) {
      colhdu[0] = "              ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "       STEP   ";
      colhdl[1] = "       SIZE   ";
      colhdu[2] = "      FIRST   ";
      colhdl[2] = "   DERIVATIVE ";
   }
   if (ikode == 4) {
      colhdu[0] = "    PARABOLIC ";
      colhdl[0] = "      ERROR   ";
      colhdu[1] = "        MINOS ";
      colhdu[2] = "ERRORS        ";
      colhdl[1] = "   NEGATIVE   ";
      colhdl[2] = "   POSITIVE   ";
   }

   if (ikode != 4) {
      if (fISW[1] < 3) colhdu[0] = "  APPROXIMATE ";
      if (fISW[1] < 1) colhdu[0] = " CURRENT GUESS";
   }
   Printf("  EXT PARAMETER              %-14s%-14s%-14s",(const char*)colhdu[0]
                                                    ,(const char*)colhdu[1]
                                                    ,(const char*)colhdu[2]);
   Printf("  NO.   NAME      VALUE + OFFSET      %-14s%-14s%-14s",(const char*)colhdl[0]
                                                    ,(const char*)colhdl[1]
                                                    ,(const char*)colhdl[2]);
//                                             loop over parameters
   for (i = 1; i <= fNu; ++i) {
      if (fNvarl[i-1] < 0) continue;
      l = fNiofex[i-1];
      cnambf = cblank(0,nadd) + fCpnam[i-1];
      if (l == 0) goto L55;
//             variable parameter.
      x1  = fWerr[l-1];
      cx2 = "PLEASE GET X..";
      cx3 = "PLEASE GET X..";
      if (ikode == 1) {
         if (fNvarl[i-1] <= 1) {
            Printf("OK ! %4d %-11s%14.5e%14.5e",i,(const char*)cnambf,fU[i-1],x1);
            continue;
         } else {
            x2 = fAlim[i-1];
            x3 = fBlim[i-1];
         }
      }
      if (ikode == 2) {
         x2 = fDirin[l-1];
         x3 = fX[l-1];
      }
      if (ikode == 3) {
         x2 = fDirin[l-1];
         x3 = fGrd[l-1];
         if (fNvarl[i-1] > 1 && TMath::Abs(TMath::Cos(fX[l-1])) < .001) {
            cx3 = "** at limit **";
         }
      }
      if (ikode == 4) {
         x2 = fErn[l-1];
         if (x2 == 0)        cx2 = " ";
         if (x2 == fUndefi)  cx2 = "   at limit   ";
         x3 = fErp[l-1];
         if (x3 == 0)        cx3 = " ";
         if (x3 == fUndefi)         cx3 = "   at limit   ";
      }
      if (cx2 == "PLEASE GET X..")  cx2.Form("%14.5e",x2);
      if (cx3 == "PLEASE GET X..")  cx3.Form("%14.5e",x3);
      Printf("OK 1 %4d %-11s%14.5e %14.5e%-14s%-14s",i
                   ,(const char*)cnambf,fU[i-1] + (m_rdmVal[i-1] *2.0 - 1.0) * m_Offset , x1
                   ,(const char*)cx2,(const char*)cx3);

//              check if parameter is at limit
      if (fNvarl[i-1] <= 1 || ikode == 3) continue;
      if (TMath::Abs(TMath::Cos(fX[l-1])) < .001) {
         Printf("                                 WARNING -   - ABOVE PARAMETER IS AT LIMIT.");
      }
      continue;

//                               print constant or fixed parameter.
L55:
      colhdu[0] = "   constant   ";
      if (fNvarl[i-1] > 0)  colhdu[0] = "     fixed    ";
      if (fNvarl[i-1] == 4 && ikode == 1) {
         Printf("OK 2 %4d %-11s%14.5e%-14s%14.5e%14.5e",i
              ,(const char*)cnambf,fU[i-1]
              ,(const char*)colhdu[0],fAlim[i-1],fBlim[i-1]);
      } else {
         Printf("OK 3 %4d %-11s%14.5e%s",i
                   ,(const char*)cnambf,fU[i-1],(const char*)colhdu[0]);
      }
   }

   if (fUp != fUpdflt) {
      Printf("                               ERR DEF= %g",fUp);
   }
   return;
}


////////////////////////////////////////////////////////////////////////////////
/// Provides the user with information concerning the current status
///
/// of parameter number IUEXT. Namely, it returns:
///      -  CHNAM: the name of the parameter
///      -  VAL: the current (external) value of the parameter
///      -  ERR: the current estimate of the parameter uncertainty
///      -  XLOLIM: the lower bound (or zero if no limits)
///      -  XUPLIM: the upper bound (or zero if no limits)
///      -  IUINT: the internal parameter number (or zero if not variable,
///            or negative if undefined).
///
///  Note also:  If IUEXT is negative, then it is -internal parameter
///           number, and IUINT is returned as the EXTERNAL number.
///     Except for IUINT, this is exactly the inverse of MNPARM
///     User-called
 


void myMinuit::mnpout(Int_t iuext1, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const
{
	if(flag_rdm){
		mnpout2(iuext1, chnam, val, err, xlolim, xuplim, iuint);
	}
	else {
		mnpout1(iuext1, chnam, val, err, xlolim, xuplim, iuint);
	}
}




void myMinuit::mnpout1(Int_t iuext1, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const
{
   /* Local variables */
   Int_t iint, iext, nvl;
 
   Int_t iuext = iuext1 + 1;
   xlolim = 0;
   xuplim = 0;
   err    = 0;
   if (iuext == 0) goto L100;
   if (iuext < 0) {
//                  internal parameter number specified
      iint  = -(iuext);
      if (iint > fNpar) goto L100;
      iext  = fNexofi[iint-1];
      iuint = iext;
   } else {
//                   external parameter number specified
      iext = iuext;
      if (iext > fNu) goto L100;
      iint  = fNiofex[iext-1];
      iuint = iint;
   }
//                    in both cases
   nvl = fNvarl[iext-1];
   if (nvl < 0) goto L100;
   chnam = fCpnam[iext-1];
   val   = fU[iext-1];
   if (iint > 0) err = fWerr[iint-1];
   if (nvl == 4) {
      xlolim = fAlim[iext-1];
      xuplim = fBlim[iext-1];
   }
   return;
//               parameter is undefined
L100:
   iuint = -1;
   chnam = "undefined";
   val = 0;
}
 

void myMinuit::mnpout2(Int_t iuext1, TString &chnam, Double_t &val, Double_t &err, Double_t &xlolim, Double_t &xuplim, Int_t &iuint) const
{
   /* Local variables */
   Int_t iint, iext, nvl;
 
   Int_t iuext = iuext1 + 1;
   xlolim = 0;
   xuplim = 0;
   err    = 0;
   if (iuext == 0) goto L100;
   if (iuext < 0) {
//                  internal parameter number specified
      iint  = -(iuext);
      if (iint > fNpar) goto L100;
      iext  = fNexofi[iint-1];
      iuint = iext;
   } else {
//                   external parameter number specified
      iext = iuext;
      if (iext > fNu) goto L100;
      iint  = fNiofex[iext-1];
      iuint = iint;
   }
//                    in both cases
   nvl = fNvarl[iext-1];
   if (nvl < 0) goto L100;
   chnam = fCpnam[iext-1];
   val   = fU[iext-1] + (m_rdmVal[iext-1] *2.0 - 1.0) * m_Offset;
   if (iint > 0) err = fWerr[iint-1];
   if (nvl == 4) {
      xlolim = fAlim[iext-1];
      xuplim = fBlim[iext-1];
   }
   return;
//               parameter is undefined
L100:
   iuint = -1;
   chnam = "undefined";
   val = 0;
}
 













