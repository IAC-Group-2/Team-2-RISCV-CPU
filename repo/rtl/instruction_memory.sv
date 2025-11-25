module instr_mem (
    input  logic [31:0] A,
    output logic [31:0] RD
);

logic [31:0] instr_rom [1023:0];
logic [7:0] byte_rom [4095:0];
initial begin
    integer i;
    $readmemh("../rtl/program.hex", byte_rom);
    for (i=0; i<256; i++)
        instr_rom[i] = {byte_rom[i*4+3], byte_rom[i*4+2], byte_rom[i*4+1], byte_rom[i*4+0]};
end

assign RD = instr_rom[A[9:2]];

endmodule
