#include <RxODE_model_shared.h>
#define __MAX_PROD__ 0
#define _CMT CMT
extern void  cortisol_cortisolModel_ode_solver_solvedata (rx_solve *solve){
  _solveData = solve;
}
extern rx_solve *cortisol_cortisolModel_ode_solver_get_solvedata(){
  return _solveData;
}
SEXP cortisol_cortisolModel_model_vars();
double _cortisol_cortisolModel__t[14];
extern double* cortisol_cortisolModel_theta(double *theta){
  _cortisol_cortisolModel__t[0] = theta[0]; _cortisol_cortisolModel__t[1] = theta[1]; _cortisol_cortisolModel__t[2] = theta[2]; _cortisol_cortisolModel__t[3] = 66500.0000000000000000; _cortisol_cortisolModel__t[4] = 55000.0000000000000000; _cortisol_cortisolModel__t[5] = 362.4599999999999795; _cortisol_cortisolModel__t[6] = theta[3]; _cortisol_cortisolModel__t[7] = theta[4]; _cortisol_cortisolModel__t[8] = theta[5]; _cortisol_cortisolModel__t[9] = theta[6]; _cortisol_cortisolModel__t[10] = theta[7]; _cortisol_cortisolModel__t[11] = theta[8]; _cortisol_cortisolModel__t[12] = theta[9]; _cortisol_cortisolModel__t[13] = theta[10];
  return _cortisol_cortisolModel__t;
}


// prj-specific differential eqns
void cortisol_cortisolModel_dydt(int *_neq, double t, double *__zzStateVar__, double *__DDtStateVar__)
{
  int _cSub = _neq[1];
  double   Age,
  P01_Age,
  Bw,
  P01_Bw,
  C01_Cu,
  C01_A,
  C01_V,
  MW_ALB,
  MW_CBG,
  MW_COR,
  F,
  TA,
  C01_ALB,
  TC,
  C01_CBG,
  TCI,
  C01_RC,
  TCE,
  KA,
  C01_Kca,
  KCI,
  C01_Kci,
  KCE,
  C01_Kce,
  TF,
  C01_fu,
  C01_C,
  PO_R,
  PO_k,
  PO_A,
  ME_k,
  ME_CL,
  ME_R,
  fu_Var,
  AUCU_AUC,
  AUC_AUC;

  (void)t;
  (void)Age;
  (void)P01_Age;
  (void)Bw;
  (void)P01_Bw;
  (void)C01_Cu;
  (void)C01_A;
  (void)C01_V;
  (void)MW_ALB;
  (void)MW_CBG;
  (void)MW_COR;
  (void)F;
  (void)TA;
  (void)C01_ALB;
  (void)TC;
  (void)C01_CBG;
  (void)TCI;
  (void)C01_RC;
  (void)TCE;
  (void)KA;
  (void)C01_Kca;
  (void)KCI;
  (void)C01_Kci;
  (void)KCE;
  (void)C01_Kce;
  (void)TF;
  (void)C01_fu;
  (void)C01_C;
  (void)PO_R;
  (void)PO_k;
  (void)PO_A;
  (void)ME_k;
  (void)ME_CL;
  (void)ME_R;
  (void)fu_Var;
  (void)AUCU_AUC;
  (void)AUC_AUC;

  _update_par_ptr(t, _cSub, _solveData, _idx);
  P01_Age = _PP[0];
  P01_Bw = _PP[1];
  C01_V = _PP[2];
  MW_ALB = _PP[3];
  MW_CBG = _PP[4];
  MW_COR = _PP[5];
  C01_ALB = _PP[6];
  C01_CBG = _PP[7];
  C01_RC = _PP[8];
  C01_Kca = _PP[9];
  C01_Kci = _PP[10];
  C01_Kce = _PP[11];
  PO_k = _PP[12];
  ME_CL = _PP[13];

  C01_A = __zzStateVar__[0]*((double)(_ON[0]));
  PO_A = __zzStateVar__[1]*((double)(_ON[1]));
  AUCU_AUC = __zzStateVar__[2]*((double)(_ON[2]));
  AUC_AUC = __zzStateVar__[3]*((double)(_ON[3]));

  Age=P01_Age+t/safe_zero(365)/safe_zero(24);
  Bw=P01_Bw;
  C01_Cu=C01_A/safe_zero(C01_V);
  F=C01_Cu/safe_zero(MW_COR)*1e+06;
  TA=C01_ALB/safe_zero(MW_ALB)*1e+06;
  TC=C01_CBG/safe_zero(MW_CBG)*1e+06;
  TCI=(1-C01_RC)*TC;
  TCE=C01_RC*TC;
  KA=C01_Kca/safe_zero(MW_ALB)*1e+06;
  KCI=C01_Kci/safe_zero(MW_CBG)*1e+06;
  KCE=C01_Kce/safe_zero(MW_CBG)*1e+06;
  TF=F*(1+TA/safe_zero((KA+F))+TCI/safe_zero((KCI+F))+TCE/safe_zero((KCE+F)));
  C01_fu=F/safe_zero(TF);
  C01_C=C01_Cu/safe_zero(C01_fu);
  PO_R=PO_k*PO_A;
  ME_k=ME_CL/safe_zero(C01_V);
  ME_R=ME_k*C01_A;
  fu_Var=C01_fu;
  __DDtStateVar__[0] = ((double)(_ON[0]))*(_IR[0] + (+PO_R)+(-ME_R));
  __DDtStateVar__[1] = ((double)(_ON[1]))*(_IR[1] + (-PO_R));
  __DDtStateVar__[2] = ((double)(_ON[2]))*(_IR[2] + C01_Cu);
  __DDtStateVar__[3] = ((double)(_ON[3]))*(_IR[3] + C01_C);
  (&_solveData->subjects[_cSub])->dadt_counter[0]++;
}

