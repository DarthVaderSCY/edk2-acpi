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

/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/AcpiLib.h>
#include <Library/DebugLib.h>

STATIC CONST EFI_GUID acpiTableFile = { 0x3b45f660, 0x2fa5, 0x4912, { 0xa4, 0x83, 0x0f, 0x25, 0x3e, 0x40, 0x76, 0x92 } };

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS            Status;
  Status = LocateAndInstallAcpiFromFv (&acpiTableFile);
  if (Status == EFI_SUCCESS) {
    Print (L"Success\n");
  } else if (Status == EFI_NOT_FOUND) {
    Print (L"Not Found\n");
  } else {
    Print (L"Error number %x\n", Status);
  }

  return EFI_SUCCESS;
}
