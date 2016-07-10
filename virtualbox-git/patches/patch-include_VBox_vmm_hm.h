$NetBSD$

--- include/VBox/vmm/hm.h.orig	2016-03-04 19:22:58.000000000 +0000
+++ include/VBox/vmm/hm.h
@@ -138,9 +138,9 @@ typedef enum HM64ON32OP
     HM64ON32OP_32BIT_HACK = 0x7fffffff
 } HM64ON32OP;
 
-VMMDECL(bool)                   HMIsEnabledNotMacro(PVM pVM);
+VMMDECL(bool)                   HMIsEnabledNotMacro(vbox_PVM pVM);
 VMM_INT_DECL(int)               HMInvalidatePage(PVMCPU pVCpu, RTGCPTR GCVirt);
-VMM_INT_DECL(bool)              HMHasPendingIrq(PVM pVM);
+VMM_INT_DECL(bool)              HMHasPendingIrq(vbox_PVM pVM);
 VMM_INT_DECL(PX86PDPE)          HMGetPaePdpes(PVMCPU pVCpu);
 VMM_INT_DECL(int)               HMAmdIsSubjectToErratum170(uint32_t *pu32Family, uint32_t *pu32Model, uint32_t *pu32Stepping);
 VMM_INT_DECL(bool)              HMSetSingleInstruction(PVMCPU pVCpu, bool fEnable);
@@ -149,14 +149,14 @@ VMM_INT_DECL(void)              HMHyperc
 
 #ifndef IN_RC
 VMM_INT_DECL(int)               HMFlushTLB(PVMCPU pVCpu);
-VMM_INT_DECL(int)               HMFlushTLBOnAllVCpus(PVM pVM);
-VMM_INT_DECL(int)               HMInvalidatePageOnAllVCpus(PVM pVM, RTGCPTR GCVirt);
-VMM_INT_DECL(int)               HMInvalidatePhysPage(PVM pVM, RTGCPHYS GCPhys);
-VMM_INT_DECL(bool)              HMIsNestedPagingActive(PVM pVM);
-VMM_INT_DECL(bool)              HMAreNestedPagingAndFullGuestExecEnabled(PVM pVM);
-VMM_INT_DECL(bool)              HMIsLongModeAllowed(PVM pVM);
-VMM_INT_DECL(bool)              HMAreMsrBitmapsAvailable(PVM pVM);
-VMM_INT_DECL(PGMMODE)           HMGetShwPagingMode(PVM pVM);
+VMM_INT_DECL(int)               HMFlushTLBOnAllVCpus(vbox_PVM pVM);
+VMM_INT_DECL(int)               HMInvalidatePageOnAllVCpus(vbox_PVM pVM, RTGCPTR GCVirt);
+VMM_INT_DECL(int)               HMInvalidatePhysPage(vbox_PVM pVM, RTGCPHYS GCPhys);
+VMM_INT_DECL(bool)              HMIsNestedPagingActive(vbox_PVM pVM);
+VMM_INT_DECL(bool)              HMAreNestedPagingAndFullGuestExecEnabled(vbox_PVM pVM);
+VMM_INT_DECL(bool)              HMIsLongModeAllowed(vbox_PVM pVM);
+VMM_INT_DECL(bool)              HMAreMsrBitmapsAvailable(vbox_PVM pVM);
+VMM_INT_DECL(PGMMODE)           HMGetShwPagingMode(vbox_PVM pVM);
 #else /* Nops in RC: */
 # define HMFlushTLB(pVCpu)                              do { } while (0)
 # define HMIsNestedPagingActive(pVM)                    false
@@ -172,30 +172,30 @@ VMM_INT_DECL(PGMMODE)           HMGetShw
  */
 VMMR0_INT_DECL(int)             HMR0Init(void);
 VMMR0_INT_DECL(int)             HMR0Term(void);
