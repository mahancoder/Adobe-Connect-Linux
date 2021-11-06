# Unofficial Adobe Connect Client for Linux
## Description:
Adobe Connect does not have a linux version officially, however, since it's written in flash, it's possible to run it in a browser. This project, uses an underlying chromium browser with flash support to run the flash file behind the meetings. It provides the binding necessary to automatically launch the app just like the Windows version for convenience.
This project uses [Chromium Embedded Framework](https://github.com/chromiumembedded) to utlize the underlying browser.
## Installation
To install the app, either [build from source](#building-from-source) or [download a prebuilt binary from the Releases section](https://github.com/mahancoder/Adobe-Connect-Linux/releases). Then, exectue `install.sh` **as root** to install the app.
### Building from source
First clone the repository
```
git clone https://github.com/mahancoder/Adobe-Connect-Linux.git
```
Then run `build.sh` to generate the binaries. Then refer to the [Installation](#installation) section to install it.
## Usage
You can use the app to open meeting launched from your browser. Currently, you can't enter the meeting url directly in the app, but rather you should enter it in the browser, and after logging in, click on the `Open in Application` button.
#### **NOTE:** You NEED to change your User-Agent to be able to open the meeting. For that, you can use the [User-Agent Switcher and Manager](https://chrome.google.com/webstore/detail/user-agent-switcher-and-m/bhchdcejhohfmigjafbampogmaanbfkg) extension.
