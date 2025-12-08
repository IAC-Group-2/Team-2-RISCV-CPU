/*
 *  Component testbench for mux3
 */

#include "base_testbench.h"

#define TB_NAME Mux3Testbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->in0_i = 0;
        top->in1_i = 0;
        top->in2_i = 0;
        top->sel_i = 0;
    }
};

TEST_F(TB_NAME, SelectIn0)
{
    top->in0_i = 0xAAAABBBB;
    top->sel_i = 0b00;
    top->eval();
    EXPECT_EQ(top->out_o, 0xAAAABBBB);
}

TEST_F(TB_NAME, SelectIn1)
{
    top->in1_i = 0x11112222;
    top->sel_i = 0b01;
    top->eval();
    EXPECT_EQ(top->out_o, 0x11112222);
}

TEST_F(TB_NAME, SelectIn2)
{
    top->in2_i = 0x33334444;
    top->sel_i = 0b10;
    top->eval();
    EXPECT_EQ(top->out_o, 0x33334444);
}

int main(int argc, char **argv)
{
    top = new Vdut;
    tfp = new VerilatedVcdC;

    Verilated::traceEverOn(true);
    top->trace(tfp, 99);
    tfp->open("waveform.vcd");

    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();

    top->final();
    tfp->close();

    delete top;
    delete tfp;

    return res;
}

