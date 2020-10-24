# PWS Engine

This is the repository for the engine itself.

## Dependencies

- nlohmann/json
- vietjtnguyen/argagg
- [libxcb](https://cgit.freedesktop.org/xcb/libxcb/)

```sh
# yay
yay -S nlohmann-json argagg libxcb xcb-util
```

```sh
# apt
apt-get install nlohmann-json3-dev argagg-dev libxcb1 libxcb1-dev libxcb-xtest0 libxcb-xtest0-dev
```

## Contributing

I'm too lazy to make a code of conduct so here are some rules:

- Run `make format` before merging/pushing to the master branch and before pull requests
- Class/typedef/struct names should start with a capital letter
- Dependencies should be handled by the distro's package manager
- Tabs > spaces (clang format should convert these but still)
- The master branch should always contain working code
- The dev branch should contain working/experimental code
- Create a branch with your feature name for broken/WIP code

## Building

```
make
./pws-engine
```

## Documentation

All documentation is handled by doxygen. There is currently a pws-documentation repository, but I (Loek) will attempt to move all documentation to this repo. The doc/ folder is, and always will be in .gitignore to keep repository size down.

