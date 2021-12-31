/** @file
  This is a simple shell application

  Copyright (c) 2008, Intel Corporation                                                         
  All rights reserved. This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/LoadedImage.h>       // to get parms
#include <Protocol/EfiShellInterface.h> //Shell 1.0
#include <Protocol/ShellParameters.h>   //Shell 2.0

EFI_STATUS // Main using Argc &
    EFIAPI //   Argv
    SampleMain(
        IN UINTN Argc,
        IN CHAR16 **Argv)
{
  UINTN Index;
  UINTN J;
  CHAR16 *Temp;
  for (Index = 1; Index < Argc; Index++)
  {
    for (J = Index + 1; J < Argc; J++)
    {
      if (StrDecimalToUintn(Argv[Index]) < StrDecimalToUintn(Argv[J]))
      {
        Temp = Argv[Index];
        Argv[Index] = Argv[J];
        Argv[J] = Temp;
      }
    }
  }
  for (Index = 1; Index < Argc; Index++)
  {
    Print(L"%s ", Argv[Index]);
  }
  Print(L"\n");
  return EFI_SUCCESS;
}

/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status;
  EFI_SHELL_PARAMETERS_PROTOCOL *mEfiShellParametersProtocol;
  EFI_SHELL_INTERFACE *mEfiShellInterface;
  UINTN Argc;
  CHAR16 **Argv;

  //Initialize local protocol pointers
  mEfiShellParametersProtocol = NULL;
  mEfiShellInterface = NULL;

  // check input parameters from command line using UEFI Shell 2.0
  Status = gBS->OpenProtocol(ImageHandle,
                             &gEfiShellParametersProtocolGuid,
                             (VOID **)&mEfiShellParametersProtocol,
                             ImageHandle,
                             NULL,
                             EFI_OPEN_PROTOCOL_GET_PROTOCOL);
  if (!EFI_ERROR(Status))
  {
    Argc = mEfiShellParametersProtocol->Argc;
    Argv = mEfiShellParametersProtocol->Argv;
    // Call our main with Argc / Argv parameters
    SampleMain(Argc, Argv);
  }
  else
  { // else check if EFI Shell 1.0
    Status = gBS->OpenProtocol(ImageHandle,
                               &gEfiShellInterfaceGuid,
                               (VOID **)&mEfiShellInterface,
                               ImageHandle,
                               NULL,
                               EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status))
    {
      Argc = mEfiShellInterface->Argc;
      Argv = mEfiShellInterface->Argv;
      SampleMain(Argc, Argv);
    }
    else
    {
      Print(L"\nGetting Shell params did NOT work: :-( \n");
    }
  }

  return EFI_SUCCESS;
}
