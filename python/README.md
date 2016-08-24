# Python plotting tools

## Check out plotting tools
- [Recipe](https://github.com/artus-analysis/Artus/wiki/Standalone-Version-of-HarryPlotter#sparse-checkout)

## Initialisation

```bash
# Python 2.7
[ ! -e ~/bin ] && mkdir ~/bin
[ ! -e ~/bin/python ] && ln -s `which python27` ~/bin/python
export PATH=~/bin:$PATH

# Initialisation
source <path/to/>Artus/Configuration/scripts/ini_artus_python_standalone.sh
source <path/to/>Artus/HarryPlotter/scripts/ini_harry.sh
```
