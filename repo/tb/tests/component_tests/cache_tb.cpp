/*
 *  Component testbench for cache
 */

#include "base_testbench.h"

#define TB_NAME CacheTestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->clk_i = 0;
        top->rst_i = 1;
        top->MemWriteM_i = 0;
        top->ResultSrcM_i = 0b01; // read
        top->funct3_i = 0b010;
        top->addr_i = 0x0;
        top->data_i = 0x0;
        top->mem_rd_data_i = 0xDEADBEEF;
    }
};

TEST_F(TB_NAME, MissFetchThenHit)
{
    // reset pulse
    top->clk_i = 0; top->eval();
    top->clk_i = 1; top->eval();

    top->rst_i = 0;

    // IDLE->FETCH
    top->clk_i = 0; top->eval();
    top->clk_i = 1; top->eval();

    // FETCH->UPDATE
    top->clk_i = 0; top->eval();
    top->clk_i = 1; top->eval();

    // UPDATE->IDLE
    top->clk_i = 0; top->eval();
    top->clk_i = 1; top->eval();

    // hit now
    top->clk_i = 0; top->eval();
    EXPECT_EQ(top->data_o, 0xDEADBEEF);
    EXPECT_EQ(top->stall_o, 0);
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

