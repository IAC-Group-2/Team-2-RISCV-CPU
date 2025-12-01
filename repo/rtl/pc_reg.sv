module pc_reg #(
    parameter DATA_WIDTH = 32
)(
    input  logic                   clk_i,
    input  logic                   rst_i,
    input  logic [DATA_WIDTH-1:0]  next_pc_i,
    output logic [DATA_WIDTH-1:0]  PC_o
);

    always_ff @(posedge clk_i, posedge rst_i) begin
        if (rst_i)
            PC_o <= {DATA_WIDTH{1'b0}};
        else
            PC_o <= next_pc_i;
    end

endmodule
