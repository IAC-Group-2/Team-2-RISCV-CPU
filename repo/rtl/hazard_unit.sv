module hazard_unit#(
    REGISTER_ADDRESS_WIDTH = 5
)(
    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      Rs1D_i;
    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      Rs2D_i;
  
    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      Rs1E_i;
    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      Rs2E_i;
    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      RdE_i;
    input   logic [1:0]                             ResultSrcE_i;

    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      RdM_i;
    input   logic                                   RegWriteM_i;
 
    input   logic [REGISTER_ADDRESS_WIDTH-1:0]      RdW_i;
    input   logic                                   RegWriteW_i;

    input   logic                                   PCSrcE_i;

    output  logic [1:0]                             ForwardAE_o;
    output  logic [1:0]                             ForwardBE_o;

    output  logic                                   StallF_o;
    output  logic                                   StallD_o;
    output  logic                                   FlushD_o;
    output  logic                                   FlushE_o;
);

endmodule