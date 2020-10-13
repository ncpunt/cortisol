OpenCPU APP: cortisol
====================
  
The purpose of this OpenCPU app is to demonstrate how to run a hydrocortisone RxODE model as a web service using OpenCPU.

Cloud Demo
----------

Try the application online at ... NA

Use locally
-----------

To run the app in your local R session:

    #install app
    library(devtools)
    install_github("cortisol", "medimatics")
    
    #load in opencpu
    library(opencpu)
    opencpu$browse("/library/cortisol/www")