-VMMR0_INT_DECL(int)             HMR0InitVM(PVM pVM);
-VMMR0_INT_DECL(int)             HMR0TermVM(PVM pVM);
-VMMR0_INT_DECL(int)             HMR0EnableAllCpus(PVM pVM);
+VMMR0_INT_DECL(int)             HMR0InitVM(vbox_PVM pVM);
+VMMR0_INT_DECL(int)             HMR0TermVM(vbox_PVM pVM);
+VMMR0_INT_DECL(int)             HMR0EnableAllCpus(vbox_PVM pVM);
 # ifdef VBOX_WITH_RAW_MODE
-VMMR0_INT_DECL(int)             HMR0EnterSwitcher(PVM pVM, VMMSWITCHER enmSwitcher, bool *pfVTxDisabled);
-VMMR0_INT_DECL(void)            HMR0LeaveSwitcher(PVM pVM, bool fVTxDisabled);
+VMMR0_INT_DECL(int)             HMR0EnterSwitcher(vbox_PVM pVM, VMMSWITCHER enmSwitcher, bool *pfVTxDisabled);
+VMMR0_INT_DECL(void)            HMR0LeaveSwitcher(vbox_PVM pVM, bool fVTxDisabled);
 # endif
 
 VMMR0_INT_DECL(void)            HMR0SavePendingIOPortWrite(PVMCPU pVCpu, RTGCPTR GCPtrRip, RTGCPTR GCPtrRipNext,
                                                            unsigned uPort, unsigned uAndVal, unsigned cbSize);
 VMMR0_INT_DECL(void)            HMR0SavePendingIOPortRead(PVMCPU pVCpu, RTGCPTR GCPtrRip, RTGCPTR GCPtrRipNext,
                                                           unsigned uPort, unsigned uAndVal, unsigned cbSize);
-VMMR0_INT_DECL(int)             HMR0SetupVM(PVM pVM);
-VMMR0_INT_DECL(int)             HMR0RunGuestCode(PVM pVM, PVMCPU pVCpu);
-VMMR0_INT_DECL(int)             HMR0Enter(PVM pVM, PVMCPU pVCpu);
+VMMR0_INT_DECL(int)             HMR0SetupVM(vbox_PVM pVM);
+VMMR0_INT_DECL(int)             HMR0RunGuestCode(vbox_PVM pVM, PVMCPU pVCpu);
+VMMR0_INT_DECL(int)             HMR0Enter(vbox_PVM pVM, PVMCPU pVCpu);
 VMMR0_INT_DECL(int)             HMR0EnterCpu(PVMCPU pVCpu);
 VMMR0_INT_DECL(int)             HMR0LeaveCpu(PVMCPU pVCpu);
 VMMR0_INT_DECL(void)            HMR0ThreadCtxCallback(RTTHREADCTXEVENT enmEvent, void *pvUser);
 VMMR0_INT_DECL(bool)            HMR0SuspendPending(void);
 
 # if HC_ARCH_BITS == 32 && defined(VBOX_WITH_64_BITS_GUESTS)
