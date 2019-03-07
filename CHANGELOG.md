# Changelog

## [git] - 2019-03-06
(first poikilos commit, based on https://github.com/egrath)
### Added
(CGUITTFont methods are in CGUITTFont class unless otherwise specified)
* README.md
* .gitignore (a [Qt .gitignore](https://github.com/github/gitignore/blob/master/Qt.gitignore))

### Changed
* changed `#include <irrlicht.h>` to `#include <irrlicht/irrlicht.h>`
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
