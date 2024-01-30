`timescale 1ns/1ps

module ca_tb;

  reg clk;
  reg rst_n;
  reg [7:0] input_1, input_2, input_3, input_4, input_5, input_6, input_7, input_8;
  wire [7:0] average;

   ca #(8) uut (
    .clk(clk),
    .rst_n(rst_n),
    .input_1(input_1),
    .input_2(input_2),
    .input_3(input_3),
    .input_4(input_4),
    .input_5(input_5),
    .input_6(input_6),
    .input_7(input_7),
    .input_8(input_8),
    .average(average)
  );

   always begin
    #5 clk = ~clk;
  end

   initial begin
    clk = 0;
    rst_n = 0;

    // Apply inputs
    input_1 = 8'h0A;
    input_2 = 8'h0B;
    input_3 = 8'h0C;
    input_4 = 8'h0D;
    input_5 = 8'h0E;
    input_6 = 8'h0F;
    input_7 = 8'h10;
    input_8 = 8'h11;
    
     #10 rst_n = 1;

     $monitor("Time=%t, Average=%d", $time, average);

     #1000000 $finish;
  end

   initial begin
     #20 input_1 = 8'd01;
    #20 input_2 = 8'd02;
    #20 input_3 = 8'd03;
    #20 input_4 = 8'd04;
    #20 input_5 = 8'd05;
    #20 input_6 = 8'd06;
    #20 input_7 = 8'd07;
    #20 input_8 = 8'd08;
  end

endmodule

