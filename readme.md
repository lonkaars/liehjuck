# PWS Engine

This is the repository for the engine itself.

## Dependencies

- nlohmann/json
- vietjtnguyen/argagg

```sh
# yay
yay -S nlohmann-json argagg
```

```sh
# apt
apt-get install nlohmann-json3-dev argagg-dev
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
