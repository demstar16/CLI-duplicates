# duplcates

Due date: **11:59pm Friday 22nd October (end of week 12)**

Grade Weighting: **25%**

Authors: Dempsey Thompson, Zach Manson

`duplicates` is a command line utility to locate and report duplicate files in (and below) a named directory based on SHA2 hashes.

## Usage

Compile using command `make` in root directory.

Run `duplicates` using
```
./duplicates directory_path [-a] [-A] [-f filename] [-h SHA2_hash] [-l] [-q]
```

`-a` includes hidden files

`-A` returns 0 as per project requirements

`-f filename` to find duplicates of a single file

`-h SHA2_hash` to match files of a given hash

`-l` to list all duplicate files found

`-q` to execute quietly
