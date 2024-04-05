# Koita
Image to ASCII converter written in C

----

# How to run
```
$ git clone https://github.com/malliamanis/koita.git && cd koita
$ make deps release
$ ./build/release/koita
```

## How to use
```
./build/release/koita [image]
```
or
```
./build/release/koita [image] [character width in pixels]
```
The second option determines how many pixels wide a single ASCII character will be. For example if it is set to 4, each character will be equivalent to 16 pixels in the image
