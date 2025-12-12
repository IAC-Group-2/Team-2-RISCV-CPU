// TB written by Yichan for Lab3 and adapted by Anthony

#include "Vdut.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include "vbuddy.cpp" // include vbuddy code
#define MAX_SIM_CYC 100000

int main(int argc, char **argv, char **env)
{
    int lights = 0; // state to toggle LED lights

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vdut *top = new Vdut;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("f1.vcd");

    // init Vbuddy
    if (vbdOpen() != 1)
        return (-1);
    vbdHeader("F1");
    //vbdSetMode(0); // Flag mode set to continuous (not one-shot)

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 0;

    // run simulation for MAX_SIM_CYC clock cycles
    for (int simcyc = 0; simcyc < MAX_SIM_CYC; simcyc++)
    {
        // dump variables into VCD file and toggle clock
        for (int tick = 0; tick < 2; tick++)
        {
            tfp->dump(2 * simcyc + tick);
            top->clk = !top->clk;
            top->eval();
        }

        top->rst = (simcyc < 2); // assert reset for 1st cycle
        vbdBar(top->a0 & 0xFF); //light sqetting

        if (Verilated::gotFinish() || vbdGetkey() == 'q')
            exit(0);
    }

    vbdClose(); // ++++
    tfp->close();
    delete top;
    exit(0);
}