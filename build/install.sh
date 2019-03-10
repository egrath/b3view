#!/bin/bash
echo
echo
if [ -z "$PREFIX" ]; then PREFIX=/usr/local; fi
dest_bin_dir="$PREFIX/bin"
dest_share_dir="$PREFIX/share"
project_unix_name=b3view
dest_name=$project_unix_name
src_path="$project_unix_name"
try_dest_bin="$dest_bin_dir/$dest_name"
icon_name="b3view.png"
icon_src_path="icons/$icon_name"
shortcut_name="org.poikilos.b3view.desktop"
shortcut_src_path="applications/$shortcut_name"
icons_root=$PREFIX/share/pixmaps
applications_path=$PREFIX/share/applications

mimes_path="share/mime/packages"
mime_name=model-b3d.xml
mime_path="$mimes_path/$mime_name"
USER_MIMETYPES_DB_PATH=$HOME/.local/share/mime
#USER_MIMETYPES_PATH="$USER_MIMETYPES_DB_PATH/packages"
SYSTEM_MIMETYPES_DB_PATH=/usr/share/mime
#SYSTEM_MIMETYPES_PATH=$SYSTEM_MIMETYPES_DB_PATH/packages
MIMETYPES_DB_PATH=$SYSTEM_MIMETYPES_DB_PATH


if [ ! -f $src_path ]; then
    echo "ERROR: Nothing done since missing $src_path"
    sleep 4
    exit 1
fi

if [ -d "$try_dest_bin" ]; then
    echo "ERROR: nothing done since '$try_dest_bin' is a directory (should be deleted or a binary file of old version)"
    sleep 4
    exit 2
fi

PROFILE_ENABLE=false
if [ -f "$try_dest_bin" ]; then
    rm -f "$try_dest_bin"
    if [ -f "$try_dest_bin" ]; then
        echo "WARNING: can't remove old $try_dest_bin, so"
	PROFILE_ENABLE=true
    fi
fi

cp -f "$src_path" "$try_dest_bin"

if [ ! -f "$try_dest_bin" ]; then
    PROFILE_ENABLE=true
    prev_dir="$dest_bin_dir"
    echo "WARNING: can't write to $prev_dir, so"
fi
if [ "@$PROFILE_ENABLE" = "@true" ]; then
    dest_bin_dir="$USER/.local/bin"
    echo "installing to '$dest_bin_dir'."
    echo "Press Ctrl C to cancel..."
    sleep 1
    echo "3..."
    sleep 1
    echo "2..."
    sleep 1
    echo "1..."
    sleep 1
else
    echo "Successfully installed as '$try_dest_bin'"
fi
if [ "@$PROFILE_ENABLE" = "@true" ]; then
    if [ ! -d "$dest_bin_dir" ]; then mkdir "$dest_bin_dir"; fi
    cp -f $src_path "$dest_bin_dir/"
    icons_root="$USER/.local/share/icons"
    applications_path="$USER/.local/share/applications"
    MIMETYPES_DB_PATH="$USER_MIMETYPES_DB_PATH"
fi
if [ ! -d "$icons_root" ]; then
    mkdir -p "$icons_root"
fi
cp -f "$icon_src_path" "$icons_root/"
if [ -f "$icons_root/$icon_name" ]; then
    echo "Successfully copied '$icons_root/$icon_name'"
else
    echo "FAILED to install '$icons_root/$icon_name'"
fi

if [ ! -d "$applications_path" ]; then
    mkdir -p "$applications_path"
fi

#if [ "@$PROFILE_ENABLE" = "@true" ]; then
# always rewrite, since PREFIX may differ
if [ -f "$shortcut_src_path" ]; then
    cat "$shortcut_src_path" | grep -v Exec= | grep -v Icon= > "$applications_path/$shortcut_name"
    echo "Exec=$dest_bin_dir/$project_unix_name" >> "$applications_path/$shortcut_name"
    echo "Icon=$icons_root/$icon_name" >> "$applications_path/$shortcut_name"
    echo >> "$applications_path/$shortcut_name"
