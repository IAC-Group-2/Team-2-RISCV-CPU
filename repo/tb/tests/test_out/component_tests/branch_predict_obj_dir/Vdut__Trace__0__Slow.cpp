// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdut__Syms.h"


VL_ATTR_COLD void Vdut___024root__trace_init_sub__TOP__0(Vdut___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+1,"clk_i", false,-1);
    tracep->declBit(c+2,"rst_i", false,-1);
    tracep->declBus(c+3,"PCF_i", false,-1, 31,0);
    tracep->declBus(c+4,"PCE_i", false,-1, 31,0);
    tracep->declBit(c+5,"predictTakenF_o", false,-1);
    tracep->declBus(c+6,"predictTargetF_o", false,-1, 31,0);
    tracep->declBus(c+7,"PCTargetE_i", false,-1, 31,0);
    tracep->declBit(c+8,"BranchE_i", false,-1);
    tracep->declBit(c+9,"TakenE_i", false,-1);
    tracep->pushNamePrefix("branch_predict ");
    tracep->declBus(c+13,"PC_WIDTH", false,-1, 31,0);
    tracep->declBus(c+14,"TABLE_BITS", false,-1, 31,0);
    tracep->declBit(c+1,"clk_i", false,-1);
    tracep->declBit(c+2,"rst_i", false,-1);
    tracep->declBus(c+3,"PCF_i", false,-1, 31,0);
    tracep->declBus(c+4,"PCE_i", false,-1, 31,0);
    tracep->declBit(c+5,"predictTakenF_o", false,-1);
    tracep->declBus(c+6,"predictTargetF_o", false,-1, 31,0);
    tracep->declBus(c+7,"PCTargetE_i", false,-1, 31,0);
    tracep->declBit(c+8,"BranchE_i", false,-1);
    tracep->declBit(c+9,"TakenE_i", false,-1);
    tracep->declBus(c+10,"index_f", false,-1, 7,0);
    tracep->declBus(c+11,"index_e", false,-1, 7,0);
    tracep->pushNamePrefix("unnamedblk1 ");
    tracep->declBus(c+12,"i", false,-1, 31,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vdut___024root__trace_init_top(Vdut___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root__trace_init_top\n"); );
    // Body
    Vdut___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vdut___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vdut___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vdut___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vdut___024root__trace_register(Vdut___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vdut___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vdut___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vdut___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vdut___024root__trace_full_sub_0(Vdut___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vdut___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root__trace_full_top_0\n"); );
    // Init
    Vdut___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdut___024root*>(voidSelf);
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vdut___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vdut___024root__trace_full_sub_0(Vdut___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vdut__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdut___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->clk_i));
    bufp->fullBit(oldp+2,(vlSelf->rst_i));
    bufp->fullIData(oldp+3,(vlSelf->PCF_i),32);
    bufp->fullIData(oldp+4,(vlSelf->PCE_i),32);
    bufp->fullBit(oldp+5,(vlSelf->predictTakenF_o));
    bufp->fullIData(oldp+6,(vlSelf->predictTargetF_o),32);
    bufp->fullIData(oldp+7,(vlSelf->PCTargetE_i),32);
    bufp->fullBit(oldp+8,(vlSelf->BranchE_i));
    bufp->fullBit(oldp+9,(vlSelf->TakenE_i));
    bufp->fullCData(oldp+10,((0xffU & (vlSelf->PCF_i 
                                       >> 2U))),8);
    bufp->fullCData(oldp+11,((0xffU & (vlSelf->PCE_i 
                                       >> 2U))),8);
    bufp->fullIData(oldp+12,(vlSelf->branch_predict__DOT__unnamedblk1__DOT__i),32);
    bufp->fullIData(oldp+13,(0x20U),32);
    bufp->fullIData(oldp+14,(8U),32);
}
