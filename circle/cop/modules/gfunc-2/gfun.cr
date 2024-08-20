
# input x0 x1 y0 y1
# output z0 z1

leq = x1 | ! ( x0 + x1 )

z0 = y0 * !leq
z1 = y1 * !leq

