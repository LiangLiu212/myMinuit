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

////////////////////////////////////////////////////////////////////////////////
/// Interprets a command and takes appropriate action
///
///        either directly by skipping to the corresponding code in
///        MNEXCM, or by setting up a call to a function
///
///  recognized MINUIT commands:
///  obsolete commands:
///      IERFLG is now (94.5) defined the same as ICONDN in MNCOMD =
///           -   0: command executed normally
///           -   1: command is blank, ignored
///           -   2: command line unreadable, ignored
///           -   3: unknown command, ignored
///           -   4: abnormal termination (e.g., MIGRAD not converged)
///           -   9: reserved
///           -  10: END command
///           -  11: EXIT or STOP command
///           -  12: RETURN command
///
/// see also
/// [the possible list of all Minuit commands](https://root.cern.ch/sites/d35c7d8c.web.cern.ch/files/minuit.pdf).
ClassImp(myMinuit);
void myMinuit::mnexcm(const char *command, Double_t *plist, Int_t llist, Int_t &ierflg)
{
   /* Initialized data */
	cout << "hello world!" << endl;
   TString comand = command;
   static const char *const cname[40] = {
      "MINImize  ",
      "SEEk      ",
      "SIMplex   ",
      "MIGrad    ",
      "MINOs     ",
      "SET xxx   ",
      "SHOw xxx  ",
      "TOP of pag",
      "FIX       ",
      "REStore   ",
      "RELease   ",
      "SCAn      ",
      "CONtour   ",
      "HESse     ",
      "SAVe      ",
      "IMProve   ",
      "CALl fcn  ",
      "STAndard  ",
      "END       ",
      "EXIt      ",
      "RETurn    ",
      "CLEar     ",
      "HELP      ",
      "MNContour ",
      "STOp      ",
      "JUMp      ",
      "          ",
      "          ",
      "          ",
      "          ",
      "          ",
      "          ",
      "          ",
      "COVARIANCE",
      "PRINTOUT  ",
      "GRADIENT  ",
      "MATOUT    ",
      "ERROR DEF ",
      "LIMITS    ",
      "PUNCH     "};

   Int_t nntot = 40;

   /* Local variables */
   Double_t step, xptu[101], yptu[101], f, rno;
   Int_t icol, kcol, ierr, iint, iext, lnow, nptu, i, iflag, ierrf;
   Int_t ilist, nparx, izero, nf, lk, it, iw, inonde, nsuper;
   Int_t it2, ke1, ke2, nowprt, kll, krl;
   TString chwhy, c26, cvblnk, cneway, comd;
   TString ctemp;
   Bool_t lfreed, ltofix, lfixed;

//  alphabetical order of command names!

   /* Function Body */

   lk = comand.Length();
   if (lk > 20) lk = 20;
   fCword =  comand;
   fCword.ToUpper();
//          Copy the first MAXP arguments into WORD7, making
//          sure that WORD7(1)=0 if LLIST=0
   for (iw = 1; iw <= fMaxpar; ++iw) {
      fWord7[iw-1] = 0;
      if (iw <= llist) fWord7[iw-1] = plist[iw-1];
   }
   ++fIcomnd;
   fNfcnlc = fNfcn;
   if (fCword(0,7) != "SET PRI" || fWord7[0] >= 0) {
      if (fISW[4] >= 0) {
         lnow = llist;
         if (lnow > 4) lnow = 4;
         Printf(" **********");
         ctemp.Form(" **%5d **%s",fIcomnd,(const char*)fCword);
         for (i = 1; i <= lnow; ++i) {
            ctemp += TString::Format("%12.4g",plist[i-1]);
         }
         Printf("%s",(const char*)ctemp);
         inonde = 0;
         if (llist > lnow) {
            kll = llist;
            if (llist > fMaxpar) {
               inonde = 1;
               kll = fMaxpar;
            }
            Printf(" ***********");
            for (i = lnow + 1; i <= kll; ++i) {
               Printf("%12.4g",plist[i-1]);
            }
         }
         Printf(" **********");
         if (inonde > 0) {
            Printf("  ERROR: ABOVE CALL TO MNEXCM TRIED TO PASS MORE THAN %d PARAMETERS.", fMaxpar);
         }
      }
   }
   fNfcnmx = Int_t(fWord7[0]);
   if (fNfcnmx <= 0) {
      fNfcnmx = fNpar*100 + 200 + fNpar*fNpar*5;
   }
   fEpsi = fWord7[1];
   if (fEpsi <= 0) {
      fEpsi = fUp*.1;
   }
   fLnewmn = kFALSE;
   fLphead = kTRUE;
   fISW[0] = 0;
   ierflg = 0;
//               look for command in list CNAME
   ctemp = fCword(0,3);
   for (i = 1; i <= nntot; ++i) {
      if (strncmp(ctemp.Data(),cname[i-1],3) == 0) goto L90;
   }
   Printf("UNKNOWN COMMAND IGNORED:%s", comand.Data());
   ierflg = 3;
   return;
//               normal case: recognized MINUIT command
L90:
   if (fCword(0,4) == "MINO") i = 5;
   if (i != 6 && i != 7 && i != 8 && i != 23) {
      fCfrom  = cname[i-1];
      fNfcnfr = fNfcn;
   }
//             1    2    3    4    5    6    7    8    9   10
   switch (i) {
      case 1:  goto L400;
      case 2:  goto L200;
      case 3:  goto L300;
      case 4:  goto L400;
      case 5:  goto L500;
      case 6:  goto L700;
      case 7:  goto L700;
      case 8:  goto L800;
      case 9:  goto L900;
      case 10:  goto L1000;
      case 11:  goto L1100;
      case 12:  goto L1200;
      case 13:  goto L1300;
      case 14:  goto L1400;
      case 15:  goto L1500;
      case 16:  goto L1600;
      case 17:  goto L1700;
      case 18:  goto L1800;
      case 19:  goto L1900;
      case 20:  goto L1900;
      case 21:  goto L1900;
      case 22:  goto L2200;
      case 23:  goto L2300;
      case 24:  goto L2400;
      case 25:  goto L1900;
      case 26:  goto L2600;
      case 27:  goto L3300;
      case 28:  goto L3300;
      case 29:  goto L3300;
      case 30:  goto L3300;
      case 31:  goto L3300;
      case 32:  goto L3300;
      case 33:  goto L3300;
      case 34:  goto L3400;
      case 35:  goto L3500;
      case 36:  goto L3600;
      case 37:  goto L3700;
      case 38:  goto L3800;
      case 39:  goto L3900;
      case 40:  goto L4000;
   }
//                                                           seek
L200:
   mnseek();
   return;
//                                                           simplex
L300:
   mnsimp();
   if (fISW[3] < 1) ierflg = 4;
   return;
//                                                   migrad, minimize
L400:
   nf = fNfcn;
   fApsi = fEpsi;
   mnmigr();
   mnwerr();
   if (fISW[3] >= 1) return;
   ierflg = 4;
   if (fISW[0] == 1) return;
   if (fCword(0,3) == "MIG") return;

   fNfcnmx = fNfcnmx + nf - fNfcn;
   nf = fNfcn;
   mnsimp();
   if (fISW[0] == 1) return;
   fNfcnmx = fNfcnmx + nf - fNfcn;
   mnmigr();
   if (fISW[3] >= 1) ierflg = 0;
   mnwerr();
   return;
//                                                           minos
L500:
   nsuper = fNfcn + ((fNpar + 1) << 1)*fNfcnmx;
//         possible loop over new minima
   fEpsi = fUp*.1;
L510:
   fCfrom  = cname[i-1]; // ensure that mncuve complains about MINOS not MIGRAD
   mncuve();
   mnmnos();
   if (! fLnewmn) return;
   mnrset(0);
   mnmigr();
   mnwerr();
   if (fNfcn < nsuper) goto L510;
   Printf(" TOO MANY FUNCTION CALLS. MINOS GIVES UP");
   ierflg = 4;
   return;
//                                                          set, show
L700:
   mnset();
   return;
//                                                           top of page

L800:
   Printf("1");
   return;
//                                                           fix
L900:
   ltofix = kTRUE;
//                                           (also release)
L901:
   lfreed = kFALSE;
   lfixed = kFALSE;
   if (llist == 0) {
      Printf("%s:  NO PARAMETERS REQUESTED ",(const char*)fCword);
      return;
   }
   for (ilist = 1; ilist <= llist; ++ilist) {
      iext = Int_t(plist[ilist-1]);
      chwhy = " IS UNDEFINED.";
      if (iext <= 0) goto L930;
      if (iext > fNu) goto L930;
      if (fNvarl[iext-1] < 0) goto L930;
      chwhy = " IS CONSTANT.  ";
      if (fNvarl[iext-1] == 0) goto L930;
      iint = fNiofex[iext-1];
      if (ltofix) {
         chwhy = " ALREADY FIXED.";
         if (iint == 0) goto L930;
         mnfixp(iint-1, ierr);
         if (ierr == 0) lfixed = kTRUE;
         else           ierflg = 4;
      } else {
         chwhy = " ALREADY VARIABLE.";
         if (iint > 0) goto L930;
         krl = -abs(iext);
         mnfree(krl);
         lfreed = kTRUE;
      }
      continue;
L930:
      if (fISW[4] >= 0) Printf(" PARAMETER %4d %s IGNORED.",iext,(const char*)chwhy);
   }
   if (lfreed || lfixed) mnrset(0);
   if (lfreed) {
      fISW[1] = 0;
      fDcovar = 1;
      fEDM = fBigedm;
      fISW[3] = 0;
   }
   mnwerr();
   if (fISW[4] > 1) mnprin(5, fAmin);
   return;
//                                                           restore
L1000:
   it = Int_t(fWord7[0]);
   if (it > 1 || it < 0) goto L1005;
   lfreed = fNpfix > 0;
   mnfree(it);
   if (lfreed) {
      mnrset(0);
      fISW[1] = 0;
      fDcovar = 1;
      fEDM    = fBigedm;
   }
   return;
L1005:
   Printf(" IGNORED.  UNKNOWN ARGUMENT:%4d",it);
   ierflg = 3;
   return;
//                                                           release
L1100:
   ltofix = kFALSE;
   goto L901;
//                                                          scan
L1200:
   iext = Int_t(fWord7[0]);
   if (iext <= 0) goto L1210;
   it2 = 0;
   if (iext <= fNu) it2 = fNiofex[iext-1];
   if (it2 <= 0) goto L1250;

L1210:
   mnscan();
   return;
L1250:
   Printf(" PARAMETER %4d NOT VARIABLE.",iext);
   ierflg = 3;
   return;
//                                                           contour
L1300:
   ke1 = Int_t(fWord7[0]);
   ke2 = Int_t(fWord7[1]);
   if (ke1 == 0) {
      if (fNpar == 2) {
         ke1 = fNexofi[0];
         ke2 = fNexofi[1];
      } else {
         Printf("%s:  NO PARAMETERS REQUESTED ",(const char*)fCword);
         ierflg = 3;
         return;
      }
   }
   fNfcnmx = 1000;
   mncntr(ke1-1, ke2-1, ierrf);
   if (ierrf > 0) ierflg = 3;
   return;
//                                                           hesse
L1400:
   mnhess();
   mnwerr();
   if (fISW[4] >= 0) mnprin(2, fAmin);
   if (fISW[4] >= 1) mnmatu(1);
   return;
//                                                           save
L1500:
   mnsave();
   return;
//                                                           improve
L1600:
   mncuve();
   mnimpr();
   if (fLnewmn) goto L400;
   ierflg = 4;
   return;
//                                                           call fcn
L1700:
   iflag = Int_t(fWord7[0]);
   nparx = fNpar;
   f = fUndefi;
   Eval(nparx, fGin, f, fU, iflag);    ++fNfcn;
   nowprt = 0;
   if (f != fUndefi) {
      if (fAmin == fUndefi) {
         fAmin  = f;
         nowprt = 1;
      } else if (f < fAmin) {
         fAmin  = f;
         nowprt = 1;
      }
      if (fISW[4] >= 0 && iflag <= 5 && nowprt == 1) {
         mnprin(5, fAmin);
      }
      if (iflag == 3)  fFval3 = f;
   }
   if (iflag > 5) mnrset(1);
   return;
//                                                           standard
L1800:
//    stand();
   return;
//                                            return, stop, end, exit
L1900:
   it = Int_t(fWord7[0]);
   if (fFval3 != fAmin && it == 0) {
      iflag = 3;
      if (fISW[4] >= 0) Printf(" CALL TO USER FUNCTION WITH IFLAG = 3");
      nparx = fNpar;
      Eval(nparx, fGin, f, fU, iflag);        ++fNfcn;
   }
   ierflg = 11;
   if (fCword(0,3) == "END") ierflg = 10;
   if (fCword(0,3) == "RET") ierflg = 12;
   return;
//                                                           clear
L2200:
   mncler();
   if (fISW[4] >= 1) {
      Printf(" MINUIT MEMORY CLEARED. NO PARAMETERS NOW DEFINED.");
   }
   return;
//                                                           help
L2300:
   kcol = 0;
   for (icol = 5; icol <= lk; ++icol) {
      if (fCword[icol-1] == ' ') continue;
      kcol = icol;
      goto L2320;
   }
L2320:
   if (kcol == 0) comd = "*   ";
   else           comd = fCword(kcol-1,lk-kcol+1);
   mnhelp(comd);
   return;
//                                                          MNContour
L2400:
   fEpsi = fUp*.05;
   ke1 = Int_t(fWord7[0]);
   ke2 = Int_t(fWord7[1]);
   if (ke1 == 0 && fNpar == 2) {
      ke1 = fNexofi[0];
      ke2 = fNexofi[1];
   }
   nptu = Int_t(fWord7[2]);
   if (nptu <= 0)  nptu = 20;
   if (nptu > 101) nptu = 101;
   fNfcnmx = (nptu + 5)*100*(fNpar + 1);
   mncont(ke1-1, ke2-1, nptu, xptu, yptu, ierrf);
   if (ierrf < nptu) ierflg = 4;
   if (ierrf == -1)  ierflg = 3;
   return;
//                                                         jump
L2600:
   step = fWord7[0];
   if (step <= 0) step = 2;
   rno = 0;
   izero = 0;
   for (i = 1; i <= fNpar; ++i) {
      mnrn15(rno, izero);
      rno      = rno*2 - 1;
      fX[i-1] += rno*step*fWerr[i-1];
   }
   mninex(fX);
   mnamin();
   mnrset(0);
   return;
//                                                         blank line
L3300:
   Printf(" BLANK COMMAND IGNORED.");
   ierflg = 1;
   return;
//                  obsolete commands
//                                                         covariance
L3400:
   Printf(" THE *COVARIANCE* COMMAND IS OSBSOLETE. THE COVARIANCE MATRIX IS NOW SAVED IN A DIFFERENT FORMAT WITH THE *SAVE* COMMAND AND READ IN WITH:*SET COVARIANCE*");
   ierflg = 3;
   return;
//                                                           printout
L3500:
   cneway = "SET PRInt ";
   goto L3100;
//                                                           gradient
L3600:
   cneway = "SET GRAd  ";
   goto L3100;
//                                                           matout
L3700:
   cneway = "SHOW COVar";
   goto L3100;
//                                                         error def
L3800:
   cneway = "SET ERRdef";
   goto L3100;
//                                                           limits
L3900:
   cneway = "SET LIMits";
   goto L3100;
//                                                           punch
L4000:
   cneway = "SAVE      ";
//                                       come from obsolete commands
L3100:
   Printf(" OBSOLETE COMMAND:%s   PLEASE USE:%s",(const char*)fCword
                                                 ,(const char*)cneway);
   fCword = cneway;
   if (fCword == "SAVE      ") goto L1500;
   goto L700;
//
}


