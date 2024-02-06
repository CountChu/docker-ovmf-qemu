#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/ShellCEntryLib.h>
#include  <Pi/PiDxeCis.h>
#include  <Protocol/MpService.h>

EFI_GUID  gEfiMpServiceProtocolGuid = { 0x3fdda605, 0xa76e, 0x4f46, 
						{ 0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08 }};
  
extern EFI_BOOT_SERVICES         *gBS;

int
EFIAPI
main (
  IN int Argc,
  IN CHAR16 **Argv
  )
{
	EFI_STATUS	Status;
	EFI_MP_SERVICES_PROTOCOL	*MP=NULL;
	UINTN   i;	
	UINTN	NumProcessors;
	UINTN	NumberOfEnabledProcessors;

	EFI_PROCESSOR_INFORMATION	ProcessorInfo;
	
	//Get MP_Service Protocol
	Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, (VOID**)&MP);
	if (EFI_ERROR (Status)) {
		Print(L"Unable to initialize MP protocol interface!");
		return EFI_UNSUPPORTED;
	}
	
	// Determine number of processors
	Status = MP->GetNumberOfProcessors( MP, &NumProcessors , &NumberOfEnabledProcessors );
	
	if (EFI_ERROR (Status))
	{
		Print( L"MP->GetNumEnabledProcessors:Unable to determine number of processors\n") ;
		return EFI_UNSUPPORTED;
	}	
	Print(L"Number of Processors %d\n",NumProcessors);
	Print(L"Number of Enabled Processors %d\n",NumberOfEnabledProcessors);
	
	//Get more information by GetProcessorInfo
	for (i=0;i<NumProcessors;i++)
	{
		Status = MP->GetProcessorInfo(MP, i , &ProcessorInfo);
		
		Print( L"Prcoessor #%d ACPI Processor ID = %lX, Flags = %x, Package = %x, Core = %x, Thread = %x \n", 
					i,
					ProcessorInfo.ProcessorId, 
					ProcessorInfo.StatusFlag,
					ProcessorInfo.Location.Package,
					ProcessorInfo.Location.Core,
					ProcessorInfo.Location.Thread);
	}
	
	return EFI_SUCCESS;
}