-VMMR0_INT_DECL(int)             HMR0SaveFPUState(PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
-VMMR0_INT_DECL(int)             HMR0SaveDebugState(PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
-VMMR0_INT_DECL(int)             HMR0TestSwitcher3264(PVM pVM);
+VMMR0_INT_DECL(int)             HMR0SaveFPUState(vbox_PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
+VMMR0_INT_DECL(int)             HMR0SaveDebugState(vbox_PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
+VMMR0_INT_DECL(int)             HMR0TestSwitcher3264(vbox_PVM pVM);
 # endif
 
 VMMR0_INT_DECL(int)             HMR0EnsureCompleteBasicContext(PVMCPU pVCpu, PCPUMCTX pMixedCtx);
@@ -216,25 +216,25 @@ VMMR3DECL(bool)                 HMR3IsSv
 VMMR3DECL(bool)                 HMR3IsVmxEnabled(PUVM pUVM);
 
 VMMR3_INT_DECL(bool)            HMR3IsEventPending(PVMCPU pVCpu);
-VMMR3_INT_DECL(int)             HMR3Init(PVM pVM);
-VMMR3_INT_DECL(int)             HMR3InitCompleted(PVM pVM, VMINITCOMPLETED enmWhat);
-VMMR3_INT_DECL(void)            HMR3Relocate(PVM pVM);
-VMMR3_INT_DECL(int)             HMR3Term(PVM pVM);
-VMMR3_INT_DECL(void)            HMR3Reset(PVM pVM);
+VMMR3_INT_DECL(int)             HMR3Init(vbox_PVM pVM);
+VMMR3_INT_DECL(int)             HMR3InitCompleted(vbox_PVM pVM, VMINITCOMPLETED enmWhat);
+VMMR3_INT_DECL(void)            HMR3Relocate(vbox_PVM pVM);
+VMMR3_INT_DECL(int)             HMR3Term(vbox_PVM pVM);
+VMMR3_INT_DECL(void)            HMR3Reset(vbox_PVM pVM);
 VMMR3_INT_DECL(void)            HMR3ResetCpu(PVMCPU pVCpu);
-VMMR3_INT_DECL(void)            HMR3CheckError(PVM pVM, int iStatusCode);
-VMMR3DECL(bool)                 HMR3CanExecuteGuest(PVM pVM, PCPUMCTX pCtx);
+VMMR3_INT_DECL(void)            HMR3CheckError(vbox_PVM pVM, int iStatusCode);
+VMMR3DECL(bool)                 HMR3CanExecuteGuest(vbox_PVM pVM, PCPUMCTX pCtx);
 VMMR3_INT_DECL(void)            HMR3NotifyScheduled(PVMCPU pVCpu);
 VMMR3_INT_DECL(void)            HMR3NotifyEmulated(PVMCPU pVCpu);
 VMMR3_INT_DECL(bool)            HMR3IsActive(PVMCPU pVCpu);
-VMMR3_INT_DECL(void)            HMR3PagingModeChanged(PVM pVM, PVMCPU pVCpu, PGMMODE enmShadowMode, PGMMODE enmGuestMode);
-VMMR3_INT_DECL(int)             HMR3EmulateIoBlock(PVM pVM, PCPUMCTX pCtx);
-VMMR3_INT_DECL(VBOXSTRICTRC)    HMR3RestartPendingIOInstr(PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
-VMMR3_INT_DECL(int)             HMR3EnablePatching(PVM pVM, RTGCPTR pPatchMem, unsigned cbPatchMem);
-VMMR3_INT_DECL(int)             HMR3DisablePatching(PVM pVM, RTGCPTR pPatchMem, unsigned cbPatchMem);
-VMMR3_INT_DECL(int)             HMR3PatchTprInstr(PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
-VMMR3_INT_DECL(bool)            HMR3IsRescheduleRequired(PVM pVM, PCPUMCTX pCtx);
-VMMR3_INT_DECL(bool)            HMR3IsVmxPreemptionTimerUsed(PVM pVM);
+VMMR3_INT_DECL(void)            HMR3PagingModeChanged(vbox_PVM pVM, PVMCPU pVCpu, PGMMODE enmShadowMode, PGMMODE enmGuestMode);
+VMMR3_INT_DECL(int)             HMR3EmulateIoBlock(vbox_PVM pVM, PCPUMCTX pCtx);
+VMMR3_INT_DECL(VBOXSTRICTRC)    HMR3RestartPendingIOInstr(vbox_PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
+VMMR3_INT_DECL(int)             HMR3EnablePatching(vbox_PVM pVM, RTGCPTR pPatchMem, unsigned cbPatchMem);
+VMMR3_INT_DECL(int)             HMR3DisablePatching(vbox_PVM pVM, RTGCPTR pPatchMem, unsigned cbPatchMem);
+VMMR3_INT_DECL(int)             HMR3PatchTprInstr(vbox_PVM pVM, PVMCPU pVCpu, PCPUMCTX pCtx);
+VMMR3_INT_DECL(bool)            HMR3IsRescheduleRequired(vbox_PVM pVM, PCPUMCTX pCtx);
+VMMR3_INT_DECL(bool)            HMR3IsVmxPreemptionTimerUsed(vbox_PVM pVM);
 
 /** @} */
 #endif /* IN_RING3 */
@@ -244,4 +244,3 @@ RT_C_DECLS_END
 
 
 #endif
-