// Jacobian derived vars
void cortisol_cortisolModel_calc_jac(int *_neq, double t, double *__zzStateVar__, double *__PDStateVar__, unsigned int __NROWPD__) {
  int _cSub=_neq[1];
  (&_solveData->subjects[_cSub])->jac_counter[0]++;
}
// Functional based initial conditions.
void cortisol_cortisolModel_inis(int _cSub, double *__zzStateVar__){
}
// prj-specific derived vars
void cortisol_cortisolModel_calc_lhs(int _cSub, double t, double *__zzStateVar__, double *_lhs) {
  double   __DDtStateVar_0__,
  __DDtStateVar_1__,
  __DDtStateVar_2__,
  __DDtStateVar_3__,
  Age,
  P01_Age,
  Bw,
  P01_Bw,
  C01_Cu,
  C01_A,
  C01_V,
  MW_ALB,
  MW_CBG,
  MW_COR,
  F,
  TA,
  C01_ALB,
  TC,
  C01_CBG,
  TCI,
  C01_RC,
  TCE,
  KA,
  C01_Kca,
  KCI,
  C01_Kci,
  KCE,
  C01_Kce,
  TF,
  C01_fu,
  C01_C,
  PO_R,
  PO_k,
  PO_A,
  ME_k,
  ME_CL,
  ME_R,
  fu_Var,
  AUCU_AUC,
  AUC_AUC;

  (void)t;
  (void)__DDtStateVar_0__;
  (void)__DDtStateVar_1__;
  (void)__DDtStateVar_2__;
  (void)__DDtStateVar_3__;
  (void)Age;
  (void)P01_Age;
  (void)Bw;
  (void)P01_Bw;
  (void)C01_Cu;
  (void)C01_A;
  (void)C01_V;
  (void)MW_ALB;
  (void)MW_CBG;
  (void)MW_COR;
  (void)F;
  (void)TA;
  (void)C01_ALB;
  (void)TC;
  (void)C01_CBG;
  (void)TCI;
  (void)C01_RC;
  (void)TCE;
  (void)KA;
  (void)C01_Kca;
  (void)KCI;
  (void)C01_Kci;
  (void)KCE;
  (void)C01_Kce;
  (void)TF;
  (void)C01_fu;
  (void)C01_C;
  (void)PO_R;
  (void)PO_k;
  (void)PO_A;
  (void)ME_k;
  (void)ME_CL;
  (void)ME_R;
  (void)fu_Var;
  (void)AUCU_AUC;
  (void)AUC_AUC;

  _update_par_ptr(t, _cSub, _solveData, _idx);
  P01_Age = _PP[0];
  P01_Bw = _PP[1];
  C01_V = _PP[2];
  MW_ALB = _PP[3];
  MW_CBG = _PP[4];
  MW_COR = _PP[5];
  C01_ALB = _PP[6];
  C01_CBG = _PP[7];
  C01_RC = _PP[8];
  C01_Kca = _PP[9];
  C01_Kci = _PP[10];
  C01_Kce = _PP[11];
  PO_k = _PP[12];
  ME_CL = _PP[13];

  C01_A = __zzStateVar__[0]*((double)(_ON[0]));
  PO_A = __zzStateVar__[1]*((double)(_ON[1]));
  AUCU_AUC = __zzStateVar__[2]*((double)(_ON[2]));
  AUC_AUC = __zzStateVar__[3]*((double)(_ON[3]));

  Age=P01_Age+t/safe_zero(365)/safe_zero(24);
  Bw=P01_Bw;
  C01_Cu=C01_A/safe_zero(C01_V);
  F=C01_Cu/safe_zero(MW_COR)*1e+06;
  TA=C01_ALB/safe_zero(MW_ALB)*1e+06;
  TC=C01_CBG/safe_zero(MW_CBG)*1e+06;
  TCI=(1-C01_RC)*TC;
  TCE=C01_RC*TC;
  KA=C01_Kca/safe_zero(MW_ALB)*1e+06;
  KCI=C01_Kci/safe_zero(MW_CBG)*1e+06;
  KCE=C01_Kce/safe_zero(MW_CBG)*1e+06;
  TF=F*(1+TA/safe_zero((KA+F))+TCI/safe_zero((KCI+F))+TCE/safe_zero((KCE+F)));
  C01_fu=F/safe_zero(TF);
  C01_C=C01_Cu/safe_zero(C01_fu);
  PO_R=PO_k*PO_A;
  ME_k=ME_CL/safe_zero(C01_V);
  ME_R=ME_k*C01_A;
  fu_Var=C01_fu;
  __DDtStateVar_0__ = ((double)(_ON[0]))*(_IR[0] + (+PO_R)+(-ME_R));
  __DDtStateVar_1__ = ((double)(_ON[1]))*(_IR[1] + (-PO_R));
  __DDtStateVar_2__ = ((double)(_ON[2]))*(_IR[2] + C01_Cu);
  __DDtStateVar_3__ = ((double)(_ON[3]))*(_IR[3] + C01_C);

  _lhs[0]=Age;
  _lhs[1]=Bw;
  _lhs[2]=C01_Cu;
  _lhs[3]=F;
  _lhs[4]=TA;
  _lhs[5]=TC;
  _lhs[6]=TCI;
  _lhs[7]=TCE;
  _lhs[8]=KA;
  _lhs[9]=KCI;
  _lhs[10]=KCE;
  _lhs[11]=TF;
  _lhs[12]=C01_fu;
  _lhs[13]=C01_C;
  _lhs[14]=PO_R;
  _lhs[15]=ME_k;
  _lhs[16]=ME_R;
  _lhs[17]=fu_Var;
}
// Functional based bioavailability
double cortisol_cortisolModel_F(int _cSub,  int _cmt, double _amt, double t){
 return _amt;
}
// Functional based absorption lag
double cortisol_cortisolModel_Lag(int _cSub,  int _cmt, double t){
 return t;
  double   Age,
  P01_Age,
  Bw,
  P01_Bw,
  C01_Cu,
  C01_A,
  C01_V,
  MW_ALB,
  MW_CBG,
  MW_COR,
  F,
  TA,
  C01_ALB,
  TC,
  C01_CBG,
  TCI,
  C01_RC,
  TCE,
  KA,
  C01_Kca,
  KCI,
  C01_Kci,
  KCE,
  C01_Kce,
  TF,
  C01_fu,
  C01_C,
  PO_R,
  PO_k,
  PO_A,
  ME_k,
  ME_CL,
  ME_R,
  fu_Var,
  AUCU_AUC,
  AUC_AUC;

  (void)t;
  (void)Age;
  (void)P01_Age;
  (void)Bw;
  (void)P01_Bw;
  (void)C01_Cu;
  (void)C01_A;
  (void)C01_V;
  (void)MW_ALB;
  (void)MW_CBG;
  (void)MW_COR;
  (void)F;
  (void)TA;
  (void)C01_ALB;
  (void)TC;
  (void)C01_CBG;
  (void)TCI;
  (void)C01_RC;
  (void)TCE;
  (void)KA;
  (void)C01_Kca;
  (void)KCI;
  (void)C01_Kci;
  (void)KCE;
  (void)C01_Kce;
  (void)TF;
  (void)C01_fu;
  (void)C01_C;
  (void)PO_R;
  (void)PO_k;
  (void)PO_A;
  (void)ME_k;
  (void)ME_CL;
  (void)ME_R;
  (void)fu_Var;
  (void)AUCU_AUC;
  (void)AUC_AUC;

  _update_par_ptr(NA_REAL, _cSub, _solveData, _idx);
  P01_Age = _PP[0];
  P01_Bw = _PP[1];
  C01_V = _PP[2];
  MW_ALB = _PP[3];
  MW_CBG = _PP[4];
  MW_COR = _PP[5];
  C01_ALB = _PP[6];
  C01_CBG = _PP[7];
  C01_RC = _PP[8];
  C01_Kca = _PP[9];
  C01_Kci = _PP[10];
  C01_Kce = _PP[11];
  PO_k = _PP[12];
  ME_CL = _PP[13];

}
// Modeled zero-order rate
double cortisol_cortisolModel_Rate(int _cSub,  int _cmt, double _amt, double t){
 return 0.0;
  double   Age,
  P01_Age,
  Bw,
  P01_Bw,
  C01_Cu,
  C01_A,
  C01_V,
  MW_ALB,
  MW_CBG,
  MW_COR,
  F,
  TA,
  C01_ALB,
  TC,
  C01_CBG,
  TCI,
  C01_RC,
  TCE,
  KA,
  C01_Kca,
  KCI,
  C01_Kci,
  KCE,
  C01_Kce,
  TF,
  C01_fu,
  C01_C,
  PO_R,
  PO_k,
  PO_A,
  ME_k,
  ME_CL,
  ME_R,
  fu_Var,
  AUCU_AUC,
  AUC_AUC;

  (void)t;
  (void)Age;
  (void)P01_Age;
  (void)Bw;
  (void)P01_Bw;
  (void)C01_Cu;
  (void)C01_A;
  (void)C01_V;
  (void)MW_ALB;
  (void)MW_CBG;
  (void)MW_COR;
  (void)F;
  (void)TA;
  (void)C01_ALB;
  (void)TC;
  (void)C01_CBG;
  (void)TCI;
  (void)C01_RC;
  (void)TCE;
  (void)KA;
  (void)C01_Kca;
  (void)KCI;
  (void)C01_Kci;
  (void)KCE;
  (void)C01_Kce;
  (void)TF;
  (void)C01_fu;
  (void)C01_C;
  (void)PO_R;
  (void)PO_k;
  (void)PO_A;
  (void)ME_k;
  (void)ME_CL;
  (void)ME_R;
  (void)fu_Var;
  (void)AUCU_AUC;
  (void)AUC_AUC;

  _update_par_ptr(NA_REAL, _cSub, _solveData, _idx);
  P01_Age = _PP[0];
  P01_Bw = _PP[1];
  C01_V = _PP[2];
  MW_ALB = _PP[3];
  MW_CBG = _PP[4];
  MW_COR = _PP[5];
  C01_ALB = _PP[6];
  C01_CBG = _PP[7];
  C01_RC = _PP[8];
  C01_Kca = _PP[9];
  C01_Kci = _PP[10];
  C01_Kce = _PP[11];
  PO_k = _PP[12];
  ME_CL = _PP[13];

}
// Modeled zero-order duration
double cortisol_cortisolModel_Dur(int _cSub,  int _cmt, double _amt, double t){
 return 0.0;
}
// Model Times
void cortisol_cortisolModel_mtime(int _cSub, double *_mtime){
}
extern SEXP cortisol_cortisolModel_model_vars(){
  int pro=0;
  SEXP _mv = PROTECT(_rxGetModelLib("cortisol_cortisolModel_model_vars"));pro++;
  if (!_rxIsCurrentC(_mv)){
    SEXP lst      = PROTECT(allocVector(VECSXP, 20));pro++;
    SEXP names    = PROTECT(allocVector(STRSXP, 20));pro++;
    SEXP sNeedSort = PROTECT(allocVector(INTSXP,1));pro++;
    int *iNeedSort  = INTEGER(sNeedSort);
    iNeedSort[0] = 0;
    SEXP sMtime = PROTECT(allocVector(INTSXP,1));pro++;
    int *iMtime  = INTEGER(sMtime);
    iMtime[0] = 0;
    SEXP sExtraCmt = PROTECT(allocVector(INTSXP,1));pro++;
    int *iExtraCmt  = INTEGER(sExtraCmt);
    iExtraCmt[0] = 0;
    SEXP params   = PROTECT(allocVector(STRSXP, 14));pro++;
    SEXP lhs      = PROTECT(allocVector(STRSXP, 18));pro++;
    SEXP state    = PROTECT(allocVector(STRSXP, 4));pro++;
  SEXP extraState = PROTECT(allocVector(STRSXP, 0));pro++;
    SEXP stateRmS = PROTECT(allocVector(INTSXP, 4));pro++;
    SEXP timeInt = PROTECT(allocVector(INTSXP, 1));pro++;
    INTEGER(timeInt)[0] = 1602544676;
    SEXP sens     = PROTECT(allocVector(STRSXP, 0));pro++;
    SEXP normState= PROTECT(allocVector(STRSXP, 4));pro++;
    SEXP fn_ini   = PROTECT(allocVector(STRSXP, 0));pro++;
    SEXP dfdy     = PROTECT(allocVector(STRSXP, 0));pro++;
    SEXP tran     = PROTECT(allocVector(STRSXP, 20));pro++;
    SEXP trann    = PROTECT(allocVector(STRSXP, 20));pro++;
    SEXP mmd5     = PROTECT(allocVector(STRSXP, 2));pro++;
    SEXP mmd5n    = PROTECT(allocVector(STRSXP, 2));pro++;
    SEXP model    = PROTECT(allocVector(STRSXP, 1));pro++;
    SEXP modeln   = PROTECT(allocVector(STRSXP, 1));pro++;
    SEXP version    = PROTECT(allocVector(STRSXP, 3));pro++;
    SEXP versionn   = PROTECT(allocVector(STRSXP, 3));pro++;
    SET_STRING_ELT(version,0,mkChar("0.8.1-0"));
    SET_STRING_ELT(version,1,mkChar("https://github.com/nlmixrdevelopment/RxODE"));
    SET_STRING_ELT(version,2,mkChar("2ef740cbdf83ec58b612d7c6d08130e4"));
    SET_STRING_ELT(versionn,0,mkChar("version"));
    SET_STRING_ELT(versionn,1,mkChar("repo"));
    SET_STRING_ELT(versionn,2,mkChar("md5"));
  SET_STRING_ELT(lhs,0,mkChar("Age"));
    SET_STRING_ELT(params,0,mkChar("P01_Age"));
  SET_STRING_ELT(lhs,1,mkChar("Bw"));
    SET_STRING_ELT(params,1,mkChar("P01_Bw"));
  SET_STRING_ELT(lhs,2,mkChar("C01_Cu"));
    SET_STRING_ELT(params,2,mkChar("C01_V"));
    SET_STRING_ELT(params,3,mkChar("MW_ALB"));
    SET_STRING_ELT(params,4,mkChar("MW_CBG"));
    SET_STRING_ELT(params,5,mkChar("MW_COR"));
  SET_STRING_ELT(lhs,3,mkChar("F"));
  SET_STRING_ELT(lhs,4,mkChar("TA"));
    SET_STRING_ELT(params,6,mkChar("C01_ALB"));
  SET_STRING_ELT(lhs,5,mkChar("TC"));
    SET_STRING_ELT(params,7,mkChar("C01_CBG"));
  SET_STRING_ELT(lhs,6,mkChar("TCI"));
    SET_STRING_ELT(params,8,mkChar("C01_RC"));
  SET_STRING_ELT(lhs,7,mkChar("TCE"));
  SET_STRING_ELT(lhs,8,mkChar("KA"));
    SET_STRING_ELT(params,9,mkChar("C01_Kca"));
  SET_STRING_ELT(lhs,9,mkChar("KCI"));
    SET_STRING_ELT(params,10,mkChar("C01_Kci"));
  SET_STRING_ELT(lhs,10,mkChar("KCE"));
    SET_STRING_ELT(params,11,mkChar("C01_Kce"));
  SET_STRING_ELT(lhs,11,mkChar("TF"));
  SET_STRING_ELT(lhs,12,mkChar("C01_fu"));
  SET_STRING_ELT(lhs,13,mkChar("C01_C"));
  SET_STRING_ELT(lhs,14,mkChar("PO_R"));
    SET_STRING_ELT(params,12,mkChar("PO_k"));
  SET_STRING_ELT(lhs,15,mkChar("ME_k"));
    SET_STRING_ELT(params,13,mkChar("ME_CL"));
  SET_STRING_ELT(lhs,16,mkChar("ME_R"));
  SET_STRING_ELT(lhs,17,mkChar("fu_Var"));
    SET_STRING_ELT(state,0,mkChar("C01_A"));
    SET_STRING_ELT(normState,0,mkChar("C01_A"));
    _SR[0] = 0;
    SET_STRING_ELT(state,1,mkChar("PO_A"));
    SET_STRING_ELT(normState,1,mkChar("PO_A"));
    _SR[1] = 0;
    SET_STRING_ELT(state,2,mkChar("AUCU_AUC"));
    SET_STRING_ELT(normState,2,mkChar("AUCU_AUC"));
    _SR[2] = 0;
    SET_STRING_ELT(state,3,mkChar("AUC_AUC"));
    SET_STRING_ELT(normState,3,mkChar("AUC_AUC"));
    _SR[3] = 0;
    SET_STRING_ELT(modeln,0,mkChar("normModel"));
    SET_STRING_ELT(model,0,mkChar("Age=P01_Age+t/365/24;\nBw=P01_Bw;\nC01_Cu=C01_A/C01_V;\nMW_ALB=66500;\nMW_CBG=55000;\nMW_COR=362.46;\nF=C01_Cu/MW_COR*1e+06;\nTA=C01_ALB/MW_ALB*1e+06;\nTC=C01_CBG/MW_CBG*1e+06;\nTCI=(1-C01_RC)*TC;\nTCE=C01_RC*TC;\nKA=C01_Kca/MW_ALB*1e+06;\nKCI=C01_Kci/MW_CBG*1e+06;\nKCE=C01_Kce/MW_CBG*1e+06;\nTF=F*(1+TA/(KA+F)+TCI/(KCI+F)+TCE/(KCE+F));\nC01_fu=F/TF;\nC01_C=C01_Cu/C01_fu;\nPO_R=PO_k*PO_A;\nME_k=ME_CL/C01_V;\nME_R=ME_k*C01_A;\nfu_Var=C01_fu;\nd/dt(C01_A)=(+PO_R)+(-ME_R);\nd/dt(PO_A)=(-PO_R);\nd/dt(AUCU_AUC)=C01_Cu;\nd/dt(AUC_AUC)=C01_C;\n"));
    SEXP ini    = PROTECT(allocVector(REALSXP,3));pro++;
    SEXP inin   = PROTECT(allocVector(STRSXP, 3));pro++;
    SET_STRING_ELT(inin,0,mkChar("MW_ALB"));
    REAL(ini)[0] = 66500.0000000000000000;
    SET_STRING_ELT(inin,1,mkChar("MW_CBG"));
    REAL(ini)[1] = 55000.0000000000000000;
    SET_STRING_ELT(inin,2,mkChar("MW_COR"));
    REAL(ini)[2] = 362.4599999999999795;
    SET_STRING_ELT(names,0,mkChar("params"));
    SET_VECTOR_ELT(lst,  0,params);
    SET_STRING_ELT(names,1,mkChar("lhs"));
    SET_VECTOR_ELT(lst,  1,lhs);
    SET_STRING_ELT(names,2,mkChar("state"));
    SET_VECTOR_ELT(lst,  2,state);
    SET_STRING_ELT(names,3,mkChar("trans"));
    SET_VECTOR_ELT(lst,  3,tran);
    SET_STRING_ELT(names,4,mkChar("model"));
    SET_VECTOR_ELT(lst,  4,model);
    SET_STRING_ELT(names,5,mkChar("ini"));
    SET_VECTOR_ELT(lst,  5,ini);
    SET_STRING_ELT(names,6,mkChar("podo"));
    SET_VECTOR_ELT(lst,   6,ScalarLogical(0));
    SET_STRING_ELT(names,7,mkChar("dfdy"));
    SET_VECTOR_ELT(lst,  7,dfdy);
    SET_STRING_ELT(names,8,mkChar("sens"));
    SET_VECTOR_ELT(lst,  8,sens);
    SET_STRING_ELT(names,9,mkChar("fn.ini"));
    SET_VECTOR_ELT(lst,  9,fn_ini);
    SET_STRING_ELT(names,10,mkChar("state.ignore"));
    SET_VECTOR_ELT(lst,  10,stateRmS);
    SET_STRING_ELT(names,11,mkChar("version"));
    SET_VECTOR_ELT(lst,  11,version);
    SET_STRING_ELT(names,12,mkChar("normal.state"));
    SET_VECTOR_ELT(lst,  12,normState);
    SET_STRING_ELT(names,13,mkChar("needSort"));
    SET_VECTOR_ELT(lst,  13,sNeedSort);
    SET_STRING_ELT(names,14,mkChar("nMtime"));
    SET_VECTOR_ELT(lst,  14,sMtime);
    SET_STRING_ELT(names,15,mkChar("extraCmt"));
    SET_VECTOR_ELT(lst,  15,sExtraCmt);
    SET_STRING_ELT(names, 16, mkChar("stateExtra"));
    SET_VECTOR_ELT(lst,  16, extraState);
    SET_STRING_ELT(names, 17, mkChar("dvid"));
    SEXP sDvid = PROTECT(allocVector(INTSXP,0));pro++;
    SET_VECTOR_ELT(lst, 17, sDvid);
    SET_STRING_ELT(names,18,mkChar("timeId"));
    SET_VECTOR_ELT(lst,  18,timeInt);
    SET_STRING_ELT(names,19,mkChar("md5"));    SET_VECTOR_ELT(lst,  19,mmd5);    SET_STRING_ELT(mmd5n,0,mkChar("file_md5"));
    SET_STRING_ELT(mmd5,0,mkChar("920146427eabe01175591b21022188b7"));
    SET_STRING_ELT(mmd5n,1,mkChar("parsed_md5"));
    SET_STRING_ELT(mmd5,1,mkChar("920146427eabe01175591b21022188b7"));
    SET_STRING_ELT(trann,0,mkChar("lib.name"));
    SET_STRING_ELT(tran, 0,mkChar("cortisol"));
    SET_STRING_ELT(trann,1,mkChar("jac"));
    SET_STRING_ELT(tran,1,mkChar("fullint"));
    SET_STRING_ELT(trann,2,mkChar("prefix"));
    SET_STRING_ELT(tran, 2,mkChar("cortisol_cortisolModel_"));
    SET_STRING_ELT(trann,3,mkChar("dydt"));
    SET_STRING_ELT(tran, 3,mkChar("cortisol_cortisolModel_dydt"));
    SET_STRING_ELT(trann,4,mkChar("calc_jac"));
    SET_STRING_ELT(tran, 4,mkChar("cortisol_cortisolModel_calc_jac"));
    SET_STRING_ELT(trann,5,mkChar("calc_lhs"));
    SET_STRING_ELT(tran, 5,mkChar("cortisol_cortisolModel_calc_lhs"));
    SET_STRING_ELT(trann,6,mkChar("model_vars"));
    SET_STRING_ELT(tran, 6,mkChar("cortisol_cortisolModel_model_vars"));
    SET_STRING_ELT(trann,7,mkChar("theta"));
    SET_STRING_ELT(tran, 7,mkChar("cortisol_cortisolModel_theta"));
    SET_STRING_ELT(trann,8,mkChar("inis"));
    SET_STRING_ELT(tran, 8,mkChar("cortisol_cortisolModel_inis"));
    SET_STRING_ELT(trann,  9,mkChar("dydt_lsoda"));
    SET_STRING_ELT(tran,   9,mkChar("cortisol_cortisolModel_dydt_lsoda"));
    SET_STRING_ELT(trann,10,mkChar("calc_jac_lsoda"));
    SET_STRING_ELT(tran, 10,mkChar("cortisol_cortisolModel_calc_jac_lsoda"));
    SET_STRING_ELT(trann,11,mkChar("ode_solver_solvedata"));
    SET_STRING_ELT(tran, 11,mkChar("cortisol_cortisolModel_ode_solver_solvedata"));
    SET_STRING_ELT(trann,12,mkChar("ode_solver_get_solvedata"));
    SET_STRING_ELT(tran, 12,mkChar("cortisol_cortisolModel_ode_solver_get_solvedata"));
    SET_STRING_ELT(trann,13,mkChar("dydt_liblsoda"));
    SET_STRING_ELT(tran, 13,mkChar("cortisol_cortisolModel_dydt_liblsoda"));
    SET_STRING_ELT(trann,14,mkChar("F"));
    SET_STRING_ELT(tran, 14,mkChar("cortisol_cortisolModel_F"));
    SET_STRING_ELT(trann,15,mkChar("Lag"));
    SET_STRING_ELT(tran, 15,mkChar("cortisol_cortisolModel_Lag"));
    SET_STRING_ELT(trann,16,mkChar("Rate"));
    SET_STRING_ELT(tran, 16,mkChar("cortisol_cortisolModel_Rate"));
    SET_STRING_ELT(trann,17,mkChar("Dur"));
    SET_STRING_ELT(tran, 17,mkChar("cortisol_cortisolModel_Dur"));
    SET_STRING_ELT(trann,18,mkChar("mtime"));
    SET_STRING_ELT(tran, 18,mkChar("cortisol_cortisolModel_mtime"));
    SET_STRING_ELT(trann,19,mkChar("assignFuns"));
    SET_STRING_ELT(tran, 19,mkChar("cortisol_cortisolModel_assignFuns"));
    setAttrib(tran, R_NamesSymbol, trann);
    setAttrib(mmd5, R_NamesSymbol, mmd5n);
    setAttrib(model, R_NamesSymbol, modeln);
    setAttrib(ini, R_NamesSymbol, inin);
    setAttrib(version, R_NamesSymbol, versionn);
    setAttrib(lst, R_NamesSymbol, names);
    SEXP cls = PROTECT(allocVector(STRSXP, 1));pro++;
    SET_STRING_ELT(cls, 0, mkChar("rxModelVars"));
    classgets(lst, cls);
    _assign_ptr(lst);
    UNPROTECT(pro);
    return lst;
  } else {
    UNPROTECT(pro);
    return _mv;
  }
}
extern void cortisol_cortisolModel_dydt_lsoda(int *neq, double *t, double *A, double *DADT)
{
  cortisol_cortisolModel_dydt(neq, *t, A, DADT);
}
extern int cortisol_cortisolModel_dydt_liblsoda(double t, double *y, double *ydot, void *data)
{
  int *neq = (int*)(data);
  cortisol_cortisolModel_dydt(neq, t, y, ydot);
  return(0);
}
extern void cortisol_cortisolModel_calc_jac_lsoda(int *neq, double *t, double *A,int *ml, int *mu, double *JAC, int *nrowpd){
  // Update all covariate parameters
  cortisol_cortisolModel_calc_jac(neq, *t, A, JAC, *nrowpd);
}

