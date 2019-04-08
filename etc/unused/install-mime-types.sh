#!/bin/sh

#NOTES on the xml file:
#see also https://developer.gnome.org/integration-guide/stable/mime.html.en
#see also https://wiki.archlinux.org/index.php/default_applications#MIME_types
# * note that mime-type tag is inside the mime-info tag (as per sites above)
# * glob-deleteall "indicates that patterns from previously parsed directories must be discarded" - https://developer.gnome.org/shared-mime-info-spec

#NOTES on desktop file:
#Desktop file installed in applications folder should include MimeType line such as:
#	MimeType=text/x-forwardfilesyncscript
# to indicate to the system that the application can open the mimetype


USER_MIMETYPES_DB_PATH=$HOME/.local/share/mime
# formerly $HOME/.mime.types according to whtyger on
# <https://unix.stackexchange.com/questions/270250/how-to-set-an-icon-for-custom-mimetype-in-linux-mint-mate>

USER_MIMETYPES_DB_PATH=$USER_MIMETYPES_DB_PATH/packages

SYSTEM_MIMETYPES_DB_PATH=/usr/share/mime/packages
SYSTEM_MIMETYPES_DB_PATH=/usr/share/mime

#MIMETYPES_DB_PATH=$USER_MIMETYPES_DB_PATH
#MIMETYPES_DB_PATH=$USER_MIMETYPES_DB_PATH
#or alternatively, install system-wide at:
MIMETYPES_DB_PATH=$SYSTEM_MIMETYPES_DB_PATH

if [ ! -d "$MIMETYPES_DB_PATH" ]; then
    mkdir "$MIMETYPES_DB_PATH"
fi
mime_name=model-b3d.xml
mime_path="$mime_name"
if [ -f "$mime_path" ]; then
    cp -f "$mime_path" "$MIMETYPES_DB_PATH/"
    update-mime-database "$MIMETYPES_DB_PATH"
else
    echo "ERROR: $mime_path must be in working directory in order to install it using this script!"
exit 1
fi
