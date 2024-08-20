# Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
import math
a = 865739010324014291123883766035082602
k = 60
y_loc  = (a >> k)
y_loc2 = (a//2**k)
print (" >> barretk  :",   y_loc)
print (" /2**barretk :",   y_loc2)
print ("DIFF   :",   y_loc2 - y_loc)

q=1329227995784783648948129721038553089
q=1532495540865518635130821056977027158796330141975560193
z=math.log2(q)
print ("log2 :", z)
