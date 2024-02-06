//
// FILENAME.
//       MpTest3.c - Multi Processor Test 3 UEFI App.
//
// FUNCTIONAL DESCRIPTION.
//       The app calculates the limitation of maximum CPU number in Hob.
//
// NOTICE.
//       Author: visualge@gmail.com (CountChu)
//       Created on 2024/1/25
//       Updated on 2024/1/27
//

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/PlatformInitLib.h>

#include <Pi/PiDxeCis.h>
#include <Protocol/MpService.h>

#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Guid/HobList.h>

typedef struct {
  UINT32    ApicId;
  UINT32    Health;
  UINT64    StartupSignalAddress;
  UINT64    StartupProcedureAddress;
} PROCESSOR_HAND_OFF;

typedef struct {
  UINT32                ProcessorIndex;
  UINT32                CpuCount;
  UINT32                WaitLoopExecutionMode;
  UINT32                StartupSignalValue;
  PROCESSOR_HAND_OFF    Info[];
} MP_HAND_OFF;

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINTN MpHandOffSize;
  UINTN ProcessorHandOffSize;
  UINTN HobGuidTypeSize;
  UINTN MaxDataLength;
  UINTN MaxCpuCount;

  Print (L"MpTest3..........\n");

  MpHandOffSize = sizeof(MP_HAND_OFF);
  ProcessorHandOffSize = sizeof(PROCESSOR_HAND_OFF);  
  HobGuidTypeSize = sizeof(EFI_HOB_GUID_TYPE);

  Print(L"MpHandOffSize        : %xh (%d)\n", MpHandOffSize, MpHandOffSize);
  Print(L"ProcessorHandOffSize : %xh (%d)\n", ProcessorHandOffSize, ProcessorHandOffSize);
  Print(L"HobGuidTypeSize      : %xh (%d)\n", HobGuidTypeSize, HobGuidTypeSize);
  Print(L"\n");

  //
  // MaxDataLength = 0xFFF8 - HobGuidTypeSize
  //

  MaxDataLength = 0XFFF8 - HobGuidTypeSize;
  Print(L"MaxDataLength : %xh (%d)\n", MaxDataLength, MaxDataLength);

  //
  // MaxDataLength = MpHandOffSize + ProcessorHandOffSize * MaxCpuCount
  // MaxCpuCount = (MaxDataLength - MpHandOffSize) / ProcessorHandOffSize
  //

  MaxCpuCount = (MaxDataLength - MpHandOffSize) / ProcessorHandOffSize;
  Print(L"MaxCpuCount   : %xh (%d)\n", MaxCpuCount, MaxCpuCount);

  return EFI_SUCCESS;
}
