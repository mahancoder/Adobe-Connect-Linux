#!/bin/bash
shopt -s extglob
echo "Copying files..." &&
INSTALL_PATH="${INSTALL_DIRECTORY:-/usr/bin/adobe/connect}" &&
mkdir -p $INSTALL_PATH &&
cp -r !(install.sh) $INSTALL_PATH &&
echo "Creating URL Scheme handlers..."
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" connect.desktop &&
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" open.sh &&
cp connect.desktop /usr/share/applications &&
xdg-mime default connect.desktop x-scheme-handler/connectpro &&
echo "Done!"
