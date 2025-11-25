module instr_mem #(
    parameter   ADDRESS_WIDTH = 32,
                BYTE_WIDTH = 8
)(
    input  logic [ADDRESS_WIDTH-1:0] A_i,
    output logic [ADDRESS_WIDTH-1:0] RD_o
);

logic [ADDRESS_WIDTH-1:0] instr_rom [1023:0];
logic [BYTE_WIDTH-1:0] byte_rom [4095:0];
initial begin
    integer i;
    $readmemh("../rtl/program.hex", byte_rom);
    for (i=0; i<256; i++)
        instr_rom[i] = {byte_rom[i*4+3], byte_rom[i*4+2], byte_rom[i*4+1], byte_rom[i*4+0]};
end

assign RD_o = instr_rom[A_i[9:2]];

endmodule
