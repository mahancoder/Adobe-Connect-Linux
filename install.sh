#!/bin/bash
shopt -s extglob
echo "Copying files..." &&
INSTALL_PATH="${INSTALL_DIRECTORY:-/usr/bin/adobe/connect}" &&
mkdir -p $INSTALL_PATH &&
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" open.sh &&
cp -r !(install.sh) $INSTALL_PATH &&
chmod +x $INSTALL_PATH/open.sh $INSTALL_PATH/connect
echo "Creating URL Scheme handlers..."
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" connect.desktop &&
cp connect.desktop /usr/share/applications &&
mkdir -p $HOME/.config &&
xdg-mime default connect.desktop x-scheme-handler/connectpro &&
echo "Done!"
