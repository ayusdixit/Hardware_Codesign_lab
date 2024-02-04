module cb #(parameter q = 10000)(
    input [31:0] num,
    output reg [63:0] sum
);

    integer i;
    reg [31:0] rand_num;

    always @* begin
        sum = 0;
        for (i = 0; i < num; i = i + 1) begin
            rand_num = $urandom_range(90000 - 10000 + 1) + 10000;  
            sum = sum + rand_num;
        end
    end

endmodule
