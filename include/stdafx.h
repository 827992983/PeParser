// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include <targetver.h>

#define WIN32_LEAN_AND_MEAN             // Exclure les en-t�tes Windows rarement utilis�s
// Fichiers d'en-t�te Windows�:
#include <windows.h>

#include <BasicParser.h>
#include <Characteristics.h>
//#include <CharToInteger.h>
#include <COFFHeaderParser.h>
#include <DataDirectoryTable.h>
#include <DllCharacteristics.h>
#include <EpochConverter.h>
#include <FileValueReader.h>
#include <GUISubsystem.h>
#include <HeaderLayout.h>
#include <MachineID.h>
#include <PeDataDirectory.h>
#include <PEFileParser.h>
#include <HeaderField.h>
#include <PeHeaderParser.h>
#include <SectionHeaderParser.h>
#include <SectionParser.h>
