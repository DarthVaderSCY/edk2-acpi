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
#include <Library/CpuCacheInfoLib.h>

#include <Protocol/LoadedImage.h>       // to get parms
#include <Protocol/EfiShellInterface.h> //Shell 1.0
#include <Protocol/ShellParameters.h>   //Shell 2.0

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
  CPU_CACHE_INFO CpuCacheInfo[128];
  UINTN CpuCacheInfoCount;

  CpuCacheInfoCount = 128;

  Status = GetCpuCacheInfo(CpuCacheInfo, &CpuCacheInfoCount);

  if (!EFI_ERROR(Status))
  {
    UINTN Index;
    Print(L"+-------+--------------------------------------------------------------------------------------+\n");
    Print(L"| Index | Packge  CoreType  CacheLevel  CacheType  CacheWays (FA|DM) CacheSizeinKB  CacheCount |\n");
    Print(L"+-------+--------------------------------------------------------------------------------------+\n");

    for (Index = 0; Index < CpuCacheInfoCount; Index++)
    {
      Print(L"| %4x  | %4x       %2x        %2x          %2x       %4x     ( %x| %x) %8x         %4x     |\n",
            Index, CpuCacheInfo[Index].Package, CpuCacheInfo[Index].CoreType, CpuCacheInfo[Index].CacheLevel,
            CpuCacheInfo[Index].CacheType, CpuCacheInfo[Index].CacheWays, CpuCacheInfo[Index].FullyAssociativeCache,
            CpuCacheInfo[Index].DirectMappedCache, CpuCacheInfo[Index].CacheSizeinKB, CpuCacheInfo[Index].CacheCount);
    }

    Print(L"+-------+--------------------------------------------------------------------------------------+\n");
  }
  else
  {
    Print(L"\nGetCpuCacheInfo did NOT work: :-( \n");
  }

  return EFI_SUCCESS;
}
