#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>
#include <RxODE.h>
#include <RxODE_model_shared.h>
#define compiledModelCall \
{"cortisol_cortisolModel_model_vars", (DL_FUNC) &cortisol_cortisolModel_model_vars, 0},
SEXP cortisol_cortisolModel_model_vars();
void R_init0_cortisol_cortisolModel();
void R_init0_cortisol_RxODE_models(){
  R_init0_cortisol_cortisolModel();
}
