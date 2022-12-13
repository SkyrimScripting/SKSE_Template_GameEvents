> 📜 other templates available at https://github.com/SkyrimScripting/SKSE_Templates

# SKSE - Game Events

A simple SKSE plugin for Skyrim using:

- C++
- CMake
- [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)
  - _automatically downloaded using vcpkg integration of CMake_

> Because this uses CommonLibSSE NG, it supports Skyrim SSE, AE, GOG, and VR!

## What does it do?

It writes to a log file whenever certain events in the game happen:
- Whenever the player or any NPC "activates" something (_e.g. opening a door, interacting with an object, etc_)
- Whenever a game menu is opened or closed

There are many more events which you can easily monitor via your SKSE plugins!

To find some, I recommend searching [CommonLibSSE](https://github.com/CharmedBaryon/CommonLibSSE-NG) for files with `TES*Event` in their names.

1. Visit this link: https://github.com/CharmedBaryon/CommonLibSSE-NG
2. Press the `T` key to open the fuzzy find file search
3. Type `TESEvent`
4. Choose any of the files that show up! They're probably events that you can get via an event sink 😸

Read [`plugin.cpp`](plugin.cpp) for details on what it's doing!

## Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition is fine!_)
- [`vcpkg`](https://github.com/microsoft/vcpkg)
  - 1. Clone the repository using git OR [download it as a .zip](https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip)
  - 2. Go into the `vcpkg` folder and double-click on `bootstrap-vcpkg.bat`
  - 3. Edit your system or user Environment Variables and add a new one:
    - Name: `VCPKG_ROOT`  
      Value: `C:\path\to\wherever\your\vcpkg\folder\is`

Once you have Visual Studio 2022 installed, you can open this folder in basically any C++ editor, e.g. [VS Code](https://code.visualstudio.com/) or [CLion](https://www.jetbrains.com/clion/) or [Visual Studio](https://visualstudio.microsoft.com/)
- > _for VS Code, if you are not automatically prompted to install the [C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions, please install those and then close VS Code and then open this project as a folder in VS Code_

You may need to click `OK` on a few windows, but the project should automatically run CMake!

It will _automatically_ download [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) and everything you need to get started making your new plugin!

## Project setup

By default, when this project compiles it will output a `.dll` for your SKSE plugin into the `build/` folder.

But you probably want to put the `.dll` into your Skyrim mods folder, e.g. the mods folder used by Mod Organizer 2 or Vortex.

You can configure this project to _automatically_ output the SKSE plugin `.dll` into:
- `<your mods folder>\<name you give this project>\SKSE\Plugins\<your mod>.dll`  
  if you set the `SKYRIM_MODS_FOLDER` environment variable to the **root of your mods folder** (i.e. `<your mods folder>`)

- **Example:**
    - Name: `SKYRIM_MODS_FOLDER`  
      Value: `C:\path\to\wherever\your\Skyrim\mods\are`

## Setup your own repository

If you clone this template on GitHub, please:

- Go into `LICENSE` and change the year and change `<YOUR NAME HERE>` to your name.
- Go into `CODE_OF_CONDUCT.md` and change `<YOUR CONTACT INFO HERE>` to your contact information.

It's good to have a `Code of Conduct` and GitHub will show your project's `CODE_OF_CONDUCT.md` in the project sidebar.

If you'd like to know more about open source licenses, see:
- [Licensing a repository](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository)
- [Choose an open source license](https://choosealicense.com/)

**If you use this template, PLEASE release your project as a public open source project.** 💖

**PLEASE DO NOT RELEASE YOUR SKSE PLUGIN ON NEXUS/ETC WITHOUT MAKING THE SOURCE CODE AVAILABLE**
