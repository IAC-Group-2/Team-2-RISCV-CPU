/*
 *  Component testbench for instr_mem
 */

#include "base_testbench.h"
#include <fstream>
#include <sstream>

#define TB_NAME InstrMemTestbench

Vdut *top;
VerilatedVcdC *tfp;
unsigned int ticks = 0;

class TB_NAME : public BaseTestbench
{
protected:
    void initializeInputs() override
    {
        top->A_i = 0;
    }
};

TEST_F(TB_NAME, ReadsFirstWordIfPresent)
{
    std::ifstream fin("program.hex");
    if (!fin.is_open())
    {
        GTEST_SKIP() << "program.hex not present, skipping ROM content check";
    }

    // pull first 4 bytes
    std::string line;
    uint32_t bytes[4] = {0};
    for (int i = 0; i < 4 && std::getline(fin, line); ++i)
    {
        std::stringstream ss;
        ss << std::hex << line;
        ss >> bytes[i];
    }
    uint32_t expected = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];

    top->A_i = 0;
    top->eval();
    EXPECT_EQ(top->RD_o, expected);
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

