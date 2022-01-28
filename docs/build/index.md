---
title: Installing the SDK
breadcrumb: SDK
---
# Build and run your own version of Upsilon

## Install the SDK

### Windows

#### With Msys2
[Msys2](https://www.msys2.org/) environment is recommended by Numworks to get most of the required tools on Windows easily. It's where you'll paste all the commands of this tutorial. Once it's installed, paste these commands into the Msys2 terminal.

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freetype mingw-w64-x86_64-pkg-config mingw-w64-x86_64-libusb git make python
echo "export PATH=/mingw64/bin:$PATH" >> .bashrc
```

Next, you'll need to install the [GCC toolchain for ARM](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). When prompted for an install location, choose `C:\msys64\home\User\gcc-arm\`. You'll then need to add this folder to your $PATH. Just enter:

```bash
echo "export PATH=$PATH:$HOME/gcc-arm/bin" >> .bashrc
```
Then, restart your terminal and that's it.

<br>
<br>

#### With WSL

You need a windows version >= 1903.

<br>

##### WSL Installation

1. Use simultaneously win + X keys and then click on "admin powershell".
```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux all /norestart
```
This command activate WSL functionalities.

```powershell
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
This one allows virtual machines developed by Microsoft.

2. Restart your computer.

3. Download [this file](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi) and follow instructions.

4. Now open powershell admin like before and type:
```powershell
wsl --set-default-version 2
```
5. Download [Ubuntu](https://www.microsoft.com/store/apps/9n6svws3rx71) from Microsoft store. You can also use [Debian](https://www.microsoft.com/store/productId/9MSVKQC78PK6).

WSL is now installed.

<br>

##### Usbipd installation to connect your calculator
If you want to connect to the calculator, you have to connect to install this [tool](https://github.com/dorssel/usbipd-win/releases/download/v1.3.0/usbipd-win_1.3.0.msi). This will allow you to connect WSL to the calculator through internet. Follow the on screen information to install.
###### Ubuntu
1. In a WSL Ubuntu command prompt, type:
```bash
sudo apt install linux-tools-5.4.0-77-generic hwdata
```
2. Edit /etc/sudoers so that root can find the usbip command. On Ubuntu, run this command.
```bash
sudo visudo
```
3. Add `/usr/lib/linux-tools/5.4.0-77-generic` to the beginning of secure_path. After editing, the line should look similar to this.
`Defaults secure_path="/usr/lib/linux-tools/5.4.0-77-generic:/usr/local/sbin:..."`

###### Debian
1. If you use debian for your WSL distro, use this command instead:
```bash
sudo apt install usbip hwdata usbutils
```
And that's all for installation and set up.

<br>

##### To connect your calculator
1. Open an Admin powershell and type:
```powershell
  usbipd wsl list
```
This will list your usb devices connected. Look at the BUSID column and remember the one for your calculator (it should be called "Numworks Calculator").
2. Now run this command replacing <BUSID> by your calculator's usb port id:
```powershell
usbipd wsl attach --busid <BUSID>
```
It will ask you to type your wsl's password and will connect your calculator to WSL.

<br>

### macOS

We recommend using [Homebrew](https://brew.sh) to install all dependencies. Once you have installed Homebrew, install all the dependencies with the following command:

```
brew install numworks/tap/epsilon-sdk
```

<br>

### Debian or Ubuntu

Most of the required tools are available as apt packages:

```
apt-get install build-essential git imagemagick libx11-dev libxext-dev libfreetype6-dev libpng-dev libjpeg-dev pkg-config apt-get install gcc-arm-none-eabi binutils-arm-none-eabi
```

<br>

### Fedora

First install basics dev tools.

```bash
dnf install make automake gcc gcc-c++ kernel-devel
```

Then install required packages.

```bash
dnf install git ImageMagick libX11-devel libXext-devel freetype-devel libpng-devel libjpeg-devel pkg-config
```

Then, install GCC cross compiler for ARM.

```bash
dnf install arm-none-eabi-gcc-cs arm-none-eabi-gcc-cs-c++
```

<br>

### Other Linux distro

You'll need to install the latest version of GCC and make it available in your $PATH:

1. Download the [GCC toolchain distributed by ARM](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). You should obtain a `gcc-arm-none-eabi-x-linux.tar.bz2` file.
2. Decompress that file with `tar xvfj gcc-arm-none-eabi-*-linux.tar.bz2`
3. Add the resulting folder to your $PATH. If you use bash,
```bash
echo "export PATH=\$PATH:`find $(pwd)/gcc-arm-none-eabi-*-update/bin -type d`" >> ~/.bashrc
```
should do what you need (you'll need to restart your terminal afterwards).

Also, try to find packages listed above in your default package manager.

<br>

## Retrieve the source code

The code is hosted on <a href="https://github.com/Lauryy06/Upsilon">GitHub</a>. You can retrieve it using the following command.

```
git clone https://github.com/Lauryy06/Upsilon.git
```

<br>

## Run Upsilon on your computer

Once the SDK has been installed, just open your terminal (Msys2, Terminal.app, xterm…) and type the following commands:

You have a lot of different choices to run Upsilon (depending on your model...).
The version of the hardware of the calculator is printed at its back.

<br>

### Simulator binaries for your platform

```
make PLATFORM=simulator clean
make PLATFORM=simulator epsilon_run
```

<br>

### Model n0100

(note: you can change the `EPSILON_I18N=en` flag to `fr`, `nl`, `pt`, `it`, `de`, `es` or `hu`).

```bash
make MODEL=n0100 clean
make MODEL=n0100 EPSILON_I18N=en OMEGA_USERNAME="{Your name, max 15 characters}" -j4
```

Now, run either:

```bash
make MODEL=n0100 epsilon_flash
```
to directly flash the calculator after pressing simultaneously `reset` and `6` buttons and plugging in.

<br>

or:

```bash
make MODEL=n0100 OMEGA_USERNAME="" binpack -j4
```
to make binpack witch you can flash to the calculator from [Ti-planet's webDFU](https://ti-planet.github.io/webdfu_numworks/n0100/). Binpacks are a great way to share a custom build of Upsilon to friends.

<br>

### Model n0110


```bash
make clean
make OMEGA_USERNAME="{Your name, max 15 characters}" -j4
```

Now, run either:

```bash
make epsilon_flash
```
to directly flash the calculator after pressing simultaneously `reset` and `6` buttons and plugging in.

<br>

or:

```bash
make OMEGA_USERNAME="" binpack -j4
```
to make binpack witch you can flash to the calculator from [Ti-planet's webDFU](https://ti-planet.github.io/webdfu_numworks/n0110/). Binpacks are a great way to share a custom build of Upsilon to friends.

<br>

### Web simulator

First, install emsdk :

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest-fastcomp
./emsdk activate latest-fastcomp
source emsdk_env.sh
```

Then, compile Upsilon :

```bash
make clean
make PLATFORM=simulator TARGET=web OMEGA_USERNAME="{Your name, max 15 characters}" -j4
```

The simulator is now in `output/release/simulator/web/simulator.zip`

<br>

### 3DS Simulator

You need devkitPro and devkitARM installed and in your path (instructions [here](https://devkitpro.org/wiki/Getting_Started))

```bash
git clone --recursive https://github.com/Lauryy06/Upsilon.git
cd Upsilon
git checkout --recursive upsilon-dev
make PLATFORM=simulator TARGET=3ds -j
```
You can then put epsilon.3dsx on a SD card to run it from the HBC or use 3dslink to launch it over the network:

```bash
3dslink output/release/simulator/3ds/epsilon.3dsx -a <3DS' IP ADDRESS>
```

Congratulations, you're running your very own version of Upsilon!

To build with a special theme, please refer to this [page](../../themes/README.md).
