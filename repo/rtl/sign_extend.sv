module sign_extend #(
    parameter DATA_WIDTH = 32
)(
    input  logic [2:0]            ImmSrc_i,
    input  logic [DATA_WIDTH-1:0] ImmInstr_i,
    output logic [DATA_WIDTH-1:0] ImmExt_o
);

    always_comb begin
        case (ImmSrc_i)
            // I-type
            3'b000: ImmExt_o = {
                {20{ImmInstr_i[31]}},
                ImmInstr_i[31:20]
            };

            // B-type
            3'b001: ImmExt_o = {
                {19{ImmInstr_i[31]}}, 
                ImmInstr_i[31],
                ImmInstr_i[7],         
                ImmInstr_i[30:25],     
                ImmInstr_i[11:8],        
                1'b0                      
            };

            // S-type
            3'b010: ImmExt_o = {
                {20{ImmInstr_i[31]}},
                ImmInstr_i[31:25],
                ImmInstr_i[11:7]
            };

            // U-type
            3'b011: ImmExt_o = { 
                ImmInstr_i[31:12], 12'b0 
            };

            // J-type
            3'b100: ImmExt_o = {
                {11{ImmInstr_i[31]}},
                ImmInstr_i[31],
                ImmInstr_i[19:12],
                ImmInstr_i[20],
                ImmInstr_i[30:21],
                1'b0         
            };
            default: ImmExt_o = {DATA_WIDTH{1'b0}};
        endcase
    end

    /* verilator lint_off UNUSED */
    wire [6:0] unused = ImmInstr_i[6:0];
    /* verilator lint_on UNUSED */

endmodule
