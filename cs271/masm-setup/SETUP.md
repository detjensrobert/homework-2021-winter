# Setting up MASM on Linux without Visual Studio

I am too stubborn to create a Windows VM for this class, so I installed MASM through Wine instead.

> **Note:** YMMV as for how well this will work with the material given and if you are able to replicate the
> functionality needed for the class outside of Visual Studio.

Steps mostly taken from [this guide by Ryan Eberhardt](
https://reberhardt.com/blog/programming/2016/01/30/masm-on-mac-or-linux.html).

---

1. Choose a Wine prefix:

   ```bash
   mkdir -p ~/.local/share/wineprefixes/masm/
   alias wine_masm="WINEARCH=win32 WINEPREFIX=~/.local/share/wineprefixes/masm/ wine"
   ```

2. Install MASM:

   ```bash
   wget http://website.assemblercode.com/masm32/masm32v11r.zip
   unzip masm32v11r.zip
   wine_masm install.exe
   ```

3. Install the Irvine support materials:

   ```bash
   wget http://www.asmirvine.com/gettingStartedVS2019/Irvine.zip
   unzip Irvine.zip
   mv ./irvine ~/.local/share/wineprefixes/masm/drive_c/Irvine
   ```

4. Set `PATH`, `LIB`, and `INCLUDE` in the Registry for convenience:

   ```bash
   wine_masm regedit
   ```

   Create the following String Values:
   - `HKEY_CURRENT_USER/Environment/PATH` -> `%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;C:\masm32\bin`
   - `HKEY_CURRENT_USER/Environment/INCLUDE` -> `C:\masm32\include;C:\Irvine`
   - `HKEY_CURRENT_USER/Environment/LIB` -> `C:\masm32\lib;C:\Irvine`

5. Grab the example projects:

   ```bash
   wget http://www.asmirvine.com/gettingStartedVS2019/Project{32,64}_VS2019.zip
   unzip Project32_VS2019.zip
   unzip Project64_VS2019.zip
   ```

6. Test it out:

   ```bash
   cd path/to/Project32_VS2019
   wine_masm ml -nologo -coff -c -Zi AddSub2.asm
   wine_masm link /NOLOGO /SUBSYSTEM:CONSOLE /ENTRY:main /LIBPATH:'C:\Irvine' irvine32.lib kernel32.lib user32.lib AddSub2.obj
   wine_masm AddSub2.exe
   ```

A Bash function to assemble, link, and run:

```bash
#!/bin/bash
set -e # Stop on errors

# Get the path to the file without a .asm extension
FILENAME="$(basename "$1")"
EXTENSION="${FILENAME##*.}"
shopt -s nocasematch   # String case-insensitive comparison
if [[ "$EXTENSION" = "asm" ]]; then
    FILENAME="${FILENAME%.*}"   # Remove extension
fi
UNIX_PATH="$(dirname "$1")/$FILENAME"

# Convert forwards slashes into backslashes
WINDOWS_PATH=$(echo "$UNIX_PATH" | sed 's|/|\\|')

shopt -s expand_aliases
alias wine_masm="WINEARCH=win32 WINEPREFIX=~/.local/share/wineprefixes/masm/ wine"

echo "Assembling..."
wine_masm ml -nologo -c -coff -Zi "$WINDOWS_PATH.asm"

echo "Linking..."
wine_masm link -nologo -subsystem:console -entry:main -libpath:'C:\Irvine' irvine32.lib kernel32.lib user32.lib "$WINDOWS_PATH.obj"

echo "Running..."
wine_masm "$WINDOWS_PATH.exe"
```
