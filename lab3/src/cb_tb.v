module cb_tb;
    reg [31:0] num;
    wire [63:0] sum;

    cb #(10000) u1 (.num(num), .sum(sum));

    initial begin
         num = 31'd2; 

        #10;

         $monitor("Sum = %d , num = %d", sum  , num );

         $finish;
    end
endmodule