//Create function to call from R's main thread that assigns the required functions. Sometimes they don't get assigned.
extern void cortisol_cortisolModel_assignFuns(){
  _assignFuns();
}

//Initialize the dll to match RxODE's calls
void R_init0_cortl_cortlModel(){
  // Get C callables on load; Otherwise it isn't thread safe
  _assignFuns();
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_assignFuns", (DL_FUNC) cortisol_cortisolModel_assignFuns);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_theta", (DL_FUNC) cortisol_cortisolModel_theta);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_inis",(DL_FUNC) cortisol_cortisolModel_inis);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_dydt",(DL_FUNC) cortisol_cortisolModel_dydt);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_calc_lhs",(DL_FUNC) cortisol_cortisolModel_calc_lhs);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_calc_jac",(DL_FUNC) cortisol_cortisolModel_calc_jac);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_dydt_lsoda", (DL_FUNC) cortisol_cortisolModel_dydt_lsoda);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_calc_jac_lsoda", (DL_FUNC) cortisol_cortisolModel_calc_jac_lsoda);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_ode_solver_solvedata", (DL_FUNC) cortisol_cortisolModel_ode_solver_solvedata);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_ode_solver_get_solvedata", (DL_FUNC) cortisol_cortisolModel_ode_solver_get_solvedata);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_F", (DL_FUNC) cortisol_cortisolModel_F);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_Lag", (DL_FUNC) cortisol_cortisolModel_Lag);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_Rate", (DL_FUNC) cortisol_cortisolModel_Rate);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_Dur", (DL_FUNC) cortisol_cortisolModel_Dur);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_mtime", (DL_FUNC) cortisol_cortisolModel_mtime);
  R_RegisterCCallable("cortisol","cortisol_cortisolModel_dydt_liblsoda", (DL_FUNC) cortisol_cortisolModel_dydt_liblsoda);
}
//Initialize the dll to match RxODE's calls
void R_init_cortl_cortlModel(DllInfo *info){
  // Get C callables on load; Otherwise it isn't thread safe
  R_init0_cortl_cortlModel();
  static const R_CallMethodDef callMethods[]  = {
    {"cortisol_cortisolModel_model_vars", (DL_FUNC) &cortisol_cortisolModel_model_vars, 0},
    {NULL, NULL, 0}
  };

  R_registerRoutines(info, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(info,FALSE);
}

void R_unload_cortl_cortlModel (DllInfo *info){
  // Free resources required for single subject solve.
  SEXP _mv = PROTECT(_rxGetModelLib("cortisol_cortisolModel_model_vars"));
  if (!isNull(_mv)){
    _rxRmModelLib("cortisol_cortisolModel_model_vars");
  }
  UNPROTECT(1);
}
