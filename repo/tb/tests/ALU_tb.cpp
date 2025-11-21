/*
 *  TEST BENCH COPY CODE 
 */

#include "base_testbench.h"

#define TB_NAME ALUTestbench 

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->SrcA = 0;
        top->SrcB = 0;
        top->ALUControl = 0;
        // outputs: ALUResult, Zero
    }
};


// ADD
TEST_F(TB_NAME, AddWorksTest)
{
    top->ALUControl = 0b000;   
    top->SrcA = 10;
    top->SrcB = 20;

    top->eval();

    EXPECT_EQ(top->ALUResult, 30);
    EXPECT_EQ(top->Zero, 0);
}

// SUB
TEST_F(TB_NAME, SubWorksTest)
{
    top->ALUControl = 0b001;   
    top->SrcA = 20;
    top->SrcB = 5;

    top->eval();

    EXPECT_EQ(top->ALUResult, 15);
}

// AND
TEST_F(TB_NAME, AndWorksTest)
{
    top->ALUControl = 0b010;   
    top->SrcA = 0b1100;
    top->SrcB = 0b1010;

    top->eval();

    EXPECT_EQ(top->ALUResult, 0b1000);
}

// OR
TEST_F(TB_NAME, OrWorksTest)
{
    top->ALUControl = 0b011;   
    top->SrcA = 0b1100;
    top->SrcB = 0b0110;

    top->eval();

    EXPECT_EQ(top->ALUResult, 0b1110);
}

// SLT (a < b)
TEST_F(TB_NAME, SltWorksTest)
{
    top->ALUControl = 0b101;   
    top->SrcA = 5;
    top->SrcB = 9;

    top->eval();

    EXPECT_EQ(top->Zero, 1);
}

// undefined opcode
TEST_F(TB_NAME, DefaultCaseTest)
{
    top->ALUControl = 0b111;   
    top->SrcA = 1234;
    top->SrcB = 5678;

    top->eval();

    EXPECT_EQ(top->ALUResult, 0);
    EXPECT_EQ(top->Zero, 0);
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
