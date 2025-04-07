# my_sudo
An almost perfect reproduction of the sudo command in Linux, complete with user verification, password handling, and some flags.

## Build

To compile the binary:

    make
    # or
    make re

The compiled binary will be called:

    my_sudo

## Permissions

To be able to run it properly, set the correct permissions:

    make set_perm

This gives the binary root ownership and sets the SUID bit.

## Disclaimer

This project is for educational purposes only. Installing or using a custom sudo binary with elevated privileges can be dangerous. Do not use it on production or critical systems.

