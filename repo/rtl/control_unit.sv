module control(
    input   logic   [6:0]   op,
    input   logic           Zero,
    input   logic   [2:0]   funct3,
    input   logic           funct7,
    output  logic           RegWrite,
    output  logic   [2:0]   ALUctrl,
    output  logic           ALUsrc,
    output  logic   [1:0]   Immsrc,
    output  logic           PCsrc
);

logic branch;

always_comb begin
    RegWrite = 0;
    ALUctrl = 3'b0;
    ALUsrc = 0;
    Immsrc = 0;
    branch = 0;

    case (op) 
        7'b0010011: begin // addi
            RegWrite = 1;
            ALUctrl = 3'b0; // add
            ALUsrc = 1; // immediate
            Immsrc = 0; // I type
            branch = 0;    
        end

        7'b1100011: begin // bne
            RegWrite = 0;
            ALUctrl = 3'b1; // sub
            ALUsrc = 0; // reg
            Immsrc = 1; // B type
            branch = 1; // ben 
        end
        
        default: begin
            RegWrite = 0;
            ALUctrl = 3'b0;
            ALUsrc = 0;
            Immsrc = 0;
            branch = 0;
        end
    endcase
    
    PCsrc = branch & ~Zero;

end
endmodule
