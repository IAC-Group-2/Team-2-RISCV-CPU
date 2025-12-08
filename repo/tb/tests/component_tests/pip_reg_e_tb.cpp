/*
 *  Component testbench for pip_reg_e (ID/EX)
 */

#include "base_testbench.h"

#define TB_NAME PipRegETestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->clk_i = 0;
        top->clr_i = 0;
        top->en_i = 1;
        top->RegWriteD_i = 0;
        top->ResultSrcD_i = 0;
        top->MemWriteD_i = 0;
        top->JumpD_i = 0;
        top->BranchD_i = 0;
        top->ALUControlD_i = 0;
        top->funct3D_i = 0;
        top->ALUSrcD_i = 0;
        top->RD1D_i = 0;
        top->RD2D_i = 0;
        top->PCD_i = 0;
        top->Rs1D_i = 0;
        top->Rs2D_i = 0;
        top->RdD_i = 0;
        top->ImmExtD_i = 0;
        top->PCPlus4D_i = 0;
    }
};

TEST_F(TB_NAME, FlushClearsState)
{
    top->RegWriteD_i = 1;
    top->ResultSrcD_i = 0b11;
    top->MemWriteD_i = 1;
    top->clr_i = 1;

    top->clk_i = 0; top->eval();
    top->clk_i = 1; top->eval();

    EXPECT_EQ(top->RegWriteE_o, 0);
    EXPECT_EQ(top->MemWriteE_o, 0);
    EXPECT_EQ(top->ResultSrcE_o, 0);
}

TEST_F(TB_NAME, LatchesOnEnable)
{
    top->clr_i = 0;
    top->en_i = 1;
    top->RegWriteD_i = 1;
    top->MemWriteD_i = 1;
    top->ResultSrcD_i = 0b10;
    top->JumpD_i = 1;
    top->BranchD_i = 1;
    top->ALUControlD_i = 0b101;
    top->funct3D_i = 0b010;
    top->ALUSrcD_i = 1;
    top->RD1D_i = 0xABCDEF01;
    top->RD2D_i = 0x12345678;
    top->PCD_i = 0x10;
    top->Rs1D_i = 1;
    top->Rs2D_i = 2;
    top->RdD_i = 3;
    top->ImmExtD_i = 0xFF00FF00;
    top->PCPlus4D_i = 0x14;

    top->clk_i = 0; top->eval();
    top->clk_i = 1; top->eval();

    EXPECT_EQ(top->RegWriteE_o, 1);
    EXPECT_EQ(top->MemWriteE_o, 1);
    EXPECT_EQ(top->ResultSrcE_o, 2u);
    EXPECT_EQ(top->JumpE_o, 1);
    EXPECT_EQ(top->BranchE_o, 1);
    EXPECT_EQ(top->ALUControlE_o, 0b101);
    EXPECT_EQ(top->funct3E_o, 0b010);
    EXPECT_EQ(top->ALUSrcE_o, 1);
    EXPECT_EQ(top->RD1E_o, 0xABCDEF01);
    EXPECT_EQ(top->RD2E_o, 0x12345678);
    EXPECT_EQ(top->PCE_o, 0x10u);
    EXPECT_EQ(top->Rs1E_o, 1);
    EXPECT_EQ(top->Rs2E_o, 2);
    EXPECT_EQ(top->RdE_o, 3);
    EXPECT_EQ(top->ImmExtE_o, 0xFF00FF00);
    EXPECT_EQ(top->PCPlus4E_o, 0x14u);
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

