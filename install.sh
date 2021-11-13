#!/bin/bash
shopt -s extglob
echo "Downloading icon..."
wget https://upload.wikimedia.org/wikipedia/commons/d/d0/Adobe_Connect_icon_%282020%29.svg -O connect.svg
convert connect.svg -transparent White connect.png
rm connect.svg connect-bg.png
echo "Copying files..." &&
INSTALL_PATH="${INSTALL_DIRECTORY:-/usr/bin/adobe/connect}" &&
mkdir -p $INSTALL_PATH &&
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" open.sh &&
cp -r !(install.sh) $INSTALL_PATH &&
echo "Creating URL Scheme handlers..."
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" connect.desktop &&
cp connect.desktop /usr/share/applications &&
xdg-mime default connect.desktop x-scheme-handler/connectpro &&
echo "Done!"
