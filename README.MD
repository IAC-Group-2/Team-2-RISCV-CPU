# Team Statement: RISC-V RV32I Pipelined Processor with Cache

## Table Of Contents

- [Quick Start](#quick-start)

- [Team Members and Contributions](#team-members-and-contributions)

- [Single Cycle Foundation](#single-cycle-foundation)

- [Pipelined Processor Design](#pipelined-processor-design)

- [Cache Implementation](#cache-implementation)

- [Testing and Verification](#testing-and-verification)

## Quick Start

Our team successfully implemented a fully functional RISC-V RV32I pipelined processor with integrated two-way set-associative cache memory, achieving all stretch goals outlined in the project specification. The processor supports the complete RV32I instruction set including arithmetic, logical, memory, branch, and jump operations, with hazard detection and forwarding logic to maintain correct execution across the pipeline stages.

To run all tests:
  
```bash

cd ./tb

./doit.sh

```

For individual component testing:

```bash

cd ./tb/tests/component_tests

chmod +x runtests.sh

./runtests.sh

```

## Team Members and Contributions


| Team Member       | GitHub        | CID      | Email           | Personal Statement |
| ----------------- | ------------- | -------- | --------------- | ------------------ |
| Joshua Hirschkorn | vortexisalpha | 02378306 | jh1234@ic.ac.uk |                    |
| Yichan            |               |          |                 |                    |
| Anthony           |               |          |                 |                    |
| Carys             |               |          |                 |                    |

### High-Level Contribution Summary

| **Component**                   | **Joshua** | **Yichan** | **Carys** | **Anthony** |
| ------------------------------- | ---------- | ---------- | --------- | ----------- |
| Single Cycle Foundation (Lab 4) | X          | X          | X         | X           |
| Pipelined Design                | X          | X          |           |             |
| Cache Implementation            | X          | X          |           |             |
| Control Unit & ALU Expansion    |            |            | X         | X           |
| Testing Framework               | X          | X          |           |             |
| Top-Level Integration           | X          | X          |           |             |
| Multiplication Instructons      |            |            |           | X           |
| Branch Prediction               |            |            | X         |             |

## Single Cycle Foundation

The project builds upon our Lab 4 implementation where we constructed a reduced RISC-V single cycle processor capable of executing basic instructions. 

Yichan was primarily responsible for the initial ALU implementation and register file design, which established the computational foundation that would later be expanded for the full instruction set. He also created and linked all the components in the `top.sv` file, ensuring that all the spacing and naming conventions were coherent to provide the least friction for future addition of modules.

Joshua worked on testing all components in the CPU. This included debugging other peoples modules and writing comprehensive test cases in C++. Individual component test benches were created for: ALU, Control Unit, Muxes, Sign extension unit and Instruction memory.

Anthony .... 

Carys.....

## Pipelined Processor Design

The transition from single cycle to pipelined architecture represented a substantial engineering challenge for the project, requiring careful coordination between team members to ensure all signals propagated correctly through the five pipeline stages: Fetch, Decode, Execute, Memory, and Writeback.

![pipeline_diagram](./personal_statement_assets/pipeline_diagram.png)

[See full image here](https://ibb.co/7tk689jL)

### Pipeline Architecture Overview

Our implementation divides instruction execution across five stages separated by pipeline registers that latch all necessary signals on each clock edge. This organisation permits up to five instructions to execute simultaneously within different stages, theoretically improving throughput by a factor of five compared to the single cycle design, though hazards and stalls reduce this advantage in practice.

The pipeline registers follow a consistent naming convention where signals include stage suffixes (F, D, E, M, W) to indicate their current position within the pipeline, making signal tracing during debugging significantly more manageable and reducing integration errors during top-level module assembly.

### Pipeline Registers

Joshua implemented `pip_reg_m` (Execute to Memory) and `pip_reg_e` (Decode to Execute), while Yichan created `pip_reg_d` (Fetch to Decode), `pip_reg_w` (Memory to Writeback), and modified the `pc_reg` module to support stalling functionality through an enable signal.

The Decode to Execute register (`pip_reg_e`) is the most complex, carrying fifteen distinct signals including control signals, register addresses, immediate values, and the program counter, all requiring flush capability to handle control hazards. This is why Joshua was working on 2 pipeline registers and Yichan was working on 3:

Example:

```systemverilog

always_ff @(posedge clk_i) begin

if (clr_i) begin // Flush logic for control hazards

RegWriteE_o <= 'b0;

ResultSrcE_o <= 'b0;

MemWriteE_o <= 'b0;

JumpE_o <= 'b0;

BranchE_o <= 'b0;

ALUControlE_o <= 'b0;

// ... all signals cleared to insert NOP

end

else if (en_i) begin

RegWriteE_o <= RegWriteD_i;

ResultSrcE_o <= ResultSrcD_i;

// ... normal propagation

end

end

```


The flush mechanism (`clr_i`) clears all outputs to zero, effectively inserting a NOP instruction into the pipeline, which becomes essential when branch mispredictions require discarding speculatively fetched instructions that should not execute.

### Hazard Detection and Forwarding

Joshua and Yichan collaboratively designed and implemented the hazard unit during extended video call sessions, carefully deriving the logic required to detect data dependencies and generate appropriate forwarding or stalling signals. The hazard unit monitors register addresses across pipeline stages and determines when forwarding can resolve dependencies without stalling.

Data forwarding resolves most Read After Write (RAW) hazards by routing computed values directly from later pipeline stages back to the execute stage inputs, bypassing the register file entirely:


```systemverilog

// Forward from Memory stage takes priority (more recent data)

if (((Rs1E_i == RdM_i) && RegWriteM_i) && (Rs1E_i != '0)) begin

ForwardAE_o = 2'b10; // Memory stage forwarding

end

else if (((Rs1E_i == RdW_i) && RegWriteW_i) && (Rs1E_i != '0)) begin

ForwardAE_o = 2'b01; // Writeback stage forwarding

end

```
  

The check ensuring source registers differ from x0 prevents unnecessary forwarding operations and maintains correct behaviour since x0 should always read as zero regardless of any forwarding paths.

Load instructions create a special hazard scenario where the data being loaded is not available until after the memory stage completes, meaning no forwarding path can resolve the dependency within a single cycle. The hazard unit detects this condition and stalls the pipeline:

```systemverilog

lwStall = ResultSrcE0_i && ((Rs1D_i == RdE_i) || (Rs2D_i == RdE_i));

StallF_o = lwStall || CacheStall_i;

StallD_o = lwStall || CacheStall_i;

FlushE_o = (lwStall || PCSrcE_i); // Insert bubble in execute stage

```

### Branch Unit

CARYS AND ANTHONY EDIT THIS

The branch unit, implemented by Carys and Anthony, evaluates branch conditions in the execute stage using the ALU zero flag and result values, determining whether conditional branches should be taken based on the `funct3` field encoding:

  

```systemverilog

always_comb begin

unique case(funct3_i)

3'b000: BranchTaken_o = Zero_i; // BEQ

3'b001: BranchTaken_o = !Zero_i; // BNE

3'b100: BranchTaken_o = ($signed(SrcA_i) < $signed(SrcB_i)); // BLT

3'b101: BranchTaken_o = ($signed(SrcA_i) >= $signed(SrcB_i)); // BGE

3'b110: BranchTaken_o = (SrcA_i < SrcB_i); // BLTU

3'b111: BranchTaken_o = (SrcA_i >= SrcB_i); // BGEU

default: BranchTaken_o = 1'b0;

endcase

end

```

  

When a branch is taken, the hazard unit flushes the decode stage to discard the incorrectly fetched instruction, and the PC multiplexer routes the computed branch target address to the fetch stage.

### Control Unit

  CARYS AND ANTHONY EDIT THIS

The control unit, significantly expanded by Carys and Anthony to support the complete RV32I instruction set, decodes the opcode, funct3, and funct7 fields to generate all control signals required by the datapath. The main decoder uses a case statement to identify instruction types and set base control signals accordingly:

  

```systemverilog

case (op_i)

7'b0110011: begin // R-Type

RegWrite_o = 1;

ALUOp = 2'b10;

end

7'b0010011: begin // I-Type Arithmetic

RegWrite_o = 1;

ALUSrc_o = 1;

ALUOp = 2'b10;

if (funct3_i == 3'b001 || funct3_i == 3'b101)

ImmSrc_o = 3'b101; // Shift immediate encoding

end

// ... additional instruction types

endcase

```

  

A secondary decoder translates the ALUOp signal and funct3/funct7 fields into the specific 4-bit ALU control signal, handling the distinction between ADD and SUB operations (which share the same funct3 but differ in funct7) and managing the various I-type immediate arithmetic operations.

## Cache Implementation

The cache implementation represented a significant extension beyond the core project requirements, with Joshua and Yichan collaborating extensively through video calls to design and implement a two way set associative writeback cache that integrates seamlessly with the pipelined processor.

INSERT PHOTO OF CACHE FULL CPU DIAGRAM
### Cache Architecture

The cache stores 2 kilobytes of data across 256 sets, with each set containing two ways (cache lines). Each way stores a 32-bit data word alongside valid, dirty, and tag bits, with an LRU (Least Recently Used) bit per set indicating which way to replace on a cache miss:

![](./personal_statement_assets/Pasted%20image%2020251209231525.png)

```

Cache Line Format:

LRU (1)
Way0: Valid(1) Dirty(1) Tag(22) Data(32)
Way1: Valid(1) Dirty(1) Tag(22) Data(32)

```

The 22-bit tag, 8-bit set index, and 2-bit byte offset partition the 32-bit address, allowing the cache to hold data from across the entire address space while using the set index for direct mapping within each way.

### State Machine Design

Cache misses trigger a finite state machine that transitions through up to four states depending on whether the evicted cache line requires writeback.

![](./personal_statement_assets/Pasted%20image%2020251210183600.png)


The logic for this is below:  

```systemverilog

typedef enum {IDLE, WRITEBACK, FETCH, UPDATE} my_state;

  

always_comb begin

case (current_state)

IDLE: begin

if (cache_miss) begin

if (target_dirty)

next_state = WRITEBACK; // Evict dirty data first

else

next_state = FETCH; // Skip directly to fetch

end

end

WRITEBACK: next_state = FETCH;

FETCH: next_state = UPDATE;

UPDATE: next_state = IDLE;

endcase

end

```

The WRITEBACK state writes the dirty cache line back to main memory before fetching the new data, ensuring coherency between cache and memory. The UPDATE state stores the fetched data into the cache and updates the appropriate metadata bits before returning to IDLE.

### Cache Stall Integration

Joshua and Yichan modified the hazard unit to handle cache miss stalling, freezing all pipeline stages while the cache completes its state machine sequence. Unlike load-word stalls which only affect the front of the pipeline, cache stalls must freeze all stages to prevent any instruction from advancing with potentially stale or inconsistent data:

```systemverilog

StallF_o = lwStall || CacheStall_i;

StallD_o = lwStall || CacheStall_i;

StallE_o = CacheStall_i; // Later stages only stall on cache miss

StallM_o = CacheStall_i;

StallW_o = CacheStall_i;

  

if (!CacheStall_i) begin // Prevent flush during cache stalls

FlushD_o = PCSrcE_i;

FlushE_o = (lwStall || PCSrcE_i);

end

```

The critical insight here is that flush operations must be disabled during cache stalls because the instructions in the pipeline remain valid and should not be discarded; they are simply waiting for memory data to become available.

### Byte Addressing Support

A significant debugging challenge arose when byte-addressed memory operations (LBU, SB) failed because the cache initially operated only on word-aligned addresses. Joshua and Yichan implemented byte offset logic that extracts the appropriate byte from cached words during reads and merges individual bytes into existing words during writes:


```systemverilog

// Extract correct byte based on offset for read operations

if (byte_offset == 2'b00)

data_o = {24'b0, raw_cache_data[7:0]};

else if (byte_offset == 2'b01)

data_o = {24'b0, raw_cache_data[15:8]};

// ... additional byte offsets

```

  

The `funct3` signal must propagate through the pipeline to the memory stage so the cache knows whether to perform word or byte operations, requiring modifications to multiple pipeline registers that were not initially designed to carry this signal.


## Full Instruction Set

CARYS AND ANTHONY PLEASE DO

INSERT PHOTO OF DRAW.IO DIAGRAM WHEN YOU FINISH IT
### ALU Design With Extended Instruction Set

The arithmetic logic unit serves as the computational core of the processor, accepting two 32-bit operands alongside a 4-bit control signal that determines which operation to perform. The initial implementation supported addition, subtraction, bitwise AND, bitwise OR, and set-less-than comparisons, which were sufficient for the reduced instruction set but required significant expansion later.


```systemverilog

always_comb begin

case (ALUControl_i)

4'b0001: ALUResult_o = SrcA_i - SrcB_i; // SUB

4'b0000: ALUResult_o = SrcA_i + SrcB_i; // ADD

4'b0010: ALUResult_o = SrcA_i & SrcB_i; // AND

4'b0011: ALUResult_o = SrcA_i | SrcB_i; // OR

4'b0100: ALUResult_o = SrcA_i ^ SrcB_i; // XOR

4'b0101: ALUResult_o = SrcA_i << SrcB_i[4:0]; // SLL

4'b0110: ALUResult_o = SrcA_i >> SrcB_i[4:0]; // SRL

4'b0111: ALUResult_o = $signed(SrcA_i) >>> SrcB_i[4:0]; // SRA

// ... additional operations

endcase

end

```


Carys and Anthony later extended this module to support the complete RV32I instruction set, adding shift operations (logical left, logical right, arithmetic right), XOR operations, and both signed and unsigned set-less-than comparisons, bringing the total supported operations to eleven distinct functions.


## Extension tasks

### Multiplication Instructions

ANTHONY PLEASE DO

### Branch Prediction

CARYS PLEASE DO
## Testing and Verification

Comprehensive testing formed a crucial part of our development methodology, with Joshua and Yichan creating extensive component testbenches using Google Test and Verilator while the full system was verified using the provided assembly test programs.

### Component Testing Framework

Joshua created a shell script that automatically discovers and runs all component testbenches within the `component_tests` directory, compiling each module with Verilator and reporting pass/fail status:


```bash

for file in "${TEST_FOLDER}"/*_tb.cpp; do

name=$(basename "$file" _tb.cpp)

verilator -Wall -trace \

-cc "${RTL_FOLDER}/${name}.sv" \

-exe "${file}" \

-LDFLAGS "-lgtest -lgtest_main -lpthread"

make -j -C obj_dir/ -f Vdut.mk

./obj_dir/Vdut

done

```

  
Individual testbenches verify specific module functionality in isolation, catching bugs before they propagate to system-level integration:

- **Hazard Unit Tests**: Verify correct forwarding signal generation, load-word stall detection, and cache stall integration

- **Branch Unit Tests**: Confirm all six branch condition types evaluate correctly

- **Control Unit Tests**: Validate proper decoding for each instruction type

- **Pipeline Register Tests**: Ensure correct flush, stall, and normal operation behaviour

- **Register File Tests**: Ensure each register can hold a value correctly under varying circumstances

- **ALU Tests**: Verify all arithmetic and logical operations produce expected results

- **Cache Tests**: Verify state machine logic and cache memory and stalling is working propelry

- **Instruction Memory Tests**: Ensure instructions are accurately loaded into memory

### System Integration Testing

The provided test programs (`1_addi_bne` through `5_pdf`) exercise progressively more complex instruction sequences, with additional custom tests (`6_program` through `12_branch_test`) created to stress-test specific functionality:


```cpp

TEST_F(CpuTestbench, TestLbuSb) {

setupTest("3_lbu_sb");

initSimulation();

runSimulation(CYCLES);

EXPECT_EQ(top_->a0, 300);

}

  

TEST_F(CpuTestbench, TestPdf) {

setupTest("5_pdf");

setData("reference/gaussian.mem");

initSimulation();

runSimulation(CYCLES * 100);

EXPECT_EQ(top_->a0, 15363);

}

```

The PDF test was particularly valuable for validating the complete system including cache behaviour, as it performs extensive memory accesses while computing a probability distribution histogram that produces a deterministic final result.

### F1 Test algorithm

CARYS AND ANTHONY PLEASE DO