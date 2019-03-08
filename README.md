# b3view
View B3D or X files (and possibly other files supported by Irrlicht)
with double-click if this program is associated with the file types.

This is a modernized fork by poikilos (see CHANGELOG.md).

## Compiling
* Make sure you have the Irrlicht and Qt development packages
  (such as via `sudo dnf -y install qt-devel qt-creator irrlicht-devel`
  on Fedora 29)
* Open Qt Creator, click File, Open, then choose this project's .pro
  file.
* Build & Run (if you have trouble compiling, see
  [filehandoff#compiling-issues](https://github.com/poikilos/filehandoff#compiling-issues))
* Copy all of the files from `./build` to your actual build directory,
  if your build directory is not `./build`
* (optional) Copy your favorite public-licensed font over
  `./build/ClearSansRegular.tff` or to current working directory of
  program

## Installation
### Windows
* copy install.bat to your build directory if you are not using a
  release version.
* double-click install.bat (read any messages that appear then press
  a key to continue when prompted).
* Associate the b3d file extension (and possibly other Irrlicht-
  compatible 3D mesh formats) with
  `%USERPROFILE%\Applications\b3view\b3view.exe` (right-click a b3d
  file, then Open With, show additional programs, then either paste that
  path or choose This PC, C:, Users, your username, Applications,
  b3view, b3view.exe)

### GNU/Linux Systems
* copy install.sh to your build directory if you are not using a release
  version and your build directory is not `./build`
* run install.sh as root, such by running `sudo bash install.sh` in
  Terminal from the project directory (if you are not root, the install
  will install to $USER/Applications after giving an opportunity to
  cancel with Ctrl C during a countdown).
  (the script will install the "Blitz3D Model File" (`model/b3d`) mime
  type, which will be used for all files with the `b3d` extension--
  this allows associating the file type with a program).
* Associate the b3d file extension (and possibly other Irrlicht-
  compatible 3D mesh formats) with b3view: Right-click any B3D file,
  "Open With...", find or type b3view, then check "Remember
  application..." or "Set as default..." or something similar depending
  on your desktop environment (an option to always use the same program
  will only be available if the mime type was successfully installed for
  the user profile or system such as via install.sh).


## Usage
* You can click "File," "Open.", then choose an Irrlicht-compatible B3D
  file. However, the program is much easier to use if you associate the
  format with b3view (see "Installation" above) so you can just double-
  click the file to open b3view automatically.

## Known Issues
* Warn on missing texture.
* Implement Start/Stop button functionality.
* Test and complete install.bat on Windows.

## Authors
* ClearSansRegular.ttf (Apache 2.0 License) by Intel
  <https://01.org/clear-sans> via
  <https://www.fontsquirrel.com/fonts/clear-sans>
* ninja.b3d, nskin*.jpg by Psionic (psionic3d.co.uk)
  <http://www.psionic3d.co.uk/downloads/ninja.zip>
  (I've seen this file ripped and in several repos, but finally found
  the original site above, which has additional skins not found
  elsewhere, via included "ninja animation ranges.txt" from
  <https://sledjhamr.org/source/media/Irrlicht/>)
  "Feel free to use however you like, commercial etc, credits are
  Appreciated..." -Psionic
* Until original author egrath responds, all files not mentioned above
  are licensed under the GitHub ToS (GitHub has rights to distribute
  the files).
