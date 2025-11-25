module control_unit(
    input   logic   [6:0]   op_i,
    input   logic           Zero_i,
    input   logic   [2:0]   funct3_i,
    input   logic           funct7_i,
    output  logic           RegWrite_o,
    output  logic   [2:0]   ALUControl_o,
    output  logic           ALUSrc_o,
    output  logic   [2:0]   ImmSrc_o,
    output  logic           PCSrc_o
);

logic branch;

always_comb begin
    RegWrite_o = 0;
    ALUControl_o = 3'b0;
    ALUSrc_o = 0;
    ImmSrc_o = 0;
    branch = 0;

    case (op_i) 
        7'b0010011: begin // addi
            RegWrite_o = 1;
            ALUControl_o = 3'b0; // add
            ALUSrc_o = 1; // immediate
            ImmSrc_o = 3'b0; // I type
            branch = 0;    
        end

        7'b1100011: begin // bne
            RegWrite_o = 0;
            ALUControl_o = 3'b1; // sub
            ALUSrc_o = 0; // reg
            ImmSrc_o = 3'b1; // B type
            branch = 1; // ben 
        end
        
        default: begin
            RegWrite_o = 0;
            ALUControl_o = 3'b0;
            ALUSrc_o = 0;
            ImmSrc_o = 3'b0;
            branch = 0;
        end
    endcase
    
    PCSrc_o = branch & ~Zero_i;

end
endmodule
