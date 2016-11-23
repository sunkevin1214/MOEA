compile:
mex wfg.cpp ExampleProblems.cpp ExampleShapes.cpp ExampleTransitions.cpp FrameworkFunctions.cpp Misc.cpp ShapeFunctions.cpp TransFunctions.cpp


usage:
4 parameters
the first: the index of the wfg problem, such as 1, 2,...9
the second: the decision variable
the third: the parameter k in wfg. commonly multiple of M-1 where M is the number of the objective of the problem
the fouth: the number of the objective of the problem.



wfg.mexa64 and wfg.mexw64 are the compiled file for 64bits linux and windows, respectively.