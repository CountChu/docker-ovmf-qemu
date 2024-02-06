/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

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

EFI_GUID gEfiMpServiceProtocolGuid = {
  0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08}};
  
extern EFI_BOOT_SERVICES         *gBS;

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
  EFI_MP_SERVICES_PROTOCOL *Mp = NULL;
  UINTN NumProcessors;
  UINTN NumberOfEnabledProcessors;  
  //EFI_HOB_GENERIC_HEADER *CurrentHob;
  EFI_HOB_GUID_TYPE      *GuidHob;
  EFI_HOB_PLATFORM_INFO *PlatformInfoHob;  
  UINT32 MaxCpuCount;
  UINT32 BootCpuCount;
  UINT32 DefaultMaxCpuCount;
  BOOLEAN QemuFwCfgChecked;
  BOOLEAN QemuFwCfgSupported;
  BOOLEAN QemuFwCfgDmaSupported;

  Print (L"MpTest2..........\n");

  //
  // Locate MP_Service Protocol
  //

  Status = gBS->LocateProtocol(&gEfiMpServiceProtocolGuid, NULL, (VOID**)&Mp);
  if (EFI_ERROR (Status)) {
    Print(L"Unable to initialize MP protocol interface!");
    return EFI_UNSUPPORTED;
  }  

  //
  // Determine number of processors
  //

  Status = Mp->GetNumberOfProcessors(Mp, &NumProcessors , &NumberOfEnabledProcessors);
  if (EFI_ERROR(Status)) {
    Print( L"Mp->GetNumEnabledProcessors(): Unable to determine number of processors.\n") ;
    return EFI_UNSUPPORTED;
  }

  //
  // Report the processors.
  //

  Print(L"Number of Processors %d\n", NumProcessors);
  Print(L"Number of Enabled Processors %d\n", NumberOfEnabledProcessors);  

  //
  // Get the start of the HOB List from the system table or DXE services
  //

  GuidHob = GetFirstGuidHob(&gUefiOvmfPkgPlatformInfoGuid);
  if (GuidHob == NULL) {
     Print(L"PlatformInfoHob is not found.\n");
     return EFI_UNSUPPORTED;
  }
  Print(L"\n");

  //
  // Report CPU numbers from PlatformInfoHob.
  //

  PlatformInfoHob = (EFI_HOB_PLATFORM_INFO *) GET_GUID_HOB_DATA(GuidHob);

  Print(L"Report CPU numbers from PlatformInfoHob.\n");  

  MaxCpuCount = PlatformInfoHob->PcdCpuMaxLogicalProcessorNumber;
  BootCpuCount = PlatformInfoHob->PcdCpuBootLogicalProcessorNumber;
  DefaultMaxCpuCount = PlatformInfoHob->DefaultMaxCpuNumber;
  QemuFwCfgChecked = PlatformInfoHob->QemuFwCfgChecked;
  QemuFwCfgSupported = PlatformInfoHob->QemuFwCfgSupported;
  QemuFwCfgDmaSupported = PlatformInfoHob->QemuFwCfgDmaSupported;


  Print(L"MaxCpuCount           = %d\n", MaxCpuCount);
  Print(L"BootCpuCount          = %d\n", BootCpuCount);
  Print(L"DefaultMaxCpuCount    = %d\n", DefaultMaxCpuCount);
  Print(L"QemuFwCfgChecked      = %d\n", QemuFwCfgChecked);
  Print(L"QemuFwCfgSupported    = %d\n", QemuFwCfgSupported);
  Print(L"QemuFwCfgDmaSupported = %d\n", QemuFwCfgDmaSupported);

  Print(L"size of EFI_HOB_GUID_TYPE: %x\n", sizeof(EFI_HOB_GUID_TYPE));

  return EFI_SUCCESS;
}
