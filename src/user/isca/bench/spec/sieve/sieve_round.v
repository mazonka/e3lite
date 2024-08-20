// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
module sieve_round (
input wire [0:0] a,
input wire [7:0] b,
output wire [7:0] y
);
assign y = a[0] * b;
endmodule
