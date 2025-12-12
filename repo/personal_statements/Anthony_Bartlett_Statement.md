# **RISC-V RV32I Processor Coursework**

#### Anthony Bartlett | CID: 0255 6059 | GitHub: an-thony350

# Personal Statement


## Overview of Contributions
---

My main contribution focused on **stretch goal 3**, as well as implementation of the M-extension (multiplication)

### [**Full ISA**](#full-isa)

- RTL Design

    - ALU (`ALU.sv`)

    - Control Unit (`control_unit.sv`)

    - Branch Unit (`branch_unit.sv`)

    - Sign Extender (`sign_extend.sv`) 

- Multiplication Logic

    - Implementation of MUL, MULH, MULHSU, MULHU

### [**F1 FSM**](#f1-fsm)
- Assembly code design
    - `f1.s`

- Testbench for displaying results on Vbuddy (updated code from Yichan in Lab3)
    - `f1_tb.cpp`

### [**Testing & Verification**](#testing)

- Instruction Tests

    - Created assembly code to test all instructions


- Integration Testing

    - Full system verification with provided test programs

  

### [**Project Management**](#project-management-1)

- Version Control

    - Merge conflict resolution

    - Release tagging for milestone versions

## Design Decisions
---

### [**ALU Design**](#alu-design)
A significant design decision I was responsible for was extending the Arithmetic Logic Unit (ALU) to support the **RISC-V multiplication instructions** from the `M` extension. Although the coursework specification only required the RV32I base ISA, I implemented this extension as an enhancement to demonstrate architectural extensibility and correctness beyond the minimum requirements.

Three distinct operand extension paths were implemented:
- **Signed × Signed** (`MULH`)
- **Unsigned × Unsigned** (`MULHU`)
- **Signed × Unsigned** (`MULHSU`)

This was achieved by creating both sign-extended and zero-extended versions of the ALU inputs, ensuring correctness across all operand combinations without duplicating multiplication logic. The extended operands are multiplied once per cycle, and the required 32-bit portion of the result is selected based on the ALU control signal.

```systemverilog
signed_product          = sign_ext_A * sign_ext_B;
unsigned_product        = zero_ext_A * zero_ext_B;
signed_unsigned_product = sign_ext_A * zero_ext_B;
```
The ALU control encoding was extended to map each multiplication instruction to a unique control value. This allowed multiplication to be integrated cleanly into the existing `case` statement without altering the surrounding datapath:

```systemverilog
4'b1010: ALUResult_o = unsigned_product[31:0];        // MUL
4'b1011: ALUResult_o = signed_product[63:32];         // MULH
4'b1100: ALUResult_o = signed_unsigned_product[63:32];// MULHSU
4'b1101: ALUResult_o = unsigned_product[63:32];       // MULHU
```
This approach preserves the modularity of the ALU while maintaining compatibility with the existing pipeline control logic. Importantly, no additional pipeline stages or hardware blocks were required, as the multiplication is treated as a standard ALU operation and naturally benefits from existing forwarding and hazard logic.

Although this implementation is not performance-optimal compared to a multi-cycle or Booth-encoded multiplier, it is functionally correct, easy to verify, and demonstrates how ISA extensions can be integrated into a RISC-V processor with minimal architectural disruption.

### [**Control Unit Design**](#control-unit-design)

### **Control Unit Design**

My work on the control unit also focused on extending an existing RV32I decoder to support the RISC-V M-extension while preserving compatibility with all base instructions. A key design constraint was that multiplication instructions should integrate seamlessly into the existing datapath, without introducing new control signals, pipeline stages, or special execution paths.

At a high level, the control unit is divided into two stages:
1. **Main Decoder** — classifies the instruction using the opcode (`op_i`)
2. **ALU Decoder** — determines the exact ALU operation using `funct3` and `funct7`

This separation was essential for cleanly supporting multiplication.

#### **Main Decoder (Opcode-Level Control)**

Multiplication instructions reuse the standard R-type opcode (`0110011`). As a result, no changes were required to the opcode-level decoding logic. All R-type instructions, including `MUL`, assert the same control signals:

- `RegWrite_o = 1`
- `ALUSrc_o = 0` (register-register operation)
- `ResultSrc_o = 0` (ALU result written back)
- `ALUOp = 2'b10` (delegates decoding to ALU decoder)

This design choice ensures that multiplication instructions flow through the datapath identically to other R-type operations, allowing existing forwarding, hazard detection, and writeback logic to function without modification.

#### **ALU Decoder and M-Extension Integration**

Support for multiplication was implemented entirely within the ALU decoder by extending the `ALUOp = 2'b10` case. The decoder distinguishes multiplication instructions by detecting `funct7 = 0000001`, as defined by the RISC-V specification.

Each multiplication variant is identified using a combination of `funct3` and `funct7`, and mapped to a unique 4-bit ALU control code:

