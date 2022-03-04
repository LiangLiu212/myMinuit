# Hidden Answer Minuit

## Introduction
A [Blind analysis](https://www.slac.stanford.edu/econf/C030908/papers/TUIT001.pdf) is a measurement which is performed without looking at the answer. Blind analyses are the optimal way to reduce or eliminate experimenter’s bias, the unintended biasing of a result in a particular direction. This package is an implementation of the hidden answer technique by modifying the TMinuit according to [Root user guide](https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#adding-a-class-with-a-shared-library)

## Member function
* ```blindParameter(bool)``` default value is true. If center = true, all parameter will be blinded, else, all parameters will be unblind.
* ```blindParameter(const int n)``` blind a specific parameter with index n.
* ```unblindParameter(const int n)``` unblind a specific parameter with index n.


## Usage
* Build a shared library ```libmyMinuit.so``` by using ```make```
* Include the header file 	```myMinuit.h``` and link to the shared library ```libmyMinuit.so```
* Call ```setRandomSeed(const int)```

## Example 
```Ifit.C``` is a example to show how to use ```myMinuit```
