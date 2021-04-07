Compilation vers jeu d'instructions ARM
=======================================

# Dépendances

Compilateur pour arm: GCC

Émulateur: qemu

Installation sous Fedora:

    sudo dnf -y install gcc-arm-linux-gnu glibc-arm-linux-gnu qemu-user

Installation sous linux : sudo apt-get install arm-linux-gnueabihf-gcc qemu-user

# Exécution

Le binaire est exécuté par "Qemu en mode utilisateur", c'est à dire que les syscalls du programme émulé sont transformés en syscalls Linux. L'affichage se fait donc nativement sur la console.

Ceci dit, le programme émulé a quand même besoin d'une Libc ARM (notamment pour `putchar`, etc). C'est pour cette raison qu'on pointe QEMU sur le bon répetopire (option `-L) cf https://stackoverflow.com/a/36500696/117814


# Liens utiles

en vrac:

https://ownyourbits.com/2018/06/13/transparently-running-binaries-from-any-architecture-in-linux-with-qemu-and-binfmt_misc/

https://wiki.linaro.org/WorkingGroups/ToolChain/FAQ#line-122