```systemverilog
3'b000: begin
    if (op_i == 7'b0110011 && funct7_i == 7'b0000001)
        ALUControl_o = 4'b1010;   // MUL
    else if (op_i == 7'b0110011 && funct7_i == 7'b0100000)
        ALUControl_o = 4'b0001;   // SUB
    else
        ALUControl_o = 4'b0000;   // ADD / ADDI
end
3'b001: begin
    if (op_i == 7'b0110011 && funct7_i == 7'b0000001)
        ALUControl_o = 4'b1011;   // MULH 
    else
        ALUControl_o = 4'b0101;   // SLL / SLLI
end
3'b010: begin
    if (op_i == 7'b0110011 && funct7_i == 7'b0000001)
        ALUControl_o = 4'b1100;   // MULHSU 
    else
        ALUControl_o = 4'b1000;   // SLT / SLTI
end
3'b011: begin
    if (op_i == 7'b0110011 && funct7_i == 7'b0000001)
        ALUControl_o = 4'b1101;   // MULHU 
    else
        ALUControl_o = 4'b1001;   // SLTU / SLTIU
end
```
If `funct7` does not indicate multiplication, the decoder falls back to the standard RV32I arithmetic operations (ADD, SUB, shifts, comparisons, etc.). This approach avoids ambiguity between instructions that share the same `funct3` value (e.g. ADD vs MUL).

#### Design Rationale

This implementation deliberately keeps multiplication as a pure ALU concern. The control unit does not need to know how multiplication is implemented internally; it simply selects the correct ALU operation. This separation of concerns provides several benefits:

- No additional datapath complexity

- No changes required to pipeline control or hazard logic

- Easy extensibility for future ALU operations

- Clear and maintainable decode logic

By isolating multiplication decoding within the ALU decoder stage, the control unit remains scalable and robust while fully supporting the RV32I base ISA plus the M extension.

### [**Branch Unit & Sign Extension Design**](#branch-unit--sign-extension-design)

To complete support for the full RV32I instruction set, I finalised the branching logic and corrected several issues in the sign extension unit. These components are critical for correct control flow and immediate handling in a pipelined processor.

#### Branch Unit
In the single-cycle implementation, branch decisions relied on the ALU zero flag alone. However, this approach does not scale to the full RV32I branch set, which includes both signed and unsigned comparisons. To address this, a dedicated branch unit was introduced in the execute stage.

The branch unit evaluates the branch condition based on the `funct3` field and the values of the source registers. Signed and unsigned comparisons are handled explicitly using `$signed(...)` where required. This design allows all branch instructions (`BEQ`, `BNE`, `BLT`, `BGE`, `BLTU`, `BGEU`) to be resolved correctly and consistently.

The branch unit is placed in the execute stage so that it can benefit from the existing forwarding logic, ensuring that branches depending on recently computed values behave correctly without additional stalls.

```systemverilog
3'b100: BranchTaken_o = ($signed(SrcA_i) < $signed(SrcB_i));   // BLT (signed)
3'b101: BranchTaken_o = ($signed(SrcA_i) >= $signed(SrcB_i));   // BGE (signed)

3'b110: BranchTaken_o = (SrcA_i < SrcB_i);           // BLTU (unsigned)
3'b111: BranchTaken_o = (SrcA_i >= SrcB_i);          // BGEU (unsigned)
```

#### Sign Extension
Supporting the full ISA required extending the sign extension unit to correctly handle all immediate formats, including I-type, S-type, B-type, U-type, and J-type immediates. In particular, careful attention was required for branch and jump immediates, which are assembled from non-contiguous instruction fields and must be sign-extended correctly to preserve control flow correctness.

Fixes were made to ensure:

- Correct sign extension for negative immediates

- Proper handling of shift-immediate instructions (`SLLI`, `SRLI`, `SRAI`)

- Correct immediate width and alignment for branch and jump targets

These corrections were validated using targeted assembly tests.

## Testing & Verification

### **Assembly Programs**

To verify correctness of the full RV32I instruction set and the M-extension multiplication instructions, I developed a suite of targeted RISC-V assembly programs. Each program isolates a specific instruction class and concludes by writing a deterministic value to register `a0`, enabling automated verification through the Verilator testbench.

Rather than relying on complex programs alone, these tests were designed to be **minimal, explicit, and diagnostic**, making it clear which instruction or datapath component was responsible if a failure occurred.

---

#### **Immediate Arithmetic & Logical Instructions**

`9_itype_alu.s`

This program validates all I-type arithmetic and logical instructions, including signed and unsigned comparisons and shift operations:

- `ADDI`, `ANDI`, `ORI`, `XORI`
- `SLLI`, `SRLI`, `SRAI`
- `SLTI`, `SLTIU`

Both positive and negative operands are used to confirm correct sign extension and comparison behaviour. The final value of `a0` acts as a checksum derived from intermediate results.

**Purpose:**
- Verify immediate decoding
- Confirm sign extension correctness
- Validate shift semantics and signed arithmetic

---

#### **Load Instructions & Byte Addressing**

`10_itype_load.s`