else
    echo "ERROR: No icon installed since missing '$shortcut_src_path'"
fi
#else
    #cp -f "$shortcut_src_path" "$applications_path/"
#fi

if [ -f "$applications_path/$shortcut_name" ]; then
    echo "Successfully copied '$applications_path/$shortcut_name'"
else
    echo "FAILED to install '$applications_path/$shortcut_name'"
fi

if [ ! -d "$MIMETYPES_DB_PATH/packages" ]; then
    # echo "Creating '$MIMETYPES_DB_PATH/packages'..."
    mkdir "$MIMETYPES_DB_PATH/packages"
fi
update_mime_enable=false
if [ ! -f "$mime_path" ]; then
    echo "ERROR: Stopped installing mime types since missing $mime_path"
    exit 1
fi
try_dest="$MIMETYPES_DB_PATH/packages/$mime_name"
if diff -q $mime_path $try_dest; then
    echo "* (You already have an identical $try_dest)"
else
    cp -f "$mime_path" "$MIMETYPES_DB_PATH/packages/"
    if [ -f "$try_dest" ]; then
	echo "* Successfully copied '$try_dest'"
	update_mime_enable=true
    fi
fi
mime_name=model-x.xml
mime_path="$mimes_path/$mime_name"
if [ ! -f "$mime_path" ]; then
    echo "ERROR: Stopped installing mime types since missing $mime_path"
    exit 1
fi
try_dest="$MIMETYPES_DB_PATH/packages/$mime_name"
if diff -q $mime_path $try_dest; then
    echo "* (You already have an identical $try_dest)"
else
    cp -f "$mime_path" "$MIMETYPES_DB_PATH/packages/"
    if [ -f "$try_dest" ]; then
	echo "* Successfully copied '$try_dest'"
	update_mime_enable=true
    fi
fi

# Since OBJ Mime type is broken on linux (detected as TGIF obj/sym
# hyperlinked vector graphics format unrelated to Wavefront OBJ
# format but sharing the same file extension), trying
# to add an overlapping mime type breaks it worse (KDE detects the
# file as "plain text file" if the xml file below is installed)
mime_name=model-obj.xml
mime_path="$mimes_path/$mime_name"
#if [ ! -f "$mime_path" ]; then
    #echo "ERROR: Stopped installing mime types since missing $mime_path"
    #exit 1
#fi
try_dest="$MIMETYPES_DB_PATH/packages/$mime_name"
#if diff -q $mime_path $try_dest; then
    #echo "* (You already have an identical $try_dest)"
#else
    #cp -f "$mime_path" "$MIMETYPES_DB_PATH/packages/"
    if [ -f "$MIMETYPES_DB_PATH/packages/$mime_name" ]; then
	# echo "* Successfully copied '$MIMETYPES_DB_PATH/packages/$mime_name'"
	echo "* Removing '$MIMETYPES_DB_PATH/packages/$mime_name' (overlaps with system usually)"
	rm -f "$MIMETYPES_DB_PATH/packages/$mime_name"
	update_mime_enable=true
    fi
#fi

mime_name=model-ms3d.xml
mime_path="$mimes_path/$mime_name"
if [ ! -f "$mime_path" ]; then
    echo "ERROR: Stopped installing mime types since missing $mime_path"
    exit 1
fi
try_dest="$MIMETYPES_DB_PATH/packages/$mime_name"
if diff -q $mime_path $try_dest; then
    echo "(You already have an identical $try_dest)"
else
    cp -f "$mime_path" "$MIMETYPES_DB_PATH/packages/"
    if [ -f "$MIMETYPES_DB_PATH/packages/$mime_name" ]; then
	echo "Successfully copied '$MIMETYPES_DB_PATH/packages/$mime_name'"
	# rm -f "$MIMETYPES_DB_PATH/packages/$mime_name"
	update_mime_enable=true
    fi
fi

if [ "@$update_mime_enable" = "@true" ]; then
    echo "Updating mime type database '$MIMETYPES_DB_PATH'..."
    update-mime-database "$MIMETYPES_DB_PATH"  # must contain packages
fi
echo "Done."

echo
echo
