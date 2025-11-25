module ALU #(
    DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  SrcA_i,
    input   logic [DATA_WIDTH-1:0]  SrcB_i,
    input   logic [2:0]             ALUControl_i,
    output  logic [DATA_WIDTH-1:0]  ALUResult_o,
    output  logic                   Zero_o
);
always_comb begin
    ALUResult_o = 0;
    Zero_o = 0;
    case (ALUControl_i) //codes given in lecture notes
        3'b000: ALUResult_o = SrcA_i + SrcB_i; //add
        3'b001: ALUResult_o = SrcA_i - SrcB_i; //subtract
        3'b101: Zero_o = SrcA_i < SrcB_i; //set less than
        3'b011: ALUResult_o = SrcA_i | SrcB_i; //bitwise or
        3'b010: ALUResult_o = SrcA_i & SrcB_i; //bitwise and
        default:
            begin
            Zero_o = 0;
            ALUResult_o = 0;
            end
    endcase
end

endmodule
