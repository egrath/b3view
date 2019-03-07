# Changelog

## [git] - 2019-03-06
(poikilos)
### Added
* created install.sh and install.bat, and added Install and Usage
  to README.md
* icon, install scripts, and mime type (`model/b3d`)--see README.md
### Changed
* The program can now start without "test.b3d" in the current working
  directory (fixed Segmentation Fault).
* set `TARGET = b3view` in B3View.pro, so that binary is lowercase as
  per usual Linux naming conventions.

## [git-94e3b8f] - 2019-03-06
(poikilos)
### Added
* README.md

### Changed
(CGUITTFont methods are in CGUITTFont class unless otherwise specified)
* fixed instances of "0 as null pointer constant" (changed to `nullptr`)
* changed inconsistent use of spaces and tabs (changed tabs to 4 spaces)
* (UserInterface.cpp) fixed "logical not is only applied to the left hand side of this comparison..." (put parenthesis around `event.EventType == EET_GUI_EVENT`)
* Silently degrade to pixel font if font file cannot be read (fixes
  Segmentation Fault when font file cannot be read).
  * check for nullptr before using:
    * (CGUITTFont.cpp) `tt_face->face` in `getWidthFromCharacter`,
      `getGlyphByChar` (return 0 as bad as per convention:
      existing code already checks for 0--see
      `getWidthFromCharacter`), `getKerningWidth`,
      `draw`, `attach` (also don't copy null by
      reference there--instead, set to nullptr if source is nullptr)
  * check length of array before using
    * (CGUITTFont.cpp) elements of `Glyph` array (type `core::array<CGUITTGlyph>`) in `getHeightFromCharacter`
  * (CGUITTFont.cpp) check whether file can be read in `CGUITTFace::load` before proceeding

### Removed
* arial.tff removed, since it may be the "real" Arial font, which has a proprietary license

## [git-d964384] - 2019-03-06
### Changed
(first poikilos commit, based on https://github.com/egrath)
* changed `#include <irrlicht.h>` to `#include <irrlicht/irrlicht.h>`

### Added
* .gitignore (a [Qt .gitignore](https://github.com/github/gitignore/blob/master/Qt.gitignore))
* CHANGELOG.md