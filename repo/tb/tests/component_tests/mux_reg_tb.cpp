/*
 *  Component testbench for mux_reg (PC mux)
 */

#include "base_testbench.h"

#define TB_NAME MuxRegTestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->PCPlus4F_i = 0;
        top->PCTargetE_i = 0;
        top->ALUResultE_i = 0;
        top->PCSrcE_i = 0;
        top->JalrE_i = 0;
    }
};

TEST_F(TB_NAME, DefaultTakesPcPlus4)
{
    top->PCPlus4F_i = 0x10;
    top->eval();
    EXPECT_EQ(top->PCNext_o, 0x10u);
}

TEST_F(TB_NAME, BranchTakesTarget)
{
    top->PCTargetE_i = 0x200;
    top->PCSrcE_i = 1;
    top->JalrE_i = 0;
    top->eval();
    EXPECT_EQ(top->PCNext_o, 0x200u);
}

TEST_F(TB_NAME, JalrUsesAluResult)
{
    top->ALUResultE_i = 0xDEADBEEF;
    top->PCTargetE_i = 0x12340000;
    top->PCSrcE_i = 1;
    top->JalrE_i = 1;
    top->eval();
    EXPECT_EQ(top->PCNext_o, 0xDEADBEEF);
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

