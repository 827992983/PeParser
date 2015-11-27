# PeParser
Parser for PE files (windows executable format) which focus on correctness.

# Brief
Focus on correctness mean of course reduced performance sometimes. Also, for the sake of simpicity, when parsing headers, the code will usually not buffer data as they are not meant to be accessed a lot in a short period of time. But unless you need to access the data in a near realtime fashion, this "slowness" should be absolutely no trouble.
This library is a collection of parser rather than a single parser, each with different goals. Right now, we have 4 differents parser available :
- The COFF header parser    : will parse only informations present in the COFF part of the PE header.
- The PE header parser      : an extension of the PE parser, it will parse information in both COFF and PE headers (along with data table informations).
- The section header parser : will parse informations about section headers.
- The section data parser   : a bit of a misnomer as it does not parser anything, but will extract data from sections.

Data layout of each header is described in the file *HeaderLayout.h*

# State
The library is considered in an "usable but highly incomplete" state right now. Some work is still required to be able to develop application like .NET obfuscator or disassembler for examples. Near todos are :
- Actually implement the section data parser.
- Add the possibility to buffer the calls.
- Complete the section header parser, and optimize it.
- Implement compilation object files section parsing.
- Find a better way to define header layout (less ugly synthax).
- A **LOT** of code cleaning.

# How to use
Using the library is actually pretty simple. Here is an example of accessing the number of section and the file characteristics from a COFF header parser :

```C++
#include <iostream>

#include <COFFHeaderParser.h>

int main()
{
  COFFHeaderParser parser("pathToYourFile");
  std::cout << "Number of sections : " << parser.getNumberOfSections() << std::endl;
  // Alternatively, you can do :
  // parser.retrieveFieldValue(COFFHeaderField::NumberOfSections)
  
  std::cout << "Now displaying file characteristics :" << std::endl;
  for(auto characteristic : parser.getCharacteristics())
  {
    std::cout << "- " << parser.getCharacteristicAsString(characteristic);
  }
  std::cout << std::endl;
}
```

For a x64 dll file with 6 sections :
```
Number of sections : 6
Now displaying file characteristics :
- Large address aware
- DLL
```

Also note that there's multiple ways to access the data. The most versatile way is using the "retrieveFieldValue" of each parsers, and using the enums defined in *HeaderLayout.h*.

More examples to come ...

# Building
To build the project, you'll need Visual Studio 2015. There's no linux port for the good reason that PE files on linux are pretty rare (they do not exist at all in fact), so this would be a pointless effort.
Simply opening the solution and building should do the trick. Resulting files will then bu outputed to :
```
$(Solution)\$(Configuration)\$(Platform)\PeParser.dll
```
For example, if your project root directory is "D:\MyProject", the configuration "Debug" and the platform "x64", resulting file will be outputed to

```
D:\MyProject\Debug\x64\PeParser.dll
```

# License
The project is under the MIT license (see the LICENSE.md for more informations)