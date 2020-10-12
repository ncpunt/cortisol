#' @title Cortisol
#'
#' @description Hydrocortisone Simulation API
#'
#' @examples
#' The function argument (args) must be a JSON object with the following structure:
#'
#' {
#'   "args":
#'    {
#'      "dose": 10,    // Dose (mg)
#'      "tint": 6,     // Interval (hurs)
#'      "ndos": 3,     // Number (-)
#'      "nseq": 1      // Period (days)
#'    }
#' }
#'
#' The function result is returned in the response body as JSON.
#'
#' {
#'   "args":
#'    {
#'      "dose": 10,    // Dose (mg)
#'      "tint": 6,     // Interval (hurs)
#'      "ndos": 3,     // Number (-)
#'      "nseq": 1,     // Period (days)
#'      "sim" :
#'      [
#'        {
#'          "t" :0,    // Time (h)
#'          "C" :0,    // Total concentration (nM)
#'          "Cu":0,    // Free concentration (nM)
#'          "fu":0     // Fraction unbound (-)
#'        }
#'      ]
#'    }
#' }
#'
#' DPU URLs for local single user server
#'
#' Web API         : POST: http://localhost:5656/ocpu/library/cortisol/R/cortisol/json
#' Web APP         : GET : http://localhost:5656/ocpu/library/cortisol(/www)
#' Package Info    : GET : http://localhost:5656/ocpu/library/cortisol/info
#' R Objects       : GET : http://localhost:5656/ocpu/library/cortisol/R
#' R Data Objects  : GET : http://localhost:5656/ocpu/library/cortisol/data
#' R Help          : GET : http://localhost:5656/ocpu/library/cortisol/man/cortisol/html
#'
#'
#' @import jsonlite
#' @import RxODE
#' @export
#' @param args json object. Required.
#' @useDynLib cortisol, .registration=TRUE
#' @return json object with simulation data added.
cortisol <- function(args){

  # We do no need to explicitly load the R model objects because lazydata=true in DESCRIPTION

  # Get regimen parameters
  dose <- args$dose
  tint <- args$tint
  ndos <- args$ndos
  nseq <- args$nseq

  # Clear interval in case of a single dose
  if (ndos==1) tint=NA

  # Create the event table (destroys existing table)
  ev <- eventTable(amount.units='mg', time.units='hours')

  # Set output range
  ev$add.sampling(seq(0, 24 * nseq, by=0.1))

  # Add dosing events
  for (i in 1:nseq)
  {
    ev$add.dosing(dose=dose * 0.96, start.time=(i-1)*24, nbr.doses=ndos, dosing.interval=tint, dosing.to=which(vdif=="PO_A"))
  }

  # Execute simulation
  result = mod$solve(parm, ev, vini);

  # Pickup relevant output
  sim = result[,c("time", "C01_C", "C01_Cu", "C01_fu")]

  # Scale from mg/L to nM
  sim[,"C01_C"]  <- sim[,"C01_C"]  / 362.46 * 1E6
  sim[,"C01_Cu"] <- sim[,"C01_Cu"] / 362.46 * 1E6

  # Change the column names
  colnames(sim)<-c("t", "C", "Cu", "fu")

  # Store results in args object as a data frame
  args$sim = as.data.frame(sim);

  # Return as JSON
  toJSON(args)
}
