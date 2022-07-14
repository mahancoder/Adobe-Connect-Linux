#!/bin/bash
shopt -s extglob
echo "Downloading Flash Player..." &&
mkdir .flash &&
cd .flash &&
wget "https://github.com/darktohka/clean-flash-builds/releases/download/v1.7/flash_player_patched_ppapi_linux.x86_64.tar.gz" -O ./flash.tar.gz &&
tar -xzf flash.tar.gz &&
mkdir -p $HOME/.local/lib/flash &&
cp ./libpepflashplayer.so $HOME/.local/lib/flash/ &&
cd .. &&
rm -r .flash/ &&
echo "Copying files..." &&
INSTALL_PATH="${INSTALL_DIRECTORY:-/usr/bin/adobe/connect}" &&
sudo mkdir -p $INSTALL_PATH &&
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" open.sh &&
sudo cp -r !(install.sh) $INSTALL_PATH &&
sudo chmod +x $INSTALL_PATH/open.sh $INSTALL_PATH/connect
echo "Creating URL Scheme handlers..."
sed -i "s|INSTALL_PATH|$INSTALL_PATH|g" connect.desktop &&
sudo cp connect.desktop /usr/share/applications &&
mkdir -p $HOME/.config &&
xdg-mime default connect.desktop x-scheme-handler/connectpro &&
echo "Done!"
