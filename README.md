# fast fuse

<img align="right" src="./assets/logo.png" width="150px" alt="Fast Fuse Logo" />

Welcome to **fast fuse**, a compressor and decompressor that uses Huffman coding
to achieve high compression ratios. This project aims to provide a simple and
efficient way to compress and decompress files while maintaining their
integrity.

- Uses Huffman coding for efficient compression
- Simple and easy-to-use interface
- Works on multiple file types, including text and binary files
- Built with C for efficiency

# getting started

Clone the repo:

```sh
git clone git@github.com:username/fast-fuse.git .
```

Compile the program:

```sh
make
```

To compress a file, use the following command:

```sh
./antman/antman /path/to/file 1 > /path/to/output.bin
```

To decompress a file, use the following command:

```sh
./fast_fuse /path/to/output.bin 1 > /path/to/file
```
