module mux_reg #(
    parameter DATA_WIDTH = 32
)(
    input  logic [DATA_WIDTH-1:0] PCPlus4F_i,
    input  logic [DATA_WIDTH-1:0] PCTargetE_i,
    input  logic [DATA_WIDTH-1:0] ALUResultE_i,
    input  logic                  PCSrcE_i,
    input  logic                  JalrE_i, // from top: (JumpE && ALUSrcE)
    output logic [DATA_WIDTH-1:0] PCNext_o
);

    always_comb begin
        if (PCSrcE_i) begin // If jump/branch taken
            // JALR uses ALU Result, others use PC adder target
            PCNext_o = (JalrE_i) ? ALUResultE_i : PCTargetE_i;
        end else begin
            // Step through normally
            PCNext_o = PCPlus4F_i;
        end
    end

endmodule