This test focuses on memory access correctness using all supported load instructions:

- `LB`, `LBU`
- `LH`, `LHU`
- `LW`

Memory is accessed at base address `0x10000` using `LUI`, and both signed and unsigned variants are summed to produce a final result.

**Purpose:**
- Validate byte and halfword extraction
- Confirm correct sign vs zero extension
- Test interaction between memory, cache, and datapath

---

#### **Jump Instructions (`JAL` / `JALR`)**

`11_jalr.s`

A control-flow test ensures correct behaviour of jump and return instructions:

- `JAL` correctly saves `PC+4` into `ra`
- `JALR` correctly returns to the calling instruction

A sentinel instruction immediately after the initial `JAL` ensures that incorrect jump behaviour is easily detected.

**Purpose:**
- Verify PC redirection logic
- Confirm correct return address handling
- Test jump datapath integration in pipeline

---

#### **Branch Instructions**

`12_branch_test.s`

All six conditional branch instructions are explicitly tested:

- `BEQ`, `BNE`
- `BLT`, `BGE` (signed)
- `BLTU`, `BGEU` (unsigned)

Each branch is structured such that failure to take the correct path overwrites `a0` with a unique failure code. A successful run ends with `a0 = 100`.

**Purpose:**
- Verify branch condition evaluation
- Test signed vs unsigned comparisons
- Confirm correct branch target calculation and pipeline flushing

---

#### **Multiplication Instructions (M-Extension)**

`13_mul.s`

This program validates all four multiplication instructions:

- `MUL`
- `MULH`
- `MULHU`
- `MULHSU`

Edge cases are deliberately chosen, including:
- Signed × signed
- Unsigned × unsigned
- Signed × unsigned
- Maximum and minimum representable values

Both lower and upper 32-bit results are tested. All results are summed into `a0` to form a final checksum.

**Purpose:**
- Verify correct operand extension
- Confirm high-word extraction logic
- Validate integration of M-extension into ALU and control unit

---

#### **Verification Strategy**

Each assembly program:
- Runs indefinitely after completion to prevent accidental fall-through
- Produces a single final value in `a0`
- Is executed under Verilator and checked automatically by the testbench

Together, these programs provided high confidence in:
- Instruction decoding
- ALU correctness
- Sign extension
- Branch and jump behaviour
- Full-system integration including cache and pipeline control




## Conclusion & What I Learned
---

### **What I Learned**

This project significantly deepened my understanding of how architectural decisions propagate through an entire processor design. While I was already familiar with individual RISC-V instructions, implementing the full RV32I ISA in RTL forced me to think carefully about how decoding, datapath control, and execution semantics interact across pipeline stages.

One of the most valuable lessons was understanding how *small control decisions*—such as when and where signals are generated—can have large system-level consequences in a pipelined design. Supporting instructions like `JALR`, `AUIPC`, and the M-extension required not only correct decoding, but also careful signal propagation through pipeline registers and hazard logic.

Implementing multiplication instructions taught me the importance of **data representation and operand extension**. Handling signed × signed, signed × unsigned, and unsigned × unsigned multiplication highlighted how subtle errors in sign extension or bit slicing can silently produce incorrect results if not rigorously tested.

Finally, working extensively with Verilator and assembly-level testing improved my ability to debug hardware systematically. Rather than guessing, I learned to reduce problems to minimal test cases and reason about behaviour at the register and signal level.

---

### **Mistakes I Made**

One early mistake was underestimating the complexity of extending the ALU for multiplication. My initial implementation assumed that operand sign handling could be simplified, which led to incorrect results for `MULH` and `MULHSU`. Fixing this required revisiting the RISC-V specification and carefully reasoning about how operands should be extended before multiplication.

Another mistake was not introducing dedicated test programs early enough. Initially, I relied too heavily on integrated system tests, which made it harder to isolate the source of errors. Once I began writing small, instruction-specific assembly tests, debugging became much more structured and efficient.

---

### **What I Would Do Differently**

If I were to repeat this project, I would adopt a **test-driven approach** earlier in development. Writing assembly tests alongside RTL changes would have reduced debugging time and caught subtle issues sooner.

Additionally, I would prototype complex instructions such as multiplication in isolation before integrating them into the full ALU, allowing for faster iteration without impacting unrelated functionality.

I would also document everything I did a bit more thoroughly, as it would have made writing this readme report a bit easier. 

---

### **Final Thoughts**

Overall, this project was one of the most technically demanding and rewarding experiences of my degree so far. It required combining low-level digital design, instruction-set reasoning, and systematic debugging into a cohesive whole.

Contributing to the full ISA implementation and advanced features such as multiplication gave me confidence in my ability to reason about non-trivial hardware systems. More importantly, it reinforced the importance of disciplined testing, clear design decisions, and incremental validation—skills that are directly applicable to real-world hardware and systems engineering.

Completing this project has strengthened my interest in computer architecture and low-level system design, and it has provided a solid foundation for tackling more advanced processor and accelerator architectures in the future.
