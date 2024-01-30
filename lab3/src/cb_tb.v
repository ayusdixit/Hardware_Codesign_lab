module cb_tb;
    reg [7:0] num;
    wire [63:0] sum;

    cb #(10000) u1 (.num(num), .sum(sum));

    initial begin
         num = 8'd2; 

        #10;

         $display("Sum = %d", sum);

         $finish;
    end
endmodule

