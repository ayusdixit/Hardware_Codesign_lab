
//module repeated sum 
module cb #(parameter q = 10000)(input [7:0] num, output reg [63:0] sum);
    integer i;
    always @* begin
        sum = 0;
        for (i = 0; i < q; i = i + 1) begin
            sum = sum + num;
        end
    end
endmodule

