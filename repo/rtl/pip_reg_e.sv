module pip_reg_e #( //Decode to execute stage
    PC_WIDTH = 32,
    INSTRUCTION_WIDTH = 32
    REGISTER_ADDR_SIZE = 5
)(
    input   logic                           clk_i,
    input   logic                           en_i,

    input   logic                           RegWriteD_i, //Decode
    output  logic                           RegWriteE_o, //Execute
    
    input   logic[1:0]                      ResultSrcD_i, //Decode
    output  logic[1:0]                      ResultSrcE_o, //Execute

    input   logic                           MemWriteD_i, //Decode
    output  logic                           MemWriteE_o //Execute

    input   logic                           JumpD_i, //Decode
    output  logic                           JumpE_i //Execute

    input   logic                           BranchD_i, //Decode
    output  logic                           BranchE_i //Execute

    input   logic [2:0]                     ALUControlD_i, //Decode
    output  logic [2:0]                     ALUControlE_o //Execute

    input   logic                           ALUSrcD_i, //Decode
    output  logic                           ALUSrcE_o //Execute
    
    input   logic [INSTRUCTION_WIDTH-1:0]   RD1D_i, //Decode
    output  logic [INSTRUCTION_WIDTH-1:0]   RD1E_o //Execute
    
    input   logic [INSTRUCTION_WIDTH-1:0]   RD2D_i, //Decode
    output  logic [INSTRUCTION_WIDTH-1:0]   RD2E_o //Execute
    
    input   logic [PC_WIDTH-1:0]            PCD_i, //Decode
    output  logic [PC_WIDTH-1:0]            PCE_o //Execute
    
    input   logic [REGISTER_ADDR_SIZE-1:0]  RdD_i, //Decode
    output  logic [REGISTER_ADDR_SIZE-1:0]  RdE_o //Execute
    
    input   logic [INSTRUCTION_WIDTH-1:0]   ImmExtD_i, //Decode
    output  logic [INSTRUCTION_WIDTH-1:0]   ImmExtE_o //Execute
    
    input   logic [PC_WIDTH-1:0]            PCPlus4D_i, //Decode
    output  logic [PC_WIDTH-1:0]            PCPlus4E_o //Execute
    
);

always_ff @(posedge clk_i) begin
    if (en_i) begin
        pcD_o <= pcF_i;
        InstrD_o <= InstrF_i;
        pcPlus4D_o <= pcPlus4F_i;
    end
    else begin//freeze
        pcD_o <= pcD_o;
        InstrD_o <= InstrD_o;
        pcPlus4D_o <= pcPlus4D_o;
    end
end
endmodule
