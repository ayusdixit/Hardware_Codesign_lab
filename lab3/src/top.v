module top #(parameter P = 8, q = 10000)(
    input clk,
    input rst_n,
    input wire [7:0] input_1,
    input wire [7:0] input_2,
    input wire [7:0] input_3,
    input wire [7:0] input_4,
    input wire [7:0] input_5,
    input wire [7:0] input_6,
    input wire [7:0] input_7,
    input wire [7:0] input_8,
    output reg [63:0] result
);

reg [63:0] cb_sum;
reg [7:0] ca_average;

ca #(P) ca_inst (
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
    .average(ca_average)
);

cb #(q) cb_inst (
    .num(ca_average),
    .sum(cb_sum)
);

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        result <= 0;
    end else begin
        result <= cb_sum;
    end
end

endmodule

