module regfile #(
    parameter   ADDRESS_WIDTH = 5,
                DATA_WIDTH = 32
)(
    input   logic                       clk_i,
    input   logic [ADDRESS_WIDTH-1:0]   A1_i,
    input   logic [ADDRESS_WIDTH-1:0]   A2_i,
    input   logic [ADDRESS_WIDTH-1:0]   A3_i,
    input   logic [DATA_WIDTH-1:0]      WD3_i,
    input   logic                       WE3_i,
    output  logic [DATA_WIDTH-1:0]      RD1_o,
    output  logic [DATA_WIDTH-1:0]      RD2_o,
    output  logic [DATA_WIDTH-1:0]      A0_o
);

    logic [DATA_WIDTH-1:0] mem [2**ADDRESS_WIDTH-1:0];

    // register write (prevent writing to x0)
    always_ff @(posedge clk_i) begin
        if (WE3_i && (A3_i != 5'b0)) begin
            mem[A3_i] <= WD3_i;
        end
    end

    // register x0 is constant value 0
    assign RD1_o = (A1_i == 5'b0) ? {DATA_WIDTH{1'b0}} : mem[A1_i];
    assign RD2_o = (A2_i == 5'b0) ? {DATA_WIDTH{1'b0}} : mem[A2_i];
    
    assign A0_o = mem[10];

endmodule
