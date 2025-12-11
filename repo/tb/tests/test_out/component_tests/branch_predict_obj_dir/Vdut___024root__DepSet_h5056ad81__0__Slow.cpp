// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdut.h for the primary calling header

#include "verilated.h"

#include "Vdut___024root.h"

VL_ATTR_COLD void Vdut___024root___settle__TOP__0(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___settle__TOP__0\n"); );
    // Body
    vlSelf->predictTakenF_o = (1U & (vlSelf->branch_predict__DOT__state_table
                                     [(0xffU & (vlSelf->PCF_i 
                                                >> 2U))] 
                                     >> 1U));
    vlSelf->predictTargetF_o = vlSelf->branch_predict__DOT__target_table
        [(0xffU & (vlSelf->PCF_i >> 2U))];
}

VL_ATTR_COLD void Vdut___024root___eval_initial(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk_i = vlSelf->clk_i;
}

VL_ATTR_COLD void Vdut___024root___eval_settle(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___eval_settle\n"); );
    // Body
    Vdut___024root___settle__TOP__0(vlSelf);
}

VL_ATTR_COLD void Vdut___024root___final(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___final\n"); );
}

VL_ATTR_COLD void Vdut___024root___ctor_var_reset(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk_i = VL_RAND_RESET_I(1);
    vlSelf->rst_i = VL_RAND_RESET_I(1);
    vlSelf->PCF_i = VL_RAND_RESET_I(32);
    vlSelf->PCE_i = VL_RAND_RESET_I(32);
    vlSelf->predictTakenF_o = VL_RAND_RESET_I(1);
    vlSelf->predictTargetF_o = VL_RAND_RESET_I(32);
    vlSelf->PCTargetE_i = VL_RAND_RESET_I(32);
    vlSelf->BranchE_i = VL_RAND_RESET_I(1);
    vlSelf->TakenE_i = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<256; ++__Vi0) {
        vlSelf->branch_predict__DOT__state_table[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0=0; __Vi0<256; ++__Vi0) {
        vlSelf->branch_predict__DOT__target_table[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->branch_predict__DOT__unnamedblk1__DOT__i = 0;
}
