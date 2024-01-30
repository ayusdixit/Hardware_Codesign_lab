`timescale 1ns/1ns

module top_tb;

reg clk;
reg rst_n;
reg [7:0] input_1, input_2, input_3, input_4, input_5, input_6, input_7, input_8;
wire [63:0] result;
integer file;

// Her P = 8  and Q = 10000
top #(8, 10000) top_inst (
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
    .result(result)
);

always #5 clk = ~clk;

initial begin
    clk = 0;
    file = $fopen("input.txt", "r");
    if (file == 0) begin
        $display("Error: could not open file inputs.txt");
        $finish;
    end
end

initial begin
    rst_n = 0;
    #10;
    while (!$feof(file)) begin
        $fscanf(file, "%d %d %d %d %d %d %d %d", input_1, input_2, input_3, input_4, input_5, input_6, input_7, input_8);
        rst_n = 1;
        #100;
        $display("Result: %0d  , %tns", result , $time);
        rst_n = 0;
        #10;
    end
    $fclose(file);
    $finish;
end

endmodule
