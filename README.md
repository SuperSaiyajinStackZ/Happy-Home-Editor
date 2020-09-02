# Happy-Home-Editor

A WIP Animal Crossing: Happy Home Designer Save Editor for Nintendo 3DS.

## Compilation
### Setting up your enviromment

To build Happy-Home-Editor from source, you will need to setup a system with devkitARM, libctru, citro2d and citro3d. Follow devkitPro's [Getting Started](https://devkitpro.org/wiki/Getting_Started) page to install pacman, then run `(sudo dkp-)pacman -S devkitARM libctru citro2d citro3d`. You will also need [bannertool](https://github.com/Steveice10/bannertool/releases/latest) and [makerom](https://github.com/profi200/Project_CTR/releases/latest) inside the `3ds` folder.

### Cloning the repo

To download the source you will need to clone it with submodules, this can be done by running
```
git clone --recursive https://github.com/SuperSaiyajinStackZ/Happy-Home-Editor.git
```
or if you've already cloned it running 
```
git submodule update --init --recursive
```
to update all the submodules.

### Compiling

Simply run `make` in the Happy-Home-Editor's 3ds directory.

## Credits
## Main Developers
- [RedShyGuy](https://github.com/RedShyGuy)
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ)

## Other
- [devkitPro](https://github.com/devkitPro), [Fincs](https://github.com/fincs), [Smealum](https://github.com/smealum), [Wintermute](https://github.com/WinterMute): For devkitARM, Citro2D, Citro3D and Libctru.

- [LeafEdit](https://github.com/Universal-Team/LeafEdit): Some code being re-used from it.

- [Universal-Team](https://github.com/Universal-Team): For [Universal-Core](https://github.com/Universal-Team/Universal-Core) and for [LeafEdit's](https://github.com/Universal-Team/LeafEdit) Pattern core, which is exactly the same for AC:HHD, so why not port it over there as well instead of writing from new.