// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdut.h for the primary calling header

#ifndef VERILATED_VDUT___024ROOT_H_
#define VERILATED_VDUT___024ROOT_H_  // guard

#include "verilated.h"

class Vdut__Syms;

class Vdut___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk_i,0,0);
    VL_IN8(rst_i,0,0);
    VL_OUT8(predictTakenF_o,0,0);
    VL_IN8(BranchE_i,0,0);
    VL_IN8(TakenE_i,0,0);
    CData/*0:0*/ __Vclklast__TOP__clk_i;
    VL_IN(PCF_i,31,0);
    VL_IN(PCE_i,31,0);
    VL_OUT(predictTargetF_o,31,0);
    VL_IN(PCTargetE_i,31,0);
    IData/*31:0*/ branch_predict__DOT__unnamedblk1__DOT__i;
    VlUnpacked<CData/*1:0*/, 256> branch_predict__DOT__state_table;
    VlUnpacked<IData/*31:0*/, 256> branch_predict__DOT__target_table;

    // INTERNAL VARIABLES
    Vdut__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vdut___024root(Vdut__Syms* symsp, const char* name);
    ~Vdut___024root();
    VL_UNCOPYABLE(Vdut___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
