// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdut.h for the primary calling header

#include "verilated.h"

#include "Vdut___024root.h"

VL_INLINE_OPT void Vdut___024root___sequent__TOP__0(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___sequent__TOP__0\n"); );
    // Init
    CData/*7:0*/ __Vdlyvdim0__branch_predict__DOT__state_table__v0;
    CData/*1:0*/ __Vdlyvval__branch_predict__DOT__state_table__v0;
    CData/*0:0*/ __Vdlyvset__branch_predict__DOT__state_table__v0;
    CData/*7:0*/ __Vdlyvdim0__branch_predict__DOT__state_table__v1;
    CData/*1:0*/ __Vdlyvval__branch_predict__DOT__state_table__v1;
    CData/*0:0*/ __Vdlyvset__branch_predict__DOT__state_table__v1;
    CData/*7:0*/ __Vdlyvdim0__branch_predict__DOT__target_table__v0;
    IData/*31:0*/ __Vdlyvval__branch_predict__DOT__target_table__v0;
    CData/*0:0*/ __Vdlyvset__branch_predict__DOT__target_table__v0;
    // Body
    __Vdlyvset__branch_predict__DOT__target_table__v0 = 0U;
    __Vdlyvset__branch_predict__DOT__state_table__v0 = 0U;
    __Vdlyvset__branch_predict__DOT__state_table__v1 = 0U;
    if ((1U & (~ (IData)(vlSelf->rst_i)))) {
        if (vlSelf->BranchE_i) {
            __Vdlyvval__branch_predict__DOT__target_table__v0 
                = vlSelf->PCTargetE_i;
            __Vdlyvset__branch_predict__DOT__target_table__v0 = 1U;
            __Vdlyvdim0__branch_predict__DOT__target_table__v0 
                = (0xffU & (vlSelf->PCE_i >> 2U));
        }
    }
    if (vlSelf->rst_i) {
        vlSelf->branch_predict__DOT__unnamedblk1__DOT__i = 0U;
        while (VL_GTS_III(32, 0x100U, vlSelf->branch_predict__DOT__unnamedblk1__DOT__i)) {
            vlSelf->branch_predict__DOT__state_table[(0xffU 
                                                      & vlSelf->branch_predict__DOT__unnamedblk1__DOT__i)] = 1U;
            vlSelf->branch_predict__DOT__target_table[(0xffU 
                                                       & vlSelf->branch_predict__DOT__unnamedblk1__DOT__i)] = 0U;
            vlSelf->branch_predict__DOT__unnamedblk1__DOT__i 
                = ((IData)(1U) + vlSelf->branch_predict__DOT__unnamedblk1__DOT__i);
        }
    } else if (vlSelf->BranchE_i) {
        if (vlSelf->TakenE_i) {
            if ((3U != vlSelf->branch_predict__DOT__state_table
                 [(0xffU & (vlSelf->PCE_i >> 2U))])) {
                __Vdlyvval__branch_predict__DOT__state_table__v0 
                    = (3U & ((IData)(1U) + vlSelf->branch_predict__DOT__state_table
                             [(0xffU & (vlSelf->PCE_i 
                                        >> 2U))]));
                __Vdlyvset__branch_predict__DOT__state_table__v0 = 1U;
                __Vdlyvdim0__branch_predict__DOT__state_table__v0 
                    = (0xffU & (vlSelf->PCE_i >> 2U));
            }
        } else if ((0U != vlSelf->branch_predict__DOT__state_table
                    [(0xffU & (vlSelf->PCE_i >> 2U))])) {
            __Vdlyvval__branch_predict__DOT__state_table__v1 
                = (3U & (vlSelf->branch_predict__DOT__state_table
                         [(0xffU & (vlSelf->PCE_i >> 2U))] 
                         - (IData)(1U)));
            __Vdlyvset__branch_predict__DOT__state_table__v1 = 1U;
            __Vdlyvdim0__branch_predict__DOT__state_table__v1 
                = (0xffU & (vlSelf->PCE_i >> 2U));
        }
    }
    if (__Vdlyvset__branch_predict__DOT__target_table__v0) {
        vlSelf->branch_predict__DOT__target_table[__Vdlyvdim0__branch_predict__DOT__target_table__v0] 
            = __Vdlyvval__branch_predict__DOT__target_table__v0;
    }
    if (__Vdlyvset__branch_predict__DOT__state_table__v0) {
        vlSelf->branch_predict__DOT__state_table[__Vdlyvdim0__branch_predict__DOT__state_table__v0] 
            = __Vdlyvval__branch_predict__DOT__state_table__v0;
    }
    if (__Vdlyvset__branch_predict__DOT__state_table__v1) {
        vlSelf->branch_predict__DOT__state_table[__Vdlyvdim0__branch_predict__DOT__state_table__v1] 
            = __Vdlyvval__branch_predict__DOT__state_table__v1;
    }
}

VL_INLINE_OPT void Vdut___024root___combo__TOP__0(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___combo__TOP__0\n"); );
    // Body
    vlSelf->predictTargetF_o = vlSelf->branch_predict__DOT__target_table
        [(0xffU & (vlSelf->PCF_i >> 2U))];
    vlSelf->predictTakenF_o = (1U & (vlSelf->branch_predict__DOT__state_table
                                     [(0xffU & (vlSelf->PCF_i 
                                                >> 2U))] 
                                     >> 1U));
}

void Vdut___024root___eval(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk_i) & (~ (IData)(vlSelf->__Vclklast__TOP__clk_i)))) {
        Vdut___024root___sequent__TOP__0(vlSelf);
    }
    Vdut___024root___combo__TOP__0(vlSelf);
    // Final
    vlSelf->__Vclklast__TOP__clk_i = vlSelf->clk_i;
}

#ifdef VL_DEBUG
void Vdut___024root___eval_debug_assertions(Vdut___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk_i & 0xfeU))) {
        Verilated::overWidthError("clk_i");}
    if (VL_UNLIKELY((vlSelf->rst_i & 0xfeU))) {
        Verilated::overWidthError("rst_i");}
    if (VL_UNLIKELY((vlSelf->BranchE_i & 0xfeU))) {
        Verilated::overWidthError("BranchE_i");}
    if (VL_UNLIKELY((vlSelf->TakenE_i & 0xfeU))) {
        Verilated::overWidthError("TakenE_i");}
}
#endif  // VL_DEBUG
