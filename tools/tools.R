#Source this file once in your workspace

#Build and install the OpenCPU app as an R package
pbuild<-function(){
  library(devtools)
  build()
  install()
}

#Document current R source (roxyge)
pdoc<-function(){
  library(devtools)
  document()
}

#Run a single server instance of the OpenCPU app
prun<-function(){
  library(opencpu)
  ocpu_start_app("cortisol", no_cache = TRUE)
}