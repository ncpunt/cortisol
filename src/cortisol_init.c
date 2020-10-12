#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>
#include <RxODE.h>
#include <RxODE_model.h>
#include "cortisol_compiled.h"
void R_init_cortisol(DllInfo *info){
  R_init0_cortisol_RxODE_models();
  static const R_CallMethodDef callMethods[]  = {
  compiledModelCall
  {NULL, NULL, 0}
  };
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(info,FALSE);
}
void R_unload_cortisol_cortisolModel(DllInfo *info);
void R_unload_cortisol(DllInfo *info){
  R_unload_cortisol_cortisolModel(info);
}
