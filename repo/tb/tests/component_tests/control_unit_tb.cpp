/*
 *  Component testbench for control_unit
 */

#include "base_testbench.h"

#define TB_NAME ControlUnitTestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->op_i = 0;
        top->funct3_i = 0;
        top->funct7_i = 0;
        // outputs: RegWrite_o, MemWrite_o, ALUControl_o, ALUSrc_o, ImmSrc_o, ResultSrc_o, Jump_o, Branch_o
    }
};

// ADDI decode
TEST_F(TB_NAME, AddiDecodeTest)
{
    top->op_i = 0b0010011;
    top->funct3_i = 0b000;
    top->eval();

    EXPECT_EQ(top->RegWrite_o, 1);
    EXPECT_EQ(top->ALUControl_o, 0b000);
    EXPECT_EQ(top->ALUSrc_o, 1);
    EXPECT_EQ(top->ImmSrc_o, 3'b000);
    EXPECT_EQ(top->ResultSrc_o, 2'b00);
    EXPECT_EQ(top->Branch_o, 0);
}

// LOAD decode
TEST_F(TB_NAME, LoadDecodeTest)
{
    top->op_i = 0b0000011;
    top->funct3_i = 0b010;
    top->eval();

    EXPECT_EQ(top->RegWrite_o, 1);
    EXPECT_EQ(top->ResultSrc_o, 2'b01);
    EXPECT_EQ(top->ALUSrc_o, 1);
    EXPECT_EQ(top->MemWrite_o, 0);
}

// STORE decode
TEST_F(TB_NAME, StoreDecodeTest)
{
    top->op_i = 0b0100011;
    top->funct3_i = 0b010;
    top->eval();

    EXPECT_EQ(top->RegWrite_o, 0);
    EXPECT_EQ(top->MemWrite_o, 1);
    EXPECT_EQ(top->ALUSrc_o, 1);
    EXPECT_EQ(top->ImmSrc_o, 3'b010);
}

// BNE branch decode
TEST_F(TB_NAME, BneDecodeTest)
{
    top->op_i = 0b1100011;
    top->funct3_i = 0b001;
    top->eval();

    EXPECT_EQ(top->Branch_o, 1);
    EXPECT_EQ(top->ALUControl_o, 0b001);
    EXPECT_EQ(top->ALUSrc_o, 0);
    EXPECT_EQ(top->ImmSrc_o, 3'b001);
}

// default decode
TEST_F(TB_NAME, DefaultCaseTest)
{
    top->op_i = 0;
    top->funct3_i = 0;
    top->funct7_i = 0;
    top->eval();

    EXPECT_EQ(top->RegWrite_o, 0);
    EXPECT_EQ(top->MemWrite_o, 0);
    EXPECT_EQ(top->ALUSrc_o, 0);
    EXPECT_EQ(top->ResultSrc_o, 0);
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

