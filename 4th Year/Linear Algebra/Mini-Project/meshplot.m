%function meshplot(fem,nodes)
%
%USAGE: meshplot(fem) or meshplot(fem,nodes).
%
%DESCRIPTION: Plot mesh using the mesh description in the structure fem. 
%
%INPUT: fem: structure containing mesh information.
%       nodes: set of labels (positive integers) for nodes in the subdivsion of the domain. 
%       If a set of nodes is specified as input, then they will be highlighted in
%       the plot. If no nodes are specified, the boundary nodes will be highlighted. 