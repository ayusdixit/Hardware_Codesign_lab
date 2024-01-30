module ca #(
    parameter P = 8
)(  input clk , 
input rst_n,
    input wire [7:0] input_1,
    input wire [7:0] input_2,
    input wire [7:0] input_3,
    input wire [7:0] input_4,
    input wire [7:0] input_5,
    input wire [7:0] input_6,
    input wire [7:0] input_7,
    input wire [7:0] input_8,
    output reg [7:0] average
);

reg [15:0] sum;

always @(posedge clk or posedge rst_n) begin
    if (!rst_n) begin
        sum <= 0;
        average <= 0;
    end else begin
         sum <= input_1 + input_2 + input_3 + input_4 + input_5 + input_6 + input_7 + input_8;
        
         average <= sum >> $clog2(P);  
    end
end

endmodule

